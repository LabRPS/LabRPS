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

#include "RPSvonKarmanVerticalWindSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLabTools/App/spectrum/VonKarmanSpectrum.h>
#include "Widgets/DlgvonKarmanVerticalWindSpectrum.h"
#include <Base/Console.h>
#include <Gui/Control.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Mod/WindLabAPI/App/IrpsWLModulation.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSvonKarmanVerticalWindSpectrum, WindLabAPI::WindLabFeatureZSpectrum)

CRPSvonKarmanVerticalWindSpectrum::CRPSvonKarmanVerticalWindSpectrum()
{
  ADD_PROPERTY_TYPE(Constant1, (4.0), "Parameters", App::Prop_None, "Constant 1");
  ADD_PROPERTY_TYPE(Constant2, (755.2), "Parameters", App::Prop_None, "Constant 2");
  ADD_PROPERTY_TYPE(Constant3, (283.2), "Parameters", App::Prop_None, "Constant 3");
  ADD_PROPERTY_TYPE(IntegralLengthScale, (80.0), "Parameters", App::Prop_None, "The integral length scale");
  ADD_PROPERTY_TYPE(StandardDeviation, (1.0), "Parameters", App::Prop_None, "The standard deviation");
  this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_WindLab");
 
}

bool CRPSvonKarmanVerticalWindSpectrum::ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
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
bool CRPSvonKarmanVerticalWindSpectrum::ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeZCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}
bool CRPSvonKarmanVerticalWindSpectrum::ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
{
	 // Local array for location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
    
    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
        if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.\n") ;
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

bool CRPSvonKarmanVerticalWindSpectrum::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    WindLabGui::DlgvonKarmanVerticalWindSpectrumEdit* dlg = new WindLabGui::DlgvonKarmanVerticalWindSpectrumEdit(Constant1, Constant2, IntegralLengthScale, StandardDeviation, Data.verticalWindSpectrumModel);
	Gui::Control().showDialog(dlg);
    return true;
}



bool CRPSvonKarmanVerticalWindSpectrum::ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
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

    WindLabTools::VonKarmanSpectrum vonKarmanPSD;
  
    //stationary and non-stationary but uniformly modulated. For non-stationarity, the user just has to make sure the mean wind speed is time dependent
	if ((Data.stationarity.getValue()) || (!Data.stationarity.getValue() && Data.uniformModulation.getValue() && this->IsUniformModulationFeature.getValue()))
	{
        PSDj = vonKarmanPSD.computeVerticalWindAutoSpectrum(dFrequency, MEANj, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue(), Constant3.getValue());
        PSDk = vonKarmanPSD.computeVerticalWindAutoSpectrum(dFrequency, MEANk, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue(), Constant3.getValue());
        dValue = std::sqrt(PSDj * PSDk) * COHjk;
    }
	else//this includes cases where the user chooses non-stationary wind with non-uniforme modulation. This feature cannot be used in this case.
	{
        Base::Console().Error("The computation of the power spectral density value has failed. The active feature does not allow non-stationarity with non-uniform modulation.\n");
        
        return false;
	}

	return true; 
}

bool CRPSvonKarmanVerticalWindSpectrum::ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
   bool returnResult = true;

    double MEAN = 0.0;

    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, location, dTime, MEAN);
    if (!returnResult) {
        Base::Console().Error("The computation of mean wind speed fails\n");
        return false;
    }

    WindLabTools::VonKarmanSpectrum vonKarmanPSD;
  
    //stationary and non-stationary but uniformly modulated. For non-stationarity, the user just has to make sure the mean wind speed is time dependent
	if ((Data.stationarity.getValue()) || (!Data.stationarity.getValue() && Data.uniformModulation.getValue() && this->IsUniformModulationFeature.getValue()))
	{
        dValue = vonKarmanPSD.computeVerticalWindAutoSpectrum(dFrequency, MEAN, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue(), Constant3.getValue());
    }
	else//this includes cases where the user chooses non-stationary wind with non-uniforme modulation. This feature cannot be used in this case.
	{
        Base::Console().Error("The computation of the power spectral density value has failed. The active feature does not allow non-stationarity with non-uniform modulation.\n");
        
        return false;
	}

	return true;

}    
bool CRPSvonKarmanVerticalWindSpectrum::ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
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
bool CRPSvonKarmanVerticalWindSpectrum::ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeZAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}