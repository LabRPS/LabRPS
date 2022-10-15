
#include "ExpoModulation.h"
#include <QMessageBox>

#include "expomodulationdialog.h"
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

void CExpoModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	double 	dTime;
    rps::WindVelocity::ExponentialModulation exponentialModulation;

	 //For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements; k++)
	{
		dTime = Data.minTime + Data.timeIncrement * k;       
        dModulationVector(k) = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
	}
}
void CExpoModulation::ComputeModulationVectorF(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
    rps::WindVelocity::ExponentialModulation exponentialModulation;

    double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    double modValue = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
	
	 //For each time increment
	for (int k = 0; k < Data.numberOfFrequency; k++)
	{
		dModulationVector(k) = modValue;

	}
}
void CExpoModulation::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
    rps::WindVelocity::ExponentialModulation exponentialModulation;

    double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    double modValue = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
	
	 //For each time increment
	for (int k = 0; k < Data.numberOfSpatialPosition; k++)
	{
		dModulationVector(k) = modValue;

	}
}
void CExpoModulation::ComputeModulationMatrixTP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
    rps::WindVelocity::ExponentialModulation exponentialModulation;

	double dTime;

	for (int k1 = 0; k1 < Data.numberOfTimeIncrements; k1++)
	{
		dTime = Data.minTime + Data.timeIncrement * k1;
		
		for (int k2 = 0; k2 < Data.numberOfSpatialPosition; k2++)
		{
            dModulationMatrix(k1, k2) = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
		}
	}
}
void CExpoModulation::ComputeModulationMatrixFP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
    rps::WindVelocity::ExponentialModulation exponentialModulation;

	double 	dTime = Data.minTime + Data.timeIncrement * Data.timeIndex;
    double modValue = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);

	for (int k1 = 0; k1 < Data.numberOfFrequency; k1++)
	{		
		for (int k2 = 0; k2 < Data.numberOfSpatialPosition; k2++)
		{
			dModulationMatrix(k1, k2) = modValue;
		}
	}
}
void CExpoModulation::ComputeModulationMatrixTF(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
    rps::WindVelocity::ExponentialModulation exponentialModulation;

	double dTime;

	for (int k1 = 0; k1 < Data.numberOfTimeIncrements; k1++)
	{
		dTime = Data.minTime + Data.timeIncrement * k1;
		
		for (int k2 = 0; k2 < Data.numberOfFrequency; k2++)
		{
            dModulationMatrix(k1, k2) = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
		}
	}
}
void CExpoModulation::ComputeModulationCubeTFP(const CRPSWindLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{
    rps::WindVelocity::ExponentialModulation exponentialModulation;

	double dTime;

	for (int k1 = 0; k1 < Data.numberOfTimeIncrements; k1++)
	{
		dTime = Data.minTime + Data.timeIncrement * k1;

		for (int k2 = 0; k2 < Data.numberOfFrequency; k2++)
		{
			for (int k3 = 0; k3 < Data.numberOfSpatialPosition; k3++)
			{
                dModulationCube(k1, k2, k3) = exponentialModulation.computeModulation(dTime, timeOfMax, stormLength);
			}
		}
	}
}
