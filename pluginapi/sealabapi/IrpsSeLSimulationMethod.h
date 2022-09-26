#ifndef IRPSSELSIMULATIONMETHOD_H
#define IRPSSELSIMULATIONMETHOD_H

#include "RPSSeaLabsimuData.h"

class IrpsSeLSimulationMethod
{
public:
  
    virtual ~IrpsSeLSimulationMethod() {}

	//Initial setting
	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;

	// The simulation function 
	virtual bool Simulate(const CRPSSeaLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation) = 0;

	// The simulation function in large scale mode 
	virtual bool SimulateInLargeScaleMode(const CRPSSeaLabsimuData &Data, QString &strFileName, QStringList &strInformation) = 0;

	// The simulation function in Comparision mode 
	virtual bool SimulateInComparisonMode(const CRPSSeaLabsimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, QStringList &strInformation) = 0;

};

#endif  // IRPSSELSIMULATIONMETHOD_H
