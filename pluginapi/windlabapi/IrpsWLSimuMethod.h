#pragma once
#include "RPSWindLabsimuData.h"

class IrpsWLSimuMethod 
{
public:
	//Initial setting
	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

	// The simulation function 
	virtual bool Simulate(const CRPSWindLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation) = 0;

	// The simulation function in large scale mode 
	virtual bool SimulateInLargeScaleMode(const CRPSWindLabsimuData &Data, QString &strFileName, QStringList &strInformation) = 0;

	// The simulation function in Comparision mode 
	virtual bool SimulateInComparisonMode(const CRPSWindLabsimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, QStringList &strInformation) = 0;

};