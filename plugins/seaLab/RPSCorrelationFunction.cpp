#include "RPSCorrelationFunction.h"

void CRPSCorrelationFunction::ComputeCrossCorrelationVectorT(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation)
{
	for (int j = 0; j < Data.numberOfTimeIncrements; j++)
	{
		dCorrelationVector(j) = 101;
	}
}
void CRPSCorrelationFunction::ComputeCrossCorrelationVectorP(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation)
{

}
void CRPSCorrelationFunction::ComputeCrossCorrelationMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfSpatialPosition; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dCorrelationMatrix(i, j) = 103;
		}
	}
}

void CRPSCorrelationFunction::ComputeCrossCorrelationCubePPT(const CRPSSeaLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation)
{

}
void CRPSCorrelationFunction::ComputeCrossCorrelationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{

}

bool CRPSCorrelationFunction::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	return true;
}

