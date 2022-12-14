
#include "RPSDoubleIndexFrequency.h"
#include <QMessageBox>


void CRPSDoubleIndexFrequency::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	for (int l = 0; l < Data.numberOfFrequency; l++)
	{
		dVarVector(l) = l+1;
		dValVector(l) = Data.minFrequency + l * Data.frequencyIncrement + (Data.locationJ + 1)*Data.frequencyIncrement / Data.numberOfSpatialPosition;
	}
}

bool CRPSDoubleIndexFrequency::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	QMessageBox::warning(0,"Frequency Distribution", "This is the double index frequency distribution (see Deodatis et al, 1987). No additional input needed.");

	return true;
}

void CRPSDoubleIndexFrequency::ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation)
{
    dValue = Data.minFrequency + frequencyIndex * Data.frequencyIncrement + (locationIndex + 1)*Data.frequencyIncrement / Data.numberOfSpatialPosition;
}
