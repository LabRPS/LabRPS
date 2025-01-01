

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
   this->IsUniformModulationFeature.setValue(true);

}

bool CRPSConstantModulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, const double& dTime, double& dValue)
{
   SeismicLabTools::ConstantModulation constantModulation;
   dValue = constantModulation.computeModulation(dTime, ConstantModulationValue.getValue());
   return true;
}
bool CRPSConstantModulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double &dFrequency, const double& dTime, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;    
	for (int k = 0; k < Data.numberOfSpatialPosition.getValue() && returnResult; k++)
    {
		dVarVector(k) = k + 1;	
        returnResult = ComputeModulationValue(Data, Base::Vector3d(0,0,0), dFrequency, dTime, dValVector(k));
    }

	return true;
}

bool CRPSConstantModulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;
    for (int k = 0; k < Data.numberOfTimeIncrements.getValue() && returnResult; k++)
	{
		dVarVector(k) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;;	
        returnResult = ComputeModulationValue(Data, location, dFrequency, dVarVector(k), dValVector(k));
	}
	return true;
}

bool CRPSConstantModulation::ComputeModulationVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector)
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

    //Initial setting
bool CRPSConstantModulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	// the input diolag
    SeismicLabGui::DlgConstantModulationEdit* dlg = new SeismicLabGui::DlgConstantModulationEdit(ConstantModulationValue, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}
