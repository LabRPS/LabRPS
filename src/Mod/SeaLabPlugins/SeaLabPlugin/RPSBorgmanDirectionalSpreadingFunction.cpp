

#include "RPSBorgmanDirectionalSpreadingFunction.h"
#include <Mod/SeaLabAPI/App/RPSSeaLabFramework.h>
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/BorgmanDirectionalSpreadingFunction.h>
#include <Base/Console.h>

using namespace SeaLab;
using namespace SeaLabAPI;

PROPERTY_SOURCE(SeaLab::CRPSBorgmanDirectionalSpreadingFunction, SeaLabAPI::SeaLabFeatureDirectionalSpreadingFunction)

CRPSBorgmanDirectionalSpreadingFunction::CRPSBorgmanDirectionalSpreadingFunction()
{
   ADD_PROPERTY_TYPE(AngleOfPropagationOfPredominantWaveEnergy, (0.00), "Parameters", App::Prop_None, "The  angle of propagation of predominant wave energy.");
   ADD_PROPERTY_TYPE(PositiveConstant, (1.00), "Parameters", App::Prop_None, "A positive constant.");
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeaLab#Borgman_Directional_Spreading_Function");

}

bool CRPSBorgmanDirectionalSpreadingFunction::ComputeDirectionalSpreadingFunctionValue(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d& location, const double& dfrequency, const double& dDirection, double& dValue)
{
  SeaLabTools::BorgmanDirectionalSpreadingFunction directionalSpreadingFunction;
  dValue = directionalSpreadingFunction.computeSpreadingFunction(dDirection, AngleOfPropagationOfPredominantWaveEnergy.getQuantityValue().getValueAs(Base::Quantity::Radian), PositiveConstant.getValue());
  return true;
}
    
bool CRPSBorgmanDirectionalSpreadingFunction::ComputeDirectionalSpreadingFunctionVectorF(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d& location, const double& dDirection, vec& dVarVector, vec& dValVector)
{
    bool returnResult = true;
    
    returnResult = CRPSSeaLabFramework::ComputeFrequenciesVectorF(Data, location, dVarVector);
    
    if (!returnResult)
    {
        Base::Console().Warning("The computation of frequency vector has failed.\n");

        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeDirectionalSpreadingFunctionValue(Data, location, dVarVector(loop), dDirection, dValVector(loop));
    }

     return returnResult;
}

bool CRPSBorgmanDirectionalSpreadingFunction::ComputeDirectionalSpreadingFunctionVectorP(const SeaLabAPI::SeaLabSimulationData& Data, const double& dfrequency, const double& dDirection, vec& dVarVector, vec& dValVector)
{
	mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

    bool returnResult = CRPSSeaLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

    if(!returnResult)
    {
        Base::Console().Error("The computation of the location coordinates matrix has failed.\n");
        
        return false;
    }
    
    Base::Vector3d location(0, 0, 0);

    for (int loop = 0; loop < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
	{
       location = Base::Vector3d(dLocCoord(loop, 1), dLocCoord(loop, 2), dLocCoord(loop, 3));
		
       dVarVector(loop) = loop+1;
       
       returnResult = ComputeDirectionalSpreadingFunctionValue(Data, location, dfrequency, dDirection, dValVector(loop));
	}

    return true;
}

bool CRPSBorgmanDirectionalSpreadingFunction::ComputeDirectionalSpreadingFunctionVectorD(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d& location, const double& dfrequency, vec& dVarVector, vec& dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfDirectionIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minDirection.getQuantityValue().getValueAs(Base::Quantity::Radian) + loop * Data.directionIncrement.getQuantityValue().getValueAs(Base::Quantity::Radian);
        returnResult = ComputeDirectionalSpreadingFunctionValue(Data, location, dfrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}

bool CRPSBorgmanDirectionalSpreadingFunction::OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data)
{
    return true;
}
