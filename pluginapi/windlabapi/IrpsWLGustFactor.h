#ifndef IRPSWLGUSTFACTOR_H
#define IRPSWLGUSTFACTOR_H

#include "RPSWindLabsimuData.h"

class IrpsWLGustFactor
{
public:

    virtual ~IrpsWLGustFactor() {};

    virtual void ComputeGustFactorValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputeGustFactorVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual void ComputeGustFactorVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLGUSTFACTOR_H
