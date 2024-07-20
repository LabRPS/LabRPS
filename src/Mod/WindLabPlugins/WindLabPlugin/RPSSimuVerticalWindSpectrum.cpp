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

#include "RPSSimuVerticalWindSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLabTools/App/spectrum/SimuSpectrum.h>
#include "Widgets/DlgSimuVerticalWindSpectrum.h"
#include <Base/Console.h>
#include <Gui/Control.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Mod/WindLabAPI/App/IrpsWLModulation.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSSimuVerticalWindSpectrum, WindLabAPI::WindLabFeatureZSpectrum)

CRPSSimuVerticalWindSpectrum::CRPSSimuVerticalWindSpectrum()
{
  ADD_PROPERTY_TYPE(ShearVelocity, (1760.0), "Parameters", App::Prop_None, "The shear velocity of the flow");
  ADD_PROPERTY_TYPE(Constant1, (2.0), "Parameters", App::Prop_None, "Constant 1");
  ADD_PROPERTY_TYPE(Constant2, (5.3), "Parameters", App::Prop_None, "Constant 2");

}

bool CRPSSimuVerticalWindSpectrum::ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    if (!returnResult)
    {
        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeZCrossSpectrumValue(Data, locationJ, locationK, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}

bool CRPSSimuVerticalWindSpectrum::ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeZCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}
bool CRPSSimuVerticalWindSpectrum::ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
{
	 // Local array for location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
    
    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
        if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.") ;
       return false;
    }
    
    Base::Vector3d locationJ(0, 0, 0);
    Base::Vector3d locationK(0, 0, 0);

    for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition.getValue(); loop1++)
    {
        for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition.getValue(); loop2++)
        {
           locationJ = Base::Vector3d(dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop1, 3));
           locationK = Base::Vector3d(dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 3));
           returnResult = ComputeZCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

//Initial setting
bool CRPSSimuVerticalWindSpectrum::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
	WindLabGui::DlgSimuVerticalWindSpectrumEdit* dlg = new WindLabGui::DlgSimuVerticalWindSpectrumEdit(ShearVelocity, Constant1, Constant2, Data.verticalWindSpectrumModel);
	Gui::Control().showDialog(dlg);
    return true;
}


bool CRPSSimuVerticalWindSpectrum::ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    bool returnResult = true;

    double MEANj = 0.0;
    double MEANk = 0.0;
    std::complex<double> COHjk = 0.0;
    double PSDj = 0.0;
    double PSDk = 0.0;

    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationJ, dTime, MEANj);
    if (!returnResult) {
        Base::Console().Error("The computation of mean wind speed fails\n");
        return returnResult;
    }
    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationK, dTime, MEANk);
    if (!returnResult) {
        Base::Console().Error("The computation of mean wind speed fails\n");
        return returnResult;
    }
    returnResult = CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, COHjk);
    if (!returnResult) {
        Base::Console().Error("The computation of coherence fails\n");
        return returnResult;
    }

    WindLabTools::SimuSpectrum simmuPSD;
    PSDj = simmuPSD.computeVerticalWindAutoSpectrum(dFrequency, locationJ.z, MEANj, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue());
    PSDk = simmuPSD.computeVerticalWindAutoSpectrum(dFrequency, locationK.z, MEANk, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue());

	if (Data.stationarity.getValue())
	{
        dValue = std::sqrt(PSDj * PSDk) * COHjk;
    }
	else if (!Data.stationarity.getValue() && Data.uniformModulation.getValue())
	{
		double dModValueJ = 0.0;
        double dModValueK = 0.0;

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
			returnResult = activeFeature->ComputeModulationValue(Data, locationJ, dTime, dModValueJ);

			if (!returnResult)
			{
				Base::Console().Error("The computation of the modulation value has failed.\n");
				return false;
			}

             returnResult = activeFeature->ComputeModulationValue(Data, locationK, dTime, dModValueK);

			if (!returnResult)
			{
				Base::Console().Error("The computation of the modulation value has failed.\n");
				return false;
			}

            dValue = std::sqrt(dModValueJ * PSDj * dModValueK * PSDk) * COHjk;
		}
		else
		{
            dValue = std::sqrt(PSDj * PSDk) * COHjk;
        }
	}
	else
	{
        Base::Console().Error("The computation of the modulation value has failed. The active feature is not non-stationary.\n");
        return false;
	}

	return true;
}

bool CRPSSimuVerticalWindSpectrum::ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
   WindLabTools::SimuSpectrum simmuPSD;

   bool returnResult = true;

   double MEAN = 0.0;

   returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, location, dTime, MEAN);
   if (!returnResult)
   {
        Base::Console().Warning("The computation of mean wind speed fails\n");
        return returnResult;
   }

	if (Data.stationarity.getValue())
	{
        dValue = simmuPSD.computeVerticalWindAutoSpectrum(dFrequency, location.z, MEAN, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue());
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

            dValue = dModValue * simmuPSD.computeVerticalWindAutoSpectrum(dFrequency, location.z, MEAN, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue());
		}
		else
		{
            dValue = simmuPSD.computeVerticalWindAutoSpectrum(dFrequency, location.z, MEAN, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue());
		}
	}
	else
	{
        Base::Console().Error("The computation of the modulation value has failed. The active feature is not non-stationary.\n");
        return false;
	}

	return true;
}    
bool CRPSSimuVerticalWindSpectrum::ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, location, dVarVector);
    
    if (!returnResult)
    {
        Base::Console().Warning("The computation of frequency vector  has failed.\n");

        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeZAutoSpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSSimuVerticalWindSpectrum::ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeZAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}