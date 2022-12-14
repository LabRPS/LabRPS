#ifndef IRPSWLTURBULENCEINTENSITY_H
#define IRPSWLTURBULENCEINTENSITY_H

#include "RPSWindLabsimuData.h"

class IrpsWLTurbulenceIntensity
{
public:

    virtual ~IrpsWLTurbulenceIntensity() {};

    virtual void ComputeTurbulenceIntensityValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputeTurbulenceIntensityVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLTURBULENCEINTENSITY_H
