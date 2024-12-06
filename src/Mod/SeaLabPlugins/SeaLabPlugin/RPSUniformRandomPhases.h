
#ifndef SEALAB_PLUGIN_UNIFORMRANDOMNESS_H
#define SEALAB_PLUGIN_UNIFORMRANDOMNESS_H

#include <Mod/SeaLabAPI/App/IrpsSeLRandomness.h>

namespace SeaLabAPI { class SeaLabSimulationData; }

class QStringList;

namespace SeaLab {

class CRPSUniformRandomPhases : public SeaLabAPI::IrpsSeLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSUniformRandomPhases);

public:

	CRPSUniformRandomPhases();

	~CRPSUniformRandomPhases() {};

	bool GenerateRandomCubeFPS(const SeaLabAPI::SeaLabSimulationData &Data, cube &dRandomValueCube);

	bool GenerateRandomMatrixFP(const SeaLabAPI::SeaLabSimulationData& Data, mat &dRandomValueArray);

	bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

	bool ComputeRandomValue(const SeaLabAPI::SeaLabSimulationData& Data, double &dValue);

public:
    App::PropertyFloat MinimumValue;
    App::PropertyFloat MaximumValue;
};

}

#endif  // SEALAB_PLUGIN_UNIFORMRANDOMNESS_H