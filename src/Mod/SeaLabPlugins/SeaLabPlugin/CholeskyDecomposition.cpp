

#include "CholeskyDecomposition.h"
#include <Mod/SeaLabAPI/App/RPSSeaLabFramework.h>
#include <Mod/GeneralTools/App/CholeskyDecomposition.h>
#include <Base/Console.h>

using namespace SeaLab;
using namespace SeaLabAPI;
using namespace std;

PROPERTY_SOURCE(SeaLab::CCholeskyDecomposition, SeaLabAPI::SeaLabFeaturePSDDecompositionMethod)

CCholeskyDecomposition::CCholeskyDecomposition() {

}
bool CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector)
{
	int n = Data.numberOfSpatialPosition.getValue();
	int N = Data.numberOfFrequency.getValue();

	bool returnResult = SeaLabAPI::CRPSSeaLabFramework::ComputeFrequenciesVectorF(Data, locationJ, dVarVector);
    
	if (!returnResult) 
		return false;

    cx_mat dCPSDDecomMatrix(n,n);

	mat locationCoord(Data.numberOfSpatialPosition.getValue(), 4);

    returnResult = CRPSSeaLabFramework::ComputeLocationCoordinateMatrixP3(Data, locationCoord);

    if (!returnResult)
     return false;

	int locationIndexJ = CRPSSeaLabFramework::getLocationIndex(Data, locationJ);
    int locationIndexK = CRPSSeaLabFramework::getLocationIndex(Data, locationK);
	
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
bool CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector)
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
bool CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCPSDDecomMatrix)
{
    cx_mat psdMatrix(Data.numberOfSpatialPosition.getValue(), Data.numberOfSpatialPosition.getValue());
    bool returnResult = SeaLabAPI::CRPSSeaLabFramework::ComputeCrossFrequencySpectrumMatrixPP(
        Data, dFrequency, dTime, psdMatrix);
    if (!returnResult)//the computation of the psd matrix has failed.
        return false;

	rps::General::CholeskyDecomposition decomposition;
   
	decomposition.computeCholeskyDecomposition_cx(psdMatrix, dCPSDDecomMatrix);
	
	return true;
}
bool CCholeskyDecomposition::OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data)
{
	return true;
}

