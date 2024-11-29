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

#include "SineModulation.h"
#include <Mod/WindLabTools/App/modulation/SineModulation.h>
#include "Widgets/DlgSineModulation.h"
#include <Gui/Control.h>

using namespace WindLab;

PROPERTY_SOURCE(WindLab::CSineModulation, WindLabAPI::WindLabFeatureModulation)

CSineModulation::CSineModulation()
{
    ADD_PROPERTY_TYPE(PulseDuration, (150), "Parameters", App::Prop_None, "The pulse duration");
    this->OutputUnit.setValue("Dimensionless");
}

bool CSineModulation::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    WindLabGui::DlgSineModulationEdit* dlg = new WindLabGui::DlgSineModulationEdit(PulseDuration, Data.modulationFunction);
	Gui::Control().showDialog(dlg);
    return true;
}


bool CSineModulation::ComputeModulationValue(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
	dValue = sin(3.14*dTime / PulseDuration.getQuantityValue().getValueAs(Base::Quantity::Second));
	return true;
}

bool CSineModulation::ComputeModulationVectorT(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    double dTime = 0.0;

    WindLabTools::SineModulation sineModulation;

	for (int k = 0; k < Data.numberOfTimeIncrements.getValue() && Data.uniformModulation.getValue() && this->IsUniformlyModulated.getValue(); k++)
	{
		dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;
		dVarVector(k) = dTime;	
        dValVector(k) = sineModulation.computeModulation(dTime, PulseDuration.getQuantityValue().getValueAs(Base::Quantity::Second));
	}
	return true;
}

bool CSineModulation::ComputeModulationVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    WindLabTools::SineModulation sineModulation;

    const double dModValue = sineModulation.computeModulation(dTime, PulseDuration.getQuantityValue().getValueAs(Base::Quantity::Second));
    
	for (int k = 0; k < Data.numberOfSpatialPosition.getValue() && Data.uniformModulation.getValue() && this->IsUniformlyModulated.getValue(); k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = dModValue;
    }

	return true;
}
