
#include "RPSLogarithmicLowProfile.h"
#include "RPSWindLabFramework.h"
// #include "LogProfileDialog.h"
#include "RPSWindLabTools.h"

// The terrain roughness length
static double dterrainRoughness = 0.01;

// The shear velocity of the flow
static double dshearVelocity = 1.76;

// The mean speed reference speed
static double dreferenceSpeed = 30.0;

// 0.4 is von karman's constant
static double VonKarmanConst = 0.4;

void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{
	// // local array for the location coordinates
	// mat dLocCoord;

	// try
	// {
	// 	// Allocate memory for the local array for the location coordinates
	// 	dLocCoord.set_size(Data.m_iNumberOfSpatialPosition, 3);
	// }
	// catch (CMemoryException* pEx)
	// {
	// 	// Simply show an error message to the user.
	// 	pEx->ReportError();
	// 	pEx->Delete();
	// 	return;
	// }
	// catch (bad_alloc &ba)
	// {
	// 	QString msg(ba.what());
	// 	AfxMessageBox(msg);
	// 	return;
	// }
	// // Compute the location coordinate array
	// CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	// // Compute the mean wind speed matrix
	// for (int loop = 0; loop < Data.m_iNumberOfSpatialPosition; loop++)
	// {
	// 	dMeanSpeedVector(loop) = log(dLocCoord(loop, 2) / dterrainRoughness)*dshearVelocity / VonKarmanConst;
	// }
}
void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{

}
void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedMatrixTP(const CRPSWindLabsimuData &Data, mat &dMeanSpeedMatrix, QStringList &strInformation)
{

}

bool CRPSLogarithmicLowProfile::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// //Create a dimensionless dialog
	// CLogProfileDialog Dlg;

	// Dlg.m_dterrainRoughness = dterrainRoughness;
	// Dlg.m_dshearVelocity = dreferenceSpeed;

	// if (Dlg.DoModal() == IDOK)  // 
	// {
	// 	dterrainRoughness = Dlg.m_dterrainRoughness;
	// 	dshearVelocity = Dlg.m_dshearVelocity;
	// }

	return true;
}

void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
	// if (dLocationzCoord < 0)
	// {
	// 	strInformation.AddTail(("Negative height detected. The computation fails."));
	// 	return;
	// }
	// dValue = log(dLocationzCoord / dterrainRoughness)*dshearVelocity / VonKarmanConst;
}
