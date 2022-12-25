
#include "IrpsWLMean.h"


class CRPSWLPowerLowProfile : public IrpsWLMean
{
public:
	~CRPSWLPowerLowProfile() {};

    bool ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation);

    bool ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    bool ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

