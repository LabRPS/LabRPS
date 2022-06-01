#pragma once
#include "RPSSeismicLabsimuData.h"

class IrpsSLSimulationMethod
{
public:

	//Initial setting
	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;

	// The simulation function 
	virtual bool Simulate(const CRPSSeismicLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation) = 0;

	// The simulation function in large scale mode 
	virtual bool SimulateInLargeScaleMode(const CRPSSeismicLabsimuData &Data, QString &strFileName, QStringList &strInformation) = 0;

	// The simulation function in Comparision mode 
	virtual bool SimulateInComparisonMode(const CRPSSeismicLabsimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, QStringList &strInformation) = 0;

};