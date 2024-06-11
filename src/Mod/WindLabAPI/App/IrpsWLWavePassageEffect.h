#ifndef IRPSWLWAVEPASSAGEEFFECT_H
#define IRPSWLWAVEPASSAGEEFFECT_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureWavePassageEffect.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLWavePassageEffect : public WindLabAPI::WindLabFeatureWavePassageEffect
{
public:

    virtual ~IrpsWLWavePassageEffect() {};

    virtual bool ComputeWavePassageEffectVectorF(const WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeWavePassageEffectVectorT(const WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeWavePassageEffectMatrixPP(const WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix) = 0;

    virtual bool ComputeWavePassageEffectValue(const WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLWAVEPASSAGEEFFECT_H
