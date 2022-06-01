#pragma once
#include "RPSSeismicLabsimuData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class IrpsSLLocationDistribution
{
public:

	virtual void ComputeLocationCoordinateMatrixP3(const CRPSSeismicLabsimuData &Data, mat &dLocCoord, QStringList &strInformation) = 0;

	//Initial setting
	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;

};
