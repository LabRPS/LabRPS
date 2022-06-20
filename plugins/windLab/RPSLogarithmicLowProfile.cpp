
#include "RPSLogarithmicLowProfile.h"
#include "RPSWindLabFramework.h"
#include "meanwindlogprofildialog.h"
#include <QMessageBox>

// The terrain roughness length
static double dterrainRoughness = 0.01;

// The shear velocity of the flow
static double dshearVelocity = 1.76;

// 0.4 is von karman's constant
static double VonKarmanConst = 0.4;

void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{
	// local array for the location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);

	// Compute the location coordinate array
	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	// Compute the mean wind speed matrix
	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{
		dMeanSpeedVector(loop) = log(dLocCoord(loop, 2) / dterrainRoughness)*dshearVelocity / VonKarmanConst;
	}
}
void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{
	// local array for the location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);

	// Compute the location coordinate array
	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	// Compute the mean wind speed matrix
	for (int loop = 0; loop < Data.numberOfTimeIncrements; loop++)
	{
		dMeanSpeedVector(loop) = log(dLocCoord(Data.locationJ, 2) / dterrainRoughness)*dshearVelocity / VonKarmanConst;
	}
}
void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedMatrixTP(const CRPSWindLabsimuData &Data, mat &dMeanSpeedMatrix, QStringList &strInformation)
{
	mat dLocCoord(Data.numberOfSpatialPosition, 3);

	// Compute the location coordinate array
	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	// Compute the mean wind speed matrix
	for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
	{
		// Compute the mean wind speed matrix
		for (int loop2 = 0; loop2 < Data.numberOfTimeIncrements; loop2++)
		{
			dMeanSpeedMatrix(loop2, loop1) = log(dLocCoord(loop1, 2) / dterrainRoughness) * dshearVelocity / VonKarmanConst;
		}
	}
}

bool CRPSLogarithmicLowProfile::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
	std::unique_ptr<MeanWindLogProfilDialog> dlg(new MeanWindLogProfilDialog(dterrainRoughness, dshearVelocity));

	if (dlg->exec() == QDialog::Accepted) //
	{
		dterrainRoughness = dlg->m_terrainRoughness;
		dshearVelocity = dlg->m_shearVelocity;
	}

	return true;
}

void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
	if (dLocationzCoord < 0)
	{
		strInformation.append("Negative height detected. The computation fails.");
		return;
	}
	dValue = log(dLocationzCoord / dterrainRoughness)*dshearVelocity / VonKarmanConst;
}
