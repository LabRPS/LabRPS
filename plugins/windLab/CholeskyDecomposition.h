#pragma once
#include "IrpsWLPSDdecompositionMethod.h"


class CCholeskyDecomposition : public IrpsWLPSDdecompositionMethod
{
public:

	void ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	void ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

