

#include "RPSJenningsEtAl1968Modulation.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/modulation/JenningsEtAl1968Modulation.h>
#include "Widgets/DlgJenningsEtAl1968Modulation.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSJenningsEtAl1968Modulation, SeismicLabAPI::SeismicLabFeatureModulation)

CRPSJenningsEtAl1968Modulation::CRPSJenningsEtAl1968Modulation()
{
   ADD_PROPERTY_TYPE(RiseTime, (3.00), "Parameters", App::Prop_None, "The instant of time (in sec) corresponding to the beginning of the horizontal part of the envelope.");
   ADD_PROPERTY_TYPE(LevelTime, (8.0), "Parameters", App::Prop_None, "The instant of time corresponding to the beginning of the descending branch of the envelope. The Level Time should be larger than the Rise Time.");
   ADD_PROPERTY_TYPE(Alpha, (0.2), "Parameters", App::Prop_None, "The parameter alpha.");
   ADD_PROPERTY_TYPE(Power, (2.0), "Parameters", App::Prop_None, "The power coefficient");
   this->IsUniformModulationFeature.setValue(true);
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Jennings_Modulation_Function");

}

bool CRPSJenningsEtAl1968Modulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, const double& dTime, double& dValue)
{
   SeismicLabTools::JenningsEtAl1968Modulation jenningsEtAl1968Modulation;
   dValue = jenningsEtAl1968Modulation.computeModulation(dTime, RiseTime.getQuantityValue().getValueAs(Base::Quantity::Second), LevelTime.getQuantityValue().getValueAs(Base::Quantity::Second), Alpha.getValue(), Power.getValue()) * ScaleCoefficient.getValue();
   return true;
}
bool CRPSJenningsEtAl1968Modulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double &dFrequency, const double& dTime, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;    
	for (int k = 0; k < Data.numberOfSpatialPosition.getValue() && returnResult; k++)
    {
		dVarVector(k) = k + 1;	
        returnResult = ComputeModulationValue(Data, Base::Vector3d(0,0,0), dFrequency, dTime, dValVector(k));
    }

	return true;
}

bool CRPSJenningsEtAl1968Modulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, const double &dFrequency, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;
    for (int k = 0; k < Data.numberOfTimeIncrements.getValue() && returnResult; k++)
	{
		dVarVector(k) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;;	
        returnResult = ComputeModulationValue(Data, location, dFrequency, dVarVector(k), dValVector(k));
	}
	return true;
}

bool CRPSJenningsEtAl1968Modulation::ComputeModulationVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector)
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
bool CRPSJenningsEtAl1968Modulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	// the input diolag
    SeismicLabGui::DlgJenningsEtAl1968ModulationEdit* dlg = new SeismicLabGui::DlgJenningsEtAl1968ModulationEdit(RiseTime, LevelTime, Alpha, Power, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}
