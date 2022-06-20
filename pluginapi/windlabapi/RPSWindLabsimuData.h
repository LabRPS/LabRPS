#pragma once

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

	// Large number of process simulation flag
	bool largeScaleSimulationFlag;

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
	
	// whether we are doing comparison or not
	bool  comparisonMode;

	// whether we are doing large scale simulation or not
	bool  largeScaleSimulationMode;

	int locationJ;

	int locationK;

	int frequencyIndex;

	int directionIndex;

	int timeIndex;

	// Selected comparison category
	QString comparisonCategory;

	// Nunber of time lags
	int numberOfTimeLags;

};




