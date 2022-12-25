
#include "IrpsWLRandomness.h"

class CRPSUniformRandomPhases : public IrpsWLRandomness
{
public:

	bool GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	bool ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation);
};

