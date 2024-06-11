
#include "GeneralizedVerticalWindKaimalSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include "widgets/DlgGeneralizedKaimalSpectrum.h"
#include <QMessageBox>
#include <Mod/WindLabTools/App/spectrum/GeneralizedKaimalSpectrum.h>
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSGeneralizedVerticalWindKaimalSpectrum, WindLabAPI::WindLabFeatureZSpectrum)

CRPSGeneralizedVerticalWindKaimalSpectrum::CRPSGeneralizedVerticalWindKaimalSpectrum()
{
ADD_PROPERTY_TYPE(ShearVelocity, (1760.0), "Parameters", App::Prop_None, "The shear velocity of the flow");

  ADD_PROPERTY_TYPE(ParameterA, (200.0), "Parameters", App::Prop_None, "The A parameter");
  ADD_PROPERTY_TYPE(ParameterB, (0.0), "Parameters", App::Prop_None, "The B parameter");
  ADD_PROPERTY_TYPE(ParameterC, (1.0), "Parameters", App::Prop_None, "The C parameter");
  ADD_PROPERTY_TYPE(ParameterD, (1.0), "Parameters", App::Prop_None, "The D parameter");
  ADD_PROPERTY_TYPE(ParameterE, (1.0), "Parameters", App::Prop_None, "The E parameter");
  ADD_PROPERTY_TYPE(ParameterF, (1.0), "Parameters", App::Prop_None, "The F parameter");
  ADD_PROPERTY_TYPE(ParameterG, (1.0), "Parameters", App::Prop_None, "The G parameter");
  ADD_PROPERTY_TYPE(ParameterH, (50.0), "Parameters", App::Prop_None, "The H parameter");
  ADD_PROPERTY_TYPE(ParameterI, (1.0), "Parameters", App::Prop_None, "The I parameter");
  ADD_PROPERTY_TYPE(ParameterJ, (5.0 / 3.0), "Parameters", App::Prop_None, "The J parameter");
}

bool CRPSGeneralizedVerticalWindKaimalSpectrum::ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    if (!returnResult)
    {
        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeZCrossSpectrumValue(Data, locationJ, locationK, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}
bool CRPSGeneralizedVerticalWindKaimalSpectrum::ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeZCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}
bool CRPSGeneralizedVerticalWindKaimalSpectrum::ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
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
           returnResult = ComputeZCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

//Initial setting
bool CRPSGeneralizedVerticalWindKaimalSpectrum::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
	    // the input diolag
    WindLabGui::DlgGeneralizedKaimalSpectrumEdit* dlg = new WindLabGui::DlgGeneralizedKaimalSpectrumEdit(
            ParameterA, ParameterB, ParameterC, ParameterD, ParameterE, ParameterF, ParameterG,
            ParameterH, ParameterI, ParameterJ, ShearVelocity, Data.alongWindSpectrumModel, 3);
	Gui::Control().showDialog(dlg);
    return true;
}

bool CRPSGeneralizedVerticalWindKaimalSpectrum::ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
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

    WindLabTools::GeneralizedKaimalSpectrum generalizedKaimalPSD;
    PSDj = generalizedKaimalPSD.computeGeneralizedKaimalWindAutoSpectrum(dFrequency, locationJ.z, MEANj, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);
    PSDk = generalizedKaimalPSD.computeGeneralizedKaimalWindAutoSpectrum(dFrequency, locationK.z, MEANk, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);
    dValue = std::sqrt(PSDj * PSDk) * COHjk;

    return returnResult;
}

bool CRPSGeneralizedVerticalWindKaimalSpectrum::ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
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

    WindLabTools::GeneralizedKaimalSpectrum generalizedKaimalPSD;
    dValue = generalizedKaimalPSD.computeGeneralizedKaimalWindAutoSpectrum(dFrequency, location.z, MEAN, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);

   return returnResult;
}    
bool CRPSGeneralizedVerticalWindKaimalSpectrum::ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
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
        returnResult = ComputeZAutoSpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSGeneralizedVerticalWindKaimalSpectrum::ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeZAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}