
#ifndef SEALAB_PLUGIN_RANDOMNESSFROMFILE_H
#define SEALAB_PLUGIN_RANDOMNESSFROMFILE_H

#include <Mod/SeaLabAPI/App/IrpsSeLRandomness.h>

namespace SeaLabAPI { class SeaLabSimulationData; }

class QStringList;

namespace SeaLab {

class CRPSRandomPhasesFromFile : public SeaLabAPI::IrpsSeLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSRandomPhasesFromFile);

public:

	CRPSRandomPhasesFromFile();

	~CRPSRandomPhasesFromFile() {};

	bool GenerateRandomMatrixFP(const SeaLabAPI::SeaLabSimulationData& Data, mat &dRandomValueArray);

	bool ComputeRandomValue(const SeaLabAPI::SeaLabSimulationData& Data, double &dValue);

	bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

	// Read random phase angle from file
	int ReadPhaseAngleFromFile(const SeaLabAPI::SeaLabSimulationData& Data, QString strFilePath, mat &dRandomValueArray);

	bool GetFilePathButton();

public:
    App::PropertyString WorkingDirectory;

};

}

#endif  // SEALAB_PLUGIN_RANDOMNESSFROMFILE_H