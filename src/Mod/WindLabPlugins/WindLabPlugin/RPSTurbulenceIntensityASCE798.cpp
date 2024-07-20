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

#include "RPSTurbulenceIntensityASCE798.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLabAPI/App/WindLabSimuData.h>
#include <Mod/WindLabTools/App/turbulenceIntensity/TurbulenceIntensity.h>
#include "Widgets/DlgTurbulenceIntensityASCE798.h"
#include <Base/Console.h>
#include <Gui/Control.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Mod/WindLabAPI/App/IrpsWLModulation.h>


using namespace WindLab;

PROPERTY_SOURCE(WindLab::RPSTurbulenceIntensityASCE798, WindLabAPI::WindLabFeatureTurbulenceIntensity)

RPSTurbulenceIntensityASCE798::RPSTurbulenceIntensityASCE798()
{
   ADD_PROPERTY_TYPE(TenMetersHighTurbulenceIntensity, (0.088), "Parameters", App::Prop_None, "The turbulence intensity at height of 10 meters");

}

bool RPSTurbulenceIntensityASCE798::ComputeTurbulenceIntensityValue(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d& location, const double& dTime, double& dValue)
{
    WindLabTools::TurbulenceIntensity turbulenceIntensity;

   bool returnResult = true;

	if (Data.stationarity.getValue())
	{
		dValue = turbulenceIntensity.computeASCETurbulenceIntensityValue(location.z, TenMetersHighTurbulenceIntensity.getValue());
	}
	else if (!Data.stationarity.getValue() && Data.uniformModulation.getValue())
	{
		double dModValue = 0.0;
		auto doc = App::GetApplication().getActiveDocument();
		if (!doc)
		{
			return false;
		}

        WindLabAPI::IrpsWLModulation* activeFeature = static_cast<WindLabAPI::IrpsWLModulation*>(doc->getObject(Data.modulationFunction.getValue()));

		if (!activeFeature)
		{
            Base::Console().Error("The computation of the modulation value has failed.\n");
			return false;
		}

		if (this->IsUniformlyModulated.getValue())
		{
			bool returnResult = activeFeature->ComputeModulationValue(Data, location, dTime, dModValue);

			if (!returnResult)
			{
				Base::Console().Error("The computation of the modulation value has failed.\n");
				return false;
			}

            dValue = dModValue * turbulenceIntensity.computeASCETurbulenceIntensityValue(location.z, TenMetersHighTurbulenceIntensity.getValue());
		}
		else
		{
			dValue = turbulenceIntensity.computeASCETurbulenceIntensityValue(location.z, TenMetersHighTurbulenceIntensity.getValue());
		}
	}
	else
	{
        Base::Console().Error("The computation of the modulation value has failed. The active feature is not non-stationary.\n");
        return false;
	}

	return true;
}

bool RPSTurbulenceIntensityASCE798::ComputeTurbulenceIntensityVectorP(const WindLabAPI::WindLabSimuData& Data, const double& dTime, vec& dVarVector, vec& dValVector)
{
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
	bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.") ;
       return false;
    }

    // The coherence value
	double intensity = 0.0;
    Base::Vector3d location(0, 0, 0);

	for (int loop = 0; loop < Data.numberOfSpatialPosition.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
	{
       location = Base::Vector3d(dLocCoord(loop, 1), dLocCoord(loop, 2), dLocCoord(loop, 3));
       returnResult = ComputeTurbulenceIntensityValue(Data, location, dTime, intensity);
       dVarVector(loop) = location.z;
	   dValVector(loop) = intensity;
	}

	return true;
}

bool RPSTurbulenceIntensityASCE798::ComputeTurbulenceIntensityVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d& location, vec& dVarVector, vec& dValVector)
{
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
	bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.") ;
       return false;
    }

    // The coherence value
	double intensity = 0.0;
	for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
	{
       const double time = Data.minTime.getValue() + Data.timeIncrement.getValue() * (loop);

       returnResult = ComputeTurbulenceIntensityValue(Data, location, time, intensity);
       dVarVector(loop) = time;
	   dValVector(loop) = intensity;
	}

	return true;
}

bool RPSTurbulenceIntensityASCE798::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    // the input diolag
    WindLabGui::DlgTurbulenceIntensityASCE798Edit* dlg = new WindLabGui::DlgTurbulenceIntensityASCE798Edit(TenMetersHighTurbulenceIntensity, Data.turbulenceIntensity);
	Gui::Control().showDialog(dlg);

    return true;
}