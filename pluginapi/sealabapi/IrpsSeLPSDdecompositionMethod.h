#pragma once
#include "RPSSeaLabsimuData.h"

class IrpsSeLPSDdecompositionMethod
{
public:

    virtual ~IrpsSeLPSDdecompositionMethod() {}

	virtual void ComputeDecomposedCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation) = 0;

	virtual void ComputeDecomposedCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;

};