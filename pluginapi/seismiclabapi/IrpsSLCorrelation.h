#ifndef IRPSSLCORRELATION_H
#define IRPSSLCORRELATION_H

#include "RPSSeismicLabsimuData.h"

class IrpsSLCorrelation
{
public:
    virtual ~IrpsSLCorrelation() {};

	virtual void ComputeCrossCorrelationVectorT(const CRPSSeismicLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationVectorP(const CRPSSeismicLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationCubePPT(const CRPSSeismicLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;

};
#endif  // IRPSSLCORRELATION_H
