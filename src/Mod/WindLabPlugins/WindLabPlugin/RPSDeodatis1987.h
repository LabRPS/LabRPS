
#ifndef WINDLAB_PLUGIN_SIMUMETHOD_H
#define WINDLAB_PLUGIN_SIMUMETHOD_H

#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CRPSDeodatis1987 : public WindLabAPI::IrpsWLSimuMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSDeodatis1987);

public:
    CRPSDeodatis1987();

    ~CRPSDeodatis1987() {};

	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	// The simulation function 
    bool Simulate(const WindLabAPI::WindLabSimuData& Data, mat &dVelocityArray);

	// The simulation function in large scale mode 
    bool SimulateInLargeScaleMode(const WindLabAPI::WindLabSimuData& Data, QString &strFileName);

    bool stationaryWind(const WindLabAPI::WindLabSimuData& Data, mat &dVelocityArray);

};

} // namespace App

#endif // WINDLAB_PLUGIN_SIMUMETHOD_H