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

#include "RPSGoenagaEtAl2017.h"
#include <unsupported/Eigen/FFT>
#include "Widgets/DlgGoenagaEtAl2017.h"
#include <Gui/Control.h>
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>
#include <Mod/GeneralTools/App/UniformRandomPhaseMatrixGenerator.h>

const double PI = 3.14159265358979323846;

using namespace UserLab;
using namespace UserLabAPI;

PROPERTY_SOURCE(UserLab::CRPSGoenagaEtAl2017, UserLabAPI::UserLabFeatureSimulationMethod)

CRPSGoenagaEtAl2017::CRPSGoenagaEtAl2017()
{
    ADD_PROPERTY_TYPE(ReferenceWaveNumber, (1.00), "Parameters", App::Prop_None, "The reference wave number.");
    ADD_PROPERTY_TYPE(ReferenceSpectrum, (0.000256), "Parameters", App::Prop_None, "The spectrum at the reference wave number.");
    ADD_PROPERTY_TYPE(PavementWavinessIndicator, (2), "Parameters", App::Prop_None, "The pavement waviness indicator.");
}
//Initial setting
bool CRPSGoenagaEtAl2017::OnInitialSetting(const UserLabAPI::UserLabSimulationData& Data)
{
    UserLabGui::DlgGoenagaEtAl2017Edit* dlg = new UserLabGui::DlgGoenagaEtAl2017Edit(ReferenceWaveNumber, ReferenceSpectrum, PavementWavinessIndicator, Data.simulationMethod);
    Gui::Control().showDialog(dlg);
	return true;
}

const char* CRPSGoenagaEtAl2017::GetPhenomenonName()
{
    return "Longitudinal Pavement Profile";
}

    // The simulation function 
bool CRPSGoenagaEtAl2017::Simulate(const UserLabAPI::UserLabSimulationData& Data, cube &dPhenomenon)
{
    if (Data.largeScaleSimulationMode.getValue()) {
        Base::Console().Error("The simulation fails.\n");
        return false;
    }

    int N = Data.numberOfWaveLengthIncrements.getValue();
    int n = Data.numberOfSpatialPosition.getValue();
    double deltaLambda = Data.waveLengthIncrement.getQuantityValue().getValueAs(Base::Quantity:: Metre);
    double minLambda = Data.minWaveLength.getQuantityValue().getValueAs(Base::Quantity:: Metre);
    int sampleN = Data.numberOfSample.getValue();
    double referenceWaveNumber = ReferenceWaveNumber.getValue();
    double referenceSpectrum = ReferenceSpectrum.getValue();
    double pavementWavinessIndicator = PavementWavinessIndicator.getValue();
    int L = Data.numberOfSpatialCoordinateIncrement.getValue();
    double dx = Data.spatialCoordinateIncrement.getQuantityValue().getValueAs(Base::Quantity:: Metre);
    double minX = Data.spatialCoordinateMinimum.getQuantityValue().getValueAs(Base::Quantity::Metre);
    double x = 0.0;

    vec PSD(N);
    vec Amp(N);
    mat thet(N, n);
    vec w(N);

    for (int ss = 1; ss <= sampleN && false == Data.isInterruptionRequested.getValue(); ss++) {
         rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
        uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseMatrix(thet, 0, 2 * PI);

         for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue(); j++){
             for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
                 w(l - 1) = 2 * PI / (minLambda + l * deltaLambda);
                 PSD(l - 1) = referenceSpectrum * (pow(w(l - 1) / referenceWaveNumber, - pavementWavinessIndicator));
                 Amp(l - 1) = sqrt(PSD(l - 1) * (2 * PI / deltaLambda) / PI);
             }

         for (int p = 1; p <= L && false == Data.isInterruptionRequested.getValue(); p++) {

             x = (p - 1) * dx + minX;

             dPhenomenon(p - 1, 0, ss - 1) = x;

             for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
                 dPhenomenon(p - 1, j, ss - 1) = dPhenomenon(p - 1, j, ss - 1) + Amp(l - 1) * sin(w(l - 1) * x - thet(l - 1, j - 1));
             }
         }      
         }
    }

return true;
}

// The simulation function in large scale mode
bool CRPSGoenagaEtAl2017::SimulateInLargeScaleMode(const UserLabAPI::UserLabSimulationData& Data, QString &strFileName)
{
    if (!Data.largeScaleSimulationMode.getValue()) {
        Base::Console().Error("The simulation fails.\n");
        return false;
    }
    //int n = NumberOfLocation.getValue();
    //int N = NumberOfFrequencies.getValue();
    //double timeMin = 0.00;
    //int M = 2*N;
    //int T = NumberOfTimeIncrements.getValue();
    //double wu = UpperCutOffFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
    //double dt = 2 * 3.14 / (2 * wu);
    //double deltaomega = wu/N;
    //double distance = LocationSpacing.getQuantityValue().getValueAs(Base::Quantity::Metre);
    //double speed = MeanSpeed.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond);
    //double height = LocationHeight.getQuantityValue().getValueAs(Base::Quantity::Metre);
    //double zo = RoughnessLength.getQuantityValue().getValueAs(Base::Quantity::Metre);
    //double Uo = 0.4 * speed / log(height / zo);
    //double Cy = CoherenceDecayCoefficient.getValue();
    //double value = 0.0;
    //double sampleN = Data.numberOfSample.getValue();

    //vec PSD1(N);
    //vec Kz(N);
    //cx_mat B = Eigen::MatrixXcd::Zero(n,M);
    //cx_mat G = Eigen::MatrixXcd::Zero(n,M);
    //mat thet(N, n);
    //vec w(N);

    //bool returnResult = CRPSUserLabFramework::GenerateRandomMatrixFP(Data, thet);
    //if(!returnResult)
    //{
    //   Base::Console().Warning("The computation of the random phase angle matrix has failed.\n");
    //   return false;
    //}

    //std::complex<double> i2(0, 1);
    //Eigen::FFT<double> fft;

    //for (int ss = 1; ss <= sampleN && false == Data.isInterruptionRequested.getValue(); ss++) {

    //    // Get the current date and time
    //    std::string dateTimeStr = CRPSUserLabFramework::getCurrentDateTime();

    //    // Create the new file name by appending the date and time
    //    std::string newFileName = Data.workingDirectoryPath.getValue().string() + "/"
    //        + Data.fileName.getValue() + "_Sample_" + std::to_string(ss) + "_" + dateTimeStr
    //        + ".txt";

    //    // Define an output stream
    //    std::ofstream fout;

    //    // open the file output mode to erase its content first
    //    fout.width(10);
    //    fout.setf(std::ios::left);
    //    fout.setf(std::ios::fixed);
    //    fout.fill('0');
    //    fout.open(newFileName, std::ios::out);

    //    for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue(); p++) {

    //        fout << (p - 1) * dt + timeMin << "\t";
    //    }
    //    fout << std::endl;


    //    for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue(); j++) {
    //        for (int m = 1; m <= j && false == Data.isInterruptionRequested.getValue(); m++) {
    //            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
    //                w(l - 1) = (l - 1) * deltaomega + (double)m / n * deltaomega;

    //                PSD1(l - 1) = 200 * height * Uo * Uo / speed
    //                    / (pow(1 + 50 * w(l - 1) * height / speed, 5.0 / 3.0));
    //            }

    //            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
    //                Kz(l - 1) = exp(-2 * w(l - 1) * distance * Cy / (speed + speed));
    //            }

    //            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
    //                if (m == 1) {
    //                    B(m - 1, l - 1) = 2 * sqrt(deltaomega) * pow(PSD1(l - 1), 0.5)
    //                        * pow(Kz(l - 1), abs(m - j)) * exp(i2 * thet(l - 1, m - 1));
    //                }
    //                else {
    //                    B(m - 1, l - 1) = 2 * sqrt(deltaomega) * pow(PSD1(l - 1), 0.5)
    //                        * pow(Kz(l - 1), abs(m - j)) * pow((1 - pow(Kz(l - 1), 2)), 0.5)
    //                        * exp(i2 * thet(l - 1, m - 1));
    //                }
    //            }
    //        }

    //        for (int ii = 1; ii <= j && false == Data.isInterruptionRequested.getValue(); ii++) {
    //            G.row(ii - 1) = (double)(M)*fft.inv(B.row(ii - 1));
    //        }

    //        int q = 0;
    //        double time = 0;

    //        for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue(); p++) {

    //            q = fmod(p - 1, M);

    //            time = (p - 1) * dt + timeMin;

    //            value = 0.0;

    //            for (int k = 1; k <= j && false == Data.isInterruptionRequested.getValue(); k++) {

    //                value = value + real(G(k - 1, q) * exp(i2 * (k * deltaomega * time / n)));
    //            }

    //            fout << value << "\t";
    //        }

    //        fout << std::endl;
    //    }

    //    fout.close();
    //
    //}

return true;
}
