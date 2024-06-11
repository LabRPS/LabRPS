#ifndef WINDLAB_PLUGIN_TURBULENCEINTENSITYASCE98_H
#define WINDLAB_PLUGIN_TURBULENCEINTENSITYASCE98_H

#include <Mod/WindLabAPI/App/IrpsWLTurbulenceIntensity.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class RPSTurbulenceIntensityASCE798: public WindLabAPI::IrpsWLTurbulenceIntensity
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::RPSTurbulenceIntensityASCE798);

public:
    RPSTurbulenceIntensityASCE798();

    ~RPSTurbulenceIntensityASCE798() {};

    bool ComputeTurbulenceIntensityValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    bool ComputeTurbulenceIntensityVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeTurbulenceIntensityVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

   bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:
   App::PropertyFloat TenMetersHighTurbulenceIntensity;

};

} // namespace App

#endif // WINDLAB_PLUGIN_KRENKCOHERENCE_H