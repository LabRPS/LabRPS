#ifndef IRPSWLVARIANCE_H
#define IRPSWLVARIANCE_H

#include "RPSWindLabsimuData.h"

class IrpsWLVariance
{
public:

    virtual ~IrpsWLVariance() {};

    virtual void ComputeVarianceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputeVarianceVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual void ComputeVarianceVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLVARIANCE_H
