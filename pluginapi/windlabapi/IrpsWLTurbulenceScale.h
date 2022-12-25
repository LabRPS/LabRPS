#ifndef IRPSWLTURBULENCESCALE_H
#define IRPSWLTURBULENCESCALE_H

#include "RPSWindLabsimuData.h"

class IrpsWLTurbulenceScale
{
public:

    virtual ~IrpsWLTurbulenceScale() {};

    virtual bool ComputeTurbulenceScaleValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual bool ComputeTurbulenceScaleVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeTurbulenceScaleVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLTURBULENCESCALE_H
