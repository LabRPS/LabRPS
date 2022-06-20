
#include "WLHorizontalUniformDistribution.h"
#include "RPSWindLabTools.h"
#include "cwlhorizontallocdistr.h"
#include <QMessageBox>


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
	// Computing the location coordinates
	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{		
		dLocCoord(loop, 0) = loop * stmdSpacing;
		dLocCoord(loop, 1) = 0.0;
		dLocCoord(loop, 2) = stmdHeight;
	}	
}


bool CWLHorizontalUniformDistribution::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
	std::unique_ptr<CWLHorizontalLocDistr> dlg(new CWLHorizontalLocDistr(stmdSpacing, stmdHeight, stmdLength));

	if (dlg->exec() == QDialog::Accepted) //
	{
		stmdSpacing = dlg->mdSpacing;
		stmdHeight = dlg->mdHeight;
		stmdLength = dlg->mdLength;
	}

	return true;
}
