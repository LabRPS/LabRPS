#include "RPSDirectionalSpectrum.h"
#include "RPSSeaLabFramework.h"


void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// This variable to hold the message from the ComputeCPSDVector function 
	QString msg;
	vec PSDVector(Data.numberOfFrequency);
	vec dSpreadingFctVector(Data.numberOfDirection);

	///spectrum

	// Compute the psd vector
	CRPSSeaLabFramework::ComputeCrossSpectrumVectorF(Data, PSDVector, strInformation);

	/////spreading function


	// Compute the psd vector
	CRPSSeaLabFramework::ComputeSpreadingFunctionVectorD(Data, dSpreadingFctVector, strInformation);

	for (int j = 0; j < Data.numberOfFrequency; j++)
	{
		dPSDVector(j) = PSDVector(j) * dSpreadingFctVector(Data.directionIndex);

	}
}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// This variable to hold the message from the ComputeCPSDVector function 
	QString msg;
	vec PSDVector(Data.numberOfFrequency);
	vec dSpreadingFctVector(Data.numberOfDirection);

	///spectrum

	// Compute the psd vector
	CRPSSeaLabFramework::ComputeCrossSpectrumVectorF(Data, PSDVector, strInformation);

	/////spreading function


	// Compute the psd vector
	CRPSSeaLabFramework::ComputeSpreadingFunctionVectorD(Data, dSpreadingFctVector, strInformation);

	double dPSD = PSDVector(Data.frequencyIndex);
	double dSpreading = 0.0;

	for (int j = 0; j < Data.numberOfDirection; j++)
	{
		dSpreading = dSpreadingFctVector(j);
		dPSDVector(j) = dPSD * dSpreadingFctVector(j);

	}
}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// This variable to hold the message from the ComputeCPSDVector function 
	QString msg;
	vec dPSDVector(Data.numberOfFrequency);
	vec dSpreadingFctVector(Data.numberOfDirection);

	///spectrum

	// Compute the psd vector
	CRPSSeaLabFramework::ComputeCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	/////spreading function


	// Compute the psd vector
	CRPSSeaLabFramework::ComputeSpreadingFunctionVectorD(Data, dSpreadingFctVector, strInformation);

	double dPSD = dPSDVector(Data.frequencyIndex);
	//double dSpreading = 0.0;

	for (int i = 0; i < Data.numberOfDirection; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			//dSpreading = dSpreadingFctVector(i);
			dPSDMatrix(i, j) = dPSD * dSpreadingFctVector(i);
		}

	}
}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// This variable to hold the message from the ComputeCPSDVector function 
	QString msg;
	vec dPSDVector(Data.numberOfFrequency);
	vec dSpreadingFctVector(Data.numberOfDirection);

	///spectrum

	// Compute the psd vector
	CRPSSeaLabFramework::ComputeCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	/////spreading function


	// Compute the psd vector
	CRPSSeaLabFramework::ComputeSpreadingFunctionVectorD(Data, dSpreadingFctVector, strInformation);

	double spreading = dSpreadingFctVector(Data.directionIndex);

	for (int i = 0; i < Data.numberOfFrequency; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dPSDMatrix(j, i) = dPSDVector(i) * spreading;
		}
	}
}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	
}
void CRPSDirectionalSpectrum::ComputeCrossDirectionalSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{

}


//Initial setting
bool CRPSDirectionalSpectrum::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	return true;
}
