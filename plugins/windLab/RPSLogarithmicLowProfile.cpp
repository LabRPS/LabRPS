
#include "RPSLogarithmicLowProfile.h"
#include "RPSWindLabFramework.h"
#include "widgets/meanwindlogprofildialog.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/meanWindSpeed/LogarithmicMeanWindSpeed.h"
#include "myWidgets/RPSMeanProfileDialog.h"

// The terrain roughness length
static double dterrainRoughness = 0.01;

// The shear velocity of the flow
static double dshearVelocity = 1.76;

// 0.4 is von karman's constant
static double VonKarmanConst = 0.4;

static double dzeroPlanDisplacement = 0;


bool CRPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// local array for the location coordinates
	mat dLocCoord(Data.numberOfSpatialPosition, 3);

	// Compute the location coordinate array
	bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

    if(!returnResult)
    {
       strInformation.append("The computation of the location coordinates matrix has failed.") ;
       return false;
    }
    const double dTime = Data.minTime + Data.timeIncrement*Data.timeIndex;

	// Compute the mean wind speed matrix
	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{
		dVarVector(loop) = loop+1;
        ComputeMeanWindSpeedValue(Data, dValVector(loop), dLocCoord(loop, 0), dLocCoord(loop, 1), dLocCoord(loop, 2), dTime, strInformation);
	}

    return true;
}

bool CRPSLogarithmicLowProfile::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // local array for the location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition, 3);

    // Compute the location coordinate array
    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

    if(!returnResult)
    {
       strInformation.append("The computation of the location coordinates matrix has failed.") ;
       return false;
    }
    // Compute the mean wind speed matrix
    for (int loop = 0; loop < Data.numberOfTimeIncrements; loop++)
    {
        const double dTime = Data.minTime + Data.timeIncrement*loop;
        ComputeMeanWindSpeedValue(Data, dValVector(loop), dLocCoord(Data.locationJ, 0), dLocCoord(Data.locationJ, 1), dLocCoord(Data.locationJ, 2), dTime, strInformation);
        dVarVector(loop) = dTime;
    }

    return true;
}

bool CRPSLogarithmicLowProfile::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
    std::unique_ptr<RPSMeanProfileDialog> dlg(new RPSMeanProfileDialog(dshearVelocity, dterrainRoughness, dzeroPlanDisplacement, 0.0, 0.0, 0.0, 1));

	if (dlg->exec() == QDialog::Accepted) //
	{
        dshearVelocity = dlg->m_para1;
        dterrainRoughness = dlg->m_para2;
        dzeroPlanDisplacement = dlg->m_para3;
	}

	return true;
}

bool CRPSLogarithmicLowProfile::ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
    rps::WindVelocity::LogarithmicMeanWindSpeed logarithmicMeanWindSpeed;

	if (dLocationzCoord < 0)
	{
		strInformation.append("Negative height detected. The computation fails.");
		return false;
	}

    if(Data.stationarity)
    {
        dValue = logarithmicMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dterrainRoughness, dshearVelocity, dzeroPlanDisplacement);
    }
    else if(!Data.stationarity && Data.uniformModulation)
    {
        double dModValue = 0.0;
        bool returnResult = CRPSWindLabFramework::ComputeModulationValue(Data, dModValue, dLocationxCoord, dLocationxCoord, dLocationxCoord, 0, dTime, strInformation);
    if(!returnResult)
    {
       strInformation.append("The computation of the modulation function has failed.") ;
       return false;
    }
        dValue = dModValue * logarithmicMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dterrainRoughness, dshearVelocity, dzeroPlanDisplacement);
    }

    return true;
}
