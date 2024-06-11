
#ifndef WINDLAB_PLUGIN_SINEMODULATION_H
#define WINDLAB_PLUGIN_SINEMODULATION_H

#include <Mod/WindLabAPI/App/IrpsWLModulation.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CSineModulation : public WindLabAPI::IrpsWLModulation
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CSineModulation);

public:

    CSineModulation();

    ~CSineModulation() {};

  bool ComputeModulationValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue);

  bool ComputeModulationVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

  bool ComputeModulationVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

  bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:
   App::PropertyTime PulseDuration;

};

} // namespace App

#endif // WINDLAB_PLUGIN_SINEMODULATION_H