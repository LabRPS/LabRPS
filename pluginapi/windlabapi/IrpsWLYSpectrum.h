#ifndef IRPSWLYSPECTRUM_H
#define IRPSWLYSPECTRUM_H

#include "RPSWindLabsimuData.h"

class IrpsWLYSpectrum 
{
public:
    virtual ~IrpsWLYSpectrum() {};

    virtual void ComputeYAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual void ComputeYAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeYCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLYSPECTRUM_H
