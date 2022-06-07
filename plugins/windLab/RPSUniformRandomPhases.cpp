
#include "RPSUniformRandomPhases.h"
#include "RPSWindLabTools.h"


bool CRPSUniformRandomPhases::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	return true;
}

void CRPSUniformRandomPhases::GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	// //dRandomValueArray = 6.28 * randu(Data.m_iNumberOfFrequency, Data.m_iNumberOfSpatialPosition);
	
	// CRPSWindLabTools::GenerateRandomArray(0, 6.28, Data.m_iNumberOfFrequency, Data.m_iNumberOfSpatialPosition, dRandomValueArray);
}

void CRPSUniformRandomPhases::ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation)
{

}