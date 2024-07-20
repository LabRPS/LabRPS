
#ifndef SEISMICLAB_PLUGIN_SINGLELEINDEXFREQUENCY_H
#define SEISMICLAB_PLUGIN_SINGLELEINDEXFREQUENCY_H

#include <Mod/SeismicLabAPI/App/IrpsSLFrequencyDistribution.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

class QStringList;

namespace SeismicLab {

class CRPSSingleIndexFrequency : public  SeismicLabAPI::IrpsSLFrequencyDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSSingleIndexFrequency);

public:
    CRPSSingleIndexFrequency();

    ~CRPSSingleIndexFrequency() {};

    bool ComputeFrequencyValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

    bool ComputeFrequenciesVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector);
  
    bool ComputeFrequenciesMatrixFP(const SeismicLabAPI::SeismicLabSimulationData &Data, mat &dMatrix);

    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

};

} // namespace App

#endif // SEISMICLAB_PLUGIN_SINGLELEINDEXFREQUENCY_H