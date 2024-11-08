

#include "RPSTrapezoidalModulation.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/modulation/TrapezoidalModulation.h>
#include "Widgets/DlgTrapezoidalModulation.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSTrapezoidalModulation, SeismicLabAPI::SeismicLabFeatureModulation)

CRPSTrapezoidalModulation::CRPSTrapezoidalModulation()
{
   ADD_PROPERTY_TYPE(RiseTime, (5.0), "Parameters", App::Prop_None, "This is the instant of time (in sec) corresponding to the beginning of the horizontal part of the envelope.");
   ADD_PROPERTY_TYPE(LevelTime, (15.0), "Parameters", App::Prop_None, "This is the instant of time corresponding to the beginning of the descending branch of the envelope. The Level Time should be larger than the Rise Time");
   ADD_PROPERTY_TYPE(MaxTime, (1536), "Parameters", App::Prop_None, "The Duration.");
}


bool CRPSTrapezoidalModulation::ComputeModulationValue(const SeismicLabSimulationData& Data, Base::Vector3d location, const double& dTime, double& dValue)
{
   SeismicLabTools::TrapezoidalModulation trapezoidalModulation;
   dValue = trapezoidalModulation.computeModulation(dTime, RiseTime.getQuantityValue().getValueAs(Base::Quantity::Second), LevelTime.getQuantityValue().getValueAs(Base::Quantity::Second), MaxTime.getQuantityValue().getValueAs(Base::Quantity::Second));
   return true;
}
bool CRPSTrapezoidalModulation::ComputeModulationVectorP(const SeismicLabSimulationData& Data, const double& dTime, vec& dVarVector, vec& dValVector)
{
   SeismicLabTools::TrapezoidalModulation trapezoidalModulation;
   const double modulationValue = trapezoidalModulation.computeModulation(dTime, RiseTime.getQuantityValue().getValueAs(Base::Quantity::Second), LevelTime.getQuantityValue().getValueAs(Base::Quantity::Second), MaxTime.getQuantityValue().getValueAs(Base::Quantity::Second));

    for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
    {
        dVarVector(k) = k+1;
        dValVector(k) = modulationValue;
    }

	return true;
}

bool CRPSTrapezoidalModulation::ComputeModulationVectorT(const SeismicLabSimulationData& Data, Base::Vector3d location, vec& dVarVector, vec& dValVector)
{
    SeismicLabTools::TrapezoidalModulation trapezoidalModulation;

	for (int k = 0; k < Data.numberOfTimeIncrements.getValue(); k++)
	{
		const double 	dTime = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * k;
        dVarVector(k) = dTime;
		dValVector(k) = trapezoidalModulation.computeModulation(dTime, RiseTime.getQuantityValue().getValueAs(Base::Quantity::Second), LevelTime.getQuantityValue().getValueAs(Base::Quantity::Second), MaxTime.getQuantityValue().getValueAs(Base::Quantity::Second));
	}

	return true;
}

bool CRPSTrapezoidalModulation::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgTrapezoidalModulationEdit* dlg = new SeismicLabGui::DlgTrapezoidalModulationEdit(RiseTime, LevelTime, MaxTime, Data.modulationFunction);
	Gui::Control().showDialog(dlg);

    return true;
}

