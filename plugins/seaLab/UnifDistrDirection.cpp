#include "UnifDistrDirection.h"

void CUnifDistrDirection::ComputeDirectionsVectorD(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation)
{
	for (int j = 0; j < Data.numberOfDirection; j++)
	{
		dDirectionVector(j) = Data.minDirection + j * Data.directionIncrement;
	}
}
void CUnifDistrDirection::ComputeDirectionsVectorF(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation)
{

}
void CUnifDistrDirection::ComputeDirectionsVectorT(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation)
{

}
void CUnifDistrDirection::ComputeDirectionsMatrixDP(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation)
{

}
void CUnifDistrDirection::ComputeDirectionsMatrixTD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation)
{

}
void CUnifDistrDirection::ComputeDirectionsMatrixFD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation)
{

}
void CUnifDistrDirection::ComputeDirectionsCubeFTD(const CRPSSeaLabsimuData &Data, cube &dDirectionCube, QStringList &strInformation)
{

}
void CUnifDistrDirection::ComputeDirectionsValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{

}

bool CUnifDistrDirection::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	return true;
}
