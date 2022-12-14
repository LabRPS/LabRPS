
#include "RPSLogarithmicLowProfile.h"
#include "RPSWindLabFramework.h"
#include "widgets/meanwindlogprofildialog.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/meanWindSpeed/LogarithmicMeanWindSpeed.h"

// The terrain roughness length
static double dterrainRoughness = 0.01;

// The shear velocity of the flow
static double dshearVelocity = 1.76;

// 0.4 is von karman's constant
static double VonKarmanConst = 0.4;

static double dzeroPlanDisplacement = 0;


void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// local array for the location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);

	// Compute the location coordinate array
	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

    const double dTime = Data.minTime + Data.timeIncrement*Data.timeIndex;

	// Compute the mean wind speed matrix
	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{
		dVarVector(loop) = loop+1;
        ComputeMeanWindSpeedValue(Data, dValVector(loop), dLocCoord(loop, 0), dLocCoord(loop, 1), dLocCoord(loop, 2), dTime, strInformation);
	}
}

void CRPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // local array for the location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition, 3);

    // Compute the location coordinate array
    CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

    // Compute the mean wind speed matrix
    for (int loop = 0; loop < Data.numberOfTimeIncrements; loop++)
    {
        const double dTime = Data.minTime + Data.timeIncrement*loop;
        ComputeMeanWindSpeedValue(Data, dValVector(loop), dLocCoord(Data.locationJ, 0), dLocCoord(Data.locationJ, 1), dLocCoord(Data.locationJ, 2), dTime, strInformation);
        dVarVector(loop) = dTime;
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

    if(Data.stationarity)
    {
        dValue = logarithmicMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dterrainRoughness, dshearVelocity, dzeroPlanDisplacement);
    }
    else if(!Data.stationarity && Data.uniformModulation)
    {
        double dModValue = 0.0;
        CRPSWindLabFramework::ComputeModulationValue(Data, dModValue, dLocationxCoord, dLocationxCoord, dLocationxCoord, 0, dTime, strInformation);
        dValue = dModValue * logarithmicMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dterrainRoughness, dshearVelocity, dzeroPlanDisplacement);
    }
}
