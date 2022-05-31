#include "RPSSpreadingFunction1.h"
#include "RPSSeaLabFramework.h"

static double PI = 3.14;
static double dLow = -PI / 2;
static double dHigh = PI / 2;

void CRPSSpreadingFunction1::ComputeSpreadingFunctionVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	double value = 0.0;

	vec dDirectionVector(Data.numberOfDirection);

	CRPSSeaLabFramework::ComputeDirectionsVectorD(Data, dDirectionVector, strInformation);

	double dDirection = dDirectionVector(Data.directionIndex);

	if (InRange(dLow, dHigh, dDirection))
	{
		value = (2 / PI)*pow(cos(dDirection), 2);
	}
	else
	{
		strInformation.append(("Direction value not in the rang -pi/2 and pi/2. The calculation of the direction spreading function fails."));
	}

	for (int j = 0; j < Data.numberOfFrequency; j++)
	{
		dPSDVector(j) = value;
	}
}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	double value = 0.0;

	vec dDirectionVector(Data.numberOfDirection);

	CRPSSeaLabFramework::ComputeDirectionsVectorD(Data, dDirectionVector, strInformation);


	for (int j = 0; j < Data.numberOfDirection; j++)
	{
		value = dDirectionVector(j);

		if (InRange(dLow, dHigh, value))
		{
			dPSDVector(j) = (2 / PI)*pow(cos(value), 2);
		}
		else
		{
			strInformation.append(("Direction value not in the rang -pi/2 and pi/2. Sorry, the calculation of the direction spreading function fails."));

			return;
		}

	}
}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CRPSSpreadingFunction1::ComputeSpreadingFunctionValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{

}


bool CRPSSpreadingFunction1::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	return true;
}


bool CRPSSpreadingFunction1::InRange(double low, double high, double x)
{
	return ((x - high)*(x - low) <= 0);
}

