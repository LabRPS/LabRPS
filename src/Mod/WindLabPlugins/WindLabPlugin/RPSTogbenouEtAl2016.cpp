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

#include "RPSTogbenouEtAl2016.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <unsupported/Eigen/FFT>
#include "Widgets/DlgTogbenouEtAl2016.h"
#include <Gui/Control.h>
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSTogbenouEtAl2016, WindLabAPI::WindLabFeatureSimulationMethod)

CRPSTogbenouEtAl2016::CRPSTogbenouEtAl2016()
{
    ADD_PROPERTY_TYPE(NumberOfLocation, (3), "Parameters", App::Prop_None, "The number of simulation points evenly distributed at a constant height.");
    ADD_PROPERTY_TYPE(NumberOfFrequencies, (1024), "Parameters", App::Prop_None, "The number of frequency increments.");
    ADD_PROPERTY_TYPE(ReferencePointIndex, (1), "Parameters", App::Prop_None, "The index of the reference point.");
    ADD_PROPERTY_TYPE(LocationSpacing, (5000.00), "Parameters", App::Prop_None, "The constant spacing between any two adjacent points.");
    ADD_PROPERTY_TYPE(CoherenceDecayCoefficient, (10.0), "Parameters", App::Prop_None, "The decay coefficient in the Davenport coherence function.");
    ADD_PROPERTY_TYPE(UpperCutOffFrequency, (2.00), "Parameters", App::Prop_None, "The upper cut off frequency.");
    ADD_PROPERTY_TYPE(NumberOfTimeIncrements, (6144), "Parameters", App::Prop_None, "The number of time increments.");
    ADD_PROPERTY_TYPE(RoughnessLength, (10.0), "Parameters", App::Prop_None, "The terrain roughness length.");
    ADD_PROPERTY_TYPE(StartingElevation, (10000.0), "Parameters", App::Prop_None, "The lowest elevation points are uniformly distributed from.");
    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_WindLab");

    

}
//Initial setting
bool CRPSTogbenouEtAl2016::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    WindLabGui::DlgTogbenouEtAl2016Edit* dlg = new WindLabGui::DlgTogbenouEtAl2016Edit(
        NumberOfLocation, NumberOfFrequencies, LocationSpacing,
        CoherenceDecayCoefficient, UpperCutOffFrequency, NumberOfTimeIncrements, RoughnessLength,
        StartingElevation, ReferencePointIndex, Data.simulationMethod);
    Gui::Control().showDialog(dlg);
	return true;
}

    // The simulation function 
bool CRPSTogbenouEtAl2016::Simulate(const WindLabAPI::WindLabSimulationData& Data, cube &dPhenomenon)
{
    int n = NumberOfLocation.getValue();
    int N = NumberOfFrequencies.getValue();
    double timeMin = 0.00;
    int M = 2*N;
    int T = NumberOfTimeIncrements.getValue();
    double wu = UpperCutOffFrequency.getQuantityValue().getValueAs(Base::Quantity::Hertz);
    double dt = 2 * 3.14 / (2 * wu);
    double deltaomega = wu/N;
    double spacing = LocationSpacing.getQuantityValue().getValueAs(Base::Quantity::Metre);
    double alpha = 0.12;
    double Uoo = 30.0;
    double Zoo = 10.0;
    double speed = 0.0;
    double height = 0.0;
    double zo = RoughnessLength.getQuantityValue().getValueAs(Base::Quantity::Metre);
    double Uo = 0.4 * Uoo / log(Zoo / zo);
    double Cz = CoherenceDecayCoefficient.getValue();
    double sampleN = Data.numberOfSample.getValue();
    double startingElevation =  StartingElevation.getQuantityValue().getValueAs(Base::Quantity::Metre);
    double beta = (alpha - 1) / 3.0;
    double No = startingElevation / spacing;
    int N1 = (int)(1 / deltaomega);
    double Zref = startingElevation + ReferencePointIndex.getValue() * spacing;
    double Uref = Uoo * std::pow(Zref / Zoo, alpha);
    double Wref = Uref / (50 * Zref);

    vec PSD1(N);
    vec Kz(N);
    cx_mat B = Eigen::MatrixXcd::Zero(n,M);
    cx_mat G = Eigen::MatrixXcd::Zero(n,M);
    mat thet(N, n);
    vec w(N);

    std::complex<double> i2(0, 1);
    Eigen::FFT<double> fft;

    for (int ss = 1; ss <= sampleN && false == Data.isInterruptionRequested.getValue(); ss++) {

    bool returnResult = CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the random phase angle matrix has failed.\n");
       return false;
    }

      for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue(); j++) {
        height = startingElevation + (j - 1) * spacing;
        speed = Uoo * std::pow(height / Zoo, alpha);
        for (int m = 1; m <= j && false == Data.isInterruptionRequested.getValue(); m++) {
            for (int l = 1; l <= N1 && false == Data.isInterruptionRequested.getValue(); l++) {
                w(l - 1) = (l - 1) * deltaomega + (double)m / n * deltaomega;
                PSD1(l - 1) = 200 * height * Uo * Uo / speed
                    / (pow(1 + 50 * w(l - 1) * height / speed, 5.0 / 3.0));
            }

            for (int l = N1 + 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
                w(l - 1) = (l - 1) * deltaomega + (double)m / n * deltaomega;
                PSD1(l - 1) = 200 * Uo * Uo * std::pow(50, -5.0 / 3.0)
                    * pow(height / speed, -2.0 / 3.0) * pow(w(l - 1) + Wref, - 5.0 / 3.0);
            }

            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
                Kz(l - 1) = exp(-2 * w(l - 1) * spacing * Cz / (Uref + Uref));
            }

            for (int l = 1; l <= N1 && false == Data.isInterruptionRequested.getValue(); l++) {
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

            for (int l = N1 + 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
                if (m == 1) {
                    B(m - 1, l - 1) = 2 * sqrt(deltaomega) * pow(PSD1(l - 1), 0.5)
                        * pow(Kz(l - 1), abs(m - j)) * exp(i2 * thet(l - 1, m - 1)) * std::pow((No + j - 1)/No, beta);
                }
                else {
                    B(m - 1, l - 1) = 2 * sqrt(deltaomega) * pow(PSD1(l - 1), 0.5)
                        * pow(Kz(l - 1), abs(m - j)) * pow((1 - pow(Kz(l - 1), 2)), 0.5)
                        * exp(i2 * thet(l - 1, m - 1)) * std::pow((No + j - 1) / No, beta);
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
                    + real(G(k - 1, q) * exp(i2 * (k * deltaomega * time / n))) * ScaleCoefficient.getValue();
            }
        }
    }


    }

return true;
}

void CRPSTogbenouEtAl2016::onChanged(const App::Property* prop)
{
    if (prop == &ReferencePointIndex) {
        if (ReferencePointIndex.getValue() < 0)
            ReferencePointIndex.setValue(0);
        if (ReferencePointIndex.getValue() > NumberOfLocation.getValue() - 1)
            ReferencePointIndex.setValue(NumberOfLocation.getValue() - 1);
    }

    WindLabFeatureSimulationMethod::onChanged(prop);
}
