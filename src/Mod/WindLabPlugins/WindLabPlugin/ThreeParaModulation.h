
#ifndef WINDLAB_PLUGIN_THREEPARAMODULATION_H
#define WINDLAB_PLUGIN_THREEPARAMODULATION_H

#include <Mod/WindLabAPI/App/IrpsWLModulation.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CThreeParaModulation : public WindLabAPI::IrpsWLModulation
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CThreeParaModulation);
public:
    CThreeParaModulation();

    ~CThreeParaModulation() {};

  bool ComputeModulationValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue);

  bool ComputeModulationVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

  bool ComputeModulationVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

  bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:
    App::PropertyFloat Alpha;

    App::PropertyFloat Betta;

    App::PropertyFloat Lambda; 
};

} // namespace App

#endif // WINDLAB_PLUGIN_THREEPARAMODULATION_H