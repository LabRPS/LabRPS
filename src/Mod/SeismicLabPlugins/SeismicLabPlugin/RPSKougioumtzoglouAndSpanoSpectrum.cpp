

#include "RPSKougioumtzoglouAndSpanoSpectrum.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/spectrum/KougioumtzoglouAndSpanoSpectrum.h>
#include "Widgets/DlgKougioumtzoglouAndSpanoSpectrum.h"
#include <Base/Console.h>
#include <Gui/Control.h>
#include <App/Application.h>
#include <App/Document.h>

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSKougioumtzoglouAndSpanoSpectrum, SeismicLabAPI::SeismicLabFeatureSpectrum)

CRPSKougioumtzoglouAndSpanoSpectrum::CRPSKougioumtzoglouAndSpanoSpectrum()
{
   ADD_PROPERTY_TYPE(ConstantS, (0.03), "Parameters", App::Prop_None, "The constant S.");

}

bool CRPSKougioumtzoglouAndSpanoSpectrum::ComputeCrossSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    if (Data.stationarity.getValue()) {
        Base::Console().Error("The active spectrum model is only for non-stationary ground motion.\n");
        return false;
    }

	bool returnResult = true;
    
    returnResult = CRPSSeismicLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    if (!returnResult)
    {
        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeCrossSpectrumValue(Data, locationJ, locationK, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}

bool CRPSKougioumtzoglouAndSpanoSpectrum::ComputeCrossSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    if (Data.stationarity.getValue()) {
        Base::Console().Error("The active spectrum model is only for non-stationary ground motion.\n");
        return false;
    }

   bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}

bool CRPSKougioumtzoglouAndSpanoSpectrum::ComputeCrossSpectrumMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
{
    if (Data.stationarity.getValue()) {
        Base::Console().Error("The active spectrum model is only for non-stationary ground motion.\n");
        return false;
    }

    Base::Vector3d locationJ(0, 0, 0);
    Base::Vector3d locationK(0, 0, 0);

    bool returnResult = true;

    for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition.getValue() && !Data.isInterruptionRequested.getValue() && returnResult; loop1++)
    {
        for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition.getValue() && !Data.isInterruptionRequested.getValue() && returnResult; loop2++)
        {
           returnResult = ComputeCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

//Initial setting
bool CRPSKougioumtzoglouAndSpanoSpectrum::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	// the input diolag
    SeismicLabGui::DlgKougioumtzoglouAndSpanoSpectrumEdit* dlg = new SeismicLabGui::DlgKougioumtzoglouAndSpanoSpectrumEdit(ConstantS, Data.spectrumModel);
	Gui::Control().showDialog(dlg);

    return true;
}


bool CRPSKougioumtzoglouAndSpanoSpectrum::ComputeCrossSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    if (Data.stationarity.getValue()) {
        Base::Console().Error("The active spectrum model is only for non-stationary ground motion.\n");
        return false;
    }

     bool returnResult = true;

    std::complex<double> COHjk = 0.0;
    double PSD = 0.0;

    returnResult = CRPSSeismicLabFramework::ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, COHjk);
    if (!returnResult) {
        Base::Console().Error("The computation of coherence fails\n");
        return returnResult;
    }

    SeismicLabTools::KougioumtzoglouAndSpanoSpectrum kougioumtzoglouAndSpanoSpectrum;
    PSD = kougioumtzoglouAndSpanoSpectrum.computeKougioumtzoglouAndSpanoSpectrum(dFrequency, dTime, ConstantS.getValue());
    dValue = PSD * COHjk;

    return true;
}

bool CRPSKougioumtzoglouAndSpanoSpectrum::ComputeAutoSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
    if (Data.stationarity.getValue()) {
        Base::Console().Error("The active spectrum model is only for non-stationary ground motion.\n");
        return false;
    }

   SeismicLabTools::KougioumtzoglouAndSpanoSpectrum kougioumtzoglouAndSpanoSpectrum;
   dValue = kougioumtzoglouAndSpanoSpectrum.computeKougioumtzoglouAndSpanoSpectrum(dFrequency, dTime, ConstantS.getValue());
   return true;
}    
bool CRPSKougioumtzoglouAndSpanoSpectrum::ComputeAutoSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
{
    if (Data.stationarity.getValue()) {
        Base::Console().Error("The active spectrum model is only for non-stationary ground motion.\n");
        return false;
    }

     bool returnResult = true;
    
    returnResult = CRPSSeismicLabFramework::ComputeFrequenciesVectorF(Data, location, dVarVector);
    
    if (!returnResult)
    {
        Base::Console().Warning("The computation of frequency vector  has failed.\n");

        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeAutoSpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSKougioumtzoglouAndSpanoSpectrum::ComputeAutoSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
    if (Data.stationarity.getValue()) {
        Base::Console().Error("The active spectrum model is only for non-stationary ground motion.\n");
        return false;
    }

     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
} 