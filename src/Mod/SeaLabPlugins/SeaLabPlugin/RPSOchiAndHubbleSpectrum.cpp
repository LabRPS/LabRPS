

#include "RPSOchiAndHubbleSpectrum.h"
#include <Mod/SeaLabAPI/App/RPSSeaLabFramework.h>
#include <Mod/SeaLabTools/App/spectrum/OchiAndHubbleSpectrum.h>
#include "Widgets/DlgOchiAndHubbleSpectrum.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeaLab;
using namespace SeaLabAPI;

PROPERTY_SOURCE(SeaLab::CRPSOchiAndHubbleSpectrum, SeaLabAPI::SeaLabFeatureFrequencySpectrum)

CRPSOchiAndHubbleSpectrum::CRPSOchiAndHubbleSpectrum()
{
   ADD_PROPERTY_TYPE(SignificantWaveHeight1, (6804.00), "Parameters", App::Prop_None,"The significant wave height of the first peak.");
   ADD_PROPERTY_TYPE(SignificantWaveHeight2, (4374.00), "Parameters", App::Prop_None,"The significant wave height of the second peak.");
   ADD_PROPERTY_TYPE(PeakFrequency1, (0.077), "Parameters", App::Prop_None, "The peak frequency of the first peak.");
   ADD_PROPERTY_TYPE(PeakFrequency2, (0.133), "Parameters", App::Prop_None, "The peak frequency of the second peak.");
   ADD_PROPERTY_TYPE(PeakShape1, (3.00), "Parameters", App::Prop_None, "The shape of the first peak.");
   ADD_PROPERTY_TYPE(PeakShape2, (0.932), "Parameters", App::Prop_None, "The shape of the second peak.");
   ADD_PROPERTY_TYPE(AutoPara, (true), "Parameters", App::Prop_None, "Whether the six parameter should be automatically computed by LabRPS or not.");
   ADD_PROPERTY_TYPE(SignificantWaveHeight, (8100.00), "Parameters", App::Prop_None,"The significant wave height used for the calculation of the six parameters in case of automatic parameter computation.");
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeaLab#Ochi_Hubble_Spectrum");

}

bool CRPSOchiAndHubbleSpectrum::ComputeCrossFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;
    
    returnResult = CRPSSeaLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    if (!returnResult)
    {
        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeCrossFrequencySpectrumValue(Data, locationJ, locationK, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}

bool CRPSOchiAndHubbleSpectrum::ComputeCrossFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
   bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeCrossFrequencySpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}

bool CRPSOchiAndHubbleSpectrum::ComputeCrossFrequencySpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
{
	 // Local array for location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
    
    bool returnResult = CRPSSeaLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
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
           returnResult = ComputeCrossFrequencySpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

//Initial setting
bool CRPSOchiAndHubbleSpectrum::OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data)
{
	// the input diolag
    SeaLabGui::DlgOchiAndHubbleSpectrumEdit* dlg = new SeaLabGui::DlgOchiAndHubbleSpectrumEdit(SignificantWaveHeight1, SignificantWaveHeight2, PeakFrequency1, PeakFrequency2, PeakShape1, PeakShape2, AutoPara, SignificantWaveHeight, Data.frequencySpectrum);
	Gui::Control().showDialog(dlg);

    return true;
}


bool CRPSOchiAndHubbleSpectrum::ComputeCrossFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
   bool returnResult = true;

   std::complex<double> COHjk = 0.0;
   double PSD = 0.0;

    returnResult = CRPSSeaLabFramework::ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, COHjk);

    SeaLabTools::OchiAndHubbleSpectrum ochiAndHubbleSpectrum;
    PSD = ochiAndHubbleSpectrum.computeSpectrum(dFrequency, 
        SignificantWaveHeight1.getQuantityValue().getValueAs(Base::Quantity::Metre),
        SignificantWaveHeight2.getQuantityValue().getValueAs(Base::Quantity::Metre),
        PeakFrequency1.getQuantityValue().getValueAs(Base::Quantity::Hertz), 
        PeakFrequency2.getQuantityValue().getValueAs(Base::Quantity::Hertz),
        PeakShape1.getValue(), 
        PeakShape2.getValue(),
        AutoPara.getValue(),
        SignificantWaveHeight.getQuantityValue().getValueAs(Base::Quantity::Metre));

    dValue = PSD * COHjk * ScaleCoefficient.getValue();

    return returnResult;
}

bool CRPSOchiAndHubbleSpectrum::ComputeAutoFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
   bool returnResult = true;
  
   SeaLabTools::OchiAndHubbleSpectrum ochiAndHubbleSpectrum;
   dValue = ochiAndHubbleSpectrum.computeSpectrum(
       dFrequency, SignificantWaveHeight1.getQuantityValue().getValueAs(Base::Quantity::Metre),
       SignificantWaveHeight2.getQuantityValue().getValueAs(Base::Quantity::Metre),
       PeakFrequency1.getQuantityValue().getValueAs(Base::Quantity::Hertz),
       PeakFrequency2.getQuantityValue().getValueAs(Base::Quantity::Hertz),
       PeakShape1.getValue(), PeakShape2.getValue(), AutoPara.getValue(),
           SignificantWaveHeight.getQuantityValue().getValueAs(Base::Quantity::Metre))
       * ScaleCoefficient.getValue();
    return returnResult;
}    
bool CRPSOchiAndHubbleSpectrum::ComputeAutoFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    
    returnResult = CRPSSeaLabFramework::ComputeFrequenciesVectorF(Data, location, dVarVector);
    
    if (!returnResult)
    {
        Base::Console().Warning("The computation of frequency vector  has failed.\n");

        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeAutoFrequencySpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSOchiAndHubbleSpectrum::ComputeAutoFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeAutoFrequencySpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
} 