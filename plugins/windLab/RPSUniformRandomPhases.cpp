
#include "RPSUniformRandomPhases.h"
#include "widgets/minmaxvaluesdlg.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/general/UniformRandomPhaseMatrixGenerator.h"

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

bool CRPSUniformRandomPhases::GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseMatrix(dRandomValueArray, minValue, maxValue);
return true;
}

bool CRPSUniformRandomPhases::ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseValue(dValue, minValue, maxValue);
    return true;
}
