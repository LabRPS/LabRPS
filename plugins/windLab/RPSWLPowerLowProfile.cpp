
#include "RPSWLPowerLowProfile.h"
#include "RPSWindLabFramework.h"
#include "meanwindpowerprofildialog.h"
#include "RPSWindLabTools.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/meanWindSpeed/PowerLawMeanWindSpeed.h"


// The mean speed reference height
static double dreferenceHeight = 10.0;

// The mean speed reference speed
static double dreferenceSpeed = 30.0;

// The dimensionless power
static double dDimensionlessPower = 0.12;

static double dzeroPlanDisplacement = 0;


void CRPSWLPowerLowProfile::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{
    rps::WindVelocity::PowerLawMeanWindSpeed powerLawMeanWindSpeed;

	// local array for the location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);

	// Compute the location coordinate array
	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{
        dMeanSpeedVector(loop) = powerLawMeanWindSpeed.computeMeanWindSpeed(dLocCoord(loop, 2), dreferenceHeight, dreferenceSpeed, dDimensionlessPower, dzeroPlanDisplacement);
	}
}

bool CRPSWLPowerLowProfile::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
    std::unique_ptr<MeanWindPowerProfilDialog> dlg(new MeanWindPowerProfilDialog(dreferenceHeight, dreferenceSpeed, dDimensionlessPower, dzeroPlanDisplacement));

	if (dlg->exec() == QDialog::Accepted) //
	{
		dreferenceHeight = dlg->m_referenceHeight;
		dreferenceSpeed = dlg->m_referenceSpeed;
		dDimensionlessPower = dlg->m_dimensionlessPower;
        dzeroPlanDisplacement = dlg->m_zeroPlanDisplacement;

	}
	
	return true;
}

void CRPSWLPowerLowProfile::ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
    rps::WindVelocity::PowerLawMeanWindSpeed powerLawMeanWindSpeed;

	if (dLocationzCoord < 0)
	{
		strInformation.append("Negative height detected. The computation fails.");
		return;
	}

    dValue = powerLawMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dreferenceHeight, dreferenceSpeed, dDimensionlessPower, dzeroPlanDisplacement);

}
