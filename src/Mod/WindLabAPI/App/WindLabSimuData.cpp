#include "PreCompiled.h"

#include "WindLabSimuData.h"
#include <App/WindLabSimuDataPy.h>


using namespace WindLabAPI;
using namespace App;

PROPERTY_SOURCE(WindLabAPI::WindLabSimuData, WindLabAPI::WindLabFeature)

WindLabSimuData::WindLabSimuData()
{

	ADD_PROPERTY_TYPE(numberOfSpatialPosition, (3), "WindLabData", App::Prop_None, "The number of simulation point which is the number of wind processes in a sample");
	ADD_PROPERTY_TYPE(numberOfFrequency, (1024), 0, Prop_None, "The number of frequency increments");
	ADD_PROPERTY_TYPE(numberOfSample, (1), 0, Prop_None, "This is the number of wind field sample in a simulation.");
	ADD_PROPERTY_TYPE(numberOfTimeIncrements, (6144), 0, Prop_None, "This is the number of time increments");
	ADD_PROPERTY_TYPE(locationJ, (1), 0, Prop_None, "The index of the a given wind process in a wind field at a location J");
	ADD_PROPERTY_TYPE(locationK, (1), 0, Prop_None, "The index of the a given wind process in a wind field at a location K");
	ADD_PROPERTY_TYPE(frequencyIndex, (1), 0, Prop_None, "Index correponding to Kth frequency increment");
	ADD_PROPERTY_TYPE(directionIndex, (1), 0, Prop_None, "Index correponding to Kth direction increment");
	ADD_PROPERTY_TYPE(timeIndex, (1), 0, Prop_None, "Index correponding to Kth time increment");
	ADD_PROPERTY_TYPE(numberOfTimeLags, (512), 0, Prop_None, "Number of time lags need for temporal correlation");
	ADD_PROPERTY_TYPE(comparisonType, (1), 0, Prop_None, "comparison time, 1 for accuracy comparison, 2 for computation speed comparison and 3 for memory usage comparison");
	ADD_PROPERTY_TYPE(numberOfWaveLengthIncrements, (1000), 0, Prop_None, "The number of wave length increment");
	ADD_PROPERTY_TYPE(numberOfDirectionIncrements, (1000), 0, Prop_None, "The number of direction increments");
	ADD_PROPERTY_TYPE(waveLengthIndex, (1), 0, Prop_None, "Index correponding to Kth wave length increment");
	ADD_PROPERTY_TYPE(numberOfIncrementOfVariableX, (101), 0, Prop_None, "The number of increments for the variable x");
	ADD_PROPERTY_TYPE(indexOfVariableX, (1), 0, Prop_None, "This current index of the variable x.");
	ADD_PROPERTY_TYPE(stationarity, (true), 0, Prop_None, "This specifies whether the simulated wind is stationary or not.");
	ADD_PROPERTY_TYPE(gaussianity, (true), 0, Prop_None, "This specifies whether the simulated wind is gaussian or not.");
	ADD_PROPERTY_TYPE(comparisonMode, (false), 0, Prop_None, "This specifies whether we are in comparison mode or not.");
	ADD_PROPERTY_TYPE(largeScaleSimulationMode, (false), 0, Prop_None, "This specifies whether we are in large scale simulation or not.");
	ADD_PROPERTY_TYPE(isSimulationSuccessful, (false), 0, Prop_None, "This specifies whether the simulation was successful or not.");
	ADD_PROPERTY_TYPE(isInterruptionRequested, (false), 0, Prop_None, "This specifies whether the simulation has been interrupted or not.");
	ADD_PROPERTY_TYPE(uniformModulation, (true), 0, Prop_None, "This specifies whether a non stataionary wind is uniformly modulated or not.");
	ADD_PROPERTY_TYPE(frequencyIncrement, (0.0039), 0, Prop_None, "This is the frequency increment value");
	ADD_PROPERTY_TYPE(timeIncrement, (0.25), 0, Prop_None, "This is the time increment value");
	ADD_PROPERTY_TYPE(minTime, (0.00), 0, Prop_None, "This is the minimum time value");
	ADD_PROPERTY_TYPE(maxTime, (1536.00), 0, Prop_None, "This is the maximum time value");
	ADD_PROPERTY_TYPE(minFrequency, (0.00), 0, Prop_None, "This is the minimum frequency value");
	ADD_PROPERTY_TYPE(maxFrequency, (4.00), 0, Prop_None, "This is the maximum frequency value");
	ADD_PROPERTY_TYPE(minWaveLength, (0.00), 0, Prop_None, "This is the minimum wave length");
	ADD_PROPERTY_TYPE(maxWaveLength, (4.00), 0, Prop_None, "This is the maximum wave length");
	ADD_PROPERTY_TYPE(waveLengthIncrement, (0.001), 0, Prop_None, "This is the wave length value");
	ADD_PROPERTY_TYPE(minDirection, (0.00), 0, Prop_None, "This is the minimum direction value");
	ADD_PROPERTY_TYPE(maxDirection, (4.00), 0, Prop_None, "This is the maximum direction value");
	ADD_PROPERTY_TYPE(incrementOfVariableX, (0.1), 0, Prop_None, "This is the variable x increment value");
	ADD_PROPERTY_TYPE(minVariableX, (-5.00), 0, Prop_None, "This is the minimum x variable value");
	ADD_PROPERTY_TYPE(directionIncrement, (0.001), 0, Prop_None, "This is the direction increment value");
	ADD_PROPERTY_TYPE(spatialDistribution, (""), 0, Prop_None, "current location distribution name");
	ADD_PROPERTY_TYPE(shearVelocity, (""), 0, Prop_None, "current shear velocity name");
	ADD_PROPERTY_TYPE(meanFunction, (""), 0, Prop_None, "current mean wind profile name");
	ADD_PROPERTY_TYPE(alongWindSpectrumModel, (""), 0, Prop_None, "current along wind spectrum model name");
	ADD_PROPERTY_TYPE(verticalWindSpectrumModel, (""), 0, Prop_None, "current vertical wind spectrum model name");
	ADD_PROPERTY_TYPE(acrossWindSpectrumModel, (""), 0, Prop_None, "current across wind spectrum model name");
	ADD_PROPERTY_TYPE(coherenceFunction, (""), 0, Prop_None, "current coherence function name");
	ADD_PROPERTY_TYPE(simulationMethod, (""), 0, Prop_None, "current simulation method name");
	ADD_PROPERTY_TYPE(frequencyDistribution, (""), 0, Prop_None, "current frequency distribution name");
	ADD_PROPERTY_TYPE(cpsdDecompositionMethod, (""), 0, Prop_None, "current psd decomposition method name");
	ADD_PROPERTY_TYPE(randomnessProvider, (""), 0, Prop_None, "current randomness provider name");
	ADD_PROPERTY_TYPE(modulationFunction, (""), 0, Prop_None, "current modulation function name");
	ADD_PROPERTY_TYPE(correlationFunction, (""), 0, Prop_None, "current correlation function name");
	ADD_PROPERTY_TYPE(varianceFunction, (""), 0, Prop_None, "current variance function name");
	ADD_PROPERTY_TYPE(workingDirPath, (""), 0, Prop_None, "current working direction path");
	ADD_PROPERTY_TYPE(tableTool, (""), 0, Prop_None, "table tool name");
	ADD_PROPERTY_TYPE(matrixTool, (""), 0, Prop_None, "matrix name");
	ADD_PROPERTY_TYPE(userDefinedRPSObject, (""), 0, Prop_None, "user defined rps object name");
	ADD_PROPERTY_TYPE(comparisonCategory, (""), 0, Prop_None, "Comparison category");
	ADD_PROPERTY_TYPE(cumulativeProbabilityDistribution, (""), 0, Prop_None, "current CPD name");
	ADD_PROPERTY_TYPE(gustFactor, (""), 0, Prop_None, "current gust factor name");
	ADD_PROPERTY_TYPE(kurtosis, (""), 0, Prop_None, "current kurtosis name");
	ADD_PROPERTY_TYPE(peakFactor, (""), 0, Prop_None, "current peak factor name");
	ADD_PROPERTY_TYPE(probabilityDensityFunction, (""), 0, Prop_None, "current PDF name");
	ADD_PROPERTY_TYPE(roughness, (""), 0, Prop_None, "current roughness name");
	ADD_PROPERTY_TYPE(shearVelocityOfFlow, (""), 0, Prop_None, "current shear velocity name");
	ADD_PROPERTY_TYPE(skewness, (""), 0, Prop_None, "current skewness name");
	ADD_PROPERTY_TYPE(standardDeviation, (""), 0, Prop_None, "current standard deviation name");
	ADD_PROPERTY_TYPE(turbulenceIntensity, (""), 0, Prop_None, "current turbulence intensity name");
	ADD_PROPERTY_TYPE(turbulenceScale, (""), 0, Prop_None, "current turbulence scale name");
	ADD_PROPERTY_TYPE(variance, (""), 0, Prop_None, "current variance name");
	ADD_PROPERTY_TYPE(wavePassageEffect, (""), 0, Prop_None, "current wave passage name");

	static const char* directions[] = {"Along wind", "Across wind", "Vertical wind", nullptr};
    ADD_PROPERTY_TYPE(WindDirection, ((long int)0), 0, Prop_None, "The wind direction");
    WindDirection.setEnums(directions);
}

WindLabSimuData::~WindLabSimuData()
{
}

short WindLabSimuData::mustExecute(void) const
{
    return WindLabFeature::mustExecute();
}

App::DocumentObjectExecReturn* WindLabSimuData::recompute(void)
{
    try {
        return WindLabAPI::WindLabFeature::recompute();
    }
    catch (Base::Exception& e) {

        App::DocumentObjectExecReturn* ret = new App::DocumentObjectExecReturn(e.what());
        if (ret->Why.empty()) ret->Why = "Unknown exception";
        return ret;
    }
}

App::DocumentObjectExecReturn* WindLabSimuData::execute(void)
{
    return WindLabFeature::execute();
}

void WindLabSimuData::onChanged(const App::Property* prop)
{
    WindLabFeature::onChanged(prop);
}

PyObject* WindLabSimuData::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new WindLabSimuDataPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}