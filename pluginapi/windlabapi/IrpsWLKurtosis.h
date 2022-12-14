#ifndef IRPSWLKURTOSIS_H
#define IRPSWLKURTOSIS_H

#include "RPSWindLabsimuData.h"

class IrpsWLKurtosis
{
public:

    virtual ~IrpsWLKurtosis() {};

    virtual void ComputeKurtosisValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputeKurtosisVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLKURTOSIS_H
