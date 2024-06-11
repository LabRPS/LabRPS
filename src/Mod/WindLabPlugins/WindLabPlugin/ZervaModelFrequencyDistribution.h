
#ifndef WINDLAB_PLUGIN_ZERVAMODELFREQUENCYDISTRIBUTION_H
#define WINDLAB_PLUGIN_ZERVAMODELFREQUENCYDISTRIBUTION_H

#include <Mod/WindLabAPI/App/IrpsWLFrequencyDistribution.h>

namespace WindLabAPI { class WindLabSimuData; }

class QStringList;

namespace WindLab {

class ZervaModelFrequencyDistribution : public  WindLabAPI::IrpsWLFrequencyDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::ZervaModelFrequencyDistribution);

public:
    ZervaModelFrequencyDistribution();

    ~ZervaModelFrequencyDistribution() {};

    bool ComputeFrequencyValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

    bool ComputeFrequenciesVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dValVector);
  
    bool ComputeFrequenciesMatrixFP(const WindLabAPI::WindLabSimuData &Data, mat &dMatrix);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

};

} // namespace App

#endif // WINDLAB_PLUGIN_ZERVAMODELFREQUENCYDISTRIBUTION_H