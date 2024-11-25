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

#include "CholeskyDecomposition.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/GeneralTools/App/CholeskyDecomposition.h>
#include <Base/Console.h>

using namespace WindLab;
using namespace WindLabAPI;
using namespace std;

PROPERTY_SOURCE(WindLab::CCholeskyDecomposition, WindLabAPI::WindLabFeaturePSDDecompositionMethod)

CCholeskyDecomposition::CCholeskyDecomposition() {

}

bool CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	int n = Data.numberOfSpatialPosition.getValue();
	int N = Data.numberOfFrequency.getValue();

	bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    
	if (!returnResult) {
        Base::Console().Error("The computation of the discrete frequencies vector has failed.\n");
        return false;
    }

    cx_mat dCPSDDecomMatrix(n,n);

	mat locationCoord(Data.numberOfSpatialPosition.getValue(), 4);
	
    returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, locationCoord);

    if (!returnResult) {
        
		Base::Console().Error("The computation of the location coordinates matrix has failed.\n");

        return false;
    }

	int locationIndexJ = CRPSWindLabFramework::getLocationIndex(Data, locationJ);
    int locationIndexK = CRPSWindLabFramework::getLocationIndex(Data, locationK);
	
	// Cholesky decomposition returns lower triangular matrix, so change indices for example S12 to S21
    int row = max(locationIndexJ,locationIndexK);
    int col = min(locationIndexJ, locationIndexK);

	for (int l = 0; l < N && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++)
	{
		returnResult = ComputeDecomposedCrossSpectrumMatrixPP(Data, dVarVector(l), dTime, dCPSDDecomMatrix);

		dValVector(l) = dCPSDDecomMatrix(row, col);
	}

	return returnResult;
}
bool CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
{
	int n = Data.numberOfSpatialPosition.getValue();
	int T = Data.numberOfTimeIncrements.getValue();

	bool returnResult = true;

    cx_mat dCPSDDecomMatrix(n,n);

	for (int l = 0; l < T && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++)
	{
        dVarVector(l) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + l * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
        returnResult = ComputeDecomposedCrossSpectrumMatrixPP(Data, dFrequency, dVarVector(l), dCPSDDecomMatrix);
        dValVector(l) = dCPSDDecomMatrix(Data.locationJ.getValue(), Data.locationK.getValue());
	}

	return returnResult;
}
bool CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCPSDDecomMatrix)
{
    cx_mat psdMatrix(Data.numberOfSpatialPosition.getValue(), Data.numberOfSpatialPosition.getValue());
    
	bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeCrossSpectrumMatrixPP(Data, dFrequency,dTime, psdMatrix);

	if (!returnResult) {
        
		Base::Console().Error("The computation of the power spectral density matrix has failed.\n");

        return false;
    }

	rps::General::CholeskyDecomposition decomposition;
   
	decomposition.computeCholeskyDecomposition_cx(psdMatrix, dCPSDDecomMatrix);
	
	return true;
}
bool CCholeskyDecomposition::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
	return true;
}

