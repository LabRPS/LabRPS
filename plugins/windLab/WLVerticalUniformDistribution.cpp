 
#include "WLVerticalUniformDistribution.h"
#include "wlvertdistrdialog.h"
#include "RPSWindLabTools.h"
#include <QMessageBox>

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
	// Computing the location coordinates
	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{
		dLocCoord(loop, 0) = vstmdPositionX;
		dLocCoord(loop, 1) = 0.0;
		dLocCoord(loop, 2) = vstmdHeightHo + loop * vstmdSpacing;
	}

}


bool CWLVerticalUniformDistribution::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	std::unique_ptr<WLVertDistrDialog> dlg(new WLVertDistrDialog(vstmdHeightHo,vstmdSpacing , vstmLength, vstmdPositionX));

	if (dlg->exec() == QDialog::Accepted)  // 
	{
		vstmdSpacing = dlg->mspacing;
		vstmdPositionX = dlg->mpositionX;
		vstmdHeightHo = dlg->mminHeightHo;
		vstmLength = dlg->mlength;
	}

	return true;
}
