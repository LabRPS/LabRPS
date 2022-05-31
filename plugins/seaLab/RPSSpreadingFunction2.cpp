#include "RPSSpreadingFunction2.h"
#include "RPSSeaLabFramework.h"

using namespace std;

static double PI = 3.14;
static double dLow = -PI / 2;
static double dHigh = PI / 2;

void CRPSSpreadingFunction2::ComputeSpreadingFunctionVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	double value = 0.0;

	vec dDirectionVector(Data.numberOfDirection);

	CRPSSeaLabFramework::ComputeDirectionsVectorD(Data, dDirectionVector, strInformation);

	double dDirection = dDirectionVector(Data.directionIndex);

	if (InRange(dLow, dHigh, dDirection))
	{
		value = (8 / (3 * PI))*pow(cos(dDirection), 4);
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
void CRPSSpreadingFunction2::ComputeSpreadingFunctionVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	double value = 0.0;

	vec dDirectionVector(Data.numberOfDirection);
	
	CRPSSeaLabFramework::ComputeDirectionsVectorD(Data, dDirectionVector, strInformation);


	for (int j = 0; j < Data.numberOfDirection; j++)
	{
		value = dDirectionVector(j);

		if (InRange(dLow, dHigh, value))
		{
			dPSDVector(j) = (8 / (3 * PI))*pow(cos(value), 4);
		}
		else
		{
			strInformation.append(("Direction value not in the rang -pi/2 and pi/2. The calculation of the direction spreading function fails."));

			return;

		}

	}
}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CRPSSpreadingFunction2::ComputeSpreadingFunctionValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{

}

bool CRPSSpreadingFunction2::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	return true;
}


bool CRPSSpreadingFunction2::InRange(double low, double high, double x)
{
	return ((x - high)*(x - low) <= 0);
}


