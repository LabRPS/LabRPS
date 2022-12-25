#ifndef IRPSWLSKEWNESS_H
#define IRPSWLSKEWNESS_H

#include "RPSWindLabsimuData.h"

class IrpsWLSkewness
{
public:

    virtual ~IrpsWLSkewness() {};

    virtual bool ComputeSkewnessValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual bool ComputeSkewnessVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeSkewnessVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLSKEWNESS_H
