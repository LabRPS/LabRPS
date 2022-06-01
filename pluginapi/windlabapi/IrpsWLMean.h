#pragma once
#include "RPSWindLabsimuData.h"
class IrpsWLMean
{
public:

virtual void ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation) = 0;

virtual void ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation) = 0;

virtual void ComputeMeanWindSpeedMatrixTP(const CRPSWindLabsimuData &Data, mat &dMeanSpeedMatrix, QStringList &strInformation) = 0;

virtual void ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation) = 0;

virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;

};
