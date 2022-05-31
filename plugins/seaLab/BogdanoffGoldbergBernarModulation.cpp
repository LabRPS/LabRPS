#include "BogdanoffGoldbergBernarModulation.h"

void CBogdanoffGoldbergBernarModulation::ComputeModulationVectorT(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	for (int j = 0; j < Data.numberOfTimeIncrements; j++)
	{
		dModulationVector(j) = 77;
	}
}
void CBogdanoffGoldbergBernarModulation::ComputeModulationVectorF(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationVectorP(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationVectorD(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationMatrixTP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationMatrixFP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationMatrixTD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationMatrixFD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationMatrixTF(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationCubeTFP(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationCubeTFD(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{

}
void CBogdanoffGoldbergBernarModulation::ComputeModulationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{

}

bool CBogdanoffGoldbergBernarModulation::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	return true;
}

