#pragma once
#include "IrpsSeLSimulationMethod.h"
#include <QStringList>


class CRPSDeodatis1996 : public IrpsSeLSimulationMethod
{
public:
	//Initial setting
	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);

	// The simulation function 
	bool Simulate(const CRPSSeaLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation);

	// The simulation function in large scale mode 
	bool SimulateInLargeScaleMode(const CRPSSeaLabsimuData &Data, QString &strFileName, QStringList &strInformation);

	// The simulation function in Comparision mode 
	bool SimulateInComparisonMode(const CRPSSeaLabsimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, QStringList &strInformation);

	//Get the name of the Simulation approach name
	QString GetSimuApproachName(QStringList &strInformation);

};

