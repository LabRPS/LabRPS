#ifndef windSimulationMethodWWYang1997_PLUGIN_CWWYang1997_H
#define windSimulationMethodWWYang1997_PLUGIN_CWWYang1997_H

#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CWWYang1997 : public WindLabAPI::IrpsWLSimuMethod
{
public:
	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	// The simulation function 
    bool Simulate(const WindLabAPI::WindLabSimuData& Data, mat &dVelocityArray);

	// The simulation function in large scale mode 
    bool SimulateInLargeScaleMode(const WindLabAPI::WindLabSimuData& Data, QString &strFileName);

};

} // namespace App

#endif // windSimulationMethodWWYang1997_PLUGIN_CWWYang1997_H