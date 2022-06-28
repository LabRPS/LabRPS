#pragma once
#include "IrpsWLRandomness.h"

class CRPSRandomPhasesFromFile : public IrpsWLRandomness
{
public:
	void GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	void ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	// Read random phase angle from file
	int ReadPhaseAngleFromFile(const CRPSWindLabsimuData &Data, QString strFilePath, mat &dRandomValueArray, QStringList &strInformation);

	void GetFilePathButton();
};

