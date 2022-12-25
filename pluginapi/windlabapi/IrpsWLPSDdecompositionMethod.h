#ifndef IRPSWLPSDDECOMPOSITIONMETHOD_H
#define IRPSWLPSDDECOMPOSITIONMETHOD_H

#include "RPSWindLabsimuData.h"

class IrpsWLPSDdecompositionMethod
{
public:
    virtual ~IrpsWLPSDdecompositionMethod() {};

    virtual bool ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

    virtual bool ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;

    virtual bool ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLPSDDECOMPOSITIONMETHOD_H
