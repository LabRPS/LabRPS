#pragma once
#include "IrpsWLFrequencyDistribution.h"

class CRPSDoubleIndexFrequency : public IrpsWLFrequencyDistribution
{
	void ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation);

	void ComputeFrequenciesMatrixFP(const CRPSWindLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);
};

