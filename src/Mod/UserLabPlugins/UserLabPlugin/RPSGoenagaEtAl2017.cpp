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
#include <Mod/UserLabAPI/App/RPSUserLabFramework.h>

const double PI = 3.14159265358979323846;

using namespace UserLab;
using namespace UserLabAPI;

PROPERTY_SOURCE(UserLab::CRPSGoenagaEtAl2017, UserLabAPI::UserLabFeatureSimulationMethod)

CRPSGoenagaEtAl2017::CRPSGoenagaEtAl2017()
{
    ADD_PROPERTY_TYPE(ReferenceWaveNumber, (1.00), "Parameters", App::Prop_None, "The reference wave number.");
    ADD_PROPERTY_TYPE(ReferenceSpectrum, (0.000256), "Parameters", App::Prop_None, "The spectrum at the reference wave number.");
    ADD_PROPERTY_TYPE(PavementWavinessIndicator, (2), "Parameters", App::Prop_None, "The pavement waviness indicator.");
    Phenomenon.setValue("Pavement Profiles");
    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_UserLab#Goenaga_et_al_2017");

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
                 w(l - 1) = (minLambda + l * deltaLambda);
                 PSD(l - 1) = referenceSpectrum * (pow(w(l - 1) / referenceWaveNumber, - pavementWavinessIndicator));
                 Amp(l - 1) = sqrt(PSD(l - 1) * (deltaLambda) / PI);
             }

         for (int p = 1; p <= L && false == Data.isInterruptionRequested.getValue(); p++) {

            x = (p - 1) * dx + minX;

             dPhenomenon(p - 1, 0, ss - 1) = x;

             for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
                 dPhenomenon(p - 1, j, ss - 1) = dPhenomenon(p - 1, j, ss - 1) + Amp(l - 1) * sin(w(l - 1) * x - thet(l - 1, j - 1)) * ScaleCoefficient.getValue();
            }
         }      
        }
    }

return true;
}
