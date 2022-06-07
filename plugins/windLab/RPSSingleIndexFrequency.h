#pragma once
#include "IrpsWLFrequencyDistribution.h"


class CRPSSingleIndexFrequency : public IrpsWLFrequencyDistribution
{

	void ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation);

	void ComputeFrequenciesMatrixFP(const CRPSWindLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation);

	//Initial setting
	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

