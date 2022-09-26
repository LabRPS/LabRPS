#ifndef IRPSSELLOCATIONDISTRIBUTION_H
#define IRPSSELLOCATIONDISTRIBUTION_H

#include "RPSSeaLabsimuData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class IrpsSeLLocationDistribution
{
public:

    virtual ~IrpsSeLLocationDistribution() {}

	virtual void ComputeLocationCoordinateMatrixP3(const CRPSSeaLabsimuData &Data, mat &dLocCoord, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSSELLOCATIONDISTRIBUTION_H
