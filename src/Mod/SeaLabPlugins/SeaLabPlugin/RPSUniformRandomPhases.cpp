
#include "RPSUniformRandomPhases.h"
#include <Mod/GeneralTools/App/UniformRandomPhaseMatrixGenerator.h>
#include "Widgets/DlgUniformRandomPhases.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeaLab;
using namespace SeaLabAPI;

PROPERTY_SOURCE(SeaLab::CRPSUniformRandomPhases, SeaLabAPI::SeaLabFeatureRandomness)


CRPSUniformRandomPhases::CRPSUniformRandomPhases()
{
    ADD_PROPERTY_TYPE(MinimumValue, (0.0), "Parameters", App::Prop_None, "The minimum value that can be generated");
    ADD_PROPERTY_TYPE(MaximumValue, (6.28), "Parameters", App::Prop_None, "The maximum value that can be generated");
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeaLab#Uniform_Random_Phases");

}

bool CRPSUniformRandomPhases::OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data)
{
	SeaLabGui::DlgUniformRandomPhasesEdit* dlg = new SeaLabGui::DlgUniformRandomPhasesEdit(MinimumValue, MaximumValue, Data.randomnessProvider);
	Gui::Control().showDialog(dlg);
    return true;
}

bool CRPSUniformRandomPhases::GenerateRandomCubeFPS(const SeaLabAPI::SeaLabSimulationData& Data, cube& dRandomValueCube)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseCube(dRandomValueCube, MinimumValue.getValue(), MaximumValue.getValue());
    return true;
}

bool CRPSUniformRandomPhases::GenerateRandomMatrixFP(const SeaLabAPI::SeaLabSimulationData& Data, mat &dRandomValueArray)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseMatrix(dRandomValueArray, MinimumValue.getValue(), MaximumValue.getValue());
    return true;
}

bool CRPSUniformRandomPhases::ComputeRandomValue(const SeaLabAPI::SeaLabSimulationData& Data, double &dValue)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseValue(dValue, MinimumValue.getValue(), MaximumValue.getValue());
    return true;
}
