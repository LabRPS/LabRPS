#ifndef IRPSWLFREQUENCYDISTRIBUTION_H
#define IRPSWLFREQUENCYDISTRIBUTION_H

#include "RPSWindLabsimuData.h"

class IrpsWLFrequencyDistribution
{
public:
    virtual ~IrpsWLFrequencyDistribution() {};

	virtual void ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation) = 0;

	virtual void ComputeFrequenciesMatrixFP(const CRPSWindLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

	};
#endif  // IRPSWLFREQUENCYDISTRIBUTION_H
