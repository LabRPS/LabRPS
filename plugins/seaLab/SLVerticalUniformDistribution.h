#pragma once

#include "IrpsSeLLocationDistribution.h"

class CSLVerticalUniformDistribution : public IrpsSeLLocationDistribution
{
public:
	~CSLVerticalUniformDistribution() {};

	void ComputeLocationCoordinateMatrixP3(const CRPSSeaLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);

};

