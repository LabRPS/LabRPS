#ifndef IRPSWLSTANDARDDEVIATION_H
#define IRPSWLSTANDARDDEVIATION_H

#include "RPSWindLabsimuData.h"

class IrpsWLStandardDeviation
{
public:

    virtual ~IrpsWLStandardDeviation() {};

    virtual bool ComputeStandardDeviationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual bool ComputeStandardDeviationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeStandardDeviationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLSTANDARDDEVIATION_H
