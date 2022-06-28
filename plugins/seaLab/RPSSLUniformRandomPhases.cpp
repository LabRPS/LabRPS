#include "RPSSLUniformRandomPhases.h"

#include "minmaxvaluesdlg.h"
#include <QSettings>

// static double minValue = 0;
// static double maxValue = 6.28;

void CRPSSLUniformRandomPhases::GenerateRandomArrayFP(const CRPSSeaLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	QSettings settings;
    settings.beginGroup("plugins/seaLab/uniformRandomness");
    double minValue = settings.value("minValue").toDouble();
    double maxValue = settings.value("maxValue").toDouble();
    settings.endGroup(); 

    std::srand((unsigned int) time(0));
	dRandomValueArray = (maxValue-minValue) * MatrixXd::Random(Data.numberOfFrequency, Data.numberOfSpatialPosition);
	dRandomValueArray.array() += minValue;
}
void CRPSSLUniformRandomPhases::ComputeRandomValue(const CRPSSeaLabsimuData &Data, double &dValue, QStringList &strInformation)
{
	
}

bool CRPSSLUniformRandomPhases::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	std::unique_ptr<MinMaxValuesDlg> dlg(new MinMaxValuesDlg());
	dlg->exec();

	// dlg->minValue = minValue;
  	// dlg->maxValue = maxValue;
  
//   if (dlg->exec() == QDialog::Accepted)
//   {
// 	minValue = dlg->minValue;
//   	maxValue = dlg->maxValue;
//   } 
	return true;
}

