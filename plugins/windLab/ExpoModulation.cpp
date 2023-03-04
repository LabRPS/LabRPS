
#include "ExpoModulation.h"
#include <QMessageBox>

#include "widgets/expomodulationdialog.h"
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/modulation/ExponentialModulation.h"
#include "myWidgets/RPSModulationDialog.h"

// The decay coefficient Cx
static double timeOfMax = 300;
static double stormLength = 125;


bool CExpoModulation::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
//	// the input diolag
//	std::unique_ptr<ExpoModulationDialog> dlg(new ExpoModulationDialog(timeOfMax, stormLength));

//	if (dlg->exec() == QDialog::Accepted) //
//	{
//		timeOfMax = dlg->m_dTimeOfMax;
//		stormLength = dlg->m_dStormLength;

//	}

//	return true;

    std::unique_ptr<RPSModulationDialog> dlg(new RPSModulationDialog(timeOfMax, stormLength, 0.0, 3));

    if (dlg->exec() == QDialog::Accepted) //
    {
        timeOfMax = dlg->m_para1;
        stormLength = dlg->m_para2;
    }

    return true;
}

bool CExpoModulation::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
    rps::WindVelocity::ExponentialModulation exponentialModulation;

    dValue = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);

	return true;
}

bool CExpoModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{

    rps::WindVelocity::ExponentialModulation exponentialModulation;

	 //For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements; k++)
	{
		const double 	dTime = Data.minTime + Data.timeIncrement * k;       
        dVarVector(k) = dTime;
		dValVector(k) = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
	}

	return true;
}

bool CExpoModulation::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
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

	return true;
}
