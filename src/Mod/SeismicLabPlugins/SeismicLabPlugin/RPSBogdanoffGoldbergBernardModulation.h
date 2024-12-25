
#ifndef SEISMICLAB_PLUGIN_BOGDANOFFGOLDBERGBERNARD_MODULATION_H
#define SEISMICLAB_PLUGIN_BOGDANOFFGOLDBERGBERNARD_MODULATION_H

#include <Mod/SeismicLabAPI/App/IrpsSLModulation.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CRPSBogdanoffGoldbergBernardModulation: public SeismicLabAPI::IrpsSLModulation
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSBogdanoffGoldbergBernardModulation);
public:
	CRPSBogdanoffGoldbergBernardModulation();
	
	~CRPSBogdanoffGoldbergBernardModulation() {};

    bool ComputeModulationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, const double &dTime, double &dValue);
    bool ComputeModulationVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector);
    bool ComputeModulationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, vec &dVarVector, vec &dValVector);
    bool ComputeModulationVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector);
 
    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

public:

    App::PropertyFloat CoefficientOne;
    App::PropertyFloat CoefficientTwo;

};

} // namespace App

#endif // SEISMICLAB_PLUGIN_EXPONENTIALMODULATION_H