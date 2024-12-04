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

#include "RPSDeodatis1996.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <unsupported/Eigen/FFT>
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSDeodatis1996, WindLabAPI::WindLabFeatureSimulationMethod)

CRPSDeodatis1996::CRPSDeodatis1996()
{ 
    this->OutputUnit.setValue("m/s");
}


bool CRPSDeodatis1996::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    QMessageBox::warning(0,QString::fromLatin1("Deodatis method"), QString::fromLatin1("No additional data required."));
    return true;
}

bool CRPSDeodatis1996::Simulate(const WindLabAPI::WindLabSimulationData& Data, mat &dVelocityArray)
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
bool CRPSDeodatis1996::stationaryWind(const WindLabAPI::WindLabSimulationData& Data, mat &dVelocityArray)
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

    cx_mat decomposedPSD2D(n, n);
    cx_cube decomposedPSD3D(n, n, N);
    
    cx_cube B(n, n, M);
    cx_cube G(n, n, M);
    B.setZero();
    G.setZero();

    cx_vec xxx(M);
    cx_vec yyy(M);
    xxx.setZero();
    yyy.setZero();

    // local array for the location coordinates
    mat dLocCoord(n, 4);
    mat frequencies(N,n);

    //compute the simulation point coordinates
    bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.\n") ;
       return false;
    }

    // generate n sequences of random phase angles phi(l), l = 1, 2, ..., N
    mat thet(N, n);
    returnResult = WindLabAPI::CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);
    
    if(!returnResult)
    {
       Base::Console().Warning("The generation of the random phase matrix has failed.\n") ;
       return false;
    }

    // compute le frequency matrix. Note that this method required the double indexing frequency
    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesMatrixFP(Data, frequencies);

    if(!returnResult)
    {
       Base::Console().Warning("The computation of the frequency increments has failed.\n") ;
       return false;
    }

    // the imaginary i
    std::complex<double> i2(0, 1);

    // fast fourier transform
    Eigen::FFT<double> fft;

    // this method is for stationry wind. Spectrum is not function of time
    double time = 0;

    for (int m = 1; m <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++) {
       for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++) { 
           returnResult = WindLabAPI::CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(Data, frequencies(l - 1, m - 1), time, decomposedPSD2D);
           for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++) {
               decomposedPSD3D(j - 1, m - 1, l - 1) = decomposedPSD2D(j - 1, m - 1);
           }
       }

       // compute matrix B
       for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
           for (int j = 1; j <= m && false == Data.isInterruptionRequested.getValue(); j++) {
               B(m - 1, j - 1, l - 1) = 2 * sqrt(deltaomega)
                   * abs(decomposedPSD3D(m - 1, j - 1, l - 1)) * exp(i2 * thet(l - 1, j - 1));
           }
       }

       //compute matrix G
       for (int j = 1; j <= m && false == Data.isInterruptionRequested.getValue(); j++) {
           for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
               xxx(l - 1) = B(m - 1, j - 1, l - 1);
           }

           yyy = (double)(M)*fft.inv(xxx);

           for (int l = 1; l <= M && false == Data.isInterruptionRequested.getValue(); l++) {
               G(m - 1, j - 1, l - 1) = yyy(l - 1);
           }
       }

       double time = 0;
       int q = 0;
       // Generate the wind velocity
       for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue(); p++) {
           q = fmod(p - 1, M);
           time = (p - 1) * dt + timeMin;
           dVelocityArray(p - 1, 0) = time;
           for (int k = 1; k <= m && false == Data.isInterruptionRequested.getValue(); k++) {
               dVelocityArray(p - 1, m) = dVelocityArray(p - 1, m) + real(G(m - 1, k - 1, q) * exp(i2 * ((k)*deltaomega * (time) / n)));
           }
       }
    }
    
    return returnResult;
}

// The simulation function in large scale mode
bool CRPSDeodatis1996::SimulateInLargeScaleMode(const WindLabAPI::WindLabSimulationData& Data, QString &strFileName)
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

    cx_mat decomposedPSD2D(n, n);
    cx_cube decomposedPSD3D(n, n, N);
    
    cx_cube B(n, n, M);
    cx_cube G(n, n, M);
    B.setZero();
    G.setZero();

    cx_vec xxx(M);
    cx_vec yyy(M);
    xxx.setZero();
    yyy.setZero();

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

    //compute the simulation point coordinates
    bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.\n") ;
       return false;
    }

    // generate n sequences of random phase angles phi(l), l = 1, 2, ..., N
    mat thet(N, n);
    returnResult = WindLabAPI::CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);
    
    if(!returnResult)
    {
       Base::Console().Warning("The generation of the random phase matrix has failed.\n") ;
       return false;
    }

    // compute le frequency matrix. Note that this method required the double indexing frequency
    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesMatrixFP(Data, frequencies);

    if(!returnResult)
    {
       Base::Console().Warning("The computation of the frequency increments has failed.\n") ;
       return false;
    }

    // the imaginary i
    std::complex<double> i2(0, 1);

    // fast fourier transform
    Eigen::FFT<double> fft;

    // this method is for stationry wind. Spectrum is not function of time
    double time = 0.0;

    for (int m = 1;
         m <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++) {
       for (int l = 1;
            l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult;
            l++) {
           returnResult = WindLabAPI::CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(
               Data, frequencies(l - 1, m - 1), time, decomposedPSD2D);
           for (int j = 1;
                j <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult;
                j++) {
               decomposedPSD3D(j - 1, m - 1, l - 1) = decomposedPSD2D(j - 1, m - 1);
           }
       }

       // compute matrix B
       for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
           for (int j = 1; j <= m && false == Data.isInterruptionRequested.getValue(); j++) {
               B(m - 1, j - 1, l - 1) = 2 * sqrt(deltaomega)
                   * abs(decomposedPSD3D(m - 1, j - 1, l - 1)) * exp(i2 * thet(l - 1, j - 1));
           }
       }

       //compute matrix G
       for (int j = 1; j <= m && false == Data.isInterruptionRequested.getValue(); j++) {
           for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
               xxx(l - 1) = B(m - 1, j - 1, l - 1);
           }

           yyy = (double)(M)*fft.inv(xxx);

           for (int l = 1; l <= M && false == Data.isInterruptionRequested.getValue(); l++) {
               G(m - 1, j - 1, l - 1) = yyy(l - 1);
           }
       }
    }

    int q = 0;
       for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue(); p++) {
       time = (p - 1) * dt + timeMin;
       q = fmod(p - 1, M);
       fout << time << "\t";
          for (int m = 1; m <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++) {
           value = 0.0;
           for (int k = 1; k <= m && false == Data.isInterruptionRequested.getValue(); k++) {
               value = value + real(G(m - 1, k - 1, q) * exp(i2 * ((k)*deltaomega * (time) / n)));
           }
           fout << value << "\t";
       }
       fout << std::endl;// New line
    }
    fout.close();
    return returnResult;
}
