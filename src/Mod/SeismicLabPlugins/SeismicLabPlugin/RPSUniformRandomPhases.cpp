
#include "RPSUniformRandomPhases.h"
#include <Mod/GeneralTools/App/UniformRandomPhaseMatrixGenerator.h>
#include "Widgets/DlgUniformRandomPhases.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSUniformRandomPhases, SeismicLabAPI::SeismicLabFeatureRandomness)


CRPSUniformRandomPhases::CRPSUniformRandomPhases()
{
    ADD_PROPERTY_TYPE(MinimumValue, (0.0), "Parameters", App::Prop_None, "The minimum value that can be generated");
    ADD_PROPERTY_TYPE(MaximumValue, (6.28), "Parameters", App::Prop_None, "The maximum value that can be generated");
}

bool CRPSUniformRandomPhases::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	SeismicLabGui::DlgUniformRandomPhasesEdit* dlg = new SeismicLabGui::DlgUniformRandomPhasesEdit(MinimumValue, MaximumValue, Data.randomnessProvider);
	Gui::Control().showDialog(dlg);
    return true;
}

bool CRPSUniformRandomPhases::GenerateRandomMatrixFP(const SeismicLabAPI::SeismicLabSimulationData& Data, mat &dRandomValueArray)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseMatrix(dRandomValueArray, MinimumValue.getValue(), MaximumValue.getValue());
    return true;
}

bool CRPSUniformRandomPhases::ComputeRandomValue(const SeismicLabAPI::SeismicLabSimulationData& Data, double &dValue)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseValue(dValue, MinimumValue.getValue(), MaximumValue.getValue());
    return true;
}
