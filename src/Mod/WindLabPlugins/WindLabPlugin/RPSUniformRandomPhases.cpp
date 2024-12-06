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

#include "RPSUniformRandomPhases.h"
#include <Mod/GeneralTools/App/UniformRandomPhaseMatrixGenerator.h>
#include "Widgets/DlgUniformRandomPhases.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSUniformRandomPhases, WindLabAPI::WindLabFeatureRandomness)


CRPSUniformRandomPhases::CRPSUniformRandomPhases()
{
    ADD_PROPERTY_TYPE(MinimumValue, (0.0), "Parameters", App::Prop_None, "The minimum value that can be generated");
    ADD_PROPERTY_TYPE(MaximumValue, (6.28), "Parameters", App::Prop_None, "The maximum value that can be generated");
    this->OutputUnit.setValue("rad");
}

bool CRPSUniformRandomPhases::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
	WindLabGui::DlgUniformRandomPhasesEdit* dlg = new WindLabGui::DlgUniformRandomPhasesEdit(MinimumValue, MaximumValue, Data.randomnessProvider);
	Gui::Control().showDialog(dlg);
    return true;
}

bool CRPSUniformRandomPhases::GenerateRandomCubeFPS(const WindLabAPI::WindLabSimulationData &Data, cube &dRandomValueCube)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseCube(dRandomValueCube, MinimumValue.getValue(), MaximumValue.getValue());
    return true;
}

bool CRPSUniformRandomPhases::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat &dRandomValueArray)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseMatrix(dRandomValueArray, MinimumValue.getValue(), MaximumValue.getValue());
    return true;
} 

bool CRPSUniformRandomPhases::ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double &dValue)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseValue(dValue, MinimumValue.getValue(), MaximumValue.getValue());
    return true;
}
