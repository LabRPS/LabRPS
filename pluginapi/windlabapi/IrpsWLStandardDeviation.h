#ifndef IRPSWLSTANDARDDEVIATION_H
#define IRPSWLSTANDARDDEVIATION_H

#include "RPSWindLabsimuData.h"

class IrpsWLStandardDeviation
{
public:

    virtual ~IrpsWLStandardDeviation() {};

    virtual void ComputeStandardDeviationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) = 0;

    virtual void ComputeStandardDeviationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLSTANDARDDEVIATION_H
