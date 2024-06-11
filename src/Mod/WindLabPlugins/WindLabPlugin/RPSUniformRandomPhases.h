
#ifndef WINDLAB_PLUGIN_UNIFORMRANDOMNESS_H
#define WINDLAB_PLUGIN_UNIFORMRANDOMNESS_H

#include <Mod/WindLabAPI/App/IrpsWLRandomness.h>

namespace WindLabAPI { class WindLabSimuData; }

class QStringList;

namespace WindLab {

class CRPSUniformRandomPhases : public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSUniformRandomPhases);

public:

	CRPSUniformRandomPhases();

	~CRPSUniformRandomPhases() {};

	bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray);

	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	bool ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue);

public:
    App::PropertyFloat MinimumValue;
    App::PropertyFloat MaximumValue;
};

}

#endif  // WINDLAB_PLUGIN_UNIFORMRANDOMNESS_H