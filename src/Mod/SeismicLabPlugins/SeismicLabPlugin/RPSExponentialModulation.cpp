

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
   this->IsUniformModulationFeature.setValue(true);
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Exponential_Modulation_Function");

}

bool CRPSExponentialModulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, const double& dTime, double& dValue)
{
   SeismicLabTools::ExponentialModulation exponentialModulation;
   dValue = exponentialModulation.computeModulation(dTime, Alpha.getValue(), Beta.getValue());
   double A = exponentialModulation.computeCoefficientA(Alpha.getValue(), Beta.getValue());
   CoefficientA.setValue(A);
   return true;
}
bool CRPSExponentialModulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double &dFrequency, const double& dTime, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;    
	for (int k = 0; k < Data.numberOfSpatialPosition.getValue() && returnResult; k++)
    {
		dVarVector(k) = k + 1;	
        returnResult = ComputeModulationValue(Data, Base::Vector3d(0,0,0), dFrequency, dTime, dValVector(k));
    }

	return true;
}

bool CRPSExponentialModulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;
    for (int k = 0; k < Data.numberOfTimeIncrements.getValue() && returnResult; k++)
	{
		dVarVector(k) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;;	
        returnResult = ComputeModulationValue(Data, location, dFrequency, dVarVector(k), dValVector(k));
	}
	return true;
}

bool CRPSExponentialModulation::ComputeModulationVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector)
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

bool CRPSExponentialModulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgExponentialModulationEdit* dlg = new SeismicLabGui::DlgExponentialModulationEdit(Alpha, Beta, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}
