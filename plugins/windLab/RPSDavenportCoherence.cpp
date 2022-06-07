
#include "RPSDavenportCoherence.h"
#include "RPSWindLabFramework.h"
#include "RPSWindLabTools.h"

// The decay coefficient Cx
static double dExponentialDecayCx = 10;

// The decay coefficient Cy
static double dExponentialDecayCy = 7;

// The decay coefficient Cy
static double dExponentialDecayCz = 6;



void CRPSDavenportCoherence::ComputeCoherenceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// double dMeanSpeed1 = 0.0;
	// double dMeanSpeed2 = 0.0;

	// CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dTime, strInformation);
	// CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dTime, strInformation);

	// dValue = (dExponentialDecayCx*dExponentialDecayCx * (dLocationJxCoord - dLocationKxCoord)*(dLocationJxCoord - dLocationKxCoord) +
	// 	dExponentialDecayCy * dExponentialDecayCy * (dLocationJyCoord - dLocationKyCoord)*(dLocationJyCoord - dLocationKyCoord) +
	// 	dExponentialDecayCz * dExponentialDecayCz * (dLocationJzCoord - dLocationKzCoord)*(dLocationJzCoord - dLocationKzCoord));

	// dValue = sqrt(dValue);

	// dValue = dValue / 2.0 / 3.14;

	// dValue = -2 * dValue / (dMeanSpeed1 + dMeanSpeed2);

	// dValue = exp(dValue * dFrequency);
}

bool  CRPSDavenportCoherence::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// CDecayCoefDlg Dlg;

	// Dlg.dExponentialDecayCx = dExponentialDecayCx;
	// Dlg.dExponentialDecayCy = dExponentialDecayCy;
	// Dlg.dExponentialDecayCz = dExponentialDecayCz;

	// if (Dlg.DoModal() == IDOK)  
	// {
	// 	dExponentialDecayCx = Dlg.dExponentialDecayCx;
	// 	dExponentialDecayCy = Dlg.dExponentialDecayCy;
	// 	dExponentialDecayCz = Dlg.dExponentialDecayCz;
	// }

	return true;
}

void  CRPSDavenportCoherence::ComputeCrossCoherenceVectorF(const CRPSWindLabsimuData &Data, vec &dCohVector, QStringList &strInformation)
{
	// // The coherence value
	// double dCoherenceValue = 0.0;
	// mat dLocCoord;
	// vec dFrequencies;


	// try
	// {
	// 	dLocCoord.set_size(Data.m_iNumberOfSpatialPosition, 3);
	// 	dFrequencies.set_size(Data.m_iNumberOfFrequency);

	// 	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	// 	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	// 	double dTime = Data.m_dTimeIncrement*Data.m_iTimeIndex;

	// 	for (int loop3 = 0; loop3 < Data.m_iNumberOfFrequency; loop3++)
	// 	{
	// 		ComputeCoherenceValue(Data, dCoherenceValue, dLocCoord(Data.m_iLocationJ, 0), dLocCoord(Data.m_iLocationJ, 1), dLocCoord(Data.m_iLocationJ, 2), dLocCoord(Data.m_iLocationK, 0), dLocCoord(Data.m_iLocationK, 1), dLocCoord(Data.m_iLocationK, 2), dFrequencies(loop3), dTime, strInformation);

	// 		dCohVector(loop3) = dCoherenceValue;
	// 	}

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
	// catch (const out_of_range &oor)
	// {
	// 	QString msg(oor.what());
	// 	AfxMessageBox(msg);
	// 	return;
	// }
	
}
void  CRPSDavenportCoherence::ComputeCrossCoherenceMatrixPP(const CRPSWindLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation)
{
	// mat dLocCoord;
	// vec dFrequencies;


	// try
	// {
	// 	// Local array for location coordinates
	// 	dLocCoord.set_size(Data.m_iNumberOfSpatialPosition, 3);
	// 	dFrequencies.set_size(Data.m_iNumberOfFrequency);

	// 	// Compute location coordinates
	// 	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
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
	
	// double coherence= 0.0;
	// double dTime = Data.m_dTimeIncrement*Data.m_iTimeIndex;
	// double frequency = dFrequencies(Data.m_iFrequencyIndex);

	// for (int loop1 = 0; loop1 < Data.m_iNumberOfSpatialPosition; loop1++)
	// {
	// 	for (int loop2 = 0; loop2 < Data.m_iNumberOfSpatialPosition; loop2++)
	// 	{
	// 		ComputeCoherenceValue(Data, coherence, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), frequency, dTime, strInformation);

	// 		dCoherenceMatrix(loop1, loop2) = coherence;

	// 	}
	// }
}
void  CRPSDavenportCoherence::ComputeCoherenceCubePPF(const CRPSWindLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation)
{
	// mat dLocCoord;
	// vec dFrequencies;

	// try
	// {
	// 	// Local array for location coordinates
	// 	dLocCoord.set_size(Data.m_iNumberOfSpatialPosition, 3);
	// 	dFrequencies.set_size(Data.m_iNumberOfFrequency);

	// 	// Compute location coordinates
	// 	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
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

	// double coherence = 0.0;
	// double dTime = Data.m_dTimeIncrement*Data.m_iTimeIndex;
	// double frequency = 0.0;

	// for (int loop3 = 0; loop3 < Data.m_iNumberOfFrequency; loop3++)
	// {
	// 	frequency = dFrequencies(loop3);

	// 	for (int loop1 = 0; loop1 < Data.m_iNumberOfSpatialPosition; loop1++)
	// 	{
	// 		for (int loop2 = 0; loop2 < Data.m_iNumberOfSpatialPosition; loop2++)
	// 		{
	// 			ComputeCoherenceValue(Data, coherence, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), frequency, dTime, strInformation);

	// 			dCoherenceCube(loop1, loop2, loop3) = coherence;

	// 		}
	// 	}
	// }
}

