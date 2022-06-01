#pragma once
#include "RPSWindLabsimuData.h"

class IrpsWLCorrelation
{
public:

	virtual void ComputeCrossCorrelationVectorT(const CRPSWindLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationVectorP(const CRPSWindLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationMatrixPP(const CRPSWindLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationCubePPT(const CRPSWindLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation) = 0;
	
	virtual void ComputeCrossCorrelationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;


};
