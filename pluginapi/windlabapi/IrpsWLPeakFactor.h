#ifndef IRPSWLPEAKFACTOR_H
#define IRPSWLPEAKFACTOR_H

#include "RPSWindLabsimuData.h"

class IrpsWLPeakFactor
{
public:

    virtual ~IrpsWLPeakFactor() {};

    virtual bool ComputePeakFactorValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual bool ComputePeakFactorVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputePeakFactorVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLPEAKFACTOR_H
