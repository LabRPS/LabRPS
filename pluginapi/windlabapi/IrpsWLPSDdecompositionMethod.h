#pragma once
#include "RPSWindLabsimuData.h"

class IrpsWLPSDdecompositionMethod
{
public:

	virtual void ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};