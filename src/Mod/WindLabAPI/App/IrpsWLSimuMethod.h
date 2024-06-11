#ifndef IRPSWLSIMUMETHOD_H
#define IRPSWLSIMUMETHOD_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureSimulationMethod.h>

namespace WindLabAPI {

class IrpsWLSimuMethod : public WindLabAPI::WindLabFeatureSimulationMethod
{
public:
    virtual ~IrpsWLSimuMethod() {};
	
    virtual bool Simulate(const WindLabSimuData &Data, mat &dVelocityArray) = 0;

    virtual bool SimulateInLargeScaleMode(const WindLabSimuData &Data, QString &strFileName) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};


} //namespace WindLabAPI


#endif  // IRPSWLSIMUMETHOD_H
