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

#ifndef RPSWINDLABFRAMEWORK_H
#define RPSWINDLABFRAMEWORK_H

#include "RPSWindLabAPIdefines.h"
#include <Mod/WindLabAPI/App/WindLabSimuData.h>
#include <Mod/WindLabAPI/App/WindLabFeatureDescription.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {


class RPS_CORE_API CRPSWindLabFramework
{
public:
	CRPSWindLabFramework();
	~CRPSWindLabFramework();

	// coherence function
    static bool ComputeCrossCoherenceVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossCoherenceVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossCoherenceMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

	// correlation function
	
    static bool ComputeCrossCorrelationVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector);

    static bool ComputeCrossCorrelationMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, mat &dCorrelationMatrix);

   // frequency
    static bool ComputeFrequenciesVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dValVector);
  
    static bool ComputeFrequenciesMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat& dMatrix);

    static bool ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat& dLocCoord);

	// mean wind speed
    static bool ComputeMeanWindSpeedVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    static bool ComputeMeanWindSpeedVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

	// modulation function
    static bool ComputeModulationVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    static bool ComputeModulationVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

	// psd decomposition
    static bool ComputeDecomposedCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeDecomposedCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeDecomposedCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix);

	// randomness
    static bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData &Data, mat &dRandomValueArray);

	// X spectrum

    static bool ComputeXCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeXCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeXCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    static bool ComputeXAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    static bool ComputeXAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    static bool ComputeXAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

	// Y spectrum
    static bool ComputeYCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeYCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeYCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    static bool ComputeYAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    static bool ComputeYAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    static bool ComputeYAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

	// Z spectrum
    static bool ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    static bool ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    static bool ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    static bool ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

	// spectrum X, Y, Z
    static bool ComputeCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    static bool ComputeCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix);

    static bool ComputeAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    static bool ComputeAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    static bool ComputeAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

	/////
    static bool ComputeCrossCoherenceValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);
    static bool ComputeCrossCorrelationValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue);
    static bool ComputeMeanWindSpeedValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    static bool ComputeModulationValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    static bool ComputeRandomValue(const WindLabAPI::WindLabSimuData &Data, double &dValue);
    static bool ComputeXCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);
    static bool ComputeYCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);
    static bool ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);
    static bool ComputeCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);
	static bool ComputeFrequencyValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

	static WindLabAPI::WindLabFeatureDescription* getWindLabFeatureDescription(const std::string& name);
	
    static bool TableToolCompute(const WindLabAPI::WindLabSimuData &Data, const mat &inputTable, mat &outputTable);
    static bool MatrixToolCompute(const WindLabAPI::WindLabSimuData &Data, const mat &inputMatrix, mat &outputMatrix);
    static bool UserDefinedRPSObjectCompute(const WindLabAPI::WindLabSimuData &Data, mat &dresult);

    static bool ComputeCPDValue(const  WindLabAPI::WindLabSimuData& Data, const double& x, double& dValue);
    static bool ComputeCPDVectorX(const WindLabAPI::WindLabSimuData &Data, vec &dVarVector, vec &dValVector) ;
    
    //gust factor
    static bool ComputeGustFactorValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeGustFactorVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeGustFactorVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //kurtosis
    static bool ComputeKurtosisValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeKurtosisVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeKurtosisVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //peak factor
    static bool ComputePeakFactorValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputePeakFactorVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputePeakFactorVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //pdf
    static bool ComputePDFValue(const WindLabAPI::WindLabSimuData &Data, const double &x, double &dValue) ;
    static bool ComputePDFVectorX(const WindLabAPI::WindLabSimuData &Data, vec &dVarVector, vec &dValVector) ;

    //roughness
    static bool ComputeRoughnessValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeRoughnessVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeRoughnessVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //shear velocity
    static bool ComputeShearVelocityOfFlowValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue);
    static bool ComputeShearVelocityOfFlowVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeShearVelocityOfFlowVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    //skewness
    static bool ComputeSkewnessValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeSkewnessVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeSkewnessVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //standard deviation
    static bool ComputeStandardDeviationValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeStandardDeviationVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeStandardDeviationVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //turbulence intensity
    static bool ComputeTurbulenceIntensityValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeTurbulenceIntensityVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeTurbulenceIntensityVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //turbulence scale
    static bool ComputeTurbulenceScaleValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeTurbulenceScaleVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeTurbulenceScaleVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    //variance
    static bool ComputeVarianceValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);
    static bool ComputeVarianceVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);
    static bool ComputeVarianceVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    // wave passage effect
    static bool ComputeWavePassageEffectVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);
    static bool ComputeWavePassageEffectVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);
    static bool ComputeWavePassageEffectMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);
    static bool ComputeWavePassageEffectValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    static int getLocationIndex(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d locationTobeFound);
};

} //namespace WindLabAPI

#endif
