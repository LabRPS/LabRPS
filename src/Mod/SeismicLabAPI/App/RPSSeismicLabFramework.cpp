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
#include "RPSSeismicLabFramework.h"
#include <iostream> 
#include <math.h>
#include <fstream>				
#include <Mod/SeismicLabAPI/App/RPSSeismicLabAPI.h>
#include <App/Application.h>
#include <App/Document.h>

using namespace std;
using namespace SeismicLabAPI;

CRPSSeismicLabFramework::CRPSSeismicLabFramework()
{
}

CRPSSeismicLabFramework::~CRPSSeismicLabFramework()
{
}

bool CRPSSeismicLabFramework::ComputeCrossCorrelationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }
   
    SeismicLabAPI::IrpsSLCorrelation* SelectedCorreObject = static_cast<SeismicLabAPI::IrpsSLCorrelation*>(doc->getObject(Data.correlationFunction.getValue()));
    

	if (NULL == SelectedCorreObject)
	{
        return false;
	}

    bool returnValue = SelectedCorreObject->ComputeCrossCorrelationVectorT(Data, locationJ, locationK, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeCrossCorrelationMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, mat &dCorrelationMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }
   
    SeismicLabAPI::IrpsSLCorrelation* SelectedCorreObject = static_cast<SeismicLabAPI::IrpsSLCorrelation*>(doc->getObject(Data.correlationFunction.getValue()));
    

	if (NULL == SelectedCorreObject)
	{
        return false;
	}

    bool returnValue = SelectedCorreObject->ComputeCrossCorrelationMatrixPP(Data, dTime, dCorrelationMatrix);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeFrequenciesVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLFrequencyDistribution* SelectedFrequencyDistributionObject = static_cast<SeismicLabAPI::IrpsSLFrequencyDistribution*>(doc->getObject(Data.frequencyDistribution.getValue()));

	if (NULL == SelectedFrequencyDistributionObject)
	{
        return false;
	}

    bool returnValue = SelectedFrequencyDistributionObject->ComputeFrequenciesVectorF(Data, location, dValVector);


    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeFrequenciesMatrixFP(const SeismicLabAPI::SeismicLabSimulationData& Data, mat& dMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLFrequencyDistribution* SelectedFrequencyDistributionObject = static_cast<SeismicLabAPI::IrpsSLFrequencyDistribution*>(doc->getObject(Data.frequencyDistribution.getValue()));

	if (NULL == SelectedFrequencyDistributionObject)
	{
        return false;
	}

    bool returnValue = SelectedFrequencyDistributionObject->ComputeFrequenciesMatrixFP(Data, dMatrix);


    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeLocationCoordinateMatrixP3(const SeismicLabAPI::SeismicLabSimulationData &Data, mat &dLocCoord)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLLocationDistribution* SelectedDistrObject = static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(doc->getObject(Data.spatialDistribution.getValue()));


	if (NULL == SelectedDistrObject)
	{
        return false;
	}

    bool returnValue = SelectedDistrObject->ComputeLocationCoordinateMatrixP3(Data, dLocCoord);


    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeMeanAccelerationSpeedVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLMeanAcceleration* SelectedMeanObject = static_cast<SeismicLabAPI::IrpsSLMeanAcceleration*>(doc->getObject(Data.meanFunction.getValue()));

	if (NULL == SelectedMeanObject)
	{
        return false;
	}

    bool returnValue = SelectedMeanObject->ComputeMeanAccelerationVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeMeanAccelerationSpeedVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLMeanAcceleration* SelectedMeanObject = static_cast<SeismicLabAPI::IrpsSLMeanAcceleration*>(doc->getObject(Data.meanFunction.getValue()));

	if (NULL == SelectedMeanObject)
	{
        return false;
	}

    bool returnValue = SelectedMeanObject->ComputeMeanAccelerationVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeModulationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLModulation* SelectedModulationObject = static_cast<SeismicLabAPI::IrpsSLModulation*>(doc->getObject(Data.modulationFunction.getValue()));

	if (NULL == SelectedModulationObject)
	{
        return false;
	}

    bool returnValue = SelectedModulationObject->ComputeModulationVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeModulationVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLModulation* SelectedModulationObject = static_cast<SeismicLabAPI::IrpsSLModulation*>(doc->getObject(Data.modulationFunction.getValue()));

	if (NULL == SelectedModulationObject)
	{
        return false;
	}

    bool returnValue = SelectedModulationObject->ComputeModulationVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}



bool CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLPSDdecompositionMethod* SelectedPSDdecomMethodObject = static_cast<SeismicLabAPI::IrpsSLPSDdecompositionMethod*>(doc->getObject(Data.cpsdDecompositionMethod.getValue()));

    if (NULL == SelectedPSDdecomMethodObject)
    {
        return false;
    }

    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLPSDdecompositionMethod* SelectedPSDdecomMethodObject = static_cast<SeismicLabAPI::IrpsSLPSDdecompositionMethod*>(doc->getObject(Data.cpsdDecompositionMethod.getValue()));

    if (NULL == SelectedPSDdecomMethodObject)
    {
        return false;
    }

    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLPSDdecompositionMethod* SelectedPSDdecomMethodObject = static_cast<SeismicLabAPI::IrpsSLPSDdecompositionMethod*>(doc->getObject(Data.cpsdDecompositionMethod.getValue()));

	if (NULL == SelectedPSDdecomMethodObject)
	{
        return false;
	}

    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixPP(Data, dFrequency, dTime, dPSDMatrix);

    return returnValue;
}

bool CRPSSeismicLabFramework::GenerateRandomMatrixFP(const SeismicLabAPI::SeismicLabSimulationData &Data, mat &dRandomValueArray)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLRandomness* SelectedRandomnessObject = static_cast<SeismicLabAPI::IrpsSLRandomness*>(doc->getObject(Data.randomnessProvider.getValue()));

	if (NULL == SelectedRandomnessObject)
	{
        return false;
	}

    bool returnValue = SelectedRandomnessObject->GenerateRandomMatrixFP(Data, dRandomValueArray);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeCrossSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLSpectrum* SelectedSpectrumObject = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(Data.spectrumModel.getValue()));

	if (NULL == SelectedSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedSpectrumObject->ComputeCrossSpectrumVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeCrossSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLSpectrum* SelectedSpectrumObject = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(Data.spectrumModel.getValue()));

	if (NULL == SelectedSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedSpectrumObject->ComputeCrossSpectrumVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

 bool CRPSSeismicLabFramework::ComputeCrossSpectrumMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
 {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     SeismicLabAPI::IrpsSLSpectrum* SelectedSpectrumObject = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(Data.spectrumModel.getValue()));

     if (NULL == SelectedSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedSpectrumObject->ComputeCrossSpectrumMatrixPP(Data, dFrequency, dTime, psdMatrix);

     return returnValue;
 }

  bool CRPSSeismicLabFramework::ComputeAutoSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
  {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     SeismicLabAPI::IrpsSLSpectrum* SelectedSpectrumObject = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(Data.spectrumModel.getValue()));

     if (NULL == SelectedSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedSpectrumObject->ComputeAutoSpectrumValue(Data,location, dFrequency, dTime, dValue);

     return returnValue;
 }  
  bool CRPSSeismicLabFramework::ComputeAutoSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
  {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     SeismicLabAPI::IrpsSLSpectrum* SelectedSpectrumObject = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(Data.spectrumModel.getValue()));

     if (NULL == SelectedSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedSpectrumObject->ComputeAutoSpectrumVectorF(Data, location, dTime, dVarVector, dValVector);

     return returnValue;
 }

  bool CRPSSeismicLabFramework::ComputeAutoSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
  {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     SeismicLabAPI::IrpsSLSpectrum* SelectedSpectrumObject = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(Data.spectrumModel.getValue()));

     if (NULL == SelectedSpectrumObject)
     {
         return false;
     }

     bool returnValue = SelectedSpectrumObject->ComputeAutoSpectrumVectorT(Data, location, dFrequency, dVarVector, dValVector);

     return returnValue;
 }

bool CRPSSeismicLabFramework::ComputeCrossCoherenceValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLCoherence* SelectedCoherenceObject = static_cast<SeismicLabAPI::IrpsSLCoherence*>(doc->getObject(Data.coherenceFunction.getValue()));

	if (NULL == SelectedCoherenceObject)
	{
        return false;
	}

    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, dValue);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeCrossCoherenceVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLCoherence* SelectedCoherenceObject = static_cast<SeismicLabAPI::IrpsSLCoherence*>(doc->getObject(Data.coherenceFunction.getValue()));

    if (NULL == SelectedCoherenceObject)
    {
        return false;
    }

    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeCrossCoherenceVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLCoherence* SelectedCoherenceObject = static_cast<SeismicLabAPI::IrpsSLCoherence*>(doc->getObject(Data.coherenceFunction.getValue()));

    if (NULL == SelectedCoherenceObject)
    {
        return false;
    }

    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceVectorT(Data,locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeCrossCoherenceMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLCoherence* SelectedCoherenceObject = static_cast<SeismicLabAPI::IrpsSLCoherence*>(doc->getObject(Data.coherenceFunction.getValue()));

    if (NULL == SelectedCoherenceObject)
    {
        return false;
    }

    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceMatrixPP(Data, dFrequency, dTime, dCoherenceMatrix);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeCrossCorrelationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLCorrelation* SelectedCorreObject = static_cast<SeismicLabAPI::IrpsSLCorrelation*>(doc->getObject(Data.correlationFunction.getValue()));

	if (NULL == SelectedCorreObject)
	{
        return false;
	}

    bool returnValue = SelectedCorreObject->ComputeCrossCorrelationValue(Data, locationJ, locationK, dTime, dValue);

    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeMeanAccelerationSpeedValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLMeanAcceleration* SelectedMeanObject = static_cast<SeismicLabAPI::IrpsSLMeanAcceleration*>(doc->getObject(Data.meanFunction.getValue()));

	if (NULL == SelectedMeanObject)
	{
        return false;
	}

    bool returnValue = SelectedMeanObject->ComputeMeanAccelerationValue(Data, location, dTime, dValue);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeModulationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLModulation* SelectedModulationObject = static_cast<SeismicLabAPI::IrpsSLModulation*>(doc->getObject(Data.modulationFunction.getValue()));

	if (NULL == SelectedModulationObject)
	{
        return false;
	}

    bool returnValue = SelectedModulationObject->ComputeModulationValue(Data, location, dTime, dValue);

    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeRandomValue(const SeismicLabAPI::SeismicLabSimulationData &Data, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLRandomness* SelectedRandomnessObject = static_cast<SeismicLabAPI::IrpsSLRandomness*>(doc->getObject(Data.randomnessProvider.getValue()));

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


bool CRPSSeismicLabFramework::ComputeCrossSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLSpectrum* SelectedSpectrumObject = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(Data.spectrumModel.getValue()));

	if (NULL == SelectedSpectrumObject)
	{
        return false;
	}

    bool returnValue = SelectedSpectrumObject->ComputeCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, dValue);

    return returnValue;
}


 bool CRPSSeismicLabFramework::ComputeFrequencyValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue)
 {
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     SeismicLabAPI::IrpsSLFrequencyDistribution* SelectedFrequencyDistributionObject = static_cast<SeismicLabAPI::IrpsSLFrequencyDistribution*>(doc->getObject(Data.frequencyDistribution.getValue()));

     if (NULL == SelectedFrequencyDistributionObject)
     {
         return false;
     }

     bool returnValue = SelectedFrequencyDistributionObject->ComputeFrequencyValue(Data, location, frequencyIndex, dValue);

     return returnValue;
 }

SeismicLabAPI::SeismicLabFeatureDescription* CRPSSeismicLabFramework::getSeismicLabFeatureDescription(const std::string& name)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return nullptr;
     }

     SeismicLabAPI::SeismicLabFeature* feature = static_cast<SeismicLabAPI::SeismicLabFeature*>(doc->getObject(name.c_str()));

     if (!feature)
     {
         return nullptr;
     }

     SeismicLabAPI::SeismicLabFeatureDescription* information = new SeismicLabAPI::SeismicLabFeatureDescription();

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

bool CRPSSeismicLabFramework::TableToolCompute(const SeismicLabAPI::SeismicLabSimulationData &Data, const mat &inputTable, mat &outputTable)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     SeismicLabAPI::IrpsSLTableTool* feature = static_cast<SeismicLabAPI::IrpsSLTableTool*>(doc->getObject(Data.tableTool.getValue()));

     if (!feature)
     {
         return false;
     }

     bool returnValue = feature->TableToolCompute(Data, inputTable, outputTable);

     return returnValue;
 }

bool CRPSSeismicLabFramework::MatrixToolCompute(const SeismicLabAPI::SeismicLabSimulationData &Data, const mat &inputMatrix, mat &outputMatrix)
{
      auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return false;
     }

     SeismicLabAPI::IrpsSLMatrixTool* feature = static_cast<SeismicLabAPI::IrpsSLMatrixTool*>(doc->getObject(Data.matrixTool.getValue()));

     if (!feature)
     {
         return false;
     }

     bool returnValue = feature->MatrixToolCompute(Data, inputMatrix, outputMatrix);

     return returnValue;
}

bool CRPSSeismicLabFramework::UserDefinedRPSObjectCompute(const SeismicLabAPI::SeismicLabSimulationData &Data, mat &dresult)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLUserDefinedRPSObject* SelectedUserDefinedRPSObject = static_cast<SeismicLabAPI::IrpsSLUserDefinedRPSObject*>(doc->getObject(Data.userDefinedRPSObject.getValue()));

	if (NULL == SelectedUserDefinedRPSObject)
	{
        return false;
	}

    bool returnValue = SelectedUserDefinedRPSObject->UserDefinedRPSObjectCompute(Data, dresult);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeCPDValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &x, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution* SelectedObject = static_cast<SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution*>(doc->getObject(Data.cumulativeProbabilityDistribution.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeCPDValue(Data, x, dValue);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputeCPDVectorX(const SeismicLabAPI::SeismicLabSimulationData &Data, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution* SelectedObject = static_cast<SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution*>(doc->getObject(Data.cumulativeProbabilityDistribution.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeCPDVectorX(Data, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeKurtosisValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLKurtosis* SelectedObject = static_cast<SeismicLabAPI::IrpsSLKurtosis*>(doc->getObject(Data.kurtosis.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeKurtosisValue(Data, location, dTime, dValue);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputeKurtosisVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLKurtosis* SelectedObject = static_cast<SeismicLabAPI::IrpsSLKurtosis*>(doc->getObject(Data.kurtosis.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeKurtosisVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputeKurtosisVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLKurtosis* SelectedObject = static_cast<SeismicLabAPI::IrpsSLKurtosis*>(doc->getObject(Data.kurtosis.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeKurtosisVectorT(Data, location, dVarVector,dValVector);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputePeakFactorValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLPeakFactor* SelectedObject = static_cast<SeismicLabAPI::IrpsSLPeakFactor*>(doc->getObject(Data.peakFactor.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePeakFactorValue(Data, location, dTime, dValue);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputePeakFactorVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLPeakFactor* SelectedObject = static_cast<SeismicLabAPI::IrpsSLPeakFactor*>(doc->getObject(Data.peakFactor.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePeakFactorVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputePeakFactorVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLPeakFactor* SelectedObject = static_cast<SeismicLabAPI::IrpsSLPeakFactor*>(doc->getObject(Data.peakFactor.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePeakFactorVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputePDFValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &x, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLProbabilityDensityFunction* SelectedObject = static_cast<SeismicLabAPI::IrpsSLProbabilityDensityFunction*>(doc->getObject(Data.probabilityDensityFunction.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePDFValue(Data, x, dValue);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputePDFVectorX(const SeismicLabAPI::SeismicLabSimulationData &Data, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLProbabilityDensityFunction* SelectedObject = static_cast<SeismicLabAPI::IrpsSLProbabilityDensityFunction*>(doc->getObject(Data.probabilityDensityFunction.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputePDFVectorX(Data, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeShearVelocityOfFlowValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLShearVelocityOfFlow* SelectedObject = static_cast<SeismicLabAPI::IrpsSLShearVelocityOfFlow*>(doc->getObject(Data.shearVelocityOfFlow.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeShearVelocityOfFlowValue(Data,location, dTime, dValue);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputeShearVelocityOfFlowVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLShearVelocityOfFlow* SelectedObject = static_cast<SeismicLabAPI::IrpsSLShearVelocityOfFlow*>(doc->getObject(Data.shearVelocityOfFlow.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeShearVelocityOfFlowVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeShearVelocityOfFlowVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLShearVelocityOfFlow* SelectedObject = static_cast<SeismicLabAPI::IrpsSLShearVelocityOfFlow*>(doc->getObject(Data.shearVelocityOfFlow.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeShearVelocityOfFlowVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeSkewnessValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLSkewness* SelectedObject = static_cast<SeismicLabAPI::IrpsSLSkewness*>(doc->getObject(Data.skewness.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeSkewnessValue(Data, location, dTime, dValue);

    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeSkewnessVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLSkewness* SelectedObject = static_cast<SeismicLabAPI::IrpsSLSkewness*>(doc->getObject(Data.skewness.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeSkewnessVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeSkewnessVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLSkewness* SelectedObject = static_cast<SeismicLabAPI::IrpsSLSkewness*>(doc->getObject(Data.skewness.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeSkewnessVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeStandardDeviationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLStandardDeviation* SelectedObject = static_cast<SeismicLabAPI::IrpsSLStandardDeviation*>(doc->getObject(Data.standardDeviation.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeStandardDeviationValue(Data, location, dTime, dValue);

    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeStandardDeviationVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLStandardDeviation* SelectedObject = static_cast<SeismicLabAPI::IrpsSLStandardDeviation*>(doc->getObject(Data.standardDeviation.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeStandardDeviationVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}


bool CRPSSeismicLabFramework::ComputeStandardDeviationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLStandardDeviation* SelectedObject = static_cast<SeismicLabAPI::IrpsSLStandardDeviation*>(doc->getObject(Data.standardDeviation.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeStandardDeviationVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeVarianceValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLVariance* SelectedObject = static_cast<SeismicLabAPI::IrpsSLVariance*>(doc->getObject(Data.variance.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeVarianceValue(Data, location, dTime, dValue);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputeVarianceVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLVariance* SelectedObject = static_cast<SeismicLabAPI::IrpsSLVariance*>(doc->getObject(Data.variance.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeVarianceVectorP(Data, dTime, dVarVector, dValVector);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputeVarianceVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLVariance* SelectedObject = static_cast<SeismicLabAPI::IrpsSLVariance*>(doc->getObject(Data.variance.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeVarianceVectorT(Data, location, dVarVector, dValVector);

    return returnValue;
}
bool CRPSSeismicLabFramework::ComputeWavePassageEffectValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLWavePassageEffect* SelectedObject = static_cast<SeismicLabAPI::IrpsSLWavePassageEffect*>(doc->getObject(Data.wavePassageEffect.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeWavePassageEffectValue(Data, locationJ, locationK, dFrequency, dTime, dValue);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeWavePassageEffectVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLWavePassageEffect* SelectedObject = static_cast<SeismicLabAPI::IrpsSLWavePassageEffect*>(doc->getObject(Data.wavePassageEffect.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeWavePassageEffectVectorF(Data, locationJ, locationK, dTime, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeWavePassageEffectVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLWavePassageEffect* SelectedObject = static_cast<SeismicLabAPI::IrpsSLWavePassageEffect*>(doc->getObject(Data.wavePassageEffect.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeWavePassageEffectVectorT(Data, locationJ, locationK, dFrequency, dVarVector, dValVector);

    return returnValue;
}

bool CRPSSeismicLabFramework::ComputeWavePassageEffectMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
    {
        return false;
    }

    SeismicLabAPI::IrpsSLWavePassageEffect* SelectedObject = static_cast<SeismicLabAPI::IrpsSLWavePassageEffect*>(doc->getObject(Data.wavePassageEffect.getValue()));

    if (NULL == SelectedObject)
    {
        return false;
    }

    bool returnValue = SelectedObject->ComputeWavePassageEffectMatrixPP(Data, dFrequency, dTime, dCoherenceMatrix);

    return returnValue;
}

int CRPSSeismicLabFramework::getLocationIndex(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d locationTobeFound)
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

    return 0;
}

std::string CRPSSeismicLabFramework::getCurrentDateTime()
{
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Convert to tm structure
    std::tm local_time;
    localtime_s(&local_time, &now_time);// Use localtime_s for safety (Windows)

    // Format the date and time into a string using strftime
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &local_time);

    return std::string(buffer);
}