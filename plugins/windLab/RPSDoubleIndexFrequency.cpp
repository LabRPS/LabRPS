
#include "RPSDoubleIndexFrequency.h"
#include <QMessageBox>
#include "myWidgets/RPSFrequencyDistributionDialog.h"

bool CRPSDoubleIndexFrequency::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	for (int l = 0; l < Data.numberOfFrequency; l++)
	{
		dVarVector(l) = l+1;
		dValVector(l) = Data.minFrequency + l * Data.frequencyIncrement + (Data.locationJ + 1)*Data.frequencyIncrement / Data.numberOfSpatialPosition;
	}
	return true;
}

bool CRPSDoubleIndexFrequency::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
    // the input diolag
    std::unique_ptr<RPSFrequencyDistributionDialog> dlg(new RPSFrequencyDistributionDialog(2));

    if (dlg->exec() == QDialog::Accepted) //
    {
    }

    return true;
}

bool CRPSDoubleIndexFrequency::ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation)
{
    dValue = Data.minFrequency + frequencyIndex * Data.frequencyIncrement + (locationIndex + 1)*Data.frequencyIncrement / Data.numberOfSpatialPosition;
return true;
}
