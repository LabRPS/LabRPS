#ifndef IRPSWLSHEARVELOCITYOFFLOW_H
#define IRPSWLSHEARVELOCITYOFFLOW_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureShearVelocityOfFlow.h>

namespace WindLabAPI {

class IrpsWLShearVelocityOfFlow : public WindLabAPI::WindLabFeatureShearVelocityOfFlow
{
public:

    virtual ~IrpsWLShearVelocityOfFlow() {};

    virtual bool ComputeShearVelocityOfFlowValue(const WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeShearVelocityOfFlowVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeShearVelocityOfFlowVectorT(const WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLSHEARVELOCITYOFFLOW_H
