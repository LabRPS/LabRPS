#pragma once
#include "IrpsSeLRandomness.h"
#include <QStringList>



class CRPSSLRandomPhasesFromFile : public IrpsSeLRandomness
{
public:
	void GenerateRandomArrayFP(const CRPSSeaLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	void ComputeRandomValue(const CRPSSeaLabsimuData &Data, double &dValue, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);

	// Read random phase angle from file
	int ReadPhaseAngleFromFile(const CRPSSeaLabsimuData &Data, QString strFilePath, mat &dRandomValueArray, QStringList &strInformation);

	void GetFilePathButton();
};

