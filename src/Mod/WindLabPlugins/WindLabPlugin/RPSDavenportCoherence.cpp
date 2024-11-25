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

#include "RPSDavenportCoherence.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLabAPI/App/WindLabSimulationData.h>
#include <Mod/WindLabTools/App/coherence/DavenportCoherence.h>
#include "Widgets/DlgDavenportCoherence.h"
#include <Base/Console.h>
#include <Gui/Control.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Mod/WindLabAPI/App/IrpsWLModulation.h>


using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSDavenportCoherence, WindLabAPI::WindLabFeatureCoherence)

CRPSDavenportCoherence::CRPSDavenportCoherence()
{
    ADD_PROPERTY_TYPE(ExponentialDecayCx, (10.0), "Decay Coefficients", App::Prop_None, "The decay coefficient Cx");
    ADD_PROPERTY_TYPE(ExponentialDecayCy, (7.0), "Decay Coefficients", App::Prop_None, "The decay coefficient Cy");
    ADD_PROPERTY_TYPE(ExponentialDecayCz, (6.0), "Decay Coefficients", App::Prop_None, "The decay coefficient Cz");

}

bool CRPSDavenportCoherence::ComputeCrossCoherenceValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue)
{
    bool returnResult = true;

    double MEANj = 0.0;
    double MEANk = 0.0;

    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationJ, dTime, MEANj);
    if (!returnResult) {
        Base::Console().Error("The computation of mean wind speed at location %s has failed.\n");
        return false;
    }

    returnResult = CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, locationK, dTime, MEANk);
    if (!returnResult) {
        Base::Console().Error("The computation of mean wind speed fails\n");
        return false;
    }

    WindLabTools::DavenportCoherence davenportCoherence;

    //stationary and non-stationary but uniformly modulated. For non-stationarity, the user just has to make sure the mean wind speed is time dependent
	if ((Data.stationarity.getValue()) || (!Data.stationarity.getValue() && Data.uniformModulation.getValue() && this->IsUniformlyModulated.getValue()))
	{
     //stationarity here is taken into account in the mean wind speed. so we have only one formula here for both stationary and non-stationary
     dValue = davenportCoherence.computeCoherenceValue(locationJ.x, locationJ.y, locationJ.z, locationK.x, locationK.y, locationK.z, dFrequency, MEANj, MEANk);

    }
	else//this includes cases where the user chooses non-stationary wind with non-uniforme modulation. This feature cannot be used in this case.
	{
        Base::Console().Error("The computation of the cross coherence value has failed. The active feature does not allow non-stationarity with non-uniform modulation.\n");
        return false;
	}

	return true;
}

bool CRPSDavenportCoherence::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    // the input diolag
    WindLabGui::DlgDavenportCoherenceEdit* dlg = new WindLabGui::DlgDavenportCoherenceEdit(ExponentialDecayCx, ExponentialDecayCy, ExponentialDecayCz, Data.coherenceFunction);
	Gui::Control().showDialog(dlg);

    return true;
}

bool CRPSDavenportCoherence::ComputeCrossCoherenceVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	// The coherence value
	std::complex<double> dCoherenceValue = 0.0;
    bool returnResult = true;

    WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);

	for (int loop3 = 0; loop3 < Data.numberOfFrequency.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop3++)
	{
        returnResult = ComputeCrossCoherenceValue(Data, locationJ, locationK, dVarVector(loop3), dTime, dCoherenceValue);

		dValVector(loop3) = dCoherenceValue;
	}

	return true;
}

bool CRPSDavenportCoherence::ComputeCrossCoherenceVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
    // The coherence value
    std::complex<double> dCoherenceValue = 0.0;
    bool returnResult = true;

    for (int loop3 = 0; loop3 < Data.numberOfTimeIncrements.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop3++)
    {
       dVarVector(loop3) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second) * (loop3);
                
       returnResult = ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dVarVector(loop3), dCoherenceValue);

       dValVector(loop3) = dCoherenceValue;
    }

	return true;
}

bool CRPSDavenportCoherence::ComputeCrossCoherenceMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix)
{
	mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

	bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.") ;
       return false;
    }
	
	std::complex<double> coherence = 0.0;
    Base::Vector3d locationJ(0, 0, 0);
    Base::Vector3d locationK(0, 0, 0);

	for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop1++)
	{
		for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition.getValue()  && false == Data.isInterruptionRequested.getValue() && true == returnResult; loop2++)
		{
           locationJ = Base::Vector3d(dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop1, 3));
           locationK = Base::Vector3d(dLocCoord(loop2, 1), dLocCoord(loop2, 2), dLocCoord(loop2, 3));

            returnResult = ComputeCrossCoherenceValue(Data, locationJ, locationK, dFrequency, dTime, coherence);

			dCoherenceMatrix(loop1, loop2) = coherence;
		}
	}

	return true;
}
