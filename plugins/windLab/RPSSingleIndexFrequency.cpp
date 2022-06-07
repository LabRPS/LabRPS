
#include "RPSSingleIndexFrequency.h"


void CRPSSingleIndexFrequency::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	// for (int l = 0; l < Data.m_iNumberOfFrequency; l++)
	// {
	// 	dFrequencyVector(l) = Data.m_dMinFrequency + l * Data.m_dFrequencyIncrement;
	// }
}
void CRPSSingleIndexFrequency::ComputeFrequenciesMatrixFP(const CRPSWindLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{

}

bool CRPSSingleIndexFrequency::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	return true;
}

