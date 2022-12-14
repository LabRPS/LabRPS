#ifndef IRPSWLMODULATION_H
#define IRPSWLMODULATION_H

#include "RPSWindLabsimuData.h"

class IrpsWLModulation
{
public:
    virtual ~IrpsWLModulation() {};

	virtual void ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual void ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

	virtual void ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};

#endif  // IRPSWLMODULATION_H
