
#include "WLHorizontalUniformDistribution.h"
#include "RPSWindLabTools.h"
// #include "HorizontalLocDistr.h"


using namespace std;
////////////////////////Horizontal distribution///////////////////////////////////////////////

//spacing between two adjacent points
static double stmdSpacing = 5;

//Height
static double stmdHeight = 40;

//Length
static double stmdLength = 10;

void CWLHorizontalUniformDistribution::ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	// // Computing the location coordinates
	// for (int loop = 0; loop < Data.m_iNumberOfSpatialPosition; loop++)
	// {		
	// 	dLocCoord(loop, 0) = loop * stmdSpacing;
	// 	dLocCoord(loop, 1) = 0.0;
	// 	dLocCoord(loop, 2) = stmdHeight;
	// }	
}


bool CWLHorizontalUniformDistribution::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// // the input diolag
	// CHorizontalLocDistr Dlg;

	// // Display the current values
	// Dlg.m_dSpacing = stmdSpacing;
	// Dlg.m_dHeight = stmdHeight;
	// Dlg.m_dLength = stmdLength;

	// if (Dlg.DoModal() == IDOK)  // 
	// {
	// 	mdSpacing = Dlg.m_dSpacing;
	// 	mdHeight = Dlg.m_dHeight;
	// 	mdLength = Dlg.m_dLength;

	// 	stmdSpacing = Dlg.m_dSpacing;
	// 	stmdHeight = Dlg.m_dHeight;
	// 	stmdLength = Dlg.m_dLength;
	// }

	return true;
}
