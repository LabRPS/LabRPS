
#ifndef SEISMICLAB_PLUGIN_SARAGONIHART1974MODULATION_H
#define SEISMICLAB_PLUGIN_SARAGONIHART1974MODULATION_H

#include <Mod/SeismicLabAPI/App/IrpsSLModulation.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CRPSSaragoniHart1974Modulation: public SeismicLabAPI::IrpsSLModulation
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSSaragoniHart1974Modulation);
public:
	CRPSSaragoniHart1974Modulation();
	
	~CRPSSaragoniHart1974Modulation() {};

    bool ComputeModulationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    bool ComputeModulationVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    bool ComputeModulationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);
    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

public:

    App::PropertyFloat AlphaOne;
    App::PropertyFloat AlphaTwo;
    App::PropertyFloat AlphaThree;


};

} // namespace App

#endif // SEISMICLAB_PLUGIN_SARAGONIHART1974MODULATION_H