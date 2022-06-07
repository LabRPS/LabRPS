
#include "RPSSLSingleIndexFrequency.h"

void CRPSSLSingleIndexFrequency::ComputeFrequenciesVectorF(const CRPSSeismicLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	// compute the frequency value
	for (int l = 0; l < Data.numberOfFrequency; l++)
	{
		dFrequencyVector(l) = Data.minFrequency + l * Data.frequencyIncrement;
	}
}
void CRPSSLSingleIndexFrequency::ComputeFrequenciesMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{

}

bool CRPSSLSingleIndexFrequency::OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation)
{
	return true;
}