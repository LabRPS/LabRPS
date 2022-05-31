#include "AbrahamsonCoherence.h"


void CAbrahamsonCoherence::ComputeCrossCoherenceVectorF(const CRPSSeaLabsimuData &Data, vec &dCohVector, QStringList &strInformation)
{
	for (int j = 0; j < Data.numberOfFrequency; j++)
	{
		dCohVector(j) = 66;
	}
}
void CAbrahamsonCoherence::ComputeCrossCoherenceMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfSpatialPosition; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dCoherenceMatrix(i, j) = 55;
		}
	}
}
void CAbrahamsonCoherence::ComputeCoherenceCubePPF(const CRPSSeaLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation)
{

}
void CAbrahamsonCoherence::ComputeCoherenceValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	dValue = 77;
}

//Initial setting
bool CAbrahamsonCoherence::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	return true;
}