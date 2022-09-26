#ifndef IRPSSLXSPECTRUM_H
#define IRPSSLXSPECTRUM_H

#include "RPSSeismicLabsimuData.h"

class IrpsSLXSpectrum 
{
public:
    virtual ~IrpsSLXSpectrum() {};

	virtual void ComputeXCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSSLXSPECTRUM_H
