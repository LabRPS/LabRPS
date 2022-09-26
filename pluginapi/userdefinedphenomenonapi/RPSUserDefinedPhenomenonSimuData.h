#ifndef RPSUSERDEFINEDPHENOMENONDATA_H
#define RPSUSERDEFINEDPHENOMENONDATA_H

#include "RPSUserDefinedPhenomenonAPIdefines.h"
#include <QStringList>
#include "RPS.h"

class RPS_CORE_API CRPSUserDefinedPhenomenonSimuData
{
 public:

	// Constructor
	CRPSUserDefinedPhenomenonSimuData();

	// Destructor
	~CRPSUserDefinedPhenomenonSimuData();

	// The number of frequency increments
	int numberOfProcess;

	// The Number of sample
	int numberOfSample;

	// Nunber of index increments
	int indexSet;

	// index increment
	double indexIncrement;

	// Minimum index value, 0 by default
	double minIndexSet;

	// Maximum index value
	double maxIndexSet;

	// Stationarity
	bool stationarity;

	// Stationarity
	bool gaussianity;

	// whether we are doing large scale simulation or not
	bool  largeScaleSimulationMode;

    // whether we are doing comparison or not
    bool  comparisonMode;

	// simulation successfull or not flag
	bool isSimulationSuccessful;

	// Selected simulation approach
	QString simulationApproach;

	// Selected simulation method
	QString simulationMethod;

	// The working directory path
	QString workingDirPath;

	// The name of the phenonmenon
	QString phenomenon;

    int phenomenonIndex;

    int indexSetIndex;

	bool isInterruptionRequested;

    QString comparisonCategory;
    int comparisonType;


};

#endif  // RPSUSERDEFINEDPHENOMENONDATA_H



