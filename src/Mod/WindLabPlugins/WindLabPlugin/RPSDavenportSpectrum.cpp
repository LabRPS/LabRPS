

#include "RPSDavenportSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLabTools/App/spectrum/DavenportSpectrum.h>
#include "Widgets/DlgDavenportSpectrum.h"
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSDavenportSpectrum, WindLabAPI::WindLabFeatureXSpectrum)

CRPSDavenportSpectrum::CRPSDavenportSpectrum()
{
   ADD_PROPERTY_TYPE(MeanWindSpeed10, (30000.0), "Parameters", App::Prop_None, "The mean wind speed at 10 meters height above sea.");
}

bool CRPSDavenportSpectrum::ComputeXCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    if (!returnResult)
    {
        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}

bool CRPSDavenportSpectrum::ComputeXCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
   bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}

bool CRPSDavenportSpectrum::ComputeXCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
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
           returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

//Initial setting
bool CRPSDavenportSpectrum::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
	// the input diolag
    WindLabGui::DlgDavenportSpectrumEdit* dlg = new WindLabGui::DlgDavenportSpectrumEdit(MeanWindSpeed10, Data.alongWindSpectrumModel);
	Gui::Control().showDialog(dlg);

    return true;
}


bool CRPSDavenportSpectrum::ComputeXCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
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

    WindLabTools::DavenportSpectrum davenportPSD;
    PSDj = davenportPSD.computeAlongWindAutoSpectrum(dFrequency, MeanWindSpeed10.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond));
    PSDk = davenportPSD.computeAlongWindAutoSpectrum(dFrequency, MeanWindSpeed10.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond));
    dValue = std::sqrt(PSDj * PSDk) * COHjk;

    return returnResult;
}

bool CRPSDavenportSpectrum::ComputeXAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
{
   bool returnResult = true;

   double MEAN = 0.0;

   returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, location, dTime, MEAN);
   if (!returnResult)
   {
        Base::Console().Warning("The computation of mean wind speed fails\n");
        return returnResult;
   }
  
   WindLabTools::DavenportSpectrum davenportPSD;
   dValue = davenportPSD.computeAlongWindAutoSpectrum(dFrequency, MeanWindSpeed10.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond));

    return returnResult;
}    
bool CRPSDavenportSpectrum::ComputeXAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
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
        returnResult = ComputeXAutoSpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSDavenportSpectrum::ComputeXAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getValue() + loop * Data.timeIncrement.getValue();
        returnResult = ComputeXAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
} 