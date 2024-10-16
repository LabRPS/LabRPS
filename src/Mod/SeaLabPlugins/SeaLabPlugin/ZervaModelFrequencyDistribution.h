
#ifndef SEALAB_PLUGIN_ZERVAMODELFREQUENCYDISTRIBUTION_H
#define SEALAB_PLUGIN_ZERVAMODELFREQUENCYDISTRIBUTION_H

#include <Mod/SeaLabAPI/App/IrpsSeLFrequencyDistribution.h>

namespace SeaLabAPI { class SeaLabSimulationData; }

class QStringList;

namespace SeaLab {

class ZervaModelFrequencyDistribution : public  SeaLabAPI::IrpsSeLFrequencyDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::ZervaModelFrequencyDistribution);

public:
    ZervaModelFrequencyDistribution();

    ~ZervaModelFrequencyDistribution() {};

    bool ComputeFrequencyValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

    bool ComputeFrequenciesVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector);
  
    bool ComputeFrequenciesMatrixFP(const SeaLabAPI::SeaLabSimulationData &Data, mat &dMatrix);

    bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

};

} // namespace App

#endif // SEALAB_PLUGIN_ZERVAMODELFREQUENCYDISTRIBUTION_H