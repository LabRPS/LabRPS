#pragma once
#include "IrpsWLSimuMethod.h"

class CRPSDeodatis1987 : public IrpsWLSimuMethod
{
public:
	//Initial setting
	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	// The simulation function 
	bool Simulate(const CRPSWindLabsimuData &Data, mat &dVelocityArray, int &minProgress, int &maxProgress, int &currentProgress, QStringList &strInformation);

	// The simulation function in large scale mode 
	bool SimulateInLargeScaleMode(const CRPSWindLabsimuData &Data, QString &strFileName, int &minProgress, int &maxProgress, int &currentProgress, QStringList &strInformation);

	// The simulation function in Comparision mode 
	bool SimulateInComparisonMode(const CRPSWindLabsimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, int &minProgress, int &maxProgress, int &currentProgress, QStringList &strInformation);

	/////////////
	void ComputeCPSDDecom3DMatrice(const CRPSWindLabsimuData &Data, cube &dCPSDDecomMatrice, QStringList &strInformation);

public:


};

