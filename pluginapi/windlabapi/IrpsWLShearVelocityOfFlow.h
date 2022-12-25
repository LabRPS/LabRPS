#ifndef IRPSWLSHEARVELOCITYOFFLOW_H
#define IRPSWLSHEARVELOCITYOFFLOW_H

#include "RPSWindLabsimuData.h"

class IrpsWLShearVelocityOfFlow
{
public:

    virtual ~IrpsWLShearVelocityOfFlow() {};

    virtual bool ComputeShearVelocityOfFlowValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual bool ComputeShearVelocityOfFlowVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeShearVelocityOfFlowVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLSHEARVELOCITYOFFLOW_H
