
#include "CloughPenzienSpectrum.h"

void CCloughPenzienSpectrum::ComputeXCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	for (int j = 0; j < Data.numberOfFrequency; j++)
	{
		dPSDVector(j) = 11;
	}
}
void CCloughPenzienSpectrum::ComputeXCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CCloughPenzienSpectrum::ComputeXCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CCloughPenzienSpectrum::ComputeXCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfSpatialPosition; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dPSDMatrix(i, j) = 22;
		}
	}
}
void CCloughPenzienSpectrum::ComputeXCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CCloughPenzienSpectrum::ComputeXCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CCloughPenzienSpectrum::ComputeXCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CCloughPenzienSpectrum::ComputeXCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CCloughPenzienSpectrum::ComputeXCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CCloughPenzienSpectrum::ComputeXCrossSpectrumValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{

}

//Initial setting
bool CCloughPenzienSpectrum::OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation)
{
	return true;
}
