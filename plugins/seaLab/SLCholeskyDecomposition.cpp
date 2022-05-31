#include "SLCholeskyDecomposition.h"
#include "RPSSeaLabFramework.h"


void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfSpatialPosition; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dCPSDDecomMatrix(i, j) = 99;
		}
	}
}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfSpatialPosition; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			for (int k = 0; k < Data.numberOfFrequency; k++)
			{
				dCPSDDecomCube(i, j, k) = 20;
			}
		}
	}

	//// Local array for the frequencies vector
	//vec dFrequencies ;

	//// Local array for the cpsd
	//mat dCPSDarray;

	//// Local 2D array for the decomposed cpsd
	//mat dCPSDdecomarray;

	//// Local 3D array for the decomposed cpsd
	//cube dCPSDdecop3Darray;

	//try
	//{
	//	// Allocate memory for cpsd array
	//	dCPSDarray.zeros(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfSpatialPosition);

	//	// Allocate memory for the 2D cpsd decomposed array
	//	dCPSDdecomarray.zeros(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfSpatialPosition);

	//	// Allocate memory for the 3D cpsd decomposed array
	//	dCPSDdecop3Darray.zeros(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfFrequency);

	//	dFrequencies.zeros(Data.m_iNumberOfFrequency);
	//}
	//catch (CMemoryException* pEx)
	//{
	//	// Simply show an error message to the user.
	//	pEx->ReportError();
	//	pEx->Delete();
	//	return;
	//}
	//catch (bad_alloc &ba)
	//{
	//	QString msg(ba.what());
	//	AfxMessageBox(msg);
	//	return;
	//}

	//QString msg = _T("");

	//for (int loop = 1; loop <= Data.m_iNumberOfSpatialPosition && true == CRPSSeaLabTools::GetSimuInProcessFlag(); loop++)
	//{
	//	// Compute the single index frequency (Shinozuka)
	//	CRPSSeaLabFramework::ComputeFrequenciesVector(Data, loop - 1, dFrequencies, strInformation);

	//	// For each frequency increment
	//	for (int loop3 = 0; loop3 < Data.m_iNumberOfFrequency && true == CRPSSeaLabTools::GetSimuInProcessFlag(); loop3++)
	//	{
	//		// Compute psd matrix for each fequency increment
	//		CRPSSeaLabFramework::ComputeCrossSpectrumMatrix(Data, dFrequencies(loop3), dCPSDarray, strInformation);

	//		// Compute the cholesky decomposition of the psd matrix
	//		//CRPSWindLabTools::RPSComputeCholeskyDecomposition(dCPSDarray, Data.m_iNumberOfSpatialPosition, dCPSDdecomarray);
	//		dCPSDdecomarray = chol(dCPSDarray, "lower");

	//		// For each row
	//		for (int loop1 = 0; loop1 < Data.m_iNumberOfSpatialPosition && true == CRPSSeaLabTools::GetSimuInProcessFlag(); loop1++)
	//		{
	//			// For each col
	//			for (int loop2 = 0; loop2 <= loop1 && true == CRPSSeaLabTools::GetSimuInProcessFlag(); loop2++)
	//			{
	//				// Save each cholesky decomposed matrix in a 3D matrix
	//				dCPSDdecop3Darray(loop1, loop2, loop3) = dCPSDdecomarray(loop1, loop2);
	//			}
	//		}
	//	}

	//	// Save only the loop-th colum of each 3D decomposed psd matrix
	//	for (int loop1 = 0; loop1 < Data.m_iNumberOfSpatialPosition && true == CRPSSeaLabTools::GetSimuInProcessFlag(); loop1++)
	//	{
	//		// For each col
	//		for (int loop2 = 0; loop2 < Data.m_iNumberOfFrequency && true == CRPSSeaLabTools::GetSimuInProcessFlag(); loop2++)
	//		{
	//			dCPSDDecomMatrice(loop1, loop - 1, loop2) = dCPSDdecop3Darray(loop1, loop - 1, loop2);
	//		}
	//	}
	//}
}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{

}
void CSLCholeskyDecomposition::ComputeDecomposedCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{

}

bool CSLCholeskyDecomposition::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	return true ;
}