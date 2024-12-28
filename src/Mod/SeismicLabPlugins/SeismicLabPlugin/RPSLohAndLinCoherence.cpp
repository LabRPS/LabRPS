

#include "RPSLohAndLinCoherence.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/coherence/LohAndLinCoherence.h>
#include "Widgets/DlgLohAndLinCoherence.h"
#include <Base/Console.h>
#include <Gui/Control.h>
#include <App/Application.h>
#include <App/Document.h>

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSLohAndLinCoherence, SeismicLabAPI::SeismicLabFeatureCoherence)

CRPSLohAndLinCoherence::CRPSLohAndLinCoherence()
{
   ADD_PROPERTY_TYPE(ParameterAlpha, (0.02), "Parameters", App::Prop_None, "The natural frequency of the ground.");
   ADD_PROPERTY_TYPE(ParameterB, (0.005), "Parameters", App::Prop_None, "The damping ratio of the ground.");
}

bool CRPSLohAndLinCoherence::ComputeCrossCoherenceVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    // The coherence value
	std::complex<double> dCoherenceValue = 0.0;
    bool returnResult = true;

    SeismicLabAPI::CRPSSeismicLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);

	for (int loop3 = 0; loop3 < Data.numberOfFrequency.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop3++)
	{
        returnResult = ComputeCrossCoherenceValue(Data, locationJ, locationK, dVarVector(loop3), dTime, dCoherenceValue);

		dValVector(loop3) = dCoherenceValue;
	}

	return true;
}

bool CRPSLohAndLinCoherence::ComputeCrossCoherenceVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
	std::complex<double> dCoherenceValue = 0.0;
    bool returnResult = true;

    for (int loop3 = 0; loop3 < Data.numberOfTimeIncrements.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop3++)
    {
       dVarVector(loop3) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * (loop3);
                
       returnResult = ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dVarVector(loop3), dCoherenceValue);

       dValVector(loop3) = dCoherenceValue;
    }

	return true;
}

bool CRPSLohAndLinCoherence::ComputeCrossCoherenceMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix)
{
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

	bool returnResult = SeismicLabAPI::CRPSSeismicLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.\n") ;
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

bool CRPSLohAndLinCoherence::ComputeCrossCoherenceValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    SeismicLabTools::LohAndLinCoherence lohAndLinCoherence;
	dValue = lohAndLinCoherence.computeCoherenceValue(locationJ.x, locationJ.y, locationJ.z, locationK.x, locationK.y, locationK.z, dFrequency, ParameterAlpha.getValue(), ParameterB.getValue());
	return true;
}

bool CRPSLohAndLinCoherence::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgLohAndLinCoherenceEdit* dlg = new SeismicLabGui::DlgLohAndLinCoherenceEdit(ParameterAlpha, ParameterB, Data.coherenceFunction);
	Gui::Control().showDialog(dlg);
    return true;
}
