#ifndef IRPSSELFREQUENCYDISTRIBUTION_H
#define IRPSSELFREQUENCYDISTRIBUTION_H

#include "RPSSeaLabsimuData.h"
class IrpsSeLFrequencyDistribution
{
public:

    virtual ~IrpsSeLFrequencyDistribution() {}

	virtual void ComputeFrequenciesVectorF(const CRPSSeaLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation) = 0;

	virtual void ComputeFrequenciesMatrixFP(const CRPSSeaLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;
};
#endif  // IRPSSELFREQUENCYDISTRIBUTION_H
