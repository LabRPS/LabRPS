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

#include "SeaLabSimulation.h"
#include "SealabUtils.h"
#include <Mod/SeaLabAPI/App/SeaLabFeatureDescription.h>
#include <Mod/SeaLabAPI/App/RPSSeaLabAPI.h>
#include <App/Application.h>
#include <App/Document.h>
#include <App/RPSpluginManager.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureCoherence.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureCorrelation.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureCumulativeProbabilityDistribution.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureFrequencyDistribution.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureKurtosis.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureLocationDistribution.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureMatrixTool.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureModulation.h>
#include <Mod/SeaLabAPI/App/SeaLabFeaturePSDDecompositionMethod.h>
#include <Mod/SeaLabAPI/App/SeaLabFeaturePeakFactor.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureProbabilityDensityFunction.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureRandomness.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureShearVelocityOfFlow.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureSimulationMethod.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureSkewness.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureStandardDeviation.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureTableTool.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureUserDefinedRPSObject.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureVariance.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureWavePassageEffect.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureSpectrum.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureMeanAcceleration.h>
#include <Base/Console.h>
#include <Mod/SeaLab/App/SeaLabSimulationPy.h>

using namespace App;
using namespace SeaLab;
using namespace SeaLabAPI;

PROPERTY_SOURCE(SeaLab::SeaLabSimulation, App::Simulation)

SeaLabSimulation::SeaLabSimulation()
{
    _simuData = new SeaLabAPI::SeaLabSimulationData();
   
    Base::Uuid id;
    ADD_PROPERTY_TYPE(Uid, (id), 0, App::Prop_None, "UUID of the simulation"); //not is use yet

    static const char* datagroup = "Basic Data";
    ADD_PROPERTY_TYPE(NumberOfSample, (1), datagroup, Prop_None,"This is the number of ground field sample in a simulation.");
    ADD_PROPERTY_TYPE(NumberOfTimeLags, (512), datagroup, Prop_None,"Number of time lags need for temporal correlation");
    ADD_PROPERTY_TYPE(Stationarity, (true), datagroup, Prop_None,"This specifies whether the simulated ground motion is stationary or not.");
    ADD_PROPERTY_TYPE(Gaussianity, (true), datagroup, Prop_None,"This specifies whether the simulated ground motion is gaussian or not.");
    ADD_PROPERTY_TYPE(ComparisonMode, (false), datagroup, Prop_None,"This specifies whether we are in comparison mode or not.");
    ADD_PROPERTY_TYPE(LargeScaleSimulationMode, (false), datagroup, Prop_None,"This specifies whether we are in large scale simulation mode or not.");
    ADD_PROPERTY_TYPE(IsSimulationSuccessful, (false), datagroup, Prop_None,"This specifies whether the simulation was successful or not.");
    ADD_PROPERTY_TYPE(IsInterruptionRequested, (false), datagroup, Prop_None,"This specifies whether the simulation has been interrupted or not.");
    ADD_PROPERTY_TYPE(UniformModulation, (true), datagroup, Prop_None,"This specifies whether a non stataionary ground motion is uniformly modulated or not.");

    static const char* locationgroup = "Location Distribution";
    ADD_PROPERTY_TYPE(NumberOfProcess, (3), locationgroup, App::Prop_None,"The number of simulation point which is the number of ground motion processes in a sample");
    ADD_PROPERTY_TYPE(LocationIndexJ, (1), locationgroup, Prop_None,"The index of the a given ground motion process in a ground motion field at a location J");
    ADD_PROPERTY_TYPE(LocationIndexK, (1), locationgroup, Prop_None,"The index of the a given ground motion process in a ground motion field at a location K");

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

    static const char* featuregroup = "Sealab Features";
    static const char* someEnums[] = {"<None>", nullptr};

    ADD_PROPERTY_TYPE(SpatialDistribution, ((long int)0), featuregroup, Prop_None,"Active location distribution name");
    ADD_PROPERTY_TYPE(MeanFunction, ((long int)0), featuregroup, Prop_None,"Active mean acceleration name");
    ADD_PROPERTY_TYPE(SpectrumModel, ((long int)0), featuregroup, Prop_None,"Active spectrum model name");
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
    ADD_PROPERTY_TYPE(Kurtosis, ((long int)0), featuregroup, Prop_None, "Active kurtosis name");
    ADD_PROPERTY_TYPE(PeakFactor, ((long int)0), featuregroup, Prop_None,"Active peak factor name");
    ADD_PROPERTY_TYPE(ProbabilityDensityFunction, ((long int)0), featuregroup, Prop_None,"Active PDF name");
    ADD_PROPERTY_TYPE(ShearVelocityOfFlow, ((long int)0), featuregroup, Prop_None,"Active shear velocity name");
    ADD_PROPERTY_TYPE(Skewness, ((long int)0), featuregroup, Prop_None, "Active skewness name");
    ADD_PROPERTY_TYPE(StandardDeviation, ((long int)0), featuregroup, Prop_None,"Active standard deviation name");
    ADD_PROPERTY_TYPE(Variance, ((long int)0), featuregroup, Prop_None, "Active variance name");
    ADD_PROPERTY_TYPE(WavePassageEffect, ((long int)0), featuregroup, Prop_None,"Active wave passage name");

    ADD_PROPERTY_TYPE(NumberOfIncrementOfVariableX, (101), "Variable X", Prop_None, "The number of increments for the variable x");
	ADD_PROPERTY_TYPE(IndexOfVariableX, (1), "Variable X", Prop_None, "This current index of the variable x.");
	ADD_PROPERTY_TYPE(IncrementOfVariableX, (0.1), "Variable X", Prop_None, "This is the variable x increment value");
	ADD_PROPERTY_TYPE(MinVariableX, (-5.00), "Variable X", Prop_None, "This is the minimum x variable value");

    ADD_PROPERTY_TYPE(Phenomenon, ("Sea Surface"), 0, Prop_ReadOnly, "The random phenonenon name");
    ADD_PROPERTY_TYPE(WorkingDirectoryPath, (Application::getHomePath()), 0, Prop_None, "The working directory path.");


    SpatialDistribution.setEnums(someEnums);
    ShearVelocity.setEnums(someEnums);
    MeanFunction.setEnums(someEnums);
    SpectrumModel.setEnums(someEnums);
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
    Kurtosis.setEnums(someEnums);
    PeakFactor.setEnums(someEnums);
    ProbabilityDensityFunction.setEnums(someEnums);
    ShearVelocityOfFlow.setEnums(someEnums);
    Skewness.setEnums(someEnums);
    StandardDeviation.setEnums(someEnums);
    Variance.setEnums(someEnums);
    WavePassageEffect.setEnums(someEnums);

    static const char* directions[] = {"X", "Y", "Z", nullptr};
    ADD_PROPERTY_TYPE(Direction, ((long int)0), datagroup, Prop_None, "The ground motion direction");
    Direction.setEnums(directions);
}

SeaLabSimulation::~SeaLabSimulation() { delete _simuData; }

void SeaLabSimulation::handleChangedPropertyName(Base::XMLReader& reader, const char* TypeName,            const char* PropName)
{
    Base::Type type = Base::Type::fromName(TypeName);
    App::DocumentObjectGroup::handleChangedPropertyName(reader, TypeName, PropName);
}

void SeaLabSimulation::updateSimulationData()
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
    _simuData->spectrumModel.setValue(this->SpectrumModel.getValueAsString());
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
    _simuData->kurtosis.setValue(this->Kurtosis.getValueAsString());
    _simuData->peakFactor.setValue(this->PeakFactor.getValueAsString());
    _simuData->probabilityDensityFunction.setValue(this->ProbabilityDensityFunction.getValueAsString());
    _simuData->shearVelocityOfFlow.setValue(this->ShearVelocityOfFlow.getValueAsString());
    _simuData->skewness.setValue(this->Skewness.getValueAsString());
    _simuData->standardDeviation.setValue(this->StandardDeviation.getValueAsString());
    _simuData->variance.setValue(this->Variance.getValueAsString());
    _simuData->wavePassageEffect.setValue(this->WavePassageEffect.getValueAsString());
    _simuData->direction.setValue(this->Direction.getValue());
    _simuData->numberOfIncrementOfVariableX.setValue(this->NumberOfIncrementOfVariableX.getValue());
    _simuData->indexOfVariableX.setValue(this->IndexOfVariableX.getValue());
    _simuData->incrementOfVariableX.setValue(this->IncrementOfVariableX.getValue());
    _simuData->minVariableX.setValue(this->MinVariableX.getValue());
}

bool SeaLabSimulation::run() { return false; }

bool SeaLabSimulation::stop() { return false; }

std::string SeaLabSimulation::getPhenomenonName() const
{
    return SeaLab::SeaLabUtils::rpsPhenomenonWindVelocity.toUtf8().constData();
}

std::string SeaLabSimulation::workbenchName() const { return "SeaLab"; }

void SeaLabSimulation::setSimulationData(SeaLabAPI::SeaLabSimulationData* simuData)
{
    _simuData = simuData;
}

SeaLabAPI::SeaLabSimulationData* SeaLabSimulation::getSimulationData() const { return _simuData; }

void SeaLabSimulation::seaLabFeatureInitalSetting(QString group, QString currentSelected)
{
    if (!_simuData)
        return;

    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return;

    if (group == SeaLab::SeaLabUtils::objGroupCoherenceFunction) {
        SeaLabAPI::IrpsSeLCoherence* activefeature = static_cast<SeaLabAPI::IrpsSeLCoherence*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

        auto simuData = getSimulationData();
        if (simuData)
    activefeature->OnInitialSetting(*simuData);

    }
    else if (group == SeaLab::SeaLabUtils::objGroupCorrelationFunction) {
        SeaLabAPI::IrpsSeLCorrelation* activefeature = static_cast<SeaLabAPI::IrpsSeLCorrelation*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution) {
        SeaLabAPI::IrpsSeLCumulativeProbabilityDistribution* activefeature =
    static_cast<SeaLabAPI::IrpsSeLCumulativeProbabilityDistribution*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupFrequencyDistribution) {
        SeaLabAPI::IrpsSeLFrequencyDistribution* activefeature =
    static_cast<SeaLabAPI::IrpsSeLFrequencyDistribution*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupKurtosis) {
        SeaLabAPI::IrpsSeLKurtosis* activefeature = static_cast<SeaLabAPI::IrpsSeLKurtosis*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupLocationDistribution) {
        SeaLabAPI::IrpsSeLLocationDistribution* activefeature =
    static_cast<SeaLabAPI::IrpsSeLLocationDistribution*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMatrixTool) {
        SeaLabAPI::IrpsSeLMatrixTool* activefeature = static_cast<SeaLabAPI::IrpsSeLMatrixTool*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile) {
        SeaLabAPI::IrpsSeLMeanAcceleration* activefeature = static_cast<SeaLabAPI::IrpsSeLMeanAcceleration*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupModulationFunction) {
        SeaLabAPI::IrpsSeLModulation* activefeature = static_cast<SeaLabAPI::IrpsSeLModulation*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupPeakFactor) {
        SeaLabAPI::IrpsSeLPeakFactor* activefeature = static_cast<SeaLabAPI::IrpsSeLPeakFactor*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction) {
        SeaLabAPI::IrpsSeLProbabilityDensityFunction* activefeature =
    static_cast<SeaLabAPI::IrpsSeLProbabilityDensityFunction*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod) {
        SeaLabAPI::IrpsSeLPSDdecompositionMethod* activefeature =
    static_cast<SeaLabAPI::IrpsSeLPSDdecompositionMethod*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupRandomnessProvider) {
        SeaLabAPI::IrpsSeLRandomness* activefeature = static_cast<SeaLabAPI::IrpsSeLRandomness*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow) {
        SeaLabAPI::IrpsSeLShearVelocityOfFlow* activefeature =
    static_cast<SeaLabAPI::IrpsSeLShearVelocityOfFlow*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSimulationMethod) {
        SeaLabAPI::IrpsSeLSimulationMethod* activefeature = static_cast<SeaLabAPI::IrpsSeLSimulationMethod*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSimulationMethod) {
        SeaLabAPI::IrpsSeLSkewness* activefeature = static_cast<SeaLabAPI::IrpsSeLSkewness*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupStandardDeviation) {
        SeaLabAPI::IrpsSeLStandardDeviation* activefeature =
    static_cast<SeaLabAPI::IrpsSeLStandardDeviation*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupTableTool) {
        SeaLabAPI::IrpsSeLTableTool* activefeature = static_cast<SeaLabAPI::IrpsSeLTableTool*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject) {
        SeaLabAPI::IrpsSeLUserDefinedRPSObject* activefeature =
    static_cast<SeaLabAPI::IrpsSeLUserDefinedRPSObject*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupVariance) {
        SeaLabAPI::IrpsSeLVariance* activefeature = static_cast<SeaLabAPI::IrpsSeLVariance*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupWavePassageEffect) {
        SeaLabAPI::IrpsSeLWavePassageEffect* activefeature =
    static_cast<SeaLabAPI::IrpsSeLWavePassageEffect*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrum) {
        SeaLabAPI::IrpsSeLSpectrum* activefeature = static_cast<SeaLabAPI::IrpsSeLSpectrum*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
}

QStringList SeaLabSimulation::findAllPluggedSeaLabFeatures(QString group)
{
    QStringList theList;
    theList.append(QString::fromLatin1("<None>"));
    if (group == SeaLab::SeaLabUtils::objGroupLocationDistribution) {
        typedef IrpsSeLLocationDistribution* (*CreateLocDistrCallback)();
        std::map<const std::string, CreateLocDistrCallback>::iterator locIt;
        for (locIt = CrpsLocationDistributionFactory::GetObjectNamesMap().begin();
     locIt != CrpsLocationDistributionFactory::GetObjectNamesMap().end(); ++locIt) {
    theList.append(QString::fromUtf8(locIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile) {
        typedef IrpsSeLMeanAcceleration* (*CreateMeanCallback)();
        std::map<const std::string, CreateMeanCallback>::iterator meanIt;
        for (meanIt = CrpsMeanFactory::GetObjectNamesMap().begin();
     meanIt != CrpsMeanFactory::GetObjectNamesMap().end(); ++meanIt) {
    theList.append(QString::fromUtf8(meanIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrum) {
        typedef IrpsSeLSpectrum* (*CreateXSpectrumCallback)();
        std::map<const std::string, CreateXSpectrumCallback>::iterator psdIt;
        for (psdIt = CrpsSpectrumFactory::GetObjectNamesMap().begin();
     psdIt != CrpsSpectrumFactory::GetObjectNamesMap().end(); ++psdIt) {
    theList.append(QString::fromUtf8(psdIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod) {

        typedef IrpsSeLPSDdecompositionMethod* (*CreatePSDdecomMethodCallback)();
        std::map<const std::string, CreatePSDdecomMethodCallback>::iterator psdDecIt;
        for (psdDecIt = CrpsPSDdecomMethodFactory::GetObjectNamesMap().begin();
     psdDecIt != CrpsPSDdecomMethodFactory::GetObjectNamesMap().end(); ++psdDecIt) {
    theList.append(QString::fromUtf8(psdDecIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCoherenceFunction) {
        typedef IrpsSeLCoherence* (*CreateCoherenceCallback)();
        std::map<const std::string, CreateCoherenceCallback>::iterator cohIt;
        for (cohIt = CrpsCoherenceFactory::GetObjectNamesMap().begin();
     cohIt != CrpsCoherenceFactory::GetObjectNamesMap().end(); ++cohIt) {
    theList.append(QString::fromUtf8(cohIt->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSimulationMethod) {
        typedef IrpsSeLSimulationMethod* (*CreateSimuMethodCallback)();
        std::map<const std::string, CreateSimuMethodCallback>::iterator simuMethIt;
        for (simuMethIt = CrpsSimuMethodFactory::GetObjectNamesMap().begin();
     simuMethIt != CrpsSimuMethodFactory::GetObjectNamesMap().end(); ++simuMethIt) {
    theList.append(QString::fromUtf8(simuMethIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupFrequencyDistribution) {
        typedef IrpsSeLFrequencyDistribution* (*CreateFrequencyDistributionCallback)();
        std::map<const std::string, CreateFrequencyDistributionCallback>::iterator freqDistrIt;
        for (freqDistrIt = CrpsFrequencyDistributionFactory::GetObjectNamesMap().begin();
     freqDistrIt != CrpsFrequencyDistributionFactory::GetObjectNamesMap().end();
     ++freqDistrIt) {
    theList.append(QString::fromUtf8(freqDistrIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupRandomnessProvider) {

        typedef IrpsSeLRandomness* (*CreateRandomnessCallback)();
        std::map<const std::string, CreateRandomnessCallback>::iterator randIt;
        for (randIt = CrpsRandomnessFactory::GetObjectNamesMap().begin();
     randIt != CrpsRandomnessFactory::GetObjectNamesMap().end(); ++randIt) {
    theList.append(QString::fromUtf8(randIt->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupModulationFunction) {

        typedef IrpsSeLModulation* (*CreateModulationCallback)();
        std::map<const std::string, CreateModulationCallback>::iterator cohIt;
        for (cohIt = CrpsModulationFactory::GetObjectNamesMap().begin();
     cohIt != CrpsModulationFactory::GetObjectNamesMap().end(); ++cohIt) {
    theList.append(QString::fromUtf8(cohIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCorrelationFunction) {

        typedef IrpsSeLCorrelation* (*CreateCorrelationCallback)();
        std::map<const std::string, CreateCorrelationCallback>::iterator corrIt;
        for (corrIt = CrpsCorrelationFactory::GetObjectNamesMap().begin();
     corrIt != CrpsCorrelationFactory::GetObjectNamesMap().end(); ++corrIt) {
    theList.append(QString::fromUtf8(corrIt->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupTableTool) {

        typedef IrpsSeLTableTool* (*CreateTableToolCallback)();
        std::map<const std::string, CreateTableToolCallback>::iterator it;
        for (it = CrpsTableToolFactory::GetObjectNamesMap().begin();
     it != CrpsTableToolFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMatrixTool) {

        typedef IrpsSeLMatrixTool* (*CreateMatrixToolCallback)();
        std::map<const std::string, CreateMatrixToolCallback>::iterator it;
        for (it = CrpsMatrixToolFactory::GetObjectNamesMap().begin();
     it != CrpsMatrixToolFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution) {

        typedef IrpsSeLCumulativeProbabilityDistribution* (
    *CreateCumulativeProbabilityDistributionCallback)();
        std::map<const std::string, CreateCumulativeProbabilityDistributionCallback>::iterator it;
        for (it = CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().begin();
     it != CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupKurtosis) {

        typedef IrpsSeLKurtosis* (*CreateKurtosisCallback)();
        std::map<const std::string, CreateKurtosisCallback>::iterator it;
        for (it = CrpsKurtosisFactory::GetObjectNamesMap().begin();
     it != CrpsKurtosisFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupPeakFactor) {

        typedef IrpsSeLPeakFactor* (*CreatePeakFactorCallback)();
        std::map<const std::string, CreatePeakFactorCallback>::iterator it;
        for (it = CrpsPeakFactorFactory::GetObjectNamesMap().begin();
     it != CrpsPeakFactorFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction) {

        typedef IrpsSeLProbabilityDensityFunction* (*CreateProbabilityDensityFunctionCallback)();
        std::map<const std::string, CreateProbabilityDensityFunctionCallback>::iterator it;
        for (it = CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().begin();
     it != CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow) {

        typedef IrpsSeLShearVelocityOfFlow* (*CreateShearVelocityOfFlowCallback)();
        std::map<const std::string, CreateShearVelocityOfFlowCallback>::iterator it;
        for (it = CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().begin();
     it != CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSkewness) {

        typedef IrpsSeLSkewness* (*CreateSkewnessCallback)();
        std::map<const std::string, CreateSkewnessCallback>::iterator it;
        for (it = CrpsSkewnessFactory::GetObjectNamesMap().begin();
     it != CrpsSkewnessFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupStandardDeviation) {

        typedef IrpsSeLStandardDeviation* (*CreateStandardDeviationCallback)();
        std::map<const std::string, CreateStandardDeviationCallback>::iterator it;
        for (it = CrpsStandardDeviationFactory::GetObjectNamesMap().begin();
     it != CrpsStandardDeviationFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupVariance) {

        typedef IrpsSeLVariance* (*CreateVarianceCallback)();
        std::map<const std::string, CreateVarianceCallback>::iterator it;
        for (it = CrpsVarianceFactory::GetObjectNamesMap().begin();
     it != CrpsVarianceFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupWavePassageEffect) {

        typedef IrpsSeLWavePassageEffect* (*CreateWavePassageEffectCallback)();
        std::map<const std::string, CreateWavePassageEffectCallback>::iterator it;
        for (it = CrpsWavePassageEffectFactory::GetObjectNamesMap().begin();
     it != CrpsWavePassageEffectFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject) {

        typedef IrpsSeLUserDefinedRPSObject* (*CreateUserDefinedRPSObjectCallback)();
        std::map<const std::string, CreateUserDefinedRPSObjectCallback>::iterator it;
        for (it = CrpsUserDefinedRPSObjectFactory::GetObjectNamesMap().begin();
     it != CrpsUserDefinedRPSObjectFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }

    return theList;
}

QStringList SeaLabSimulation::findAllFeatureMethods(QString group)
{
    QStringList theList;
    theList.append(QString::fromLatin1("<None>"));
    if (group == SeaLab::SeaLabUtils::objGroupLocationDistribution) {
        theList.append(SeaLab::SeaLabUtils::ComputeLocationCoordinateMatrixP3);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile) {
        theList.append(SeaLab::SeaLabUtils::ComputeMeanAccelerationValue);
        theList.append(SeaLab::SeaLabUtils::ComputeMeanAccelerationVectorP);
        theList.append(SeaLab::SeaLabUtils::ComputeMeanAccelerationVectorT);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrum) {
        theList.append(SeaLab::SeaLabUtils::ComputeCrossSpectrumValue);
        theList.append(SeaLab::SeaLabUtils::ComputeCrossSpectrumVectorF);
        theList.append(SeaLab::SeaLabUtils::ComputeCrossSpectrumVectorT);
        theList.append(SeaLab::SeaLabUtils::ComputeCrossSpectrumMatrixPP);
        theList.append(SeaLab::SeaLabUtils::ComputeAutoSpectrumValue);
        theList.append(SeaLab::SeaLabUtils::ComputeAutoSpectrumVectorF);
        theList.append(SeaLab::SeaLabUtils::ComputeAutoSpectrumVectorT);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod) {

        theList.append(SeaLab::SeaLabUtils::ComputeDecomposedPSDValue);
        theList.append(SeaLab::SeaLabUtils::ComputeDecomposedCrossSpectrumVectorF);
        theList.append(SeaLab::SeaLabUtils::ComputeDecomposedCrossSpectrumVectorT);
        theList.append(SeaLab::SeaLabUtils::ComputeDecomposedCrossSpectrumMatrixPP);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCoherenceFunction) {
        theList.append(SeaLab::SeaLabUtils::ComputeCrossCoherenceValue);
        theList.append(SeaLab::SeaLabUtils::ComputeCrossCoherenceVectorF);
        theList.append(SeaLab::SeaLabUtils::ComputeCrossCoherenceVectorT);
        theList.append(SeaLab::SeaLabUtils::ComputeCrossCoherenceMatrixPP);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSimulationMethod) {
        theList.append(SeaLab::SeaLabUtils::Simulate);
        theList.append(SeaLab::SeaLabUtils::SimulateInLargeScaleMode);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupFrequencyDistribution) {
        theList.append(SeaLab::SeaLabUtils::ComputeFrequencyValue);
        theList.append(SeaLab::SeaLabUtils::ComputeFrequenciesVectorF);
        theList.append(SeaLab::SeaLabUtils::ComputeFrequenciesMatrixFP);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupRandomnessProvider) {
        theList.append(SeaLab::SeaLabUtils::ComputeRandomValue);
        theList.append(SeaLab::SeaLabUtils::GenerateRandomMatrixFP);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupModulationFunction) {
        theList.append(SeaLab::SeaLabUtils::ComputeModulationValue);
        theList.append(SeaLab::SeaLabUtils::ComputeModulationVectorP);
        theList.append(SeaLab::SeaLabUtils::ComputeModulationVectorT);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCorrelationFunction) {
        theList.append(SeaLab::SeaLabUtils::ComputeCrossCorrelationValue);
        theList.append(SeaLab::SeaLabUtils::ComputeCrossCorrelationVectorT);
        theList.append(SeaLab::SeaLabUtils::ComputeCrossCorrelationMatrixPP);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupTableTool) {
        theList.append(SeaLab::SeaLabUtils::TableToolCompute);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMatrixTool) {
        theList.append(SeaLab::SeaLabUtils::MatrixToolCompute);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution) {
        theList.append(SeaLab::SeaLabUtils::ComputeCPDValue);
        theList.append(SeaLab::SeaLabUtils::ComputeCPDVectorX);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupKurtosis) {
        theList.append(SeaLab::SeaLabUtils::ComputeKurtosisValue);
        theList.append(SeaLab::SeaLabUtils::ComputeKurtosisVectorP);
        theList.append(SeaLab::SeaLabUtils::ComputeKurtosisVectorT);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupPeakFactor) {
        theList.append(SeaLab::SeaLabUtils::ComputePeakFactorValue);
        theList.append(SeaLab::SeaLabUtils::ComputePeakFactorVectorP);
        theList.append(SeaLab::SeaLabUtils::ComputePeakFactorVectorT);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction) {
        theList.append(SeaLab::SeaLabUtils::ComputePDFValue);
        theList.append(SeaLab::SeaLabUtils::ComputePDFVectorX);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow) {
        theList.append(SeaLab::SeaLabUtils::ComputeShearVelocityOfFlowValue);
        theList.append(SeaLab::SeaLabUtils::ComputeShearVelocityOfFlowVectorP);
        theList.append(SeaLab::SeaLabUtils::ComputeShearVelocityOfFlowVectorT);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSkewness) {
        theList.append(SeaLab::SeaLabUtils::ComputeSkewnessValue);
        theList.append(SeaLab::SeaLabUtils::ComputeSkewnessVectorP);
        theList.append(SeaLab::SeaLabUtils::ComputeSkewnessVectorT);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupStandardDeviation) {
        theList.append(SeaLab::SeaLabUtils::ComputeStandardDeviationValue);
        theList.append(SeaLab::SeaLabUtils::ComputeStandardDeviationVectorP);
        theList.append(SeaLab::SeaLabUtils::ComputeStandardDeviationVectorT);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupVariance) {
        theList.append(SeaLab::SeaLabUtils::ComputeVarianceValue);
        theList.append(SeaLab::SeaLabUtils::ComputeVarianceVectorP);
        theList.append(SeaLab::SeaLabUtils::ComputeVarianceVectorT);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupWavePassageEffect) {
        theList.append(SeaLab::SeaLabUtils::ComputeWavePassageEffectValue);
        theList.append(SeaLab::SeaLabUtils::ComputeWavePassageEffectVectorF);
        theList.append(SeaLab::SeaLabUtils::ComputeWavePassageEffectVectorT);
        theList.append(SeaLab::SeaLabUtils::ComputeWavePassageEffectMatrixPP);
        return theList;
    }
    else if (group == SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject) {
        theList.append(SeaLab::SeaLabUtils::UserDefinedRPSObjectCompute);
        return theList;
    }

    return theList;
}

SeaLabAPI::SeaLabFeature* SeaLabSimulation::createFeature(Base::Type type, std::string pluggedObjectTypeName, std::string name)
{
    //get the active document
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;

    //make unique name for this new feature in the active document (its parent document)
    std::string uniqueName = doc->getUniqueObjectName(name.c_str());

    //now figure out the feature type and create it
    if (type == SeaLabAPI::SeaLabFeatureCoherence::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureCoherence* newFeature =  CrpsCoherenceFactory::BuildObject(pluggedObjectTypeName);
        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureCorrelation::getClassTypeId()) {
    // Build an object
    SeaLabAPI::SeaLabFeatureCorrelation* newFeature = CrpsCorrelationFactory::BuildObject(pluggedObjectTypeName);
    if (NULL == newFeature) {
    return nullptr;
    }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureCumulativeProbabilityDistribution::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureCumulativeProbabilityDistribution* newFeature = CrpsCumulativeProbabilityDistributionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureFrequencyDistribution::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureFrequencyDistribution* newFeature = CrpsFrequencyDistributionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureKurtosis::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureKurtosis* newFeature = CrpsKurtosisFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureLocationDistribution::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureLocationDistribution* newFeature = CrpsLocationDistributionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureMatrixTool::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureMatrixTool* newFeature = CrpsMatrixToolFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureMeanAcceleration::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureMeanAcceleration* newFeature = CrpsMeanFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureModulation::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureModulation* newFeature =CrpsModulationFactory::BuildObject(pluggedObjectTypeName);
        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeaturePeakFactor::getClassTypeId()) {
        SeaLabAPI::SeaLabFeaturePeakFactor* newFeature = CrpsPeakFactorFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureProbabilityDensityFunction::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureProbabilityDensityFunction* newFeature = CrpsProbabilityDensityFunctionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeaturePSDDecompositionMethod::getClassTypeId()) {
        SeaLabAPI::SeaLabFeaturePSDDecompositionMethod* newFeature =  CrpsPSDdecomMethodFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureRandomness::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureRandomness* newFeature =  CrpsRandomnessFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureShearVelocityOfFlow::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureShearVelocityOfFlow* newFeature = CrpsShearVelocityOfFlowFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureSimulationMethod::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureSimulationMethod* newFeature = CrpsSimuMethodFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureSkewness::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureSkewness* newFeature = CrpsSkewnessFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureStandardDeviation::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureStandardDeviation* newFeature = CrpsStandardDeviationFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());
        return newFeature;

    }
    else if (type == SeaLabAPI::SeaLabFeatureTableTool::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureTableTool* newFeature = CrpsTableToolFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureUserDefinedRPSObject::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureUserDefinedRPSObject* newFeature =  CrpsUserDefinedRPSObjectFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureVariance::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureVariance* newFeature = CrpsVarianceFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureWavePassageEffect::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureWavePassageEffect* newFeature = CrpsWavePassageEffectFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeaLabAPI::SeaLabFeatureSpectrum::getClassTypeId()) {
        SeaLabAPI::SeaLabFeatureSpectrum* newFeature = CrpsSpectrumFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }

}

void SeaLabSimulation::setEnums(Base::Type type)
{

    if (type == SeaLabAPI::SeaLabFeatureCoherence::getClassTypeId()) {
        CoherenceFunction.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureCorrelation::getClassTypeId()) {
        CorrelationFunction.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureCumulativeProbabilityDistribution::getClassTypeId()) {
        CumulativeProbabilityDistribution.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureFrequencyDistribution::getClassTypeId()) {
        FrequencyDistribution.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureKurtosis::getClassTypeId()) {
        Kurtosis.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureLocationDistribution::getClassTypeId()) {
        SpatialDistribution.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureMatrixTool::getClassTypeId()) {
        MatrixTool.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureMeanAcceleration::getClassTypeId()) {
        MeanFunction.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureModulation::getClassTypeId()) {
        ModulationFunction.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeaturePeakFactor::getClassTypeId()) {
        PeakFactor.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureProbabilityDensityFunction::getClassTypeId()) {
        ProbabilityDensityFunction.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeaturePSDDecompositionMethod::getClassTypeId()) {
        SpectrumDecompositionMethod.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureRandomness::getClassTypeId()) {
        RandomnessProvider.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureShearVelocityOfFlow::getClassTypeId()) {
        ShearVelocityOfFlow.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureSimulationMethod::getClassTypeId()) {
        SimulationMethod.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureSkewness::getClassTypeId()) {
        Skewness.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureStandardDeviation::getClassTypeId()) {
        StandardDeviation.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureTableTool::getClassTypeId()) {
        TableTool.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureUserDefinedRPSObject::getClassTypeId()) {
        UserDefinedRPSObject.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureVariance::getClassTypeId()) {
        VarianceFunction.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureWavePassageEffect::getClassTypeId()) {
        WavePassageEffect.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
    else if (type == SeaLabAPI::SeaLabFeatureSpectrum::getClassTypeId()) {
        SpectrumModel.setEnums(findAllSeaLabFeaturesOfThisType(type));
    }
}

void SeaLabSimulation::resetAllEnums()
{
  CoherenceFunction.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureCoherence::getClassTypeId()));
  CorrelationFunction.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureCorrelation::getClassTypeId()));
  CumulativeProbabilityDistribution.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureCumulativeProbabilityDistribution::getClassTypeId()));
  FrequencyDistribution.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureFrequencyDistribution::getClassTypeId()));
  Kurtosis.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureKurtosis::getClassTypeId()));
  SpatialDistribution.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureLocationDistribution::getClassTypeId()));
  MatrixTool.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureMatrixTool::getClassTypeId()));
  MeanFunction.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureMeanAcceleration::getClassTypeId()));
  ModulationFunction.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureModulation::getClassTypeId()));
  PeakFactor.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeaturePeakFactor::getClassTypeId()));
  ProbabilityDensityFunction.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureProbabilityDensityFunction::getClassTypeId()));
  SpectrumDecompositionMethod.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeaturePSDDecompositionMethod::getClassTypeId()));
  RandomnessProvider.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureRandomness::getClassTypeId()));
  ShearVelocityOfFlow.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureShearVelocityOfFlow::getClassTypeId()));
  SimulationMethod.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureSimulationMethod::getClassTypeId()));
  Skewness.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureSkewness::getClassTypeId()));
  StandardDeviation.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureStandardDeviation::getClassTypeId()));
  TableTool.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureTableTool::getClassTypeId()));
  UserDefinedRPSObject.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureUserDefinedRPSObject::getClassTypeId()));
  VarianceFunction.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureVariance::getClassTypeId()));
  WavePassageEffect.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureWavePassageEffect::getClassTypeId()));
  SpectrumModel.setEnums(findAllSeaLabFeaturesOfThisType(SeaLabAPI::SeaLabFeatureSpectrum::getClassTypeId()));
}

QStringList SeaLabSimulation::findAllSeaLabFeatures(Base::Type type)
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

QStringList SeaLabSimulation::findAllSeaLabFeaturesByGoupAndType(QString group, QString type)
{
    QStringList featureList;
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc) return featureList;
    auto features = this->getAllChildren();
    for (auto& feat : features) {
       auto myFeat = static_cast<SeaLabAPI::SeaLabFeature*>(feat);
       if (myFeat && myFeat->FeatureType.getStrValue() == type.toUtf8().constData() && myFeat->FeatureGroup.getStrValue() == group.toUtf8().constData())
    featureList.append(QString::fromUtf8(myFeat->getNameInDocument()));
    }
    return featureList;
}

std::vector<std::string> SeaLabSimulation::findAllSeaLabFeaturesOfThisType(Base::Type type)
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

Base::Type SeaLabSimulation::getRPSType(QString group)
{
    if (group == SeaLab::SeaLabUtils::objGroupCoherenceFunction) {
        return SeaLabAPI::IrpsSeLCoherence::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCorrelationFunction) {
        return SeaLabAPI::IrpsSeLCorrelation::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution) {
        return SeaLabAPI::IrpsSeLCumulativeProbabilityDistribution::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupFrequencyDistribution) {
        return SeaLabAPI::IrpsSeLFrequencyDistribution::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupKurtosis) {
        return SeaLabAPI::IrpsSeLKurtosis::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupLocationDistribution) {
        return SeaLabAPI::IrpsSeLLocationDistribution::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMatrixTool) {
        return SeaLabAPI::IrpsSeLMatrixTool::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile) {
        return SeaLabAPI::IrpsSeLMeanAcceleration::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupModulationFunction) {
        return SeaLabAPI::IrpsSeLModulation::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupPeakFactor) {
        return SeaLabAPI::IrpsSeLPeakFactor::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction) {
        return SeaLabAPI::IrpsSeLProbabilityDensityFunction::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod) {
        return SeaLabAPI::IrpsSeLPSDdecompositionMethod::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupRandomnessProvider) {
        return SeaLabAPI::IrpsSeLRandomness::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow) {
        return SeaLabAPI::IrpsSeLShearVelocityOfFlow::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSimulationMethod) {
        return SeaLabAPI::IrpsSeLSimulationMethod::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSimulationMethod) {
        return SeaLabAPI::IrpsSeLSkewness::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupStandardDeviation) {
        return SeaLabAPI::IrpsSeLStandardDeviation::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupTableTool) {
        return SeaLabAPI::IrpsSeLTableTool::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject) {
        return SeaLabAPI::IrpsSeLUserDefinedRPSObject::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupVariance) {
        return SeaLabAPI::IrpsSeLVariance::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupWavePassageEffect) {
        return SeaLabAPI::IrpsSeLWavePassageEffect::getClassTypeId();
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrum) {
        return SeaLabAPI::IrpsSeLSpectrum::getClassTypeId();
    }
}

std::vector<Base::Type> SeaLabSimulation::getRPSTypesOfPluggableFeatures()
{
    std::vector<Base::Type> types;
    types.emplace_back(SeaLabAPI::SeaLabFeatureLocationDistribution::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureMeanAcceleration::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureSpectrum::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeaturePSDDecompositionMethod::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureCoherence::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureSimulationMethod::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureFrequencyDistribution::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureRandomness::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureModulation::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureCorrelation::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureTableTool::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureMatrixTool::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureCumulativeProbabilityDistribution::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureKurtosis::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeaturePeakFactor::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureProbabilityDensityFunction::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureShearVelocityOfFlow::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureSkewness::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureStandardDeviation::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureVariance::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureWavePassageEffect::getClassTypeId());
    types.emplace_back(SeaLabAPI::SeaLabFeatureUserDefinedRPSObject::getClassTypeId());

    return types;
}

std::vector<QString> SeaLabSimulation::getSeaLabPluggableFeatures()
{
    std::vector<QString> groups;
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupLocationDistribution);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupSpectrum);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupCoherenceFunction);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupSimulationMethod);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupFrequencyDistribution);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupRandomnessProvider);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupModulationFunction);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupCorrelationFunction);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupTableTool);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupMatrixTool);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupKurtosis);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupPeakFactor);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupSkewness);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupStandardDeviation);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupVariance);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupWavePassageEffect);
    groups.emplace_back(SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject);

    return groups;
}

bool SeaLabSimulation::doubleClicked(void) 
{
    return true;
}

void SeaLabSimulation::onChanged(const App::Property* prop)
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

        ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/SeaLab/General");
        int limitAutoAct = hGrp->GetBool("AutomaticLargeScaleModeActivation", true);
    
        hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/SeaLab/Limit");
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


SeaLabAPI::SeaLabFeatureDescription* SeaLabSimulation::GetSeaLabPluggedSeaLabFeatureDescription(const QString& objectGroup, const QString& objName)
{
    SeaLabFeatureDescription* pluggedSeaLabFeatureDescription = new SeaLabFeatureDescription();
    std::string pluginName;
    std::string descrip;
    std::string pubTitle;
    std::string pubLink;
    std::string pubAuthor;
    std::string pubDate;
    std::string version;
    bool stationarity;
    std::string objectName = objName.toUtf8().constData();

    if (objectGroup == SeaLab::SeaLabUtils::objGroupLocationDistribution) {
        pluginName = CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsLocationDistributionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsLocationDistributionFactory::GetTitleMap()[objectName];
        pubLink = CrpsLocationDistributionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsLocationDistributionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsLocationDistributionFactory::GetDateMap()[objectName];
        version = CrpsLocationDistributionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsLocationDistributionFactory::GetStationarityMap()[objectName];

    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile) {
        pluginName = CrpsMeanFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsMeanFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsMeanFactory::GetTitleMap()[objectName];
        pubLink = CrpsMeanFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsMeanFactory::GetAuthorMap()[objectName];
        pubDate = CrpsMeanFactory::GetDateMap()[objectName];
        version = CrpsMeanFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsMeanFactory::GetStationarityMap()[objectName];

    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupSpectrum) {
        pluginName = CrpsSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsSpectrumFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsSpectrumFactory::GetTitleMap()[objectName];
        pubLink = CrpsSpectrumFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsSpectrumFactory::GetAuthorMap()[objectName];
        pubDate = CrpsSpectrumFactory::GetDateMap()[objectName];
        version = CrpsSpectrumFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsSpectrumFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod) {
        pluginName = CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsPSDdecomMethodFactory::GetTitleMap()[objectName];
        pubLink = CrpsPSDdecomMethodFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsPSDdecomMethodFactory::GetAuthorMap()[objectName];
        pubDate = CrpsPSDdecomMethodFactory::GetDateMap()[objectName];
        version = CrpsPSDdecomMethodFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsPSDdecomMethodFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupCoherenceFunction) {
        pluginName = CrpsCoherenceFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsCoherenceFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsCoherenceFactory::GetTitleMap()[objectName];
        pubLink = CrpsCoherenceFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsCoherenceFactory::GetAuthorMap()[objectName];
        pubDate = CrpsCoherenceFactory::GetDateMap()[objectName];
        version = CrpsCoherenceFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsCoherenceFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupSimulationMethod) {
        pluginName = CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsSimuMethodFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsSimuMethodFactory::GetTitleMap()[objectName];
        pubLink = CrpsSimuMethodFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsSimuMethodFactory::GetAuthorMap()[objectName];
        pubDate = CrpsSimuMethodFactory::GetDateMap()[objectName];
        version = CrpsSimuMethodFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsSimuMethodFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupFrequencyDistribution) {
        pluginName = CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsFrequencyDistributionFactory::GetTitleMap()[objectName];
        pubLink = CrpsFrequencyDistributionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsFrequencyDistributionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsFrequencyDistributionFactory::GetDateMap()[objectName];
        version = CrpsFrequencyDistributionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsFrequencyDistributionFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupRandomnessProvider) {
        pluginName = CrpsRandomnessFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsRandomnessFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsRandomnessFactory::GetTitleMap()[objectName];
        pubLink = CrpsRandomnessFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsRandomnessFactory::GetAuthorMap()[objectName];
        pubDate = CrpsRandomnessFactory::GetDateMap()[objectName];
        version = CrpsRandomnessFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsRandomnessFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupModulationFunction) {
        pluginName = CrpsModulationFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsModulationFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsModulationFactory::GetTitleMap()[objectName];
        pubLink = CrpsModulationFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsModulationFactory::GetAuthorMap()[objectName];
        pubDate = CrpsModulationFactory::GetDateMap()[objectName];
        version = CrpsModulationFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsModulationFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupTableTool) {
        pluginName = CrpsTableToolFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsTableToolFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsTableToolFactory::GetTitleMap()[objectName];
        pubLink = CrpsTableToolFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsTableToolFactory::GetAuthorMap()[objectName];
        pubDate = CrpsTableToolFactory::GetDateMap()[objectName];
        version = CrpsTableToolFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsTableToolFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupMatrixTool) {
        pluginName = CrpsMatrixToolFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsMatrixToolFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsMatrixToolFactory::GetTitleMap()[objectName];
        pubLink = CrpsMatrixToolFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsMatrixToolFactory::GetAuthorMap()[objectName];
        pubDate = CrpsMatrixToolFactory::GetDateMap()[objectName];
        version = CrpsMatrixToolFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsMatrixToolFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject) {
        pluginName = CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsUserDefinedRPSObjectFactory::GetTitleMap()[objectName];
        pubLink = CrpsUserDefinedRPSObjectFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsUserDefinedRPSObjectFactory::GetAuthorMap()[objectName];
        pubDate = CrpsUserDefinedRPSObjectFactory::GetDateMap()[objectName];
        version = CrpsUserDefinedRPSObjectFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsUserDefinedRPSObjectFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution) {
        pluginName = CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsCumulativeProbabilityDistributionFactory::GetTitleMap()[objectName];
        pubLink = CrpsCumulativeProbabilityDistributionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsCumulativeProbabilityDistributionFactory::GetDateMap()[objectName];
        version = CrpsCumulativeProbabilityDistributionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsCumulativeProbabilityDistributionFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupKurtosis) {
        pluginName = CrpsKurtosisFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsKurtosisFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsKurtosisFactory::GetTitleMap()[objectName];
        pubLink = CrpsKurtosisFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsKurtosisFactory::GetAuthorMap()[objectName];
        pubDate = CrpsKurtosisFactory::GetDateMap()[objectName];
        version = CrpsKurtosisFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsKurtosisFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupPeakFactor) {
        pluginName = CrpsPeakFactorFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsPeakFactorFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsPeakFactorFactory::GetTitleMap()[objectName];
        pubLink = CrpsPeakFactorFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsPeakFactorFactory::GetAuthorMap()[objectName];
        pubDate = CrpsPeakFactorFactory::GetDateMap()[objectName];
        version = CrpsPeakFactorFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsPeakFactorFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction) {
        pluginName = CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsProbabilityDensityFunctionFactory::GetTitleMap()[objectName];
        pubLink = CrpsProbabilityDensityFunctionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsProbabilityDensityFunctionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsProbabilityDensityFunctionFactory::GetDateMap()[objectName];
        version = CrpsProbabilityDensityFunctionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsProbabilityDensityFunctionFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow) {
        pluginName = CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsShearVelocityOfFlowFactory::GetTitleMap()[objectName];
        pubLink = CrpsShearVelocityOfFlowFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsShearVelocityOfFlowFactory::GetAuthorMap()[objectName];
        pubDate = CrpsShearVelocityOfFlowFactory::GetDateMap()[objectName];
        version = CrpsShearVelocityOfFlowFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsShearVelocityOfFlowFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupSkewness) {
        pluginName = CrpsSkewnessFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsSkewnessFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsSkewnessFactory::GetTitleMap()[objectName];
        pubLink = CrpsSkewnessFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsSkewnessFactory::GetAuthorMap()[objectName];
        pubDate = CrpsSkewnessFactory::GetDateMap()[objectName];
        version = CrpsSkewnessFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsSkewnessFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupStandardDeviation) {
        pluginName = CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsStandardDeviationFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsStandardDeviationFactory::GetTitleMap()[objectName];
        pubLink = CrpsStandardDeviationFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsStandardDeviationFactory::GetAuthorMap()[objectName];
        pubDate = CrpsStandardDeviationFactory::GetDateMap()[objectName];
        version = CrpsStandardDeviationFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsStandardDeviationFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupVariance) {
        pluginName = CrpsVarianceFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsVarianceFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsVarianceFactory::GetTitleMap()[objectName];
        pubLink = CrpsVarianceFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsVarianceFactory::GetAuthorMap()[objectName];
        pubDate = CrpsVarianceFactory::GetDateMap()[objectName];
        version = CrpsVarianceFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsVarianceFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeaLab::SeaLabUtils::objGroupWavePassageEffect) {
        pluginName = CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsWavePassageEffectFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsWavePassageEffectFactory::GetTitleMap()[objectName];
        pubLink = CrpsWavePassageEffectFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsWavePassageEffectFactory::GetAuthorMap()[objectName];
        pubDate = CrpsWavePassageEffectFactory::GetDateMap()[objectName];
        version = CrpsWavePassageEffectFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsWavePassageEffectFactory::GetStationarityMap()[objectName];
    }

    pluggedSeaLabFeatureDescription->PluginName.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())] ->GetPluginName().toUtf8().constData());
    pluggedSeaLabFeatureDescription->ReleaseDate.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())] ->GetPluginReleaseDate().toUtf8().constData());
    pluggedSeaLabFeatureDescription->Path.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginSubFolder().toUtf8().constData());
    pluggedSeaLabFeatureDescription->Author.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginAuthor().toUtf8().constData());
    pluggedSeaLabFeatureDescription->PluginVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginVersion().toUtf8().constData());
    pluggedSeaLabFeatureDescription->LabRPSVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetLabRPSVersion().toUtf8().constData());
    pluggedSeaLabFeatureDescription->APIVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetAPIVersion().toUtf8().constData());
    pluggedSeaLabFeatureDescription->ObjectName.setValue(objectName);
    pluggedSeaLabFeatureDescription->Version.setValue(version);
    pluggedSeaLabFeatureDescription->Stationarity.setValue(stationarity);
    pluggedSeaLabFeatureDescription->Description.setValue(descrip);
    pluggedSeaLabFeatureDescription->PublicationTitle.setValue(pubTitle);
    pluggedSeaLabFeatureDescription->PublicationLink.setValue(pubLink);
    pluggedSeaLabFeatureDescription->PublicationAuthor.setValue(pubAuthor);
    pluggedSeaLabFeatureDescription->PublicationDate.setValue(pubDate);

    return pluggedSeaLabFeatureDescription;
}

void SeaLabSimulation::createNewSimulation() {}

PyObject* SeaLabSimulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        PythonObject = Py::Object(new SeaLabSimulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool SeaLabSimulation::computeCrossCoherenceVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
   auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
        return false;
    SeaLabAPI::IrpsSeLCoherence* activefeature = static_cast<SeaLabAPI::IrpsSeLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
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
bool SeaLabSimulation::computeCrossCoherenceVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
        return false;
    SeaLabAPI::IrpsSeLCoherence* activefeature = static_cast<SeaLabAPI::IrpsSeLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
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

bool SeaLabSimulation::computeCrossCoherenceMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    SeaLabAPI::IrpsSeLCoherence* activefeature = static_cast<SeaLabAPI::IrpsSeLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
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

	
bool SeaLabSimulation::computeCrossCorrelationVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
        if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLCorrelation* activefeature = static_cast<SeaLabAPI::IrpsSeLCorrelation*>(doc->getObject(_simuData->correlationFunction.getValue()));
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

bool SeaLabSimulation::computeCrossCorrelationMatrixPP(const double &dTime, mat &dCorrelationMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLCorrelation* activefeature = static_cast<SeaLabAPI::IrpsSeLCorrelation*>(doc->getObject(_simuData->correlationFunction.getValue()));
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

bool SeaLabSimulation::computeFrequenciesVectorF(const Base::Vector3d &location, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLFrequencyDistribution* activefeature = static_cast<SeaLabAPI::IrpsSeLFrequencyDistribution*>(doc->getObject(_simuData->frequencyDistribution.getValue()));
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
  
bool SeaLabSimulation::computeFrequenciesMatrixFP(mat& dMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLFrequencyDistribution* activefeature = static_cast<SeaLabAPI::IrpsSeLFrequencyDistribution*>(doc->getObject(_simuData->frequencyDistribution.getValue()));
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

bool SeaLabSimulation::computeLocationCoordinateMatrixP3(mat& dLocCoord, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLLocationDistribution* activefeature = static_cast<SeaLabAPI::IrpsSeLLocationDistribution*>(doc->getObject(_simuData->spatialDistribution.getValue()));
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

bool SeaLabSimulation::computeMeanAccelerationVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLMeanAcceleration* activefeature = static_cast<SeaLabAPI::IrpsSeLMeanAcceleration*>(doc->getObject(_simuData->meanFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active mean ground motion acceleration feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeMeanAccelerationVectorP(*this->getSimulationData(), dTime, dVarVector, dValVector);
     if (!returnResult) {
        Base::Console().Error("The computation of the mean ground motion acceleration vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeaLabSimulation::computeMeanAccelerationVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLMeanAcceleration* activefeature = static_cast<SeaLabAPI::IrpsSeLMeanAcceleration*>(doc->getObject(_simuData->meanFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active mean ground motion acceleration feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeMeanAccelerationVectorT(*this->getSimulationData(), location, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the mean velocity vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeaLabSimulation::computeModulationVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLModulation* activefeature = static_cast<SeaLabAPI::IrpsSeLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
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

bool SeaLabSimulation::computeModulationVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLModulation* activefeature = static_cast<SeaLabAPI::IrpsSeLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
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

bool SeaLabSimulation::computeDecomposedCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLPSDdecompositionMethod* activefeature = static_cast<SeaLabAPI::IrpsSeLPSDdecompositionMethod*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));
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

bool SeaLabSimulation::computeDecomposedCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLPSDdecompositionMethod* activefeature = static_cast<SeaLabAPI::IrpsSeLPSDdecompositionMethod*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));
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

bool SeaLabSimulation::computeDecomposedCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLPSDdecompositionMethod* activefeature = static_cast<SeaLabAPI::IrpsSeLPSDdecompositionMethod*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));
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

bool SeaLabSimulation::generateRandomMatrixFP(mat& dRandomValueArray, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLRandomness* activefeature = static_cast<SeaLabAPI::IrpsSeLRandomness*>(doc->getObject(_simuData->randomnessProvider.getValue()));
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

bool SeaLabSimulation::computeCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSpectrum* activefeature = static_cast<SeaLabAPI::IrpsSeLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeCrossSpectrumVectorF(*this->getSimulationData(), locationJ, locationK, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeaLabSimulation::computeCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSpectrum* activefeature = static_cast<SeaLabAPI::IrpsSeLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeCrossSpectrumVectorT(*this->getSimulationData(), locationJ, locationK, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}

bool SeaLabSimulation::computeCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &psdMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSpectrum* activefeature = static_cast<SeaLabAPI::IrpsSeLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum model feature found.\n");
        return false;
    }
    psdMatrix.resize(this->getSimulationData()->numberOfSpatialPosition.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeCrossSpectrumMatrixPP(*this->getSimulationData(), dFrequency, dTime, psdMatrix);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the decomposed spectrum matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeaLabSimulation::computeAutoSpectrumValue(const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSpectrum* activefeature = static_cast<SeaLabAPI::IrpsSeLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum model feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeAutoSpectrumValue(*this->getSimulationData(), location, dFrequency, dTime, dValue);    
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}
    
bool SeaLabSimulation::computeAutoSpectrumVectorF(const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSpectrum* activefeature = static_cast<SeaLabAPI::IrpsSeLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    dValVector.resize(this->getSimulationData()->numberOfFrequency.getValue());
    bool returnResult = activefeature->ComputeAutoSpectrumVectorF(*this->getSimulationData(), location, dTime, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeaLabSimulation::computeAutoSpectrumVectorT(const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSpectrum* activefeature = static_cast<SeaLabAPI::IrpsSeLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum model feature found.\n");
        return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeAutoSpectrumVectorT(*this->getSimulationData(), location, dFrequency, dVarVector, dValVector);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum vector has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeaLabSimulation::computeCrossCoherenceValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLCoherence* activefeature = static_cast<SeaLabAPI::IrpsSeLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
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

bool SeaLabSimulation::computeCrossCorrelationValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLCorrelation* activefeature = static_cast<SeaLabAPI::IrpsSeLCorrelation*>(doc->getObject(_simuData->correlationFunction.getValue()));
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
bool SeaLabSimulation::computeMeanAccelerationValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLMeanAcceleration* activefeature = static_cast<SeaLabAPI::IrpsSeLMeanAcceleration*>(doc->getObject(_simuData->meanFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active mean ground motion accelerationfeature found.\n");
    return false;
    }
    bool returnResult = activefeature->ComputeMeanAccelerationValue(*this->getSimulationData(), location, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of mean ground motion acceleration value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeaLabSimulation::computeModulationValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLModulation* activefeature = static_cast<SeaLabAPI::IrpsSeLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
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
bool SeaLabSimulation::computeRandomValue(double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    Base::Console().Error("Sorry this tool is not yet implemented.\n");
    return true;

}
bool SeaLabSimulation::computeCrossSpectrumValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSpectrum* activefeature = static_cast<SeaLabAPI::IrpsSeLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active spectrum model feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeCrossSpectrumValue(*this->getSimulationData(), locationJ, locationK, dFrequency, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the spectrum value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeaLabSimulation::computeFrequencyValue(const Base::Vector3d &location, const int &frequencyIndex, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLFrequencyDistribution* activefeature = static_cast<SeaLabAPI::IrpsSeLFrequencyDistribution*>(doc->getObject(_simuData->frequencyDistribution.getValue()));
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


bool SeaLabSimulation::tableToolCompute(mat& inputTable, mat &outputTable, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLTableTool* activefeature = static_cast<SeaLabAPI::IrpsSeLTableTool*>(doc->getObject(_simuData->tableTool.getValue()));
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
bool SeaLabSimulation::matrixToolCompute(mat& inputTable, mat &outputMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLMatrixTool* activefeature = static_cast<SeaLabAPI::IrpsSeLMatrixTool*>(doc->getObject(_simuData->matrixTool.getValue()));
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
bool SeaLabSimulation::userDefinedRPSObjectCompute(mat &dresult, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLUserDefinedRPSObject* activefeature = static_cast<SeaLabAPI::IrpsSeLUserDefinedRPSObject*>(doc->getObject(_simuData->userDefinedRPSObject.getValue()));
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

bool SeaLabSimulation::computeCPDValue(const double& x, double& dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLCumulativeProbabilityDistribution* activefeature = static_cast<SeaLabAPI::IrpsSeLCumulativeProbabilityDistribution*>(doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue()));
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
bool SeaLabSimulation::computeCPDVectorX(vec& dVarVector, vec& dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLCumulativeProbabilityDistribution* activefeature = static_cast<SeaLabAPI::IrpsSeLCumulativeProbabilityDistribution*>(doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue()));
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

bool SeaLabSimulation::computeKurtosisValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLKurtosis* activefeature = static_cast<SeaLabAPI::IrpsSeLKurtosis*>(doc->getObject(_simuData->kurtosis.getValue()));
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
bool SeaLabSimulation::computeKurtosisVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLKurtosis* activefeature = static_cast<SeaLabAPI::IrpsSeLKurtosis*>(doc->getObject(_simuData->kurtosis.getValue()));
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

bool SeaLabSimulation::computeKurtosisVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLKurtosis* activefeature = static_cast<SeaLabAPI::IrpsSeLKurtosis*>(doc->getObject(_simuData->kurtosis.getValue()));
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

bool SeaLabSimulation::computePeakFactorValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLPeakFactor* activefeature = static_cast<SeaLabAPI::IrpsSeLPeakFactor*>(doc->getObject(_simuData->peakFactor.getValue()));
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
bool SeaLabSimulation::computePeakFactorVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLPeakFactor* activefeature = static_cast<SeaLabAPI::IrpsSeLPeakFactor*>(doc->getObject(_simuData->peakFactor.getValue()));
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

bool SeaLabSimulation::computePeakFactorVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLPeakFactor* activefeature = static_cast<SeaLabAPI::IrpsSeLPeakFactor*>(doc->getObject(_simuData->peakFactor.getValue()));
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

bool SeaLabSimulation::computePDFValue(const double& x, double& dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLProbabilityDensityFunction* activefeature = static_cast<SeaLabAPI::IrpsSeLProbabilityDensityFunction*>(doc->getObject(_simuData->probabilityDensityFunction.getValue()));
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

bool SeaLabSimulation::computePDFVectorX(vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLProbabilityDensityFunction* activefeature = static_cast<SeaLabAPI::IrpsSeLProbabilityDensityFunction*>(doc->getObject(_simuData->probabilityDensityFunction.getValue()));
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

bool SeaLabSimulation::computeShearVelocityOfFlowValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLShearVelocityOfFlow* activefeature = static_cast<SeaLabAPI::IrpsSeLShearVelocityOfFlow*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active shear velocity feature found.\n");
        return false;
    }
    bool returnResult = activefeature->ComputeShearVelocityOfFlowValue(*this->getSimulationData(), location, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the shear velocity value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;

}
bool SeaLabSimulation::computeShearVelocityOfFlowVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLShearVelocityOfFlow* activefeature = static_cast<SeaLabAPI::IrpsSeLShearVelocityOfFlow*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));
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
bool SeaLabSimulation::computeShearVelocityOfFlowVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLShearVelocityOfFlow* activefeature = static_cast<SeaLabAPI::IrpsSeLShearVelocityOfFlow*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));
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

bool SeaLabSimulation::computeSkewnessValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSkewness* activefeature = static_cast<SeaLabAPI::IrpsSeLSkewness*>(doc->getObject(_simuData->skewness.getValue()));
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
bool SeaLabSimulation::computeSkewnessVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSkewness* activefeature = static_cast<SeaLabAPI::IrpsSeLSkewness*>(doc->getObject(_simuData->skewness.getValue()));
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
bool SeaLabSimulation::computeSkewnessVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSkewness* activefeature = static_cast<SeaLabAPI::IrpsSeLSkewness*>(doc->getObject(_simuData->skewness.getValue()));

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

bool SeaLabSimulation::computeStandardDeviationValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLStandardDeviation* activefeature = static_cast<SeaLabAPI::IrpsSeLStandardDeviation*>(doc->getObject(_simuData->standardDeviation.getValue()));
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
bool SeaLabSimulation::computeStandardDeviationVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLStandardDeviation* activefeature = static_cast<SeaLabAPI::IrpsSeLStandardDeviation*>(doc->getObject(_simuData->standardDeviation.getValue()));
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
bool SeaLabSimulation::computeStandardDeviationVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLStandardDeviation* activefeature = static_cast<SeaLabAPI::IrpsSeLStandardDeviation*>(doc->getObject(_simuData->standardDeviation.getValue()));
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

bool SeaLabSimulation::computeVarianceValue( const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLVariance* activefeature = static_cast<SeaLabAPI::IrpsSeLVariance*>(doc->getObject(_simuData->varianceFunction.getValue()));
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
bool SeaLabSimulation::computeVarianceVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLVariance* activefeature = static_cast<SeaLabAPI::IrpsSeLVariance*>(doc->getObject(_simuData->varianceFunction.getValue()));
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
bool SeaLabSimulation::computeVarianceVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
     if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLVariance* activefeature = static_cast<SeaLabAPI::IrpsSeLVariance*>(doc->getObject(_simuData->varianceFunction.getValue()));
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

bool SeaLabSimulation::computeWavePassageEffectVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLWavePassageEffect* activefeature = static_cast<SeaLabAPI::IrpsSeLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
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
bool SeaLabSimulation::computeWavePassageEffectVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLWavePassageEffect* activefeature = static_cast<SeaLabAPI::IrpsSeLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
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
bool SeaLabSimulation::computeWavePassageEffectMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
     if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLWavePassageEffect* activefeature = static_cast<SeaLabAPI::IrpsSeLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
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
bool SeaLabSimulation::computeWavePassageEffectValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLWavePassageEffect* activefeature = static_cast<SeaLabAPI::IrpsSeLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
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


bool SeaLabSimulation::simulate(mat &dVelocityArray, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSimulationMethod* activefeature = static_cast<SeaLabAPI::IrpsSeLSimulationMethod*>(doc->getObject(_simuData->simulationMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active simulation method feature found.\n");
        return false;
    }
    dVelocityArray.resize(this->getSimulationData()->numberOfTimeIncrements.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue() + 1);
    dVelocityArray.setZero();

    bool returnResult = activefeature->Simulate(*this->getSimulationData(), dVelocityArray);

    if (!returnResult) {
     Base::Console().Error("The computation of the ground acceleration matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();

    return true;

}

bool SeaLabSimulation::simulateInLargeScaleMode(std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeaLabAPI::IrpsSeLSimulationMethod* activefeature = static_cast<SeaLabAPI::IrpsSeLSimulationMethod*>(doc->getObject(_simuData->simulationMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active simulation method feature found.\n");
        return false;
    }
    QString fineName = QString::fromLatin1("WindVelocity");
    bool returnResult = activefeature->SimulateInLargeScaleMode(*this->getSimulationData(), fineName);
    if (!returnResult) {
     Base::Console().Error("The computation of the ground acceleration matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}


void SeaLabSimulation::setActiveFeature(App::RPSFeature* feature)
{
    if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureCoherence::getClassTypeId())) {
        _simuData->coherenceFunction.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureCorrelation::getClassTypeId())) {
        _simuData->correlationFunction.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureCumulativeProbabilityDistribution::getClassTypeId())) {
        _simuData->cumulativeProbabilityDistribution.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureFrequencyDistribution::getClassTypeId())) {
        _simuData->frequencyDistribution.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureKurtosis::getClassTypeId())) {
        _simuData->kurtosis.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureLocationDistribution::getClassTypeId())) {
        _simuData->spatialDistribution.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureMatrixTool::getClassTypeId())) {
        _simuData->matrixTool.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureMeanAcceleration::getClassTypeId())) {
        _simuData->meanFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureModulation::getClassTypeId())) {
        _simuData->modulationFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeaturePeakFactor::getClassTypeId())) {
        _simuData->peakFactor.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureProbabilityDensityFunction::getClassTypeId())) {
        _simuData->probabilityDensityFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeaturePSDDecompositionMethod::getClassTypeId())) {
        _simuData->cpsdDecompositionMethod.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureRandomness::getClassTypeId())) {
        _simuData->randomnessProvider.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureShearVelocityOfFlow::getClassTypeId())) {
        _simuData->shearVelocityOfFlow.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureSimulationMethod::getClassTypeId())) {
        _simuData->simulationMethod.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureSkewness::getClassTypeId())) {
        _simuData->skewness.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureStandardDeviation::getClassTypeId())) {
        _simuData->standardDeviation.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureTableTool::getClassTypeId())) {
        _simuData->tableTool.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureUserDefinedRPSObject::getClassTypeId())) {
        _simuData->userDefinedRPSObject.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureVariance::getClassTypeId())) {
        _simuData->varianceFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureWavePassageEffect::getClassTypeId())) {
        _simuData->wavePassageEffect.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeaLabAPI::SeaLabFeatureSpectrum::getClassTypeId())) {
        _simuData->spectrumModel.setValue(feature->getNameInDocument());  
    }
}

App::RPSFeature* SeaLabSimulation::getActiveFeature(const QString group)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;

    if (group == SeaLab::SeaLabUtils::objGroupCoherenceFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->coherenceFunction.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCorrelationFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->correlationFunction.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupFrequencyDistribution) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->frequencyDistribution.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupKurtosis) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->kurtosis.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupLocationDistribution) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->spatialDistribution.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMatrixTool) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->matrixTool.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->meanFunction.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupModulationFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->modulationFunction.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupPeakFactor) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->peakFactor.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->probabilityDensityFunction.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupRandomnessProvider) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->randomnessProvider.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSimulationMethod) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->simulationMethod.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupStandardDeviation) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->standardDeviation.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupTableTool) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->tableTool.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->userDefinedRPSObject.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupVariance) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->varianceFunction.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupWavePassageEffect) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->wavePassageEffect.getValue()));  
    }
    else if (group == SeaLab::SeaLabUtils::objGroupSpectrum) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->spectrumModel.getValue()));  
    }
}

std::vector<App::RPSFeature*> SeaLabSimulation::getAllFeatures(const QString group)
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

App::DocumentObject* SeaLabSimulation::getActiveCoherence()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->coherenceFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveCorrelation()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->correlationFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveCumulativeProbabilityDistribution()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveFrequencyDistribution()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->frequencyDistribution.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveKurtosis()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->kurtosis.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveLocationDistribution()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->spatialDistribution.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveMeanAcceleration()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->meanFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveModulation()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->modulationFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActivePeakFactor()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->peakFactor.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveProbabilityDensityFunction()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->probabilityDensityFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActivePSDDecompositionMethod()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->cpsdDecompositionMethod.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveRandomness()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->randomnessProvider.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveShearVelocityOfFlow()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->shearVelocityOfFlow.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveSimulationMethod()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->simulationMethod.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveSkewness()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->skewness.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveStandardDeviation()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->standardDeviation.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveUserDefinedRPSObject()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->userDefinedRPSObject.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveVariance()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->varianceFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveWavePassageEffect()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->wavePassageEffect.getValue());
    return activeFeature;
}

App::DocumentObject* SeaLabSimulation::getActiveSpectrum()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->spectrumModel.getValue());
    return activeFeature;
}

App::DocumentObject* SeaLabSimulation::getActiveMatrixTool()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->matrixTool.getValue());
    return activeFeature;
}
App::DocumentObject* SeaLabSimulation::getActiveTableTool()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->tableTool.getValue());
    return activeFeature;
}

App::DocumentObject*  SeaLabSimulation::addFeature(const std::string featureName, const std::string simulationName, const std::string featureTypeName, const std::string featureGroup)
{
    Base::Type type = getRPSType(QString::fromStdString(featureGroup));
    
    //create the feature
	SeaLabAPI::SeaLabFeature* newFeature = this->createFeature(type, featureTypeName, featureName);

	if (!newFeature)
		return nullptr;

	//set the feature properties
	auto featureProperties = this->GetSeaLabPluggedSeaLabFeatureDescription(QString::fromLatin1(featureGroup.c_str()), QString::fromLatin1(featureTypeName.c_str()));
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
