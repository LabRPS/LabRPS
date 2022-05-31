#pragma once
#include "IrpsSeLPSDdecompositionMethod.h"

class CSLCholeskyDecomposition : public IrpsSeLPSDdecompositionMethod
{
public:
	void ComputeDecomposedCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);
};

