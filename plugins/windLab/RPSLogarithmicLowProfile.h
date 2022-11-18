
#include "IrpsWLMean.h"


class CRPSLogarithmicLowProfile : public IrpsWLMean
{
public:
	~CRPSLogarithmicLowProfile() {};

    void ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation);

    void ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation);

    bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

