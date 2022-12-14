#ifndef IRPSWLPDF_H
#define IRPSWLPDF_H

#include "RPSWindLabsimuData.h"

class IrpsWLProbabilityDensityFunction
{
public:

    virtual ~IrpsWLProbabilityDensityFunction() {};

    virtual void ComputePDFValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputePDFVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLPDF_H
