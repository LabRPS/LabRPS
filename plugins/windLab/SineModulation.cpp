
#include "SineModulation.h"
#include "sinemodulationdialog.h"
#include <QMessageBox>

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

	 //For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements; k++)
	{
		dTime = Data.minTime + Data.timeIncrement * k;

		dModulationVector(k) = sin(3.14*dTime / pulseDuration);

	}
}
void CSineModulation::ComputeModulationVectorF(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
    double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    double modValue = sin(3.14*dTime / pulseDuration);
	
	 //For each time increment
	for (int k = 0; k < Data.numberOfFrequency; k++)
	{
		dModulationVector(k) = modValue;

	}
}
void CSineModulation::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
    double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    double modValue = sin(3.14*dTime / pulseDuration);
	
	 //For each time increment
	for (int k = 0; k < Data.numberOfSpatialPosition; k++)
	{
		dModulationVector(k) = modValue;

	}
}
void CSineModulation::ComputeModulationMatrixTP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	double dTime;

	for (int k1 = 0; k1 < Data.numberOfTimeIncrements; k1++)
	{
		dTime = Data.minTime + Data.timeIncrement * k1;
		
		for (int k2 = 0; k2 < Data.numberOfSpatialPosition; k2++)
		{
			dModulationMatrix(k1, k2) = sin(3.14*dTime / pulseDuration);
		}
	}
}
void CSineModulation::ComputeModulationMatrixFP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    double modValue = sin(3.14*dTime / pulseDuration);

	for (int k1 = 0; k1 < Data.numberOfFrequency; k1++)
	{		
		for (int k2 = 0; k2 < Data.numberOfSpatialPosition; k2++)
		{
			dModulationMatrix(k1, k2) = modValue;
		}
	}
}
void CSineModulation::ComputeModulationMatrixTF(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	double dTime;

	for (int k1 = 0; k1 < Data.numberOfTimeIncrements; k1++)
	{
		dTime = Data.minTime + Data.timeIncrement * k1;
		
		for (int k2 = 0; k2 < Data.numberOfFrequency; k2++)
		{
			dModulationMatrix(k1, k2) = sin(3.14*dTime / pulseDuration);
		}
	}
}
void CSineModulation::ComputeModulationCubeTFP(const CRPSWindLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{
	double dTime;

	for (int k1 = 0; k1 < Data.numberOfTimeIncrements; k1++)
	{
		dTime = Data.minTime + Data.timeIncrement * k1;

		for (int k2 = 0; k2 < Data.numberOfFrequency; k2++)
		{
			for (int k3 = 0; k3 < Data.numberOfSpatialPosition; k3++)
			{
				dModulationCube(k1, k2, k3) = sin(3.14*dTime / pulseDuration);
			}
		}
	}
}


