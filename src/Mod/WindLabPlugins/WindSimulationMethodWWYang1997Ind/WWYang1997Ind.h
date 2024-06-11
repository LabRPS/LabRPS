
#ifndef windSimulationMethodWWYang1997Ind_PLUGIN_CWWYang1997Ind_H
#define windSimulationMethodWWYang1997Ind_PLUGIN_CWWYang1997Ind_H

#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CWWYang1997Ind : public WindLabAPI::IrpsWLSimuMethod
{
public:
		CWWYang1997Ind();

		~CWWYang1997Ind() {};

	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	// The simulation function 
    bool Simulate(const WindLabAPI::WindLabSimuData& Data, mat &dVelocityArray);

	// The simulation function in large scale mode 
    bool SimulateInLargeScaleMode(const WindLabAPI::WindLabSimuData& Data, QString &strFileName);

private:
int numberOfLocation;
int numberOfFrequencies;
double locationHeight;
double locationSpacing;
double meanSpeed;
double shearVelocity;
double upperCutoffFrequency;
int numberOfTimeIncrements;

};

} // namespace App

#endif // windSimulationMethodWWYang1997Ind_PLUGIN_CWWYang1997Ind_H