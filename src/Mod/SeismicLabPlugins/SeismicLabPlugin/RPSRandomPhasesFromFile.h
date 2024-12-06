
#ifndef SEISMICLAB_PLUGIN_RANDOMNESSFROMFILE_H
#define SEISMICLAB_PLUGIN_RANDOMNESSFROMFILE_H

#include <Mod/SeismicLabAPI/App/IrpsSLRandomness.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

class QStringList;

namespace SeismicLab {

class CRPSRandomPhasesFromFile : public SeismicLabAPI::IrpsSLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSRandomPhasesFromFile);

public:

	CRPSRandomPhasesFromFile();

	~CRPSRandomPhasesFromFile() {};

	bool GenerateRandomCubeFPS(const SeismicLabAPI::SeismicLabSimulationData &Data, cube &dRandomValueCube);

	bool GenerateRandomMatrixFP(const SeismicLabAPI::SeismicLabSimulationData& Data, mat &dRandomValueArray);

	bool ComputeRandomValue(const SeismicLabAPI::SeismicLabSimulationData& Data, double &dValue);

	bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

	// Read random phase angle from file
	int ReadPhaseAngleFromFile(const SeismicLabAPI::SeismicLabSimulationData& Data, QString strFilePath, mat &dRandomValueArray);

	bool GetFilePathButton();

public:
    App::PropertyString WorkingDirectory;

};

}

#endif  // SEISMICLAB_PLUGIN_RANDOMNESSFROMFILE_H