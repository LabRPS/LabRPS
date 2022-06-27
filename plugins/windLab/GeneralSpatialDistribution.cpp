
#include "GeneralSpatialDistribution.h"
#include "RPSWindLabTools.h"
#include "generaldistributiondialog.h"
#include <QMessageBox>


using namespace std;
////////////////////////Horizontal distribution///////////////////////////////////////////////

//spacing between two adjacent points
static mat pointsMatrix(3,3);

void GeneralSpatialDistribution::ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	dLocCoord = pointsMatrix;
}


bool GeneralSpatialDistribution::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
	std::unique_ptr<GeneralDistributionDialog> dlg(new GeneralDistributionDialog(Data.numberOfSpatialPosition, pointsMatrix));

	if (dlg->exec() == QDialog::Accepted) //
	{
		pointsMatrix = dlg->m_pointsMatrix;
	}

	return true;
}
