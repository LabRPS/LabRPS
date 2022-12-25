#ifndef IRPSWLFREQUENCYDISTRIBUTION_H
#define IRPSWLFREQUENCYDISTRIBUTION_H

#include "RPSWindLabsimuData.h"

class IrpsWLFrequencyDistribution
{
public:
    virtual ~IrpsWLFrequencyDistribution() {};

    virtual bool ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation) = 0;

    virtual bool ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data,  vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

	};
#endif  // IRPSWLFREQUENCYDISTRIBUTION_H
