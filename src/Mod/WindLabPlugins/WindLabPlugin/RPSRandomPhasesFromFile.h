
#ifndef WINDLAB_PLUGIN_RANDOMNESSFROMFILE_H
#define WINDLAB_PLUGIN_RANDOMNESSFROMFILE_H

#include <Mod/WindLabAPI/App/IrpsWLRandomness.h>

namespace WindLabAPI { class WindLabSimuData; }

class QStringList;

namespace WindLab {

class CRPSRandomPhasesFromFile : public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSRandomPhasesFromFile);

public:

	CRPSRandomPhasesFromFile();

	~CRPSRandomPhasesFromFile() {};

	bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray);

	bool ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue);

	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	// Read random phase angle from file
	int ReadPhaseAngleFromFile(const WindLabAPI::WindLabSimuData& Data, QString strFilePath, mat &dRandomValueArray);

	bool GetFilePathButton();

public:
    App::PropertyString WorkingDirectory;

};

}

#endif  // WINDLAB_PLUGIN_RANDOMNESSFROMFILE_H