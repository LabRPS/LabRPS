#pragma once
#include "IrpsWLXSpectrum.h"


class CRPSKaimalSpectr : public IrpsWLXSpectrum
{
public:

	void ComputeXCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeXCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeXCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeXCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeXCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeXCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeXCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	void ComputeXCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	void ComputeXCrossSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);


public:
	double ComputeTargetAutoSpectrumValue(const CRPSWindLabsimuData &Data, double dFrequency, double dHeight, double dMeanSpeed);
};

