

#include "RPSvonKarmanAcrossWindSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLabTools/App/spectrum/VonKarmanSpectrum.h>
#include "Widgets/DlgvonKarmanAcrossWindSpectrum.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSvonKarmanAcrossWindSpectrum, WindLabAPI::WindLabFeatureYSpectrum)

CRPSvonKarmanAcrossWindSpectrum::CRPSvonKarmanAcrossWindSpectrum()
{
  ADD_PROPERTY_TYPE(Constant1, (4.0), "Parameters", App::Prop_None, "Constant 1");
  ADD_PROPERTY_TYPE(Constant2, (755.2), "Parameters", App::Prop_None, "Constant 2");
  ADD_PROPERTY_TYPE(Constant3, (283.2), "Parameters", App::Prop_None, "Constant 3");
  ADD_PROPERTY_TYPE(IntegralLengthScale, (80.0), "Parameters", App::Prop_None, "The integral length scale");
  ADD_PROPERTY_TYPE(StandardDeviation, (1.0), "Parameters", App::Prop_None, "The standard deviation");

}

bool CRPSvonKarmanAcrossWindSpectrum::ComputeYCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    if (!returnResult)
    {
        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeYCrossSpectrumValue(Data, locationJ, locationK, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}
bool CRPSvonKarmanAcrossWindSpectrum::ComputeYCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeYCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}
bool CRPSvonKarmanAcrossWindSpectrum::ComputeYCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
{
	 // Local array for location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
    
    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
        if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.") ;
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
           returnResult = ComputeYCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

bool CRPSvonKarmanAcrossWindSpectrum::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    WindLabGui::DlgvonKarmanAcrossWindSpectrumEdit* dlg = new WindLabGui::DlgvonKarmanAcrossWindSpectrumEdit(Constant1, Constant2, IntegralLengthScale, StandardDeviation, Data.acrossWindSpectrumModel);
	Gui::Control().showDialog(dlg);
    return true;
}



bool CRPSvonKarmanAcrossWindSpectrum::ComputeYCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    bool returnResult = true;

   double MEANj = 0.0;
   double MEANk = 0.0;
   std::complex<double> COHjk = 0.0;
   double PSDj = 0.0;
   double PSDk = 0.0;

    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationJ, dTime, MEANj);
    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationK, dTime, MEANk);
    returnResult = CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, COHjk);

    WindLabTools::VonKarmanSpectrum vonKarmanPSD;
    PSDj = vonKarmanPSD.computeAcrossWindAutoSpectrum(dFrequency, MEANj, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue(), Constant3.getValue());
    PSDk = vonKarmanPSD.computeAcrossWindAutoSpectrum(dFrequency, MEANk, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue(), Constant3.getValue());
    dValue = std::sqrt(PSDj * PSDk) * COHjk;

    return returnResult;
}

bool CRPSvonKarmanAcrossWindSpectrum::ComputeYAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
   bool returnResult = true;

   double MEAN = 0.0;

   returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, location, dTime, MEAN);
   if (!returnResult)
   {
        Base::Console().Warning("The computation of mean wind speed fails\n");
        return returnResult;
   }
    WindLabTools::VonKarmanSpectrum vonKarmanPSD;
    dValue = vonKarmanPSD.computeAcrossWindAutoSpectrum(dFrequency, MEAN, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), Constant1.getValue(), Constant2.getValue(), Constant3.getValue());

    return returnResult;
}    
bool CRPSvonKarmanAcrossWindSpectrum::ComputeYAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, location, dVarVector);
    
    if (!returnResult)
    {
        Base::Console().Warning("The computation of frequency vector  has failed.\n");

        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeYAutoSpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSvonKarmanAcrossWindSpectrum::ComputeYAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeYAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}