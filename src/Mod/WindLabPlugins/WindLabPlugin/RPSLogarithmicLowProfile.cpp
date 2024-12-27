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
#include "RPSLogarithmicLowProfile.h"
#include <Mod/WindLabAPI/App/IrpsWLLocationDistribution.h>
#include "Widgets/DlgLogarithmicLowProfile.h"
#include <Mod/WindLabAPI/App/WindLabSimulationData.h>
#include <Mod/WindLabTools/App/WindLabTools.h>
#include <Mod/WindLabTools/App/meanWindSpeed/LogarithmicMeanWindSpeed.h>
#include <App/Document.h>
#include <App/Application.h>
#include <Base/Console.h>
#include <Gui/Control.h>
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>

using namespace WindLab;
using namespace WindLabAPI;
using namespace App;


PROPERTY_SOURCE(WindLab::RPSLogarithmicLowProfile, WindLabAPI::WindLabFeatureMeanWind)

RPSLogarithmicLowProfile::RPSLogarithmicLowProfile()
{
    ADD_PROPERTY_TYPE(TerrainRoughness, (0.01), "Parameters", Prop_None, "This is the terrain roughness value");
    ADD_PROPERTY_TYPE(ShearVelocity, (1760.0), "Parameters", Prop_None, "This is the shear velocity value");
    ADD_PROPERTY_TYPE(vonKarmanConstant, (0.4), "Parameters", Prop_None, "This is the von karman constant value");
    ADD_PROPERTY_TYPE(ZeroPlanDisplacement, (0), "Parameters", Prop_None, "This is the zero plan displacement value");
    
}
bool RPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
	mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

    bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if(!returnResult)
    {
        Base::Console().Error("The computation of the location coordinates matrix has failed.\n");
        
        return false;
    }
    
    Base::Vector3d location(0, 0, 0);

	// Compute the mean wind speed matrix
    for (int loop = 0; loop < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
	{
       location = Base::Vector3d(dLocCoord(loop, 1), dLocCoord(loop, 2), dLocCoord(loop, 3));
		
       dVarVector(loop) = loop+1;
       
        returnResult = ComputeMeanWindSpeedValue(Data, location, dTime, dValVector(loop));
	}

    return true;
}

bool RPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorT(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    // local array for the location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

   bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if(!returnResult)
    {
       Base::Console().Error("The computation of the location coordinates matrix has failed.\n");
       return false;
    }

    // Compute the mean wind speed matrix
    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        const double dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) *loop;
        
        returnResult = ComputeMeanWindSpeedValue(Data, location, dTime, dValVector(loop));
        
        dVarVector(loop) = dTime;
    }

    return true;
}

bool RPSLogarithmicLowProfile::OnInitialSetting(const WindLabAPI::WindLabSimulationData &Data)
{
    WindLabGui::DlgLogarithmicLowProfileEdit* dlg = new WindLabGui::DlgLogarithmicLowProfileEdit(TerrainRoughness, ShearVelocity, ZeroPlanDisplacement, Data.meanFunction);
    Gui::Control().showDialog(dlg);
	return true;
}

bool RPSLogarithmicLowProfile::ComputeMeanWindSpeedValue(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    WindLabTools::LogarithmicMeanWindSpeed logarithmicMeanWindSpeed;

	if (location.z < 0)
	{
        Base::Console().Error("Negative height detected. The computation fails.\n");
		return false;
	}

    dValue = logarithmicMeanWindSpeed.computeMeanWindSpeed(location.z, TerrainRoughness.getQuantityValue().getValueAs(Base::Quantity::Metre), ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), ZeroPlanDisplacement.getQuantityValue().getValueAs(Base::Quantity::Metre));

	return true;
}
