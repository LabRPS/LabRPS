#pragma once
#include "IrpsSeLDirectionDistribution.h"

class CUnifDistrDirection : public IrpsSeLDirectionDistribution
{
	public:
	void ComputeDirectionsVectorD(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation);

	void ComputeDirectionsVectorF(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation);

	void ComputeDirectionsVectorT(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation);

	void ComputeDirectionsMatrixDP(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation);

	void ComputeDirectionsMatrixTD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation);

	void ComputeDirectionsMatrixFD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation);

	void ComputeDirectionsCubeFTD(const CRPSSeaLabsimuData &Data, cube &dDirectionCube, QStringList &strInformation);

	void ComputeDirectionsValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);

};

