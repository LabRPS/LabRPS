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

#include "ThreeParaModulation.h"
#include <Mod/WindLabTools/App/modulation/ThreeParametersModulation.h>
#include "Widgets/DlgThreeParaModulation.h"
#include <Gui/Control.h>

	
using namespace WindLab;

PROPERTY_SOURCE(WindLab::CThreeParaModulation, WindLabAPI::WindLabFeatureModulation)

 CThreeParaModulation::CThreeParaModulation()
 {
    ADD_PROPERTY_TYPE(Alpha, (4.98), "The three Parameters", App::Prop_None, "The alpha coefficient");
    ADD_PROPERTY_TYPE(Betta, (3.00), "The three Parameters", App::Prop_None, "The beta coefficient");
    ADD_PROPERTY_TYPE(Lambda, (0.003), "The three Parameters", App::Prop_None, "The lambda coefficient");
    this->OutputUnit.setValue("Dimensionless");

 }

bool CThreeParaModulation::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    WindLabGui::DlgThreeParaModulationEdit* dlg = new WindLabGui::DlgThreeParaModulationEdit(Alpha, Betta, Lambda, Data.modulationFunction);
	Gui::Control().showDialog(dlg);
    return true;
}

bool CThreeParaModulation::ComputeModulationValue(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    WindLabTools::ThreeParametersModulation threeParametersModulation;

    dValue = threeParametersModulation.computeModulation(Alpha.getValue(), Betta.getValue(), Lambda.getValue(), dTime);

	return true;
}


bool CThreeParaModulation::ComputeModulationVectorT(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    WindLabTools::ThreeParametersModulation threeParametersModulation;

	//  Maximum value of modulation function
	double max = 0.0;
	//double 	dTime;

	// For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;
		dVarVector(k) = dTime;
		// compute approximate buffeting force 
        dValVector(k) = threeParametersModulation.computeModulation(Alpha.getValue(), Betta.getValue(), Lambda.getValue(), dTime);

		// Max
		if (dValVector(k) > max)
		{
			max = dValVector(k);
		}
	}

	// For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		// Normalizing the modulation function 
		dValVector(k) /= max;
	}

	return true;

}

bool CThreeParaModulation::ComputeModulationVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    WindLabTools::ThreeParametersModulation threeParametersModulation;

    //  Maximum value of modulation function
    double max = 0.0;
    //const double dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * Data.timeIndex.getValue();
    const double dModValue = threeParametersModulation.computeModulation(dTime, Alpha.getValue(), Betta.getValue(), Lambda.getValue());

    // For each time increment
    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        // compute approximate buffeting force
        dValVector(k) = dModValue;

        // Max
        if (dValVector(k) > max)
        {
            max = dValVector(k);
        }
    }

    // For each time increment
    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        // Normalizing the modulation function
        dValVector(k) /= max;
    }

	return true;
}
