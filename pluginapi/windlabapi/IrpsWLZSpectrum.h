#ifndef IRPSWLZSPECTRUM_H
#define IRPSWLZSPECTRUM_H

#include "RPSWindLabsimuData.h"

class IrpsWLZSpectrum 
{
public:
    virtual ~IrpsWLZSpectrum() {};

    virtual bool ComputeZAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

    virtual bool ComputeZAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeZAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeZCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLZSPECTRUM_H
