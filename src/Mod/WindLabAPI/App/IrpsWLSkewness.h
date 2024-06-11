#ifndef IRPSWLSKEWNESS_H
#define IRPSWLSKEWNESS_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureSkewness.h>

namespace WindLabAPI {

class IrpsWLSkewness : public WindLabAPI::WindLabFeatureSkewness
{
public:

    virtual ~IrpsWLSkewness() {};

    virtual bool ComputeSkewnessValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeSkewnessVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeSkewnessVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLSKEWNESS_H
