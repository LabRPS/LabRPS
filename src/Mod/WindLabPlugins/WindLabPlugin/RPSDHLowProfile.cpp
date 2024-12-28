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
#include "RPSDHLowProfile.h"
#include <Mod/WindLabAPI/App/WindLabSimulationData.h>
#include <Mod/WindLabTools/App/meanWindSpeed/DeavesHarrisMeanWindSpeed.h>
#include "Widgets/DlgDHLowProfile.h"
#include <App/Document.h>
#include <App/DocumentObject.h>
#include <App/Application.h>
#include <Base/Console.h>
#include <Gui/Control.h>
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSDHLowProfile, WindLabAPI::WindLabFeatureMeanWind)

CRPSDHLowProfile::CRPSDHLowProfile()
{
	ADD_PROPERTY_TYPE(TerrainRoughness, (0.01), "Parameters", App::Prop_None, "The terrain roughness length");
    ADD_PROPERTY_TYPE(ShearVelocity, (1.760), "Parameters", App::Prop_None, "The shear velocity of the flow");
    ADD_PROPERTY_TYPE(ZeroPlanDisplacement, (0.00), "Parameters", App::Prop_None, "The zero plan displacement");
    ADD_PROPERTY_TYPE(Latitude, (0.00), "Parameters", App::Prop_None, "The latitude");
	ADD_PROPERTY_TYPE(EarthAngularVelocity, (0.0000729), "Parameters", App::Prop_None, "The earth angular velocity");
    ADD_PROPERTY_TYPE(Betta, (6.0), "Parameters", App::Prop_None, "The coefficient beta");
    
}

bool CRPSDHLowProfile::ComputeMeanWindSpeedVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
	mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

    bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if(!returnResult)
    {
        Base::Console().Error("The computation of the location coordinates matrix has failed.\n");
        
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

bool CRPSDHLowProfile::ComputeMeanWindSpeedVectorT(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
	mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

    bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if(!returnResult)
    {
        Base::Console().Error("The computation of the location coordinates matrix has failed.\n");
        
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
bool CRPSDHLowProfile::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
	// the input diolag
    WindLabGui::DlgDHLowProfileEdit* dlg = new WindLabGui::DlgDHLowProfileEdit(TerrainRoughness, ShearVelocity, ZeroPlanDisplacement, Latitude, EarthAngularVelocity, Betta, Data.meanFunction);
	Gui::Control().showDialog(dlg);

    return true;
}

bool CRPSDHLowProfile::ComputeMeanWindSpeedValue(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    WindLabTools::DeavesHarrisMeanWindSpeed deavesHarrisMeanWindSpeed;

	if (location.z < 0)
	{
        Base::Console().Error("Negative height detected. The computation fails.\n");
		return false;
	}

	dValue = deavesHarrisMeanWindSpeed.computeMeanWindSpeed(location.z, TerrainRoughness.getQuantityValue().getValueAs(Base::Quantity::Metre), ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), ZeroPlanDisplacement.getQuantityValue().getValueAs(Base::Quantity::Metre), Latitude.getQuantityValue().getValueAs(Base::Quantity::Degree), EarthAngularVelocity.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond), Betta.getValue());

	return true;
}
