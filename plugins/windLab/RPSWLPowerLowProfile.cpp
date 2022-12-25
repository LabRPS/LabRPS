
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


bool CRPSWLPowerLowProfile::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // local array for the location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition, 3);

    // Compute the location coordinate array
    const bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
    
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
bool CRPSWLPowerLowProfile::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // local array for the location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition, 3);

    // Compute the location coordinate array
    const bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

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

bool CRPSWLPowerLowProfile::ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
    rps::WindVelocity::PowerLawMeanWindSpeed powerLawMeanWindSpeed;

	if (dLocationzCoord < 0)
	{
		strInformation.append("Negative height detected. The computation fails.");
		return false;
	}


    if(Data.stationarity)
    {
        dValue = powerLawMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dreferenceHeight, dreferenceSpeed, dDimensionlessPower, dzeroPlanDisplacement);
    }
    else if(!Data.stationarity && Data.uniformModulation)
    {
        double dModValue = 0.0;
        const bool returnResult = CRPSWindLabFramework::ComputeModulationValue(Data, dModValue, dLocationxCoord, dLocationxCoord, dLocationxCoord, 0, dTime, strInformation);
        if(!returnResult)
    {
       strInformation.append("The computation of the modulation value has failed.") ;
       return false;
    }
        dValue = dModValue * powerLawMeanWindSpeed.computeMeanWindSpeed(dLocationzCoord, dreferenceHeight, dreferenceSpeed, dDimensionlessPower, dzeroPlanDisplacement);
    }

    return true;
}
