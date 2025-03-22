

#include "RPSPiersonMoskowitzSpectrum.h"
#include <Mod/SeaLabAPI/App/RPSSeaLabFramework.h>
#include <Mod/SeaLabTools/App/spectrum/PiersonMoskowitzSpectrum.h>
#include "Widgets/DlgPiersonMoskowitzSpectrum.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace SeaLab;
using namespace SeaLabAPI;

PROPERTY_SOURCE(SeaLab::CRPSPiersonMoskowitzSpectrum, SeaLabAPI::SeaLabFeatureFrequencySpectrum)

CRPSPiersonMoskowitzSpectrum::CRPSPiersonMoskowitzSpectrum()
{
   ADD_PROPERTY_TYPE(SignificantWaveHeight, (12100), "Parameters", App::Prop_None, "The significant wave height.");
   ADD_PROPERTY_TYPE(PeakPeriod, (12.7), "Parameters", App::Prop_None, "The peak period.");
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeaLab#Pierson_Moskowitz_Spectrum_1964");

}

bool CRPSPiersonMoskowitzSpectrum::ComputeCrossFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
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

bool CRPSPiersonMoskowitzSpectrum::ComputeCrossFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
   bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeCrossFrequencySpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}

bool CRPSPiersonMoskowitzSpectrum::ComputeCrossFrequencySpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
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
bool CRPSPiersonMoskowitzSpectrum::OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data)
{
	// the input diolag
    SeaLabGui::DlgPiersonMoskowitzSpectrumEdit* dlg = new SeaLabGui::DlgPiersonMoskowitzSpectrumEdit(SignificantWaveHeight, PeakPeriod, Data.frequencySpectrum);
	Gui::Control().showDialog(dlg);

    return true;
}


bool CRPSPiersonMoskowitzSpectrum::ComputeCrossFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
   bool returnResult = true;

   std::complex<double> COHjk = 0.0;
   double PSD = 0.0;

    returnResult = CRPSSeaLabFramework::ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, COHjk);

    SeaLabTools::PiersonMoskowitzSpectrum piersonMoskowitzSpectrum;
    PSD = piersonMoskowitzSpectrum.computeSpectrum(dFrequency, SignificantWaveHeight.getQuantityValue().getValueAs(Base::Quantity::Metre), PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Second));

    dValue = PSD * COHjk * ScaleCoefficient.getValue();

    return returnResult;
}

bool CRPSPiersonMoskowitzSpectrum::ComputeAutoFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
   bool returnResult = true;
  
   SeaLabTools::PiersonMoskowitzSpectrum piersonMoskowitzSpectrum;
   dValue = piersonMoskowitzSpectrum.computeSpectrum(dFrequency, SignificantWaveHeight.getQuantityValue().getValueAs(Base::Quantity::Metre), PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Second)) * ScaleCoefficient.getValue();

    return returnResult;
}    
bool CRPSPiersonMoskowitzSpectrum::ComputeAutoFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
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
bool CRPSPiersonMoskowitzSpectrum::ComputeAutoFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeAutoFrequencySpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
} 