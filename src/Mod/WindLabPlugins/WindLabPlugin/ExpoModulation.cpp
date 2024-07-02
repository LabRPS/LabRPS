
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

#include "ExpoModulation.h"
#include <Mod/WindLabTools/App/modulation/ExponentialModulation.h>
#include "Widgets/DlgExpoModulation.h"
#include <Gui/Control.h>


using namespace WindLab;

PROPERTY_SOURCE(WindLab::CExpoModulation, WindLabAPI::WindLabFeatureModulation)

CExpoModulation::CExpoModulation()
{
    ADD_PROPERTY_TYPE(TimeOfMax, (300), "Parameters", App::Prop_None, "The time when the modulation function reaches its maximum");
    ADD_PROPERTY_TYPE(StormLength, (60), "Parameters", App::Prop_None, "The storm length");
}
bool CExpoModulation::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    WindLabGui::DlgExpoModulationEdit* dlg = new WindLabGui::DlgExpoModulationEdit(TimeOfMax, StormLength, Data.modulationFunction);
	Gui::Control().showDialog(dlg);
    return true;
}

bool CExpoModulation::ComputeModulationValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    WindLabTools::ExponentialModulation exponentialModulation;

    dValue = exponentialModulation.computeModulation(dTime, TimeOfMax.getQuantityValue().getValueAs(Base::Quantity::Second), StormLength.getQuantityValue().getValueAs(Base::Quantity::Second));

	return true;
}

bool CExpoModulation::ComputeModulationVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{

    WindLabTools::ExponentialModulation exponentialModulation;

	 //For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double 	dTime = Data.minTime.getValue() + Data.timeIncrement.getValue() * k;
        dVarVector(k) = dTime;
		dValVector(k) = exponentialModulation.computeModulation(dTime, TimeOfMax.getQuantityValue().getValueAs(Base::Quantity::Second), StormLength.getQuantityValue().getValueAs(Base::Quantity::Second));
	}

	return true;
}

bool CExpoModulation::ComputeModulationVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    WindLabTools::ExponentialModulation exponentialModulation;
    //const double 	dTime = Data.minTime.getValue() + Data.timeIncrement.getValue() * Data.timeIndex.getValue();
    const double modulationValue = exponentialModulation.computeModulation(dTime, TimeOfMax.getQuantityValue().getValueAs(Base::Quantity::Second), StormLength.getQuantityValue().getValueAs(Base::Quantity::Second));
     //For each time increment
    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = modulationValue;
    }

	return true;
}
