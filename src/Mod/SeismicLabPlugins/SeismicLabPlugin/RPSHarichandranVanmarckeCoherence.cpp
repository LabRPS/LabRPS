

#include "RPSHarichandranVanmarckeCoherence.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/coherence/HarichandranVanmarckeCoherence.h>
#include "Widgets/DlgHarichandranVanmarckeCoherence.h"
#include <Base/Console.h>
#include <Gui/Control.h>
#include <App/Application.h>
#include <App/Document.h>

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSHarichandranVanmarckeCoherence, SeismicLabAPI::SeismicLabFeatureCoherence)

CRPSHarichandranVanmarckeCoherence::CRPSHarichandranVanmarckeCoherence()
{
   ADD_PROPERTY_TYPE(ParameterA, (0.626), "Parameters", App::Prop_None, "The parameter A.");
   ADD_PROPERTY_TYPE(ParameterAlpha, (0.022), "Parameters", App::Prop_None, "The parameter Alpha.");
   ADD_PROPERTY_TYPE(ParameterK, (19700000), "Parameters", App::Prop_None, "The parameter K.");
   ADD_PROPERTY_TYPE(ParameterOmegaZero, (12.692/6.28), "Parameters", App::Prop_None, "The parameter omega zero.");
   ADD_PROPERTY_TYPE(ParameterB, (3.47), "Parameters", App::Prop_None, "The parameter b.");
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Harichandran_Vanmarcke_Coherence_Function");

}

bool CRPSHarichandranVanmarckeCoherence::ComputeCrossCoherenceVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
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

bool CRPSHarichandranVanmarckeCoherence::ComputeCrossCoherenceVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
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

bool CRPSHarichandranVanmarckeCoherence::ComputeCrossCoherenceMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix)
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

bool CRPSHarichandranVanmarckeCoherence::ComputeCrossCoherenceValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    SeismicLabTools::HarichandranVanmarckeCoherence harichandranVanmarckeCoherence;
	dValue = harichandranVanmarckeCoherence.computeCoherenceValue(locationJ.x, locationJ.y, locationJ.z, locationK.x, locationK.y, locationK.z, dFrequency, ParameterA.getValue(), ParameterAlpha.getValue(), ParameterK.getQuantityValue().getValueAs(Base::Quantity::Metre), ParameterOmegaZero.getQuantityValue().getValueAs(Base::Quantity::Hertz), ParameterB.getValue()) * ScaleCoefficient.getValue();
	return true;
}

bool CRPSHarichandranVanmarckeCoherence::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    SeismicLabGui::DlgHarichandranVanmarckeCoherenceEdit* dlg = new SeismicLabGui::DlgHarichandranVanmarckeCoherenceEdit(ParameterA, ParameterAlpha, ParameterK, ParameterOmegaZero, ParameterB, Data.coherenceFunction);
	Gui::Control().showDialog(dlg);
    return true;
}
