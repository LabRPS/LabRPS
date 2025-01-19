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

#include "DeodatisAndShinozyka1991.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <unsupported/Eigen/FFT>
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CDeodatisAndShinozyka1991, WindLabAPI::WindLabFeatureSimulationMethod)

CDeodatisAndShinozyka1991::CDeodatisAndShinozyka1991()
{ 
    
}

bool CDeodatisAndShinozyka1991::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    QMessageBox::warning(0,QString::fromLatin1("Deodatis method"), QString::fromLatin1("No additional data required."));
    return true;
}

bool CDeodatisAndShinozyka1991::Simulate(const WindLabAPI::WindLabSimulationData& Data, cube &dPhenomenon)
{
    int n = Data.numberOfSpatialPosition.getValue();
    int N = Data.numberOfFrequency.getValue();
    double dt = Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
    double timeMin = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second);
    double deltaomega = Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
    int M = 2 * N;
    int T = Data.numberOfTimeIncrements.getValue();
    double sampleN = Data.numberOfSample.getValue();

    vec PSD(N);
    cx_vec xxx(M);
    cx_vec yyy(M);
    xxx.setZero();
    yyy.setZero();

    // local array for the location coordinates
    mat dLocCoord(n, 4);
    vec frequencies(N);
    vec frequenciesVar(N);

    //compute the simulation point coordinates
    bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

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
    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, Base::Vector3d(0,0,0), frequencies);

    if (!returnResult) {
        Base::Console().Error("The computation of the frequency distribution has failed.\n");
        return false;
    }

    // the imaginary i
    std::complex<double> i2(0, 1);

    // fast fourier transform
    Eigen::FFT<double> fft;

    // this method is for stationry wind. Spectrum is not function of time
    double time = 0;
    for (int ss = 1; ss <= sampleN && false == Data.isInterruptionRequested.getValue(); ss++) {
        returnResult = WindLabAPI::CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);
        if (!returnResult) {
            Base::Console().Error(
                "The computation of the random phase angle matrix has failed.\n");
            return false;
        }       
        for (int m = 1; m <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++) {
           
            Base::Vector3d location(dLocCoord(m - 1, 1), dLocCoord(m - 1, 2), dLocCoord(m - 1, 3));
            returnResult = WindLabAPI::CRPSWindLabFramework::ComputeAutoSpectrumVectorF(Data, location, time, frequenciesVar, PSD);

            //compute matrix G
            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
                xxx(l - 1) = std::sqrt(2) * std::sqrt(2 * PSD(l - 1) * deltaomega) * exp(i2 * thet(l - 1, m - 1));
            }

            yyy = (double)(M)*fft.inv(xxx);


            double time = 0;
            int q = 0;
            // Generate the wind velocity
            for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue(); p++) {
                q = fmod(p - 1, M);
                time = (p - 1) * dt + timeMin;
                dPhenomenon(p - 1, 0, ss - 1) = time;
                dPhenomenon(p - 1, m, ss - 1) = dPhenomenon(p - 1, m, ss - 1) + real(yyy(q) * exp(i2 * ( time / n)));            
            }
        }
    }

    return returnResult;
}

