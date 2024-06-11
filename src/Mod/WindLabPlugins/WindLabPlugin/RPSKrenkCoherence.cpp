

#include "RPSKrenkCoherence.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLabAPI/App/WindLabSimuData.h>
#include <Mod/WindLabTools/App/coherence/KrenkCoherence.h>
#include "Widgets/DlgKrenkCoherence.h"
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace WindLab;

PROPERTY_SOURCE(WindLab::RPSKrenkCoherence, WindLabAPI::WindLabFeatureCoherence)

RPSKrenkCoherence::RPSKrenkCoherence()
{
   ADD_PROPERTY_TYPE(IntegralLengthScale, (150.0), "Parameters", App::Prop_None, "The integral length scale");

}

bool RPSKrenkCoherence::ComputeCrossCoherenceValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
	double dMeanSpeed1 = 0.0;
	double dMeanSpeed2 = 0.0;
   
    WindLabTools::KrenkCoherence krenkCoherence;

    WindLabAPI::CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationJ, dTime, dMeanSpeed1);
    WindLabAPI::CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationK, dTime, dMeanSpeed2);

    dValue = krenkCoherence.computeCoherenceValue(locationJ.x, locationJ.y, locationJ.z, locationK.x, locationK.y, locationK.z, dFrequency, dMeanSpeed1, dMeanSpeed2, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre));
    
	return true;
}

bool RPSKrenkCoherence::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    // the input diolag
    WindLabGui::DlgKrenkCoherenceEdit* dlg = new WindLabGui::DlgKrenkCoherenceEdit(IntegralLengthScale, Data.coherenceFunction);
	Gui::Control().showDialog(dlg);

    return true;
}

bool RPSKrenkCoherence::ComputeCrossCoherenceVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	// The coherence value
	std::complex<double> dCoherenceValue = 0.0;
    bool returnResult = true;

    WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);

	for (int loop3 = 0; loop3 < Data.numberOfFrequency.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop3++)
	{
        returnResult = ComputeCrossCoherenceValue(Data, locationJ, locationK, dVarVector(loop3), dTime, dCoherenceValue);

		dValVector(loop3) = dCoherenceValue;
	}

	return true;
}

bool RPSKrenkCoherence::ComputeCrossCoherenceVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    // The coherence value
    std::complex<double> dCoherenceValue = 0.0;
    bool returnResult = true;

    for (int loop3 = 0; loop3 < Data.numberOfTimeIncrements.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop3++)
    {
       dVarVector(loop3) = Data.minTime.getValue() + Data.timeIncrement.getValue() * (loop3);
                
       returnResult = ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dVarVector(loop3), dCoherenceValue);

       dValVector(loop3) = dCoherenceValue;
    }

	return true;
}

bool RPSKrenkCoherence::ComputeCrossCoherenceMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix)
{
	mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

	bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.") ;
       return false;
    }
	
	std::complex<double> coherence = 0.0;
    Base::Vector3d locationJ(0, 0, 0);
    Base::Vector3d locationK(0, 0, 0);

	for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop1++)
	{
		for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop2++)
		{
           locationJ = Base::Vector3d(dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop1, 3));
           locationK = Base::Vector3d(dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 3));

            returnResult = ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, coherence);

			dCoherenceMatrix(loop1, loop2) = coherence;
		}
	}

	return true;
}
