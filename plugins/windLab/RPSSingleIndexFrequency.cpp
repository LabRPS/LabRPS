
#include "RPSSingleIndexFrequency.h"
#include <QMessageBox>


bool CRPSSingleIndexFrequency::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	for (int l = 0; l < Data.numberOfFrequency; l++)
	{
		dVarVector(l) = l+1;
		dValVector(l) = Data.minFrequency + l * Data.frequencyIncrement;
	}

	strInformation.append("Frequency distribution successfully computed");
	return true;
}

bool CRPSSingleIndexFrequency::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
    QMessageBox::warning(0,"Frequency Distribution", "This is the single index frequency distribution. No additional input needed.");

	return true;
}

bool CRPSSingleIndexFrequency::ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation)
{
    dValue = Data.minFrequency + frequencyIndex * Data.frequencyIncrement;
	return true;
}

