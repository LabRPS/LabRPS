

#include "RPSTurbulenceIntensityASCE798.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLabAPI/App/WindLabSimuData.h>
#include <Mod/WindLabTools/App/turbulenceIntensity/TurbulenceIntensity.h>
#include "Widgets/DlgTurbulenceIntensityASCE798.h"
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace WindLab;

PROPERTY_SOURCE(WindLab::RPSTurbulenceIntensityASCE798, WindLabAPI::WindLabFeatureTurbulenceIntensity)

RPSTurbulenceIntensityASCE798::RPSTurbulenceIntensityASCE798()
{
   ADD_PROPERTY_TYPE(TenMetersHighTurbulenceIntensity, (0.088), "Parameters", App::Prop_None, "The turbulence intensity at height of 10 meters");

}

bool RPSTurbulenceIntensityASCE798::ComputeTurbulenceIntensityValue(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d& location, const double& dTime, double& dValue)
{
  
    WindLabTools::TurbulenceIntensity turbulenceIntensity;
    dValue = turbulenceIntensity.computeASCETurbulenceIntensityValue(location.z, TenMetersHighTurbulenceIntensity.getValue());
    
	return true;
}

bool RPSTurbulenceIntensityASCE798::ComputeTurbulenceIntensityVectorP(const WindLabAPI::WindLabSimuData& Data, const double& dTime, vec& dVarVector, vec& dValVector)
{
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
	bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.") ;
       return false;
    }

    // The coherence value
	double intensity = 0.0;
    Base::Vector3d location(0, 0, 0);

	for (int loop = 0; loop < Data.numberOfSpatialPosition.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
	{
       location = Base::Vector3d(dLocCoord(loop, 1), dLocCoord(loop, 2), dLocCoord(loop, 3));
       returnResult = ComputeTurbulenceIntensityValue(Data, location, dTime, intensity);
       dVarVector(loop) = location.z;
	   dValVector(loop) = intensity;
	}

	return true;
}

bool RPSTurbulenceIntensityASCE798::ComputeTurbulenceIntensityVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d& location, vec& dVarVector, vec& dValVector)
{
     mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
	bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.") ;
       return false;
    }

    // The coherence value
	double intensity = 0.0;
	for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
	{
       const double time = Data.minTime.getValue() + Data.timeIncrement.getValue() * (loop);

       returnResult = ComputeTurbulenceIntensityValue(Data, location, time, intensity);
       dVarVector(loop) = time;
	   dValVector(loop) = intensity;
	}

	return true;
}

bool RPSTurbulenceIntensityASCE798::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    // the input diolag
    WindLabGui::DlgTurbulenceIntensityASCE798Edit* dlg = new WindLabGui::DlgTurbulenceIntensityASCE798Edit(TenMetersHighTurbulenceIntensity, Data.turbulenceIntensity);
	Gui::Control().showDialog(dlg);

    return true;
}