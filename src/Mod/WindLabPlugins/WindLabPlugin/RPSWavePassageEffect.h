
#ifndef WINDLAB_PLUGIN_WAVEPASSAGEEFFECT_H
#define WINDLAB_PLUGIN_WAVEPASSAGEEFFECT_H

#include <Mod/WindLabAPI/App/IrpsWLWavePassageEffect.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CRPSWavePassageEffect: public WindLabAPI::IrpsWLWavePassageEffect
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSWavePassageEffect);
public:
	CRPSWavePassageEffect();
	
	~CRPSWavePassageEffect() {};

    bool ComputeWavePassageEffectVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeWavePassageEffectVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeWavePassageEffectMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

    bool ComputeWavePassageEffectValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:

    App::PropertySpeed ApparentWaveVelocity;
    App::PropertyFloat Coefficient;


};

} // namespace App

#endif // WINDLAB_PLUGIN_CHOLESKYDECOMP_H