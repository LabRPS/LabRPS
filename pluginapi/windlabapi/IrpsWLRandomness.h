#ifndef IRPSWLRANDOMNESS_H
#define IRPSWLRANDOMNESS_H

#include "RPSWindLabsimuData.h"

class IrpsWLRandomness
{
public:
    virtual ~IrpsWLRandomness() {};

    virtual bool ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation) = 0;

    virtual bool GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};

#endif  // IRPSWLRANDOMNESS_H
