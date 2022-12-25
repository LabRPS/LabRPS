#ifndef IRPSWLWAVEPASSAGEEFFECT_H
#define IRPSWLWAVEPASSAGEEFFECT_H

#include "RPSWindLabsimuData.h"

class IrpsWLWavePassageEffect
{
public:

    virtual ~IrpsWLWavePassageEffect() {};

    virtual bool ComputeWavePassageEffectVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, cx_vec &cValVector, QStringList &strInformation) = 0;

    virtual bool ComputeWavePassageEffectVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, cx_vec &cValVector, QStringList &strInformation) = 0;

    virtual bool ComputeWavePassageEffectMatrixPP(const CRPSWindLabsimuData &Data, cx_mat &cMatrix, QStringList &strInformation) = 0;

    virtual bool ComputeWavePassageEffectValue(const CRPSWindLabsimuData &Data, double &dRValue, double &dIValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSWLWAVEPASSAGEEFFECT_H
