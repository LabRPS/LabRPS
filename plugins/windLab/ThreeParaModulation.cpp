
#include "ThreeParaModulation.h"
// #include "ThreeParaModulatinDialog.h"
#include <QMessageBox>


void CThreeParaModulation::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// //  Maximum value of modulation function
	// double max = 0.0;

	// // For each time increment
	// for (int k = 0; k < Data.m_iNumberOfTimeIncrements; k++)
	// {
	// 	// compute approximate buffeting force 
	// 	dModulationVector(k) = m_dModAlpha * (pow(Data.m_dTimeIncrement*k, m_dModBeta))*(exp(-m_dModLambda * Data.m_dTimeIncrement*k));

	// 	// Max
	// 	if (dModulationVector(k) > max)
	// 	{
	// 		max = dModulationVector(k);
	// 	}
	// }

	// // For each time increment
	// for (int k = 0; k < Data.m_iNumberOfTimeIncrements; k++)
	// {
	// 	// Normalizing the modulation function 
	// 	dModulationVector(k) /= max;

	// }
}
void CThreeParaModulation::ComputeModulationVectorF(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CThreeParaModulation::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{

}
void CThreeParaModulation::ComputeModulationMatrixTP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CThreeParaModulation::ComputeModulationMatrixFP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CThreeParaModulation::ComputeModulationMatrixTF(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{

}
void CThreeParaModulation::ComputeModulationCubeTFP(const CRPSWindLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{

}


bool CThreeParaModulation::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// // Create a drad coefficient dialog
	// CThreeParaModulatinDialog   ThreeParaModDialog;

	// // Make the alpha in the dialog equaled to the one in the document
	// ThreeParaModDialog.m_dModAlpha = m_dModAlpha;

	// // Make the beta in the dialog equaled to the one in the document
	// ThreeParaModDialog.m_dModBeta = m_dModBeta;

	// // Make the lambda in the dialog equaled to the one in the document
	// ThreeParaModDialog.m_dModLambda = m_dModLambda;

	// // If the ok bouton on the dialog (with modal display) is clicked then do the following
	// if (ThreeParaModDialog.DoModal() == IDOK)
	// {
	// 	// Save the beta parameter in the document
	// 	m_dModBeta = ThreeParaModDialog.m_dModBeta;

	// 	// Save the lambda parameter in the document
	// 	m_dModLambda = ThreeParaModDialog.m_dModLambda;

	// 	// Save the alpha parameter in the document
	// 	m_dModAlpha = (pow(m_dModLambda, m_dModBeta)) / ((pow(m_dModBeta, m_dModBeta))*exp(m_dModBeta));

	// }
	QMessageBox::warning(0,"hi", "in in three para modulation");

	return true;
}

void CThreeParaModulation::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{

}
