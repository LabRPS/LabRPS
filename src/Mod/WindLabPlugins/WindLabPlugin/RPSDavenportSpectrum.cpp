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

#include "RPSDavenportSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLabTools/App/spectrum/DavenportSpectrum.h>
#include "Widgets/DlgDavenportSpectrum.h"
#include <Base/Console.h>
#include <Gui/Control.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Mod/WindLabAPI/App/IrpsWLModulation.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSDavenportSpectrum, WindLabAPI::WindLabFeatureXSpectrum)

CRPSDavenportSpectrum::CRPSDavenportSpectrum()
{
   ADD_PROPERTY_TYPE(MeanWindSpeed10, (30000.0), "Parameters", App::Prop_None, "The mean wind speed at 10 meters height above sea.");
}

bool CRPSDavenportSpectrum::ComputeXCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    if (!returnResult)
    {
        Base::Console().Error("The computation of the discrete frequencies vector has failed.\n");
        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}

bool CRPSDavenportSpectrum::ComputeXCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
   bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}

bool CRPSDavenportSpectrum::ComputeXCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
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

    for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop1++)
    {
        for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop2++)
        {
           locationJ = Base::Vector3d(dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop1, 3));
           locationK = Base::Vector3d(dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 3));
           returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

//Initial setting
bool CRPSDavenportSpectrum::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
	// the input diolag
    WindLabGui::DlgDavenportSpectrumEdit* dlg = new WindLabGui::DlgDavenportSpectrumEdit(MeanWindSpeed10, Data.alongWindSpectrumModel);
	Gui::Control().showDialog(dlg);

    return true;
}


bool CRPSDavenportSpectrum::ComputeXCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
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
        return false;
    }
    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationK, dTime, MEANk);
    if (!returnResult) {
        Base::Console().Error("The computation of mean wind speed fails\n");
        return false;
    }
    returnResult = CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, COHjk);
    if (!returnResult) {
        Base::Console().Error("The computation of coherence fails\n");
        return false;
    }

    WindLabTools::DavenportSpectrum davenportPSD;
  
    //stationary
	if (Data.stationarity.getValue())
	{
        PSDj = davenportPSD.computeAlongWindAutoSpectrum(dFrequency, MeanWindSpeed10.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond));
        PSDk = davenportPSD.computeAlongWindAutoSpectrum(dFrequency, MeanWindSpeed10.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond));
        dValue = std::sqrt(PSDj * PSDk) * COHjk;

    }//non-stationary but uniformly modulated.
	else if (!Data.stationarity.getValue() && Data.uniformModulation.getValue() && this->IsUniformlyModulated.getValue())
	{
		double dModValueJ = 0.0;
        double dModValueK = 0.0;

        returnResult = CRPSWindLabFramework::ComputeModulationValue(Data, locationJ, dTime, dModValueJ);

		if (!returnResult)
		{
            Base::Console().Error("The computation of the modulation value has failed.\n");
			return false;
		}

        returnResult = CRPSWindLabFramework::ComputeModulationValue(Data, locationJ, dTime, dModValueK);

		if (!returnResult)
		{
            Base::Console().Error("The computation of the modulation value has failed.\n");
			return false;
		}

        //we compute the time dependent mean wind speed first before introducing it in the psd formula
        PSDj = davenportPSD.computeAlongWindAutoSpectrum(dFrequency, dModValueJ * MeanWindSpeed10.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond));
        PSDk = davenportPSD.computeAlongWindAutoSpectrum(dFrequency, dModValueK * MeanWindSpeed10.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond));
        dValue = std::sqrt(PSDj * PSDk) * COHjk;
	}
	else//this includes cases where the user chooses non-stationary wind with non-uniforme modulation. This feature cannot be used in this case.
	{
        Base::Console().Error("The computation of the power spectral density value has failed. The active feature does not allow non-stationarity with non-uniform modulation.\n");
        return false;
	}

	return true;
}

bool CRPSDavenportSpectrum::ComputeXAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
   bool returnResult = true;

    double MEAN = 0.0;
    double PSDj = 0.0;

    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, location, dTime, MEAN);
    if (!returnResult) {
        Base::Console().Error("The computation of mean wind speed fails\n");
        return false;
    }

    WindLabTools::DavenportSpectrum davenportPSD;
  
    //stationary
	if (Data.stationarity.getValue())
	{
        dValue = davenportPSD.computeAlongWindAutoSpectrum(dFrequency, MeanWindSpeed10.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond));

    }//non-stationary but uniformly modulated.
	else if (!Data.stationarity.getValue() && Data.uniformModulation.getValue() && this->IsUniformlyModulated.getValue())
	{
		double dModValue = 0.0;

        returnResult = CRPSWindLabFramework::ComputeModulationValue(Data, location, dTime, dModValue);

		if (!returnResult)
		{
            Base::Console().Error("The computation of the modulation value has failed.\n");
			return false;
		}

        //we compute the time dependent mean wind speed first before introducing it in the psd formula
        dValue = davenportPSD.computeAlongWindAutoSpectrum(dFrequency, dModValue * MeanWindSpeed10.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond));
	}
	else//this includes cases where the user chooses non-stationary wind with non-uniforme modulation. This feature cannot be used in this case.
	{
        Base::Console().Error("The computation of the power spectral density value has failed. The active feature does not allow non-stationarity with non-uniform modulation.\n");
        return false;
	}

	return true;
}    
bool CRPSDavenportSpectrum::ComputeXAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
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
        returnResult = ComputeXAutoSpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSDavenportSpectrum::ComputeXAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        
        returnResult = ComputeXAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
} 