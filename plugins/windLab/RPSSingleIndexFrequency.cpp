
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

bool CRPSSingleIndexFrequency::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
    QMessageBox::warning(0,"Frequency Distribution", "This is the single index frequency distribution. No additional input needed.");

	return true;
}

void CRPSSingleIndexFrequency::ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation)
{
    dValue = Data.minFrequency + frequencyIndex * Data.frequencyIncrement;
}

