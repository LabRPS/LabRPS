#pragma once
#include "RPSSeismicLabsimuData.h"

class IrpsSLPSDdecompositionMethod
{
public:

	virtual void ComputeDecomposedCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedPSDValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;
};