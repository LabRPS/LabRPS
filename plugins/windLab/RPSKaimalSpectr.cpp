
#include "RPSKaimalSpectr.h"
#include "RPSWindLabFramework.h"
#include "kaimalpsdshearvelocitydialog.h"
#include "RPSWindLabTools.h"
#include <QMessageBox>

// The shear velocity of the flow
static double dShearVecForSpec = 1.76;
// Some constant
double dBuf, dBuf1, dBuf2, dBuf3, dBuf4;
double dPSD = 0.0;
double Par1 = 200.0;
double Par2 = 50.0;
double PI = 22.0 / 7.0;
double Coherence = 0.0;

void CRPSKaimalSpectr::ComputeXCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	vec dcoherenceVector(Data.numberOfFrequency);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeCrossCoherenceVectorF(Data, dcoherenceVector, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double dFrequency = 0.0;
	double dMeanSpeed1 = 0.0;
	double dMeanSpeed2 = 0.0;
	double dTime = Data.minTime + Data.timeIncrement*Data.timeIndex;
	int loop1 = Data.locationJ;
	int loop2 = Data.locationK;

	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);

	for (int loop = 0; loop < Data.numberOfFrequency; loop++)
	{
		dFrequency = dFrequencies(loop);

			dPSDVector(loop) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop1, 2), dMeanSpeed1)*
			ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop2, 2), dMeanSpeed2))*
			dcoherenceVector(loop);
	}
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	vec dcoherenceVector(Data.numberOfFrequency);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeCrossCoherenceVectorF(Data, dcoherenceVector, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double dTime = 0.0;
	double dMeanSpeed1 = 0.0;
	double dMeanSpeed2 = 0.0;
	int loop1 = Data.locationJ;
	int loop2 = Data.locationK;
	int loop3 = Data.frequencyIndex;
	double dFrequency = dFrequencies(Data.frequencyIndex);


	for (int loop = 0; loop < Data.numberOfTimeIncrements; loop++)
	{
		dTime = Data.minTime + Data.timeIncrement*loop;

		CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
		CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);
		
		dPSDVector(loop) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop1, 2), dMeanSpeed1)*
								ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop2, 2), dMeanSpeed2))*
								dcoherenceVector(loop3);
	}
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	mat dCoherenceMatrix(Data.numberOfSpatialPosition,Data.numberOfSpatialPosition);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeCrossCoherenceMatrixPP(Data, dCoherenceMatrix, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double dMeanSpeed1 = 0.0;
	double dMeanSpeed2 = 0.0;
	double dTime = Data.minTime + Data.timeIncrement*(Data.timeIndex);
	double dFrequency = dFrequencies(Data.frequencyIndex);

	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{

		CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop, 0), dLocCoord(loop, 1), dLocCoord(loop, 2), dTime, strInformation);
		CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop, 0), dLocCoord(loop, 1), dLocCoord(loop, 2), dTime, strInformation);
		
		dPSDVector(loop) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop, 2), dMeanSpeed1)*
								ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop, 2), dMeanSpeed2))*
								dCoherenceMatrix(loop, loop);
	}
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	//vec dMeanSpeed;
	mat dcoherenceArray(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeCrossCoherenceMatrixPP(Data, dcoherenceArray, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double dFrequency = dFrequencies(Data.frequencyIndex);
	double dMeanSpeed1 = 0.0;
	double dMeanSpeed2 = 0.0;
	double dTime = Data.minTime + Data.timeIncrement*(Data.timeIndex);


	for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
	{
		for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
		{
			CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
			CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);
			
			dPSDMatrix(loop1, loop2) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop1, 2), dMeanSpeed1)*
											ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop2, 2), dMeanSpeed2))*
											dcoherenceArray(loop1, loop2);
		}
	}
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double dFrequency = dFrequencies(Data.frequencyIndex);
	double thePSD = 0.0;
	double dTime = 0.0;

	for (int loop1 = 0; loop1 < Data.numberOfTimeIncrements; loop1++)
	{
		dTime = Data.minTime +  Data.timeIncrement*loop1;

		for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
		{
			// Compute the frequency vector
			ComputeXCrossSpectrumValue(Data, thePSD, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dFrequency, dTime, strInformation);
			dPSDMatrix(loop1, loop2) = thePSD;
		}
	}

}
void CRPSKaimalSpectr::ComputeXCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double thePSD = 0.0;
	double dTime = Data.minTime +  Data.timeIncrement*(Data.timeIndex);

	for (int loop1 = 0; loop1 < Data.numberOfFrequency; loop1++)
	{
		for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
		{
			// Compute the frequency vector
			ComputeXCrossSpectrumValue(Data, thePSD, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dFrequencies(loop1), dTime, strInformation);
			dPSDMatrix(loop1, loop2) = thePSD;
		}
	}
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double thePSD = 0.0;
	int loop3 = Data.locationJ;

	double dTime = 0.0;

	for (int loop1 = 0; loop1 < Data.numberOfTimeIncrements; loop1++)
	{
		dTime = Data.minTime +  Data.timeIncrement*loop1;

		for (int loop2 = 0; loop2 < Data.numberOfFrequency; loop2++)
		{
			// Compute the frequency vector
			ComputeXCrossSpectrumValue(Data, thePSD, dLocCoord(loop3, 0), dLocCoord(loop3, 1), dLocCoord(loop3, 2), dLocCoord(loop3, 0), dLocCoord(loop3, 1), dLocCoord(loop3, 2), dFrequencies(loop2), dTime, strInformation);
			dPSDMatrix(loop1, loop2) = thePSD;
		}
	}

}
void CRPSKaimalSpectr::ComputeXCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	cube dcoherenceCube(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfFrequency);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeCoherenceCubePPF(Data, dcoherenceCube, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double dFrequency ;
	double dMeanSpeed1 = 0.0;
	double dMeanSpeed2 = 0.0;
	double dTime = Data.minTime + Data.timeIncrement*(Data.timeIndex);

	for (int loop3 = 0; loop3 < Data.numberOfFrequency; loop3++)
	{
		dFrequency = dFrequencies(loop3);

		for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
		{
			for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
			{
				CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
				CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);
				
				dPSDCube(loop1, loop2, loop3) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop1, 2), dMeanSpeed1)*
					                            ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop2, 2), dMeanSpeed2))*
												dcoherenceCube(loop1, loop2, loop3);
			}
		}
	}
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	cube dcoherenceCube(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfTimeIncrements);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeCoherenceCubePPF(Data, dcoherenceCube, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double dFrequency = dFrequencies(Data.frequencyIndex);
	double dMeanSpeed1 = 0.0;
	double dMeanSpeed2 = 0.0;
	double dTime = 0.0;

	for (int loop3 = 0; loop3 < Data.numberOfTimeIncrements; loop3++)
	{
		dTime = Data.minTime +  Data.timeIncrement*loop3;

		for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
		{
			for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
			{
				CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
				CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);
				
				dPSDCube(loop1, loop2, loop3) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop1, 2), dMeanSpeed1)*
					                            ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop2, 2), dMeanSpeed2))*
												dcoherenceCube(loop1, loop2, loop3);
			}
		}
	}
}

double CRPSKaimalSpectr::ComputeTargetAutoSpectrumValue(const CRPSWindLabsimuData &Data, double dFrequency, double dHeight, double dMeanSpeed)
{
	dBuf1 = 1.0 + Par2 * dFrequency * dHeight / (2.0 * PI * dMeanSpeed);

	dBuf = pow(dBuf1, 5.0 / 3.0);

	dPSD = Par1 * dShearVecForSpec * dShearVecForSpec * dHeight / dMeanSpeed;

	dPSD /= dBuf;			// (rad/s)

	dPSD /= 2.0*PI;

	return dPSD;
}

//Initial setting
bool CRPSKaimalSpectr::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	
	// the input diolag
	std::unique_ptr<KaimalPSDShearVelocityDialog> dlg(new KaimalPSDShearVelocityDialog(dShearVecForSpec));

	if (dlg->exec() == QDialog::Accepted) //
	{
		dShearVecForSpec = dlg->m_shearVelocity;
	}
	
	return true;
}


void CRPSKaimalSpectr::ComputeXCrossSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{

	double dMeanSpeed = 0.0;
	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dTime, strInformation);

	dBuf1 = 1.0 + Par2 * dFrequency * dLocationJzCoord / (2.0 * PI * dMeanSpeed);

	dBuf = pow(dBuf1, 5.0 / 3.0);

	dPSD = Par1 * dShearVecForSpec * dShearVecForSpec * dLocationJzCoord / dMeanSpeed;

	dPSD /= dBuf;			// (rad/s)

	dPSD /= 2.0*PI;

	dValue =  dPSD;
}
