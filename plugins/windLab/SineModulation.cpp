
#include "SineModulation.h"
#include "widgets/sinemodulationdialog.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/modulation/SineModulation.h"
#include "myWidgets/RPSModulationDialog.h"

static double pulseDuration = 150;

bool CSineModulation::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
//	// the input diolag
//	std::unique_ptr<SineModulationDialog> dlg(new SineModulationDialog(pulseDuration));

//	if (dlg->exec() == QDialog::Accepted) //
//	{
//		pulseDuration = dlg->m_dPulseDuration;
//	}

//	return true;

    std::unique_ptr<RPSModulationDialog> dlg(new RPSModulationDialog(pulseDuration, 0.0, 0.0, 2));

    if (dlg->exec() == QDialog::Accepted) //
    {
        pulseDuration = dlg->m_para1;
    }

    return true;
}


bool CSineModulation::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	dValue = sin(3.14*dTime / pulseDuration);
	return true;
}

bool CSineModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	//double 	dTime;
    rps::WindVelocity::SineModulation sineModulation;

	 //For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements; k++)
	{
		const double dTime = Data.minTime + Data.timeIncrement * k;
		dVarVector(k) = dTime;	
        dValVector(k) = sineModulation.computeModulation(dTime, pulseDuration);
	}
	return true;
}

bool CSineModulation::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    //double 	dTime;
    rps::WindVelocity::SineModulation sineModulation;
    const double dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    const double dModValue = sineModulation.computeModulation(dTime, pulseDuration);

     //For each time increment
    for (int k = 0; k < Data.numberOfSpatialPosition; k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = dModValue;
    }

	return true;
}
