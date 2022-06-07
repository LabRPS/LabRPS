#pragma once
#include "IrpsWLRandomness.h"

class CRPSUniformRandomPhases : public IrpsWLRandomness
{
public:

	void GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	void ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation);
};

