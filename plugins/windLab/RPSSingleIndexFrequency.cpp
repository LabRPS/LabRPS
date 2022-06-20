
#include "RPSSingleIndexFrequency.h"
#include <QMessageBox>


void CRPSSingleIndexFrequency::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	for (int l = 0; l < Data.numberOfFrequency; l++)
	{
		dFrequencyVector(l) = Data.minFrequency + l * Data.frequencyIncrement;
	}

	strInformation.append("Frequency distribution successfully computed");
}
void CRPSSingleIndexFrequency::ComputeFrequenciesMatrixFP(const CRPSWindLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfFrequency; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dFrequencyMatrix(i, j) = Data.minFrequency + i * Data.frequencyIncrement;
		}
	}
}

bool CRPSSingleIndexFrequency::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	QMessageBox::warning(0,"Frequency Distribution", "This the single index frequency distribution. No additional input needed.");

	return true;
}

