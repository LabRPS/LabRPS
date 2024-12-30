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

#include "SeismicLabSimulation.h"
#include "SeismiclabUtils.h"
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureDescription.h>
#include <Mod/SeismicLabAPI/App/RPSSeismicLabAPI.h>
#include <App/Application.h>
#include <App/Document.h>
#include <App/RPSpluginManager.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureCoherence.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureCorrelation.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureCumulativeProbabilityDistribution.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureFrequencyDistribution.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureKurtosis.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureLocationDistribution.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureMatrixTool.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureModulation.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeaturePSDDecompositionMethod.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeaturePeakFactor.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureProbabilityDensityFunction.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureRandomness.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureShearVelocityOfFlow.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureSimulationMethod.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureSkewness.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureStandardDeviation.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureTableTool.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureUserDefinedRPSObject.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureVariance.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureWavePassageEffect.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureSpectrum.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureMeanAcceleration.h>
#include <Base/Console.h>
#include <Mod/SeismicLab/App/SeismicLabSimulationPy.h>

using namespace App;
using namespace SeismicLab;
using namespace SeismicLabAPI;
namespace sp = std::placeholders;

PROPERTY_SOURCE(SeismicLab::SeismicLabSimulation, App::Simulation)

SeismicLabSimulation::SeismicLabSimulation()
{
    _simuData = new SeismicLabAPI::SeismicLabSimulationData();
   
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
    ADD_PROPERTY_TYPE(PeakGroundAcceleration, (1.0), "Peaks", App::Prop_None, "The peak ground acceleration");
    ADD_PROPERTY_TYPE(PeakGroundVelocity, (1.0), "Peaks", App::Prop_None, "The peak ground velocity");
    ADD_PROPERTY_TYPE(PeackGroundDisplacement, (1.0), "Peaks", App::Prop_None, "The peak ground displacement");

    static const char* featuregroup = "Seismiclab Features";
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

    ADD_PROPERTY_TYPE(Phenomenon, ("Seismic Ground Motion"), 0, Prop_ReadOnly, "The random phenonenon name");
    ADD_PROPERTY_TYPE(WorkingDirectoryPath, (Application::getHomePath()), 0, Prop_None, "The working directory path.");
    ADD_PROPERTY_TYPE(FileName, ("Velocities"), 0, Prop_None, "The wind velocity file name.");
    ADD_PROPERTY_TYPE(SampleIndex, (0), datagroup, Prop_None,"The index of the a given sample");


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

	static const char* directions[] = {"East-West", "North-South", "Vertical", nullptr};
    ADD_PROPERTY_TYPE(Direction, ((long int)0), datagroup, Prop_None, "The ground motion direction");
    Direction.setEnums(directions);

    static const char* soilTYpes[] = {"Clay", "Deep Cohesionless", "Sand", "Soft", "Stiff", "Firm", "Medium", "Rock", "Soft Rock", "Hard Rock", nullptr};
    ADD_PROPERTY_TYPE(SoilType, ((long int)0), datagroup, Prop_None, "The soil type");
    SoilType.setEnums(soilTYpes);

    static const char* motionTypes[] = {"Acceleration", "Velocity", "Displacement", nullptr};
    ADD_PROPERTY_TYPE(MotionType, ((long int)0), datagroup, Prop_None, "The types of the motion");
    MotionType.setEnums(motionTypes);

    App::Document* doc = App::GetApplication().getActiveDocument();

    doc->signalSimulationAbort.connect(
       std::bind(&SeismicLab::SeismicLabSimulation::slotSimulationAbort, this, sp::_1));

}

SeismicLabSimulation::~SeismicLabSimulation() { delete _simuData; }

void SeismicLabSimulation::handleChangedPropertyName(Base::XMLReader& reader, const char* TypeName,            const char* PropName)
{
    Base::Type type = Base::Type::fromName(TypeName);
    App::DocumentObjectGroup::handleChangedPropertyName(reader, TypeName, PropName);
}

void SeismicLabSimulation::updateSimulationData()
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
    _simuData->workingDirectoryPath.setValue(this->WorkingDirectoryPath.getValue());
    _simuData->waveLengthIndex.setValue(this->WaveLengthIndex.getValue());
    _simuData->stationarity.setValue(this->Stationarity.getValue());
    _simuData->gaussianity.setValue(this->Gaussianity.getValue());
    _simuData->comparisonMode.setValue(this->ComparisonMode.getValue());
    _simuData->largeScaleSimulationMode.setValue(this->LargeScaleSimulationMode.getValue());
    _simuData->isSimulationSuccessful.setValue(this->IsSimulationSuccessful.getValue());
    _simuData->isInterruptionRequested.setValue(this->IsInterruptionRequested.getValue());
    _simuData->uniformModulation.setValue(this->UniformModulation.getValue());
    _simuData->minTime.setValue(this->MinTime.getValue());
    _simuData->maxTime.setValue(this->MaxTime.getValue());
    _simuData->timeIncrement.setValue(this->TimeIncrement.getValue());
    _simuData->minFrequency.setValue(this->MinFrequency.getValue());
    _simuData->frequencyIncrement.setValue(this->FrequencyIncrement.getValue());
    _simuData->maxFrequency.setValue(this->MaxFrequency.getValue());
    _simuData->minWaveLength.setValue(this->MinWaveLength.getValue());
    _simuData->maxWaveLength.setValue(this->MaxWaveLength.getValue());
    _simuData->waveLengthIncrement.setValue(this->WaveLengthIncrement.getValue());
    _simuData->minDirection.setValue(this->MinDirection.getValue());
    _simuData->maxDirection.setValue(this->MaxDirection.getValue());
    _simuData->peakGroundAcceleration.setValue(this->PeakGroundAcceleration.getValue());
    _simuData->peakGroundVelocity.setValue(this->PeakGroundVelocity.getValue());
    _simuData->peackGroundDisplacement.setValue(this->PeackGroundDisplacement.getValue());
    _simuData->directionIncrement.setValue(this->DirectionIncrement.getValue());
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
    _simuData->soilType.setValue(this->SoilType.getValueAsString());
    _simuData->motionType.setValue(this->MotionType.getValueAsString());
    _simuData->direction.setValue(this->Direction.getValue());
    _simuData->numberOfIncrementOfVariableX.setValue(this->NumberOfIncrementOfVariableX.getValue());
    _simuData->indexOfVariableX.setValue(this->IndexOfVariableX.getValue());
    _simuData->incrementOfVariableX.setValue(this->IncrementOfVariableX.getValue());
    _simuData->minVariableX.setValue(this->MinVariableX.getValue());
    _simuData->fileName.setValue(this->FileName.getValue());
    _simuData->sampleIndex.setValue(this->SampleIndex.getValue());

}

bool SeismicLabSimulation::run(){ 
    _simuData->isInterruptionRequested.setValue(true);
    this->setStatus(App::SimulationStatus::Stopped, true);
    return true;
}

bool SeismicLabSimulation::stop()
{ 
    _simuData->isInterruptionRequested.setValue(true);
    this->setStatus(App::SimulationStatus::Stopped, true);
    return true;
}

std::string SeismicLabSimulation::getPhenomenonName() const
{
    return SeismicLab::SeismicLabUtils::rpsPhenomenonWindVelocity.toUtf8().constData();
}

std::string SeismicLabSimulation::workbenchName() const { return "SeismicLab"; }

void SeismicLabSimulation::setSimulationData(SeismicLabAPI::SeismicLabSimulationData* simuData)
{
    _simuData = simuData;
}

SeismicLabAPI::SeismicLabSimulationData* SeismicLabSimulation::getSimulationData() const { return _simuData; }

void SeismicLabSimulation::seismicLabFeatureInitalSetting(QString group, QString currentSelected)
{
    if (!_simuData)
        return;

    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return;

    if (group == SeismicLab::SeismicLabUtils::objGroupCoherenceFunction) {
        SeismicLabAPI::IrpsSLCoherence* activefeature = static_cast<SeismicLabAPI::IrpsSLCoherence*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

        auto simuData = getSimulationData();
        if (simuData)
    activefeature->OnInitialSetting(*simuData);

    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCorrelationFunction) {
        SeismicLabAPI::IrpsSLCorrelation* activefeature = static_cast<SeismicLabAPI::IrpsSLCorrelation*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution) {
        SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution* activefeature =
    static_cast<SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution) {
        SeismicLabAPI::IrpsSLFrequencyDistribution* activefeature =
    static_cast<SeismicLabAPI::IrpsSLFrequencyDistribution*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupKurtosis) {
        SeismicLabAPI::IrpsSLKurtosis* activefeature = static_cast<SeismicLabAPI::IrpsSLKurtosis*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupLocationDistribution) {
        SeismicLabAPI::IrpsSLLocationDistribution* activefeature =
    static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMatrixTool) {
        SeismicLabAPI::IrpsSLMatrixTool* activefeature = static_cast<SeismicLabAPI::IrpsSLMatrixTool*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile) {
        SeismicLabAPI::IrpsSLMeanAcceleration* activefeature = static_cast<SeismicLabAPI::IrpsSLMeanAcceleration*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupModulationFunction) {
        SeismicLabAPI::IrpsSLModulation* activefeature = static_cast<SeismicLabAPI::IrpsSLModulation*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupPeakFactor) {
        SeismicLabAPI::IrpsSLPeakFactor* activefeature = static_cast<SeismicLabAPI::IrpsSLPeakFactor*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction) {
        SeismicLabAPI::IrpsSLProbabilityDensityFunction* activefeature =
    static_cast<SeismicLabAPI::IrpsSLProbabilityDensityFunction*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod) {
        SeismicLabAPI::IrpsSLPSDdecompositionMethod* activefeature =
    static_cast<SeismicLabAPI::IrpsSLPSDdecompositionMethod*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupRandomnessProvider) {
        SeismicLabAPI::IrpsSLRandomness* activefeature = static_cast<SeismicLabAPI::IrpsSLRandomness*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow) {
        SeismicLabAPI::IrpsSLShearVelocityOfFlow* activefeature =
    static_cast<SeismicLabAPI::IrpsSLShearVelocityOfFlow*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSimulationMethod) {
        SeismicLabAPI::IrpsSLSimulationMethod* activefeature = static_cast<SeismicLabAPI::IrpsSLSimulationMethod*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSimulationMethod) {
        SeismicLabAPI::IrpsSLSkewness* activefeature = static_cast<SeismicLabAPI::IrpsSLSkewness*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupStandardDeviation) {
        SeismicLabAPI::IrpsSLStandardDeviation* activefeature =
    static_cast<SeismicLabAPI::IrpsSLStandardDeviation*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupTableTool) {
        SeismicLabAPI::IrpsSLTableTool* activefeature = static_cast<SeismicLabAPI::IrpsSLTableTool*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject) {
        SeismicLabAPI::IrpsSLUserDefinedRPSObject* activefeature =
    static_cast<SeismicLabAPI::IrpsSLUserDefinedRPSObject*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupVariance) {
        SeismicLabAPI::IrpsSLVariance* activefeature = static_cast<SeismicLabAPI::IrpsSLVariance*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupWavePassageEffect) {
        SeismicLabAPI::IrpsSLWavePassageEffect* activefeature =
    static_cast<SeismicLabAPI::IrpsSLWavePassageEffect*>(
        doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrum) {
        SeismicLabAPI::IrpsSLSpectrum* activefeature = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
        return;
    }

    auto simuData = getSimulationData();
    if (simuData)
        activefeature->OnInitialSetting(*simuData);
    }
}

QStringList SeismicLabSimulation::findAllPluggedSeismicLabFeatures(QString group)
{
    QStringList theList;
    theList.append(QString::fromLatin1("<None>"));
    if (group == SeismicLab::SeismicLabUtils::objGroupLocationDistribution) {
        typedef IrpsSLLocationDistribution* (*CreateLocDistrCallback)();
        std::map<const std::string, CreateLocDistrCallback>::iterator locIt;
        for (locIt = CrpsLocationDistributionFactory::GetObjectNamesMap().begin();
     locIt != CrpsLocationDistributionFactory::GetObjectNamesMap().end(); ++locIt) {
    theList.append(QString::fromUtf8(locIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile) {
        typedef IrpsSLMeanAcceleration* (*CreateMeanCallback)();
        std::map<const std::string, CreateMeanCallback>::iterator meanIt;
        for (meanIt = CrpsMeanFactory::GetObjectNamesMap().begin();
     meanIt != CrpsMeanFactory::GetObjectNamesMap().end(); ++meanIt) {
    theList.append(QString::fromUtf8(meanIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrum) {
        typedef IrpsSLSpectrum* (*CreateXSpectrumCallback)();
        std::map<const std::string, CreateXSpectrumCallback>::iterator psdIt;
        for (psdIt = CrpsSpectrumFactory::GetObjectNamesMap().begin();
     psdIt != CrpsSpectrumFactory::GetObjectNamesMap().end(); ++psdIt) {
    theList.append(QString::fromUtf8(psdIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod) {

        typedef IrpsSLPSDdecompositionMethod* (*CreatePSDdecomMethodCallback)();
        std::map<const std::string, CreatePSDdecomMethodCallback>::iterator psdDecIt;
        for (psdDecIt = CrpsPSDdecomMethodFactory::GetObjectNamesMap().begin();
     psdDecIt != CrpsPSDdecomMethodFactory::GetObjectNamesMap().end(); ++psdDecIt) {
    theList.append(QString::fromUtf8(psdDecIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCoherenceFunction) {
        typedef IrpsSLCoherence* (*CreateCoherenceCallback)();
        std::map<const std::string, CreateCoherenceCallback>::iterator cohIt;
        for (cohIt = CrpsCoherenceFactory::GetObjectNamesMap().begin();
     cohIt != CrpsCoherenceFactory::GetObjectNamesMap().end(); ++cohIt) {
    theList.append(QString::fromUtf8(cohIt->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSimulationMethod) {
        typedef IrpsSLSimulationMethod* (*CreateSimuMethodCallback)();
        std::map<const std::string, CreateSimuMethodCallback>::iterator simuMethIt;
        for (simuMethIt = CrpsSimuMethodFactory::GetObjectNamesMap().begin();
     simuMethIt != CrpsSimuMethodFactory::GetObjectNamesMap().end(); ++simuMethIt) {
    theList.append(QString::fromUtf8(simuMethIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution) {
        typedef IrpsSLFrequencyDistribution* (*CreateFrequencyDistributionCallback)();
        std::map<const std::string, CreateFrequencyDistributionCallback>::iterator freqDistrIt;
        for (freqDistrIt = CrpsFrequencyDistributionFactory::GetObjectNamesMap().begin();
     freqDistrIt != CrpsFrequencyDistributionFactory::GetObjectNamesMap().end();
     ++freqDistrIt) {
    theList.append(QString::fromUtf8(freqDistrIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupRandomnessProvider) {

        typedef IrpsSLRandomness* (*CreateRandomnessCallback)();
        std::map<const std::string, CreateRandomnessCallback>::iterator randIt;
        for (randIt = CrpsRandomnessFactory::GetObjectNamesMap().begin();
     randIt != CrpsRandomnessFactory::GetObjectNamesMap().end(); ++randIt) {
    theList.append(QString::fromUtf8(randIt->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupModulationFunction) {

        typedef IrpsSLModulation* (*CreateModulationCallback)();
        std::map<const std::string, CreateModulationCallback>::iterator cohIt;
        for (cohIt = CrpsModulationFactory::GetObjectNamesMap().begin();
     cohIt != CrpsModulationFactory::GetObjectNamesMap().end(); ++cohIt) {
    theList.append(QString::fromUtf8(cohIt->first.c_str()));
        }
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCorrelationFunction) {

        typedef IrpsSLCorrelation* (*CreateCorrelationCallback)();
        std::map<const std::string, CreateCorrelationCallback>::iterator corrIt;
        for (corrIt = CrpsCorrelationFactory::GetObjectNamesMap().begin();
     corrIt != CrpsCorrelationFactory::GetObjectNamesMap().end(); ++corrIt) {
    theList.append(QString::fromUtf8(corrIt->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupTableTool) {

        typedef IrpsSLTableTool* (*CreateTableToolCallback)();
        std::map<const std::string, CreateTableToolCallback>::iterator it;
        for (it = CrpsTableToolFactory::GetObjectNamesMap().begin();
     it != CrpsTableToolFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMatrixTool) {

        typedef IrpsSLMatrixTool* (*CreateMatrixToolCallback)();
        std::map<const std::string, CreateMatrixToolCallback>::iterator it;
        for (it = CrpsMatrixToolFactory::GetObjectNamesMap().begin();
     it != CrpsMatrixToolFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution) {

        typedef IrpsSLCumulativeProbabilityDistribution* (
    *CreateCumulativeProbabilityDistributionCallback)();
        std::map<const std::string, CreateCumulativeProbabilityDistributionCallback>::iterator it;
        for (it = CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().begin();
     it != CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupKurtosis) {

        typedef IrpsSLKurtosis* (*CreateKurtosisCallback)();
        std::map<const std::string, CreateKurtosisCallback>::iterator it;
        for (it = CrpsKurtosisFactory::GetObjectNamesMap().begin();
     it != CrpsKurtosisFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupPeakFactor) {

        typedef IrpsSLPeakFactor* (*CreatePeakFactorCallback)();
        std::map<const std::string, CreatePeakFactorCallback>::iterator it;
        for (it = CrpsPeakFactorFactory::GetObjectNamesMap().begin();
     it != CrpsPeakFactorFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction) {

        typedef IrpsSLProbabilityDensityFunction* (*CreateProbabilityDensityFunctionCallback)();
        std::map<const std::string, CreateProbabilityDensityFunctionCallback>::iterator it;
        for (it = CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().begin();
     it != CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow) {

        typedef IrpsSLShearVelocityOfFlow* (*CreateShearVelocityOfFlowCallback)();
        std::map<const std::string, CreateShearVelocityOfFlowCallback>::iterator it;
        for (it = CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().begin();
     it != CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSkewness) {

        typedef IrpsSLSkewness* (*CreateSkewnessCallback)();
        std::map<const std::string, CreateSkewnessCallback>::iterator it;
        for (it = CrpsSkewnessFactory::GetObjectNamesMap().begin();
     it != CrpsSkewnessFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupStandardDeviation) {

        typedef IrpsSLStandardDeviation* (*CreateStandardDeviationCallback)();
        std::map<const std::string, CreateStandardDeviationCallback>::iterator it;
        for (it = CrpsStandardDeviationFactory::GetObjectNamesMap().begin();
     it != CrpsStandardDeviationFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupVariance) {

        typedef IrpsSLVariance* (*CreateVarianceCallback)();
        std::map<const std::string, CreateVarianceCallback>::iterator it;
        for (it = CrpsVarianceFactory::GetObjectNamesMap().begin();
     it != CrpsVarianceFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupWavePassageEffect) {

        typedef IrpsSLWavePassageEffect* (*CreateWavePassageEffectCallback)();
        std::map<const std::string, CreateWavePassageEffectCallback>::iterator it;
        for (it = CrpsWavePassageEffectFactory::GetObjectNamesMap().begin();
     it != CrpsWavePassageEffectFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject) {

        typedef IrpsSLUserDefinedRPSObject* (*CreateUserDefinedRPSObjectCallback)();
        std::map<const std::string, CreateUserDefinedRPSObjectCallback>::iterator it;
        for (it = CrpsUserDefinedRPSObjectFactory::GetObjectNamesMap().begin();
     it != CrpsUserDefinedRPSObjectFactory::GetObjectNamesMap().end(); ++it) {
    theList.append(QString::fromUtf8(it->first.c_str()));
        }

        return theList;
    }

    return theList;
}

QStringList SeismicLabSimulation::findAllFeatureMethods(QString group)
{
    QStringList theList;
    theList.append(QString::fromLatin1("<None>"));
    if (group == SeismicLab::SeismicLabUtils::objGroupLocationDistribution) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeLocationCoordinateMatrixP3);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeMeanAccelerationValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeMeanAccelerationVectorP);
        theList.append(SeismicLab::SeismicLabUtils::ComputeMeanAccelerationVectorT);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrum) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossSpectrumValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossSpectrumVectorF);
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossSpectrumVectorT);
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossSpectrumMatrixPP);
        theList.append(SeismicLab::SeismicLabUtils::ComputeAutoSpectrumValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeAutoSpectrumVectorF);
        theList.append(SeismicLab::SeismicLabUtils::ComputeAutoSpectrumVectorT);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod) {

        theList.append(SeismicLab::SeismicLabUtils::ComputeDecomposedPSDValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorF);
        theList.append(SeismicLab::SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorT);
        theList.append(SeismicLab::SeismicLabUtils::ComputeDecomposedCrossSpectrumMatrixPP);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCoherenceFunction) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossCoherenceValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossCoherenceVectorF);
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossCoherenceVectorT);
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossCoherenceMatrixPP);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSimulationMethod) {
        theList.append(SeismicLab::SeismicLabUtils::Simulate);
        theList.append(SeismicLab::SeismicLabUtils::SimulateInLargeScaleMode);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeFrequencyValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeFrequenciesVectorF);
        theList.append(SeismicLab::SeismicLabUtils::ComputeFrequenciesMatrixFP);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupRandomnessProvider) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeRandomValue);
        theList.append(SeismicLab::SeismicLabUtils::GenerateRandomMatrixFP);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupModulationFunction) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeModulationValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeModulationVectorP);
        theList.append(SeismicLab::SeismicLabUtils::ComputeModulationVectorT);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCorrelationFunction) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossCorrelationValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossCorrelationVectorT);
        theList.append(SeismicLab::SeismicLabUtils::ComputeCrossCorrelationMatrixPP);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupTableTool) {
        theList.append(SeismicLab::SeismicLabUtils::TableToolCompute);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMatrixTool) {
        theList.append(SeismicLab::SeismicLabUtils::MatrixToolCompute);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeCPDValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeCPDVectorX);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupKurtosis) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeKurtosisValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeKurtosisVectorP);
        theList.append(SeismicLab::SeismicLabUtils::ComputeKurtosisVectorT);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupPeakFactor) {
        theList.append(SeismicLab::SeismicLabUtils::ComputePeakFactorValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputePeakFactorVectorP);
        theList.append(SeismicLab::SeismicLabUtils::ComputePeakFactorVectorT);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction) {
        theList.append(SeismicLab::SeismicLabUtils::ComputePDFValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputePDFVectorX);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowVectorP);
        theList.append(SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowVectorT);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSkewness) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeSkewnessValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeSkewnessVectorP);
        theList.append(SeismicLab::SeismicLabUtils::ComputeSkewnessVectorT);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupStandardDeviation) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeStandardDeviationValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeStandardDeviationVectorP);
        theList.append(SeismicLab::SeismicLabUtils::ComputeStandardDeviationVectorT);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupVariance) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeVarianceValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeVarianceVectorP);
        theList.append(SeismicLab::SeismicLabUtils::ComputeVarianceVectorT);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupWavePassageEffect) {
        theList.append(SeismicLab::SeismicLabUtils::ComputeWavePassageEffectValue);
        theList.append(SeismicLab::SeismicLabUtils::ComputeWavePassageEffectVectorF);
        theList.append(SeismicLab::SeismicLabUtils::ComputeWavePassageEffectVectorT);
        theList.append(SeismicLab::SeismicLabUtils::ComputeWavePassageEffectMatrixPP);
        return theList;
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject) {
        theList.append(SeismicLab::SeismicLabUtils::UserDefinedRPSObjectCompute);
        return theList;
    }

    return theList;
}

SeismicLabAPI::SeismicLabFeature* SeismicLabSimulation::createFeature(Base::Type type, std::string pluggedObjectTypeName, std::string name)
{
    //get the active document
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;

    //make unique name for this new feature in the active document (its parent document)
    std::string uniqueName = doc->getUniqueObjectName(name.c_str());

    //now figure out the feature type and create it
    if (type == SeismicLabAPI::SeismicLabFeatureCoherence::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureCoherence* newFeature =  CrpsCoherenceFactory::BuildObject(pluggedObjectTypeName);
        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureCorrelation::getClassTypeId()) {
    // Build an object
    SeismicLabAPI::SeismicLabFeatureCorrelation* newFeature = CrpsCorrelationFactory::BuildObject(pluggedObjectTypeName);
    if (NULL == newFeature) {
    return nullptr;
    }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureCumulativeProbabilityDistribution::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureCumulativeProbabilityDistribution* newFeature = CrpsCumulativeProbabilityDistributionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureFrequencyDistribution::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureFrequencyDistribution* newFeature = CrpsFrequencyDistributionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureKurtosis::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureKurtosis* newFeature = CrpsKurtosisFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureLocationDistribution::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureLocationDistribution* newFeature = CrpsLocationDistributionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureMatrixTool::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureMatrixTool* newFeature = CrpsMatrixToolFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureMeanAcceleration::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureMeanAcceleration* newFeature = CrpsMeanFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureModulation::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureModulation* newFeature =CrpsModulationFactory::BuildObject(pluggedObjectTypeName);
        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeaturePeakFactor::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeaturePeakFactor* newFeature = CrpsPeakFactorFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureProbabilityDensityFunction::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureProbabilityDensityFunction* newFeature = CrpsProbabilityDensityFunctionFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeaturePSDDecompositionMethod::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeaturePSDDecompositionMethod* newFeature =  CrpsPSDdecomMethodFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureRandomness::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureRandomness* newFeature =  CrpsRandomnessFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureShearVelocityOfFlow::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureShearVelocityOfFlow* newFeature = CrpsShearVelocityOfFlowFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureSimulationMethod::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureSimulationMethod* newFeature = CrpsSimuMethodFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureSkewness::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureSkewness* newFeature = CrpsSkewnessFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureStandardDeviation::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureStandardDeviation* newFeature = CrpsStandardDeviationFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());
        return newFeature;

    }
    else if (type == SeismicLabAPI::SeismicLabFeatureTableTool::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureTableTool* newFeature = CrpsTableToolFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureUserDefinedRPSObject::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureUserDefinedRPSObject* newFeature =  CrpsUserDefinedRPSObjectFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureVariance::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureVariance* newFeature = CrpsVarianceFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureWavePassageEffect::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureWavePassageEffect* newFeature = CrpsWavePassageEffectFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureSpectrum::getClassTypeId()) {
        SeismicLabAPI::SeismicLabFeatureSpectrum* newFeature = CrpsSpectrumFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }

}

void SeismicLabSimulation::setEnums(Base::Type type)
{

    if (type == SeismicLabAPI::SeismicLabFeatureCoherence::getClassTypeId()) {
        CoherenceFunction.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureCorrelation::getClassTypeId()) {
        CorrelationFunction.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureCumulativeProbabilityDistribution::getClassTypeId()) {
        CumulativeProbabilityDistribution.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureFrequencyDistribution::getClassTypeId()) {
        FrequencyDistribution.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureKurtosis::getClassTypeId()) {
        Kurtosis.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureLocationDistribution::getClassTypeId()) {
        SpatialDistribution.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureMatrixTool::getClassTypeId()) {
        MatrixTool.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureMeanAcceleration::getClassTypeId()) {
        MeanFunction.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureModulation::getClassTypeId()) {
        ModulationFunction.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeaturePeakFactor::getClassTypeId()) {
        PeakFactor.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureProbabilityDensityFunction::getClassTypeId()) {
        ProbabilityDensityFunction.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeaturePSDDecompositionMethod::getClassTypeId()) {
        SpectrumDecompositionMethod.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureRandomness::getClassTypeId()) {
        RandomnessProvider.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureShearVelocityOfFlow::getClassTypeId()) {
        ShearVelocityOfFlow.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureSimulationMethod::getClassTypeId()) {
        SimulationMethod.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureSkewness::getClassTypeId()) {
        Skewness.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureStandardDeviation::getClassTypeId()) {
        StandardDeviation.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureTableTool::getClassTypeId()) {
        TableTool.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureUserDefinedRPSObject::getClassTypeId()) {
        UserDefinedRPSObject.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureVariance::getClassTypeId()) {
        VarianceFunction.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureWavePassageEffect::getClassTypeId()) {
        WavePassageEffect.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
    else if (type == SeismicLabAPI::SeismicLabFeatureSpectrum::getClassTypeId()) {
        SpectrumModel.setEnums(findAllSeismicLabFeaturesOfThisType(type));
    }
}

void SeismicLabSimulation::resetAllEnums()
{
  CoherenceFunction.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureCoherence::getClassTypeId()));
  CorrelationFunction.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureCorrelation::getClassTypeId()));
  CumulativeProbabilityDistribution.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureCumulativeProbabilityDistribution::getClassTypeId()));
  FrequencyDistribution.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureFrequencyDistribution::getClassTypeId()));
  Kurtosis.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureKurtosis::getClassTypeId()));
  SpatialDistribution.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureLocationDistribution::getClassTypeId()));
  MatrixTool.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureMatrixTool::getClassTypeId()));
  MeanFunction.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureMeanAcceleration::getClassTypeId()));
  ModulationFunction.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureModulation::getClassTypeId()));
  PeakFactor.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeaturePeakFactor::getClassTypeId()));
  ProbabilityDensityFunction.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureProbabilityDensityFunction::getClassTypeId()));
  SpectrumDecompositionMethod.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeaturePSDDecompositionMethod::getClassTypeId()));
  RandomnessProvider.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureRandomness::getClassTypeId()));
  ShearVelocityOfFlow.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureShearVelocityOfFlow::getClassTypeId()));
  SimulationMethod.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureSimulationMethod::getClassTypeId()));
  Skewness.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureSkewness::getClassTypeId()));
  StandardDeviation.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureStandardDeviation::getClassTypeId()));
  TableTool.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureTableTool::getClassTypeId()));
  UserDefinedRPSObject.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureUserDefinedRPSObject::getClassTypeId()));
  VarianceFunction.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureVariance::getClassTypeId()));
  WavePassageEffect.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureWavePassageEffect::getClassTypeId()));
  SpectrumModel.setEnums(findAllSeismicLabFeaturesOfThisType(SeismicLabAPI::SeismicLabFeatureSpectrum::getClassTypeId()));
}

QStringList SeismicLabSimulation::findAllSeismicLabFeatures(Base::Type type)
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

QStringList SeismicLabSimulation::findAllSeismicLabFeaturesByGoupAndType(QString group, QString type)
{
    QStringList featureList;
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc) return featureList;
    auto features = this->getAllChildren();
    for (auto& feat : features) {
       auto myFeat = static_cast<SeismicLabAPI::SeismicLabFeature*>(feat);
       if (myFeat && myFeat->FeatureType.getStrValue() == type.toUtf8().constData() && myFeat->FeatureGroup.getStrValue() == group.toUtf8().constData())
    featureList.append(QString::fromUtf8(myFeat->getNameInDocument()));
    }
    return featureList;
}

std::vector<std::string> SeismicLabSimulation::findAllSeismicLabFeaturesOfThisType(Base::Type type)
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

Base::Type SeismicLabSimulation::getRPSType(QString group)
{
    if (group == SeismicLab::SeismicLabUtils::objGroupCoherenceFunction) {
        return SeismicLabAPI::IrpsSLCoherence::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCorrelationFunction) {
        return SeismicLabAPI::IrpsSLCorrelation::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution) {
        return SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution) {
        return SeismicLabAPI::IrpsSLFrequencyDistribution::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupKurtosis) {
        return SeismicLabAPI::IrpsSLKurtosis::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupLocationDistribution) {
        return SeismicLabAPI::IrpsSLLocationDistribution::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMatrixTool) {
        return SeismicLabAPI::IrpsSLMatrixTool::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile) {
        return SeismicLabAPI::IrpsSLMeanAcceleration::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupModulationFunction) {
        return SeismicLabAPI::IrpsSLModulation::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupPeakFactor) {
        return SeismicLabAPI::IrpsSLPeakFactor::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction) {
        return SeismicLabAPI::IrpsSLProbabilityDensityFunction::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod) {
        return SeismicLabAPI::IrpsSLPSDdecompositionMethod::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupRandomnessProvider) {
        return SeismicLabAPI::IrpsSLRandomness::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow) {
        return SeismicLabAPI::IrpsSLShearVelocityOfFlow::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSimulationMethod) {
        return SeismicLabAPI::IrpsSLSimulationMethod::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSimulationMethod) {
        return SeismicLabAPI::IrpsSLSkewness::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupStandardDeviation) {
        return SeismicLabAPI::IrpsSLStandardDeviation::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupTableTool) {
        return SeismicLabAPI::IrpsSLTableTool::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject) {
        return SeismicLabAPI::IrpsSLUserDefinedRPSObject::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupVariance) {
        return SeismicLabAPI::IrpsSLVariance::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupWavePassageEffect) {
        return SeismicLabAPI::IrpsSLWavePassageEffect::getClassTypeId();
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrum) {
        return SeismicLabAPI::IrpsSLSpectrum::getClassTypeId();
    }
}

std::vector<Base::Type> SeismicLabSimulation::getRPSTypesOfPluggableFeatures()
{
    std::vector<Base::Type> types;
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureLocationDistribution::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureMeanAcceleration::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureSpectrum::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeaturePSDDecompositionMethod::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureCoherence::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureSimulationMethod::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureFrequencyDistribution::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureRandomness::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureModulation::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureCorrelation::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureTableTool::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureMatrixTool::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureCumulativeProbabilityDistribution::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureKurtosis::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeaturePeakFactor::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureProbabilityDensityFunction::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureShearVelocityOfFlow::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureSkewness::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureStandardDeviation::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureVariance::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureWavePassageEffect::getClassTypeId());
    types.emplace_back(SeismicLabAPI::SeismicLabFeatureUserDefinedRPSObject::getClassTypeId());

    return types;
}

std::vector<QString> SeismicLabSimulation::getSeismicLabPluggableFeatures()
{
    std::vector<QString> groups;
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupLocationDistribution);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupSpectrum);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupCoherenceFunction);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupSimulationMethod);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupRandomnessProvider);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupModulationFunction);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupCorrelationFunction);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupTableTool);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupMatrixTool);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupKurtosis);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupPeakFactor);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupSkewness);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupStandardDeviation);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupVariance);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupWavePassageEffect);
    groups.emplace_back(SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject);

    return groups;
}

bool SeismicLabSimulation::doubleClicked(void) 
{
    return true;
}

void SeismicLabSimulation::onChanged(const App::Property* prop)
{
     ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/SeismicLab/General");
     int limitAutoAct = hGrp->GetBool("AutomaticLargeScaleModeActivation", true);
    
    hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/SeismicLab/Limit");
    int numberOfSampleLimit = hGrp->GetInt("MaxSN", 300);
    int numberOfProcessLimit = hGrp->GetInt("MaxSPN", 300);
    int numberOfFrequencyLimit = hGrp->GetInt("MaxFIN", 102400);
    int numberOfTimeIncrementsLimit = hGrp->GetInt("MaxTIN", 61400);
    int numberOfDirectionIncrementsLimit = hGrp->GetInt("MaxDIN", 100000);
    int numberOfIncrementOfVariableXLimit = hGrp->GetInt("MaxXIN", 100000);

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
    else if (prop == &SampleIndex) {
        if (SampleIndex.getValue() < 0)
            SampleIndex.setValue(0);
        if (SampleIndex.getValue() > NumberOfSample.getValue() - 1)
            SampleIndex.setValue(NumberOfSample.getValue() - 1);
    }
    else if (prop == &NumberOfSample) {
        if (NumberOfSample.getValue() < 1) 
        {
            NumberOfSample.setValue(1);
        }
        if (NumberOfSample.getValue() > numberOfSampleLimit && limitAutoAct)
        {
            LargeScaleSimulationMode.setValue(true);
            Base::Console().Warning("The number of sample(%s) has exceded its limit(%s). Large scale simulation mode has been activated.\n",NumberOfSample.getValue(), numberOfSampleLimit);
        }
        else {
            LargeScaleSimulationMode.setValue(false);
        }
    }
    else if (prop == &NumberOfProcess) {
        if (NumberOfProcess.getValue() < 1) 
        {
            NumberOfProcess.setValue(1);
        }
        if (NumberOfProcess.getValue() > numberOfProcessLimit && limitAutoAct)
        {
            LargeScaleSimulationMode.setValue(true);
            Base::Console().Warning("The number of process(%s) has exceded its limit(%s). Large scale simulation mode has been activated.\n",NumberOfProcess.getValue(), numberOfProcessLimit);
        }
        else {
            LargeScaleSimulationMode.setValue(false);
        }
    }
    else if (prop == &NumberOfFrequency) {
        if (NumberOfFrequency.getValue() < 1) 
        {
            NumberOfFrequency.setValue(1);
        }
        if (NumberOfFrequency.getValue() > numberOfFrequencyLimit && limitAutoAct)
        {
            LargeScaleSimulationMode.setValue(true);
            Base::Console().Warning("The number of frequency increments(%s) has exceded its limit(%s). Large scale simulation mode has been activated.\n",NumberOfFrequency.getValue(), numberOfFrequencyLimit);
        }
        else {
            LargeScaleSimulationMode.setValue(false);
        }
    }
    else if (prop == &NumberOfTimeIncrements) {
        if (NumberOfTimeIncrements.getValue() < 1) 
        {
            NumberOfTimeIncrements.setValue(1);
        }
        if (NumberOfTimeIncrements.getValue() > numberOfTimeIncrementsLimit && limitAutoAct)
        {
            LargeScaleSimulationMode.setValue(true);
            Base::Console().Warning("The number of time increments(%s) has exceded its limit(%s). Large scale simulation mode has been activated.\n",NumberOfTimeIncrements.getValue(), numberOfTimeIncrementsLimit);

        }
        else {
            LargeScaleSimulationMode.setValue(false);
        }
    }
    else if (prop == &NumberOfDirectionIncrements) {
        if (NumberOfDirectionIncrements.getValue() < 1) 
        {
            NumberOfDirectionIncrements.setValue(1);
        }
        if (NumberOfDirectionIncrements.getValue() > numberOfDirectionIncrementsLimit && limitAutoAct)
        {
            LargeScaleSimulationMode.setValue(true);
            Base::Console().Warning("The number of direction increments(%s) has exceded its limit(%s). Large scale simulation mode has been activated.\n",NumberOfDirectionIncrements.getValue(), numberOfDirectionIncrementsLimit);
        }
        else {
            LargeScaleSimulationMode.setValue(false);
        }
    }
    else if (prop == &NumberOfIncrementOfVariableX) {
        if (NumberOfIncrementOfVariableX.getValue() < 1) 
        {
            NumberOfIncrementOfVariableX.setValue(1);
        }
        if (NumberOfIncrementOfVariableX.getValue() > numberOfIncrementOfVariableXLimit && limitAutoAct)
        {
            LargeScaleSimulationMode.setValue(true);
            Base::Console().Warning("The number of increments(%s) of the variable X has exceded its limit(%s). Large scale simulation mode has been activated.\n",NumberOfIncrementOfVariableX.getValue(), numberOfIncrementOfVariableXLimit);
        }
        else {
            LargeScaleSimulationMode.setValue(false);
        }
    }
   
    updateSimulationData();

    Simulation::onChanged(prop);
}


SeismicLabAPI::SeismicLabFeatureDescription* SeismicLabSimulation::GetSeismicLabPluggedSeismicLabFeatureDescription(const QString& objectGroup, const QString& objName)
{
    SeismicLabFeatureDescription* pluggedSeismicLabFeatureDescription = new SeismicLabFeatureDescription();
    std::string pluginName;
    std::string descrip;
    std::string pubTitle;
    std::string pubLink;
    std::string pubAuthor;
    std::string pubDate;
    std::string version;
    bool stationarity;
    std::string objectName = objName.toUtf8().constData();

    if (objectGroup == SeismicLab::SeismicLabUtils::objGroupLocationDistribution) {
        pluginName = CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsLocationDistributionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsLocationDistributionFactory::GetTitleMap()[objectName];
        pubLink = CrpsLocationDistributionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsLocationDistributionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsLocationDistributionFactory::GetDateMap()[objectName];
        version = CrpsLocationDistributionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsLocationDistributionFactory::GetStationarityMap()[objectName];

    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile) {
        pluginName = CrpsMeanFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsMeanFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsMeanFactory::GetTitleMap()[objectName];
        pubLink = CrpsMeanFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsMeanFactory::GetAuthorMap()[objectName];
        pubDate = CrpsMeanFactory::GetDateMap()[objectName];
        version = CrpsMeanFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsMeanFactory::GetStationarityMap()[objectName];

    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupSpectrum) {
        pluginName = CrpsSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsSpectrumFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsSpectrumFactory::GetTitleMap()[objectName];
        pubLink = CrpsSpectrumFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsSpectrumFactory::GetAuthorMap()[objectName];
        pubDate = CrpsSpectrumFactory::GetDateMap()[objectName];
        version = CrpsSpectrumFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsSpectrumFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod) {
        pluginName = CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsPSDdecomMethodFactory::GetTitleMap()[objectName];
        pubLink = CrpsPSDdecomMethodFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsPSDdecomMethodFactory::GetAuthorMap()[objectName];
        pubDate = CrpsPSDdecomMethodFactory::GetDateMap()[objectName];
        version = CrpsPSDdecomMethodFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsPSDdecomMethodFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupCoherenceFunction) {
        pluginName = CrpsCoherenceFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsCoherenceFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsCoherenceFactory::GetTitleMap()[objectName];
        pubLink = CrpsCoherenceFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsCoherenceFactory::GetAuthorMap()[objectName];
        pubDate = CrpsCoherenceFactory::GetDateMap()[objectName];
        version = CrpsCoherenceFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsCoherenceFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupSimulationMethod) {
        pluginName = CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsSimuMethodFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsSimuMethodFactory::GetTitleMap()[objectName];
        pubLink = CrpsSimuMethodFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsSimuMethodFactory::GetAuthorMap()[objectName];
        pubDate = CrpsSimuMethodFactory::GetDateMap()[objectName];
        version = CrpsSimuMethodFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsSimuMethodFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution) {
        pluginName = CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsFrequencyDistributionFactory::GetTitleMap()[objectName];
        pubLink = CrpsFrequencyDistributionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsFrequencyDistributionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsFrequencyDistributionFactory::GetDateMap()[objectName];
        version = CrpsFrequencyDistributionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsFrequencyDistributionFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupRandomnessProvider) {
        pluginName = CrpsRandomnessFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsRandomnessFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsRandomnessFactory::GetTitleMap()[objectName];
        pubLink = CrpsRandomnessFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsRandomnessFactory::GetAuthorMap()[objectName];
        pubDate = CrpsRandomnessFactory::GetDateMap()[objectName];
        version = CrpsRandomnessFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsRandomnessFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupModulationFunction) {
        pluginName = CrpsModulationFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsModulationFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsModulationFactory::GetTitleMap()[objectName];
        pubLink = CrpsModulationFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsModulationFactory::GetAuthorMap()[objectName];
        pubDate = CrpsModulationFactory::GetDateMap()[objectName];
        version = CrpsModulationFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsModulationFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupTableTool) {
        pluginName = CrpsTableToolFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsTableToolFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsTableToolFactory::GetTitleMap()[objectName];
        pubLink = CrpsTableToolFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsTableToolFactory::GetAuthorMap()[objectName];
        pubDate = CrpsTableToolFactory::GetDateMap()[objectName];
        version = CrpsTableToolFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsTableToolFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupMatrixTool) {
        pluginName = CrpsMatrixToolFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsMatrixToolFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsMatrixToolFactory::GetTitleMap()[objectName];
        pubLink = CrpsMatrixToolFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsMatrixToolFactory::GetAuthorMap()[objectName];
        pubDate = CrpsMatrixToolFactory::GetDateMap()[objectName];
        version = CrpsMatrixToolFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsMatrixToolFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject) {
        pluginName = CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsUserDefinedRPSObjectFactory::GetTitleMap()[objectName];
        pubLink = CrpsUserDefinedRPSObjectFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsUserDefinedRPSObjectFactory::GetAuthorMap()[objectName];
        pubDate = CrpsUserDefinedRPSObjectFactory::GetDateMap()[objectName];
        version = CrpsUserDefinedRPSObjectFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsUserDefinedRPSObjectFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution) {
        pluginName = CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsCumulativeProbabilityDistributionFactory::GetTitleMap()[objectName];
        pubLink = CrpsCumulativeProbabilityDistributionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsCumulativeProbabilityDistributionFactory::GetDateMap()[objectName];
        version = CrpsCumulativeProbabilityDistributionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsCumulativeProbabilityDistributionFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupKurtosis) {
        pluginName = CrpsKurtosisFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsKurtosisFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsKurtosisFactory::GetTitleMap()[objectName];
        pubLink = CrpsKurtosisFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsKurtosisFactory::GetAuthorMap()[objectName];
        pubDate = CrpsKurtosisFactory::GetDateMap()[objectName];
        version = CrpsKurtosisFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsKurtosisFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupPeakFactor) {
        pluginName = CrpsPeakFactorFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsPeakFactorFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsPeakFactorFactory::GetTitleMap()[objectName];
        pubLink = CrpsPeakFactorFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsPeakFactorFactory::GetAuthorMap()[objectName];
        pubDate = CrpsPeakFactorFactory::GetDateMap()[objectName];
        version = CrpsPeakFactorFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsPeakFactorFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction) {
        pluginName = CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsProbabilityDensityFunctionFactory::GetTitleMap()[objectName];
        pubLink = CrpsProbabilityDensityFunctionFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsProbabilityDensityFunctionFactory::GetAuthorMap()[objectName];
        pubDate = CrpsProbabilityDensityFunctionFactory::GetDateMap()[objectName];
        version = CrpsProbabilityDensityFunctionFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsProbabilityDensityFunctionFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow) {
        pluginName = CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsShearVelocityOfFlowFactory::GetTitleMap()[objectName];
        pubLink = CrpsShearVelocityOfFlowFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsShearVelocityOfFlowFactory::GetAuthorMap()[objectName];
        pubDate = CrpsShearVelocityOfFlowFactory::GetDateMap()[objectName];
        version = CrpsShearVelocityOfFlowFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsShearVelocityOfFlowFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupSkewness) {
        pluginName = CrpsSkewnessFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsSkewnessFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsSkewnessFactory::GetTitleMap()[objectName];
        pubLink = CrpsSkewnessFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsSkewnessFactory::GetAuthorMap()[objectName];
        pubDate = CrpsSkewnessFactory::GetDateMap()[objectName];
        version = CrpsSkewnessFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsSkewnessFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupStandardDeviation) {
        pluginName = CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsStandardDeviationFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsStandardDeviationFactory::GetTitleMap()[objectName];
        pubLink = CrpsStandardDeviationFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsStandardDeviationFactory::GetAuthorMap()[objectName];
        pubDate = CrpsStandardDeviationFactory::GetDateMap()[objectName];
        version = CrpsStandardDeviationFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsStandardDeviationFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupVariance) {
        pluginName = CrpsVarianceFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsVarianceFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsVarianceFactory::GetTitleMap()[objectName];
        pubLink = CrpsVarianceFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsVarianceFactory::GetAuthorMap()[objectName];
        pubDate = CrpsVarianceFactory::GetDateMap()[objectName];
        version = CrpsVarianceFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsVarianceFactory::GetStationarityMap()[objectName];
    }
    else if (objectGroup == SeismicLab::SeismicLabUtils::objGroupWavePassageEffect) {
        pluginName = CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsWavePassageEffectFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsWavePassageEffectFactory::GetTitleMap()[objectName];
        pubLink = CrpsWavePassageEffectFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsWavePassageEffectFactory::GetAuthorMap()[objectName];
        pubDate = CrpsWavePassageEffectFactory::GetDateMap()[objectName];
        version = CrpsWavePassageEffectFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsWavePassageEffectFactory::GetStationarityMap()[objectName];
    }

    pluggedSeismicLabFeatureDescription->PluginName.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())] ->GetPluginName().toUtf8().constData());
    pluggedSeismicLabFeatureDescription->ReleaseDate.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())] ->GetPluginReleaseDate().toUtf8().constData());
    pluggedSeismicLabFeatureDescription->Path.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginSubFolder().toUtf8().constData());
    pluggedSeismicLabFeatureDescription->Author.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginAuthor().toUtf8().constData());
    pluggedSeismicLabFeatureDescription->PluginVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginVersion().toUtf8().constData());
    pluggedSeismicLabFeatureDescription->LabRPSVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetLabRPSVersion().toUtf8().constData());
    pluggedSeismicLabFeatureDescription->APIVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetAPIVersion().toUtf8().constData());
    pluggedSeismicLabFeatureDescription->ObjectName.setValue(objectName);
    pluggedSeismicLabFeatureDescription->Version.setValue(version);
    pluggedSeismicLabFeatureDescription->Stationarity.setValue(stationarity);
    pluggedSeismicLabFeatureDescription->Description.setValue(descrip);
    pluggedSeismicLabFeatureDescription->PublicationTitle.setValue(pubTitle);
    pluggedSeismicLabFeatureDescription->PublicationLink.setValue(pubLink);
    pluggedSeismicLabFeatureDescription->PublicationAuthor.setValue(pubAuthor);
    pluggedSeismicLabFeatureDescription->PublicationDate.setValue(pubDate);

    return pluggedSeismicLabFeatureDescription;
}

void SeismicLabSimulation::createNewSimulation() {}

PyObject* SeismicLabSimulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        PythonObject = Py::Object(new SeismicLabSimulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool SeismicLabSimulation::computeCrossCoherenceVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
   auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
        return false;
    SeismicLabAPI::IrpsSLCoherence* activefeature = static_cast<SeismicLabAPI::IrpsSLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
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
bool SeismicLabSimulation::computeCrossCoherenceVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();

    if (!doc)
        return false;
    SeismicLabAPI::IrpsSLCoherence* activefeature = static_cast<SeismicLabAPI::IrpsSLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
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

bool SeismicLabSimulation::computeCrossCoherenceMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    SeismicLabAPI::IrpsSLCoherence* activefeature = static_cast<SeismicLabAPI::IrpsSLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
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

	
bool SeismicLabSimulation::computeCrossCorrelationVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
        if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLCorrelation* activefeature = static_cast<SeismicLabAPI::IrpsSLCorrelation*>(doc->getObject(_simuData->correlationFunction.getValue()));
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

bool SeismicLabSimulation::computeCrossCorrelationMatrixPP(const double &dTime, mat &dCorrelationMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLCorrelation* activefeature = static_cast<SeismicLabAPI::IrpsSLCorrelation*>(doc->getObject(_simuData->correlationFunction.getValue()));
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

bool SeismicLabSimulation::computeFrequenciesVectorF(const Base::Vector3d &location, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLFrequencyDistribution* activefeature = static_cast<SeismicLabAPI::IrpsSLFrequencyDistribution*>(doc->getObject(_simuData->frequencyDistribution.getValue()));
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
  
bool SeismicLabSimulation::computeFrequenciesMatrixFP(mat& dMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLFrequencyDistribution* activefeature = static_cast<SeismicLabAPI::IrpsSLFrequencyDistribution*>(doc->getObject(_simuData->frequencyDistribution.getValue()));
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

bool SeismicLabSimulation::computeLocationCoordinateMatrixP3(mat& dLocCoord, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLLocationDistribution* activefeature = static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(doc->getObject(_simuData->spatialDistribution.getValue()));
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

bool SeismicLabSimulation::computeMeanAccelerationVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLMeanAcceleration* activefeature = static_cast<SeismicLabAPI::IrpsSLMeanAcceleration*>(doc->getObject(_simuData->meanFunction.getValue()));
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

bool SeismicLabSimulation::computeMeanAccelerationVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLMeanAcceleration* activefeature = static_cast<SeismicLabAPI::IrpsSLMeanAcceleration*>(doc->getObject(_simuData->meanFunction.getValue()));
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

bool SeismicLabSimulation::computeModulationValue(Base::Vector3d location, const double &dFrequency, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLModulation* activefeature = static_cast<SeismicLabAPI::IrpsSLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active modulation function feature found.\n");
    return false;
    }
    bool returnResult = activefeature->ComputeModulationValue(*this->getSimulationData(), location, dFrequency, dTime, dValue);
    if (!returnResult)
    {
     Base::Console().Error("The computation of the modulation value has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeismicLabSimulation::computeModulationVectorT(Base::Vector3d location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLModulation* activefeature = static_cast<SeismicLabAPI::IrpsSLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active modulation function feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeModulationVectorT(*this->getSimulationData(), location, dFrequency, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the modulation vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeismicLabSimulation::computeModulationVectorP(const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLModulation* activefeature = static_cast<SeismicLabAPI::IrpsSLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active modulation function feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    dValVector.resize(this->getSimulationData()->numberOfSpatialPosition.getValue());
    bool returnResult = activefeature->ComputeModulationVectorP(*this->getSimulationData(), dFrequency, dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the modulation vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeismicLabSimulation::computeModulationVectorF(Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLModulation* activefeature = static_cast<SeismicLabAPI::IrpsSLModulation*>(doc->getObject(_simuData->modulationFunction.getValue()));
    if (!activefeature) {
    Base::Console().Error("No valid active modulation function feature found.\n");
    return false;
    }
    dVarVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    dValVector.resize(this->getSimulationData()->numberOfTimeIncrements.getValue());
    bool returnResult = activefeature->ComputeModulationVectorF(*this->getSimulationData(), location, dTime, dVarVector, dValVector);
    if (!returnResult) {
        Base::Console().Error("The computation of the modulation vector has failed.\n");
        return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}




bool SeismicLabSimulation::computeDecomposedCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLPSDdecompositionMethod* activefeature = static_cast<SeismicLabAPI::IrpsSLPSDdecompositionMethod*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));
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

bool SeismicLabSimulation::computeDecomposedCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLPSDdecompositionMethod* activefeature = static_cast<SeismicLabAPI::IrpsSLPSDdecompositionMethod*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));
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

bool SeismicLabSimulation::computeDecomposedCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLPSDdecompositionMethod* activefeature = static_cast<SeismicLabAPI::IrpsSLPSDdecompositionMethod*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));
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

bool SeismicLabSimulation::generateRandomMatrixFP(mat& dRandomValueArray, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLRandomness* activefeature = static_cast<SeismicLabAPI::IrpsSLRandomness*>(doc->getObject(_simuData->randomnessProvider.getValue()));
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

bool SeismicLabSimulation::generateRandomCubeFPS(cube& dRandomValueCube, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLRandomness* activefeature = static_cast<SeismicLabAPI::IrpsSLRandomness*>(doc->getObject(_simuData->randomnessProvider.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active randomness provider feature found.\n");
        return false;
    }
    dRandomValueCube.resize(this->getSimulationData()->numberOfFrequency.getValue(),
                            this->getSimulationData()->numberOfSpatialPosition.getValue(),
                            this->getSimulationData()->numberOfSample.getValue());

    bool returnResult = activefeature->GenerateRandomCubeFPS(*this->getSimulationData(), dRandomValueCube);
    if (!returnResult)
    {
     Base::Console().Error("The computation of random phase cube has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}

bool SeismicLabSimulation::computeCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSpectrum* activefeature = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
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

bool SeismicLabSimulation::computeCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSpectrum* activefeature = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
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

bool SeismicLabSimulation::computeCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &psdMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSpectrum* activefeature = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
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

bool SeismicLabSimulation::computeAutoSpectrumValue(const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSpectrum* activefeature = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
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
    
bool SeismicLabSimulation::computeAutoSpectrumVectorF(const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSpectrum* activefeature = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
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

bool SeismicLabSimulation::computeAutoSpectrumVectorT(const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSpectrum* activefeature = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
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

bool SeismicLabSimulation::computeCrossCoherenceValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLCoherence* activefeature = static_cast<SeismicLabAPI::IrpsSLCoherence*>(doc->getObject(_simuData->coherenceFunction.getValue()));
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

bool SeismicLabSimulation::computeCrossCorrelationValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLCorrelation* activefeature = static_cast<SeismicLabAPI::IrpsSLCorrelation*>(doc->getObject(_simuData->correlationFunction.getValue()));
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
bool SeismicLabSimulation::computeMeanAccelerationValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLMeanAcceleration* activefeature = static_cast<SeismicLabAPI::IrpsSLMeanAcceleration*>(doc->getObject(_simuData->meanFunction.getValue()));
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

bool SeismicLabSimulation::computeRandomValue(double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    Base::Console().Error("Sorry this tool is not yet implemented.\n");
    return true;

}

bool SeismicLabSimulation::computeCrossSpectrumValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSpectrum* activefeature = static_cast<SeismicLabAPI::IrpsSLSpectrum*>(doc->getObject(_simuData->spectrumModel.getValue()));
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

bool SeismicLabSimulation::computeFrequencyValue(const Base::Vector3d &location, const int &frequencyIndex, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLFrequencyDistribution* activefeature = static_cast<SeismicLabAPI::IrpsSLFrequencyDistribution*>(doc->getObject(_simuData->frequencyDistribution.getValue()));
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


bool SeismicLabSimulation::tableToolCompute(mat& inputTable, mat &outputTable, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLTableTool* activefeature = static_cast<SeismicLabAPI::IrpsSLTableTool*>(doc->getObject(_simuData->tableTool.getValue()));
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
bool SeismicLabSimulation::matrixToolCompute(mat& inputTable, mat &outputMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLMatrixTool* activefeature = static_cast<SeismicLabAPI::IrpsSLMatrixTool*>(doc->getObject(_simuData->matrixTool.getValue()));
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
bool SeismicLabSimulation::userDefinedRPSObjectCompute(mat &dresult, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLUserDefinedRPSObject* activefeature = static_cast<SeismicLabAPI::IrpsSLUserDefinedRPSObject*>(doc->getObject(_simuData->userDefinedRPSObject.getValue()));
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

bool SeismicLabSimulation::computeCPDValue(const double& x, double& dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution* activefeature = static_cast<SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution*>(doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue()));
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
bool SeismicLabSimulation::computeCPDVectorX(vec& dVarVector, vec& dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution* activefeature = static_cast<SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution*>(doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue()));
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

bool SeismicLabSimulation::computeKurtosisValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLKurtosis* activefeature = static_cast<SeismicLabAPI::IrpsSLKurtosis*>(doc->getObject(_simuData->kurtosis.getValue()));
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
bool SeismicLabSimulation::computeKurtosisVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLKurtosis* activefeature = static_cast<SeismicLabAPI::IrpsSLKurtosis*>(doc->getObject(_simuData->kurtosis.getValue()));
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

bool SeismicLabSimulation::computeKurtosisVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLKurtosis* activefeature = static_cast<SeismicLabAPI::IrpsSLKurtosis*>(doc->getObject(_simuData->kurtosis.getValue()));
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

bool SeismicLabSimulation::computePeakFactorValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLPeakFactor* activefeature = static_cast<SeismicLabAPI::IrpsSLPeakFactor*>(doc->getObject(_simuData->peakFactor.getValue()));
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
bool SeismicLabSimulation::computePeakFactorVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLPeakFactor* activefeature = static_cast<SeismicLabAPI::IrpsSLPeakFactor*>(doc->getObject(_simuData->peakFactor.getValue()));
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

bool SeismicLabSimulation::computePeakFactorVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLPeakFactor* activefeature = static_cast<SeismicLabAPI::IrpsSLPeakFactor*>(doc->getObject(_simuData->peakFactor.getValue()));
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

bool SeismicLabSimulation::computePDFValue(const double& x, double& dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLProbabilityDensityFunction* activefeature = static_cast<SeismicLabAPI::IrpsSLProbabilityDensityFunction*>(doc->getObject(_simuData->probabilityDensityFunction.getValue()));
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

bool SeismicLabSimulation::computePDFVectorX(vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLProbabilityDensityFunction* activefeature = static_cast<SeismicLabAPI::IrpsSLProbabilityDensityFunction*>(doc->getObject(_simuData->probabilityDensityFunction.getValue()));
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

bool SeismicLabSimulation::computeShearVelocityOfFlowValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLShearVelocityOfFlow* activefeature = static_cast<SeismicLabAPI::IrpsSLShearVelocityOfFlow*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));
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
bool SeismicLabSimulation::computeShearVelocityOfFlowVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLShearVelocityOfFlow* activefeature = static_cast<SeismicLabAPI::IrpsSLShearVelocityOfFlow*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));
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
bool SeismicLabSimulation::computeShearVelocityOfFlowVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLShearVelocityOfFlow* activefeature = static_cast<SeismicLabAPI::IrpsSLShearVelocityOfFlow*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));
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

bool SeismicLabSimulation::computeSkewnessValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSkewness* activefeature = static_cast<SeismicLabAPI::IrpsSLSkewness*>(doc->getObject(_simuData->skewness.getValue()));
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
bool SeismicLabSimulation::computeSkewnessVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSkewness* activefeature = static_cast<SeismicLabAPI::IrpsSLSkewness*>(doc->getObject(_simuData->skewness.getValue()));
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
bool SeismicLabSimulation::computeSkewnessVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSkewness* activefeature = static_cast<SeismicLabAPI::IrpsSLSkewness*>(doc->getObject(_simuData->skewness.getValue()));

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

bool SeismicLabSimulation::computeStandardDeviationValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLStandardDeviation* activefeature = static_cast<SeismicLabAPI::IrpsSLStandardDeviation*>(doc->getObject(_simuData->standardDeviation.getValue()));
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
bool SeismicLabSimulation::computeStandardDeviationVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLStandardDeviation* activefeature = static_cast<SeismicLabAPI::IrpsSLStandardDeviation*>(doc->getObject(_simuData->standardDeviation.getValue()));
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
bool SeismicLabSimulation::computeStandardDeviationVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLStandardDeviation* activefeature = static_cast<SeismicLabAPI::IrpsSLStandardDeviation*>(doc->getObject(_simuData->standardDeviation.getValue()));
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

bool SeismicLabSimulation::computeVarianceValue( const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLVariance* activefeature = static_cast<SeismicLabAPI::IrpsSLVariance*>(doc->getObject(_simuData->varianceFunction.getValue()));
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
bool SeismicLabSimulation::computeVarianceVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLVariance* activefeature = static_cast<SeismicLabAPI::IrpsSLVariance*>(doc->getObject(_simuData->varianceFunction.getValue()));
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
bool SeismicLabSimulation::computeVarianceVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
     if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLVariance* activefeature = static_cast<SeismicLabAPI::IrpsSLVariance*>(doc->getObject(_simuData->varianceFunction.getValue()));
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

bool SeismicLabSimulation::computeWavePassageEffectVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLWavePassageEffect* activefeature = static_cast<SeismicLabAPI::IrpsSLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
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
bool SeismicLabSimulation::computeWavePassageEffectVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLWavePassageEffect* activefeature = static_cast<SeismicLabAPI::IrpsSLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
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
bool SeismicLabSimulation::computeWavePassageEffectMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
     if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLWavePassageEffect* activefeature = static_cast<SeismicLabAPI::IrpsSLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
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
bool SeismicLabSimulation::computeWavePassageEffectValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLWavePassageEffect* activefeature = static_cast<SeismicLabAPI::IrpsSLWavePassageEffect*>(doc->getObject(_simuData->wavePassageEffect.getValue()));
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


bool SeismicLabSimulation::simulate(cube &dPhenomenon, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSimulationMethod* activefeature = static_cast<SeismicLabAPI::IrpsSLSimulationMethod*>(doc->getObject(_simuData->simulationMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active simulation method feature found.\n");
        return false;
    }
    dPhenomenon.resize(this->getSimulationData()->numberOfTimeIncrements.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue() + 1, this->getSimulationData()->numberOfSample.getValue());
    dPhenomenon.setZero();

    bool returnResult = activefeature->Simulate(*this->getSimulationData(), dPhenomenon);

    if (!returnResult) {
     Base::Console().Error("The computation of the ground acceleration matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();

    return true;

}

bool SeismicLabSimulation::simulateInLargeScaleMode(std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    SeismicLabAPI::IrpsSLSimulationMethod* activefeature = static_cast<SeismicLabAPI::IrpsSLSimulationMethod*>(doc->getObject(_simuData->simulationMethod.getValue()));
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


void SeismicLabSimulation::setActiveFeature(App::RPSFeature* feature)
{
    if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureCoherence::getClassTypeId())) {
        _simuData->coherenceFunction.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureCorrelation::getClassTypeId())) {
        _simuData->correlationFunction.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureCumulativeProbabilityDistribution::getClassTypeId())) {
        _simuData->cumulativeProbabilityDistribution.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureFrequencyDistribution::getClassTypeId())) {
        _simuData->frequencyDistribution.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureKurtosis::getClassTypeId())) {
        _simuData->kurtosis.setValue(feature->getNameInDocument());
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureLocationDistribution::getClassTypeId())) {
        _simuData->spatialDistribution.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureMatrixTool::getClassTypeId())) {
        _simuData->matrixTool.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureMeanAcceleration::getClassTypeId())) {
        _simuData->meanFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureModulation::getClassTypeId())) {
        _simuData->modulationFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeaturePeakFactor::getClassTypeId())) {
        _simuData->peakFactor.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureProbabilityDensityFunction::getClassTypeId())) {
        _simuData->probabilityDensityFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeaturePSDDecompositionMethod::getClassTypeId())) {
        _simuData->cpsdDecompositionMethod.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureRandomness::getClassTypeId())) {
        _simuData->randomnessProvider.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureShearVelocityOfFlow::getClassTypeId())) {
        _simuData->shearVelocityOfFlow.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureSimulationMethod::getClassTypeId())) {
        _simuData->simulationMethod.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureSkewness::getClassTypeId())) {
        _simuData->skewness.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureStandardDeviation::getClassTypeId())) {
        _simuData->standardDeviation.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureTableTool::getClassTypeId())) {
        _simuData->tableTool.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureUserDefinedRPSObject::getClassTypeId())) {
        _simuData->userDefinedRPSObject.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureVariance::getClassTypeId())) {
        _simuData->varianceFunction.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureWavePassageEffect::getClassTypeId())) {
        _simuData->wavePassageEffect.setValue(feature->getNameInDocument());  
    }
    else if (feature->getTypeId().isDerivedFrom(SeismicLabAPI::SeismicLabFeatureSpectrum::getClassTypeId())) {
        _simuData->spectrumModel.setValue(feature->getNameInDocument());  
    }
}

App::RPSFeature* SeismicLabSimulation::getActiveFeature(const QString group)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;

    if (group == SeismicLab::SeismicLabUtils::objGroupCoherenceFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->coherenceFunction.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCorrelationFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->correlationFunction.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->frequencyDistribution.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupKurtosis) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->kurtosis.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupLocationDistribution) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->spatialDistribution.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMatrixTool) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->matrixTool.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->meanFunction.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupModulationFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->modulationFunction.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupPeakFactor) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->peakFactor.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->probabilityDensityFunction.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->cpsdDecompositionMethod.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupRandomnessProvider) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->randomnessProvider.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->shearVelocityOfFlow.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSimulationMethod) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->simulationMethod.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupStandardDeviation) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->standardDeviation.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupTableTool) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->tableTool.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->userDefinedRPSObject.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupVariance) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->varianceFunction.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupWavePassageEffect) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->wavePassageEffect.getValue()));  
    }
    else if (group == SeismicLab::SeismicLabUtils::objGroupSpectrum) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->spectrumModel.getValue()));  
    }
}

std::vector<App::RPSFeature*> SeismicLabSimulation::getAllFeatures(const QString group)
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

App::DocumentObject* SeismicLabSimulation::getActiveCoherence()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->coherenceFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveCorrelation()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->correlationFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveCumulativeProbabilityDistribution()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->cumulativeProbabilityDistribution.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveFrequencyDistribution()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->frequencyDistribution.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveKurtosis()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->kurtosis.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveLocationDistribution()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->spatialDistribution.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveMeanAcceleration()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->meanFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveModulation()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->modulationFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActivePeakFactor()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->peakFactor.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveProbabilityDensityFunction()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->probabilityDensityFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActivePSDDecompositionMethod()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->cpsdDecompositionMethod.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveRandomness()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->randomnessProvider.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveShearVelocityOfFlow()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->shearVelocityOfFlow.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveSimulationMethod()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->simulationMethod.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveSkewness()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->skewness.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveStandardDeviation()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->standardDeviation.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveUserDefinedRPSObject()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->userDefinedRPSObject.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveVariance()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->varianceFunction.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveWavePassageEffect()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->wavePassageEffect.getValue());
    return activeFeature;
}

App::DocumentObject* SeismicLabSimulation::getActiveSpectrum()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->spectrumModel.getValue());
    return activeFeature;
}

App::DocumentObject* SeismicLabSimulation::getActiveMatrixTool()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->matrixTool.getValue());
    return activeFeature;
}
App::DocumentObject* SeismicLabSimulation::getActiveTableTool()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->tableTool.getValue());
    return activeFeature;
}

App::DocumentObject*  SeismicLabSimulation::addFeature(const std::string featureName, const std::string simulationName, const std::string featureTypeName, const std::string featureGroup)
{
    Base::Type type = getRPSType(QString::fromStdString(featureGroup));
    
    //create the feature
	SeismicLabAPI::SeismicLabFeature* newFeature = this->createFeature(type, featureTypeName, featureName);

	if (!newFeature)
		return nullptr;

	//set the feature properties
	auto featureProperties = this->GetSeismicLabPluggedSeismicLabFeatureDescription(QString::fromLatin1(featureGroup.c_str()), QString::fromLatin1(featureTypeName.c_str()));
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

void SeismicLabSimulation::slotSimulationAbort(const App::Document& Doc) { 
    this->stop(); 
}