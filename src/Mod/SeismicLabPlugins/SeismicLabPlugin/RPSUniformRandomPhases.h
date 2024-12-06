
#ifndef SEISMICLAB_PLUGIN_UNIFORMRANDOMNESS_H
#define SEISMICLAB_PLUGIN_UNIFORMRANDOMNESS_H

#include <Mod/SeismicLabAPI/App/IrpsSLRandomness.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

class QStringList;

namespace SeismicLab {

class CRPSUniformRandomPhases : public SeismicLabAPI::IrpsSLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSUniformRandomPhases);

public:

	CRPSUniformRandomPhases();

	~CRPSUniformRandomPhases() {};

	bool GenerateRandomCubeFPS(const SeismicLabAPI::SeismicLabSimulationData &Data, cube &dRandomValueCube);

	bool GenerateRandomMatrixFP(const SeismicLabAPI::SeismicLabSimulationData& Data, mat &dRandomValueArray);

	bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

	bool ComputeRandomValue(const SeismicLabAPI::SeismicLabSimulationData& Data, double &dValue);

public:
    App::PropertyFloat MinimumValue;
    App::PropertyFloat MaximumValue;
};

}

#endif  // SEISMICLAB_PLUGIN_UNIFORMRANDOMNESS_H