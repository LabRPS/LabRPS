
#ifndef SEISMICLAB_PLUGIN_EXPONENTIALMODULATION_H
#define SEISMICLAB_PLUGIN_EXPONENTIALMODULATION_H

#include <Mod/SeismicLabAPI/App/IrpsSLModulation.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CRPSExponentialModulation: public SeismicLabAPI::IrpsSLModulation
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSExponentialModulation);
public:
	CRPSExponentialModulation();
	
	~CRPSExponentialModulation() {};

    bool ComputeModulationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, const double &dTime, double &dValue);
    bool ComputeModulationVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector);
    bool ComputeModulationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, vec &dVarVector, vec &dValVector);
    bool ComputeModulationVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector);
    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

public:

    App::PropertyFloat Alpha;
    App::PropertyFloat Beta;
    App::PropertyFloat CoefficientA;


};

} // namespace App

#endif // SEISMICLAB_PLUGIN_EXPONENTIALMODULATION_H