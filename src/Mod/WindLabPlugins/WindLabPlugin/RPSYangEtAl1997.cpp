/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "RPSYangEtAl1997.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <unsupported/Eigen/FFT>
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSYangEtAl1997, WindLabAPI::WindLabFeatureSimulationMethod)

CRPSYangEtAl1997::CRPSYangEtAl1997()
{ 
    this->OutputUnit.setValue("m/s");
}


bool CRPSYangEtAl1997::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    QMessageBox::warning(0,QString::fromLatin1("Yang et al"), QString::fromLatin1("No additional data required."));
    return true;
}

bool CRPSYangEtAl1997::Simulate(const WindLabAPI::WindLabSimulationData& Data, mat &dVelocityArray)
{
    // generate a random wind velocity
   const bool simResult = stationaryWind(Data, dVelocityArray);
   
   bool returnResult = true;

   if(!simResult)
   {
       Base::Console().Warning("The simulation has failed.\n");
       return simResult;
   }

   // is non-stationary wind is wanted and there is active modulation function in the simulation
   if(!Data.stationarity.getValue() && Data.uniformModulation.getValue())
   {
       vec modulationVar(Data.numberOfTimeIncrements.getValue());
       vec modulationVal(Data.numberOfTimeIncrements.getValue());
       mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

       returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

       Base::Vector3d location(0, 0, 0);

       for (int j = 0; j < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
       {
           location = Base::Vector3d(dLocCoord(j, 1), dLocCoord(j, 2), dLocCoord(j, 3));

           returnResult = WindLabAPI::CRPSWindLabFramework::ComputeModulationVectorT(Data, location, modulationVar, modulationVal);

           for (int i = 0; i < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue(); i++)
           {
              dVelocityArray(i,j) = modulationVal(i) * dVelocityArray(i,j);
           }
       }

    if(!returnResult)
    {
       Base::Console().Error("The computation of the modulation function has failed.\n") ;
       return false;
    }

   }

   return true;
}

// The simulation function
bool CRPSYangEtAl1997::stationaryWind(const WindLabAPI::WindLabSimulationData& Data, mat &dVelocityArray)
{
    auto PbuInfo = CRPSWindLabFramework::getWindLabFeatureDescription(Data.frequencyDistribution.getValue());

    if (!PbuInfo)
    {
       Base::Console().Warning("Invalid frequency distribution. The simulation has failed.\n") ;
       return false;
    }

    if (strcmp(PbuInfo->type.getValue(), "Double Index Frequency Discretization") != 0 || strcmp(PbuInfo->PluginName.getValue(), "WindLabPlugin") != 0)
    {
        Base::Console().Warning("This tool required the wind velocity to be simulated with the double index frequency discretization implemented by the WindLab plugin.\n");
        return false;
    }

    int n = Data.numberOfSpatialPosition.getValue();
    int N = Data.numberOfFrequency.getValue();
    double dt = Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
    double timeMin = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second);
    double deltaomega = Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
    int M = 2*N;
    int T = Data.numberOfTimeIncrements.getValue();

    vec PSD1(N);
    vec Kz(N);
    cx_mat B = Eigen::MatrixXcd::Zero(n,M);
    cx_mat G = Eigen::MatrixXcd::Zero(n,M);

    // local array for the location coordinates
    mat dLocCoord(n, 4);
    mat frequencies(N,n);

     bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if(!returnResult)
    {
        Base::Console().Warning("The computation of the location coordinates matrix has failed.\n");
       return false;
    }

    //compute the simulation point coordinates
    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.\n") ;
       return false;
    }

    mat thet(N, n);
    returnResult = CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the random phase angle matrix has failed.\n");
       return false;
    }

    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesMatrixFP(Data, frequencies);
    if (!returnResult) {
        Base::Console().Warning("The computation of the frequency matrix has failed.\n");
        return false;
    }

    std::complex<double> i2(0, 1);
    Eigen::FFT<double> fft;
    std::complex<double> coherenceValue;
    double C;

    double speed = 0.0;
    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, Base::Vector3d(dLocCoord(0, 1), dLocCoord(0, 2), dLocCoord(0, 3)), 0.00, speed);
    if (!returnResult) {
        Base::Console().Warning("The computation of the mean wind value has failed.\n");
        return false;
    }

    Base::Vector3d AA(dLocCoord(0, 1), dLocCoord(0, 2), dLocCoord(0, 3));
    Base::Vector3d BB(dLocCoord(1, 1), dLocCoord(1, 2), dLocCoord(1, 3));

    // pick two adjacent simulation and compute the distance between them
    double x = AA.x - BB.x, y = AA.y - BB.y, z = AA.z - BB.z;
    double distance = sqrt((x * x) + (y * y) + (z * z));

    // Simulation starts

    for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        for (int m = 1; m <= j && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++)
        {
            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++)
            {
                returnResult = CRPSWindLabFramework::ComputeAutoSpectrumValue(Data, AA,frequencies(l - 1, m - 1), 0, PSD1(l-1));
                if (!returnResult) {
                    Base::Console().Warning("The computation of the auto spectrum value has failed.\n");
                    return false;
                }
            }

            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++)
            {
                Kz(l - 1) = exp(-2 * frequencies(l - 1, m - 1) * distance * 7 / (speed + speed));
            }

            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++)
            {
                if (m == 1){
                    B(m - 1, l - 1) = 2 * sqrt(deltaomega) * pow(PSD1(l-1),0.5) * pow(Kz(l-1),abs(m-j)) * exp(i2 * thet(l - 1,m - 1));
                }
                else{
                    B(m - 1, l - 1) = 2 * sqrt(deltaomega)*pow(PSD1(l-1),0.5)*pow(Kz(l-1),abs(m-j))*pow((1-pow(Kz(l-1),2)),0.5)*exp(i2*thet(l - 1,m - 1));
                }
            }

        }

        for (int ii = 1; ii <= j && false == Data.isInterruptionRequested.getValue(); ii++)
        {
            G.row(ii-1) = (double)(M) *fft.inv( B.row(ii-1) );
        }
        int q = 0;
        double time = 0;

        for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue(); p++) {
            q = fmod(p-1,M);
            time = (p - 1) * dt + timeMin;
            dVelocityArray(p - 1, 0) = time;
            for (int k = 1; k <= j && false == Data.isInterruptionRequested.getValue(); k++) {
                dVelocityArray(p - 1, j) = dVelocityArray(p - 1, j) + real(G(k - 1,q) * exp(i2 * (k * deltaomega * time/n)));
            }
        }
    }

return returnResult;
}

// The simulation function in large scale mode
bool CRPSYangEtAl1997::SimulateInLargeScaleMode(const WindLabAPI::WindLabSimulationData& Data, QString &strFileName)
{
    auto PbuInfo = CRPSWindLabFramework::getWindLabFeatureDescription(Data.frequencyDistribution.getValue());

    if (!PbuInfo)
    {
       Base::Console().Warning("Invalid frequency distribution. The simulation has failed.\n") ;
       return false;
    }

    if (strcmp(PbuInfo->type.getValue(), "Double Index Frequency Discretization") != 0 || strcmp(PbuInfo->PluginName.getValue(), "WindLabPlugin") != 0)
    {
        Base::Console().Warning("This tool required the wind velocity to be simulated with the double index frequency discretization implemented by the WindLab plugin.\n");
        return false;
    }

    int n = Data.numberOfSpatialPosition.getValue();
    int N = Data.numberOfFrequency.getValue();
    double dt = Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
    double timeMin = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second);
    double deltaomega = Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
    int M = 2*N;
    int T = Data.numberOfTimeIncrements.getValue();

    vec PSD1(N);
    vec Kz(N);
    cx_mat B = Eigen::MatrixXcd::Zero(n,M);
    cx_mat G = Eigen::MatrixXcd::Zero(n,M);

    // local array for the location coordinates
    mat dLocCoord(n, 4);
    mat frequencies(N,n);

    // Get the current date and time
    std::string dateTimeStr = CRPSWindLabFramework::getCurrentDateTime();

    // Create the new file name by appending the date and time
    std::string newFileName = Data.workingDirectoryPath.getValue().string() + "/" + Data.fileName.getValue() + "_" + dateTimeStr + ".txt";
    
    // Define an output stream
    std::ofstream fout;

    // open the file output mode to erase its content first
    fout.width(10);
    fout.setf(std::ios::left);
    fout.setf(std::ios::fixed);
    fout.fill('0');
    fout.open(newFileName, std::ios::out);
    
    double value;

    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if(!returnResult)
    {
        Base::Console().Warning("The computation of the location coordinates matrix has failed.\n");
       return false;
    }

    //compute the simulation point coordinates
    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.\n") ;
       return false;
    }

    mat thet(N, n);
    returnResult = CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the random phase angle matrix has failed.\n");
       return false;
    }

    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesMatrixFP(Data, frequencies);

    std::complex<double> i2(0, 1);
    Eigen::FFT<double> fft;
    std::complex<double> coherenceValue;
    double C1;
    double C2;
    double C3;

    Base::Vector3d locationJ(0, 0, 0);
    Base::Vector3d locationK(0, 0, 0);

    // Simulation starts

    for (int j = 1;
         j <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++) {
        Base::Vector3d location(dLocCoord(j - 1, 1), dLocCoord(j - 1, 2), dLocCoord(j - 1, 3));

        for (int m = 1;
             m <= j && false == Data.isInterruptionRequested.getValue() && true == returnResult;
             m++) {
            // Auto spectrum
            for (int l = 1;
                 l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult;
                 l++) {
                returnResult = CRPSWindLabFramework::ComputeAutoSpectrumValue(
                    Data, location, frequencies(l - 1, m - 1), 0, PSD1(m - 1));
            }

            Base::Vector3d locationJ(dLocCoord(j - 1, 1), dLocCoord(j - 1, 2), dLocCoord(j - 1, 3));
            Base::Vector3d locationK(dLocCoord(m - 1, 1), dLocCoord(m - 1, 2), dLocCoord(m - 1, 3));

            for (int l = 1;
                 l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult;
                 l++) {
                returnResult = CRPSWindLabFramework::ComputeCrossCoherenceValue(
                    Data, locationJ, locationK, frequencies(l - 1, m - 1), 0, coherenceValue);
                Kz(l - 1) =
                    coherenceValue
                        .real();// Anyway for this method the coherence is not complex. Make sure you don't have any active wave passage effect in the simulation
            }

            //Compute element of matrix B needed for the computation of wind velocity
            //at point j
            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
                C1 = pow(PSD1(l - 1), 0.5) * pow(Kz(l - 1), abs(m - j));

                if (m == 1) {
                    B(m - 1, l - 1) = 2 * sqrt(deltaomega) * C1 * exp(i2 * thet(l - 1, m - 1));
                }
                else {
                    C2 = pow(Kz(l - 1), 2);
                    C3 = pow(1 - C2, 0.5);
                    B(m - 1, l - 1) = 2 * sqrt(deltaomega) * C1 * C3 * exp(i2 * thet(l - 1, m - 1));
                }
            }
        }


        // Fast Fourier Transform (FFT)
        for (int ii = 1; ii <= j && false == Data.isInterruptionRequested.getValue(); ii++) {
            G.row(ii - 1) = (double)(M)*fft.inv(B.row(ii - 1));
        }

    }

       double time = 0;
       int q = 0;
       for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue() && true == returnResult; p++) {
       time = (p - 1) * dt + timeMin;
       q = fmod(p - 1, M);
       fout << time << "\t";
       for (int m = 1; m <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++) {
           value = 0.0;
           for (int k = 1; k <= m && false == Data.isInterruptionRequested.getValue(); k++) {
               value = value + real(G(k - 1, q) * exp(i2 * ((k)*deltaomega * (time) / n)));
           }
           fout << value << "\t";
       }
       fout << std::endl;// New line
    }
    fout.close();
return returnResult;
}
