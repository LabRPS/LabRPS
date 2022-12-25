
#include "IrpsWLRandomness.h"

class CRPSRandomPhasesFromFile : public IrpsWLRandomness
{
public:
	bool GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	bool ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	// Read random phase angle from file
	int ReadPhaseAngleFromFile(const CRPSWindLabsimuData &Data, QString strFilePath, mat &dRandomValueArray, QStringList &strInformation);

	bool GetFilePathButton();
};

