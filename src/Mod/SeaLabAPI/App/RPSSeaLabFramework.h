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

#ifndef RPSSEALABFRAMEWORK_H
#define RPSSEALABFRAMEWORK_H

#include "RPSSeaLabAPIdefines.h"
#include <Mod/SeaLabAPI/App/SeaLabSimulationData.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureDescription.h>
#include <Base/Vector3D.h>

namespace SeaLabAPI {


class RPS_CORE_API CRPSSeaLabFramework
{
public:
	CRPSSeaLabFramework();
	~CRPSSeaLabFramework();

	// coherence function
    static bool ComputeCrossCoherenceVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossCoherenceVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossCoherenceMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

	// correlation function
	
    static bool ComputeCrossCorrelationVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector);

    static bool ComputeCrossCorrelationMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dTime, mat &dCorrelationMatrix);

   // frequency
    static bool ComputeFrequenciesVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector);
  
    static bool ComputeFrequenciesMatrixFP(const SeaLabAPI::SeaLabSimulationData& Data, mat& dMatrix);

    static bool ComputeLocationCoordinateMatrixP3(const SeaLabAPI::SeaLabSimulationData& Data, mat& dLocCoord);

	// mean wind speed
    static bool ComputeMeanAccelerationSpeedVectorP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    static bool ComputeMeanAccelerationSpeedVectorT(const SeaLabAPI::SeaLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

	// modulation function
    static bool ComputeModulationValue(const SeaLabAPI::SeaLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, const double &dTime, double &dValue);
    static bool ComputeModulationVectorP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeModulationVectorT(const SeaLabAPI::SeaLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, vec &dVarVector, vec &dValVector);
    static bool ComputeModulationVectorF(const SeaLabAPI::SeaLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector);
	
    // psd decomposition
    static bool ComputeDecomposedCrossSpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeDecomposedCrossSpectrumVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeDecomposedCrossSpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix);

	// randomness
    static bool GenerateRandomMatrixFP(const SeaLabAPI::SeaLabSimulationData &Data, mat &dRandomValueArray);

	// frequency spectrum
    static bool ComputeAutoFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    static bool ComputeAutoFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    static bool ComputeAutoFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    static bool ComputeCrossFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossFrequencySpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData& Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);
  
    static bool ComputeCrossFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

// directional spectrum
  
    static bool ComputeCrossDirectionalSpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, const double &dDirection, std::complex<double> &dValue);

    static bool ComputeCrossDirectionalSpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, const double &dDirection, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossDirectionalSpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dDirection, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossDirectionalSpectrumVectorD(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossDirectionalSpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, const double &dDirection, cx_mat &psdMatrix);

    static bool ComputeAutoDirectionalSpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, const double &dDirection, double &dValue);
    
    static bool ComputeAutoDirectionalSpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, const double &dDirection, vec &dVarVector, vec &dValVector);

    static bool ComputeAutoDirectionalSpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, const double &dDirection, vec &dVarVector, vec &dValVector);

    static bool ComputeAutoDirectionalSpectrumVectorD(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector);

// directional spreading function
    static bool ComputeDirectionalSpreadingFunctionValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dfrequency, const double &dDirection, double &dValue);
    
    static bool ComputeDirectionalSpreadingFunctionVectorF(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dDirection, vec &dVarVector, vec &dValVector);

    static bool ComputeDirectionalSpreadingFunctionVectorP(const SeaLabAPI::SeaLabSimulationData& Data, const double &dfrequency, const double &dDirection, vec &dVarVector, vec &dValVector);

    static bool ComputeDirectionalSpreadingFunctionVectorD(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dfrequency, vec &dVarVector, vec &dValVector);


	/////
    static bool ComputeCrossCoherenceValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);
    static bool ComputeCrossCorrelationValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue);
    static bool ComputeMeanAccelerationSpeedValue(const SeaLabAPI::SeaLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    static bool ComputeRandomValue(const SeaLabAPI::SeaLabSimulationData &Data, double &dValue);
	static bool ComputeFrequencyValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

	static SeaLabAPI::SeaLabFeatureDescription* getSeaLabFeatureDescription(const std::string& name);
	
    static bool TableToolCompute(const SeaLabAPI::SeaLabSimulationData &Data, const mat &inputTable, mat &outputTable);
    static bool MatrixToolCompute(const SeaLabAPI::SeaLabSimulationData &Data, const mat &inputMatrix, mat &outputMatrix);
    static bool UserDefinedRPSObjectCompute(const SeaLabAPI::SeaLabSimulationData &Data, mat &dresult);

    static bool ComputeCPDValue(const  SeaLabAPI::SeaLabSimulationData& Data, const double& x, double& dValue);
    static bool ComputeCPDVectorX(const SeaLabAPI::SeaLabSimulationData &Data, vec &dVarVector, vec &dValVector) ;
    
    //kurtosis
    static bool ComputeKurtosisValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeKurtosisVectorP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeKurtosisVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //peak factor
    static bool ComputePeakFactorValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputePeakFactorVectorP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputePeakFactorVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //pdf
    static bool ComputePDFValue(const SeaLabAPI::SeaLabSimulationData &Data, const double &x, double &dValue) ;
    static bool ComputePDFVectorX(const SeaLabAPI::SeaLabSimulationData &Data, vec &dVarVector, vec &dValVector) ;

    //shear velocity
    static bool ComputeShearVelocityOfFlowValue(const SeaLabAPI::SeaLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    static bool ComputeShearVelocityOfFlowVectorP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeShearVelocityOfFlowVectorT(const SeaLabAPI::SeaLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    //skewness
    static bool ComputeSkewnessValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeSkewnessVectorP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeSkewnessVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //standard deviation
    static bool ComputeStandardDeviationValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeStandardDeviationVectorP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeStandardDeviationVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //variance
    static bool ComputeVarianceValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeVarianceVectorP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeVarianceVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    // wave passage effect
    static bool ComputeWavePassageEffectVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);
    static bool ComputeWavePassageEffectVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);
    static bool ComputeWavePassageEffectMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);
    static bool ComputeWavePassageEffectValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    static int getLocationIndex(const SeaLabAPI::SeaLabSimulationData &Data, Base::Vector3d locationTobeFound);

    /** Get the current date time
    * @return         return current date and time.
    */
    static std::string getCurrentDateTime();
};

} //namespace SeaLabAPI

#endif
