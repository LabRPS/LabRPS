#ifndef IRPSWLXSPECTRUM_H
#define IRPSWLXSPECTRUM_H

#include "RPSWindLabsimuData.h"
class IrpsWLXSpectrum
{
public:
    virtual ~IrpsWLXSpectrum() {};

    virtual void ComputeXAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual void ComputeXAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLSIMUMETHOD_H
