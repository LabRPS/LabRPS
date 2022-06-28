
#include "RPSUniformRandomPhases.h"
#include "RPSWindLabTools.h"
#include "minmaxvaluesdlg.h"
#include <QMessageBox>

static double minValue = 0;
static double maxValue = 6.28;

bool CRPSUniformRandomPhases::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	std::unique_ptr<MinMaxValuesDlg> dlg(new MinMaxValuesDlg(minValue, maxValue));
  
  if (dlg->exec() == QDialog::Accepted)
  {
	minValue = dlg->m_minValue;
  	maxValue = dlg->m_maxValue;
  } 
	return true;
}

void CRPSUniformRandomPhases::GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	std::srand((unsigned int) time(0));
	dRandomValueArray = (maxValue-minValue) * MatrixXd::Random(Data.numberOfFrequency, Data.numberOfSpatialPosition);
	dRandomValueArray.array() += minValue;
}

void CRPSUniformRandomPhases::ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation)
{

}