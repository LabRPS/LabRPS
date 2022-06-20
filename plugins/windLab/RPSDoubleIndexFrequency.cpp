
#include "RPSDoubleIndexFrequency.h"
#include <QMessageBox>


void CRPSDoubleIndexFrequency::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	for (int l = 0; l < Data.numberOfFrequency; l++)
	{
		dFrequencyVector(l) = Data.minFrequency + l * Data.frequencyIncrement + (Data.locationJ + 1)*Data.frequencyIncrement / Data.numberOfSpatialPosition;
	}
}
void CRPSDoubleIndexFrequency::ComputeFrequenciesMatrixFP(const CRPSWindLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfFrequency; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dFrequencyMatrix(i, j) = Data.minFrequency + i * Data.frequencyIncrement + (j + 1) * Data.frequencyIncrement / Data.numberOfSpatialPosition;
		}
	}
}

bool CRPSDoubleIndexFrequency::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	QMessageBox::warning(0,"Frequency Distribution", "This is the double index frequency distribution (see Deodatis et al, 1987). No additional input needed.");

	return true;
}

