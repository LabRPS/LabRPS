#ifndef CRPSWINDLABDATA_H
#define CRPSWINDLABDATA_H

#include "RPSWindLabAPIdefines.h"
#include <QStringList>
#include "RPS.h"

class RPS_CORE_API CRPSWindLabsimuData
{
 public:

	// Constructor
	CRPSWindLabsimuData();

	// Destructor
	~CRPSWindLabsimuData();

	// The Number of process
	int numberOfSpatialPosition;

	// The number of frequency increments
	int numberOfFrequency;

	// The Number of sample
	int numberOfSample;

	// Wind Direction
	int direction;

	// Frequency distribution type
	int frequencyDistrType;

	// Nunber of time instant
	int numberOfTimeIncrements;

	// Stationarity
	bool stationarity;

	// Stationarity
	bool gaussianity;

	// whether we are doing comparison or not
	bool  comparisonMode;

	// whether we are doing large scale simulation or not
	bool  largeScaleSimulationMode;

	// simulation successfull or not flag
	bool isSimulationSuccessful;

	// The current frequency increment
	double frequencyIncrement;

	// Time increment
	double timeIncrement;

	// Minimum Time, 0 by default
	double minTime;

	// Maximum Time,
	double maxTime;

	// The minimum frequency
	double minFrequency;

	// The maximum frequency
	double maxFrequency;

	// The selected spatial distribution
	QString spatialDistribution;

	// The selected shear velocity
	QString shearVelocity;

	// The selected mean wind profile
	QString meanFunction;

	// The selected spectrum model
	QString spectrumModel;

	// The selected coherence function
	QString coherenceFunction;

	// Selected simulation approach
	QString simulationApproach;

	// Selected simulation method
	QString simulationMethod;

	// Selected Simulation
	QString freqencyDistribution;

	// Selected CPSD Decomposition Method
	QString cpsdDecompositionMethod;

	// Selected randomness
	QString randomnessProvider;

	// Selected Modulation function model
	QString modulationFunction;

	// Selected correlation function model
	QString correlationFunction;

	// Selected variance model
	QString varianceFunction;

	// The working directory path
	QString workingDirPath;

	// table tool name
	QString tableTool;

	// matrix tool name
	QString matrixTool;

	// user defined object name
	QString userDefinedRPSObject;

	int locationJ;

	int locationK;

	int frequencyIndex;

	int directionIndex;

	int timeIndex;

	// Selected comparison category
	QString comparisonCategory;

	// Nunber of time lags
	int numberOfTimeLags;

	bool isInterruptionRequested;

	//comparison type: 1 for accuracy, 2 for time and 3 for memory
	int comparisonType;

    int indexControls;

   QString cumulativeProbabilityDistribution;
   QString gustFactor;
   QString kurtosis;
   QString peakFactor;
   QString probabilityDensityFunction;
   QString roughness;
   QString shearVelocityOfFlow;
   QString skewness;
   QString standardDeviation;
   QString turbulenceIntensity;
   QString turbulenceScale;
   QString variance;
   QString wavePassageEffect;

   bool uniformModulation;

};

#endif  // CRPSWINDLABDATA_H



