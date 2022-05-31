#include "SLHorizontalUniformDistribution.h"
#include "cslhorizontallocdistr.h"

////////////////////////Horizontal distribution///////////////////////////////////////////////

// spacing between two adjacent points
static double stmdSpacing = 5;

// Height
static double stmdHeight = 40;

// Length
static double stmdLength = 10;

void CSeLHorizontalUniformDistribution::ComputeLocationCoordinateMatrixP3(const CRPSSeaLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	// Computing the location coordinates
	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{
		dLocCoord(loop, 0) = loop * stmdSpacing;
		dLocCoord(loop, 1) = 0.0;
		dLocCoord(loop, 2) = stmdHeight;
	}
}

bool CSeLHorizontalUniformDistribution::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
	std::unique_ptr<CSLHorizontalLocDistr> dlg(new CSLHorizontalLocDistr(stmdSpacing, stmdHeight, stmdLength));

	if (dlg->exec() == QDialog::Accepted) //
	{
		stmdSpacing = dlg->mdSpacing;
		stmdHeight = dlg->mdHeight;
		stmdLength = dlg->mdLength;
	}

	return true;
}
