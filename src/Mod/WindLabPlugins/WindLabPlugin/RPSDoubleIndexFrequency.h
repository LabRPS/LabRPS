#ifndef WINDLAB_PLUGIN_DOUBLEINDEXFREQUENCY_H
#define WINDLAB_PLUGIN_DOUBLEINDEXFREQUENCY_H

#include <Mod/WindLabAPI/App/IrpsWLFrequencyDistribution.h>
#include <App/PropertyStandard.h>
#include <App/PropertyGeo.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {


class CRPSDoubleIndexFrequency : public  WindLabAPI::IrpsWLFrequencyDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSDoubleIndexFrequency);

public:
    CRPSDoubleIndexFrequency();

    ~CRPSDoubleIndexFrequency() {};

    bool ComputeFrequencyValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

    bool ComputeFrequenciesVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dValVector);
  
    bool ComputeFrequenciesMatrixFP(const WindLabAPI::WindLabSimuData &Data, mat &dMatrix);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

    };

} // namespace App

#endif // WINDLAB_PLUGIN_DOUBLEINDEXFREQUENCY_H