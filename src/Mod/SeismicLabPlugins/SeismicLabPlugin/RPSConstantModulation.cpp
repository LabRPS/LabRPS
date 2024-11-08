

#include "RPSConstantModulation.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/modulation/ConstantModulation.h>
#include "Widgets/DlgConstantModulation.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSConstantModulation, SeismicLabAPI::SeismicLabFeatureModulation)

CRPSConstantModulation::CRPSConstantModulation()
{
   ADD_PROPERTY_TYPE(ConstantModulationValue, (1), "Parameters", App::Prop_None, "The constant modulation value.");
}

bool CRPSConstantModulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double& dTime, double& dValue)
{
   SeismicLabTools::ConstantModulation constantModulation;
   dValue = constantModulation.computeModulation(dTime, ConstantModulationValue.getValue());
   return true;
}
bool CRPSConstantModulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double& dTime, vec& dVarVector, vec& dValVector)
{
   SeismicLabTools::ConstantModulation constantModulation;
    const double modulationValue = constantModulation.computeModulation(dTime, ConstantModulationValue.getValue());
    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = modulationValue;
    }

	return true;
}

bool CRPSConstantModulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, vec& dVarVector, vec& dValVector)
{
    SeismicLabTools::ConstantModulation constantModulation;

	 //For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double 	dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;
        dVarVector(k) = dTime;
		dValVector(k) = constantModulation.computeModulation(dTime, ConstantModulationValue.getValue());
	}

	return true;
}

    //Initial setting
bool CRPSConstantModulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	// the input diolag
    SeismicLabGui::DlgConstantModulationEdit* dlg = new SeismicLabGui::DlgConstantModulationEdit(ConstantModulationValue, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}
