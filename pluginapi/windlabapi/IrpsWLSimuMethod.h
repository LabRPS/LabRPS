#ifndef IRPSWLSIMUMETHOD_H
#define IRPSWLSIMUMETHOD_H

#include "RPSWindLabsimuData.h"

class IrpsWLSimuMethod 
{
public:
    virtual ~IrpsWLSimuMethod() {};
	
	// The simulation function 
    virtual bool Simulate(const CRPSWindLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation) = 0;

	// The simulation function in large scale mode 
    virtual bool SimulateInLargeScaleMode(const CRPSWindLabsimuData &Data, QString &strFileName, QStringList &strInformation) = 0;

	//Initial setting
	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLSIMUMETHOD_H
