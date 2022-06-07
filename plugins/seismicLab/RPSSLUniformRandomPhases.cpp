
#include "RPSSLUniformRandomPhases.h"
#include "RPSSeismicLabTools.h"

void CRPSSLUniformRandomPhases::GenerateRandomArrayFP(const CRPSSeismicLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	// dRandomValueArray = 6.28 * randu(Data.numberOfFrequency, Data.numberOfSpatialPosition);

	// //CRPSWindLabTools::GenerateRandomArray(0, 6.28, Data.numberOfFrequency, Data.numberOfSpatialPosition, dRandomValueArray);

}
void CRPSSLUniformRandomPhases::ComputeRandomValue(const CRPSSeismicLabsimuData &Data, double &dValue, QStringList &strInformation)
{

}

bool CRPSSLUniformRandomPhases::OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation)
{
	return true;
}
