#ifndef IRPSWLGUSTFACTOR_H
#define IRPSWLGUSTFACTOR_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureGustFactor.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLGustFactor : public WindLabAPI::WindLabFeatureGustFactor
{
public:

    virtual ~IrpsWLGustFactor() {};

    virtual bool ComputeGustFactorValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeGustFactorVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeGustFactorVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLGUSTFACTOR_H
