
#ifndef SEISMICLAB_PLUGIN_WAVEPASSAGEEFFECT_H
#define SEISMICLAB_PLUGIN_WAVEPASSAGEEFFECT_H

#include <Mod/SeismicLabAPI/App/IrpsSLWavePassageEffect.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CRPSWavePassageEffect: public SeismicLabAPI::IrpsSLWavePassageEffect
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSWavePassageEffect);
public:
	CRPSWavePassageEffect();
	
	~CRPSWavePassageEffect() {};

    bool ComputeWavePassageEffectVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeWavePassageEffectVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeWavePassageEffectMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

    bool ComputeWavePassageEffectValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

public:

    App::PropertySpeed ApparentWaveVelocity;
    App::PropertyFloat Coefficient;


};

} // namespace App

#endif // SEISMICLAB_PLUGIN_CHOLESKYDECOMP_H