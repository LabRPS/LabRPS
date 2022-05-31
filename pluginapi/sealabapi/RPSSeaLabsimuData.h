#pragma once

#include "RPSSeaLabAPIdefines.h"
#include <QStringList>
#include <QObject>
#include "RPS.h"

class RPS_CORE_API CRPSSeaLabsimuData : public QObject
{

public:

	// Constructor
	CRPSSeaLabsimuData();

	// Destructor
	~CRPSSeaLabsimuData();

	// Large number of process simulation flag
	bool largeScaleSimulationFlag;

	// whether we are doing comparison or not
	bool  comparisonMode;

	// whether we are doing large scale simulation or not
	bool  largeScaleSimulationMode;

	// The Number of process
	int numberOfSpatialPosition;

	// The selected mean wind profile
	QString meanFunction;

	// The number of frequency increments
	int numberOfFrequency;

	// The Number of sample
	int numberOfSample;

	// Wind Direction
	int direction;

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

	// The minimum frequency
	double minFrequency;

	// The maximum frequency
	double maxFrequency;

	// The working directory path
	QString workingDirPath;

	// simulation Method
	QString simulationMethod;

	// The selected spatial distribution
	QString spatialDistribution;

	// The selected spectrum model
	QString spectrumModel;

	// The selected coherence function
	QString coherenceFunction;

	// Selected simulation approach
	QString simulationApproach;

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

	// Selected variance model
	QString waveType;

	// Selected correlation function model
	QString directionalSpectrumFunction;

	// Selected variance model
	QString directionDistributionFunction;

	// Selected variance model
	QString directionSpreadingFunction;

	// frequency distribution type
	int frequencyDistrType;

	// The number of direction increments
	int numberOfDirection;

	// The minimum frequency
	double minDirection;

	// The maximum frequency
	double maxDirection;

	// The maximum frequency
	double directionIncrement;

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

