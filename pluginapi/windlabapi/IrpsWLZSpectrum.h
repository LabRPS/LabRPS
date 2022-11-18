#ifndef IRPSWLZSPECTRUM_H
#define IRPSWLZSPECTRUM_H

#include "RPSWindLabsimuData.h"

class IrpsWLZSpectrum 
{
public:
    virtual ~IrpsWLZSpectrum() {};

    virtual void ComputeZAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual void ComputeZAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeZCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLZSPECTRUM_H
