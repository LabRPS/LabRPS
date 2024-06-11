

#include "ThreeParaModulation.h"
#include <Mod/WindLabTools/App/modulation/ThreeParametersModulation.h>
#include "Widgets/DlgThreeParaModulation.h"
#include <Gui/Control.h>

	
using namespace WindLab;

PROPERTY_SOURCE(WindLab::CThreeParaModulation, WindLabAPI::WindLabFeatureModulation)

 CThreeParaModulation::CThreeParaModulation()
 {
    ADD_PROPERTY_TYPE(Alpha, (4.98), "The three Parameters", App::Prop_None, "The alpha coefficient");
    ADD_PROPERTY_TYPE(Betta, (3.00), "The three Parameters", App::Prop_None, "The beta coefficient");
    ADD_PROPERTY_TYPE(Lambda, (0.003), "The three Parameters", App::Prop_None, "The lambda coefficient");
 }

bool CThreeParaModulation::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    WindLabGui::DlgThreeParaModulationEdit* dlg = new WindLabGui::DlgThreeParaModulationEdit(Alpha, Betta, Lambda, Data.modulationFunction);
	Gui::Control().showDialog(dlg);
    return true;
}

bool CThreeParaModulation::ComputeModulationValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue)
{
    WindLabTools::ThreeParametersModulation threeParametersModulation;

    dValue = threeParametersModulation.computeModulation(Alpha.getValue(), Betta.getValue(), Lambda.getValue(), dTime);

	return true;
}


bool CThreeParaModulation::ComputeModulationVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector)
{
    WindLabTools::ThreeParametersModulation threeParametersModulation;

	//  Maximum value of modulation function
	double max = 0.0;
	//double 	dTime;

	// For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double dTime = Data.minTime.getValue() + Data.timeIncrement.getValue() * k;
		dVarVector(k) = dTime;
		// compute approximate buffeting force 
        dValVector(k) = threeParametersModulation.computeModulation(Alpha.getValue(), Betta.getValue(), Lambda.getValue(), dTime);

		// Max
		if (dValVector(k) > max)
		{
			max = dValVector(k);
		}
	}

	// For each time increment
	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		// Normalizing the modulation function 
		dValVector(k) /= max;
	}

	return true;

}

bool CThreeParaModulation::ComputeModulationVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector)
{
    WindLabTools::ThreeParametersModulation threeParametersModulation;

    //  Maximum value of modulation function
    double max = 0.0;
    //const double dTime = Data.minTime.getValue() + Data.timeIncrement.getValue() * Data.timeIndex.getValue();
    const double dModValue = threeParametersModulation.computeModulation(dTime, Alpha.getValue(), Betta.getValue(), Lambda.getValue());

    // For each time increment
    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        // compute approximate buffeting force
        dValVector(k) = dModValue;

        // Max
        if (dValVector(k) > max)
        {
            max = dValVector(k);
        }
    }

    // For each time increment
    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        // Normalizing the modulation function
        dValVector(k) /= max;
    }

	return true;
}
