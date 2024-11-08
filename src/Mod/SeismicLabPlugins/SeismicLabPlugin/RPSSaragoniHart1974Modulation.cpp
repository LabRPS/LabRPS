

#include "RPSSaragoniHart1974Modulation.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/modulation/SaragoniHart1974Modulation.h>
#include "Widgets/DlgSaragoniHart1974Modulation.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSSaragoniHart1974Modulation, SeismicLabAPI::SeismicLabFeatureModulation)

CRPSSaragoniHart1974Modulation::CRPSSaragoniHart1974Modulation()
{
    ADD_PROPERTY_TYPE(AlphaOne, (0.4618), "Parameters", App::Prop_None, "The parameter 1.");
   ADD_PROPERTY_TYPE(AlphaTwo, (3.0), "Parameters", App::Prop_None, "The parameter 2.");
   ADD_PROPERTY_TYPE(AlphaThree, (0.5), "Parameters", App::Prop_None, "The parameter 3.");
}


bool CRPSSaragoniHart1974Modulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double& dTime, double& dValue)
{
   SeismicLabTools::SaragoniHart1974Modulation saragoniHart1974Modulation;
   dValue = saragoniHart1974Modulation.computeModulation(dTime, AlphaOne.getValue(), AlphaTwo.getValue(), AlphaThree.getValue());
   return true;
}
bool CRPSSaragoniHart1974Modulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double& dTime, vec& dVarVector, vec& dValVector)
{
   SeismicLabTools::SaragoniHart1974Modulation saragoniHart1974Modulation;
   const double modulationValue = saragoniHart1974Modulation.computeModulation(dTime, AlphaOne.getValue(), AlphaTwo.getValue(), AlphaThree.getValue());
   
    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = modulationValue;
    }

	return true;
}

bool CRPSSaragoniHart1974Modulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, vec& dVarVector, vec& dValVector)
{
    SeismicLabTools::SaragoniHart1974Modulation saragoniHart1974Modulation;

	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double 	dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;
        dVarVector(k) = dTime;
		dValVector(k) = saragoniHart1974Modulation.computeModulation(dTime, AlphaOne.getValue(), AlphaTwo.getValue(), AlphaThree.getValue());
	}

	return true;
}

bool CRPSSaragoniHart1974Modulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgSaragoniHart1974ModulationEdit* dlg = new SeismicLabGui::DlgSaragoniHart1974ModulationEdit(AlphaOne, AlphaTwo, AlphaThree, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}

