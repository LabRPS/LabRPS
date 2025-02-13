

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
    this->IsUniformModulationFeature.setValue(true);
    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Bogdanoff_Goldberg_Bernard_Modulation_Function");

}

bool CRPSBogdanoffGoldbergBernardModulation::ComputeModulationValue(const SeismicLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, const double &dTime, double &dValue)
{
   SeismicLabTools::BogdanoffGoldbergBernardModulation bogdanoffGoldbergBernardModulation;
   dValue = bogdanoffGoldbergBernardModulation.computeModulation(dTime, CoefficientOne.getValue(), CoefficientTwo.getValue());
   return true;
}
bool CRPSBogdanoffGoldbergBernardModulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double &dFrequency, const double& dTime, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;    
	for (int k = 0; k < Data.numberOfSpatialPosition.getValue() && returnResult; k++)
    {
		dVarVector(k) = k + 1;	
        returnResult = ComputeModulationValue(Data, Base::Vector3d(0,0,0), dFrequency, dTime, dValVector(k));
    }

	return true;
}

bool CRPSBogdanoffGoldbergBernardModulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;
    for (int k = 0; k < Data.numberOfTimeIncrements.getValue() && returnResult; k++)
	{
		dVarVector(k) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;;	
        returnResult = ComputeModulationValue(Data, location, dFrequency, dVarVector(k), dValVector(k));
	}
	return true;
}

bool CRPSBogdanoffGoldbergBernardModulation::ComputeModulationVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    
    returnResult = CRPSSeismicLabFramework::ComputeFrequenciesVectorF(Data, location, dVarVector);
    
    if (!returnResult)
    {
        Base::Console().Warning("The computation of frequency vector  has failed.\n");

        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeModulationValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}

bool CRPSBogdanoffGoldbergBernardModulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgBogdanoffGoldbergBernardModulationEdit* dlg = new SeismicLabGui::DlgBogdanoffGoldbergBernardModulationEdit(CoefficientOne, CoefficientTwo, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}
