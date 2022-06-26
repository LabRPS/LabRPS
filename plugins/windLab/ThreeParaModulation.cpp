
#include "ThreeParaModulation.h"
#include "threeparamodulationdialog.h"
#include <QMessageBox>

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
	// compute approximate buffeting force 
	dValue = alpha * (pow(dTime, betta))*(exp(-lambda * dTime));
}


void CThreeParaModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	//  Maximum value of modulation function
	double max = 0.0;
	double 	dTime;

	// For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements; k++)
	{
		dTime = Data.minTime + Data.timeIncrement * k;

		// compute approximate buffeting force 
		dModulationVector(k) = alpha * (pow(dTime, betta))*(exp(-lambda * dTime));

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

void CThreeParaModulation::ComputeModulationVectorF(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
    double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    double modValue = alpha * (pow(dTime, betta))*(exp(-lambda * dTime));
	
	 //For each time increment
	for (int k = 0; k < Data.numberOfFrequency; k++)
	{
		dModulationVector(k) = modValue;

	}
}
void CThreeParaModulation::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
    double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    double modValue = alpha * (pow(dTime, betta))*(exp(-lambda * dTime));
	
	 //For each time increment
	for (int k = 0; k < Data.numberOfSpatialPosition; k++)
	{
		dModulationVector(k) = modValue;

	}
}
void CThreeParaModulation::ComputeModulationMatrixTP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	double dTime;

	for (int k1 = 0; k1 < Data.numberOfTimeIncrements; k1++)
	{
		dTime = Data.minTime + Data.timeIncrement * k1;
		
		for (int k2 = 0; k2 < Data.numberOfSpatialPosition; k2++)
		{
			dModulationMatrix(k1, k2) = alpha * (pow(dTime, betta))*(exp(-lambda * dTime));
		}
	}
}
void CThreeParaModulation::ComputeModulationMatrixFP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    double modValue = alpha * (pow(dTime, betta))*(exp(-lambda * dTime));

	for (int k1 = 0; k1 < Data.numberOfFrequency; k1++)
	{		
		for (int k2 = 0; k2 < Data.numberOfSpatialPosition; k2++)
		{
			dModulationMatrix(k1, k2) = modValue;
		}
	}
}
void CThreeParaModulation::ComputeModulationMatrixTF(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	double dTime;

	for (int k1 = 0; k1 < Data.numberOfTimeIncrements; k1++)
	{
		dTime = Data.minTime + Data.timeIncrement * k1;
		
		for (int k2 = 0; k2 < Data.numberOfFrequency; k2++)
		{
			dModulationMatrix(k1, k2) = alpha * (pow(dTime, betta))*(exp(-lambda * dTime));
		}
	}
}
void CThreeParaModulation::ComputeModulationCubeTFP(const CRPSWindLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{
	double dTime;

	for (int k1 = 0; k1 < Data.numberOfTimeIncrements; k1++)
	{
		dTime = Data.minTime + Data.timeIncrement * k1;

		for (int k2 = 0; k2 < Data.numberOfFrequency; k2++)
		{
			for (int k3 = 0; k3 < Data.numberOfSpatialPosition; k3++)
			{
				dModulationCube(k1, k2, k3) = alpha * (pow(dTime, betta))*(exp(-lambda * dTime));
			}
		}
	}
}

