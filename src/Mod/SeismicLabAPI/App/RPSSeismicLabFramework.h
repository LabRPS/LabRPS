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

#ifndef RPSSEISMICLABFRAMEWORK_H
#define RPSSEISMICLABFRAMEWORK_H

#include "RPSSeismicLabAPIdefines.h"
#include <Mod/SeismicLabAPI/App/SeismicLabSimulationData.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureDescription.h>
#include <Base/Vector3D.h>

namespace SeismicLabAPI {


class RPS_CORE_API CRPSSeismicLabFramework
{
public:
	CRPSSeismicLabFramework();
	~CRPSSeismicLabFramework();

	// coherence function
    static bool ComputeCrossCoherenceVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossCoherenceVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossCoherenceMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

	// correlation function
	
    static bool ComputeCrossCorrelationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector);

    static bool ComputeCrossCorrelationMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, mat &dCorrelationMatrix);

   // frequency
    static bool ComputeFrequenciesVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector);
  
    static bool ComputeFrequenciesMatrixFP(const SeismicLabAPI::SeismicLabSimulationData& Data, mat& dMatrix);

    static bool ComputeLocationCoordinateMatrixP3(const SeismicLabAPI::SeismicLabSimulationData& Data, mat& dLocCoord);

	// mean wind speed
    static bool ComputeMeanAccelerationSpeedVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    static bool ComputeMeanAccelerationSpeedVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

	// modulation function
    static bool ComputeModulationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    static bool ComputeModulationVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

	// psd decomposition
    static bool ComputeDecomposedCrossSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeDecomposedCrossSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeDecomposedCrossSpectrumMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix);

	// randomness
    static bool GenerateRandomMatrixFP(const SeismicLabAPI::SeismicLabSimulationData &Data, mat &dRandomValueArray);

	// spectrum
    static bool ComputeCrossSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);
    static bool ComputeCrossSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);
    static bool ComputeCrossSpectrumMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);
    static bool ComputeCrossSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);
    static bool ComputeAutoSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    static bool ComputeAutoSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeAutoSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

	/////
    static bool ComputeCrossCoherenceValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);
    static bool ComputeCrossCorrelationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue);
    static bool ComputeMeanAccelerationSpeedValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    static bool ComputeModulationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    static bool ComputeRandomValue(const SeismicLabAPI::SeismicLabSimulationData &Data, double &dValue);
	static bool ComputeFrequencyValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

	static SeismicLabAPI::SeismicLabFeatureDescription* getSeismicLabFeatureDescription(const std::string& name);
	
    static bool TableToolCompute(const SeismicLabAPI::SeismicLabSimulationData &Data, const mat &inputTable, mat &outputTable);
    static bool MatrixToolCompute(const SeismicLabAPI::SeismicLabSimulationData &Data, const mat &inputMatrix, mat &outputMatrix);
    static bool UserDefinedRPSObjectCompute(const SeismicLabAPI::SeismicLabSimulationData &Data, mat &dresult);

    static bool ComputeCPDValue(const  SeismicLabAPI::SeismicLabSimulationData& Data, const double& x, double& dValue);
    static bool ComputeCPDVectorX(const SeismicLabAPI::SeismicLabSimulationData &Data, vec &dVarVector, vec &dValVector) ;
    
    //kurtosis
    static bool ComputeKurtosisValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeKurtosisVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeKurtosisVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //peak factor
    static bool ComputePeakFactorValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputePeakFactorVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputePeakFactorVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //pdf
    static bool ComputePDFValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &x, double &dValue) ;
    static bool ComputePDFVectorX(const SeismicLabAPI::SeismicLabSimulationData &Data, vec &dVarVector, vec &dValVector) ;

    //shear velocity
    static bool ComputeShearVelocityOfFlowValue(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    static bool ComputeShearVelocityOfFlowVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeShearVelocityOfFlowVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    //skewness
    static bool ComputeSkewnessValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeSkewnessVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeSkewnessVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //standard deviation
    static bool ComputeStandardDeviationValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeStandardDeviationVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeStandardDeviationVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //variance
    static bool ComputeVarianceValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeVarianceVectorP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeVarianceVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    // wave passage effect
    static bool ComputeWavePassageEffectVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);
    static bool ComputeWavePassageEffectVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);
    static bool ComputeWavePassageEffectMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);
    static bool ComputeWavePassageEffectValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    static int getLocationIndex(const SeismicLabAPI::SeismicLabSimulationData &Data, Base::Vector3d locationTobeFound);
};

} //namespace SeismicLabAPI

#endif
