#ifndef IRPSWLVARIANCE_H
#define IRPSWLVARIANCE_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureVariance.h>

namespace WindLabAPI {

class IrpsWLVariance : public WindLabAPI::WindLabFeatureVariance
{
public:

    virtual ~IrpsWLVariance() {};

    virtual bool ComputeVarianceValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeVarianceVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeVarianceVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLVARIANCE_H
