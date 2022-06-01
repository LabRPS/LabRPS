#pragma once

#include "RPSSeismicLabAPIdefines.h"
#include <QStringList>
#include <QObject>
#include "RPS.h"


class RPS_CORE_API CRPSSeismicLabsimuData : public QObject
{

 public:

	// Constructor
	CRPSSeismicLabsimuData();

	// Destructor
	~CRPSSeismicLabsimuData();

	// Large number of process simulation flag
	bool m_bLargeScaleSimulationFlag;

	// whether we are doing comparison or not
	bool  m_bComparisonMode;

	// whether we are doing large scale simulation or not
	bool  m_bLargeScaleSimulationMode;

	// The Number of process
	int m_iNumberOfSpatialPosition;

	// The number of frequency increments
	int m_iNumberOfFrequency;

	// The Number of sample
	int m_iNumberOfSample;

	// Wind Direction
	int m_iDirection;

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

	// The working directory path
	QString m_strWorkingDirPath;

	// simulation Method
	QString m_strSimulationMethod;

	// The selected spatial distribution
	QString m_strSpatialDistribution;

	// The stationarity of the rp
	QString m_strStationarity;

	// The selected spectrum model
	QString m_strSpectrumModel;

	// The selected coherence function
	QString m_strCoherenceFunction;

	// Selected simulation approach
	QString m_strSimulationApproach;

	// Selected Simulation
	QString m_strFreqencyDistribution;

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

	// Selected variance model
	QString m_strSoilType;

	// frequency distribution type
	int m_iFrequencyDistrType;

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

