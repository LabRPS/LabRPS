#ifndef SEALAB_PLUGIN_DOUBLEINDEXFREQUENCY_H
#define SEALAB_PLUGIN_DOUBLEINDEXFREQUENCY_H

#include <Mod/SeaLabAPI/App/IrpsSeLFrequencyDistribution.h>

namespace SeaLabAPI { class SeaLabSimulationData; }

namespace SeaLab {


class CRPSDoubleIndexFrequency : public  SeaLabAPI::IrpsSeLFrequencyDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSDoubleIndexFrequency);

public:
    CRPSDoubleIndexFrequency();

    ~CRPSDoubleIndexFrequency() {};

    bool ComputeFrequencyValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

    bool ComputeFrequenciesVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector);
  
    bool ComputeFrequenciesMatrixFP(const SeaLabAPI::SeaLabSimulationData &Data, mat &dMatrix);

    bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

    };

} // namespace App

#endif // SEALAB_PLUGIN_DOUBLEINDEXFREQUENCY_H