
#include "RPSWLPowerLowProfile.h"
#include "RPSWindLabFramework.h"
// #include "DimensPowerDialog.h";
#include "RPSWindLabTools.h"


// The mean speed reference height
static double dreferenceHeight = 10.0;

// The mean speed reference speed
static double dreferenceSpeed = 30.0;

// The dimensionless power
static double dDimensionlessPower = 0.12;


void CRPSWLPowerLowProfile::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
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

	// for (int loop = 0; loop < Data.m_iNumberOfSpatialPosition; loop++)
	// {
	// 	dMeanSpeedVector(loop) = pow(dLocCoord(loop, 2) / dreferenceHeight, dDimensionlessPower) * dreferenceSpeed;
	// }
}
void CRPSWLPowerLowProfile::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{

}
void CRPSWLPowerLowProfile::ComputeMeanWindSpeedMatrixTP(const CRPSWindLabsimuData &Data, mat &dMeanSpeedMatrix, QStringList &strInformation)
{

}

bool CRPSWLPowerLowProfile::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// //Create a dimensionless dialog
	// CDimensPowerDialog Dlg;

	// Dlg.m_dreferenceHeight = dreferenceHeight;
	// Dlg.m_dreferenceSpeed = dreferenceSpeed;
	// Dlg.m_dDimensionlessPower = dDimensionlessPower;


	// if (Dlg.DoModal() == IDOK)  // 
	// {
	// 	dreferenceHeight = Dlg.m_dreferenceHeight;
	// 	dreferenceSpeed = Dlg.m_dreferenceSpeed;
	// 	dDimensionlessPower = Dlg.m_dDimensionlessPower;
	// }

	return true;
}

void CRPSWLPowerLowProfile::ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
	// if (dLocationzCoord < 0)
	// {
	// 	strInformation.AddTail(("Negative height detected. The computation fails."));
	// 	return;
	// }

	// dValue = pow(dLocationzCoord / dreferenceHeight, dDimensionlessPower) * dreferenceSpeed;

}
