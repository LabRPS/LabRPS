#pragma once
#include "IrpsSeLRandomness.h"

#include <QStringList>


class CRPSSLUniformRandomPhases : public IrpsSeLRandomness
{
public:
	void GenerateRandomArrayFP(const CRPSSeaLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	void ComputeRandomValue(const CRPSSeaLabsimuData &Data, double &dValue, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);

};

