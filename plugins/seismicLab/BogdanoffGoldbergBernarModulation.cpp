
#include "BogdanoffGoldbergBernarModulation.h"

void CBogdanoffGoldbergBernarModulation::ComputeModulationVectorT(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	for (int j = 0; j < Data.numberOfTimeIncrements; j++)
	{
		dModulationVector(j) = 77;
	}
}
void CBogdanoffGoldbergBernarModulation::ComputeModulationVectorF(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationVectorP(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationCubeTFP(const CRPSSeismicLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{

}

bool CBogdanoffGoldbergBernarModulation::OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation)
{
	return true;
}

