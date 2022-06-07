#pragma once

#include "IrpsWLLocationDistribution.h"

class CWLVerticalUniformDistribution : public IrpsWLLocationDistribution
{
public:
	~CWLVerticalUniformDistribution() {};

	void ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

