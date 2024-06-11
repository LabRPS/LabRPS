

#include "SineModulation.h"
#include <Mod/WindLabTools/App/modulation/SineModulation.h>
#include "Widgets/DlgSineModulation.h"
#include <Gui/Control.h>

using namespace WindLab;

PROPERTY_SOURCE(WindLab::CSineModulation, WindLabAPI::WindLabFeatureModulation)

CSineModulation::CSineModulation()
{
    ADD_PROPERTY_TYPE(PulseDuration, (150), "Parameters", App::Prop_None, "The pulse duration");

}

bool CSineModulation::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    WindLabGui::DlgSineModulationEdit* dlg = new WindLabGui::DlgSineModulationEdit(PulseDuration, Data.modulationFunction);
	Gui::Control().showDialog(dlg);
    return true;
}


bool CSineModulation::ComputeModulationValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
	dValue = sin(3.14*dTime / PulseDuration.getQuantityValue().getValueAs(Base::Quantity::Second));
	return true;
}

bool CSineModulation::ComputeModulationVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
	//double 	dTime;
    WindLabTools::SineModulation sineModulation;

	 //For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double dTime = Data.minTime.getValue() + Data.timeIncrement.getValue() * k;
		dVarVector(k) = dTime;	
        dValVector(k) = sineModulation.computeModulation(dTime, PulseDuration.getQuantityValue().getValueAs(Base::Quantity::Second));
	}
	return true;
}

bool CSineModulation::ComputeModulationVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    //double 	dTime;
    WindLabTools::SineModulation sineModulation;
    //const double dTime = Data.minTime.getValue() + Data.timeIncrement.getValue() * Data.timeIndex.getValue();
    const double dModValue = sineModulation.computeModulation(dTime, PulseDuration.getQuantityValue().getValueAs(Base::Quantity::Second));

     //For each time increment
    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = dModValue;
    }

	return true;
}
