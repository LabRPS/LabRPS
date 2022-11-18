
#include "ThreeParaModulation.h"
#include "threeparamodulationdialog.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/modulation/ThreeParametersModulation.h"

	static double alpha = 4.98;

	static double betta = 3;

	static double lambda = 0.003; // maximum modulation funtion value occurs at t = 3/1000, 3 = m_dBeta

bool CThreeParaModulation::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
	std::unique_ptr<ThreeParaModulationDialog> dlg(new ThreeParaModulationDialog(alpha, betta, lambda));

	if (dlg->exec() == QDialog::Accepted) //
	{
		alpha = dlg->m_dAlpha;
		betta = dlg->m_dBeta;
		lambda = dlg->m_dLambda;

	}

	return true;
}

void CThreeParaModulation::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
    rps::WindVelocity::ThreeParametersModulation threeParametersModulation;

    dValue = threeParametersModulation.computeModulation(alpha, betta, lambda, dTime);
}


void CThreeParaModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
    rps::WindVelocity::ThreeParametersModulation threeParametersModulation;

	//  Maximum value of modulation function
	double max = 0.0;
	double 	dTime;

	// For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements; k++)
	{
		dTime = Data.minTime + Data.timeIncrement * k;

		// compute approximate buffeting force 
        dModulationVector(k) = threeParametersModulation.computeModulation(alpha, betta, lambda, dTime);

		// Max
		if (dModulationVector(k) > max)
		{
			max = dModulationVector(k);
		}
	}

	// For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements; k++)
	{
		// Normalizing the modulation function 
		dModulationVector(k) /= max;
	}

}
