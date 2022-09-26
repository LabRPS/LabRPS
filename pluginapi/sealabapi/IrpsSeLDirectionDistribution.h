#ifndef IRPSSELDIRECTIONDISTRIBUTION_H
#define IRPSSELDIRECTIONDISTRIBUTION_H
#include "RPSSeaLabsimuData.h"
class IrpsSeLDirectionDistribution
{
public:

    virtual ~IrpsSeLDirectionDistribution() {};

	virtual void ComputeDirectionsVectorD(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation) = 0;

	virtual void ComputeDirectionsVectorF(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation) = 0;

	virtual void ComputeDirectionsVectorT(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation) = 0;

	virtual void ComputeDirectionsMatrixDP(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDirectionsMatrixTD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDirectionsMatrixFD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation) = 0;

	virtual void ComputeDirectionsCubeFTD(const CRPSSeaLabsimuData &Data, cube &dDirectionCube, QStringList &strInformation) = 0;

	virtual void ComputeDirectionsValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;
};
#endif  // IRPSSELDIRECTIONDISTRIBUTION_H
