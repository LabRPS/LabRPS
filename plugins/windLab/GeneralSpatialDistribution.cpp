
#include "GeneralSpatialDistribution.h"
#include "widgets/generaldistributiondialog.h"
#include <QMessageBox>


using namespace std;
////////////////////////Horizontal distribution///////////////////////////////////////////////

//spacing between two adjacent points
static mat pointsMatrix;

bool GeneralSpatialDistribution::ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	dLocCoord = pointsMatrix;
	return true;
}


bool GeneralSpatialDistribution::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	pointsMatrix = MatrixXd::Zero(Data.numberOfSpatialPosition, 3);
	
	// the input diolag
	std::unique_ptr<GeneralDistributionDialog> dlg(new GeneralDistributionDialog(Data.numberOfSpatialPosition, pointsMatrix));

	if (dlg->exec() == QDialog::Accepted) //
	{
		pointsMatrix = dlg->m_pointsMatrix;
		strInformation += dlg->m_information;
	}

	return true;
}
