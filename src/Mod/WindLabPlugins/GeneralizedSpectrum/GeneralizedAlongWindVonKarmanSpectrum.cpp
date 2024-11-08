/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "GeneralizedAlongWindVonKarmanSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include "widgets/DlgGeneralizedVonKarmanSpectrum.h"
#include <QMessageBox>
#include <Mod/WindLabTools/App/spectrum/GeneralizedVonKarmanSpectrum.h>
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSGeneralizedAlongWindVonKarmanSpectrum, WindLabAPI::WindLabFeatureXSpectrum)

CRPSGeneralizedAlongWindVonKarmanSpectrum::CRPSGeneralizedAlongWindVonKarmanSpectrum()
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

bool CRPSGeneralizedAlongWindVonKarmanSpectrum::ComputeXCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
    bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    if (!returnResult)
    {
        Base::Console().Error("The computation of the frequency vector has failed.\n");
        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}
bool CRPSGeneralizedAlongWindVonKarmanSpectrum::ComputeXCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{

    bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}
bool CRPSGeneralizedAlongWindVonKarmanSpectrum::ComputeXCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
{
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
    
    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
        if(!returnResult)
    {
       Base::Console().Error("The computation of the location coordinates matrix has failed.") ;
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
           returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

bool CRPSGeneralizedAlongWindVonKarmanSpectrum::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    WindLabGui::DlgGeneralizedVonKarmanSpectrumEdit* dlg = new WindLabGui::DlgGeneralizedVonKarmanSpectrumEdit(
            ParameterA, ParameterB, ParameterC, ParameterD, ParameterE, ParameterF, ParameterG,
            ParameterH, ParameterI, ParameterJ, IntegralLengthScale, StandardDeviation, Data.alongWindSpectrumModel, 4);
	Gui::Control().showDialog(dlg);

    return true;
}


bool CRPSGeneralizedAlongWindVonKarmanSpectrum::ComputeXCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
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
    if(!returnResult)
    {
       Base::Console().Error("The computation of the mean wind speed has failed.\n") ;
       return false;
    }
    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationK, dTime, MEANk);
    if(!returnResult)
    {
       Base::Console().Error("The computation of the mean wind speed has failed.\n") ;
       return false;
    }
    returnResult = CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, COHjk);
    if(!returnResult)
    {
       Base::Console().Error("The computation of the coherence value has failed.\n") ;
       return false;
    }

    WindLabTools::GeneralizedVonKarmanSpectrum generalizedVonKarmanPSD;
    PSDj = generalizedVonKarmanPSD.computeGeneralizedVonKarmanWindAutoSpectrum(dFrequency, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), MEANj, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);
    PSDk = generalizedVonKarmanPSD.computeGeneralizedVonKarmanWindAutoSpectrum(dFrequency, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), MEANk, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);
    dValue = std::sqrt(PSDj * PSDk) * COHjk;

    return returnResult;
}

bool CRPSGeneralizedAlongWindVonKarmanSpectrum::ComputeXAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
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
        Base::Console().Warning("The computation of the mean wind speed fails\n");
        return returnResult;
   }

    WindLabTools::GeneralizedVonKarmanSpectrum generalizedVonKarmanPSD;
    dValue = generalizedVonKarmanPSD.computeGeneralizedVonKarmanWindAutoSpectrum(dFrequency, IntegralLengthScale.getQuantityValue().getValueAs(Base::Quantity::Metre), MEAN, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);

   return returnResult;
}    
bool CRPSGeneralizedAlongWindVonKarmanSpectrum::ComputeXAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, location, dVarVector);
    
    if (!returnResult)
    {
        Base::Console().Warning("The computation of the frequency vector  has failed.\n");

        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeXAutoSpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSGeneralizedAlongWindVonKarmanSpectrum::ComputeXAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeXAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}