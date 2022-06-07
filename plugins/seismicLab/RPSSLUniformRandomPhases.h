
#include "IrpsSLRandomness.h"


class CRPSSLUniformRandomPhases : public IrpsSLRandomness
{
public:
	void GenerateRandomArrayFP(const CRPSSeismicLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	void ComputeRandomValue(const CRPSSeismicLabsimuData &Data, double &dValue, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation);

};

