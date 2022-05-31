#pragma once
#include "RPSSeaLabsimuData.h"
class IrpsSeLMean
{
public:

    virtual ~IrpsSeLMean() {}

	virtual void ComputeMeanWindSpeedVectorP(const CRPSSeaLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation) = 0;

	virtual void ComputeMeanWindSpeedVectorT(const CRPSSeaLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation) = 0;

	virtual void ComputeMeanWindSpeedMatrixTP(const CRPSSeaLabsimuData &Data, mat &dMeanSpeedMatrix, QStringList &strInformation) = 0;

	virtual void ComputeMeanWindSpeedValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;

};
