
#include "CholeskyDecomposition.h"
#include "RPSWindLabTools.h"
#include "RPSWindLabFramework.h"
#include <QMessageBox>

void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	ObjectDescription description = CRPSWindLabFramework::getFrequencyDistributionObjDescription(Data.freqencyDistribution);
	if(Data.freqencyDistribution != "Single Index Frequency" || description.m_pluginName != "windLab" || description.m_publicationAuthor != "Koffi Daniel")
	{
		strInformation.append("Computation fails. This method requires the single index frequency distribution from the windLab plugin created by Koffi Daneil");
		return;
	}

	// allocate memory for all array needed
	mat decompPSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	mat PSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	cube dPSDCube(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfFrequency);

	// compute the psd cube for all positions and frequencies
	CRPSWindLabFramework::ComputeCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	for (int loop = 0; loop < Data.numberOfFrequency; loop++)
	{
		for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
		{
			for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
			{
				// for each frequency pick corresponding matrix
				PSDMatrix(loop1, loop2) = dPSDCube(loop1, loop2, loop);
			}
		}

		// decompose each matrix
		ComputeDecomposedCrossSpectrumMatrixPP(Data, decompPSDMatrix, PSDMatrix, strInformation);

		// pick the decomposed according to derised positions for each frequency
		dPSDVector(loop) = decompPSDMatrix(Data.locationJ, Data.locationK);
	}
}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// allocate memory for all array needed
	mat decompPSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	mat PSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	cube dPSDCube(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfTimeIncrements);

	// compute the psd cube for all positions and time
	CRPSWindLabFramework::ComputeCrossSpectrumCubePPT(Data, dPSDCube, strInformation);

	for (int loop = 0; loop < Data.numberOfTimeIncrements; loop++)
	{
		for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
		{
			for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
			{
				// for each frequency pick corresponding matrix
				PSDMatrix(loop1, loop2) = dPSDCube(loop1, loop2, loop);
			}
		}

		// decompose each matrix
		ComputeDecomposedCrossSpectrumMatrixPP(Data, decompPSDMatrix, PSDMatrix, strInformation);

		// pick the decomposed according to derised positions for each time
		dPSDVector(loop) = decompPSDMatrix(Data.locationJ, Data.locationK);
	}
}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// allocate memory for all array needed
	mat decompPSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	mat PSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);

	// compute the psd matrix for selected frequency and time
	CRPSWindLabFramework::ComputeXCrossSpectrumMatrixPP(Data, PSDMatrix, strInformation);

	// decompose the psd matrix
	ComputeDecomposedCrossSpectrumMatrixPP(Data, decompPSDMatrix, PSDMatrix, strInformation);

	for (int loop = 0; loop < Data.numberOfSpatialPosition; loop++)
	{
		// colllect the value for all position (i,i)
		dPSDVector(loop) = decompPSDMatrix(loop, loop);
	}
}

void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
	// LLT<mat> lltOfdPSDMatrix(dPSDMatrix); // compute the Cholesky decomposition of dPSDMatrix
	// dCPSDDecomMatrix = lltOfdPSDMatrix.matrixL(); // retrieve factor L  in the decomposition

	// The previous two lines can also be written as "dCPSDDecomMatrix = dPSDMatrix.llt().matrixL()"
	dCPSDDecomMatrix = dPSDMatrix.llt().matrixL();
}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// allocate memory for all array needed
	mat decompPSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	mat PSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	cube dPSDCube(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfTimeIncrements);

	// compute the psd cube for all positions and time
	CRPSWindLabFramework::ComputeCrossSpectrumCubePPT(Data, dPSDCube, strInformation);

	for (int i = 0; i < Data.numberOfTimeIncrements; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
			{
				for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
				{
					// for each frequency pick corresponding matrix
					PSDMatrix(loop1, loop2) = dPSDCube(loop1, loop2, i);
				}
			}

			// decompose each matrix
			ComputeDecomposedCrossSpectrumMatrixPP(Data, decompPSDMatrix, PSDMatrix, strInformation);

			// pick the decomposed according to derised positions for each time
			dPSDMatrix(i, j) = decompPSDMatrix(j, j);
		}
	}
}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// allocate memory for all array needed
	mat decompPSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	mat PSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	cube dPSDCube(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfFrequency);

	// compute the psd cube for all positions and time
	CRPSWindLabFramework::ComputeCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	for (int i = 0; i < Data.numberOfFrequency; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
			{
				for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
				{
					// for each frequency pick corresponding matrix
					PSDMatrix(loop1, loop2) = dPSDCube(loop1, loop2, i);
				}
			}

			// decompose each matrix
			ComputeDecomposedCrossSpectrumMatrixPP(Data, decompPSDMatrix, PSDMatrix, strInformation);

			// pick the decomposed according to derised positions for each time
			dPSDMatrix(i, j) = decompPSDMatrix(j, j);
		}
	}
}

void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	strInformation.append("This function is not implemented.");
}

void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// allocate memory for all array needed
	mat decompPSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	mat PSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	cube dPSDCube(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfFrequency);

	// compute the psd cube for all positions and frequencies
	CRPSWindLabFramework::ComputeCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	for (int loop = 0; loop < Data.numberOfFrequency; loop++)
	{
		for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
		{
			for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
			{
				// for each frequency pick corresponding matrix
				PSDMatrix(loop1, loop2) = dPSDCube(loop1, loop2, loop);
			}
		}

		// decompose each matrix
		ComputeDecomposedCrossSpectrumMatrixPP(Data, decompPSDMatrix, PSDMatrix, strInformation);

        for (int i = 0; i < Data.numberOfSpatialPosition; i++)
		{
			for (int j = 0; j < Data.numberOfSpatialPosition; j++)
			{
				// for each frequency pick corresponding matrix
				dCPSDDecomCube(i, j, loop) = decompPSDMatrix(i, j);
			}
		}
		
	}
}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// allocate memory for all array needed
	mat decompPSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	mat PSDMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);
	cube dPSDCube(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfTimeIncrements);

	// compute the psd cube for all positions and frequencies
	CRPSWindLabFramework::ComputeCrossSpectrumCubePPT(Data, dPSDCube, strInformation);

	for (int loop = 0; loop < Data.numberOfTimeIncrements; loop++)
	{
		for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
		{
			for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
			{
				// for each frequency pick corresponding matrix
				PSDMatrix(loop1, loop2) = dPSDCube(loop1, loop2, loop);
			}
		}

		// decompose each matrix
		ComputeDecomposedCrossSpectrumMatrixPP(Data, decompPSDMatrix, PSDMatrix, strInformation);

        for (int i = 0; i < Data.numberOfSpatialPosition; i++)
		{
			for (int j = 0; j < Data.numberOfSpatialPosition; j++)
			{
				// for each frequency pick corresponding matrix
				dCPSDDecomCube(i, j, loop) = decompPSDMatrix(i, j);
			}
		}
		
	}
}

bool CCholeskyDecomposition::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	QMessageBox::warning(0, "Cholesky Decomposition", "Please, note that the lowwe triangular matrix will be computed.");
	return true;
}

void CCholeskyDecomposition::ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	strInformation.append("This function is not implemented.");
}
