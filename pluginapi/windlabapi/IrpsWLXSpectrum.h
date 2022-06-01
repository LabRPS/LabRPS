#pragma once
#include "RPSWindLabsimuData.h"
class IrpsWLXSpectrum
{
public:

	virtual void ComputeXCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
