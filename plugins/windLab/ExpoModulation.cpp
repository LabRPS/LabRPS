
#include "ExpoModulation.h"
#include <QMessageBox>

#include "widgets/expomodulationdialog.h"
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/modulation/ExponentialModulation.h"

// The decay coefficient Cx
static double timeOfMax = 300;
static double stormLength = 125;



bool CExpoModulation::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
	std::unique_ptr<ExpoModulationDialog> dlg(new ExpoModulationDialog(timeOfMax, stormLength));

	if (dlg->exec() == QDialog::Accepted) //
	{
		timeOfMax = dlg->m_dTimeOfMax;
		stormLength = dlg->m_dStormLength;

	}

	return true;
}

void CExpoModulation::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
    rps::WindVelocity::ExponentialModulation exponentialModulation;

    dValue = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
}

void CExpoModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{

    rps::WindVelocity::ExponentialModulation exponentialModulation;

	 //For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements; k++)
	{
		const double 	dTime = Data.minTime + Data.timeIncrement * k;       
        dVarVector(k) = dTime;
		dValVector(k) = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
	}
}

void CExpoModulation::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    rps::WindVelocity::ExponentialModulation exponentialModulation;
    const double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    const double modulationValue = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
     //For each time increment
    for (int k = 0; k < Data.numberOfSpatialPosition; k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = modulationValue;
    }
}
