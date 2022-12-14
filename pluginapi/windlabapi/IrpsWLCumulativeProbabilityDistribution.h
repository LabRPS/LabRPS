#ifndef IRPSWLCPD_H
#define IRPSWLCPD_H

#include "RPSWindLabsimuData.h"

class IrpsWLCumulativeProbabilityDistribution
{
public:

    virtual ~IrpsWLCumulativeProbabilityDistribution() {};

    virtual void ComputeCDFValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputeCDFVectorP(const CRPSWindLabsimuData &Data,  vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLCPD_H
