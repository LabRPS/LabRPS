#pragma once
#include "RPSSeaLabsimuData.h"

class IrpsSeLCorrelation
{
public:

    virtual ~IrpsSeLCorrelation() {};

	virtual void ComputeCrossCorrelationVectorT(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationVectorP(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationCubePPT(const CRPSSeaLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;

};
