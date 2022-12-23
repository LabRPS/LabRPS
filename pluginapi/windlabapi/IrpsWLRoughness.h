#ifndef IRPSWLROUGHNESS_H
#define IRPSWLROUGHNESS_H

#include "RPSWindLabsimuData.h"

class IrpsWLRoughness
{
public:

    virtual ~IrpsWLRoughness() {};

    virtual void ComputeRoughnessValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputeRoughnessVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual void ComputeRoughnessVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLROUGHNESS_H
