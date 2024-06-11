/***************************************************************************
 *   Copyright (c) 2016 Victor Titov (DeepSOIC) <vv.titov@gmail.com>       *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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

/**
  * AttacherTexts.h, .cpp - files that contain user-friendly translatable names
  * of attachment modes, as well as help texts, and the like.
  */

#ifndef WINDLABFRAMEWORKPYTHON
#define WINDLABFRAMEWORKPYTHON

#include <Mod/WindLab/WindLabGlobal.h>
#include <CXX/Objects.hxx>

namespace WindLab
{
// Python interface
class WindLabExport WindLabFrameworkPython
{
public:
    static PyObject* returnResult1(vec& dVarVector, vec& dValVector);
    static PyObject* returnResult2(vec& dVarVector, cx_vec& dValVector);
    static PyObject* returnResult3(cx_mat& resArray, std::string featureName, const char* displayOption);
    static PyObject* returnResult4(mat& resArray);
    static PyObject* returnResult5(std::complex<double>& resValue);
    static PyObject* returnResult6(double resValue);

public:
    static PyMethodDef    Methods[];

    // coherence function
    static PyObject* ComputeCrossCoherenceVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeCrossCoherenceVectorT(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeCrossCoherenceMatrixPP(PyObject* /*self*/, PyObject* args);

	// correlation function
	
    static PyObject* ComputeCrossCorrelationVectorT(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeCrossCorrelationMatrixPP(PyObject* /*self*/, PyObject* args);

   // frequency
    static PyObject* ComputeFrequenciesVectorF(PyObject* /*self*/, PyObject* args);
  
    static PyObject* ComputeFrequenciesMatrixFP(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeLocationCoordinateMatrixP3(PyObject* /*self*/, PyObject* args);

	// mean wind speed
    static PyObject* ComputeMeanWindSpeedVectorP(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeMeanWindSpeedVectorT(PyObject* /*self*/, PyObject* args);

	// modulation function
    static PyObject* ComputeModulationVectorT(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeModulationVectorP(PyObject* /*self*/, PyObject* args);

	// psd decomposition
    static PyObject* ComputeDecomposedCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeDecomposedCrossSpectrumVectorT(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeDecomposedCrossSpectrumMatrixPP(PyObject* /*self*/, PyObject* args);

	// randomness
    static PyObject* GenerateRandomMatrixFP(PyObject* /*self*/, PyObject* args);

	// X spectrum

    static PyObject* ComputeXCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeXCrossSpectrumVectorT(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeXCrossSpectrumMatrixPP(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeXAutoSpectrumValue(PyObject* /*self*/, PyObject* args);
    
    static PyObject* ComputeXAutoSpectrumVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeXAutoSpectrumVectorT(PyObject* /*self*/, PyObject* args);

	// Y spectrum
    static PyObject* ComputeYCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeYCrossSpectrumVectorT(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeYCrossSpectrumMatrixPP(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeYAutoSpectrumValue(PyObject* /*self*/, PyObject* args);
    
    static PyObject* ComputeYAutoSpectrumVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeYAutoSpectrumVectorT(PyObject* /*self*/, PyObject* args);

	// Z spectrum
    static PyObject* ComputeZCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeZCrossSpectrumVectorT(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeZCrossSpectrumMatrixPP(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeZAutoSpectrumValue(PyObject* /*self*/, PyObject* args);
    
    static PyObject* ComputeZAutoSpectrumVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeZAutoSpectrumVectorT(PyObject* /*self*/, PyObject* args);

	// spectrum X, Y, Z
    static PyObject* ComputeCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeCrossSpectrumVectorT(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeCrossSpectrumMatrixPP(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeAutoSpectrumValue(PyObject* /*self*/, PyObject* args);
    
    static PyObject* ComputeAutoSpectrumVectorF(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeAutoSpectrumVectorT(PyObject* /*self*/, PyObject* args);

	/////
    static PyObject* ComputeCrossCoherenceValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeCrossCorrelationValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeMeanWindSpeedValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeModulationValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeRandomValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeXCrossSpectrumValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeYCrossSpectrumValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeZCrossSpectrumValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeCrossSpectrumValue(PyObject* /*self*/, PyObject* args);
	static PyObject* ComputeFrequencyValue(PyObject* /*self*/, PyObject* args);

	static PyObject* getSpatialDistributionObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getMeanProfilObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getAlongWindSpectrumObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getVerticalWindSpectrumObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getAcrossWindSpectrumObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getDecomposedSpectrumObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getCoherenceFunctionObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getSimulationMethodObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getFrequencyDistributionObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getRandomnessProviderObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getModulationFunctionObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getCorrelationFunctionObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getTableToolObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getMatrixToolObjDescription(PyObject* /*self*/, PyObject* args);
	static PyObject* getUserDefinedRPSObjDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getCDFDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getGustFactorDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getKurtosisDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getPeakFactorDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getPDFDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getRoughnessDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getShearVelocityOfFlowDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getSkewnessDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getStandardDeviationDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getTurbulenceIntensityDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getTurbulenceScaleDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getVarianceDescription(PyObject* /*self*/, PyObject* args);
    static PyObject* getWavePassageEffectDescription(PyObject* /*self*/, PyObject* args);

    static PyObject* TableToolCompute(PyObject* /*self*/, PyObject* args);
    static PyObject* MatrixToolCompute(PyObject* /*self*/, PyObject* args);
    static PyObject* UserDefinedRPSObjectCompute(PyObject* /*self*/, PyObject* args);

    static PyObject* ComputeCPDValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeCPDVectorX(PyObject* /*self*/, PyObject* args) ;
    
    //gust factor
    static PyObject* ComputeGustFactorValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeGustFactorVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeGustFactorVectorT(PyObject* /*self*/, PyObject* args);

    //kurtosis
    static PyObject* ComputeKurtosisValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeKurtosisVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeKurtosisVectorT(PyObject* /*self*/, PyObject* args);

    //peak factor
    static PyObject* ComputePeakFactorValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputePeakFactorVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputePeakFactorVectorT(PyObject* /*self*/, PyObject* args);

    //pdf
    static PyObject* ComputePDFValue(PyObject* /*self*/, PyObject* args) ;
    static PyObject* ComputePDFVectorX(PyObject* /*self*/, PyObject* args) ;

    //roughness
    static PyObject* ComputeRoughnessValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeRoughnessVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeRoughnessVectorT(PyObject* /*self*/, PyObject* args);

    //shear velocity
    static PyObject* ComputeShearVelocityOfFlowValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeShearVelocityOfFlowVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeShearVelocityOfFlowVectorT(PyObject* /*self*/, PyObject* args);

    //skewness
    static PyObject* ComputeSkewnessValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeSkewnessVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeSkewnessVectorT(PyObject* /*self*/, PyObject* args);

    //standard deviation
    static PyObject* ComputeStandardDeviationValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeStandardDeviationVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeStandardDeviationVectorT(PyObject* /*self*/, PyObject* args);

    //turbulence intensity
    static PyObject* ComputeTurbulenceIntensityValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeTurbulenceIntensityVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeTurbulenceIntensityVectorT(PyObject* /*self*/, PyObject* args);

    //turbulence scale
    static PyObject* ComputeTurbulenceScaleValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeTurbulenceScaleVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeTurbulenceScaleVectorT(PyObject* /*self*/, PyObject* args);

    //variance
    static PyObject* ComputeVarianceValue(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeVarianceVectorP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeVarianceVectorT(PyObject* /*self*/, PyObject* args);

    // wave passage effect
    static PyObject* ComputeWavePassageEffectVectorF(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeWavePassageEffectVectorT(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeWavePassageEffectMatrixPP(PyObject* /*self*/, PyObject* args);
    static PyObject* ComputeWavePassageEffectValue(PyObject* /*self*/, PyObject* args);
    static PyObject* getLocationIndex(PyObject* /*self*/, PyObject* args);


};

} 
#endif // WINDLABFRAMEWORKPYTHON