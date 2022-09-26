#ifndef IRPSSELCOHERENCE_H
#define IRPSSELCOHERENCE_H

#include "RPSSeaLabsimuData.h"

class IrpsSeLCoherence 
{
public:
    virtual ~IrpsSeLCoherence() {};
	
	virtual void ComputeCrossCoherenceVectorF(const CRPSSeaLabsimuData &Data, vec &dCohVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossCoherenceMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCoherenceCubePPF(const CRPSSeaLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation) = 0;

	virtual void ComputeCoherenceValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;
};
#endif  // IRPSSELCOHERENCE_H
