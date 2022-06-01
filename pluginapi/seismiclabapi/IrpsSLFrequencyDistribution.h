#pragma once
#include "RPSSeismicLabsimuData.h"
class IrpsSLFrequencyDistribution
{
public:
	virtual void ComputeFrequenciesVectorF(const CRPSSeismicLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation) = 0;

	virtual void ComputeFrequenciesMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;
};
