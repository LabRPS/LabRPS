
#ifndef SEISMICLAB_PLUGIN_TRAPEZOIDALMODULATION_H
#define SEISMICLAB_PLUGIN_TRAPEZOIDALMODULATION_H

#include <Mod/SeismicLabAPI/App/IrpsSLModulation.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CRPSTrapezoidalModulation: public SeismicLabAPI::IrpsSLModulation
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSTrapezoidalModulation);
public:
	CRPSTrapezoidalModulation();
	
	~CRPSTrapezoidalModulation() {};

    bool ComputeModulationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    bool ComputeModulationVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    bool ComputeModulationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);
    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

public:

    App::PropertyTime RiseTime;
    App::PropertyTime LevelTime;
    App::PropertyTime MaxTime;


};

} // namespace App

#endif// SEISMICLAB_PLUGIN_TRAPEZOIDALMODULATION_H