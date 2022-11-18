
#include "IrpsWLSimuMethod.h"

class CRPSDeodatis1987 : public IrpsWLSimuMethod
{
public:
	//Initial setting
	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	// The simulation function 
    bool Simulate(const CRPSWindLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation);

	// The simulation function in large scale mode 
    bool SimulateInLargeScaleMode(const CRPSWindLabsimuData &Data, QString &strFileName, QStringList &strInformation);

};

