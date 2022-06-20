#pragma once
#include "RPSWindLabsimuData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class IrpsWLLocationDistribution
{
public:
    virtual ~IrpsWLLocationDistribution() {};

	virtual void ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;
};
