#pragma once
#include "IrpsWLRandomness.h"

class CRPSRandomPhasesFromFile : public IrpsWLRandomness
{
public:
	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	////Generate a random const double &precision value between dMin and dMax
	void GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	void ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation);

	// Read random phase angle from file
	int ReadPhaseAngleFromFile(const CRPSWindLabsimuData &Data, QString strFilePath, mat &dRandomValueArray);

	void GetFilePathButton();
};

