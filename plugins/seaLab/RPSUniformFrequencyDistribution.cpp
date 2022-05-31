#include "RPSUniformFrequencyDistribution.h"

void CRPSUniformFrequencyDistribution::ComputeFrequenciesVectorF(const CRPSSeaLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	for (int l = 0; l < Data.numberOfFrequency; l++)
	{
		dFrequencyVector(l) = Data.minFrequency + l * Data.frequencyIncrement;
	}
}

void CRPSUniformFrequencyDistribution::ComputeFrequenciesMatrixFP(const CRPSSeaLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{

}

bool CRPSUniformFrequencyDistribution::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	return true;
}