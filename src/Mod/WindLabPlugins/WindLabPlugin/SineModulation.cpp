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
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>

using namespace WindLab;

PROPERTY_SOURCE(WindLab::CSineModulation, WindLabAPI::WindLabFeatureModulation)

CSineModulation::CSineModulation()
{
    ADD_PROPERTY_TYPE(PulseDuration, (150), "Parameters", App::Prop_None, "The pulse duration");
    this->IsUniformModulationFeature.setValue(true);
    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_WindLab#Sine_Modulation_Function");

}

bool CSineModulation::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    WindLabGui::DlgSineModulationEdit* dlg = new WindLabGui::DlgSineModulationEdit(PulseDuration, Data.modulationFunction);
	Gui::Control().showDialog(dlg);
    return true;
}


bool CSineModulation::ComputeModulationValue(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, const double &dTime, double &dValue)
{
    WindLabTools::SineModulation sineModulation;
    dValue = sineModulation.computeModulation(dTime, PulseDuration.getQuantityValue().getValueAs(Base::Quantity::Second)) * ScaleCoefficient.getValue();
	return true;
}

bool CSineModulation::ComputeModulationVectorT(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;
    for (int k = 0; k < Data.numberOfTimeIncrements.getValue() && returnResult; k++)
	{
		dVarVector(k) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;;	
        returnResult = ComputeModulationValue(Data, location, dFrequency, dVarVector(k), dValVector(k));
	}
	return true;
}

bool CSineModulation::ComputeModulationVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;    
	for (int k = 0; k < Data.numberOfSpatialPosition.getValue() && returnResult; k++)
    {
		dVarVector(k) = k + 1;	
        returnResult = ComputeModulationValue(Data, Base::Vector3d(0,0,0), dFrequency, dTime, dValVector(k));
    }

	return true;
}

bool CSineModulation::ComputeModulationVectorF(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;
    
    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, location, dVarVector);
    
    if (!returnResult)
    {
        Base::Console().Warning("The computation of frequency vector  has failed.\n");

        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeModulationValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;    
}