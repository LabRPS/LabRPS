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
        this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_WindLab");
}


bool CRPSYangEtAl1997::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    QMessageBox::warning(0,QString::fromLatin1("Yang et al"), QString::fromLatin1("No additional data required."));
    return true;
}

bool CRPSYangEtAl1997::Simulate(const WindLabAPI::WindLabSimulationData& Data, cube &dPhenomenon)
{
    auto PbuInfo =
        CRPSWindLabFramework::getWindLabFeatureDescription(Data.frequencyDistribution.getValue());

    if (!PbuInfo) {
        Base::Console().Warning("Invalid frequency distribution. The simulation has failed.\n");
        return false;
    }

    if (strcmp(PbuInfo->type.getValue(), "Double Index Frequency Discretization") != 0
        || strcmp(PbuInfo->PluginName.getValue(), "WindLabPlugin") != 0) {
        Base::Console().Warning(
            "This tool required the wind velocity to be simulated with the double index frequency "
            "discretization implemented by the WindLab plugin.\n");
        return false;
    }

    int n = Data.numberOfSpatialPosition.getValue();
    int N = Data.numberOfFrequency.getValue();
    double dt = Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
    double timeMin = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second);
    double deltaomega =
        Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
    int M = 2 * N;
    int T = Data.numberOfTimeIncrements.getValue();
    double sampleN = Data.numberOfSample.getValue();

    vec PSD1(N);
    vec Kz(N);
    cx_mat B = Eigen::MatrixXcd::Zero(n, M);
    cx_mat G = Eigen::MatrixXcd::Zero(n, M);

    // local array for the location coordinates
    mat dLocCoord(n, 4);
    mat frequencies(N, n);

    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if (!returnResult) {
        Base::Console().Warning("The computation of the location coordinates matrix has failed.\n");
        return false;
    }

    //compute the simulation point coordinates
    returnResult =
        WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if (!returnResult) {
        Base::Console().Warning("The computation of the location coordinates matrix has failed.\n");
        return false;
    }

    mat thet(N, n);

    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesMatrixFP(Data, frequencies);
    if (!returnResult) {
        Base::Console().Warning("The computation of the frequency matrix has failed.\n");
        return false;
    }

    std::complex<double> i2(0, 1);
    Eigen::FFT<double> fft;
    std::complex<double> coherenceValue;
    double C;

    for (int ss = 1; ss <= sampleN && false == Data.isInterruptionRequested.getValue(); ss++) {
        returnResult = CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);
        if (!returnResult) {
            Base::Console().Warning(
                "The computation of the random phase angle matrix has failed.\n");
            return false;
        }

        double speed = 0.0;
        returnResult = WindLabAPI::CRPSWindLabFramework::ComputeMeanWindSpeedValue(
            Data, Base::Vector3d(dLocCoord(0, 1), dLocCoord(0, 2), dLocCoord(0, 3)), 0.00, speed);
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

        for (int j = 1;
             j <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult;
             j++) {
            for (int m = 1;
                 m <= j && false == Data.isInterruptionRequested.getValue() && true == returnResult;
                 m++) {
                for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue()
                     && true == returnResult;
                     l++) {
                    returnResult = CRPSWindLabFramework::ComputeAutoSpectrumValue(
                        Data, AA, frequencies(l - 1, m - 1), 0, PSD1(l - 1));
                    if (!returnResult) {
                        Base::Console().Warning(
                            "The computation of the auto spectrum value has failed.\n");
                        return false;
                    }
                }

                for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue()
                     && true == returnResult;
                     l++) {
                    Kz(l - 1) =
                        exp(-2 * frequencies(l - 1, m - 1) * distance * 7 / (speed + speed));
                }

                for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
                    if (m == 1) {
                        B(m - 1, l - 1) = 2 * sqrt(deltaomega) * pow(PSD1(l - 1), 0.5)
                            * pow(Kz(l - 1), abs(m - j)) * exp(i2 * thet(l - 1, m - 1));
                    }
                    else {
                        B(m - 1, l - 1) = 2 * sqrt(deltaomega) * pow(PSD1(l - 1), 0.5)
                            * pow(Kz(l - 1), abs(m - j)) * pow((1 - pow(Kz(l - 1), 2)), 0.5)
                            * exp(i2 * thet(l - 1, m - 1));
                    }
                }
            }

            for (int ii = 1; ii <= j && false == Data.isInterruptionRequested.getValue(); ii++) {
                G.row(ii - 1) = (double)(M)*fft.inv(B.row(ii - 1));
            }
            int q = 0;
            double time = 0;

            for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue(); p++) {
                q = fmod(p - 1, M);
                time = (p - 1) * dt + timeMin;
                dPhenomenon(p - 1, 0, ss - 1) = time;
                for (int k = 1; k <= j && false == Data.isInterruptionRequested.getValue(); k++) {
                    dPhenomenon(p - 1, j, ss - 1) = dPhenomenon(p - 1, j, ss - 1)
                        + real(G(k - 1, q) * exp(i2 * (k * deltaomega * time / n)));
                }
            }
        }
    }

    return returnResult;
}
