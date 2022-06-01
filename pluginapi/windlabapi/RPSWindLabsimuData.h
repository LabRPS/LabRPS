#pragma once

#include "RPSWindLabAPIdefines.h"
#include <QStringList>
#include <QObject>
#include "RPS.h"

class RPS_CORE_API CRPSWindLabsimuData : public QObject
{
 public:

	// Constructor
	CRPSWindLabsimuData();

	// Destructor
	~CRPSWindLabsimuData();

	// Large number of process simulation flag
	bool m_bLargeScaleSimulationFlag;

	// The Number of process
	int m_iNumberOfSpatialPosition;

	// The number of frequency increments
	int m_iNumberOfFrequency;

	// The Number of sample
	int m_iNumberOfSample;

	// Wind Direction
	int m_iDirection;

	// Frequency distribution type
	int m_iFrequencyDistrType;

	// Nunber of time instant
	int m_iNumberOfTimeIncrements;

	// Stationarity
	int m_iStationarity;

	// Stationarity
	int m_iGaussianity;

	// The current frequency increment
	double m_dFrequencyIncrement;

	// Time increment
	double m_dTimeIncrement;

	// Minimum Time, 0 by default
	double m_dMinTime;

	// The minimum frequency
	double m_dMinFrequency;

	// The maximum frequency
	double m_dMaxFrequency;

	////Selected RP
	//QString m_strRandomProcess;

	// The selected spatial distribution
	QString m_strSpatialDistribution;

	// The stationarity of the rp
	QString m_strStationarity;

	// The selected shear velocity
	QString m_strShearVelocity;

	// The selected mean wind profile
	QString m_strMeanFunction;

	// The selected spectrum model
	QString m_strSpectrumModel;

	// The selected coherence function
	QString m_strCoherenceFunction;

	// Selected simulation approach
	QString m_strSimulationApproach;

	// Selected simulation method
	QString m_strSimulationMethod;

	// Selected Simulation
	QString m_strFreqencyDistribution;

	// Selected wind generation method
	QString m_strRPGenerationMethod;

	// Selected CPSD Decomposition Method
	QString m_strCPSDDecompositionMethod;

	// Selected randomness
	QString m_strRandomnessProvider;

	// Selected Modulation function model
	QString m_strModulationFunction;

	// Selected correlation function model
	QString m_strCorrelationFunction;

	// Selected variance model
	QString m_strVarianceFunction;

	// The working directory path
	QString m_strWorkingDirPath;
	
	// whether we are doing comparison or not
	bool  m_bComparisonMode;

	// whether we are doing large scale simulation or not
	bool  m_bLargeScaleSimulationMode;

	int m_iLocationJ;

	int m_iLocationK;

	int m_iFrequencyIndex;

	int m_iDirectionIndex;

	int m_iTimeIndex;

	// Selected comparison category
	QString m_strComparisonCategory;

	// Nunber of time lags
	int m_iNumberOfTimeLags;

};




