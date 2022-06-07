 
#include "WLVerticalUniformDistribution.h"
// #include "VertDistrDialog.h"
#include "RPSWindLabTools.h"

// Spacing along vertical line
static double vstmdSpacing = 5;

// Position x of the vertical line
static double vstmdPositionX = 15;

// Height of the lowest location
static double vstmdHeightHo = 25;

//The length on which the locations are vertically distributed
static double vstmLength = 10;

void CWLVerticalUniformDistribution::ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	// // Computing the location coordinates
	// for (int loop = 0; loop < Data.m_iNumberOfSpatialPosition; loop++)
	// {
	// 	dLocCoord(loop, 0) = vstmdPositionX;
	// 	dLocCoord(loop, 1) = 0.0;
	// 	dLocCoord(loop, 2) = vstmdHeightHo + loop * vstmdSpacing;
	// }

}


bool CWLVerticalUniformDistribution::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// CVertDistrDialog Dlg;

	// Dlg.m_dSpacing = vstmdSpacing;
	// Dlg.m_dPositionX = vstmdPositionX;
	// Dlg.m_dHeightHo = vstmdHeightHo;
	// Dlg.m_dLength = vstmLength;

	// if (Dlg.DoModal() == IDOK)  // 
	// {
	// 	vstmdSpacing = Dlg.m_dSpacing;
	// 	vstmdPositionX = Dlg.m_dPositionX;
	// 	vstmdHeightHo = Dlg.m_dHeightHo;
	// 	vstmLength = Dlg.m_dLength;
	// }

	return true;
}
