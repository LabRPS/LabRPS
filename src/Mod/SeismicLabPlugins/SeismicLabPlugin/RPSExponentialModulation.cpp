

#include "RPSExponentialModulation.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/modulation/ExponentialModulation.h>
#include "Widgets/DlgExponentialModulation.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSExponentialModulation, SeismicLabAPI::SeismicLabFeatureModulation)

CRPSExponentialModulation::CRPSExponentialModulation()
{
   ADD_PROPERTY_TYPE(Alpha, (0.2), "Parameters", App::Prop_None, "The parameter alpha.");
   ADD_PROPERTY_TYPE(Beta, (0.6), "Parameters", App::Prop_None, "The parameter beta.");
   ADD_PROPERTY_TYPE(CoefficientA, (1.0), "Parameters", App::Prop_ReadOnly, "The internal coefficient A.");
}

bool CRPSExponentialModulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double& dTime, double& dValue)
{
   SeismicLabTools::ExponentialModulation exponentialModulation;
   dValue = exponentialModulation.computeModulation(dTime, Alpha.getValue(), Beta.getValue());
   double A = exponentialModulation.computeCoefficientA(Alpha.getValue(), Beta.getValue());
   CoefficientA.setValue(A);
   return true;
}
bool CRPSExponentialModulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double& dTime, vec& dVarVector, vec& dValVector)
{
   SeismicLabTools::ExponentialModulation exponentialModulation;
   const double modulationValue = exponentialModulation.computeModulation(dTime, Alpha.getValue(), Beta.getValue());
   double A = exponentialModulation.computeCoefficientA(Alpha.getValue(), Beta.getValue());
   CoefficientA.setValue(A);

    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = modulationValue;
    }

	return true;
}

bool CRPSExponentialModulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, vec& dVarVector, vec& dValVector)
{
    SeismicLabTools::ExponentialModulation exponentialModulation;

	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double 	dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;
        dVarVector(k) = dTime;
		dValVector(k) = exponentialModulation.computeModulation(dTime, Alpha.getValue(), Beta.getValue());
	}

    double A = exponentialModulation.computeCoefficientA(Alpha.getValue(), Beta.getValue());
    CoefficientA.setValue(A);
	return true;
}

bool CRPSExponentialModulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgExponentialModulationEdit* dlg = new SeismicLabGui::DlgExponentialModulationEdit(Alpha, Beta, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}
