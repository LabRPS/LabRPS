#pragma once
#include "IrpsWLMean.h";


class CRPSLogarithmicLowProfile : public IrpsWLMean
{
public:
	~CRPSLogarithmicLowProfile() {};

	void ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation);

	void ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation);

	void ComputeMeanWindSpeedMatrixTP(const CRPSWindLabsimuData &Data, mat &dMeanSpeedMatrix, QStringList &strInformation);

	void ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation);

	//Initial setting
	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	
};

