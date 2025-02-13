

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
   this->IsUniformModulationFeature.setValue(true);
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Saragoni_and_Hart_Modulation_Function");

}


bool CRPSSaragoniHart1974Modulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, const double& dTime, double& dValue)
{
   SeismicLabTools::SaragoniHart1974Modulation saragoniHart1974Modulation;
   dValue = saragoniHart1974Modulation.computeModulation(dTime, AlphaOne.getValue(), AlphaTwo.getValue(), AlphaThree.getValue());
   return true;
}
bool CRPSSaragoniHart1974Modulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double &dFrequency, const double& dTime, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;    
	for (int k = 0; k < Data.numberOfSpatialPosition.getValue() && returnResult; k++)
    {
		dVarVector(k) = k + 1;	
        returnResult = ComputeModulationValue(Data, Base::Vector3d(0,0,0), dFrequency, dTime, dValVector(k));
    }

	return true;
}

bool CRPSSaragoniHart1974Modulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;
    for (int k = 0; k < Data.numberOfTimeIncrements.getValue() && returnResult; k++)
	{
		dVarVector(k) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;;	
        returnResult = ComputeModulationValue(Data, location, dFrequency, dVarVector(k), dValVector(k));
	}
	return true;
}

bool CRPSSaragoniHart1974Modulation::ComputeModulationVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector)
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

bool CRPSSaragoniHart1974Modulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgSaragoniHart1974ModulationEdit* dlg = new SeismicLabGui::DlgSaragoniHart1974ModulationEdit(AlphaOne, AlphaTwo, AlphaThree, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}

