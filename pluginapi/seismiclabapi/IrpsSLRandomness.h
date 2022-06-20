#pragma once
#include "RPSSeismicLabsimuData.h"

class IrpsSLRandomness
{
public:
    virtual ~IrpsSLRandomness() {};

	virtual void GenerateRandomArrayFP(const CRPSSeismicLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation) = 0;

	virtual void ComputeRandomValue(const CRPSSeismicLabsimuData &Data, double &dValue, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;
};
