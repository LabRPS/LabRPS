/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>          *
 *                         *
 *   This file is part of the LabRPS development system.      *
 *                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.          *
 *                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                *
 *                         *
 ***************************************************************************/

#include "PreCompiled.h"

#include <Base/Uuid.h>

#include "WindLabSimulation.h"
#include "WindlabUtils.h"
#include <Mod/WindLabAPI/App/WindLabFeatureDescription.h>
#include <Mod/WindLabAPI/App/RPSWindLabAPI.h>
#include <App/Application.h>
#include <App/Document.h>
#include <App/RPSpluginManager.h>
#include <Mod/WindLabAPI/App/WindLabFeatureCoherence.h>
#include <Mod/WindLabAPI/App/WindLabFeatureCorrelation.h>
#include <Mod/WindLabAPI/App/WindLabFeatureCumulativeProbabilityDistribution.h>
#include <Mod/WindLabAPI/App/WindLabFeatureFrequencyDistribution.h>
#include <Mod/WindLabAPI/App/WindLabFeatureGustFactor.h>
#include <Mod/WindLabAPI/App/WindLabFeatureKurtosis.h>
#include <Mod/WindLabAPI/App/WindLabFeatureLocationDistribution.h>
#include <Mod/WindLabAPI/App/WindLabFeatureMatrixTool.h>
#include <Mod/WindLabAPI/App/WindLabFeatureMeanWind.h>
#include <Mod/WindLabAPI/App/WindLabFeatureModulation.h>
#include <Mod/WindLabAPI/App/WindLabFeaturePSDDecompositionMethod.h>
#include <Mod/WindLabAPI/App/WindLabFeaturePeakFactor.h>
#include <Mod/WindLabAPI/App/WindLabFeatureProbabilityDensityFunction.h>
#include <Mod/WindLabAPI/App/WindLabFeatureRandomness.h>
#include <Mod/WindLabAPI/App/WindLabFeatureRoughness.h>
#include <Mod/WindLabAPI/App/WindLabFeatureShearVelocityOfFlow.h>
#include <Mod/WindLabAPI/App/WindLabFeatureSimulationMethod.h>
#include <Mod/WindLabAPI/App/WindLabFeatureSkewness.h>
#include <Mod/WindLabAPI/App/WindLabFeatureStandardDeviation.h>
#include <Mod/WindLabAPI/App/WindLabFeatureTableTool.h>
#include <Mod/WindLabAPI/App/WindLabFeatureTurbulenceIntensity.h>
#include <Mod/WindLabAPI/App/WindLabFeatureTurbulenceScale.h>
#include <Mod/WindLabAPI/App/WindLabFeatureUserDefinedRPSObject.h>
#include <Mod/WindLabAPI/App/WindLabFeatureVariance.h>
#include <Mod/WindLabAPI/App/WindLabFeatureWavePassageEffect.h>
#include <Mod/WindLabAPI/App/WindLabFeatureXSpectrum.h>
#include <Mod/WindLabAPI/App/WindLabFeatureYSpectrum.h>
#include <Mod/WindLabAPI/App/WindLabFeatureZSpectrum.h>
#include <Base/Console.h>
#include <Mod/WindLab/App/WindLabSimulationPy.h>
#include <App/DocumentObjectPy.h>
#include <App/FeaturePythonPyImp.h>

using namespace App;
using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::WindLabSimulation, App::Simulation)

WindLabSimulation::WindLabSimulation()
{
    _simuData = new WindLabAPI::WindLabSimuData();
   
    Base::Uuid id;
    ADD_PROPERTY_TYPE(Uid, (id), 0, App::Prop_None, "UUID of the simulation"); //not is use yet

    static const char* datagroup = "Basic Data";
    ADD_PROPERTY_TYPE(NumberOfSample, (1), datagroup, Prop_None,"This is the number of wind field sample in a simulation.");
    ADD_PROPERTY_TYPE(NumberOfTimeLags, (512), datagroup, Prop_None,"Number of time lags need for temporal correlation");
    ADD_PROPERTY_TYPE(Stationarity, (true), datagroup, Prop_None,"This specifies whether the simulated wind is stationary or not.");
    ADD_PROPERTY_TYPE(Gaussianity, (true), datagroup, Prop_None,"This specifies whether the simulated wind is gaussian or not.");
    ADD_PROPERTY_TYPE(ComparisonMode, (false), datagroup, Prop_None,"This specifies whether we are in comparison mode or not.");
    ADD_PROPERTY_TYPE(LargeScaleSimulationMode, (false), datagroup, Prop_None,"This specifies whether we are in large scale simulation mode or not.");
    ADD_PROPERTY_TYPE(IsSimulationSuccessful, (false), datagroup, Prop_None,"This specifies whether the simulation was successful or not.");
    ADD_PROPERTY_TYPE(IsInterruptionRequested, (false), datagroup, Prop_None,"This specifies whether the simulation has been interrupted or not.");
    ADD_PROPERTY_TYPE(UniformModulation, (true), datagroup, Prop_None,"This specifies whether a non stataionary wind is uniformly modulated or not.");

    static const char* locationgroup = "Location Distribution";
    ADD_PROPERTY_TYPE(NumberOfProcess, (3), locationgroup, App::Prop_None,"The number of simulation point which is the number of wind processes in a sample");
    ADD_PROPERTY_TYPE(LocationIndexJ, (1), locationgroup, Prop_None,"The index of the a given wind process in a wind field at a location J");
    ADD_PROPERTY_TYPE(LocationIndexK, (1), locationgroup, Prop_None,"The index of the a given wind process in a wind field at a location K");

    static const char* frequencygroup = "Frequency Discretization";
    ADD_PROPERTY_TYPE(NumberOfFrequency, (1024), frequencygroup, Prop_None,"The number of frequency increments");
    ADD_PROPERTY_TYPE(FrequencyIncrement, (0.0039), frequencygroup, Prop_None,"This is the frequency increment value");
    ADD_PROPERTY_TYPE(MinFrequency, (0.00), frequencygroup, Prop_None,"This is the minimum frequency value");
    ADD_PROPERTY_TYPE(MaxFrequency, (4.00), frequencygroup, Prop_None,"This is the maximum frequency value or the cutoff frequency");
    ADD_PROPERTY_TYPE(FrequencyIndex, (1), frequencygroup, Prop_None,"Index correponding to Kth frequency increment");

    static const char* timegroup = "Time Discretization";
    ADD_PROPERTY_TYPE(NumberOfTimeIncrements, (6144), timegroup, Prop_None,"This is the number of time increments");
    ADD_PROPERTY_TYPE(TimeIncrement, (0.25), timegroup, Prop_None,"This is the time increment value");
    ADD_PROPERTY_TYPE(MinTime, (0.00), timegroup, Prop_None, "This is the minimum time value");
    ADD_PROPERTY_TYPE(MaxTime, (1536.00), timegroup, Prop_None, "This is the maximum time value");
    ADD_PROPERTY_TYPE(TimeIndex, (1), timegroup, Prop_None,"Index correponding to Kth time increment");

    static const char* directiongroup = "Direction Discretization";
    ADD_PROPERTY_TYPE(NumberOfDirectionIncrements, (1000), directiongroup, Prop_None,"The number of direction increments");
    ADD_PROPERTY_TYPE(DirectionIncrement, (0.001), directiongroup, Prop_None,"This is the direction increment value");
    ADD_PROPERTY_TYPE(MinDirection, (0.00), directiongroup, Prop_None,"This is the minimum direction value");
    ADD_PROPERTY_TYPE(MaxDirection, (4.00), directiongroup, Prop_None,"This is the maximum direction value");
    ADD_PROPERTY_TYPE(DirectionIndex, (1), directiongroup, Prop_None,"Index correponding to Kth direction increment");

    static const char* waveLengthgroup = "Wave Length Discretization";
    ADD_PROPERTY_TYPE(NumberOfWaveLengthIncrements, (1000), waveLengthgroup, Prop_None,"The number of wave length increment");
    ADD_PROPERTY_TYPE(WaveLengthIncrement, (0.001), waveLengthgroup, Prop_None,"This is the wave length value");
    ADD_PROPERTY_TYPE(MinWaveLength, (0.00), waveLengthgroup, Prop_None,"This is the minimum wave length");
    ADD_PROPERTY_TYPE(MaxWaveLength, (4.00), waveLengthgroup, Prop_None,"This is the maximum wave length");
    ADD_PROPERTY_TYPE(WaveLengthIndex, (1), waveLengthgroup, Prop_None,"Index correponding to Kth wave length increment");

    static const char* featuregroup = "Windlab Features";
    static const char* someEnums[] = {"<None>", nullptr};

    ADD_PROPERTY_TYPE(SpatialDistribution, ((long int)0), featuregroup, Prop_None,"Active location distribution name");
    ADD_PROPERTY_TYPE(MeanFunction, ((long int)0), featuregroup, Prop_None,"Active mean wind profile name");
    ADD_PROPERTY_TYPE(AlongWindSpectrumModel, ((long int)0), featuregroup, Prop_None,"Active along wind spectrum model name");
    ADD_PROPERTY_TYPE(VerticalWindSpectrumModel, ((long int)0), featuregroup, Prop_None,"Active vertical wind spectrum model name");
    ADD_PROPERTY_TYPE(AcrossWindSpectrumModel, ((long int)0), featuregroup, Prop_None,"Active across wind spectrum model name");
    ADD_PROPERTY_TYPE(CoherenceFunction, ((long int)0), featuregroup, Prop_None,"Active coherence function name");
    ADD_PROPERTY_TYPE(SimulationMethod, ((long int)0), featuregroup, Prop_None,"Active simulation method name");
    ADD_PROPERTY_TYPE(FrequencyDistribution, ((long int)0), featuregroup, Prop_None,"Active frequency distribution name");
    ADD_PROPERTY_TYPE(SpectrumDecompositionMethod, ((long int)0), featuregroup, Prop_None,"Active psd decomposition method name");
    ADD_PROPERTY_TYPE(RandomnessProvider, ((long int)0), featuregroup, Prop_None,"Active randomness provider name");
    ADD_PROPERTY_TYPE(ModulationFunction, ((long int)0), featuregroup, Prop_None,"Active modulation function name");
    ADD_PROPERTY_TYPE(CorrelationFunction, ((long int)0), featuregroup, Prop_None,"Active correlation function name");
    ADD_PROPERTY_TYPE(TableTool, ((long int)0), featuregroup, Prop_None, "table tool name");
    ADD_PROPERTY_TYPE(MatrixTool, ((long int)0), featuregroup, Prop_None, "matrix name");
    ADD_PROPERTY_TYPE(UserDefinedRPSObject, ((long int)0), featuregroup, Prop_None,"user defined rps object name");
    ADD_PROPERTY_TYPE(CumulativeProbabilityDistribution, ((long int)0), featuregroup, Prop_None,  "Active CPD name");
    ADD_PROPERTY_TYPE(GustFactor, ((long int)0), featuregroup, Prop_None,"Active gust factor name");
    ADD_PROPERTY_TYPE(Kurtosis, ((long int)0), featuregroup, Prop_None, "Active kurtosis name");
    ADD_PROPERTY_TYPE(PeakFactor, ((long int)0), featuregroup, Prop_None,"Active peak factor name");
    ADD_PROPERTY_TYPE(ProbabilityDensityFunction, ((long int)0), featuregroup, Prop_None,"Active PDF name");
    ADD_PROPERTY_TYPE(Roughness, ((long int)0), featuregroup, Prop_None, "Active roughness name");
    ADD_PROPERTY_TYPE(ShearVelocityOfFlow, ((long int)0), featuregroup, Prop_None,"Active shear velocity name");
    ADD_PROPERTY_TYPE(Skewness, ((long int)0), featuregroup, Prop_None, "Active skewness name");
    ADD_PROPERTY_TYPE(StandardDeviation, ((long int)0), featuregroup, Prop_None,"Active standard deviation name");
    ADD_PROPERTY_TYPE(TurbulenceIntensity, ((long int)0), featuregroup, Prop_None,"Active turbulence intensity name");
    ADD_PROPERTY_TYPE(TurbulenceScale, ((long int)0), featuregroup, Prop_None,"Active turbulence scale name");
    ADD_PROPERTY_TYPE(Variance, ((long int)0), featuregroup, Prop_None, "Active variance name");
    ADD_PROPERTY_TYPE(WavePassageEffect, ((long int)0), featuregroup, Prop_None,"Active wave passage name");

    ADD_PROPERTY_TYPE(NumberOfIncrementOfVariableX, (101), "Variable X", Prop_None, "The number of increments for the variable x");
	ADD_PROPERTY_TYPE(IndexOfVariableX, (1), "Variable X", Prop_None, "This current index of the variable x.");
	ADD_PROPERTY_TYPE(IncrementOfVariableX, (0.1), "Variable X", Prop_None, "This is the variable x increment value");
	ADD_PROPERTY_TYPE(MinVariableX, (-5.00), "Variable X", Prop_None, "This is the minimum x variable value");

    ADD_PROPERTY_TYPE(Phenomenon, ("Wind Velocity"), 0, Prop_ReadOnly, "The random phenonenon name");
    ADD_PROPERTY_TYPE(WorkingDirectoryPath, (Application::getHomePath()), 0, Prop_None, "The working directory path.");


    SpatialDistribution.setEnums(someEnums);
    ShearVelocity.setEnums(someEnums);
    MeanFunction.setEnums(someEnums);
    AlongWindSpectrumModel.setEnums(someEnums);
    VerticalWindSpectrumModel.setEnums(someEnums);
    AcrossWindSpectrumModel.setEnums(someEnums);
    CoherenceFunction.setEnums(someEnums);
    SimulationMethod.setEnums(someEnums);
    FrequencyDistribution.setEnums(someEnums);
    SpectrumDecompositionMethod.setEnums(someEnums);
    RandomnessProvider.setEnums(someEnums);
    ModulationFunction.setEnums(someEnums);
    CorrelationFunction.setEnums(someEnums);
    VarianceFunction.setEnums(someEnums);
    TableTool.setEnums(someEnums);
    MatrixTool.setEnums(someEnums);
    UserDefinedRPSObject.setEnums(someEnums);
    CumulativeProbabilityDistribution.setEnums(someEnums);
    GustFactor.setEnums(someEnums);
    Kurtosis.setEnums(someEnums);
    PeakFactor.setEnums(someEnums);
    ProbabilityDensityFunction.setEnums(someEnums);
    Roughness.setEnums(someEnums);
    ShearVelocityOfFlow.setEnums(someEnums);
    Skewness.setEnums(someEnums);
    StandardDeviation.setEnums(someEnums);
    TurbulenceIntensity.setEnums(someEnums);
    TurbulenceScale.setEnums(someEnums);
    Variance.setEnums(someEnums);
    WavePassageEffect.setEnums(someEnums);

    static const char* directions[] = {"Along wind", "Across wind", "Vertical wind", nullptr};
    ADD_PROPERTY_TYPE(WindDirection, ((long int)0), datagroup, Prop_None, "The wind direction");
    WindDirection.setEnums(directions);
}

WindLabSimulation::~WindLabSimulation() { delete _simuData; }

void WindLabSimulation::handleChangedPropertyName(Base::XMLReader& reader, const char* TypeName,            const char* PropName)
{
    Base::Type type = Base::Type::fromName(TypeName);
    App::DocumentObjectGroup::handleChangedPropertyName(reader, TypeName, PropName);
}

void WindLabSimulation::updateSimulationData()
{
    _simuData->numberOfSpatialPosition.setValue(this->NumberOfProcess.getValue());
    _simuData->numberOfFrequency.setValue(this->NumberOfFrequency.getValue());
    _simuData->numberOfSample.setValue(this->NumberOfSample.getValue());
    _simuData->numberOfTimeIncrements.setValue(this->NumberOfTimeIncrements.getValue());
    _simuData->locationJ.setValue(this->LocationIndexJ.getValue());
    _simuData->locationK.setValue(this->LocationIndexK.getValue());
    _simuData->frequencyIndex.setValue(this->FrequencyIndex.getValue());
    _simuData->directionIndex.setValue(this->DirectionIndex.getValue());
    _simuData->timeIndex.setValue(this->TimeIndex.getValue());
    _simuData->numberOfTimeLags.setValue(this->NumberOfTimeLags.getValue());
    _simuData->numberOfWaveLengthIncrements.setValue(this->NumberOfWaveLengthIncrements.getValue());
    _simuData->numberOfDirectionIncrements.setValue(this->NumberOfDirectionIncrements.getValue());
    _simuData->workingDirPath.setValue(this->WorkingDirectoryPath.getValue());
    _simuData->waveLengthIndex.setValue(this->WaveLengthIndex.getValue());
    _simuData->stationarity.setValue(this->Stationarity.getValue());
    _simuData->gaussianity.setValue(this->Gaussianity.getValue());
    _simuData->comparisonMode.setValue(this->ComparisonMode.getValue());
    _simuData->largeScaleSimulationMode.setValue(this->LargeScaleSimulationMode.getValue());
    _simuData->isSimulationSuccessful.setValue(this->IsSimulationSuccessful.getValue());
    _simuData->isInterruptionRequested.setValue(this->IsInterruptionRequested.getValue());
    _simuData->uniformModulation.setValue(this->UniformModulation.getValue());
    _simuData->minTime.setValue(this->MinTime.getQuantityValue().getValueAs(Base::Quantity::Second));
    _simuData->maxTime.setValue(this->MaxTime.getQuantityValue().getValueAs(Base::Quantity::Second));
    _simuData->timeIncrement.setValue(this->TimeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second));
    _simuData->minFrequency.setValue(this->MinFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond));
    _simuData->frequencyIncrement.setValue(this->FrequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond));
    _simuData->maxFrequency.setValue(this->MaxFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond));
    _simuData->minWaveLength.setValue(this->MinWaveLength.getValue());
    _simuData->maxWaveLength.setValue(this->MaxWaveLength.getValue());
    _simuData->waveLengthIncrement.setValue(this->WaveLengthIncrement.getValue());
    _simuData->minDirection.setValue(this->MinDirection.getQuantityValue().getValueAs(Base::Quantity::Degree));
    _simuData->maxDirection.setValue(this->MaxDirection.getQuantityValue().getValueAs(Base::Quantity::Degree));
    _simuData->directionIncrement.setValue(this->DirectionIncrement.getQuantityValue().getValueAs(Base::Quantity::Degree));
    _simuData->spatialDistribution.setValue(this->SpatialDistribution.getValueAsString());
    _simuData->shearVelocity.setValue(this->ShearVelocity.getValueAsString());
    _simuData->meanFunction.setValue(this->MeanFunction.getValueAsString());
    _simuData->alongWindSpectrumModel.setValue(this->AlongWindSpectrumModel.getValueAsString());
    _simuData->verticalWindSpectrumModel.setValue(this->VerticalWindSpectrumModel.getValueAsString());
    _simuData->acrossWindSpectrumModel.setValue(this->AcrossWindSpectrumModel.getValueAsString());
    _simuData->coherenceFunction.setValue(this->CoherenceFunction.getValueAsString());
    _simuData->simulationMethod.setValue(this->SimulationMethod.getValueAsString());
    _simuData->frequencyDistribution.setValue(this->FrequencyDistribution.getValueAsString());
    _simuData->cpsdDecompositionMethod.setValue(this->SpectrumDecompositionMethod.getValueAsString());
    _simuData->randomnessProvider.setValue(this->RandomnessProvider.getValueAsString());
    _simuData->modulationFunction.setValue(this->ModulationFunction.getValueAsString());
    _simuData->correlationFunction.setValue(this->CorrelationFunction.getValueAsString());
    _simuData->varianceFunction.setValue(this->VarianceFunction.getValueAsString());
    _simuData->tableTool.setValue(this->TableTool.getValueAsString());
    _simuData->matrixTool.setValue(this->MatrixTool.getValueAsString());
    _simuData->userDefinedRPSObject.setValue(this->UserDefinedRPSObject.getValueAsString());
    _simuData->cumulativeProbabilityDistribution.setValue(this->CumulativeProbabilityDistribution.getValueAsString());
    _simuData->gustFactor.setValue(this->GustFactor.getValueAsString());
    _simuData->kurtosis.setValue(this->Kurtosis.getValueAsString());
    _simuData->peakFactor.setValue(this->PeakFactor.getValueAsString());
    _simuData->probabilityDensityFunction.setValue(this->ProbabilityDensityFunction.getValueAsString());
    _simuData->roughness.setValue(this->Roughness.getValueAsString());
    _simuData->shearVelocityOfFlow.setValue(this->ShearVelocityOfFlow.getValueAsString());
    _simuData->skewness.setValue(this->Skewness.getValueAsString());
    _simuData->standardDeviation.setValue(this->StandardDeviation.getValueAsString());
    _simuData->turbulenceIntensity.setValue(this->TurbulenceIntensity.getValueAsString());
    _simuData->turbulenceScale.setValue(this->TurbulenceScale.getValueAsString());
    _simuData->variance.setValue(this->Variance.getValueAsString());
    _simuData->wavePassageEffect.setValue(this->WavePassageEffect.getValueAsString());
    _simuData->WindDirection.setValue(this->WindDirection.getValue());
    _simuData->numberOfIncrementOfVariableX.setValue(this->NumberOfIncrementOfVariableX.getValue());
    _simuData->indexOfVariableX.setValue(this->IndexOfVariableX.getValue());
    _simuData->incrementOfVariableX.setValue(this->IncrementOfVariableX.getValue());
    _simuData->minVariableX.setValue(this->MinVariableX.getValue());
}

bool WindLabSimulation::run() { return false; }

bool WindLabSimulation::stop() { return false; }

std::string WindLabSimulation::getPhenomenonName() const
{
    return WindLab::WindLabUtils::rpsPhenomenonWindVelocity.toUtf8().constData();
}

std::string WindLabSimulation::workbenchName() const { return "WindLab"; }

void WindLabSimulation::setSimulationData(WindLabAPI::WindLabSimuData* simuData)
{
    _simuData = simuData;
}

WindLabAPI::WindLabSimuData* WindLabSimulation::getSimulationData() const { return _simuData; }

void WindLabSimulation::windLabFeatureInitalSetting(QString group, QString currentSelected)
{
    if (!_simuData)
        return;

    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return;

    if (group == WindLab::WindLabUtils::objGroupCoherenceFunction) {
        WindLabAPI::IrpsWLCoherence* activefeature = static_cast<WindLabAPI::IrpsWLCoherence*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);

    }
    else if (group == WindLab::WindLabUtils::objGroupCorrelationFunction) {
        WindLabAPI::IrpsWLCorrelation* activefeature = static_cast<WindLabAPI::IrpsWLCorrelation*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupCumulativeProbabilityDistribution) {
        WindLabAPI::IrpsWLCumulativeProbabilityDistribution* activefeature =
    static_cast<WindLabAPI::IrpsWLCumulativeProbabilityDistribution*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupFrequencyDistribution) {
        WindLabAPI::IrpsWLFrequencyDistribution* activefeature =
    static_cast<WindLabAPI::IrpsWLFrequencyDistribution*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupGustFactor) {
        WindLabAPI::IrpsWLGustFactor* activefeature = static_cast<WindLabAPI::IrpsWLGustFactor*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupKurtosis) {
        WindLabAPI::IrpsWLKurtosis* activefeature = static_cast<WindLabAPI::IrpsWLKurtosis*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupLocationDistribution) {
        WindLabAPI::IrpsWLLocationDistribution* activefeature =
    static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupMatrixTool) {
        WindLabAPI::IrpsWLMatrixTool* activefeature = static_cast<WindLabAPI::IrpsWLMatrixTool*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupMeanWindProfile) {
        WindLabAPI::IrpsWLMean* activefeature = static_cast<WindLabAPI::IrpsWLMean*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupModulationFunction) {
        WindLabAPI::IrpsWLModulation* activefeature = static_cast<WindLabAPI::IrpsWLModulation*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupPeakFactor) {
        WindLabAPI::IrpsWLPeakFactor* activefeature = static_cast<WindLabAPI::IrpsWLPeakFactor*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupProbabilityDensityFunction) {
        WindLabAPI::IrpsWLProbabilityDensityFunction* activefeature =
    static_cast<WindLabAPI::IrpsWLProbabilityDensityFunction*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupSpectrumDecompositionMethod) {
        WindLabAPI::IrpsWLPSDdecompositionMethod* activefeature =
    static_cast<WindLabAPI::IrpsWLPSDdecompositionMethod*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupRandomnessProvider) {
        WindLabAPI::IrpsWLRandomness* activefeature = static_cast<WindLabAPI::IrpsWLRandomness*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupRoughness) {
        WindLabAPI::IrpsWLRoughness* activefeature = static_cast<WindLabAPI::IrpsWLRoughness*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupShearVelocityOfFlow) {
        WindLabAPI::IrpsWLShearVelocityOfFlow* activefeature =
    static_cast<WindLabAPI::IrpsWLShearVelocityOfFlow*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupSimulationMethod) {
        WindLabAPI::IrpsWLSimuMethod* activefeature = static_cast<WindLabAPI::IrpsWLSimuMethod*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupSimulationMethod) {
        WindLabAPI::IrpsWLSkewness* activefeature = static_cast<WindLabAPI::IrpsWLSkewness*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupStandardDeviation) {
        WindLabAPI::IrpsWLStandardDeviation* activefeature =
    static_cast<WindLabAPI::IrpsWLStandardDeviation*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupTableTool) {
        WindLabAPI::IrpsWLTableTool* activefeature = static_cast<WindLabAPI::IrpsWLTableTool*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceIntensity) {
        WindLabAPI::IrpsWLTurbulenceIntensity* activefeature =
    static_cast<WindLabAPI::IrpsWLTurbulenceIntensity*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceScale) {
        WindLabAPI::IrpsWLTurbulenceScale* activefeature =
    static_cast<WindLabAPI::IrpsWLTurbulenceScale*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupUserDefinedRPSObject) {
        WindLabAPI::IrpsWLUserDefinedRPSObject* activefeature =
    static_cast<WindLabAPI::IrpsWLUserDefinedRPSObject*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupVariance) {
        WindLabAPI::IrpsWLVariance* activefeature = static_cast<WindLabAPI::IrpsWLVariance*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupWavePassageEffect) {
        WindLabAPI::IrpsWLWavePassageEffect* activefeature =
    static_cast<WindLabAPI::IrpsWLWavePassageEffect*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupAlongWindSpectrum) {
        WindLabAPI::IrpsWLXSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLXSpectrum*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupAcrossWindSpectrum) {
        WindLabAPI::IrpsWLYSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLYSpectrum*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == WindLab::WindLabUtils::objGroupVerticalWindSpectrum) {
        WindLabAPI::IrpsWLZSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLZSpectrum*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
}

QStringList WindLabSimulation::findAllPluggedWindLabFeatures(QString group)
{
    QStringList theList;
    theList.append(QString::fromLatin1("<None>"));
    if (group == WindLab::WindLabUtils::objGroupLocationDistribution) {
        typedef IrpsWLLocationDistribution* (*CreateLocDistrCallback)();
        std::map<const std::string, CreateLocDistrCallback>::iterator locIt;
        for (locIt = CrpsLocationDistributionFactory::GetObjectNamesMap().begin();
     locIt != CrpsLocationDistributionFactory::GetObjectNamesMap().end(); ++locIt) {
    theList.append(QString::fromUtf8(locIt->first.c_str()));
        }
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupMeanWindProfile) {
        typedef IrpsWLMean* (*CreateMeanCallback)();
        std::map<const std::string, CreateMeanCallback>::iterator meanIt;
        for (meanIt = CrpsMeanFactory::GetObjectNamesMap().begin();
     meanIt != CrpsMeanFactory::GetObjectNamesMap().end(); ++meanIt) {
    theList.append(QString::fromUtf8(meanIt->first.c_str()));
        }
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupAlongWindSpectrum) {
        typedef IrpsWLXSpectrum* (*CreateXSpectrumCallback)();
        std::map<const std::string, CreateXSpectrumCallback>::iterator psdIt;
        for (psdIt = CrpsXSpectrumFactory::GetObjectNamesMap().begin();
     psdIt != CrpsXSpectrumFactory::GetObjectNamesMap().end(); ++psdIt) {
    theList.append(QString::fromUtf8(psdIt->first.c_str()));
        }
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupAcrossWindSpectrum) {
        typedef IrpsWLYSpectrum* (*CreateYSpectrumCallback)();
        std::map<const std::string, CreateYSpectrumCallback>::iterator psdIt;
        for (psdIt = CrpsYSpectrumFactory::GetObjectNamesMap().begin();
     psdIt != CrpsYSpectrumFactory::GetObjectNamesMap().end(); ++psdIt) {
    theList.append(QString::fromUtf8(psdIt->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupVerticalWindSpectrum) {
        typedef IrpsWLZSpectrum* (*CreateZSpectrumCallback)();
        std::map<const std::string, CreateZSpectrumCallback>::iterator psdIt;
        for (psdIt = CrpsZSpectrumFactory::GetObjectNamesMap().begin();
     psdIt != CrpsZSpectrumFactory::GetObjectNamesMap().end(); ++psdIt) {
    theList.append(QString::fromUtf8(psdIt->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupSpectrumDecompositionMethod) {

        typedef IrpsWLPSDdecompositionMethod* (*CreatePSDdecomMethodCallback)();
        std::map<const std::string, CreatePSDdecomMethodCallback>::iterator psdDecIt;
        for (psdDecIt = CrpsPSDdecomMethodFactory::GetObjectNamesMap().begin();
     psdDecIt != CrpsPSDdecomMethodFactory::GetObjectNamesMap().end(); ++psdDecIt) {
    theList.append(QString::fromUtf8(psdDecIt->first.c_str()));
        }
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupCoherenceFunction) {
        typedef IrpsWLCoherence* (*CreateCoherenceCallback)();
        std::map<const std::string, CreateCoherenceCallback>::iterator cohIt;
        for (cohIt = CrpsCoherenceFactory::GetObjectNamesMap().begin();
     cohIt != CrpsCoherenceFactory::GetObjectNamesMap().end(); ++cohIt) {
    theList.append(QString::fromUtf8(cohIt->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupSimulationMethod) {
        typedef IrpsWLSimuMethod* (*CreateSimuMethodCallback)();
        std::map<const std::string, CreateSimuMethodCallback>::iterator simuMethIt;
        for (simuMethIt = CrpsSimuMethodFactory::GetObjectNamesMap().begin();
     simuMethIt != CrpsSimuMethodFactory::GetObjectNamesMap().end(); ++simuMethIt) {
    theList.append(QString::fromUtf8(simuMethIt->first.c_str()));
        }
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupFrequencyDistribution) {
        typedef IrpsWLFrequencyDistribution* (*CreateFrequencyDistributionCallback)();
        std::map<const std::string, CreateFrequencyDistributionCallback>::iterator freqDistrIt;
        for (freqDistrIt = CrpsFrequencyDistributionFactory::GetObjectNamesMap().begin();
     freqDistrIt != CrpsFrequencyDistributionFactory::GetObjectNamesMap().end();
     ++freqDistrIt) {
    theList.append(QString::fromUtf8(freqDistrIt->first.c_str()));
        }
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupRandomnessProvider) {

        typedef IrpsWLRandomness* (*CreateRandomnessCallback)();
        std::map<const std::string, CreateRandomnessCallback>::iterator randIt;
        for (randIt = CrpsRandomnessFactory::GetObjectNamesMap().begin();
     randIt != CrpsRandomnessFactory::GetObjectNamesMap().end(); ++randIt) {
    theList.append(QString::fromUtf8(randIt->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupModulationFunction) {

        typedef IrpsWLModulation* (*CreateModulationCallback)();
        std::map<const std::string, CreateModulationCallback>::iterator cohIt;
        for (cohIt = CrpsModulationFactory::GetObjectNamesMap().begin();
     cohIt != CrpsModulationFactory::GetObjectNamesMap().end(); ++cohIt) {
    theList.append(QString::fromUtf8(cohIt->first.c_str()));
        }
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupCorrelationFunction) {

        typedef IrpsWLCorrelation* (*CreateCorrelationCallback)();
        std::map<const std::string, CreateCorrelationCallback>::iterator corrIt;
        for (corrIt = CrpsCorrelationFactory::GetObjectNamesMap().begin();
     corrIt != CrpsCorrelationFactory::GetObjectNamesMap().end(); ++corrIt) {
    theList.append(QString::fromUtf8(corrIt->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupTableTool) {

        typedef IrpsWLTableTool* (*CreateTableToolCallback)();
        std::map<const std::string, CreateTableToolCallback>::iterator it;
        for (it = CrpsTableToolFactory::GetObjectNamesMap().begin();
     it != CrpsTableToolFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupMatrixTool) {

        typedef IrpsWLMatrixTool* (*CreateMatrixToolCallback)();
        std::map<const std::string, CreateMatrixToolCallback>::iterator it;
        for (it = CrpsMatrixToolFactory::GetObjectNamesMap().begin();
     it != CrpsMatrixToolFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupCumulativeProbabilityDistribution) {

        typedef IrpsWLCumulativeProbabilityDistribution* (
    *CreateCumulativeProbabilityDistributionCallback)();
        std::map<const std::string, CreateCumulativeProbabilityDistributionCallback>::iterator it;
        for (it = CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().begin();
     it != CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupGustFactor) {

        typedef IrpsWLGustFactor* (*CreateGustFactorCallback)();
        std::map<const std::string, CreateGustFactorCallback>::iterator it;
        for (it = CrpsGustFactorFactory::GetObjectNamesMap().begin();
     it != CrpsGustFactorFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupKurtosis) {

        typedef IrpsWLKurtosis* (*CreateKurtosisCallback)();
        std::map<const std::string, CreateKurtosisCallback>::iterator it;
        for (it = CrpsKurtosisFactory::GetObjectNamesMap().begin();
     it != CrpsKurtosisFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupPeakFactor) {

        typedef IrpsWLPeakFactor* (*CreatePeakFactorCallback)();
        std::map<const std::string, CreatePeakFactorCallback>::iterator it;
        for (it = CrpsPeakFactorFactory::GetObjectNamesMap().begin();
     it != CrpsPeakFactorFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupProbabilityDensityFunction) {

        typedef IrpsWLProbabilityDensityFunction* (*CreateProbabilityDensityFunctionCallback)();
        std::map<const std::string, CreateProbabilityDensityFunctionCallback>::iterator it;
        for (it = CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().begin();
     it != CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupRoughness) {

        typedef IrpsWLRoughness* (*CreateRoughnessCallback)();
        std::map<const std::string, CreateRoughnessCallback>::iterator it;
        for (it = CrpsRoughnessFactory::GetObjectNamesMap().begin();
     it != CrpsRoughnessFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupShearVelocityOfFlow) {

        typedef IrpsWLShearVelocityOfFlow* (*CreateShearVelocityOfFlowCallback)();
        std::map<const std::string, CreateShearVelocityOfFlowCallback>::iterator it;
        for (it = CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().begin();
     it != CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupSkewness) {

        typedef IrpsWLSkewness* (*CreateSkewnessCallback)();
        std::map<const std::string, CreateSkewnessCallback>::iterator it;
        for (it = CrpsSkewnessFactory::GetObjectNamesMap().begin();
     it != CrpsSkewnessFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupStandardDeviation) {

        typedef IrpsWLStandardDeviation* (*CreateStandardDeviationCallback)();
        std::map<const std::string, CreateStandardDeviationCallback>::iterator it;
        for (it = CrpsStandardDeviationFactory::GetObjectNamesMap().begin();
     it != CrpsStandardDeviationFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceIntensity) {

        typedef IrpsWLTurbulenceIntensity* (*CreateTurbulenceIntensityCallback)();
        std::map<const std::string, CreateTurbulenceIntensityCallback>::iterator it;
        for (it = CrpsTurbulenceIntensityFactory::GetObjectNamesMap().begin();
     it != CrpsTurbulenceIntensityFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceScale) {

        typedef IrpsWLTurbulenceScale* (*CreateTurbulenceScaleCallback)();
        std::map<const std::string, CreateTurbulenceScaleCallback>::iterator it;
        for (it = CrpsTurbulenceScaleFactory::GetObjectNamesMap().begin();
     it != CrpsTurbulenceScaleFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupVariance) {

        typedef IrpsWLVariance* (*CreateVarianceCallback)();
        std::map<const std::string, CreateVarianceCallback>::iterator it;
        for (it = CrpsVarianceFactory::GetObjectNamesMap().begin();
     it != CrpsVarianceFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupWavePassageEffect) {

        typedef IrpsWLWavePassageEffect* (*CreateWavePassageEffectCallback)();
        std::map<const std::string, CreateWavePassageEffectCallback>::iterator it;
        for (it = CrpsWavePassageEffectFactory::GetObjectNamesMap().begin();
     it != CrpsWavePassageEffectFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupUserDefinedRPSObject) {

        typedef IrpsWLUserDefinedRPSObject* (*CreateUserDefinedRPSObjectCallback)();
        std::map<const std::string, CreateUserDefinedRPSObjectCallback>::iterator it;
        for (it = CrpsUserDefinedRPSObjectFactory::GetObjectNamesMap().begin();
     it != CrpsUserDefinedRPSObjectFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }

    return theList;
}

QStringList WindLabSimulation::findAllFeatureMethods(QString group)
{
    QStringList theList;
    theList.append(QString::fromLatin1("<None>"));
    if (group == WindLab::WindLabUtils::objGroupLocationDistribution) {
        theList.append(WindLab::WindLabUtils::ComputeLocationCoordinateMatrixP3);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupMeanWindProfile) {
        theList.append(WindLab::WindLabUtils::ComputeMeanWindSpeedValue);
        theList.append(WindLab::WindLabUtils::ComputeMeanWindSpeedVectorP);
        theList.append(WindLab::WindLabUtils::ComputeMeanWindSpeedVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupAlongWindSpectrum) {
        theList.append(WindLab::WindLabUtils::ComputeXCrossSpectrumValue);
        theList.append(WindLab::WindLabUtils::ComputeXCrossSpectrumVectorF);
        theList.append(WindLab::WindLabUtils::ComputeXCrossSpectrumVectorT);
        theList.append(WindLab::WindLabUtils::ComputeXCrossSpectrumMatrixPP);
        theList.append(WindLab::WindLabUtils::ComputeXAutoSpectrumValue);
        theList.append(WindLab::WindLabUtils::ComputeXAutoSpectrumVectorF);
        theList.append(WindLab::WindLabUtils::ComputeXAutoSpectrumVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupAcrossWindSpectrum) {
        theList.append(WindLab::WindLabUtils::ComputeYCrossSpectrumValue);
        theList.append(WindLab::WindLabUtils::ComputeYCrossSpectrumVectorF);
        theList.append(WindLab::WindLabUtils::ComputeYCrossSpectrumVectorT);
        theList.append(WindLab::WindLabUtils::ComputeYCrossSpectrumMatrixPP);
        theList.append(WindLab::WindLabUtils::ComputeYAutoSpectrumValue);
        theList.append(WindLab::WindLabUtils::ComputeYAutoSpectrumVectorF);
        theList.append(WindLab::WindLabUtils::ComputeYAutoSpectrumVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupVerticalWindSpectrum) {
        theList.append(WindLab::WindLabUtils::ComputeZCrossSpectrumValue);
        theList.append(WindLab::WindLabUtils::ComputeZCrossSpectrumVectorF);
        theList.append(WindLab::WindLabUtils::ComputeZCrossSpectrumVectorT);
        theList.append(WindLab::WindLabUtils::ComputeZCrossSpectrumMatrixPP);
        theList.append(WindLab::WindLabUtils::ComputeZAutoSpectrumValue);
        theList.append(WindLab::WindLabUtils::ComputeZAutoSpectrumVectorF);
        theList.append(WindLab::WindLabUtils::ComputeZAutoSpectrumVectorT);

        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupSpectrumDecompositionMethod) {

        theList.append(WindLab::WindLabUtils::ComputeDecomposedPSDValue);
        theList.append(WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumVectorF);
        theList.append(WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumVectorT);
        theList.append(WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumMatrixPP);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupCoherenceFunction) {
        theList.append(WindLab::WindLabUtils::ComputeCrossCoherenceValue);
        theList.append(WindLab::WindLabUtils::ComputeCrossCoherenceVectorF);
        theList.append(WindLab::WindLabUtils::ComputeCrossCoherenceVectorT);
        theList.append(WindLab::WindLabUtils::ComputeCrossCoherenceMatrixPP);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupSimulationMethod) {
        theList.append(WindLab::WindLabUtils::Simulate);
        theList.append(WindLab::WindLabUtils::SimulateInLargeScaleMode);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupFrequencyDistribution) {
        theList.append(WindLab::WindLabUtils::ComputeFrequencyValue);
        theList.append(WindLab::WindLabUtils::ComputeFrequenciesVectorF);
        theList.append(WindLab::WindLabUtils::ComputeFrequenciesMatrixFP);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupRandomnessProvider) {
        theList.append(WindLab::WindLabUtils::ComputeRandomValue);
        theList.append(WindLab::WindLabUtils::GenerateRandomMatrixFP);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupModulationFunction) {
        theList.append(WindLab::WindLabUtils::ComputeModulationValue);
        theList.append(WindLab::WindLabUtils::ComputeModulationVectorP);
        theList.append(WindLab::WindLabUtils::ComputeModulationVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupCorrelationFunction) {
        theList.append(WindLab::WindLabUtils::ComputeCrossCorrelationValue);
        theList.append(WindLab::WindLabUtils::ComputeCrossCorrelationVectorT);
        theList.append(WindLab::WindLabUtils::ComputeCrossCorrelationMatrixPP);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupTableTool) {
        theList.append(WindLab::WindLabUtils::TableToolCompute);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupMatrixTool) {
        theList.append(WindLab::WindLabUtils::MatrixToolCompute);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupCumulativeProbabilityDistribution) {
        theList.append(WindLab::WindLabUtils::ComputeCPDValue);
        theList.append(WindLab::WindLabUtils::ComputeCPDVectorX);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupGustFactor) {
        theList.append(WindLab::WindLabUtils::ComputeGustFactorValue);
        theList.append(WindLab::WindLabUtils::ComputeGustFactorVectorP);
        theList.append(WindLab::WindLabUtils::ComputeGustFactorVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupKurtosis) {
        theList.append(WindLab::WindLabUtils::ComputeKurtosisValue);
        theList.append(WindLab::WindLabUtils::ComputeKurtosisVectorP);
        theList.append(WindLab::WindLabUtils::ComputeKurtosisVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupPeakFactor) {
        theList.append(WindLab::WindLabUtils::ComputePeakFactorValue);
        theList.append(WindLab::WindLabUtils::ComputePeakFactorVectorP);
        theList.append(WindLab::WindLabUtils::ComputePeakFactorVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupProbabilityDensityFunction) {
        theList.append(WindLab::WindLabUtils::ComputePDFValue);
        theList.append(WindLab::WindLabUtils::ComputePDFVectorX);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupRoughness) {
        theList.append(WindLab::WindLabUtils::ComputeRoughnessValue);
        theList.append(WindLab::WindLabUtils::ComputeRoughnessVectorP);
        theList.append(WindLab::WindLabUtils::ComputeRoughnessVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupShearVelocityOfFlow) {
        theList.append(WindLab::WindLabUtils::ComputeShearVelocityOfFlowValue);
        theList.append(WindLab::WindLabUtils::ComputeShearVelocityOfFlowVectorP);
        theList.append(WindLab::WindLabUtils::ComputeShearVelocityOfFlowVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupSkewness) {
        theList.append(WindLab::WindLabUtils::ComputeSkewnessValue);
        theList.append(WindLab::WindLabUtils::ComputeSkewnessVectorP);
        theList.append(WindLab::WindLabUtils::ComputeSkewnessVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupStandardDeviation) {
        theList.append(WindLab::WindLabUtils::ComputeStandardDeviationValue);
        theList.append(WindLab::WindLabUtils::ComputeStandardDeviationVectorP);
        theList.append(WindLab::WindLabUtils::ComputeStandardDeviationVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceIntensity) {
        theList.append(WindLab::WindLabUtils::ComputeTurbulenceIntensityValue);
        theList.append(WindLab::WindLabUtils::ComputeTurbulenceIntensityVectorP);
        theList.append(WindLab::WindLabUtils::ComputeTurbulenceIntensityVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceScale) {
        theList.append(WindLab::WindLabUtils::ComputeTurbulenceScaleValue);
        theList.append(WindLab::WindLabUtils::ComputeTurbulenceScaleVectorP);
        theList.append(WindLab::WindLabUtils::ComputeTurbulenceScaleVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupVariance) {
        theList.append(WindLab::WindLabUtils::ComputeVarianceValue);
        theList.append(WindLab::WindLabUtils::ComputeVarianceVectorP);
        theList.append(WindLab::WindLabUtils::ComputeVarianceVectorT);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupWavePassageEffect) {
        theList.append(WindLab::WindLabUtils::ComputeWavePassageEffectValue);
        theList.append(WindLab::WindLabUtils::ComputeWavePassageEffectVectorF);
        theList.append(WindLab::WindLabUtils::ComputeWavePassageEffectVectorT);
        theList.append(WindLab::WindLabUtils::ComputeWavePassageEffectMatrixPP);
        return theList;
    }
    else if (group == WindLab::WindLabUtils::objGroupUserDefinedRPSObject) {
        theList.append(WindLab::WindLabUtils::UserDefinedRPSObjectCompute);
        return theList;
    }

    return theList;
}

WindLabAPI::WindLabFeature* WindLabSimulation::createFeature(Base::Type type, std::string pluggedObjectTypeName, std::string name)
{
    //get the active document
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;

    //make unique name for this new feature in the active document (its parent document)
    std::string uniqueName = doc->getUniqueObjectName(name.c_str());

    //now figure out the feature type and create it
    if (type == WindLabAPI::WindLabFeatureCoherence::getClassTypeId()) {
        WindLabAPI::WindLabFeatureCoherence* newFeature =  CrpsCoherenceFactory::BuildObject(pluggedObjectTypeName);
        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureCorrelation::getClassTypeId()) {
    // Build an object
    WindLabAPI::WindLabFeatureCorrelation* newFeature = CrpsCorrelationFactory::BuildObject(pluggedObjectTypeName);
    if (NULL == newFeature) {
    return nullptr;
    }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution::getClassTypeId()) {
        WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution* newFeature = CrpsCumulativeProbabilityDistributionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureFrequencyDistribution::getClassTypeId()) {
        WindLabAPI::WindLabFeatureFrequencyDistribution* newFeature = CrpsFrequencyDistributionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureGustFactor::getClassTypeId()) {
        WindLabAPI::WindLabFeatureGustFactor* newFeature = CrpsGustFactorFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureKurtosis::getClassTypeId()) {
        WindLabAPI::WindLabFeatureKurtosis* newFeature = CrpsKurtosisFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureLocationDistribution::getClassTypeId()) {
        WindLabAPI::WindLabFeatureLocationDistribution* newFeature = CrpsLocationDistributionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureMatrixTool::getClassTypeId()) {
        WindLabAPI::WindLabFeatureMatrixTool* newFeature = CrpsMatrixToolFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureMeanWind::getClassTypeId()) {
        WindLabAPI::WindLabFeatureMeanWind* newFeature = CrpsMeanFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureModulation::getClassTypeId()) {
        WindLabAPI::WindLabFeatureModulation* newFeature =CrpsModulationFactory::BuildObject(pluggedObjectTypeName);
        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeaturePeakFactor::getClassTypeId()) {
        WindLabAPI::WindLabFeaturePeakFactor* newFeature = CrpsPeakFactorFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureProbabilityDensityFunction::getClassTypeId()) {
        WindLabAPI::WindLabFeatureProbabilityDensityFunction* newFeature = CrpsProbabilityDensityFunctionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeaturePSDDecompositionMethod::getClassTypeId()) {
        WindLabAPI::WindLabFeaturePSDDecompositionMethod* newFeature =  CrpsPSDdecomMethodFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureRandomness::getClassTypeId()) {
        WindLabAPI::WindLabFeatureRandomness* newFeature =  CrpsRandomnessFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureRoughness::getClassTypeId()) {
        WindLabAPI::WindLabFeatureRoughness* newFeature = CrpsRoughnessFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureShearVelocityOfFlow::getClassTypeId()) {
        WindLabAPI::WindLabFeatureShearVelocityOfFlow* newFeature = CrpsShearVelocityOfFlowFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureSimulationMethod::getClassTypeId()) {
        WindLabAPI::WindLabFeatureSimulationMethod* newFeature = CrpsSimuMethodFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureSkewness::getClassTypeId()) {
        WindLabAPI::WindLabFeatureSkewness* newFeature = CrpsSkewnessFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureStandardDeviation::getClassTypeId()) {
        WindLabAPI::WindLabFeatureStandardDeviation* newFeature = CrpsStandardDeviationFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());
        return newFeature;

    }
    else if (type == WindLabAPI::WindLabFeatureTableTool::getClassTypeId()) {
        WindLabAPI::WindLabFeatureTableTool* newFeature = CrpsTableToolFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureTurbulenceIntensity::getClassTypeId()) {
        WindLabAPI::WindLabFeatureTurbulenceIntensity* newFeature = CrpsTurbulenceIntensityFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureTurbulenceScale::getClassTypeId()) {
        WindLabAPI::WindLabFeatureTurbulenceScale* newFeature = CrpsTurbulenceScaleFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureUserDefinedRPSObject::getClassTypeId()) {
        WindLabAPI::WindLabFeatureUserDefinedRPSObject* newFeature =  CrpsUserDefinedRPSObjectFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureVariance::getClassTypeId()) {
        WindLabAPI::WindLabFeatureVariance* newFeature = CrpsVarianceFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureWavePassageEffect::getClassTypeId()) {
        WindLabAPI::WindLabFeatureWavePassageEffect* newFeature = CrpsWavePassageEffectFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureXSpectrum::getClassTypeId()) {
        WindLabAPI::WindLabFeatureXSpectrum* newFeature = CrpsXSpectrumFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureYSpectrum::getClassTypeId()) {
        WindLabAPI::WindLabFeatureYSpectrum* newFeature = CrpsYSpectrumFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == WindLabAPI::WindLabFeatureZSpectrum::getClassTypeId()) {
        WindLabAPI::WindLabFeatureZSpectrum* newFeature = CrpsZSpectrumFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }

}

void WindLabSimulation::setEnums(Base::Type type)
{

    if (type == WindLabAPI::WindLabFeatureCoherence::getClassTypeId()) {
        CoherenceFunction.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureCorrelation::getClassTypeId()) {
        CorrelationFunction.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution::getClassTypeId()) {
        CumulativeProbabilityDistribution.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureFrequencyDistribution::getClassTypeId()) {
        FrequencyDistribution.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureGustFactor::getClassTypeId()) {
        GustFactor.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureKurtosis::getClassTypeId()) {
        Kurtosis.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureLocationDistribution::getClassTypeId()) {
        SpatialDistribution.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureMatrixTool::getClassTypeId()) {
        MatrixTool.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureMeanWind::getClassTypeId()) {
        MeanFunction.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureModulation::getClassTypeId()) {
        ModulationFunction.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeaturePeakFactor::getClassTypeId()) {
        PeakFactor.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureProbabilityDensityFunction::getClassTypeId()) {
        ProbabilityDensityFunction.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeaturePSDDecompositionMethod::getClassTypeId()) {
        SpectrumDecompositionMethod.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureRandomness::getClassTypeId()) {
        RandomnessProvider.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureRoughness::getClassTypeId()) {
        Roughness.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureShearVelocityOfFlow::getClassTypeId()) {
        ShearVelocityOfFlow.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureSimulationMethod::getClassTypeId()) {
        SimulationMethod.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureSkewness::getClassTypeId()) {
        Skewness.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureStandardDeviation::getClassTypeId()) {
        StandardDeviation.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureTableTool::getClassTypeId()) {
        TableTool.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureTurbulenceIntensity::getClassTypeId()) {
        TurbulenceIntensity.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureTurbulenceScale::getClassTypeId()) {
        TurbulenceScale.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureUserDefinedRPSObject::getClassTypeId()) {
        UserDefinedRPSObject.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureVariance::getClassTypeId()) {
        VarianceFunction.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureWavePassageEffect::getClassTypeId()) {
        WavePassageEffect.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureXSpectrum::getClassTypeId()) {
        AlongWindSpectrumModel.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureYSpectrum::getClassTypeId()) {
        AcrossWindSpectrumModel.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
    else if (type == WindLabAPI::WindLabFeatureZSpectrum::getClassTypeId()) {
        VerticalWindSpectrumModel.setEnums(findAllWindLabFeaturesOfThisType(type));
    }
}

void WindLabSimulation::resetAllEnums()
{
  CoherenceFunction.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureCoherence::getClassTypeId()));
  CorrelationFunction.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureCorrelation::getClassTypeId()));
  CumulativeProbabilityDistribution.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution::getClassTypeId()));
  FrequencyDistribution.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureFrequencyDistribution::getClassTypeId()));
  GustFactor.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureGustFactor::getClassTypeId()));
  Kurtosis.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureKurtosis::getClassTypeId()));
  SpatialDistribution.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureLocationDistribution::getClassTypeId()));
  MatrixTool.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureMatrixTool::getClassTypeId()));
  MeanFunction.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureMeanWind::getClassTypeId()));
  ModulationFunction.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureModulation::getClassTypeId()));
  PeakFactor.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeaturePeakFactor::getClassTypeId()));
  ProbabilityDensityFunction.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureProbabilityDensityFunction::getClassTypeId()));
  SpectrumDecompositionMethod.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeaturePSDDecompositionMethod::getClassTypeId()));
  RandomnessProvider.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureRandomness::getClassTypeId()));
  Roughness.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureRoughness::getClassTypeId()));
  ShearVelocityOfFlow.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureShearVelocityOfFlow::getClassTypeId()));
  SimulationMethod.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureSimulationMethod::getClassTypeId()));
  Skewness.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureSkewness::getClassTypeId()));
  StandardDeviation.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureStandardDeviation::getClassTypeId()));
  TableTool.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureTableTool::getClassTypeId()));
  TurbulenceIntensity.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureTurbulenceIntensity::getClassTypeId()));
  TurbulenceScale.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureTurbulenceScale::getClassTypeId()));
  UserDefinedRPSObject.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureUserDefinedRPSObject::getClassTypeId()));
  VarianceFunction.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureVariance::getClassTypeId()));
  WavePassageEffect.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureWavePassageEffect::getClassTypeId()));
  AlongWindSpectrumModel.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureXSpectrum::getClassTypeId()));
  AcrossWindSpectrumModel.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureYSpectrum::getClassTypeId()));
  VerticalWindSpectrumModel.setEnums(findAllWindLabFeaturesOfThisType(WindLabAPI::WindLabFeatureZSpectrum::getClassTypeId()));
}

QStringList WindLabSimulation::findAllWindLabFeatures(Base::Type type)
{
    QStringList featureList;
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc) return featureList;
    auto features = doc->getObjectsOfType(type);
    for (auto& feat : features) {
       featureList.append(QString::fromUtf8(feat->getNameInDocument()));
    }
    return featureList;
}

QStringList WindLabSimulation::findAllWindLabFeaturesByGoupAndType(QString group, QString type)
{
    QStringList featureList;
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc) return featureList;
    auto features = this->getAllChildren();
    for (auto& feat : features) {
       auto myFeat = static_cast<WindLabAPI::WindLabFeature*>(feat);
       if (myFeat && myFeat->FeatureType.getStrValue() == type.toUtf8().constData() && myFeat->FeatureGroup.getStrValue() == group.toUtf8().constData())
    featureList.append(QString::fromUtf8(myFeat->getNameInDocument()));
    }
    return featureList;
}

std::vector<std::string> WindLabSimulation::findAllWindLabFeaturesOfThisType(Base::Type type)
{
    std::vector<std::string> featureList;
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc)return featureList;
    auto features = doc->getObjectsOfType(type);
    for (auto& feat : features) {
       App::DocumentObjectGroup* group = feat->getGroup();
       if (group)
       {
    if (this->getNameInDocument() == feat->getGroup()->getNameInDocument())
        featureList.emplace_back(feat->getNameInDocument());
       }
    }
    if (featureList.empty())
        featureList.emplace_back("<None>");

    return featureList;
}

Base::Type WindLabSimulation::getRPSType(QString group)
{
    if (group == WindLab::WindLabUtils::objGroupCoherenceFunction) {
        return WindLabAPI::IrpsWLCoherence::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupCorrelationFunction) {
        return WindLabAPI::IrpsWLCorrelation::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupCumulativeProbabilityDistribution) {
        return WindLabAPI::IrpsWLCumulativeProbabilityDistribution::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupFrequencyDistribution) {
        return WindLabAPI::IrpsWLFrequencyDistribution::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupGustFactor) {
        return WindLabAPI::IrpsWLGustFactor::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupKurtosis) {
        return WindLabAPI::IrpsWLKurtosis::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupLocationDistribution) {
        return WindLabAPI::IrpsWLLocationDistribution::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupMatrixTool) {
        return WindLabAPI::IrpsWLMatrixTool::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupMeanWindProfile) {
        return WindLabAPI::IrpsWLMean::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupModulationFunction) {
        return WindLabAPI::IrpsWLModulation::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupPeakFactor) {
        return WindLabAPI::IrpsWLPeakFactor::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupProbabilityDensityFunction) {
        return WindLabAPI::IrpsWLProbabilityDensityFunction::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupSpectrumDecompositionMethod) {
        return WindLabAPI::IrpsWLPSDdecompositionMethod::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupRandomnessProvider) {
        return WindLabAPI::IrpsWLRandomness::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupRoughness) {
        return WindLabAPI::IrpsWLRoughness::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupShearVelocityOfFlow) {
        return WindLabAPI::IrpsWLShearVelocityOfFlow::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupSimulationMethod) {
        return WindLabAPI::IrpsWLSimuMethod::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupSimulationMethod) {
        return WindLabAPI::IrpsWLSkewness::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupStandardDeviation) {
        return WindLabAPI::IrpsWLStandardDeviation::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupTableTool) {
        return WindLabAPI::IrpsWLTableTool::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceIntensity) {
        return WindLabAPI::IrpsWLTurbulenceIntensity::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceScale) {
        return WindLabAPI::IrpsWLTurbulenceScale::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupUserDefinedRPSObject) {
        return WindLabAPI::IrpsWLUserDefinedRPSObject::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupVariance) {
        return WindLabAPI::IrpsWLVariance::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupWavePassageEffect) {
        return WindLabAPI::IrpsWLWavePassageEffect::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupAlongWindSpectrum) {
        return WindLabAPI::IrpsWLXSpectrum::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupAcrossWindSpectrum) {
        return WindLabAPI::IrpsWLYSpectrum::getClassTypeId();
    }
    else if (group == WindLab::WindLabUtils::objGroupVerticalWindSpectrum) {
        return WindLabAPI::IrpsWLZSpectrum::getClassTypeId();
    }
}

std::vector<Base::Type> WindLabSimulation::getRPSTypesOfPluggableFeatures()
{
    std::vector<Base::Type> types;
    types.emplace_back(WindLabAPI::WindLabFeatureLocationDistribution::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureMeanWind::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureXSpectrum::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureZSpectrum::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureYSpectrum::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeaturePSDDecompositionMethod::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureCoherence::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureSimulationMethod::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureFrequencyDistribution::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureRandomness::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureModulation::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureCorrelation::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureTableTool::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureMatrixTool::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureGustFactor::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureKurtosis::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeaturePeakFactor::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureProbabilityDensityFunction::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureRoughness::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureShearVelocityOfFlow::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureSkewness::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureStandardDeviation::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureTurbulenceIntensity::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureTurbulenceScale::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureVariance::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureWavePassageEffect::getClassTypeId());
    types.emplace_back(WindLabAPI::WindLabFeatureUserDefinedRPSObject::getClassTypeId());

    return types;
}

std::vector<QString> WindLabSimulation::getWindLabPluggableFeatures()
{
    std::vector<QString> groups;
    groups.emplace_back(WindLab::WindLabUtils::objGroupLocationDistribution);
    groups.emplace_back(WindLab::WindLabUtils::objGroupMeanWindProfile);
    groups.emplace_back(WindLab::WindLabUtils::objGroupAlongWindSpectrum);
    groups.emplace_back(WindLab::WindLabUtils::objGroupAcrossWindSpectrum);
    groups.emplace_back(WindLab::WindLabUtils::objGroupVerticalWindSpectrum);
    groups.emplace_back(WindLab::WindLabUtils::objGroupSpectrumDecompositionMethod);
    groups.emplace_back(WindLab::WindLabUtils::objGroupCoherenceFunction);
    groups.emplace_back(WindLab::WindLabUtils::objGroupSimulationMethod);
    groups.emplace_back(WindLab::WindLabUtils::objGroupFrequencyDistribution);
    groups.emplace_back(WindLab::WindLabUtils::objGroupRandomnessProvider);
    groups.emplace_back(WindLab::WindLabUtils::objGroupModulationFunction);
    groups.emplace_back(WindLab::WindLabUtils::objGroupCorrelationFunction);
    groups.emplace_back(WindLab::WindLabUtils::objGroupTableTool);
    groups.emplace_back(WindLab::WindLabUtils::objGroupMatrixTool);
    groups.emplace_back(WindLab::WindLabUtils::objGroupCumulativeProbabilityDistribution);
    groups.emplace_back(WindLab::WindLabUtils::objGroupGustFactor);
    groups.emplace_back(WindLab::WindLabUtils::objGroupKurtosis);
    groups.emplace_back(WindLab::WindLabUtils::objGroupPeakFactor);
    groups.emplace_back(WindLab::WindLabUtils::objGroupProbabilityDensityFunction);
    groups.emplace_back(WindLab::WindLabUtils::objGroupRoughness);
    groups.emplace_back(WindLab::WindLabUtils::objGroupShearVelocityOfFlow);
    groups.emplace_back(WindLab::WindLabUtils::objGroupSkewness);
    groups.emplace_back(WindLab::WindLabUtils::objGroupStandardDeviation);
    groups.emplace_back(WindLab::WindLabUtils::objGroupTurbulenceIntensity);
    groups.emplace_back(WindLab::WindLabUtils::objGroupTurbulenceScale);
    groups.emplace_back(WindLab::WindLabUtils::objGroupVariance);
    groups.emplace_back(WindLab::WindLabUtils::objGroupWavePassageEffect);
    groups.emplace_back(WindLab::WindLabUtils::objGroupUserDefinedRPSObject);

    return groups;
}

bool WindLabSimulation::doubleClicked(void) 
{
    return true;
}

void WindLabSimulation::onChanged(const App::Property* prop)
{
    if (prop == &LocationIndexJ) {
        if (LocationIndexJ.getValue() < 0)
    LocationIndexJ.setValue(0);
        if (LocationIndexJ.getValue() > NumberOfProcess.getValue() - 1)
    LocationIndexJ.setValue(NumberOfProcess.getValue() - 1);
    }
    else if (prop == &LocationIndexK) {
        if (LocationIndexK.getValue() < 0)
    LocationIndexK.setValue(0);
        if (LocationIndexK.getValue() > NumberOfProcess.getValue() - 1)
    LocationIndexK.setValue(NumberOfProcess.getValue() - 1);
    }
    else if (prop == &FrequencyIndex) {
        if (FrequencyIndex.getValue() < 0)
    FrequencyIndex.setValue(0);
        if (FrequencyIndex.getValue() > NumberOfFrequency.getValue() - 1)
    FrequencyIndex.setValue(NumberOfFrequency.getValue() - 1);
    }
    else if (prop == &TimeIndex) {
        if (TimeIndex.getValue() < 0)
    TimeIndex.setValue(0);
        if (TimeIndex.getValue() > NumberOfTimeIncrements.getValue() - 1)
    TimeIndex.setValue(NumberOfTimeIncrements.getValue() - 1);
    }
    else if (prop == &DirectionIndex) {
        if (DirectionIndex.getValue() < 0)
    DirectionIndex.setValue(0);
        if (DirectionIndex.getValue() > NumberOfDirectionIncrements.getValue() - 1)
    DirectionIndex.setValue(NumberOfDirectionIncrements.getValue() - 1);
    }
    else if (prop == &NumberOfSample) {

        if (NumberOfSample.getValue() < 1) {
    NumberOfSample.setValue(1);
        }

        if (NumberOfSample.getValue() > 1)
        {
    LargeScaleSimulationMode.setValue(true);
        }
        else {

    LargeScaleSimulationMode.setValue(false);
        }
    }
    else if ((prop == &NumberOfProcess)
     || (prop == &NumberOfFrequency)
     || (prop == &NumberOfTimeIncrements) 
     || (prop == &NumberOfDirectionIncrements)
     || (prop == &NumberOfIncrementOfVariableX)) {

        ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/WindLab/General");
        int limitAutoAct = hGrp->GetBool("AutomaticLargeScaleModeActivation", true);
    
        hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/WindLab/Limit");
        int numberOfProcessLimit = hGrp->GetInt("MaxSPN", 300);
        int numberOfFrequencyLimit = hGrp->GetInt("MaxFIN", 102400);
        int numberOfTimeIncrementsLimit = hGrp->GetInt("MaxTIN", 61400);
        int numberOfDirectionIncrementsLimit = hGrp->GetInt("MaxDIN", 100000);
        int numberOfIncrementOfVariableXLimit = hGrp->GetInt("MaxXIN", 100000);

        if (limitAutoAct)
        {
    if ((NumberOfProcess.getValue() > numberOfProcessLimit)
        || (NumberOfFrequency.getValue() > numberOfFrequencyLimit)
        || (NumberOfTimeIncrements.getValue() > numberOfTimeIncrementsLimit)
        || (NumberOfDirectionIncrements.getValue() > numberOfDirectionIncrementsLimit)
        || (NumberOfIncrementOfVariableX.getValue() > numberOfIncrementOfVariableXLimit)) {

        LargeScaleSimulationMode.setValue(true);
    }
    else {
        LargeScaleSimulationMode.setValue(false);
    }
        }
       

    }
   
    updateSimulationData();

    Simulation::onChanged(prop);
}


WindLabAPI::WindLabFeatureDescription* WindLabSimulation::GetWindLabPluggedWindLabFeatureDescription(const QString& objectGroup, const QString& objName)
{
    WindLabFeatureDescription* pluggedWindLabFeatureDescription = new WindLabFeatureDescription();
    std::string pluginName;
    std::string descrip;
    std::string pubTitle;
    std::string pubLink;
    std::string pubAuthor;
    std::string pubDate;
    std::string version;
    bool stationarity;
    std::string objectName = objName.toUtf8().constData();

    if (objectGroup == WindLab::WindLabUtils::objGroupLocationDistribution) {
        pluginName = CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsLocationDistributionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsLocationDistributionFactory::GetTitleMap()[objectName];
        pubLink = CrpsLocationDistributionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsLocationDistributionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsLocationDistributionFactory::GetDateMap()[objectName];
        version = CrpsLocationDistributionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsLocationDistributionFactory::GetStationarityMap()[objectName];

    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupMeanWindProfile) {
        pluginName = CrpsMeanFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsMeanFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsMeanFactory::GetTitleMap()[objectName];
        pubLink = CrpsMeanFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsMeanFactory::GetAuthorMap()[objectName];
        pubDate = CrpsMeanFactory::GetDateMap()[objectName];
        version = CrpsMeanFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsMeanFactory::GetStationarityMap()[objectName];

    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupAlongWindSpectrum) {
        pluginName = CrpsXSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsXSpectrumFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsXSpectrumFactory::GetTitleMap()[objectName];
        pubLink = CrpsXSpectrumFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsXSpectrumFactory::GetAuthorMap()[objectName];
        pubDate = CrpsXSpectrumFactory::GetDateMap()[objectName];
        version = CrpsXSpectrumFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsXSpectrumFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupAcrossWindSpectrum) {
        pluginName = CrpsYSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsYSpectrumFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsYSpectrumFactory::GetTitleMap()[objectName];
        pubLink = CrpsYSpectrumFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsYSpectrumFactory::GetAuthorMap()[objectName];
        pubDate = CrpsYSpectrumFactory::GetDateMap()[objectName];
        version = CrpsYSpectrumFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsYSpectrumFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupVerticalWindSpectrum) {
        pluginName = CrpsZSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsZSpectrumFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsZSpectrumFactory::GetTitleMap()[objectName];
        pubLink = CrpsZSpectrumFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsZSpectrumFactory::GetAuthorMap()[objectName];
        pubDate = CrpsZSpectrumFactory::GetDateMap()[objectName];
        version = CrpsZSpectrumFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsZSpectrumFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupSpectrumDecompositionMethod) {
        pluginName = CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsPSDdecomMethodFactory::GetTitleMap()[objectName];
        pubLink = CrpsPSDdecomMethodFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsPSDdecomMethodFactory::GetAuthorMap()[objectName];
        pubDate = CrpsPSDdecomMethodFactory::GetDateMap()[objectName];
        version = CrpsPSDdecomMethodFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsPSDdecomMethodFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupCoherenceFunction) {
        pluginName = CrpsCoherenceFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsCoherenceFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsCoherenceFactory::GetTitleMap()[objectName];
        pubLink = CrpsCoherenceFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsCoherenceFactory::GetAuthorMap()[objectName];
        pubDate = CrpsCoherenceFactory::GetDateMap()[objectName];
        version = CrpsCoherenceFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsCoherenceFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupSimulationMethod) {
        pluginName = CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsSimuMethodFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsSimuMethodFactory::GetTitleMap()[objectName];
        pubLink = CrpsSimuMethodFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsSimuMethodFactory::GetAuthorMap()[objectName];
        pubDate = CrpsSimuMethodFactory::GetDateMap()[objectName];
        version = CrpsSimuMethodFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsSimuMethodFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupFrequencyDistribution) {
        pluginName = CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsFrequencyDistributionFactory::GetTitleMap()[objectName];
        pubLink = CrpsFrequencyDistributionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsFrequencyDistributionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsFrequencyDistributionFactory::GetDateMap()[objectName];
        version = CrpsFrequencyDistributionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsFrequencyDistributionFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupRandomnessProvider) {
        pluginName = CrpsRandomnessFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsRandomnessFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsRandomnessFactory::GetTitleMap()[objectName];
        pubLink = CrpsRandomnessFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsRandomnessFactory::GetAuthorMap()[objectName];
        pubDate = CrpsRandomnessFactory::GetDateMap()[objectName];
        version = CrpsRandomnessFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsRandomnessFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupModulationFunction) {
        pluginName = CrpsModulationFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsModulationFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsModulationFactory::GetTitleMap()[objectName];
        pubLink = CrpsModulationFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsModulationFactory::GetAuthorMap()[objectName];
        pubDate = CrpsModulationFactory::GetDateMap()[objectName];
        version = CrpsModulationFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsModulationFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupTableTool) {
        pluginName = CrpsTableToolFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsTableToolFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsTableToolFactory::GetTitleMap()[objectName];
        pubLink = CrpsTableToolFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsTableToolFactory::GetAuthorMap()[objectName];
        pubDate = CrpsTableToolFactory::GetDateMap()[objectName];
        version = CrpsTableToolFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsTableToolFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupMatrixTool) {
        pluginName = CrpsMatrixToolFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsMatrixToolFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsMatrixToolFactory::GetTitleMap()[objectName];
        pubLink = CrpsMatrixToolFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsMatrixToolFactory::GetAuthorMap()[objectName];
        pubDate = CrpsMatrixToolFactory::GetDateMap()[objectName];
        version = CrpsMatrixToolFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsMatrixToolFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupUserDefinedRPSObject) {
        pluginName = CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsUserDefinedRPSObjectFactory::GetTitleMap()[objectName];
        pubLink = CrpsUserDefinedRPSObjectFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsUserDefinedRPSObjectFactory::GetAuthorMap()[objectName];
        pubDate = CrpsUserDefinedRPSObjectFactory::GetDateMap()[objectName];
        version = CrpsUserDefinedRPSObjectFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsUserDefinedRPSObjectFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupCumulativeProbabilityDistribution) {
        pluginName = CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsCumulativeProbabilityDistributionFactory::GetTitleMap()[objectName];
        pubLink = CrpsCumulativeProbabilityDistributionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsCumulativeProbabilityDistributionFactory::GetDateMap()[objectName];
        version = CrpsCumulativeProbabilityDistributionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsCumulativeProbabilityDistributionFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupGustFactor) {
        pluginName = CrpsGustFactorFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsGustFactorFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsGustFactorFactory::GetTitleMap()[objectName];
        pubLink = CrpsGustFactorFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsGustFactorFactory::GetAuthorMap()[objectName];
        pubDate = CrpsGustFactorFactory::GetDateMap()[objectName];
        version = CrpsGustFactorFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsGustFactorFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupKurtosis) {
        pluginName = CrpsKurtosisFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsKurtosisFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsKurtosisFactory::GetTitleMap()[objectName];
        pubLink = CrpsKurtosisFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsKurtosisFactory::GetAuthorMap()[objectName];
        pubDate = CrpsKurtosisFactory::GetDateMap()[objectName];
        version = CrpsKurtosisFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsKurtosisFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupPeakFactor) {
        pluginName = CrpsPeakFactorFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsPeakFactorFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsPeakFactorFactory::GetTitleMap()[objectName];
        pubLink = CrpsPeakFactorFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsPeakFactorFactory::GetAuthorMap()[objectName];
        pubDate = CrpsPeakFactorFactory::GetDateMap()[objectName];
        version = CrpsPeakFactorFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsPeakFactorFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupProbabilityDensityFunction) {
        pluginName = CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsProbabilityDensityFunctionFactory::GetTitleMap()[objectName];
        pubLink = CrpsProbabilityDensityFunctionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsProbabilityDensityFunctionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsProbabilityDensityFunctionFactory::GetDateMap()[objectName];
        version = CrpsProbabilityDensityFunctionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsProbabilityDensityFunctionFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupRoughness) {
        pluginName = CrpsRoughnessFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsRoughnessFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsRoughnessFactory::GetTitleMap()[objectName];
        pubLink = CrpsRoughnessFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsRoughnessFactory::GetAuthorMap()[objectName];
        pubDate = CrpsRoughnessFactory::GetDateMap()[objectName];
        version = CrpsRoughnessFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsRoughnessFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupShearVelocityOfFlow) {
        pluginName = CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsShearVelocityOfFlowFactory::GetTitleMap()[objectName];
        pubLink = CrpsShearVelocityOfFlowFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsShearVelocityOfFlowFactory::GetAuthorMap()[objectName];
        pubDate = CrpsShearVelocityOfFlowFactory::GetDateMap()[objectName];
        version = CrpsShearVelocityOfFlowFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsShearVelocityOfFlowFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupSkewness) {
        pluginName = CrpsSkewnessFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsSkewnessFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsSkewnessFactory::GetTitleMap()[objectName];
        pubLink = CrpsSkewnessFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsSkewnessFactory::GetAuthorMap()[objectName];
        pubDate = CrpsSkewnessFactory::GetDateMap()[objectName];
        version = CrpsSkewnessFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsSkewnessFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupStandardDeviation) {
        pluginName = CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsStandardDeviationFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsStandardDeviationFactory::GetTitleMap()[objectName];
        pubLink = CrpsStandardDeviationFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsStandardDeviationFactory::GetAuthorMap()[objectName];
        pubDate = CrpsStandardDeviationFactory::GetDateMap()[objectName];
        version = CrpsStandardDeviationFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsStandardDeviationFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupTurbulenceIntensity) {
        pluginName = CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsTurbulenceIntensityFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsTurbulenceIntensityFactory::GetTitleMap()[objectName];
        pubLink = CrpsTurbulenceIntensityFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsTurbulenceIntensityFactory::GetAuthorMap()[objectName];
        pubDate = CrpsTurbulenceIntensityFactory::GetDateMap()[objectName];
        version = CrpsTurbulenceIntensityFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsTurbulenceIntensityFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupTurbulenceScale) {
        pluginName = CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsTurbulenceScaleFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsTurbulenceScaleFactory::GetTitleMap()[objectName];
        pubLink = CrpsTurbulenceScaleFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsTurbulenceScaleFactory::GetAuthorMap()[objectName];
        pubDate = CrpsTurbulenceScaleFactory::GetDateMap()[objectName];
        version = CrpsTurbulenceScaleFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsTurbulenceScaleFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupVariance) {
        pluginName = CrpsVarianceFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsVarianceFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsVarianceFactory::GetTitleMap()[objectName];
        pubLink = CrpsVarianceFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsVarianceFactory::GetAuthorMap()[objectName];
        pubDate = CrpsVarianceFactory::GetDateMap()[objectName];
        version = CrpsVarianceFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsVarianceFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == WindLab::WindLabUtils::objGroupWavePassageEffect) {
        pluginName = CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsWavePassageEffectFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsWavePassageEffectFactory::GetTitleMap()[objectName];
        pubLink = CrpsWavePassageEffectFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsWavePassageEffectFactory::GetAuthorMap()[objectName];
        pubDate = CrpsWavePassageEffectFactory::GetDateMap()[objectName];
        version = CrpsWavePassageEffectFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsWavePassageEffectFactory::GetStationarityMap()[objectName];
    }

    pluggedWindLabFeatureDescription->PluginName.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())] ->GetPluginName().toUtf8().constData());
    pluggedWindLabFeatureDescription->ReleaseDate.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())] ->GetPluginReleaseDate().toUtf8().constData());
    pluggedWindLabFeatureDescription->Path.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginSubFolder().toUtf8().constData());
    pluggedWindLabFeatureDescription->Author.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginAuthor().toUtf8().constData());
    pluggedWindLabFeatureDescription->PluginVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginVersion().toUtf8().constData());
    pluggedWindLabFeatureDescription->LabRPSVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetLabRPSVersion().toUtf8().constData());
    pluggedWindLabFeatureDescription->APIVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetAPIVersion().toUtf8().constData());
    pluggedWindLabFeatureDescription->ObjectName.setValue(objectName);
    pluggedWindLabFeatureDescription->Version.setValue(version);
    pluggedWindLabFeatureDescription->Stationarity.setValue(stationarity);
    pluggedWindLabFeatureDescription->Description.setValue(descrip);
    pluggedWindLabFeatureDescription->PublicationTitle.setValue(pubTitle);
    pluggedWindLabFeatureDescription->PublicationLink.setValue(pubLink);
    pluggedWindLabFeatureDescription->PublicationAuthor.setValue(pubAuthor);
    pluggedWindLabFeatureDescription->PublicationDate.setValue(pubDate);

    return pluggedWindLabFeatureDescription;
}

void WindLabSimulation::createNewSimulation() {}

PyObject* WindLabSimulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        PythonObject = Py::Object(new WindLabSimulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool WindLabSimulation::computeCrossCoherenceVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
   auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
        return false;
    WindLabAPI::IrpsWLCoherence* activefeature = static_cast<WindLabAPI::IrpsWLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active coherence function feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeCrossCoherenceVectorF(*this->getSimulationData(),locationJ, locationK, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the coherence vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeCrossCoherenceVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
        return false;
    WindLabAPI::IrpsWLCoherence* activefeature = static_cast<WindLabAPI::IrpsWLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active coherence function feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeCrossCoherenceVectorT(*this->getSimulationData(), locationJ, locationK, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the coherence vector has failed.\n");
     return false;
    }

    return true;
}

bool WindLabSimulation::computeCrossCoherenceMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    WindLabAPI::IrpsWLCoherence* activefeature = static_cast<WindLabAPI::IrpsWLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active coherence function feature found.\n");
        return false;
    }
    dCoherenceMatrix.resize(this->getSimulationData()->numberOfSpatialPosition.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeCrossCoherenceMatrixPP(*this->getSimulationData(), dFrequency, dTime,  dCoherenceMatrix);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the coherence matrix has failed.\n");
     return false;
    }

    return true;
}

	
bool WindLabSimulation::computeCrossCorrelationVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
        if(!doc)
	    return false;
    WindLabAPI::IrpsWLCorrelation* activefeature = static_cast<WindLabAPI::IrpsWLCorrelation*>(doc->getObject(_simuData->correlationFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active correlation function feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeCrossCorrelationVectorT(*this->getSimulationData(), locationJ, locationK, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the correlation vector has failed.\n");
     return false;
    }

    return true;
}

bool WindLabSimulation::computeCrossCorrelationMatrixPP(const double &dTime, mat &dCorrelationMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLCorrelation* activefeature = static_cast<WindLabAPI::IrpsWLCorrelation*>(doc->getObject(_simuData->correlationFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active correlation function feature found.\n");
        return false;
    }
    dCorrelationMatrix.resize(this->getSimulationData()->numberOfSpatialPosition.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeCrossCorrelationMatrixPP(*this->getSimulationData(), dTime, dCorrelationMatrix);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the correlation matrix has failed.\n");
     return false;
    }

    return true;

}

bool WindLabSimulation::computeFrequenciesVectorF(const Base::Vector3d &location, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLFrequencyDistribution* activefeature = static_cast<WindLabAPI::IrpsWLFrequencyDistribution*>(doc->getObject(_simuData->frequencyDistribution.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active frequency distribution feature found.\n");
        return false;
    }
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeFrequenciesVectorF(*this->getSimulationData(), location, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the frequency vector has failed.\n");
     return false;
    }
    return true;
}
  
bool WindLabSimulation::computeFrequenciesMatrixFP(mat& dMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLFrequencyDistribution* activefeature = static_cast<WindLabAPI::IrpsWLFrequencyDistribution*>(doc->getObject(_simuData->frequencyDistribution.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active frequency distribution feature found.\n");
        return false;
    }
    dMatrix.resize(this->getSimulationData()->numberOfFrequency.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeFrequenciesMatrixFP(*this->getSimulationData(), dMatrix);
    if (!returnResult) {
     Base::Console().Error("The computation of the frequency matrix has failed.\n");
     return false;
    }
    return true;

}

bool WindLabSimulation::computeLocationCoordinateMatrixP3(mat& dLocCoord, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLLocationDistribution* activefeature = static_cast<WindLabAPI::IrpsWLLocationDistribution*>(doc->getObject(_simuData->spatialDistribution.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active location distribution feature found.\n");
        return false;
    }
    dLocCoord.resize(_simuData->numberOfSpatialPosition.getValue(), 4);
    bool returnResult = activefeature->ComputeLocationCoordinateMatrixP3(*this->getSimulationData(), dLocCoord);
    if (!returnResult) {
        Base::Console().Error("The computation of the location coordinates has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeMeanWindSpeedVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLMean* activefeature = static_cast<WindLabAPI::IrpsWLMean*>(doc->getObject(_simuData->meanFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active mean wind speed profile feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeMeanWindSpeedVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
     if (!returnResult) {
        Base::Console().Error("The computation of the mean wind speed vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeMeanWindSpeedVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLMean* activefeature = static_cast<WindLabAPI::IrpsWLMean*>(doc->getObject(_simuData->meanFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active mean wind speed profile feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeMeanWindSpeedVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the mean velocity vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeModulationVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLModulation* activefeature = static_cast<WindLabAPI::IrpsWLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active modulation function feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeModulationVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the modulation vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeModulationVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLModulation* activefeature = static_cast<WindLabAPI::IrpsWLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active modulation function feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeModulationVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the modulation vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeDecomposedCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLPSDdecompositionMethod* activefeature = static_cast<WindLabAPI::IrpsWLPSDdecompositionMethod*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum decomposition method feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeDecomposedCrossSpectrumVectorF(*this->getSimulationData(), locationJ, locationK, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the decomposed spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeDecomposedCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLPSDdecompositionMethod* activefeature = static_cast<WindLabAPI::IrpsWLPSDdecompositionMethod*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum decomposition method feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeDecomposedCrossSpectrumVectorT(*this->getSimulationData(), locationJ, locationK, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the decomposed spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeDecomposedCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLPSDdecompositionMethod* activefeature = static_cast<WindLabAPI::IrpsWLPSDdecompositionMethod*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum decomposition method feature found.\n");
        return false;
    }
    dPSDMatrix.resize(this->getSimulationData()->numberOfSpatialPosition.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeDecomposedCrossSpectrumMatrixPP(*this->getSimulationData(), dFrequency, dTime, dPSDMatrix);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the decomposed spectrum matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::generateRandomMatrixFP(mat& dRandomValueArray, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLRandomness* activefeature = static_cast<WindLabAPI::IrpsWLRandomness*>(doc->getObject(_simuData->randomnessProvider.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active randomness provider feature found.\n");
        return false;
    }
    dRandomValueArray.resize(this->getSimulationData()->numberOfFrequency.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->GenerateRandomMatrixFP(*this->getSimulationData(), dRandomValueArray);
    if (!returnResult)
    {
     Base::Console().Error("The computation of random phase vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeXCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLXSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(_simuData->alongWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active along wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeXCrossSpectrumVectorF(*this->getSimulationData(), locationJ, locationK, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeXCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLXSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(_simuData->alongWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active along wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeXCrossSpectrumVectorT(*this->getSimulationData(), locationJ, locationK, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeXCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &psdMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLXSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(_simuData->alongWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active along wind spectrum model feature found.\n");
        return false;
    }
    psdMatrix.resize(this->getSimulationData()->numberOfSpatialPosition.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeXCrossSpectrumMatrixPP(*this->getSimulationData(), dFrequency, dTime, psdMatrix);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the decomposed spectrum matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeXAutoSpectrumValue(const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLXSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(_simuData->alongWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active along wind spectrum model feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeXAutoSpectrumValue(*this->getSimulationData(), location, dFrequency, dTime, dValue);    
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}
    
bool WindLabSimulation::computeXAutoSpectrumVectorF(const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLXSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(_simuData->alongWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active along wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeXAutoSpectrumVectorF(*this->getSimulationData(), location, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeXAutoSpectrumVectorT(const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLXSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(_simuData->alongWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active along wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeXAutoSpectrumVectorT(*this->getSimulationData(), location, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeYCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLYSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(_simuData->acrossWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active across wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeYCrossSpectrumVectorF(*this->getSimulationData(), locationJ, locationK, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeYCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLYSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(_simuData->acrossWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active across wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeYCrossSpectrumVectorT(*this->getSimulationData(), locationJ, locationK, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeYCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &psdMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLYSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(_simuData->acrossWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active across wind spectrum model feature found.\n");
        return false;
    }
    psdMatrix.resize(this->getSimulationData()->numberOfSpatialPosition.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeYCrossSpectrumMatrixPP(*this->getSimulationData(), dFrequency, dTime, psdMatrix);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeYAutoSpectrumValue(const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLYSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(_simuData->acrossWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active across wind spectrum model feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeYAutoSpectrumValue(*this->getSimulationData(), location, dFrequency, dTime, dValue);       
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}
    
bool WindLabSimulation::computeYAutoSpectrumVectorF(const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLYSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(_simuData->acrossWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active across wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeYAutoSpectrumVectorF(*this->getSimulationData(), location, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeYAutoSpectrumVectorT(const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLYSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(_simuData->acrossWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active across wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeYAutoSpectrumVectorT(*this->getSimulationData(), location, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeZCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLZSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(_simuData->verticalWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active vertical wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeZCrossSpectrumVectorF(*this->getSimulationData(), locationJ, locationK, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeZCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLZSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(_simuData->verticalWindSpectrumModel.getValue()));

    if (!activefeature) {
        Base::Console().Error("No valid active vertical wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeZCrossSpectrumVectorT(*this->getSimulationData(), locationJ, locationK, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeZCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &psdMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLZSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(_simuData->verticalWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active vertical wind spectrum model feature found.\n");
        return false;
    }
    psdMatrix.resize(this->getSimulationData()->numberOfSpatialPosition.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeZCrossSpectrumMatrixPP(*this->getSimulationData(), dFrequency, dTime, psdMatrix);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeZAutoSpectrumValue(const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLZSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(_simuData->verticalWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active vertical wind spectrum model feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeZAutoSpectrumValue(*this->getSimulationData(), location, dFrequency, dTime, dValue); 
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}
    
bool WindLabSimulation::computeZAutoSpectrumVectorF(const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLZSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(_simuData->verticalWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active vertical wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeZAutoSpectrumVectorF(*this->getSimulationData(), location, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeZAutoSpectrumVectorT(const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLZSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(_simuData->verticalWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active vertical wind spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeZAutoSpectrumVectorT(*this->getSimulationData(), location, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
     if (strcmp(_simuData->WindDirection.getValueAsString(), "Along wind") == 0)
	{
        return computeXCrossSpectrumVectorF(locationJ, locationK, dTime, dVarVector, dValVector, featureName);
	}
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Across wind") == 0)
	{
        return computeYCrossSpectrumVectorF(locationJ, locationK, dTime, dVarVector, dValVector, featureName);
	}
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Vertical wind") == 0)
	{
        return computeZCrossSpectrumVectorF(locationJ, locationK, dTime, dVarVector, dValVector, featureName);
	}

}

bool WindLabSimulation::computeCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    if (strcmp(_simuData->WindDirection.getValueAsString(), "Along wind") == 0)
	{
        return computeXCrossSpectrumVectorT(locationJ, locationK, dFrequency, dVarVector, dValVector, featureName);
	}
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Across wind") == 0)
	{
        return computeYCrossSpectrumVectorT(locationJ, locationK, dFrequency, dVarVector, dValVector, featureName);
	}
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Vertical wind") == 0)
	{
        return computeZCrossSpectrumVectorT(locationJ, locationK, dFrequency, dVarVector, dValVector, featureName);
	}
}

bool WindLabSimulation::computeCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix, std::string& featureName)
{
    if (strcmp(_simuData->WindDirection.getValueAsString(), "Along wind") == 0) {
        return computeXCrossSpectrumMatrixPP(dFrequency, dTime, dPSDMatrix, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Across wind") == 0) {
        return computeYCrossSpectrumMatrixPP(dFrequency, dTime, dPSDMatrix, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Vertical wind") == 0) {
        return computeZCrossSpectrumMatrixPP(dFrequency, dTime, dPSDMatrix, featureName);
    }
}

bool WindLabSimulation::computeAutoSpectrumValue(const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue, std::string& featureName)
{
    if (strcmp(_simuData->WindDirection.getValueAsString(), "Along wind") == 0) {
        return computeXAutoSpectrumValue(location, dFrequency, dTime, dValue, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Across wind") == 0) {
        return computeYAutoSpectrumValue(location, dFrequency, dTime, dValue, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Vertical wind") == 0) {
        return computeZAutoSpectrumValue(location, dFrequency, dTime, dValue, featureName);
    }
}
    
bool WindLabSimulation::computeAutoSpectrumVectorF(const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    if (strcmp(_simuData->WindDirection.getValueAsString(), "Along wind") == 0) {
        return computeXAutoSpectrumVectorF(location, dTime, dVarVector, dValVector, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Across wind") == 0) {
        return computeYAutoSpectrumVectorF(location, dTime, dVarVector, dValVector, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Vertical wind") == 0) {
        return computeZAutoSpectrumVectorF(location, dTime, dVarVector, dValVector, featureName);
    }
}

bool WindLabSimulation::computeAutoSpectrumVectorT(const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    if (strcmp(_simuData->WindDirection.getValueAsString(), "Along wind") == 0) {
        return computeXAutoSpectrumVectorT(location, dFrequency, dVarVector, dValVector, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Across wind") == 0) {
        return computeYAutoSpectrumVectorT(location, dFrequency, dVarVector, dValVector, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Vertical wind") == 0) {
        return computeZAutoSpectrumVectorT(location, dFrequency, dVarVector, dValVector, featureName);
    }
}

bool WindLabSimulation::computeCrossCoherenceValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLCoherence* activefeature = static_cast<WindLabAPI::IrpsWLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active coherence function feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeCrossCoherenceValue(*this->getSimulationData(), locationJ, locationK, dFrequency, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the coherence value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeCrossCorrelationValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLCorrelation* activefeature = static_cast<WindLabAPI::IrpsWLCorrelation*>(doc->getObject(_simuData->correlationFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active correlation function feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeCrossCorrelationValue(*this->getSimulationData(), locationJ, locationK, dTime, dValue);    
    if (!returnResult)
    {
     Base::Console().Error("The computation of the correlation value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeMeanWindSpeedValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLMean* activefeature = static_cast<WindLabAPI::IrpsWLMean*>(doc->getObject(_simuData->meanFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active mean wind speed profile feature found.\n");
    return false;
    }
    bool returnResult = activefeature->ComputeMeanWindSpeedValue(*this->getSimulationData(), location, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of mean wind speed value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeModulationValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLModulation* activefeature = static_cast<WindLabAPI::IrpsWLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active modulation function feature found.\n");
    return false;
    }
    bool returnResult = activefeature->ComputeModulationValue(*this->getSimulationData(), location, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the modulation value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}
bool WindLabSimulation::computeRandomValue(double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    Base::Console().Error("Sorry this tool is not yet implemented.\n");
    return true;

}
bool WindLabSimulation::computeXCrossSpectrumValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLXSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLXSpectrum*>(doc->getObject(_simuData->alongWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active along wind spectrum model feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeXCrossSpectrumValue(*this->getSimulationData(), locationJ, locationK, dFrequency, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}
bool WindLabSimulation::computeYCrossSpectrumValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLYSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLYSpectrum*>(doc->getObject(_simuData->acrossWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active across wind spectrum model feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeYCrossSpectrumValue(*this->getSimulationData(), locationJ, locationK, dFrequency, dTime, dValue);   
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeZCrossSpectrumValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLZSpectrum* activefeature = static_cast<WindLabAPI::IrpsWLZSpectrum*>(doc->getObject(_simuData->verticalWindSpectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active vertical wind spectrum model feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeZCrossSpectrumValue(*this->getSimulationData(), locationJ, locationK, dFrequency, dTime, dValue);   
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeCrossSpectrumValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    if (strcmp(_simuData->WindDirection.getValueAsString(), "Along wind") == 0) {
     return computeXCrossSpectrumValue(locationJ, locationK, dFrequency, dTime, dValue, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Across wind") == 0) {
     return computeYCrossSpectrumValue(locationJ, locationK, dFrequency, dTime, dValue, featureName);
    }
    else if (strcmp(_simuData->WindDirection.getValueAsString(), "Vertical wind") == 0) {
     return computeZCrossSpectrumValue(locationJ, locationK, dFrequency, dTime, dValue, featureName);
    }
}
bool WindLabSimulation::computeFrequencyValue(const Base::Vector3d &location, const int &frequencyIndex, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLFrequencyDistribution* activefeature = static_cast<WindLabAPI::IrpsWLFrequencyDistribution*>(doc->getObject(_simuData->frequencyDistribution.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active frequency distribution feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeFrequencyValue(*this->getSimulationData(), location, frequencyIndex, dValue);
    if (!returnResult) {
     Base::Console().Error("The computation of the frequency value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();

    return true;

}


bool WindLabSimulation::tableToolCompute(mat& inputTable, mat &outputTable, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLTableTool* activefeature = static_cast<WindLabAPI::IrpsWLTableTool*>(doc->getObject(_simuData->tableTool.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active table tool feature found.\n");
        return false;
    }
    outputTable.resize(inputTable.rows(), inputTable.cols());
    bool returnResult = activefeature->TableToolCompute(*this->getSimulationData(), inputTable, outputTable);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the table tool has failed.\n");
     return false;
    }
    return true;
}
bool WindLabSimulation::matrixToolCompute(mat& inputTable, mat &outputMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLMatrixTool* activefeature = static_cast<WindLabAPI::IrpsWLMatrixTool*>(doc->getObject(_simuData->matrixTool.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active matrix tool feature found.\n");
        return false;
    }
    outputMatrix.resize(inputTable.rows(), inputTable.cols());
    bool returnResult = activefeature->MatrixToolCompute(*this->getSimulationData(), inputTable, outputMatrix);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the correlation matrix has failed.\n");
     return false;
    }

    return true;
}
bool WindLabSimulation::userDefinedRPSObjectCompute(mat &dresult, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLUserDefinedRPSObject* activefeature = static_cast<WindLabAPI::IrpsWLUserDefinedRPSObject*>(doc->getObject(_simuData->userDefinedRPSObject.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active user defined feature found.\n");
        return false;
    }
    dresult.resize(this->getSimulationData()->numberOfSpatialPosition.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->UserDefinedRPSObjectCompute(*this->getSimulationData(), dresult);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the user defined feature has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeCPDValue(const double& x, double& dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLCumulativeProbabilityDistribution* activefeature = static_cast<WindLabAPI::IrpsWLCumulativeProbabilityDistribution*>(doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active CPD feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeCPDValue(*this->getSimulationData(), x, dValue);     
    if (!returnResult)
    {
     Base::Console().Error("The computation of the CPD value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();

    return true;

}
bool WindLabSimulation::computeCPDVectorX(vec& dVarVector, vec& dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLCumulativeProbabilityDistribution* activefeature = static_cast<WindLabAPI::IrpsWLCumulativeProbabilityDistribution*>(doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active cummulative probability distribution feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfIncrementOfVariableX.getValue());
    dValVector.resize(this->getSimulationData()->numberOfIncrementOfVariableX.getValue());
    bool returnResult = activefeature->ComputeCPDVectorX(*this->getSimulationData(), dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the CPD vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}    
bool WindLabSimulation::computeGustFactorValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLGustFactor* activefeature = static_cast<WindLabAPI::IrpsWLGustFactor*>(doc->getObject(_simuData->gustFactor.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active gust factor feature found.\n");
        return false;
    }   
    bool returnResult = activefeature->ComputeGustFactorValue(*this->getSimulationData(), location, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the gust factor value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeGustFactorVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLGustFactor* activefeature = static_cast<WindLabAPI::IrpsWLGustFactor*>(doc->getObject(_simuData->gustFactor.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active gust factor feature found.\n");
    return false;
    }
    bool returnResult = activefeature->ComputeGustFactorVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the gust factor value has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}
bool WindLabSimulation::computeGustFactorVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLGustFactor* activefeature = static_cast<WindLabAPI::IrpsWLGustFactor*>(doc->getObject(_simuData->gustFactor.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active gust factor feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeGustFactorVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the gust factor vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeKurtosisValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLKurtosis* activefeature = static_cast<WindLabAPI::IrpsWLKurtosis*>(doc->getObject(_simuData->kurtosis.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active kurtosis feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeKurtosisValue(*this->getSimulationData(), location, dTime, dValue);       
    if (!returnResult)
    {
     Base::Console().Error("The computation of the kurtosis value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeKurtosisVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLKurtosis* activefeature = static_cast<WindLabAPI::IrpsWLKurtosis*>(doc->getObject(_simuData->kurtosis.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active kurtosis feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeKurtosisVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the kurtosis vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeKurtosisVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLKurtosis* activefeature = static_cast<WindLabAPI::IrpsWLKurtosis*>(doc->getObject(_simuData->kurtosis.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active kurtosis feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeKurtosisVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the kurtosis vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computePeakFactorValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLPeakFactor* activefeature = static_cast<WindLabAPI::IrpsWLPeakFactor*>(doc->getObject(_simuData->peakFactor.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active peak factor feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputePeakFactorValue(*this->getSimulationData(), location, dTime, dValue);         
    if (!returnResult)
    {
     Base::Console().Error("The computation of the kurtosis value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computePeakFactorVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLPeakFactor* activefeature = static_cast<WindLabAPI::IrpsWLPeakFactor*>(doc->getObject(_simuData->peakFactor.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active peak factor feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputePeakFactorVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the peak factor vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computePeakFactorVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLPeakFactor* activefeature = static_cast<WindLabAPI::IrpsWLPeakFactor*>(doc->getObject(_simuData->peakFactor.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active peak factor feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputePeakFactorVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the peack factor vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computePDFValue(const double& x, double& dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLProbabilityDensityFunction* activefeature = static_cast<WindLabAPI::IrpsWLProbabilityDensityFunction*>(doc->getObject(_simuData->probabilityDensityFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active probability density function feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputePDFValue(*this->getSimulationData(), x, dValue);         
    if (!returnResult)
    {
     Base::Console().Error("The computation of probability density function has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computePDFVectorX(vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLProbabilityDensityFunction* activefeature = static_cast<WindLabAPI::IrpsWLProbabilityDensityFunction*>(doc->getObject(_simuData->probabilityDensityFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active probability density function feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfIncrementOfVariableX.getValue());
    dValVector.resize(this->getSimulationData()->numberOfIncrementOfVariableX.getValue());
    bool returnResult = activefeature->ComputePDFVectorX(*this->getSimulationData(), dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of probability density function has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeRoughnessValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
     auto doc = App::GetApplication().getActiveDocument();
     if(!doc)
	    return false;
    WindLabAPI::IrpsWLRoughness* activefeature = static_cast<WindLabAPI::IrpsWLRoughness*>(doc->getObject(_simuData->roughness.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active roughness feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeRoughnessValue(*this->getSimulationData(), location, dTime, dValue);    
    if (!returnResult)
    {
     Base::Console().Error("The computation of the roughness value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeRoughnessVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLRoughness* activefeature = static_cast<WindLabAPI::IrpsWLRoughness*>(doc->getObject(_simuData->roughness.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active roughness feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeRoughnessVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the roughness vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeRoughnessVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLRoughness* activefeature = static_cast<WindLabAPI::IrpsWLRoughness*>(doc->getObject(_simuData->roughness.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active roughness feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeRoughnessVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the roughness vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeShearVelocityOfFlowValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLShearVelocityOfFlow* activefeature = static_cast<WindLabAPI::IrpsWLShearVelocityOfFlow*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active shear velocity feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeShearVelocityOfFlowValue(*this->getSimulationData(), location, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the roughness value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeShearVelocityOfFlowVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLShearVelocityOfFlow* activefeature = static_cast<WindLabAPI::IrpsWLShearVelocityOfFlow*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active shear velocity feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeShearVelocityOfFlowVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the shear velocity vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeShearVelocityOfFlowVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLShearVelocityOfFlow* activefeature = static_cast<WindLabAPI::IrpsWLShearVelocityOfFlow*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active shear velocity feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeShearVelocityOfFlowVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the shear vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeSkewnessValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLSkewness* activefeature = static_cast<WindLabAPI::IrpsWLSkewness*>(doc->getObject(_simuData->skewness.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active skewness feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeSkewnessValue(*this->getSimulationData(), location, dTime, dValue);        
    if (!returnResult)
    {
     Base::Console().Error("The computation of the skewness value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeSkewnessVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLSkewness* activefeature = static_cast<WindLabAPI::IrpsWLSkewness*>(doc->getObject(_simuData->skewness.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active skewness feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeSkewnessVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the skewness vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeSkewnessVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLSkewness* activefeature = static_cast<WindLabAPI::IrpsWLSkewness*>(doc->getObject(_simuData->skewness.getValue()));

    if (!activefeature) {
        Base::Console().Error("No valid active skewness feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeSkewnessVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the skewness vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeStandardDeviationValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLStandardDeviation* activefeature = static_cast<WindLabAPI::IrpsWLStandardDeviation*>(doc->getObject(_simuData->standardDeviation.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active standard deviation feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeStandardDeviationValue(*this->getSimulationData(), location, dTime, dValue);  
    if (!returnResult)
    {
     Base::Console().Error("The computation of the skewness value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeStandardDeviationVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLStandardDeviation* activefeature = static_cast<WindLabAPI::IrpsWLStandardDeviation*>(doc->getObject(_simuData->standardDeviation.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active standard deviation feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeStandardDeviationVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the standard deviation vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeStandardDeviationVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLStandardDeviation* activefeature = static_cast<WindLabAPI::IrpsWLStandardDeviation*>(doc->getObject(_simuData->standardDeviation.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active standard deviation feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeStandardDeviationVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the skewness vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool WindLabSimulation::computeTurbulenceIntensityValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLTurbulenceIntensity* activefeature = static_cast<WindLabAPI::IrpsWLTurbulenceIntensity*>(doc->getObject(_simuData->turbulenceIntensity.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active turbulence intensity feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeTurbulenceIntensityValue(*this->getSimulationData(), location, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the turbulence intensity value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeTurbulenceIntensityVectorP( const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLTurbulenceIntensity* activefeature = static_cast<WindLabAPI::IrpsWLTurbulenceIntensity*>(doc->getObject(_simuData->turbulenceIntensity.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active turbulence intensity feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeTurbulenceIntensityVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);

    if (!returnResult) {
        Base::Console().Error("The computation of the turbulence intensity vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeTurbulenceIntensityVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLTurbulenceIntensity* activefeature = static_cast<WindLabAPI::IrpsWLTurbulenceIntensity*>(doc->getObject(_simuData->turbulenceIntensity.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active turbulence intensity feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeTurbulenceIntensityVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the skewness vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeTurbulenceScaleValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLTurbulenceScale* activefeature = static_cast<WindLabAPI::IrpsWLTurbulenceScale*>(doc->getObject(_simuData->turbulenceScale.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active turbulence scale feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeTurbulenceScaleValue(*this->getSimulationData(), location, dTime, dValue);       
    if (!returnResult)
    {
     Base::Console().Error("The computation of the turbulence scale value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeTurbulenceScaleVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLTurbulenceScale* activefeature = static_cast<WindLabAPI::IrpsWLTurbulenceScale*>(doc->getObject(_simuData->turbulenceScale.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active turbulence scale feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeTurbulenceScaleVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the turbulence scale vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeTurbulenceScaleVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLTurbulenceScale* activefeature = static_cast<WindLabAPI::IrpsWLTurbulenceScale*>(doc->getObject(_simuData->turbulenceScale.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active turbulence scale feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeTurbulenceScaleVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the turbulence scale vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();

    return true;

}

bool WindLabSimulation::computeVarianceValue( const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLVariance* activefeature = static_cast<WindLabAPI::IrpsWLVariance*>(doc->getObject(_simuData->varianceFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active variance function feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeVarianceValue(*this->getSimulationData(),  location, dTime, dValue);       
    if (!returnResult)
    {
     Base::Console().Error("The computation of the variance value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeVarianceVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLVariance* activefeature = static_cast<WindLabAPI::IrpsWLVariance*>(doc->getObject(_simuData->varianceFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active variance function feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeVarianceVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the variance vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeVarianceVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
     if(!doc)
	    return false;
    WindLabAPI::IrpsWLVariance* activefeature = static_cast<WindLabAPI::IrpsWLVariance*>(doc->getObject(_simuData->varianceFunction.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active variance feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeVarianceVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the variance vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool WindLabSimulation::computeWavePassageEffectVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLWavePassageEffect* activefeature = static_cast<WindLabAPI::IrpsWLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active wave passage effect feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeWavePassageEffectVectorF(*this->getSimulationData(), locationJ, locationK, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of wave passage effect vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeWavePassageEffectVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLWavePassageEffect* activefeature = static_cast<WindLabAPI::IrpsWLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active wave passage effect feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeWavePassageEffectVectorT(*this->getSimulationData(), locationJ, locationK, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the wave passage effect vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeWavePassageEffectMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
     if(!doc)
	    return false;
    WindLabAPI::IrpsWLWavePassageEffect* activefeature = static_cast<WindLabAPI::IrpsWLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active wave passage effect feature found.\n");
        return false;
    }

    dCoherenceMatrix.resize(this->getSimulationData()->numberOfSpatialPosition.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeWavePassageEffectMatrixPP(*this->getSimulationData(), dFrequency, dTime, dCoherenceMatrix);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the coherence matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool WindLabSimulation::computeWavePassageEffectValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLWavePassageEffect* activefeature = static_cast<WindLabAPI::IrpsWLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active wave passage effect feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeWavePassageEffectValue(*this->getSimulationData(), locationJ, locationK, dFrequency, dTime, dValue);  
    if (!returnResult)
    {
     Base::Console().Error("The computation of the wave passage effect value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}


bool WindLabSimulation::simulate(mat &dVelocityArray, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLSimuMethod* activefeature = static_cast<WindLabAPI::IrpsWLSimuMethod*>(doc->getObject(_simuData->simulationMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active simulation method feature found.\n");
        return false;
    }
    dVelocityArray.resize(this->getSimulationData()->numberOfTimeIncrements.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue() + 1);
    dVelocityArray.setZero();

    bool returnResult = activefeature->Simulate(*this->getSimulationData(), dVelocityArray);

    if (!returnResult) {
     Base::Console().Error("The computation of the wind velocity matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();

    return true;

}

bool WindLabSimulation::simulateInLargeScaleMode(std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    WindLabAPI::IrpsWLSimuMethod* activefeature = static_cast<WindLabAPI::IrpsWLSimuMethod*>(doc->getObject(_simuData->simulationMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active simulation method feature found.\n");
        return false;
    }
    QString fineName = QString::fromLatin1("WindVelocity");
    bool returnResult = activefeature->SimulateInLargeScaleMode(*this->getSimulationData(), fineName);
    if (!returnResult) {
     Base::Console().Error("The computation of the wind velocity matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}


void WindLabSimulation::setActiveFeature(App::RPSFeature* feature)
{
    if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureCoherence::getClassTypeId())) {
        _simuData->coherenceFunction.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureCorrelation::getClassTypeId())) {
        _simuData->correlationFunction.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution::getClassTypeId())) {
        _simuData->cumulativeProbabilityDistribution.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureFrequencyDistribution::getClassTypeId())) {
        _simuData->frequencyDistribution.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureGustFactor::getClassTypeId())) {
        _simuData->gustFactor.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureKurtosis::getClassTypeId())) {
        _simuData->kurtosis.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureLocationDistribution::getClassTypeId())) {
        _simuData->spatialDistribution.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureMatrixTool::getClassTypeId())) {
        _simuData->matrixTool.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureMeanWind::getClassTypeId())) {
        _simuData->meanFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureModulation::getClassTypeId())) {
        _simuData->modulationFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeaturePeakFactor::getClassTypeId())) {
        _simuData->peakFactor.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureProbabilityDensityFunction::getClassTypeId())) {
        _simuData->probabilityDensityFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeaturePSDDecompositionMethod::getClassTypeId())) {
        _simuData->cpsdDecompositionMethod.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureRandomness::getClassTypeId())) {
        _simuData->randomnessProvider.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureRoughness::getClassTypeId())) {
        _simuData->roughness.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureShearVelocityOfFlow::getClassTypeId())) {
        _simuData->shearVelocityOfFlow.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureSimulationMethod::getClassTypeId())) {
        _simuData->simulationMethod.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureSkewness::getClassTypeId())) {
        _simuData->skewness.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureStandardDeviation::getClassTypeId())) {
        _simuData->standardDeviation.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureTableTool::getClassTypeId())) {
        _simuData->tableTool.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureTurbulenceIntensity::getClassTypeId())) {
        _simuData->turbulenceIntensity.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureTurbulenceScale::getClassTypeId())) {
        _simuData->turbulenceScale.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureUserDefinedRPSObject::getClassTypeId())) {
        _simuData->userDefinedRPSObject.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureVariance::getClassTypeId())) {
        _simuData->varianceFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureWavePassageEffect::getClassTypeId())) {
        _simuData->wavePassageEffect.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureXSpectrum::getClassTypeId())) {
        _simuData->alongWindSpectrumModel.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureYSpectrum::getClassTypeId())) {
        _simuData->acrossWindSpectrumModel.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeatureZSpectrum::getClassTypeId())) {
        _simuData->verticalWindSpectrumModel.setValue(feature->getNameInDocument());  
    }

}

App::RPSFeature* WindLabSimulation::getActiveFeature(const QString group)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;

    if (group == WindLab::WindLabUtils::objGroupCoherenceFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->coherenceFunction.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupCorrelationFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->correlationFunction.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupCumulativeProbabilityDistribution) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupFrequencyDistribution) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->frequencyDistribution.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupGustFactor) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->gustFactor.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupKurtosis) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->kurtosis.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupLocationDistribution) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->spatialDistribution.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupMatrixTool) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->matrixTool.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupMeanWindProfile) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->meanFunction.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupModulationFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->modulationFunction.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupPeakFactor) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->peakFactor.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupProbabilityDensityFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->probabilityDensityFunction.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupSpectrumDecompositionMethod) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupRandomnessProvider) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->randomnessProvider.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupRoughness) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->roughness.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupShearVelocityOfFlow) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupSimulationMethod) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->simulationMethod.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupStandardDeviation) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->standardDeviation.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupTableTool) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->tableTool.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceIntensity) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->turbulenceIntensity.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupTurbulenceScale) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->turbulenceScale.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupUserDefinedRPSObject) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->userDefinedRPSObject.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupVariance) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->varianceFunction.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupWavePassageEffect) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->wavePassageEffect.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupAlongWindSpectrum) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->alongWindSpectrumModel.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupAcrossWindSpectrum) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->acrossWindSpectrumModel.getValue()));  
    }
    else if (group == WindLab::WindLabUtils::objGroupVerticalWindSpectrum) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->verticalWindSpectrumModel.getValue()));  
    }
}

std::vector<App::RPSFeature*> WindLabSimulation::getAllFeatures(const QString group)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return std::vector<App::RPSFeature*>();
    std::vector<DocumentObject*> docObjects = doc->getObjects();
    std::vector<App::RPSFeature*> featureList;
    for (std::vector<DocumentObject*>::iterator j = docObjects.begin(); j != docObjects.end(); ++j) {
        if ((*j)->getTypeId().isDerivedFrom(getRPSType(group))) {
            featureList.push_back(static_cast<App::RPSFeature*>(*j));
        }
    }
    return featureList;
}

App::DocumentObject* WindLabSimulation::getActiveCoherence()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->coherenceFunction.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveCorrelation()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->correlationFunction.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveCumulativeProbabilityDistribution()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveFrequencyDistribution()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->frequencyDistribution.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveGustFactor()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->gustFactor.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveKurtosis()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->kurtosis.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveLocationDistribution()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->spatialDistribution.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveMeanWind()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->meanFunction.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveModulation()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->modulationFunction.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActivePeakFactor()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->peakFactor.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveProbabilityDensityFunction()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->probabilityDensityFunction.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActivePSDDecompositionMethod()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->cpsdDecompositionMethod.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveRandomness()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->randomnessProvider.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveRoughness()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->roughness.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveShearVelocityOfFlow()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->shearVelocityOfFlow.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveSimulationMethod()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->simulationMethod.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveSkewness()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->skewness.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveStandardDeviation()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->standardDeviation.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveTurbulenceIntensity()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->turbulenceIntensity.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveTurbulenceScale()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->turbulenceScale.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveUserDefinedRPSObject()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->userDefinedRPSObject.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveVariance()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->varianceFunction.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveWavePassageEffect()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->wavePassageEffect.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveXSpectrum()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->alongWindSpectrumModel.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveYSpectrum()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->acrossWindSpectrumModel.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveZSpectrum()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->verticalWindSpectrumModel.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveMatrixTool()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->matrixTool.getValue());
    return activeFeature;
}
App::DocumentObject* WindLabSimulation::getActiveTableTool()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->tableTool.getValue());
    return activeFeature;
}

App::DocumentObject*  WindLabSimulation::addFeature(const std::string featureName, const std::string simulationName, const std::string featureTypeName, const std::string featureGroup)
{
    Base::Type type = getRPSType(QString::fromStdString(featureGroup));
    
    //create the feature
	WindLabAPI::WindLabFeature* newFeature = this->createFeature(type, featureTypeName, featureName);

	if (!newFeature)
		return nullptr;

	//set the feature properties
	auto featureProperties = this->GetWindLabPluggedWindLabFeatureDescription(QString::fromLatin1(featureGroup.c_str()), QString::fromLatin1(featureTypeName.c_str()));
    newFeature->FeatureGroup.setValue(featureGroup);
    newFeature->FeatureType.setValue(featureTypeName);
    newFeature->Author.setValue(featureProperties->Author.getValue());
    newFeature->PublicationTopic.setValue(featureProperties->PublicationTitle.getValue());
    newFeature->PublicationDate.setValue(featureProperties->PublicationDate.getValue());
    newFeature->LinkToPublication.setValue(featureProperties->PublicationLink.getValue());
    newFeature->PublicationAuthor.setValue(featureProperties->PublicationAuthor.getValue());
    newFeature->Version.setValue(featureProperties->Version.getValue());
    newFeature->IsStationary.setValue(featureProperties->Stationarity.getValue());
    newFeature->PluginName.setValue(featureProperties->PluginName.getValue());
    newFeature->PluginVersion.setValue(featureProperties->PluginVersion.getValue());
    newFeature->APIVersion.setValue(featureProperties->APIVersion.getValue());
    newFeature->ReleaseDate.setValue(featureProperties->ReleaseDate.getValue());
	newFeature->Simulation.setValue(this->getNameInDocument());

    this->setActiveFeature(newFeature);
	App::DocumentObjectGroup* group = static_cast<App::DocumentObjectGroup*>(static_cast<App::DocumentObject*>(this));
    newFeature->recomputeFeature();
	group->addObject(newFeature);
    this->setEnums(type);
    App::GetApplication().getActiveDocument()->recompute();

    return newFeature;
    }

// Dummy class 'DocumentObject' in WindLab namespace
PROPERTY_SOURCE_ABSTRACT(WindLab::DocumentObject, App::DocumentObject)
// Python feature ---------------------------------------------------------

namespace App
{
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(WindLab::WindLabSimulationPython, WindLab::WindLabSimulation)
template<>
const char* WindLab::WindLabSimulationPython::getViewProviderName() const
{
    return "WindLabGui::ViewProviderWindLabSimulationPython";
}

// explicit template instantiation
template class WindLabExport FeaturePythonT<WindLab::WindLabSimulation>;
}  // namespace App

// ---------------------------------------------------------

namespace App
{
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(WindLab::FeaturePython, WindLab::DocumentObject)
template<>
const char* WindLab::FeaturePython::getViewProviderName() const
{
    return "Gui::ViewProviderFeaturePython";
}
template<>
PyObject* WindLab::FeaturePython::getPyObject()
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new App::FeaturePythonPyT<App::DocumentObjectPy>(this), true);
    }
    return Py::new_reference_to(PythonObject);
}
// explicit template instantiation
template class WindLabExport FeaturePythonT<WindLab::DocumentObject>;
/// @endcond
}  // namespace App
