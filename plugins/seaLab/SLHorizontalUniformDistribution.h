#pragma once

#include "IrpsSeLLocationDistribution.h"

class CSeLHorizontalUniformDistribution : public IrpsSeLLocationDistribution
{
public:
	~CSeLHorizontalUniformDistribution() {};

	void ComputeLocationCoordinateMatrixP3(const CRPSSeaLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);

	//
public:
	//spacing between two adjacent points
	double mdSpacing;

	//Height
	double mdHeight;

	//Length
	double mdLength;
};


