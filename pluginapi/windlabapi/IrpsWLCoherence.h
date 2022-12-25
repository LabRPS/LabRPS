#ifndef IRPSWLCOHERENCE_H
#define IRPSWLCOHERENCE_H

#include "RPSWindLabsimuData.h"

class IrpsWLCoherence 
{
public:

    virtual ~IrpsWLCoherence() {};

    virtual bool ComputeCrossCoherenceVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeCrossCoherenceVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeCrossCoherenceMatrixPP(const CRPSWindLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation) = 0;

    virtual bool ComputeCrossCoherenceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;
};

#endif  // IRPSWLCOHERENCE_H
