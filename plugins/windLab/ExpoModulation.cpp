
#include "ExpoModulation.h"

bool CExpoModulation::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// // Create a exponential modulation function dialog
	// CExpoModuDialog   ExpoModuModelDialog;

	// // Make the To in the dialog equaled to the one in the document
	// ExpoModuModelDialog.m_dTimeOfMax = m_dTimeOfMax;

	// // Make the Dt in the dialog equaled to the one in the document
	// ExpoModuModelDialog.m_dStormLength = m_dStormLength;

	// // If the ok bouton on the dialog (with modal display) is clicked then do the following
	// if (ExpoModuModelDialog.DoModal() == IDOK)
	// {
	// 	// Save the To parameter in the document
	// 	m_dTimeOfMax = ExpoModuModelDialog.m_dTimeOfMax;

	// 	// Save the Dt parameter in the document
	// 	m_dStormLength = ExpoModuModelDialog.m_dStormLength;
	// }

	return true;
}

void CExpoModulation::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// dValue = exp(-(dTime - m_dTimeOfMax)*(dTime - m_dTimeOfMax) / (2 * m_dStormLength*m_dStormLength));

}

void CExpoModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	//  //For each time increment
	// for (int k = 0; k < Data.m_iNumberOfTimeIncrements; k++)
	// {
	// 	// compute approximate buffeting force 
	// 	dModulationVector(k) = exp(-(Data.m_dTimeIncrement*k - m_dTimeOfMax)*(Data.m_dTimeIncrement*k - m_dTimeOfMax) / (2 * m_dStormLength*m_dStormLength));

	// }
}
void CExpoModulation::ComputeModulationVectorF(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CExpoModulation::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CExpoModulation::ComputeModulationMatrixTP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CExpoModulation::ComputeModulationMatrixFP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CExpoModulation::ComputeModulationMatrixTF(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CExpoModulation::ComputeModulationCubeTFP(const CRPSWindLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{

}