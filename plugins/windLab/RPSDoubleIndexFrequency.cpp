
#include "RPSDoubleIndexFrequency.h"


void CRPSDoubleIndexFrequency::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	// for (int l = 0; l < Data.m_iNumberOfFrequency; l++)
	// {
	// 	dFrequencyVector(l) = Data.m_dMinFrequency + l * Data.m_dFrequencyIncrement + (Data.m_iLocationJ + 1)*Data.m_dFrequencyIncrement / Data.m_iNumberOfSpatialPosition;
	// }
}
void CRPSDoubleIndexFrequency::ComputeFrequenciesMatrixFP(const CRPSWindLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{

}

bool CRPSDoubleIndexFrequency::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	return true;
}

