#ifndef IRPSWLCORRELATION_H
#define IRPSWLCORRELATION_H

#include "RPSWindLabsimuData.h"

class IrpsWLCorrelation
{
public:
    virtual ~IrpsWLCorrelation() {};
	
	virtual void ComputeCrossCorrelationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual void ComputeCrossCorrelationVectorT(const CRPSWindLabsimuData &Data,  vec &dVarVector, vec &dValVector, QStringList &strInformation) = 0;
	
	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;


};

#endif  // IRPSWLCORRELATION_H
