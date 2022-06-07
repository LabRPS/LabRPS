
#include "RPSSLDoubleIndexFrequency.h"

void CRPSSLDoubleIndexFrequency::ComputeFrequenciesVectorF(const CRPSSeismicLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	for (int l = 0; l < Data.numberOfFrequency; l++)
	{
		dFrequencyVector(l) = Data.minFrequency + l * Data.frequencyIncrement + (Data.locationJ + 1)*Data.frequencyIncrement / Data.numberOfSpatialPosition;
	}
}
void CRPSSLDoubleIndexFrequency::ComputeFrequenciesMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{

}

bool CRPSSLDoubleIndexFrequency::OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation)
{
	return true;
}
