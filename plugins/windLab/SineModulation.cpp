
#include "SineModulation.h"
// #include "SineModuDlg.h"

void CSineModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// for (int k = 0; k < Data.m_iNumberOfTimeIncrements; k++)
	// {
	// 	dModulationVector(k) = sin(3.14*Data.m_dTimeIncrement*k / m_dPulseDuration);

	// }
}
void CSineModulation::ComputeModulationVectorF(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CSineModulation::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CSineModulation::ComputeModulationMatrixTP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CSineModulation::ComputeModulationMatrixFP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CSineModulation::ComputeModulationMatrixTF(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CSineModulation::ComputeModulationCubeTFP(const CRPSWindLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{

}

bool CSineModulation::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// // Create a exponential modulation function dialog
	// CSineModuDlg   SineModuModelDialog;

	// // Make the dt in the dialog equaled to the one in the document
	// SineModuModelDialog.m_dPulseDuration = m_dPulseDuration;

	// // If the ok bouton on the dialog (with modal display) is clicked then do the following
	// if (SineModuModelDialog.DoModal() == IDOK)
	// {
	// 	// Save the To parameter in the document
	// 	m_dPulseDuration = SineModuModelDialog.m_dPulseDuration;
	// }

	return true;
}


void CSineModulation::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{

}
