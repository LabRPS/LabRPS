
#include "RPSWLPowerLowProfile.h"
#include "RPSWindLabFramework.h"
#include "widgets/meanwindpowerprofildialog.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/meanWindSpeed/PowerLawMeanWindSpeed.h"


// The mean speed reference height
static double dreferenceHeight = 10.0;

// The mean speed reference speed
static double dreferenceSpeed = 30.0;

// The dimensionless power
static double dDimensionlessPower = 0.12;

static double dzeroPlanDisplacement = 0;


void CRPSWLPowerLowProfile::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
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
void CRPSWLPowerLowProfile::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
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


    if(Data.stationarity)
    {
        dValue = powerLawMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dreferenceHeight, dreferenceSpeed, dDimensionlessPower, dzeroPlanDisplacement);
    }
    else if(!Data.stationarity && Data.uniformModulation)
    {
        double dModValue = 0.0;
        CRPSWindLabFramework::ComputeModulationValue(Data, dModValue, dLocationxCoord, dLocationxCoord, dLocationxCoord, 0, dTime, strInformation);
        dValue = dModValue * powerLawMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dreferenceHeight, dreferenceSpeed, dDimensionlessPower, dzeroPlanDisplacement);
    }
}
