
#include "RPSDeodatis1996.h"

bool CRPSDeodatis1996::OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation)
{
	return true;
}

// The simulation function 
bool CRPSDeodatis1996::Simulate(const CRPSSeismicLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfTimeIncrements; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dVelocityArray(i, j) = 300;
		}
	}
	return true;
}


// The simulation function in large scale mode 
bool CRPSDeodatis1996::SimulateInLargeScaleMode(const CRPSSeismicLabsimuData &Data, QString &strFileName, QStringList &strInformation)
{
	return true;
}


// The simulation function in Comparision mode 
bool CRPSDeodatis1996::SimulateInComparisonMode(const CRPSSeismicLabsimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfTimeIncrements; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dVelocityArray(i, j) = 200;
		}
	}
	return true;
}


//Get the name of the Simulation approach name
QString CRPSDeodatis1996::GetSimuApproachName(QStringList &strInformation)
{
	return ("");
}


