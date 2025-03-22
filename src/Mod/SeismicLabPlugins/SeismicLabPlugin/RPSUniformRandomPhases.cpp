
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
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Uniform_Random_Phases");

}

bool CRPSUniformRandomPhases::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	SeismicLabGui::DlgUniformRandomPhasesEdit* dlg = new SeismicLabGui::DlgUniformRandomPhasesEdit(MinimumValue, MaximumValue, Data.randomnessProvider);
	Gui::Control().showDialog(dlg);
    return true;
}

bool CRPSUniformRandomPhases::GenerateRandomCubeFPS(const SeismicLabAPI::SeismicLabSimulationData &Data, cube &dRandomValueCube)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseCube(dRandomValueCube, MinimumValue.getValue(), MaximumValue.getValue());
    dRandomValueCube = dRandomValueCube * ScaleCoefficient.getValue();
    return true;
}

bool CRPSUniformRandomPhases::GenerateRandomMatrixFP(const SeismicLabAPI::SeismicLabSimulationData& Data, mat &dRandomValueArray)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseMatrix(dRandomValueArray, MinimumValue.getValue(), MaximumValue.getValue());
    dRandomValueArray = dRandomValueArray * ScaleCoefficient.getValue();
    return true;
}

bool CRPSUniformRandomPhases::ComputeRandomValue(const SeismicLabAPI::SeismicLabSimulationData& Data, double &dValue)
{
    rps::General::UniformRandomPhaseMatrixGenerator uniformRandomPhaseMatrixGenerator;
    uniformRandomPhaseMatrixGenerator.generateUniformRandomPhaseValue(dValue, MinimumValue.getValue(), MaximumValue.getValue());
    dValue = dValue * ScaleCoefficient.getValue();
    return true;
}
