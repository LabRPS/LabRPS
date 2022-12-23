#ifndef IRPSWLPEAKFACTOR_H
#define IRPSWLPEAKFACTOR_H

#include "RPSWindLabsimuData.h"

class IrpsWLPeakFactor
{
public:

    virtual ~IrpsWLPeakFactor() {};

    virtual void ComputePeakFactorValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputePeakFactorVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual void ComputePeakFactorVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLPEAKFACTOR_H
