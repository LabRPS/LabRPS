#ifndef IRPSWLLOCATIONDISTRIBUTION_H
#define IRPSWLLOCATIONDISTRIBUTION_H

#include "RPSWindLabsimuData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class IrpsWLLocationDistribution
{
public:
    virtual ~IrpsWLLocationDistribution() {};

    virtual bool ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;
};

#endif  // IRPSWLLOCATIONDISTRIBUTION_H
