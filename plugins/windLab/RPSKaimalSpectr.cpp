
#include "RPSKaimalSpectr.h"
#include "RPSWindLabFramework.h"
// #include "ShearVeloDialog.h"
#include "RPSWindLabTools.h"

// The shear velocity of the flow
static double dShearVecForSpec = 1.76;
// Some constant
double dBuf, dBuf1, dBuf2, dBuf3, dBuf4;
double dPSD = 0.0;
double Par1 = 200.0;
double Par2 = 50.0;
double PI = 22.0 / 7.0;
double Coherence = 0.0;

void CRPSKaimalSpectr::ComputeXCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// // Local array for location coordinates
	// mat dLocCoord;
	// //vec dMeanSpeed;
	// vec dcoherenceVector;
	// vec dFrequencies;

	// try
	// {
	// 	dLocCoord.set_size(Data.m_iNumberOfSpatialPosition, 3);
	// 	//dMeanSpeed.set_size(Data.m_iNumberOfSpatialPosition);
	// 	dcoherenceVector.set_size(Data.m_iNumberOfFrequency);
	// 	dFrequencies.set_size(Data.m_iNumberOfFrequency);

	// 	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	// 	CRPSWindLabFramework::ComputeCrossCoherenceVectorF(Data, dcoherenceVector, strInformation);
	// 	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	// }
	// catch (CMemoryException* pEx)
	// {
	// 	// Simply show an error message to the user.
	// 	pEx->ReportError();
	// 	pEx->Delete();
	// 	return;
	// }
	// catch (bad_alloc &ba)
	// {
	// 	QString msg(ba.what());
	// 	AfxMessageBox(msg);
	// 	return;
	// }


	// double dFrequency = 0.0;
	// double dMeanSpeed1 = 0.0;
	// double dMeanSpeed2 = 0.0;
	// double dTime = Data.m_dTimeIncrement*Data.m_iTimeIndex;
	// int loop1 = Data.m_iLocationJ;
	// int loop2 = Data.m_iLocationK;

	// for (int loop = 0; loop < Data.m_iNumberOfFrequency; loop++)
	// {
	// 	dFrequency = dFrequencies(loop);

	// 	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
	// 	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);
	// 	dPSDVector(loop) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop1, 2), dMeanSpeed1)*
	// 		ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop2, 2), dMeanSpeed2))*
	// 		dcoherenceVector(loop);
	// }
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CRPSKaimalSpectr::ComputeXCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CRPSKaimalSpectr::ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// // Local array for location coordinates
	// mat dLocCoord;
	// //vec dMeanSpeed;
	// mat dcoherenceArray;
	// vec dFrequencies;

	// try
	// {
	// 	dLocCoord.set_size(Data.m_iNumberOfSpatialPosition, 3);
	// 	//dMeanSpeed.set_size(Data.m_iNumberOfSpatialPosition);
	// 	dcoherenceArray.set_size(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfSpatialPosition);
	// 	dFrequencies.set_size(Data.m_iNumberOfFrequency);

	// 	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	// 	CRPSWindLabFramework::ComputeCrossCoherenceMatrixPP(Data, dcoherenceArray, strInformation);
	// 	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	// }
	// catch (CMemoryException* pEx)
	// {
	// 	// Simply show an error message to the user.
	// 	pEx->ReportError();
	// 	pEx->Delete();
	// 	return;
	// }
	// catch (bad_alloc &ba)
	// {
	// 	QString msg(ba.what());
	// 	AfxMessageBox(msg);
	// 	return;
	// }


	// double dFrequency = dFrequencies(Data.m_iFrequencyIndex);
	// double dMeanSpeed1 = 0.0;
	// double dMeanSpeed2 = 0.0;
	// double dTime = Data.m_dTimeIncrement*Data.m_iTimeIndex;


	// for (int loop1 = 0; loop1 < Data.m_iNumberOfSpatialPosition; loop1++)
	// {
	// 	for (int loop2 = 0; loop2 < Data.m_iNumberOfSpatialPosition; loop2++)
	// 	{
	// 		CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
	// 		CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);
	// 		dPSDMatrix(loop1, loop2) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop1, 2), dMeanSpeed1)*
	// 			ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop2, 2), dMeanSpeed2))*
	// 			dcoherenceArray(loop1, loop2);
	// 	}
	// }
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSKaimalSpectr::ComputeXCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// // Local array for location coordinates
	// mat dLocCoord;
	// //vec dMeanSpeed;
	// vec dFrequencies;

	// try
	// {
	// 	dLocCoord.set_size(Data.m_iNumberOfSpatialPosition, 3);
	// 	//dMeanSpeed.set_size(Data.m_iNumberOfSpatialPosition);
	// 	dFrequencies.set_size(Data.m_iNumberOfFrequency);

	// 	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	// 	//CRPSWindLabFramework::ComputeMeanWindSpeed(Data, dMeanSpeed, strInformation);
	// 	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	// }
	// catch (CMemoryException* pEx)
	// {
	// 	// Simply show an error message to the user.
	// 	pEx->ReportError();
	// 	pEx->Delete();
	// 	return;
	// }
	// catch (bad_alloc &ba)
	// {
	// 	QString msg(ba.what());
	// 	AfxMessageBox(msg);
	// 	return;
	// }

	// //double frequency = dFrequencies(Data.m_iFrequencyIndex);
	// double thePSD = 0.0;
	// double dTime = Data.m_dTimeIncrement*Data.m_iTimeIndex;

	// for (int loop1 = 0; loop1 < Data.m_iNumberOfFrequency; loop1++)
	// {
	// 	for (int loop2 = 0; loop2 < Data.m_iNumberOfSpatialPosition; loop2++)
	// 	{
	// 		// Compute the frequency vector
	// 		ComputeXCrossSpectrumValue(Data, thePSD, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dFrequencies(loop1), dTime, strInformation);
	// 		dPSDMatrix(loop1, loop2) = thePSD;
	// 	}
	// }
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CRPSKaimalSpectr::ComputeXCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// // Local array for location coordinates
	// mat dLocCoord;
	// cube dcoherenceCube;
	// vec dFrequencies;

	// try
	// {
	// 	dLocCoord.set_size(Data.m_iNumberOfSpatialPosition, 3);
	// 	dFrequencies.set_size(Data.m_iNumberOfFrequency);
	// 	dcoherenceCube.zeros(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfFrequency);

	// 	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	// 	CRPSWindLabFramework::ComputeCoherenceCubePPF(Data, dcoherenceCube, strInformation);
	// 	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	// }
	// catch (CMemoryException* pEx)
	// {
	// 	// Simply show an error message to the user.
	// 	pEx->ReportError();
	// 	pEx->Delete();
	// 	return;
	// }
	// catch (bad_alloc &ba)
	// {
	// 	QString msg(ba.what());
	// 	AfxMessageBox(msg);
	// 	return;
	// }


	// double dFrequency ;
	// double dMeanSpeed1 = 0.0;
	// double dMeanSpeed2 = 0.0;
	// double dTime = Data.m_dTimeIncrement*Data.m_iTimeIndex;


	// for (int loop3 = 0; loop3 < Data.m_iNumberOfFrequency; loop3++)
	// {
	// 	dFrequency = dFrequencies(loop3);

	// 	for (int loop1 = 0; loop1 < Data.m_iNumberOfSpatialPosition; loop1++)
	// 	{
	// 		for (int loop2 = 0; loop2 < Data.m_iNumberOfSpatialPosition; loop2++)
	// 		{
	// 			CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dTime, strInformation);
	// 			CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), dTime, strInformation);
	// 			dPSDCube(loop1, loop2, loop3) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop1, 2), dMeanSpeed1)*
	// 				ComputeTargetAutoSpectrumValue(Data, dFrequency, dLocCoord(loop2, 2), dMeanSpeed2))*
	// 				dcoherenceCube(loop1, loop2, loop3);
	// 		}
	// 	}
	// }
}
void CRPSKaimalSpectr::ComputeXCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}

double CRPSKaimalSpectr::ComputeTargetAutoSpectrumValue(const CRPSWindLabsimuData &Data, double dFrequency, double dHeight, double dMeanSpeed)
{
	// dBuf1 = 1.0 + Par2 * dFrequency * dHeight / (2.0 * PI * dMeanSpeed);

	// dBuf = pow(dBuf1, 5.0 / 3.0);

	// dPSD = Par1 * dShearVecForSpec * dShearVecForSpec * dHeight / dMeanSpeed;

	// dPSD /= dBuf;			// (rad/s)

	// dPSD /= 2.0*PI;

	// return dPSD;

	return 0;
}



//Initial setting
bool CRPSKaimalSpectr::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// //Create a dimensionless dialog
	// CShearVeloDialog Dlg;

	// Dlg.mdShearVecForSpec = dShearVecForSpec;

	// if (Dlg.DoModal() == IDOK)  // 
	// {
	// 	dShearVecForSpec = Dlg.mdShearVecForSpec;
	// }

	return true;
}


//void CRPSKaimalSpectr::ComputeXCrossSpectrumVector(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
//{
//	// Local array for location coordinates
//	mat dLocCoord;
//	vec dFrequencies;
//
//	try
//	{
//		dLocCoord.set_size(Data.m_iNumberOfSpatialPosition, 3);
//
//		dFrequencies.set_size(Data.m_iNumberOfFrequency);
//
//		CRPSWindLabFramework::ComputeFrequenciesVector(Data, dFrequencies, strInformation);
//		CRPSWindLabFramework::ComputeLocationCoord(Data, dLocCoord, strInformation);
//
//	}
//	catch (CMemoryException* pEx)
//	{
//		// Simply show an error message to the user.
//		pEx->ReportError();
//		pEx->Delete();
//		return;
//	}
//	catch (bad_alloc &ba)
//	{
//		QString msg(ba.what());
//		AfxMessageBox(msg);
//		return;
//	}
//
//
//
//	int loop1;
//	int loop2;
//	double Coherence;
//	double dMeanSpeed1 = 0.0;
//	double dMeanSpeed2 = 0.0;
//	double dTime = Data.m_dTimeIncrement*Data.m_iTimeIndex;
//
//	for (int loop = 0; loop < Data.m_iNumberOfFrequency; loop++)
//	{
//		loop1 = Data.m_iLocationJ;
//		loop2 = Data.m_iLocationK;
//
//		CRPSWindLabFramework::ComputeCoherenceValue(Data, Coherence, dLocCoord(Data.m_iLocationJ, 0), dLocCoord(Data.m_iLocationJ, 1), dLocCoord(Data.m_iLocationJ, 2), dLocCoord(Data.m_iLocationK, 0), dLocCoord(Data.m_iLocationK, 1), dLocCoord(Data.m_iLocationK, 2), dFrequencies(loop), dTime, strInformation);
//		CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocCoord(Data.m_iLocationJ, 0), dLocCoord(Data.m_iLocationJ, 1), dLocCoord(Data.m_iLocationJ, 2), dTime, strInformation);
//		CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocCoord(Data.m_iLocationK, 0), dLocCoord(Data.m_iLocationK, 1), dLocCoord(Data.m_iLocationK, 2), dTime, strInformation);
//
//		dPSDVector(loop) = sqrt(ComputeTargetAutoSpectrumValue(Data, dFrequencies(loop), dLocCoord(loop1, 2), dMeanSpeed1)*
//			ComputeTargetAutoSpectrumValue(Data, dFrequencies(loop), dLocCoord(loop2, 2), dMeanSpeed2))*
//			Coherence;
//	}
//}


void CRPSKaimalSpectr::ComputeXCrossSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{

	// double dMeanSpeed = 0.0;
	// CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dTime, strInformation);


	// dBuf1 = 1.0 + Par2 * dFrequency * dLocationJzCoord / (2.0 * PI * dMeanSpeed);

	// dBuf = pow(dBuf1, 5.0 / 3.0);

	// dPSD = Par1 * dShearVecForSpec * dShearVecForSpec * dLocationJzCoord / dMeanSpeed;

	// dPSD /= dBuf;			// (rad/s)

	// dPSD /= 2.0*PI;

	// dValue =  dPSD;
}
