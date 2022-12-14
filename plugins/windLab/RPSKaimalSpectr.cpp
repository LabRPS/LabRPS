
#include "RPSKaimalSpectr.h"
#include "RPSWindLabFramework.h"
#include "widgets/kaimalpsdshearvelocitydialog.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/spectrum/KaimalSpectrum.h"

// The shear velocity of the flow
static double dShearVecForSpec = 1.76;


void CRPSKaimalSpectr::ComputeXAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	vec dcoherenceVector(Data.numberOfFrequency);
    vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
    CRPSWindLabFramework::ComputeCrossCoherenceVectorF(Data, dFrequencies, dcoherenceVector, strInformation);
    CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, dVarVector, strInformation);

	//double dFrequency = 0.0;
	double dTime = Data.minTime + Data.timeIncrement*Data.timeIndex;
	int loop1 = Data.locationJ;
	int loop2 = Data.locationK;
    double PSDj = 0.0;
    double PSDk = 0.0;

	for (int loop = 0; loop < Data.numberOfFrequency; loop++)
	{
		const double dFrequency = dVarVector(loop);

        ComputeXAutoSpectrumValue(Data, PSDj, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dFrequency, dTime, strInformation);
        ComputeXAutoSpectrumValue(Data, PSDk, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dFrequency, dTime, strInformation);

        dValVector(loop) = sqrt(PSDj*PSDk)*dcoherenceVector(loop);
     }
}
void CRPSKaimalSpectr::ComputeXAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Local array for location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition, 3);
    vec dcoherenceVector(Data.numberOfFrequency);
    vec dFrequencies(Data.numberOfFrequency);
    vec dFreqVar(Data.numberOfFrequency);

    CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
    CRPSWindLabFramework::ComputeCrossCoherenceVectorF(Data, dFrequencies, dcoherenceVector, strInformation);
    CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFreqVar, dFrequencies, strInformation);

    //double dFrequency = 0.0;
    const double dFrequency = dFrequencies(Data.frequencyIndex);
    int loop1 = Data.locationJ;
    int loop2 = Data.locationK;
    double PSDj = 0.0;
    double PSDk = 0.0;
    double Coh = 0.0;

    for (int loop = 0; loop < Data.numberOfTimeIncrements; loop++)
    {
        double dTime = Data.minTime + Data.timeIncrement*loop;
        ComputeXAutoSpectrumValue(Data, PSDj, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dFrequency, dTime, strInformation);
        ComputeXAutoSpectrumValue(Data, PSDk, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dFrequency, dTime, strInformation);
        CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, Coh, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dFrequency, dTime, strInformation);

        dVarVector(loop) = dTime;
        dValVector(loop) = sqrt(PSDj*PSDk)*Coh;
     }
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Local array for location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	//vec dMeanSpeed;
	mat dcoherenceArray(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	vec dFrequencies(Data.numberOfFrequency);
    vec varialble(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeCrossCoherenceMatrixPP(Data, dcoherenceArray, strInformation);
    CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, varialble, dFrequencies, strInformation);

	double dFrequency = dFrequencies(Data.frequencyIndex);
	double dTime = Data.minTime + Data.timeIncrement*(Data.timeIndex);
    double PSDj = 0.0;
    double PSDk = 0.0;


	for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
	{
		for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
		{
            ComputeXAutoSpectrumValue(Data, PSDj, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dFrequency, dTime, strInformation);
            ComputeXAutoSpectrumValue(Data, PSDk, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dFrequency, dTime, strInformation);

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
