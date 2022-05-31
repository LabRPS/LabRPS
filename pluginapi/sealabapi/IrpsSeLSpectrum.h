#pragma once
#include "RPSSeaLabsimuData.h"

class IrpsSeLSpectrum 
{
public:

    virtual ~IrpsSeLSpectrum() {}

	virtual void ComputeCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;

};
