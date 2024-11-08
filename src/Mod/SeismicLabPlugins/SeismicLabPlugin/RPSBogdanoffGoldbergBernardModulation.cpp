

#include "RPSBogdanoffGoldbergBernardModulation.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/modulation/BogdanoffGoldbergBernardModulation.h>
#include "Widgets/DlgBogdanoffGoldbergBernardModulation.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSBogdanoffGoldbergBernardModulation, SeismicLabAPI::SeismicLabFeatureModulation)

CRPSBogdanoffGoldbergBernardModulation::CRPSBogdanoffGoldbergBernardModulation()
{
    ADD_PROPERTY_TYPE(CoefficientOne, (0.68), "Parameters", App::Prop_None, "The coefficient 1.");
    ADD_PROPERTY_TYPE(CoefficientTwo, (1.0/4.0), "Parameters", App::Prop_None, "The coefficient 2.");
}

bool CRPSBogdanoffGoldbergBernardModulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double& dTime, double& dValue)
{
    SeismicLabTools::BogdanoffGoldbergBernardModulation bogdanoffGoldbergBernardModulation;
   dValue = bogdanoffGoldbergBernardModulation.computeModulation(dTime, CoefficientOne.getValue(), CoefficientTwo.getValue());
   return true;
}
bool CRPSBogdanoffGoldbergBernardModulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double& dTime, vec& dVarVector, vec& dValVector)
{
   SeismicLabTools::BogdanoffGoldbergBernardModulation bogdanoffGoldbergBernardModulation;
   const double modulationValue = bogdanoffGoldbergBernardModulation.computeModulation(dTime, CoefficientOne.getValue(), CoefficientTwo.getValue());

    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = modulationValue;
    }

	return true;
}

bool CRPSBogdanoffGoldbergBernardModulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, vec& dVarVector, vec& dValVector)
{
    SeismicLabTools::BogdanoffGoldbergBernardModulation bogdanoffGoldbergBernardModulation;

	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double 	dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;
        dVarVector(k) = dTime;
		dValVector(k) = bogdanoffGoldbergBernardModulation.computeModulation(dTime, CoefficientOne.getValue(), CoefficientTwo.getValue());
	}

	return true;
}

bool CRPSBogdanoffGoldbergBernardModulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgBogdanoffGoldbergBernardModulationEdit* dlg = new SeismicLabGui::DlgBogdanoffGoldbergBernardModulationEdit(CoefficientOne, CoefficientTwo, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}
