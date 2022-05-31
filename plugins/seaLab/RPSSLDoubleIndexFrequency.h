#pragma once
#include "IrpsSeLFrequencyDistribution.h"

class CRPSSLDoubleIndexFrequency : public IrpsSeLFrequencyDistribution
{
public:

	void ComputeFrequenciesVectorF(const CRPSSeaLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation);

	void ComputeFrequenciesMatrixFP(const CRPSSeaLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);
};

