

#include "RPSCloughPenzienSpectrum.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLabTools/App/spectrum/CloughPenzienSpectrum.h>
#include "Widgets/DlgCloughPenzienSpectrum.h"
#include <Base/Console.h>
#include <Gui/Control.h>
#include <App/Application.h>
#include <App/Document.h>

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSCloughPenzienSpectrum, SeismicLabAPI::SeismicLabFeatureSpectrum)

CRPSCloughPenzienSpectrum::CRPSCloughPenzienSpectrum()
{
   ADD_PROPERTY_TYPE(GroundNaturalFrequency, (2.39), "Parameters", App::Prop_None, "The natural frequency of the ground.");
   ADD_PROPERTY_TYPE(GroundDampingRatio, (6.0), "Parameters", App::Prop_None, "The damping ratio of the ground.");
   ADD_PROPERTY_TYPE(SecondFilterLayerFrequency, (0.239), "Parameters", App::Prop_None, "The frequency of the second  filter layer.");
   ADD_PROPERTY_TYPE(SecondFilterLayerDampingRatio, (0.6), "Parameters", App::Prop_None, "The damping ratio of the second  filter layer.");
   ADD_PROPERTY_TYPE(ConstantSpectralIntensity, (1.0), "Parameters", App::Prop_None, "The shaking intensity of the ground.");

}

bool CRPSCloughPenzienSpectrum::ComputeCrossSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
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

bool CRPSCloughPenzienSpectrum::ComputeCrossSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
   bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}

bool CRPSCloughPenzienSpectrum::ComputeCrossSpectrumMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
{
	 // Local array for location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
    
    bool returnResult = CRPSSeismicLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
        if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.\n") ;
       return false;
    }
    
    Base::Vector3d locationJ(0, 0, 0);
    Base::Vector3d locationK(0, 0, 0);

    for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition.getValue(); loop1++)
    {
        for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition.getValue(); loop2++)
        {
           locationJ = Base::Vector3d(dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop1, 3));
           locationK = Base::Vector3d(dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 3));
           returnResult = ComputeCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

//Initial setting
bool CRPSCloughPenzienSpectrum::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	// the input diolag
    SeismicLabGui::DlgCloughPenzienSpectrumEdit* dlg = new SeismicLabGui::DlgCloughPenzienSpectrumEdit(GroundNaturalFrequency,GroundDampingRatio, SecondFilterLayerFrequency, SecondFilterLayerDampingRatio, ConstantSpectralIntensity, Data.spectrumModel);
	Gui::Control().showDialog(dlg);

    return true;
}


bool CRPSCloughPenzienSpectrum::ComputeCrossSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    bool returnResult = true;

    std::complex<double> COHjk = 0.0;
    double PSDj = 0.0;
    double PSDk = 0.0;

    returnResult = CRPSSeismicLabFramework::ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, COHjk);
    if (!returnResult) {
        Base::Console().Error("The computation of coherence fails\n");
        return returnResult;
    }

    SeismicLabTools::CloughPenzienSpectrum cloughPenzienSpectrum;
    PSDj = cloughPenzienSpectrum.computeCloughPenzienSpectrum(dFrequency, GroundNaturalFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond), GroundDampingRatio.getValue(), SecondFilterLayerFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond), SecondFilterLayerDampingRatio.getValue(), ConstantSpectralIntensity.getValue());
    PSDk = cloughPenzienSpectrum.computeCloughPenzienSpectrum(dFrequency, GroundNaturalFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond), GroundDampingRatio.getValue(), SecondFilterLayerFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond), SecondFilterLayerDampingRatio.getValue(), ConstantSpectralIntensity.getValue());
    dValue = std::sqrt(PSDj * PSDk) * COHjk;

    return true;
}

bool CRPSCloughPenzienSpectrum::ComputeAutoSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
   SeismicLabTools::CloughPenzienSpectrum cloughPenzienSpectrum;
   dValue = cloughPenzienSpectrum.computeCloughPenzienSpectrum(dFrequency, GroundNaturalFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond), GroundDampingRatio.getValue(), SecondFilterLayerFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond), SecondFilterLayerDampingRatio.getValue(), ConstantSpectralIntensity.getValue());
   return true;
}    
bool CRPSCloughPenzienSpectrum::ComputeAutoSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
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
        returnResult = ComputeAutoSpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSCloughPenzienSpectrum::ComputeAutoSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
} 