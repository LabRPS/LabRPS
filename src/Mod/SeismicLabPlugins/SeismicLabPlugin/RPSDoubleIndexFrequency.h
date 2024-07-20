#ifndef SEISMICLAB_PLUGIN_DOUBLEINDEXFREQUENCY_H
#define SEISMICLAB_PLUGIN_DOUBLEINDEXFREQUENCY_H

#include <Mod/SeismicLabAPI/App/IrpsSLFrequencyDistribution.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {


class CRPSDoubleIndexFrequency : public  SeismicLabAPI::IrpsSLFrequencyDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSDoubleIndexFrequency);

public:
    CRPSDoubleIndexFrequency();

    ~CRPSDoubleIndexFrequency() {};

    bool ComputeFrequencyValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

    bool ComputeFrequenciesVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector);
  
    bool ComputeFrequenciesMatrixFP(const SeismicLabAPI::SeismicLabSimulationData &Data, mat &dMatrix);

    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

    };

} // namespace App

#endif // SEISMICLAB_PLUGIN_DOUBLEINDEXFREQUENCY_H