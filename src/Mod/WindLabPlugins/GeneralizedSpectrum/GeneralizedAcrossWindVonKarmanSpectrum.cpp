
#include "GeneralizedAcrossWindVonKarmanSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include "widgets/DlgGeneralizedVonKarmanSpectrum.h"
#include <QMessageBox>
#include <Mod/WindLabTools/App/spectrum/GeneralizedVonKarmanSpectrum.h>
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSGeneralizedAcrossWindVonKarmanSpectrum, WindLabAPI::WindLabFeatureYSpectrum)

CRPSGeneralizedAcrossWindVonKarmanSpectrum::CRPSGeneralizedAcrossWindVonKarmanSpectrum()
{
  ADD_PROPERTY_TYPE(IntegralLengthScale, (1.0), "Parameters", App::Prop_None, "The integral length scale");
  ADD_PROPERTY_TYPE(StandardDeviation, (1.0), "Parameters", App::Prop_None, "The standard deviation");

  ADD_PROPERTY_TYPE(ParameterA, (4.0), "Parameters", App::Prop_None, "The A parameter");
  ADD_PROPERTY_TYPE(ParameterB, (0.0), "Parameters", App::Prop_None, "The B parameter");
  ADD_PROPERTY_TYPE(ParameterC, (1.0), "Parameters", App::Prop_None, "The C parameter");
  ADD_PROPERTY_TYPE(ParameterD, (1.0), "Parameters", App::Prop_None, "The D parameter");
  ADD_PROPERTY_TYPE(ParameterE, (1.0), "Parameters", App::Prop_None, "The E parameter");
  ADD_PROPERTY_TYPE(ParameterF, (1.0), "Parameters", App::Prop_None, "The F parameter");
  ADD_PROPERTY_TYPE(ParameterG, (1.0), "Parameters", App::Prop_None, "The G parameter");
  ADD_PROPERTY_TYPE(ParameterH, (70.8), "Parameters", App::Prop_None, "The H parameter");
  ADD_PROPERTY_TYPE(ParameterI, (2.0), "Parameters", App::Prop_None, "The I parameter");
  ADD_PROPERTY_TYPE(ParameterJ, (5.0 / 6.0), "Parameters", App::Prop_None, "The J parameter");

}

bool CRPSGeneralizedAcrossWindVonKarmanSpectrum::ComputeYCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
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
bool CRPSGeneralizedAcrossWindVonKarmanSpectrum::ComputeYCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{

   bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeYCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}
bool CRPSGeneralizedAcrossWindVonKarmanSpectrum::ComputeYCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
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
           Base::Vector3d locationJ(dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop1, 3));
           Base::Vector3d locationK(dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 3));
           returnResult = ComputeYCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

//Initial setting
bool CRPSGeneralizedAcrossWindVonKarmanSpectrum::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    // the input diolag
    WindLabGui::DlgGeneralizedVonKarmanSpectrumEdit* dlg = new WindLabGui::DlgGeneralizedVonKarmanSpectrumEdit(
            ParameterA, ParameterB, ParameterC, ParameterD, ParameterE, ParameterF, ParameterG,
            ParameterH, ParameterI, ParameterJ, IntegralLengthScale, StandardDeviation, Data.alongWindSpectrumModel, 5);
	Gui::Control().showDialog(dlg);

    return true;
}


bool CRPSGeneralizedAcrossWindVonKarmanSpectrum::ComputeYCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    bool returnResult = true;

   double a = ParameterA.getValue();
   double b = ParameterB.getValue();
   double c = ParameterC.getValue();
   double d = ParameterD.getValue();
   double e = ParameterE.getValue();
   double f = ParameterF.getValue();
   double g = ParameterG.getValue();
   double h = ParameterH.getValue();
   double i = ParameterI.getValue();
   double j = ParameterJ.getValue();

   double MEANj = 0.0;
   double MEANk = 0.0;
   std::complex<double> COHjk = 0.0;
   double PSDj = 0.0;
   double PSDk = 0.0;

    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationJ, dTime, MEANj);
    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationK, dTime, MEANk);
    returnResult = CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, COHjk);

    WindLabTools::GeneralizedVonKarmanSpectrum generalizedVonKarmanPSD;
    PSDj = generalizedVonKarmanPSD.computeGeneralizedVonKarmanWindAutoSpectrum(dFrequency, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), MEANj, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);
    PSDk = generalizedVonKarmanPSD.computeGeneralizedVonKarmanWindAutoSpectrum(dFrequency, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), MEANk, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);
    dValue = std::sqrt(PSDj * PSDk) * COHjk;

    return returnResult;
}

bool CRPSGeneralizedAcrossWindVonKarmanSpectrum::ComputeYAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
    bool returnResult = true;

   double a = ParameterA.getValue();
   double b = ParameterB.getValue();
   double c = ParameterC.getValue();
   double d = ParameterD.getValue();
   double e = ParameterE.getValue();
   double f = ParameterF.getValue();
   double g = ParameterG.getValue();
   double h = ParameterH.getValue();
   double i = ParameterI.getValue();
   double j = ParameterJ.getValue();
   double MEAN = 0.0;

   returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, location, dTime, MEAN);
   if (!returnResult)
   {
        Base::Console().Warning("The computation of mean wind speed fails\n");
        return returnResult;
   }

    WindLabTools::GeneralizedVonKarmanSpectrum generalizedVonKarmanPSD;
    dValue = generalizedVonKarmanPSD.computeGeneralizedVonKarmanWindAutoSpectrum(dFrequency, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), MEAN, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);

    return returnResult;
}    
bool CRPSGeneralizedAcrossWindVonKarmanSpectrum::ComputeYAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
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
bool CRPSGeneralizedAcrossWindVonKarmanSpectrum::ComputeYAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeYAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}