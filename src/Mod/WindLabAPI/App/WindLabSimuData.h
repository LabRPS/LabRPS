#ifndef CRPSWINDLABDATA_H
#define CRPSWINDLABDATA_H

#include "RPSWindLabAPIdefines.h"
#include <Mod/WindLabAPI/App/WindLabFeature.h>
#include <App/PropertyContainer.h>
#include <App/PropertyStandard.h>
#include <Mod/WindLabAPI/WindLabAPIGlobal.h>
#include <Base/SmartPtrPy.h>
#include "RPS.h"

#include <QString>

namespace WindLabAPI
{
class RPS_CORE_API WindLabSimuData : public WindLabAPI::WindLabFeature
{
	PROPERTY_HEADER_WITH_OVERRIDE(WindLabAPI::WindLabFeature);

 public:

	// Constructor
	WindLabSimuData();

	// Destructor
	~WindLabSimuData();

	// The Number of process
	App::PropertyInteger numberOfSpatialPosition;

	// The number of frequency increments
	App::PropertyInteger numberOfFrequency;

	// The Number of sample
	App::PropertyInteger numberOfSample;

	// Wind Direction
    App::PropertyEnumeration WindDirection;

	// Nunber of time instant
	App::PropertyInteger numberOfTimeIncrements;

	App::PropertyInteger locationJ;

	App::PropertyInteger locationK;

	App::PropertyInteger frequencyIndex;

	App::PropertyInteger directionIndex;

	App::PropertyInteger timeIndex;

	// Nunber of time lags
	App::PropertyInteger numberOfTimeLags;

	//comparison type: 1 for accuracy, 2 for time and 3 for memory
	App::PropertyInteger comparisonType;

	App::PropertyInteger numberOfWaveLengthIncrements;

	App::PropertyInteger numberOfDirectionIncrements;

	App::PropertyInteger waveLengthIndex;

    App::PropertyInteger numberOfIncrementOfVariableX;

    App::PropertyInteger indexOfVariableX;

	// Stationarity
	App::PropertyBool stationarity;

	// Stationarity
	App::PropertyBool gaussianity;

	// whether we are doing comparison or not
	App::PropertyBool  comparisonMode;

	// whether we are doing large scale simulation or not
	App::PropertyBool  largeScaleSimulationMode;

	// simulation successfull or not flag
	App::PropertyBool isSimulationSuccessful;

	App::PropertyBool isInterruptionRequested;
	
	App::PropertyBool uniformModulation;

	// Minimum Time, 0 by default
	App::PropertyFloat minTime;

	// Maximum Time,
	App::PropertyFloat maxTime;

	// Time increment
	App::PropertyFloat timeIncrement;

	// The minimum frequency
	App::PropertyFloat minFrequency;

	// The current frequency increment
	App::PropertyFloat frequencyIncrement;

	// The maximum frequency
	App::PropertyFloat maxFrequency;

	// The minimum wave length
	App::PropertyFloat minWaveLength;

	// The maximum wave length
	App::PropertyFloat maxWaveLength;

	// The current wave length increment
	App::PropertyFloat waveLengthIncrement;

	// The minimum direction
	App::PropertyFloat minDirection;

	// The maximum direction
	App::PropertyFloat maxDirection;

	// The current direction increment
	App::PropertyFloat directionIncrement;

	App::PropertyFloat incrementOfVariableX;

    App::PropertyFloat minVariableX;

	// The selected spatial distribution
	App::PropertyString spatialDistribution;

	// The selected shear velocity
	App::PropertyString shearVelocity;

	// The selected mean wind profile
	App::PropertyString meanFunction;

	// The selected along wind spectrum model
	App::PropertyString alongWindSpectrumModel;

	// The selected vertical wind spectrum model
	App::PropertyString verticalWindSpectrumModel;

	// The selected across wind spectrum model
	App::PropertyString acrossWindSpectrumModel;

	// The selected coherence function
	App::PropertyString coherenceFunction;

	// Selected simulation method
	App::PropertyString simulationMethod;

	// Selected Simulation
	App::PropertyString frequencyDistribution;

	// Selected CPSD Decomposition Method
	App::PropertyString cpsdDecompositionMethod;

	// Selected randomness
	App::PropertyString randomnessProvider;

	// Selected Modulation function model
	App::PropertyString modulationFunction;

	// Selected correlation function model
	App::PropertyString correlationFunction;

	// Selected variance model
	App::PropertyString varianceFunction;

	// The working directory path
	App::PropertyString workingDirPath;

	// table tool name
	App::PropertyString tableTool;

	// matrix tool name
	App::PropertyString matrixTool;

	// user defined feature name
	App::PropertyString userDefinedRPSObject;

	// Selected comparison category
	App::PropertyString comparisonCategory;

   App::PropertyString cumulativeProbabilityDistribution;
   App::PropertyString gustFactor;
   App::PropertyString kurtosis;
   App::PropertyString peakFactor;
   App::PropertyString probabilityDensityFunction;
   App::PropertyString roughness;
   App::PropertyString shearVelocityOfFlow;
   App::PropertyString skewness;
   App::PropertyString standardDeviation;
   App::PropertyString turbulenceIntensity;
   App::PropertyString turbulenceScale;
   App::PropertyString variance;
   App::PropertyString wavePassageEffect;


   /** @name methods override feature */
//@{
   virtual short mustExecute() const override;
   //@}
    virtual PyObject* getPyObject() override;

   /// python object of this class
   protected:// attributes
   Py::SmartPtr PythonObject;

   protected:
	/// recompute only this object
	virtual App::DocumentObjectExecReturn* recompute() override;
	/// recalculate the feature
	virtual App::DocumentObjectExecReturn* execute() override;
	virtual void onChanged(const App::Property* prop) override;

};

} //namespace WindLabAPI

#endif  // CRPSWINDLABDATA_H



