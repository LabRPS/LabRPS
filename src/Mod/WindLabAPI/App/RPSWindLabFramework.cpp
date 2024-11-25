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
#include "RPSWindLabFramework.h"
#include <iostream> 
#include <math.h>
#include <fstream>				
#include <Mod/WindLabAPI/App/RPSWindLabAPI.h>
#include <App/Application.h>
#include <App/Document.h>

using namespace std;
using namespace WindLabAPI;

CRPSWindLabFramework::CRPSWindLabFramework()
{
}

CRPSWindLabFramework::~CRPSWindLabFramework()
{
}

bool CRPSWindLabFramework::ComputeCrossCorrelationVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }
   
    WindLabAPI::IrpsWLCorrelation* SelectedCorreObject = static_cast<WindLabAPI::IrpsWLCorrelation*>(doc->getObject(Data.correlationFunction.getValue()));
    

	if (NULL == SelectedCorreObject)
	{
        return false;
	}

    bool returnValue = SelectedCorreObject->ComputeCrossCorrelationVectorT(Data, locationJ, locationK, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeCrossCorrelationMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, mat &dCorrelationMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }
   
    WindLabAPI::IrpsWLCorrelation* SelectedCorreObject = static_cast<WindLabAPI::IrpsWLCorrelation*>(doc->getObject(Data.correlationFunction.getValue()));
    

	if (NULL == SelectedCorreObject)
	{
        return false;
	}

    bool returnValue = SelectedCorreObject->ComputeCrossCorrelationMatrixPP(Data, dTime, dCorrelationMatrix);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeFrequenciesVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLFrequencyDistribution* SelectedFrequencyDistributionObject = static_cast<WindLabAPI::IrpsWLFrequencyDistribution*>(doc->getObject(Data.frequencyDistribution.getValue()));

	if (NULL == SelectedFrequencyDistributionObject)
	{
        return false;
	}

    bool returnValue = SelectedFrequencyDistributionObject->ComputeFrequenciesVectorF(Data, location, dValVector);


    return returnValue;
}

bool CRPSWindLabFramework::ComputeFrequenciesMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLFrequencyDistribution* SelectedFrequencyDistributionObject = static_cast<WindLabAPI::IrpsWLFrequencyDistribution*>(doc->getObject(Data.frequencyDistribution.getValue()));

	if (NULL == SelectedFrequencyDistributionObject)
	{
        return false;
	}

    bool returnValue = SelectedFrequencyDistributionObject->ComputeFrequenciesMatrixFP(Data, dMatrix);


    return returnValue;
}


bool CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimulationData &Data, mat &dLocCoord)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLLocationDistribution* SelectedDistrObject = static_cast<WindLabAPI::IrpsWLLocationDistribution*>(doc->getObject(Data.spatialDistribution.getValue()));


	if (NULL == SelectedDistrObject)
	{
        return false;
	}

    bool returnValue = SelectedDistrObject->ComputeLocationCoordinateMatrixP3(Data, dLocCoord);


    return returnValue;
}

bool CRPSWindLabFramework::ComputeMeanWindSpeedVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLMean* SelectedMeanObject = static_cast<WindLabAPI::IrpsWLMean*>(doc->getObject(Data.meanFunction.getValue()));

	if (NULL == SelectedMeanObject)
	{
        return false;
	}

    bool returnValue = SelectedMeanObject->ComputeMeanWindSpeedVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeMeanWindSpeedVectorT(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLMean* SelectedMeanObject = static_cast<WindLabAPI::IrpsWLMean*>(doc->getObject(Data.meanFunction.getValue()));

	if (NULL == SelectedMeanObject)
	{
        return false;
	}

    bool returnValue = SelectedMeanObject->ComputeMeanWindSpeedVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeModulationVectorT(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLModulation* SelectedModulationObject = static_cast<WindLabAPI::IrpsWLModulation*>(doc->getObject(Data.modulationFunction.getValue()));

	if (NULL == SelectedModulationObject)
	{
        return false;
	}

    bool returnValue = SelectedModulationObject->ComputeModulationVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeModulationVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLModulation* SelectedModulationObject = static_cast<WindLabAPI::IrpsWLModulation*>(doc->getObject(Data.modulationFunction.getValue()));

	if (NULL == SelectedModulationObject)
	{
        return false;
	}

    bool returnValue = SelectedModulationObject->ComputeModulationVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}



bool CRPSWindLabFramework::ComputeDecomposedCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLPSDdecompositionMethod* SelectedPSDdecomMethodObject = static_cast<WindLabAPI::IrpsWLPSDdecompositionMethod*>(doc->getObject(Data.cpsdDecompositionMethod.getValue()));

    if (NULL == SelectedPSDdecomMethodObject)
    {
        return false;
    }

    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeDecomposedCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLPSDdecompositionMethod* SelectedPSDdecomMethodObject = static_cast<WindLabAPI::IrpsWLPSDdecompositionMethod*>(doc->getObject(Data.cpsdDecompositionMethod.getValue()));

    if (NULL == SelectedPSDdecomMethodObject)
    {
        return false;
    }

    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLPSDdecompositionMethod* SelectedPSDdecomMethodObject = static_cast<WindLabAPI::IrpsWLPSDdecompositionMethod*>(doc->getObject(Data.cpsdDecompositionMethod.getValue()));

	if (NULL == SelectedPSDdecomMethodObject)
	{
        return false;
	}

    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixPP(Data, dFrequency, dTime, dPSDMatrix);

    return returnValue;
}

bool CRPSWindLabFramework::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData &Data, mat &dRandomValueArray)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLRandomness* SelectedRandomnessObject = static_cast<WindLabAPI::IrpsWLRandomness*>(doc->getObject(Data.randomnessProvider.getValue()));

	if (NULL == SelectedRandomnessObject)
	{
        return false;
	}

    bool returnValue = SelectedRandomnessObject->GenerateRandomMatrixFP(Data, dRandomValueArray);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeXCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLXSpectrum* SelectedXSpectrumObject = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(Data.alongWindSpectrumModel.getValue()));

	if (NULL == SelectedXSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedXSpectrumObject->ComputeXCrossSpectrumVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeXCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLXSpectrum* SelectedXSpectrumObject = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(Data.alongWindSpectrumModel.getValue()));

	if (NULL == SelectedXSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedXSpectrumObject->ComputeXCrossSpectrumVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

 bool CRPSWindLabFramework::ComputeXCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
 {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLXSpectrum* SelectedXSpectrumObject = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(Data.alongWindSpectrumModel.getValue()));

     if (NULL == SelectedXSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixPP(Data, dFrequency, dTime, psdMatrix);

     return returnValue;
 }

  bool CRPSWindLabFramework::ComputeXAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
  {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLXSpectrum* SelectedXSpectrumObject = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(Data.alongWindSpectrumModel.getValue()));

     if (NULL == SelectedXSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedXSpectrumObject->ComputeXAutoSpectrumValue(Data,location, dFrequency, dTime, dValue);

     return returnValue;
 }  
  bool CRPSWindLabFramework::ComputeXAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
  {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLXSpectrum* SelectedXSpectrumObject = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(Data.alongWindSpectrumModel.getValue()));

     if (NULL == SelectedXSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedXSpectrumObject->ComputeXAutoSpectrumVectorF(Data, location, dTime, dVarVector, dValVector);

     return returnValue;
 }

  bool CRPSWindLabFramework::ComputeXAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
  {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLXSpectrum* SelectedXSpectrumObject = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(Data.alongWindSpectrumModel.getValue()));

     if (NULL == SelectedXSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedXSpectrumObject->ComputeXAutoSpectrumVectorT(Data, location, dFrequency, dVarVector, dValVector);

     return returnValue;
 }


bool CRPSWindLabFramework::ComputeYCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)

{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLYSpectrum* SelectedYSpectrumObject = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(Data.acrossWindSpectrumModel.getValue()));

	if (NULL == SelectedYSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedYSpectrumObject->ComputeYCrossSpectrumVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeYCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLYSpectrum* SelectedYSpectrumObject = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(Data.acrossWindSpectrumModel.getValue()));

	if (NULL == SelectedYSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedYSpectrumObject->ComputeYCrossSpectrumVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

 bool CRPSWindLabFramework::ComputeYCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
 {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLYSpectrum* SelectedYSpectrumObject = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(Data.acrossWindSpectrumModel.getValue()));

     if (NULL == SelectedYSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixPP(Data, dFrequency, dTime, psdMatrix);

     return returnValue;
 }

bool CRPSWindLabFramework::ComputeYAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLYSpectrum* SelectedYSpectrumObject = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(Data.acrossWindSpectrumModel.getValue()));

     if (NULL == SelectedYSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedYSpectrumObject->ComputeYAutoSpectrumValue(Data, location, dFrequency, dTime, dValue);

     return returnValue;
 }    
bool CRPSWindLabFramework::ComputeYAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLYSpectrum* SelectedYSpectrumObject = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(Data.acrossWindSpectrumModel.getValue()));

     if (NULL == SelectedYSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedYSpectrumObject->ComputeYAutoSpectrumVectorF(Data, location, dTime, dVarVector, dValVector);

     return returnValue;
 }
bool CRPSWindLabFramework::ComputeYAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLYSpectrum* SelectedYSpectrumObject = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(Data.acrossWindSpectrumModel.getValue()));

     if (NULL == SelectedYSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedYSpectrumObject->ComputeYAutoSpectrumVectorT(Data, location, dFrequency, dVarVector, dValVector);

     return returnValue;
 }


bool CRPSWindLabFramework::ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)

{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLZSpectrum* SelectedZSpectrumObject = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(Data.verticalWindSpectrumModel.getValue()));

	if (NULL == SelectedZSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedZSpectrumObject->ComputeZCrossSpectrumVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLZSpectrum* SelectedZSpectrumObject = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(Data.verticalWindSpectrumModel.getValue()));

	if (NULL == SelectedZSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedZSpectrumObject->ComputeZCrossSpectrumVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

 bool CRPSWindLabFramework::ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
 {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLZSpectrum* SelectedZSpectrumObject = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(Data.verticalWindSpectrumModel.getValue()));

     if (NULL == SelectedZSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixPP(Data, dFrequency, dTime, psdMatrix);

     return returnValue;
 }

bool CRPSWindLabFramework::ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLZSpectrum* SelectedZSpectrumObject = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(Data.verticalWindSpectrumModel.getValue()));

     if (NULL == SelectedZSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedZSpectrumObject->ComputeZAutoSpectrumValue(Data, location, dFrequency, dTime, dValue);

     return returnValue;
 }    
bool CRPSWindLabFramework::ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLZSpectrum* SelectedZSpectrumObject = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(Data.verticalWindSpectrumModel.getValue()));

     if (NULL == SelectedZSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedZSpectrumObject->ComputeZAutoSpectrumVectorF(Data, location, dTime, dVarVector, dValVector);

     return returnValue;
 }
bool CRPSWindLabFramework::ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLZSpectrum* SelectedZSpectrumObject = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(Data.verticalWindSpectrumModel.getValue()));

     if (NULL == SelectedZSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedZSpectrumObject->ComputeZAutoSpectrumVectorT(Data, location, dFrequency, dVarVector, dValVector);

     return returnValue;
 }

bool CRPSWindLabFramework::ComputeCrossCoherenceValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLCoherence* SelectedCoherenceObject = static_cast<WindLabAPI::IrpsWLCoherence*>(doc->getObject(Data.coherenceFunction.getValue()));

	if (NULL == SelectedCoherenceObject)
	{
        return false;
	}

    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, dValue);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeCrossCoherenceVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLCoherence* SelectedCoherenceObject = static_cast<WindLabAPI::IrpsWLCoherence*>(doc->getObject(Data.coherenceFunction.getValue()));

    if (NULL == SelectedCoherenceObject)
    {
        return false;
    }

    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeCrossCoherenceVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLCoherence* SelectedCoherenceObject = static_cast<WindLabAPI::IrpsWLCoherence*>(doc->getObject(Data.coherenceFunction.getValue()));

    if (NULL == SelectedCoherenceObject)
    {
        return false;
    }

    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceVectorT(Data,locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeCrossCoherenceMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLCoherence* SelectedCoherenceObject = static_cast<WindLabAPI::IrpsWLCoherence*>(doc->getObject(Data.coherenceFunction.getValue()));

    if (NULL == SelectedCoherenceObject)
    {
        return false;
    }

    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceMatrixPP(Data, dFrequency, dTime, dCoherenceMatrix);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeCrossCorrelationValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLCorrelation* SelectedCorreObject = static_cast<WindLabAPI::IrpsWLCorrelation*>(doc->getObject(Data.correlationFunction.getValue()));

	if (NULL == SelectedCorreObject)
	{
        return false;
	}

    bool returnValue = SelectedCorreObject->ComputeCrossCorrelationValue(Data, locationJ, locationK, dTime, dValue);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeMeanWindSpeedValue(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLMean* SelectedMeanObject = static_cast<WindLabAPI::IrpsWLMean*>(doc->getObject(Data.meanFunction.getValue()));

	if (NULL == SelectedMeanObject)
	{
        return false;
	}

    bool returnValue = SelectedMeanObject->ComputeMeanWindSpeedValue(Data, location, dTime, dValue);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeModulationValue(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLModulation* SelectedModulationObject = static_cast<WindLabAPI::IrpsWLModulation*>(doc->getObject(Data.modulationFunction.getValue()));

	if (NULL == SelectedModulationObject)
	{
        return false;
	}

    bool returnValue = SelectedModulationObject->ComputeModulationValue(Data, location, dTime, dValue);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeRandomValue(const WindLabAPI::WindLabSimulationData &Data, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLRandomness* SelectedRandomnessObject = static_cast<WindLabAPI::IrpsWLRandomness*>(doc->getObject(Data.randomnessProvider.getValue()));

	if (NULL == SelectedRandomnessObject)
	{
        return false;
	}

	if (Data.comparisonMode.getValue())
	{

	}

    bool returnValue = SelectedRandomnessObject->ComputeRandomValue(Data, dValue);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeXCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLXSpectrum* SelectedXSpectrumObject = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(Data.alongWindSpectrumModel.getValue()));

	if (NULL == SelectedXSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedXSpectrumObject->ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, dValue);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeYCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLYSpectrum* SelectedYSpectrumObject = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(Data.acrossWindSpectrumModel.getValue()));

	if (NULL == SelectedYSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedYSpectrumObject->ComputeYCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, dValue);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLZSpectrum* SelectedZSpectrumObject = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(Data.verticalWindSpectrumModel.getValue()));

	if (NULL == SelectedZSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedZSpectrumObject->ComputeZCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, dValue);

    return returnValue;
}


// X, Y, Z

bool CRPSWindLabFramework::ComputeCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    if (strcmp(Data.WindDirection.getValueAsString(), "Along wind") == 0)
	{
       return CRPSWindLabFramework::ComputeXCrossSpectrumVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);
	}
    else if (strcmp(Data.WindDirection.getValueAsString(), "Across wind") == 0)
	{
        return CRPSWindLabFramework::ComputeYCrossSpectrumVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

	}
    else if (strcmp(Data.WindDirection.getValueAsString(), "Vertical wind") == 0)
	{
       return CRPSWindLabFramework::ComputeZCrossSpectrumVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);
	}

    return false;

}

bool CRPSWindLabFramework::ComputeCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    if (strcmp(Data.WindDirection.getValueAsString(), "Along wind") == 0)
	{
        return CRPSWindLabFramework::ComputeXCrossSpectrumVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);
	}
    else if (strcmp(Data.WindDirection.getValueAsString(), "Across wind") == 0)
	{
       return CRPSWindLabFramework::ComputeYCrossSpectrumVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);

	}
    else if (strcmp(Data.WindDirection.getValueAsString(), "Vertical wind") == 0)
	{
        return CRPSWindLabFramework::ComputeZCrossSpectrumVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);
	}

    return false;
}

bool CRPSWindLabFramework::ComputeCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    if (strcmp(Data.WindDirection.getValueAsString(), "Along wind") == 0)
	{
       return CRPSWindLabFramework::ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, dValue);
	}
    else if (strcmp(Data.WindDirection.getValueAsString(), "Across wind") == 0)
	{
       return CRPSWindLabFramework::ComputeYCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, dValue);
    }
    else if (strcmp(Data.WindDirection.getValueAsString(), "Vertical wind") == 0)
	{
       return CRPSWindLabFramework::ComputeZCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, dValue);
    }

    return false;
}

bool CRPSWindLabFramework::ComputeCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix)
{
	if (strcmp(Data.WindDirection.getValueAsString(), "Along wind") == 0)
	{
       return CRPSWindLabFramework::ComputeXCrossSpectrumMatrixPP(Data, dFrequency, dTime, dPSDMatrix);
	}
    else if (strcmp(Data.WindDirection.getValueAsString(), "Across wind") == 0)
	{
       return CRPSWindLabFramework::ComputeYCrossSpectrumMatrixPP(Data, dFrequency, dTime, dPSDMatrix);
    }
    else if (strcmp(Data.WindDirection.getValueAsString(), "Vertical wind") == 0)
	{
       return CRPSWindLabFramework::ComputeZCrossSpectrumMatrixPP(Data, dFrequency, dTime, dPSDMatrix);
    }

    return false;
}

 bool CRPSWindLabFramework::ComputeAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
 {
	if (strcmp(Data.WindDirection.getValueAsString(), "Along wind") == 0)
	{
       return CRPSWindLabFramework::ComputeXAutoSpectrumValue(Data, location, dFrequency, dTime, dValue);
	}
    else if (strcmp(Data.WindDirection.getValueAsString(), "Across wind") == 0)
	{
       return CRPSWindLabFramework::ComputeYAutoSpectrumValue(Data, location, dFrequency, dTime, dValue);
    }
    else if (strcmp(Data.WindDirection.getValueAsString(), "Vertical wind") == 0)
	{
       return CRPSWindLabFramework::ComputeZAutoSpectrumValue(Data, location, dFrequency, dTime, dValue);
    }

    return false;
}   
 bool CRPSWindLabFramework::ComputeAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
 {
	if (strcmp(Data.WindDirection.getValueAsString(), "Along wind") == 0)
	{
       return CRPSWindLabFramework::ComputeXAutoSpectrumVectorF(Data, location, dTime, dVarVector, dValVector);
	}
    else if (strcmp(Data.WindDirection.getValueAsString(), "Across wind") == 0)
	{
       return CRPSWindLabFramework::ComputeYAutoSpectrumVectorF(Data, location, dTime, dVarVector, dValVector);
    }
    else if (strcmp(Data.WindDirection.getValueAsString(), "Vertical wind") == 0)
	{
       return CRPSWindLabFramework::ComputeZAutoSpectrumVectorF(Data, location, dTime, dVarVector, dValVector);
    }

    return false;
}
 bool CRPSWindLabFramework::ComputeAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
 {
	if (strcmp(Data.WindDirection.getValueAsString(), "Along wind") == 0)
	{
       return CRPSWindLabFramework::ComputeXAutoSpectrumVectorT(Data, location, dFrequency, dVarVector, dValVector);
	}
    else if (strcmp(Data.WindDirection.getValueAsString(), "Across wind") == 0)
	{
       return CRPSWindLabFramework::ComputeYAutoSpectrumVectorT(Data, location, dFrequency, dVarVector, dValVector);
    }
    else if (strcmp(Data.WindDirection.getValueAsString(), "Vertical wind") == 0)
	{
       return CRPSWindLabFramework::ComputeZAutoSpectrumVectorT(Data, location, dFrequency, dVarVector, dValVector);
    }

    return false;
}

 bool CRPSWindLabFramework::ComputeFrequencyValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue)
 {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLFrequencyDistribution* SelectedFrequencyDistributionObject = static_cast<WindLabAPI::IrpsWLFrequencyDistribution*>(doc->getObject(Data.frequencyDistribution.getValue()));

     if (NULL == SelectedFrequencyDistributionObject)
     {
         return false;
     }

     bool returnValue = SelectedFrequencyDistributionObject->ComputeFrequencyValue(Data, location, frequencyIndex, dValue);

     return returnValue;
 }

WindLabAPI::WindLabFeatureDescription* CRPSWindLabFramework::getWindLabFeatureDescription(const std::string& name)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return nullptr;
     }

     WindLabAPI::WindLabFeature* feature = static_cast<WindLabAPI::WindLabFeature*>(doc->getObject(name.c_str()));

     if (!feature)
     {
         return nullptr;
     }

     WindLabAPI::WindLabFeatureDescription* information = new WindLabAPI::WindLabFeatureDescription();

     information->PluginName.setValue(feature->PluginName.getValue());
     information->PublicationTitle.setValue(feature->PublicationTopic.getValue());
     information->PublicationLink.setValue(feature->LinkToPublication.getValue());
     information->PublicationAuthor.setValue(feature->PublicationAuthor.getValue());
     information->PublicationDate.setValue(feature->PublicationDate.getValue());
     information->ReleaseDate.setValue(feature->ReleaseDate.getValue());
     information->Version.setValue(feature->Version.getValue());
     information->Author.setValue(feature->Author.getValue());
     information->APIVersion.setValue(feature->APIVersion.getValue());
     information->PluginVersion.setValue(feature->PluginVersion.getValue());
     information->Stationarity.setValue(feature->IsStationary.getValue());
     information->type.setValue(feature->FeatureType.getValue());
     information->group.setValue(feature->FeatureGroup.getValue());

	return information;
}

bool CRPSWindLabFramework::TableToolCompute(const WindLabAPI::WindLabSimulationData &Data, const mat &inputTable, mat &outputTable)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLTableTool* feature = static_cast<WindLabAPI::IrpsWLTableTool*>(doc->getObject(Data.tableTool.getValue()));

     if (!feature)
     {
         return false;
     }

     bool returnValue = feature->TableToolCompute(Data, inputTable, outputTable);

     return returnValue;
 }

bool CRPSWindLabFramework::MatrixToolCompute(const WindLabAPI::WindLabSimulationData &Data, const mat &inputMatrix, mat &outputMatrix)
{
      auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     WindLabAPI::IrpsWLMatrixTool* feature = static_cast<WindLabAPI::IrpsWLMatrixTool*>(doc->getObject(Data.matrixTool.getValue()));

     if (!feature)
     {
         return false;
     }

     bool returnValue = feature->MatrixToolCompute(Data, inputMatrix, outputMatrix);

     return returnValue;
}

bool CRPSWindLabFramework::UserDefinedRPSObjectCompute(const WindLabAPI::WindLabSimulationData &Data, mat &dresult)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLUserDefinedRPSObject* SelectedUserDefinedRPSObject = static_cast<WindLabAPI::IrpsWLUserDefinedRPSObject*>(doc->getObject(Data.userDefinedRPSObject.getValue()));

	if (NULL == SelectedUserDefinedRPSObject)
	{
        return false;
	}

    bool returnValue = SelectedUserDefinedRPSObject->UserDefinedRPSObjectCompute(Data, dresult);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeCPDValue(const WindLabAPI::WindLabSimulationData &Data, const double &x, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLCumulativeProbabilityDistribution* SelectedObject = static_cast<WindLabAPI::IrpsWLCumulativeProbabilityDistribution*>(doc->getObject(Data.cumulativeProbabilityDistribution.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeCPDValue(Data, x, dValue);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLCumulativeProbabilityDistribution* SelectedObject = static_cast<WindLabAPI::IrpsWLCumulativeProbabilityDistribution*>(doc->getObject(Data.cumulativeProbabilityDistribution.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeCPDVectorX(Data, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeGustFactorValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLGustFactor* SelectedObject = static_cast<WindLabAPI::IrpsWLGustFactor*>(doc->getObject(Data.gustFactor.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeGustFactorValue(Data, location, dTime, dValue);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeGustFactorVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLGustFactor* SelectedObject = static_cast<WindLabAPI::IrpsWLGustFactor*>(doc->getObject(Data.gustFactor.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeGustFactorVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeGustFactorVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLGustFactor* SelectedObject = static_cast<WindLabAPI::IrpsWLGustFactor*>(doc->getObject(Data.gustFactor.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeGustFactorVectorT(Data, location, dVarVector,dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeKurtosisValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLKurtosis* SelectedObject = static_cast<WindLabAPI::IrpsWLKurtosis*>(doc->getObject(Data.kurtosis.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeKurtosisValue(Data, location, dTime, dValue);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeKurtosisVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLKurtosis* SelectedObject = static_cast<WindLabAPI::IrpsWLKurtosis*>(doc->getObject(Data.kurtosis.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeKurtosisVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeKurtosisVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLKurtosis* SelectedObject = static_cast<WindLabAPI::IrpsWLKurtosis*>(doc->getObject(Data.kurtosis.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeKurtosisVectorT(Data, location, dVarVector,dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputePeakFactorValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLPeakFactor* SelectedObject = static_cast<WindLabAPI::IrpsWLPeakFactor*>(doc->getObject(Data.peakFactor.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePeakFactorValue(Data, location, dTime, dValue);

    return returnValue;
}
bool CRPSWindLabFramework::ComputePeakFactorVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLPeakFactor* SelectedObject = static_cast<WindLabAPI::IrpsWLPeakFactor*>(doc->getObject(Data.peakFactor.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePeakFactorVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputePeakFactorVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLPeakFactor* SelectedObject = static_cast<WindLabAPI::IrpsWLPeakFactor*>(doc->getObject(Data.peakFactor.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePeakFactorVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputePDFValue(const WindLabAPI::WindLabSimulationData &Data, const double &x, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLProbabilityDensityFunction* SelectedObject = static_cast<WindLabAPI::IrpsWLProbabilityDensityFunction*>(doc->getObject(Data.probabilityDensityFunction.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePDFValue(Data, x, dValue);

    return returnValue;
}
bool CRPSWindLabFramework::ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLProbabilityDensityFunction* SelectedObject = static_cast<WindLabAPI::IrpsWLProbabilityDensityFunction*>(doc->getObject(Data.probabilityDensityFunction.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePDFVectorX(Data, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeRoughnessValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLRoughness* SelectedObject = static_cast<WindLabAPI::IrpsWLRoughness*>(doc->getObject(Data.roughness.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeRoughnessValue(Data, location, dTime, dValue);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeRoughnessVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLRoughness* SelectedObject = static_cast<WindLabAPI::IrpsWLRoughness*>(doc->getObject(Data.roughness.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeRoughnessVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeRoughnessVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLRoughness* SelectedObject = static_cast<WindLabAPI::IrpsWLRoughness*>(doc->getObject(Data.roughness.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeRoughnessVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeShearVelocityOfFlowValue(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLShearVelocityOfFlow* SelectedObject = static_cast<WindLabAPI::IrpsWLShearVelocityOfFlow*>(doc->getObject(Data.shearVelocityOfFlow.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeShearVelocityOfFlowValue(Data,location, dTime, dValue);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeShearVelocityOfFlowVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLShearVelocityOfFlow* SelectedObject = static_cast<WindLabAPI::IrpsWLShearVelocityOfFlow*>(doc->getObject(Data.shearVelocityOfFlow.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeShearVelocityOfFlowVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeShearVelocityOfFlowVectorT(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLShearVelocityOfFlow* SelectedObject = static_cast<WindLabAPI::IrpsWLShearVelocityOfFlow*>(doc->getObject(Data.shearVelocityOfFlow.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeShearVelocityOfFlowVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeSkewnessValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLSkewness* SelectedObject = static_cast<WindLabAPI::IrpsWLSkewness*>(doc->getObject(Data.skewness.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeSkewnessValue(Data, location, dTime, dValue);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeSkewnessVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLSkewness* SelectedObject = static_cast<WindLabAPI::IrpsWLSkewness*>(doc->getObject(Data.skewness.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeSkewnessVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeSkewnessVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLSkewness* SelectedObject = static_cast<WindLabAPI::IrpsWLSkewness*>(doc->getObject(Data.skewness.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeSkewnessVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeStandardDeviationValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLStandardDeviation* SelectedObject = static_cast<WindLabAPI::IrpsWLStandardDeviation*>(doc->getObject(Data.standardDeviation.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeStandardDeviationValue(Data, location, dTime, dValue);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeStandardDeviationVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLStandardDeviation* SelectedObject = static_cast<WindLabAPI::IrpsWLStandardDeviation*>(doc->getObject(Data.standardDeviation.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeStandardDeviationVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}


bool CRPSWindLabFramework::ComputeStandardDeviationVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLStandardDeviation* SelectedObject = static_cast<WindLabAPI::IrpsWLStandardDeviation*>(doc->getObject(Data.standardDeviation.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeStandardDeviationVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceIntensityValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLTurbulenceIntensity* SelectedObject = static_cast<WindLabAPI::IrpsWLTurbulenceIntensity*>(doc->getObject(Data.turbulenceIntensity.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeTurbulenceIntensityValue(Data, location, dTime, dValue);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceIntensityVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLTurbulenceIntensity* SelectedObject = static_cast<WindLabAPI::IrpsWLTurbulenceIntensity*>(doc->getObject(Data.turbulenceIntensity.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeTurbulenceIntensityVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceIntensityVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLTurbulenceIntensity* SelectedObject = static_cast<WindLabAPI::IrpsWLTurbulenceIntensity*>(doc->getObject(Data.turbulenceIntensity.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeTurbulenceIntensityVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceScaleValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLTurbulenceScale* SelectedObject = static_cast<WindLabAPI::IrpsWLTurbulenceScale*>(doc->getObject(Data.turbulenceScale.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeTurbulenceScaleValue(Data, location, dTime, dValue);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceScaleVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLTurbulenceScale* SelectedObject = static_cast<WindLabAPI::IrpsWLTurbulenceScale*>(doc->getObject(Data.turbulenceScale.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeTurbulenceScaleVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceScaleVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLTurbulenceScale* SelectedObject = static_cast<WindLabAPI::IrpsWLTurbulenceScale*>(doc->getObject(Data.turbulenceScale.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeTurbulenceScaleVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeVarianceValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLVariance* SelectedObject = static_cast<WindLabAPI::IrpsWLVariance*>(doc->getObject(Data.variance.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeVarianceValue(Data, location, dTime, dValue);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeVarianceVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLVariance* SelectedObject = static_cast<WindLabAPI::IrpsWLVariance*>(doc->getObject(Data.variance.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeVarianceVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeVarianceVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLVariance* SelectedObject = static_cast<WindLabAPI::IrpsWLVariance*>(doc->getObject(Data.variance.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeVarianceVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}
bool CRPSWindLabFramework::ComputeWavePassageEffectValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLWavePassageEffect* SelectedObject = static_cast<WindLabAPI::IrpsWLWavePassageEffect*>(doc->getObject(Data.wavePassageEffect.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeWavePassageEffectValue(Data, locationJ, locationK, dFrequency, dTime, dValue);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeWavePassageEffectVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLWavePassageEffect* SelectedObject = static_cast<WindLabAPI::IrpsWLWavePassageEffect*>(doc->getObject(Data.wavePassageEffect.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeWavePassageEffectVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeWavePassageEffectVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLWavePassageEffect* SelectedObject = static_cast<WindLabAPI::IrpsWLWavePassageEffect*>(doc->getObject(Data.wavePassageEffect.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeWavePassageEffectVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

bool CRPSWindLabFramework::ComputeWavePassageEffectMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    WindLabAPI::IrpsWLWavePassageEffect* SelectedObject = static_cast<WindLabAPI::IrpsWLWavePassageEffect*>(doc->getObject(Data.wavePassageEffect.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeWavePassageEffectMatrixPP(Data, dFrequency, dTime, dCoherenceMatrix);

    return returnValue;
}

int CRPSWindLabFramework::getLocationIndex(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d locationTobeFound)
{
    mat locationMatrix(Data.numberOfSpatialPosition.getValue(), 4);

    bool returnResult = ComputeLocationCoordinateMatrixP3(Data, locationMatrix);

    if (!returnResult)
    {
        return -1;
    }

    Base::Vector3d location(0, 0, 0);

    for (int m = 0; m < locationMatrix.rows(); m++) {

        location = Base::Vector3d(locationMatrix(m, 1), locationMatrix(m, 2), locationMatrix(m, 3));

        if (location == locationTobeFound) {
            
            return m;
        }
    }

    return -1;
}