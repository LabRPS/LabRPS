
#include "CholeskyDecomposition.h"
#include "RPSWindLabTools.h"
#include "RPSWindLabFramework.h"




void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
	// dCPSDDecomMatrix = chol(dPSDMatrix, "lower");
}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// 	// Local array for the frequencies vector
	// vec dFrequencies ;

	// // Local array for the cpsd
	// mat dCPSDarray;

	// // Local 2D array for the decomposed cpsd
	// mat dCPSDdecomarray;

	// // Local 3D array for the decomposed cpsd
	// cube dCPSDdecop3Darray;

	// cube dCPSD3Darray;


	// try
	// {
	// 	// Allocate memory for cpsd array
	// 	dCPSDarray.zeros(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfSpatialPosition);

	// 	// Allocate memory for the 2D cpsd decomposed array
	// 	dCPSDdecomarray.zeros(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfSpatialPosition);

	// 	// Allocate memory for the 3D cpsd decomposed array
	// 	dCPSDdecop3Darray.zeros(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfFrequency);

	// 	dCPSD3Darray.zeros(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfFrequency);

	// 	dFrequencies.zeros(Data.m_iNumberOfFrequency);
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

	// QString msg = ("");

	// CRPSWindLabFramework::ComputeCrossSpectrumCubePPF(Data, dCPSD3Darray, strInformation);

	// for (int loop = 1; loop <= Data.m_iNumberOfSpatialPosition; loop++)
	// {
	// 	// Compute the single index frequency (Shinozuka)
	// 	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	// 	// For each frequency increment
	// 	for (int loop3 = 0; loop3 < Data.m_iNumberOfFrequency; loop3++)
	// 	{
	// 		//// Compute psd matrix for each fequency increment
	// 		//CRPSWindLabFramework::ComputeCrossSpectrumMatrixPP(Data, dCPSDarray, strInformation);
	// 		dCPSDarray = dCPSD3Darray.slice(loop3);

	// 		// Compute the cholesky decomposition of the psd matrix
	// 		//CRPSWindLabTools::RPSComputeCholeskyDecomposition(dCPSDarray, Data.m_iNumberOfSpatialPosition, dCPSDdecomarray);
	// 		dCPSDdecomarray = chol(dCPSDarray, "lower");

	// 		// For each row
	// 		for (int loop1 = 0; loop1 < Data.m_iNumberOfSpatialPosition; loop1++)
	// 		{
	// 			// For each col
	// 			for (int loop2 = 0; loop2 <= loop1; loop2++)
	// 			{
	// 				// Save each cholesky decomposed matrix in a 3D matrix
	// 				dCPSDdecop3Darray(loop1, loop2, loop3) = dCPSDdecomarray(loop1, loop2);
	// 			}
	// 		}
	// 	}

	// 	// Save only the loop-th colum of each 3D decomposed psd matrix
	// 	for (int loop1 = 0; loop1 < Data.m_iNumberOfSpatialPosition; loop1++)
	// 	{
	// 		// For each col
	// 		for (int loop2 = 0; loop2 < Data.m_iNumberOfFrequency; loop2++)
	// 		{
	// 			dCPSDDecomCube(loop1, loop - 1, loop2) = dCPSDdecop3Darray(loop1, loop - 1, loop2);
	// 		}
	// 	}
	// }
}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{

}

bool CCholeskyDecomposition::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	return true ;
}

void CCholeskyDecomposition::ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{

}
