#ifndef IRPSWLSKEWNESS_H
#define IRPSWLSKEWNESS_H

#include "RPSWindLabsimuData.h"

class IrpsWLSkewness
{
public:

    virtual ~IrpsWLSkewness() {};

    virtual void ComputeSkewnessValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputeSkewnessVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual void ComputeSkewnessVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLSKEWNESS_H
