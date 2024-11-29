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

#include "PreCompiled.h"
#include "RPSWLPowerLowProfile.h"
#include <Mod/WindLabAPI/App/WindLabSimulationData.h>
#include <Mod/WindLabTools/App/meanWindSpeed/PowerLawMeanWindSpeed.h>
#include "Widgets/DlgPowerLowProfile.h"
#include <App/Document.h>
#include <App/DocumentObject.h>
#include <App/Application.h>
#include <Base/Console.h>
#include <Gui/Control.h>
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>


using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::RPSWLPowerLowProfile, WindLabAPI::WindLabFeatureMeanWind)

RPSWLPowerLowProfile::RPSWLPowerLowProfile()
{
	ADD_PROPERTY_TYPE(ReferenceHeight, (10000.0), "Parameters", App::Prop_None, "The mean speed reference height");
    ADD_PROPERTY_TYPE(ReferenceSpeed, (30000.0), "Parameters", App::Prop_None, "The mean speed reference speed");
    ADD_PROPERTY_TYPE(DimensionlessPower, (0.12), "Parameters", App::Prop_None, "The dimensionless power");
    ADD_PROPERTY_TYPE(ZeroPlanDisplacement, (0), "Parameters", App::Prop_None, "The zero plan displacement");
    this->OutputUnit.setValue("m/s");
}

bool RPSWLPowerLowProfile::ComputeMeanWindSpeedVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
	// local array for the location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

	//get the active document
	auto doc = App::GetApplication().getActiveDocument();
	if (!doc)
	{
		return false;
	}
	
	// Compute the location coordinate array
	WindLabAPI::IrpsWLLocationDistribution* activeLocationDis = static_cast<WindLabAPI::IrpsWLLocationDistribution*>(doc->getObject(Data.spatialDistribution.getValue()));
	
	activeLocationDis->ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
	
	if (!activeLocationDis)
	{
		Base::Console().Warning("The computation of the location coordinates matrix has failed.\n");
		return false;
	}

	//const double dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * Data.timeIndex.getValue();
    Base::Vector3d location(0, 0, 0);
	// Compute the mean wind speed matrix
	for (int loop = 0; loop < Data.numberOfSpatialPosition.getValue(); loop++)
	{
        location = Base::Vector3d(dLocCoord(loop, 1), dLocCoord(loop, 2), dLocCoord(loop, 3));
		dVarVector(loop) = loop + 1;
		ComputeMeanWindSpeedValue(Data, location, dTime, dValVector(loop));
	}

	return true;
}
bool RPSWLPowerLowProfile::ComputeMeanWindSpeedVectorT(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
	// local array for the location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

	//get the active document
	auto doc = App::GetApplication().getActiveDocument();
	if (!doc)
	{
		return false;
	}
	// Compute the location coordinate array
	WindLabAPI::IrpsWLLocationDistribution* activeLocationDis = static_cast<WindLabAPI::IrpsWLLocationDistribution*>(doc->getObject(Data.spatialDistribution.getValue()));
	activeLocationDis->ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

	if (!activeLocationDis)
	{
		Base::Console().Warning("The computation of the location coordinates matrix has failed.\n");
		return false;
	}
	// Compute the mean wind speed matrix
	for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue(); loop++)
	{
		const double dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * loop;
        ComputeMeanWindSpeedValue(Data, location, dTime, dValVector(loop));
		dVarVector(loop) = dTime;
	}

	return true;
}
bool RPSWLPowerLowProfile::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
	// the input diolag
    WindLabGui::DlgPowerLowProfileEdit* dlg = new WindLabGui::DlgPowerLowProfileEdit(ReferenceHeight, ReferenceSpeed, DimensionlessPower, ZeroPlanDisplacement, Data.meanFunction);
    Gui::Control().showDialog(dlg);

	return true;
}

bool RPSWLPowerLowProfile::ComputeMeanWindSpeedValue(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    WindLabTools::PowerLawMeanWindSpeed powerLawMeanWindSpeed;

	if (location.z < 0)
	{
        Base::Console().Error("Negative height detected. The computation fails.\n");
		return false;
	}

	if (Data.stationarity.getValue())
	{
		dValue = powerLawMeanWindSpeed.computeMeanWindSpeed(location.z, ReferenceHeight.getQuantityValue().getValueAs(Base::Quantity::Metre), ReferenceSpeed.getQuantityValue().getValueAs(Base::Quantity::Metre), DimensionlessPower.getValue(), ZeroPlanDisplacement.getQuantityValue().getValueAs(Base::Quantity::Metre));
	}
	else if (!Data.stationarity.getValue() && Data.uniformModulation.getValue() && this->IsUniformlyModulated.getValue())
	{
		double dModValue = 0.0;

		bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeModulationValue(Data, location, dTime, dModValue);

        if(!returnResult)
        {
            Base::Console().Error("The computation of the modulation value has failed.\n");
            return false;
        }
        
        dValue = dModValue * powerLawMeanWindSpeed.computeMeanWindSpeed(location.z, ReferenceHeight.getQuantityValue().getValueAs(Base::Quantity::Metre), ReferenceSpeed.getQuantityValue().getValueAs(Base::Quantity::Metre), DimensionlessPower.getValue(), ZeroPlanDisplacement.getQuantityValue().getValueAs(Base::Quantity::Metre));

	}
	else
	{
        Base::Console().Error("The computation of the mean wind speed value has failed. The active feature is not non-stationary.\n");
        return false;
	}

	return true;
}
