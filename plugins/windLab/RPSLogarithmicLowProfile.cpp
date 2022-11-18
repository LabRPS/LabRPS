
#include "RPSLogarithmicLowProfile.h"
#include "RPSWindLabFramework.h"
#include "meanwindlogprofildialog.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/meanWindSpeed/LogarithmicMeanWindSpeed.h"

// The terrain roughness length
static double dterrainRoughness = 0.01;

// The shear velocity of the flow
static double dshearVelocity = 1.76;

// 0.4 is von karman's constant
static double VonKarmanConst = 0.4;

static double dzeroPlanDisplacement = 0;


void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{
    rps::WindVelocity::LogarithmicMeanWindSpeed logarithmicMeanWindSpeed;
	// local array for the location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);

	// Compute the location coordinate array
	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	// Compute the mean wind speed matrix
	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{
        dMeanSpeedVector(loop) = logarithmicMeanWindSpeed.computeMeanWindSpeed(dLocCoord(loop, 2), dterrainRoughness, dshearVelocity, dzeroPlanDisplacement);
	}
}

bool CRPSLogarithmicLowProfile::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
    std::unique_ptr<MeanWindLogProfilDialog> dlg(new MeanWindLogProfilDialog(dterrainRoughness, dshearVelocity, dzeroPlanDisplacement));

	if (dlg->exec() == QDialog::Accepted) //
	{
		dterrainRoughness = dlg->m_terrainRoughness;
		dshearVelocity = dlg->m_shearVelocity;
        dzeroPlanDisplacement = dlg->m_zeroPlanDisplacement;

	}

	return true;
}

void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
    rps::WindVelocity::LogarithmicMeanWindSpeed logarithmicMeanWindSpeed;

	if (dLocationzCoord < 0)
	{
		strInformation.append("Negative height detected. The computation fails.");
		return;
	}
    dValue = logarithmicMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dterrainRoughness, dshearVelocity, dzeroPlanDisplacement);

}
