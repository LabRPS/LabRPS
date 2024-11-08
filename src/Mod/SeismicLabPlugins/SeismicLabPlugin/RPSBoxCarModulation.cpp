

#include "RPSBoxCarModulation.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/modulation/BoxCarModulation.h>
#include "Widgets/DlgBoxCarModulation.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSBoxCarModulation, SeismicLabAPI::SeismicLabFeatureModulation)

CRPSBoxCarModulation::CRPSBoxCarModulation()
{
   ADD_PROPERTY_TYPE(ScalingFactor, (1.0), "Parameters", App::Prop_None, "This is the scaling factor.");
   ADD_PROPERTY_TYPE(StrongMotionDuration, (15.0), "Parameters", App::Prop_None, "This is the strong motion duration of the earthquake excitation.");
}


bool CRPSBoxCarModulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double& dTime, double& dValue)
{
   SeismicLabTools::BoxCarModulation boxCarModulation;
   dValue = boxCarModulation.computeModulation(dTime, ScalingFactor.getValue(), StrongMotionDuration.getQuantityValue().getValueAs(Base::Quantity::Second));
   return true;
}
bool CRPSBoxCarModulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double& dTime, vec& dVarVector, vec& dValVector)
{
   SeismicLabTools::BoxCarModulation boxCarModulation;
   const double modulationValue = boxCarModulation.computeModulation(dTime, ScalingFactor.getValue(), StrongMotionDuration.getQuantityValue().getValueAs(Base::Quantity::Second));

    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = modulationValue;
    }

	return true;
}

bool CRPSBoxCarModulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, vec& dVarVector, vec& dValVector)
{
    SeismicLabTools::BoxCarModulation boxCarModulation;

	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;
        dVarVector(k) = dTime;
		dValVector(k) = boxCarModulation.computeModulation(dTime, ScalingFactor.getValue(), StrongMotionDuration.getQuantityValue().getValueAs(Base::Quantity::Second));
	}

	return true;
}

bool CRPSBoxCarModulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgBoxCarModulationEdit* dlg = new SeismicLabGui::DlgBoxCarModulationEdit(ScalingFactor, StrongMotionDuration, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}

