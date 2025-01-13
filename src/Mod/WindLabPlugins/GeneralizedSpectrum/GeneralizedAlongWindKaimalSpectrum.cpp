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

#include "GeneralizedAlongWindKaimalSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include "widgets/DlgGeneralizedKaimalSpectrum.h"
#include <Mod/WindLabTools/App/spectrum/GeneralizedKaimalSpectrum.h>
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSGeneralizedAlongWindKaimalSpectrum, WindLabAPI::WindLabFeatureXSpectrum)

CRPSGeneralizedAlongWindKaimalSpectrum::CRPSGeneralizedAlongWindKaimalSpectrum()
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

bool CRPSGeneralizedAlongWindKaimalSpectrum::ComputeXCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    if (!returnResult)
    {
        Base::Console().Error("The computation of the frequency vector has failed.") ;
        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
}
bool CRPSGeneralizedAlongWindKaimalSpectrum::ComputeXCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
	bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}
bool CRPSGeneralizedAlongWindKaimalSpectrum::ComputeXCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix)
{
	 // Local array for location coordinates
    mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
    
    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
        if(!returnResult)
    {
       Base::Console().Error("The computation of the location coordinates matrix has failed.") ;
       return false;
    }
    
    Base::Vector3d locationJ(0, 0, 0);
    Base::Vector3d locationK(0, 0, 0);

    for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition.getValue() && true == returnResult; loop1++)
    {
        for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition.getValue() && true == returnResult; loop2++)
        {
           locationJ = Base::Vector3d(dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop1, 3));
           locationK = Base::Vector3d(dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 3));
           returnResult = ComputeXCrossSpectrumValue(Data, locationJ, locationK, dFrequency, dTime, psdMatrix(loop1, loop2));
        }
    }

    return returnResult;
}

bool CRPSGeneralizedAlongWindKaimalSpectrum::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    WindLabGui::DlgGeneralizedKaimalSpectrumEdit* dlg = new WindLabGui::DlgGeneralizedKaimalSpectrumEdit(
            ParameterA, ParameterB, ParameterC, ParameterD, ParameterE, ParameterF, ParameterG,
            ParameterH, ParameterI, ParameterJ, ShearVelocity, Data.alongWindSpectrumModel, 1);
	Gui::Control().showDialog(dlg);
    return true;
	
}

bool CRPSGeneralizedAlongWindKaimalSpectrum::ComputeXCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
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

	WindLabTools::GeneralizedKaimalSpectrum generalizedKaimalPSD;
    PSDj = generalizedKaimalPSD.computeGeneralizedKaimalWindAutoSpectrum(dFrequency, locationJ.z, MEANj, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);
    PSDk = generalizedKaimalPSD.computeGeneralizedKaimalWindAutoSpectrum(dFrequency, locationK.z, MEANk, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);
    dValue = std::sqrt(PSDj * PSDk) * COHjk;

    return returnResult;
}

bool CRPSGeneralizedAlongWindKaimalSpectrum::ComputeXAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue)
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
        Base::Console().Error("The computation of the mean wind speed fails\n");
        return returnResult;
   }

   WindLabTools::GeneralizedKaimalSpectrum generalizedKaimalPSD;
   dValue = generalizedKaimalPSD.computeGeneralizedKaimalWindAutoSpectrum(dFrequency, location.z, MEAN, ShearVelocity.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond), a, b, c, d, e, f, g, h, i, j);

   return returnResult;
}    
bool CRPSGeneralizedAlongWindKaimalSpectrum::ComputeXAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    
    returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, location, dVarVector);
    
    if (!returnResult)
    {
        Base::Console().Error("The computation of the frequency vector has failed.\n");

        return false;
    }

    for (int loop = 0; loop < Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        returnResult = ComputeXAutoSpectrumValue(Data, location, dVarVector(loop), dTime, dValVector(loop));
    }

     return returnResult;
} 
bool CRPSGeneralizedAlongWindKaimalSpectrum::ComputeXAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;

    for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop++)
    {
        dVarVector(loop) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + loop * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeXAutoSpectrumValue(Data, location, dFrequency, dVarVector(loop), dValVector(loop));
    }

     return returnResult;
}