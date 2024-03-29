#ifndef IRPSSLCOHERENCE_H
#define IRPSSLCOHERENCE_H

#include "RPSSeismicLabsimuData.h"

class IrpsSLCoherence 
{
public:
    virtual ~IrpsSLCoherence() {};

	virtual void ComputeCrossCoherenceVectorF(const CRPSSeismicLabsimuData &Data, vec &dCohVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossCoherenceMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCoherenceCubePPF(const CRPSSeismicLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation) = 0;

	virtual void ComputeCoherenceValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;
};

#endif  // IRPSSLCOHERENCE_H
