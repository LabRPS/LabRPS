
#include "SineModulation.h"
#include "sinemodulationdialog.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/modulation/SineModulation.h"

static double pulseDuration = 150;

bool CSineModulation::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
	std::unique_ptr<SineModulationDialog> dlg(new SineModulationDialog(pulseDuration));

	if (dlg->exec() == QDialog::Accepted) //
	{
		pulseDuration = dlg->m_dPulseDuration;
	}

	return true;
}


void CSineModulation::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	dValue = sin(3.14*dTime / pulseDuration);
}

void CSineModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	double 	dTime;
    rps::WindVelocity::SineModulation sineModulation;

	 //For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements; k++)
	{
		dTime = Data.minTime + Data.timeIncrement * k;

        dModulationVector(k) = sineModulation.computeModulation(dTime, pulseDuration);
	}
}
