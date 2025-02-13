

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
   this->IsUniformModulationFeature.setValue(true);
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Box_Car_Modulation_Function");

}


bool CRPSBoxCarModulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, const double& dTime, double& dValue)
{
   SeismicLabTools::BoxCarModulation boxCarModulation;
   dValue = boxCarModulation.computeModulation(dTime, ScalingFactor.getValue(), StrongMotionDuration.getQuantityValue().getValueAs(Base::Quantity::Second));
   return true;
}
bool CRPSBoxCarModulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double &dFrequency, const double& dTime, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;    
	for (int k = 0; k < Data.numberOfSpatialPosition.getValue() && returnResult; k++)
    {
		dVarVector(k) = k + 1;	
        returnResult = ComputeModulationValue(Data, Base::Vector3d(0,0,0), dFrequency, dTime, dValVector(k));
    }

	return true;
}

bool CRPSBoxCarModulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;
    for (int k = 0; k < Data.numberOfTimeIncrements.getValue() && returnResult; k++)
	{
		dVarVector(k) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;;	
        returnResult = ComputeModulationValue(Data, location, dFrequency, dVarVector(k), dValVector(k));
	}
	return true;
}

bool CRPSBoxCarModulation::ComputeModulationVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector)
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

bool CRPSBoxCarModulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgBoxCarModulationEdit* dlg = new SeismicLabGui::DlgBoxCarModulationEdit(ScalingFactor, StrongMotionDuration, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}

