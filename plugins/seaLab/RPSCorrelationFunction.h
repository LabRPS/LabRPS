#pragma once
#include "IrpsSeLCorrelation.h"

class CRPSCorrelationFunction : public IrpsSeLCorrelation
{
	public:
	void ComputeCrossCorrelationVectorT(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation);

	void ComputeCrossCorrelationVectorP(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation);

	void ComputeCrossCorrelationMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation);

	void ComputeCrossCorrelationCubePPT(const CRPSSeaLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation);

	void ComputeCrossCorrelationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);
};

