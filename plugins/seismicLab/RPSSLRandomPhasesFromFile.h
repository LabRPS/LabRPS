
#include "IrpsSLRandomness.h"

class CRPSSLRandomPhasesFromFile : public IrpsSLRandomness
{
public:
	void GenerateRandomArrayFP(const CRPSSeismicLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	void ComputeRandomValue(const CRPSSeismicLabsimuData &Data, double &dValue, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation);

	// Read random phase angle from file
	int ReadPhaseAngleFromFile(const CRPSSeismicLabsimuData &Data, QString strFilePath, mat &dRandomValueArray);

	void GetFilePathButton();
};

