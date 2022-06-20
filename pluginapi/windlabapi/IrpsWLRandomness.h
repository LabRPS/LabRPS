#pragma once
#include "RPSWindLabsimuData.h"

class IrpsWLRandomness
{
public:
    virtual ~IrpsWLRandomness() {};

	virtual void GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation) = 0;

	virtual void ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
