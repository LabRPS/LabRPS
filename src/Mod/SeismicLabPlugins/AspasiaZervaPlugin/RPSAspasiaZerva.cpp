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

#include "RPSAspasiaZerva.h"
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>
#include <Mod/GeneralTools/App/UniformRandomPhaseMatrixGenerator.h>
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>

const double PI = 3.14159265358979323846;

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSAspasiaZerva, SeismicLabAPI::SeismicLabFeatureSimulationMethod)

CRPSAspasiaZerva::CRPSAspasiaZerva()
{
    ADD_PROPERTY_TYPE(StandardDeviation, (300), "Parameters", App::Prop_None, "The standard deviation of the excitation.");
    ADD_PROPERTY_TYPE(DominantFrequency, (5.0), "Parameters", App::Prop_None, "The dominant frequency of the earthquake excitation.");
    ADD_PROPERTY_TYPE(DampingRatio, (0.3), "Parameters", App::Prop_None, "The bandwidth of the earthquake excitation.");
    ADD_PROPERTY_TYPE(EnvelopValueAtNinetyPercentDuration, (0.3), "Parameters", App::Prop_None, "The value of the envelop function at 90 percent of the duration.");
    ADD_PROPERTY_TYPE(NormalizedDurationTimeAtPeak, (0.4), "Parameters", App::Prop_None, "normalized duration time when ground motion achieves peak.");
}
//Initial setting
bool CRPSAspasiaZerva::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	return true;
}

// The simulation function 
bool CRPSAspasiaZerva::Simulate(const SeismicLabAPI::SeismicLabSimulationData& Data, cube &dPhenomenon)
{
    if (!Data.stationarity.getValue() ) {
        Base::Console().Error("The simulation method is only for non-stationary wind velocity.\n");
        return false;
    }

    if (!Data.IsUniformModulationFeature.getValue() ) {
        Base::Console().Error("The simulation method is only for non-stationary uniformly modulated wind velocity.\n");
        return false;
    }

    auto PbuInfo = SeismicLabAPI::CRPSSeismicLabFramework::getSeismicLabFeatureDescription(Data.modulationFunction.getValue());

    if (!PbuInfo->IsUniformModulationFeature.getValue()) {
        Base::Console().Error("Invalid modulation function. The method accepts only uniform modulation function.\n");
        return false;
    }

    int n = Data.numberOfSpatialPosition.getValue();
    int N = Data.numberOfFrequency.getValue();
    double dt = Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
    double timeMin = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second);
    double deltaomega = Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
    int T = Data.numberOfTimeIncrements.getValue();
    double sampleN = Data.numberOfSample.getValue();
    double time = 0;

    // local array for the location coordinates
    mat dLocCoord(n, 4);
    mat frequencies(N, n);
    vec freq(N);
    vec PSD(N);
    vec Env(T);
    vec EnvVar(T);

    //compute the simulation point coordinates
    bool returnResult = SeismicLabAPI::CRPSSeismicLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if (!returnResult) {
        Base::Console().Warning("The computation of the location coordinates matrix has failed.\n");
        return false;
    }

    // generate n sequences of random phase angles phi(l), l = 1, 2, ..., N
    mat thet(N, n);

    if (!returnResult) {
        Base::Console().Warning("The generation of the random phase matrix has failed.\n");
        return false;
    }

    // compute le frequency matrix. Note that this method required the double indexing frequency
    returnResult = SeismicLabAPI::CRPSSeismicLabFramework::ComputeFrequenciesMatrixFP(Data, frequencies);

    if (!returnResult) {
        Base::Console().Warning("The computation of the frequency increments has failed.\n");
        return false;
    }

    for (int ss = 1; ss <= sampleN && false == Data.isInterruptionRequested.getValue(); ss++) 
    {
        rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
        uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseMatrix(thet, 0, 2 * PI);

        for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue(); j++)
        {
            Base::Vector3d point(dLocCoord(j - 1, 1), dLocCoord(j - 1, 2), dLocCoord(j - 1, 3));
            returnResult = SeismicLabAPI::CRPSSeismicLabFramework::ComputeAutoSpectrumVectorF(Data, point, 0.0, freq, PSD);
            if (!returnResult)
            {
                Base::Console().Warning("The computation of the frequency increments has failed.\n");
                return false;
            }

            returnResult = SeismicLabAPI::CRPSSeismicLabFramework::ComputeModulationVectorT(Data, point, 0.0, EnvVar, Env);

            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the modulation function vector has failed.\n");
                return false;
            }

            for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue(); p++) {
                time = (p - 1) * dt + timeMin;
                dPhenomenon(p - 1, 0, ss - 1) = time;
                for (int k = 1; k <= N && false == Data.isInterruptionRequested.getValue(); k++) {
                    dPhenomenon(p - 1, j, ss - 1) = dPhenomenon(p - 1, j, ss - 1)
                        + Env(p - 1) * 2 * std::sqrt(PSD(k - 1) * deltaomega)
                            * std::cos(frequencies(k - 1, j - 1) * time + thet(k - 1, j - 1));
                }
            }             
         }
    }
return true;
}

// The simulation function in large scale mode
bool CRPSAspasiaZerva::SimulateInLargeScaleMode(const SeismicLabAPI::SeismicLabSimulationData& Data, QString &strFileName)
{
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

    //bool returnResult = CRPSSeismicLabFramework::GenerateRandomMatrixFP(Data, thet);
    //if(!returnResult)
    //{
    //   Base::Console().Warning("The computation of the random phase angle matrix has failed.\n");
    //   return false;
    //}

    //std::complex<double> i2(0, 1);
    //Eigen::FFT<double> fft;

    //for (int ss = 1; ss <= sampleN && false == Data.isInterruptionRequested.getValue(); ss++) {

    //    // Get the current date and time
    //    std::string dateTimeStr = CRPSSeismicLabFramework::getCurrentDateTime();

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

