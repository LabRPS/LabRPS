#ifndef IRPSSELRANDOMNESS_H
#define IRPSSELRANDOMNESS_H

#include "RPSSeaLabsimuData.h"

class IrpsSeLRandomness
{
public:

    virtual ~IrpsSeLRandomness() {}

	virtual void GenerateRandomArrayFP(const CRPSSeaLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation) = 0;

	virtual void ComputeRandomValue(const CRPSSeaLabsimuData &Data, double &dValue, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSSELRANDOMNESS_H
