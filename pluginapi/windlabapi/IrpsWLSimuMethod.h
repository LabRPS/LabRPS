#ifndef IRPSWLSIMUMETHOD_H
#define IRPSWLSIMUMETHOD_H

#include "RPSWindLabsimuData.h"

class IrpsWLSimuMethod 
{
public:
    virtual ~IrpsWLSimuMethod() {};

	//Initial setting
	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

	// The simulation function 
	virtual bool Simulate(const CRPSWindLabsimuData &Data, mat &dVelocityArray, int &minProgress, int &maxProgress, int &currentProgress, QStringList &strInformation) = 0;

	// The simulation function in large scale mode 
	virtual bool SimulateInLargeScaleMode(const CRPSWindLabsimuData &Data, QString &strFileName, int &minProgress, int &maxProgress, int &currentProgress, QStringList &strInformation) = 0;

	// The simulation function in Comparision mode 
	virtual bool SimulateInComparisonMode(const CRPSWindLabsimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, int &minProgress, int &maxProgress, int &currentProgress, QStringList &strInformation) = 0;

};
#endif  // IRPSWLSIMUMETHOD_H
