
#include "RPSKaimalSpectr.h"
#include "RPSWindLabFramework.h"
#include "kaimalpsdshearvelocitydialog.h"
#include "RPSWindLabTools.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/spectrum/KaimalSpectrum.h"

// The shear velocity of the flow
static double dShearVecForSpec = 1.76;


void CRPSKaimalSpectr::ComputeXAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
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
    double PSDj = 0.0;
    double PSDk = 0.0;

	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);

	for (int loop = 0; loop < Data.numberOfFrequency; loop++)
	{
		dFrequency = dFrequencies(loop);

        ComputeXAutoSpectrumValue(Data, PSDj, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dFrequency, 0, strInformation);
        ComputeXAutoSpectrumValue(Data, PSDk, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dFrequency, 0, strInformation);

        dPSDVector(loop) = sqrt(PSDj*PSDk)*dcoherenceVector(loop);
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
    double PSDj = 0.0;
    double PSDk = 0.0;


	for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
	{
		for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
		{
			CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
			CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);

            ComputeXAutoSpectrumValue(Data, PSDj, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dFrequency, 0, strInformation);
            ComputeXAutoSpectrumValue(Data, PSDk, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dFrequency, 0, strInformation);

            dPSDMatrix(loop1, loop2) = sqrt(PSDj*PSDk)*dcoherenceArray(loop1, loop2);
		}
	}
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


void CRPSKaimalSpectr::ComputeXAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{

	double dMeanSpeed = 0.0;
    CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed, xCoord, yCoord, zCoord, dTime, strInformation);

    rps::WindVelocity::KaimalSpectrum kaimalPSD;
    dValue = kaimalPSD.computeAlongWindAutoSpectrum(dFrequency, zCoord, dMeanSpeed, dShearVecForSpec);
}
