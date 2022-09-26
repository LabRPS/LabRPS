#ifndef IRPSSLLOCATIONDISTRIBUTION_H
#define IRPSSLLOCATIONDISTRIBUTION_H

#include "RPSSeismicLabsimuData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class IrpsSLLocationDistribution
{
public:
    virtual ~IrpsSLLocationDistribution() {};

	virtual void ComputeLocationCoordinateMatrixP3(const CRPSSeismicLabsimuData &Data, mat &dLocCoord, QStringList &strInformation) = 0;

	//Initial setting
	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSSLLOCATIONDISTRIBUTION_H
