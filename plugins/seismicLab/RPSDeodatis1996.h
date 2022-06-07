
#include "IrpsSLSimulationMethod.h"

class CRPSDeodatis1996 : public IrpsSLSimulationMethod
{
public:
	//Initial setting
	bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation);

	// The simulation function 
	bool Simulate(const CRPSSeismicLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation);

	// The simulation function in large scale mode 
	bool SimulateInLargeScaleMode(const CRPSSeismicLabsimuData &Data, QString &strFileName, QStringList &strInformation);

	// The simulation function in Comparision mode 
	bool SimulateInComparisonMode(const CRPSSeismicLabsimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, QStringList &strInformation);

	//Get the name of the Simulation approach name
	QString GetSimuApproachName(QStringList &strInformation);

};

