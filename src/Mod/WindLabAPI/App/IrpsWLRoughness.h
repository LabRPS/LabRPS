#ifndef IRPSWLROUGHNESS_H
#define IRPSWLROUGHNESS_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureRoughness.h>

namespace WindLabAPI {

class IrpsWLRoughness : public WindLabAPI::WindLabFeatureRoughness
{
public:

    virtual ~IrpsWLRoughness() {};

    virtual bool ComputeRoughnessValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeRoughnessVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeRoughnessVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLROUGHNESS_H
