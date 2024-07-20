/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>         *
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


#include "PreCompiled.h"
#include "WindLabUtils.h"



using namespace App;

//phenomenon
QString WindLabUtils::rpsPhenomenonWindVelocity = QString::fromLatin1("Wind Velocity");

// object groups
QString WindLabUtils::objGroupLocationDistribution =  QString::fromLatin1("Location Distribution");
QString WindLabUtils::objGroupMeanWindProfile =  QString::fromLatin1("Mean Wind Profile");
QString WindLabUtils::objGroupAlongWindSpectrum =  QString::fromLatin1("Along Wind Spectrum");
QString WindLabUtils::objGroupVerticalWindSpectrum =  QString::fromLatin1("Vertical Wind Spectrum");
QString WindLabUtils::objGroupAcrossWindSpectrum =  QString::fromLatin1("Across Wind Spectrum");
QString WindLabUtils::objGroupSpectrumDecompositionMethod =  QString::fromLatin1("Spectrum Decomposition Method");
QString WindLabUtils::objGroupCoherenceFunction =  QString::fromLatin1("Coherence Function");
QString WindLabUtils::objGroupSimulationMethod =  QString::fromLatin1("Simulation Method");
QString WindLabUtils::objGroupFrequencyDistribution =  QString::fromLatin1("Frequency Distribution");
QString WindLabUtils::objGroupRandomnessProvider =  QString::fromLatin1("Randomness Provider");
QString WindLabUtils::objGroupModulationFunction =  QString::fromLatin1("Modulation Function");
QString WindLabUtils::objGroupCorrelationFunction =  QString::fromLatin1("Correlation Function");
QString WindLabUtils::objGroupTableTool =  QString::fromLatin1("Table Tool");
QString WindLabUtils::objGroupMatrixTool =  QString::fromLatin1("Matrix Tool");
QString WindLabUtils::objGroupUserDefinedRPSObject =  QString::fromLatin1("User Defined RPS object");
QString WindLabUtils::objGroupUserDefinedPhenomenonObject =  QString::fromLatin1("User Defined Phenomenon");
QString WindLabUtils::objGroupCumulativeProbabilityDistribution =  QString::fromLatin1("Cumulative Probability Distribution");
QString WindLabUtils::objGroupGustFactor =  QString::fromLatin1("Gust Factor");
QString WindLabUtils::objGroupKurtosis =  QString::fromLatin1("Kurtosis");
QString WindLabUtils::objGroupPeakFactor =  QString::fromLatin1("Peak Factor");
QString WindLabUtils::objGroupProbabilityDensityFunction =  QString::fromLatin1("Probability Density Function");
QString WindLabUtils::objGroupRoughness =  QString::fromLatin1("Roughness");
QString WindLabUtils::objGroupShearVelocityOfFlow =  QString::fromLatin1("Shear Velocity of Flow");
QString WindLabUtils::objGroupSkewness =  QString::fromLatin1("Skewness");
QString WindLabUtils::objGroupStandardDeviation =  QString::fromLatin1("Standard Deviation");
QString WindLabUtils::objGroupTurbulenceIntensity =  QString::fromLatin1("Turbulence Intensity");
QString WindLabUtils::objGroupTurbulenceScale =  QString::fromLatin1("Turbulence Scale");
QString WindLabUtils::objGroupVariance =  QString::fromLatin1("Variance");
QString WindLabUtils::objGroupWavePassageEffect =  QString::fromLatin1("Wave Passage Effect");

QString WindLabUtils::docRPSFeatures =  QString::fromLatin1("RPS Features");
QString WindLabUtils::docSimulations =  QString::fromLatin1("Simulations");


 
QString WindLabUtils::ComputeLocationCoordinateMatrixP3 = QString::fromLatin1("ComputeLocationCoordinateMatrixP3");

QString WindLabUtils::ComputeCrossCoherenceValue = QString::fromLatin1("ComputeCrossCoherenceValue");
QString WindLabUtils::ComputeCrossCoherenceVectorF =  QString::fromLatin1("ComputeCrossCoherenceVectorF");
QString WindLabUtils::ComputeCrossCoherenceVectorT = QString::fromLatin1("ComputeCrossCoherenceVectorT");
QString WindLabUtils::ComputeCrossCoherenceMatrixPP = QString::fromLatin1("ComputeCrossCoherenceMatrixPP");

QString WindLabUtils::ComputeCPDValue = QString::fromLatin1("ComputeCPDValue");
QString WindLabUtils::ComputeCPDVectorX = QString::fromLatin1("ComputeCPDVectorX");

QString WindLabUtils::ComputeCrossCorrelationValue = QString::fromLatin1("ComputeCrossCorrelationValue");
QString WindLabUtils::ComputeCrossCorrelationVectorT = QString::fromLatin1("ComputeCrossCorrelationVectorT");
QString WindLabUtils::ComputeCrossCorrelationMatrixPP = QString::fromLatin1("ComputeCrossCorrelationMatrixPP");

QString WindLabUtils::ComputeFrequencyValue = QString::fromLatin1("ComputeFrequencyValue");
QString WindLabUtils::ComputeFrequenciesVectorF = QString::fromLatin1("ComputeFrequenciesVectorF");
QString WindLabUtils::ComputeFrequenciesMatrixFP = QString::fromLatin1("ComputeFrequenciesMatrixFP");

QString WindLabUtils::ComputeGustFactorValue = QString::fromLatin1("ComputeGustFactorValue");
QString WindLabUtils::ComputeGustFactorVectorP = QString::fromLatin1("ComputeGustFactorVectorP");
QString WindLabUtils::ComputeGustFactorVectorT = QString::fromLatin1("ComputeGustFactorVectorT");

QString WindLabUtils::ComputeKurtosisValue = QString::fromLatin1("ComputeKurtosisValue");
QString WindLabUtils::ComputeKurtosisVectorP = QString::fromLatin1("ComputeKurtosisVectorP");
QString WindLabUtils::ComputeKurtosisVectorT = QString::fromLatin1("ComputeKurtosisVectorT");

QString WindLabUtils::MatrixToolCompute = QString::fromLatin1("MatrixToolCompute");

QString WindLabUtils::ComputeMeanWindSpeedValue =  QString::fromLatin1("ComputeMeanWindSpeedValue");
QString WindLabUtils::ComputeMeanWindSpeedVectorP =  QString::fromLatin1("ComputeMeanWindSpeedVectorP");
QString WindLabUtils::ComputeMeanWindSpeedVectorT =  QString::fromLatin1("ComputeMeanWindSpeedVectorT");

QString WindLabUtils::ComputeModulationValue = QString::fromLatin1("ComputeModulationValue");
QString WindLabUtils::ComputeModulationVectorP = QString::fromLatin1("ComputeModulationVectorP");
QString WindLabUtils::ComputeModulationVectorT = QString::fromLatin1("ComputeModulationVectorT");

QString WindLabUtils::ComputePeakFactorValue = QString::fromLatin1("ComputePeakFactorValue");
QString WindLabUtils::ComputePeakFactorVectorP = QString::fromLatin1("ComputePeakFactorVectorP");
QString WindLabUtils::ComputePeakFactorVectorT = QString::fromLatin1("ComputePeakFactorVectorT");

QString WindLabUtils::ComputePDFValue = QString::fromLatin1("ComputePDFValue");
QString WindLabUtils::ComputePDFVectorX = QString::fromLatin1("ComputePDFVectorX");

QString WindLabUtils::ComputeDecomposedPSDValue = QString::fromLatin1("ComputeDecomposedPSDValue");
QString WindLabUtils::ComputeDecomposedCrossSpectrumVectorF = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorF");
QString WindLabUtils::ComputeDecomposedCrossSpectrumVectorT = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorT");
QString WindLabUtils::ComputeDecomposedCrossSpectrumMatrixPP = QString::fromLatin1("ComputeDecomposedCrossSpectrumMatrixPP");

QString WindLabUtils::ComputeRandomValue = QString::fromLatin1("ComputeRandomValue");
QString WindLabUtils::GenerateRandomMatrixFP = QString::fromLatin1("GenerateRandomMatrixFP");

QString WindLabUtils::ComputeRoughnessValue = QString::fromLatin1("ComputeRoughnessValue");
QString WindLabUtils::ComputeRoughnessVectorP = QString::fromLatin1("ComputeRoughnessVectorP");
QString WindLabUtils::ComputeRoughnessVectorT = QString::fromLatin1("ComputeRoughnessVectorT");

QString WindLabUtils::ComputeShearVelocityOfFlowValue = QString::fromLatin1("ComputeShearVelocityOfFlowValue");
QString WindLabUtils::ComputeShearVelocityOfFlowVectorT = QString::fromLatin1("ComputeShearVelocityOfFlowVectorT");
QString WindLabUtils::ComputeShearVelocityOfFlowVectorP = QString::fromLatin1("ComputeShearVelocityOfFlowVectorP");

QString WindLabUtils::Simulate = QString::fromLatin1("Simulate");
QString WindLabUtils::SimulateInLargeScaleMode = QString::fromLatin1("SimulateInLargeScaleMode");

QString WindLabUtils::ComputeSkewnessValue = QString::fromLatin1("ComputeSkewnessValue");
QString WindLabUtils::ComputeSkewnessVectorP = QString::fromLatin1("ComputeSkewnessVectorP");
QString WindLabUtils::ComputeSkewnessVectorT = QString::fromLatin1("ComputeSkewnessVectorT");

QString WindLabUtils::ComputeStandardDeviationValue = QString::fromLatin1("ComputeStandardDeviationValue");
QString WindLabUtils::ComputeStandardDeviationVectorP = QString::fromLatin1("ComputeStandardDeviationVectorP");
QString WindLabUtils::ComputeStandardDeviationVectorT = QString::fromLatin1("ComputeStandardDeviationVectorT");

QString WindLabUtils::TableToolCompute = QString::fromLatin1("TableToolCompute");

QString WindLabUtils::ComputeTurbulenceIntensityValue = QString::fromLatin1("ComputeTurbulenceIntensityValue");
QString WindLabUtils::ComputeTurbulenceIntensityVectorP = QString::fromLatin1("ComputeTurbulenceIntensityVectorP");
QString WindLabUtils::ComputeTurbulenceIntensityVectorT = QString::fromLatin1("ComputeTurbulenceIntensityVectorT");

QString WindLabUtils::ComputeTurbulenceScaleValue = QString::fromLatin1("ComputeTurbulenceScaleValue");
QString WindLabUtils::ComputeTurbulenceScaleVectorP = QString::fromLatin1("ComputeTurbulenceScaleVectorP");
QString WindLabUtils::ComputeTurbulenceScaleVectorT = QString::fromLatin1("ComputeTurbulenceScaleVectorT");

QString WindLabUtils::UserDefinedRPSObjectCompute = QString::fromLatin1("UserDefinedRPSObjectCompute");

QString WindLabUtils::ComputeVarianceValue = QString::fromLatin1("ComputeVarianceValue");
QString WindLabUtils::ComputeVarianceVectorP = QString::fromLatin1("ComputeVarianceVectorP");
QString WindLabUtils::ComputeVarianceVectorT = QString::fromLatin1("ComputeVarianceVectorT");


QString WindLabUtils::ComputeWavePassageEffectValue = QString::fromLatin1("ComputeWavePassageEffectValue");
QString WindLabUtils::ComputeWavePassageEffectVectorF = QString::fromLatin1("ComputeWavePassageEffectVectorF");
QString WindLabUtils::ComputeWavePassageEffectVectorT = QString::fromLatin1("ComputeWavePassageEffectVectorT");
QString WindLabUtils::ComputeWavePassageEffectMatrixPP = QString::fromLatin1("ComputeWavePassageEffectMatrixPP");

QString WindLabUtils::ComputeXCrossSpectrumValue = QString::fromLatin1("ComputeXCrossSpectrumValue");
QString WindLabUtils::ComputeXCrossSpectrumVectorF = QString::fromLatin1("ComputeXCrossSpectrumVectorF");
QString WindLabUtils::ComputeXCrossSpectrumVectorT = QString::fromLatin1("ComputeXCrossSpectrumVectorT");
QString WindLabUtils::ComputeXCrossSpectrumMatrixPP = QString::fromLatin1("ComputeXCrossSpectrumMatrixPP");
QString WindLabUtils::ComputeXAutoSpectrumValue = QString::fromLatin1("ComputeXAutoSpectrumValue");
QString WindLabUtils::ComputeXAutoSpectrumVectorF = QString::fromLatin1("ComputeXAutoSpectrumVectorF");
QString WindLabUtils::ComputeXAutoSpectrumVectorT = QString::fromLatin1("ComputeXAutoSpectrumVectorT");

QString WindLabUtils::ComputeYCrossSpectrumValue = QString::fromLatin1("ComputeYCrossSpectrumValue");
QString WindLabUtils::ComputeYCrossSpectrumVectorF = QString::fromLatin1("ComputeYCrossSpectrumVectorF");
QString WindLabUtils::ComputeYCrossSpectrumVectorT = QString::fromLatin1("ComputeYCrossSpectrumVectorT");
QString WindLabUtils::ComputeYCrossSpectrumMatrixPP = QString::fromLatin1("ComputeYCrossSpectrumMatrixPP");
QString WindLabUtils::ComputeYAutoSpectrumValue = QString::fromLatin1("ComputeYAutoSpectrumValue");
QString WindLabUtils::ComputeYAutoSpectrumVectorF = QString::fromLatin1("ComputeYAutoSpectrumVectorF");
QString WindLabUtils::ComputeYAutoSpectrumVectorT = QString::fromLatin1("ComputeYAutoSpectrumVectorT");

QString WindLabUtils::ComputeZCrossSpectrumValue = QString::fromLatin1("ComputeZCrossSpectrumValue");
QString WindLabUtils::ComputeZCrossSpectrumVectorF = QString::fromLatin1("ComputeZCrossSpectrumVectorF");
QString WindLabUtils::ComputeZCrossSpectrumVectorT = QString::fromLatin1("ComputeZCrossSpectrumVectorT");
QString WindLabUtils::ComputeZCrossSpectrumMatrixPP = QString::fromLatin1("ComputeZCrossSpectrumMatrixPP");
QString WindLabUtils::ComputeZAutoSpectrumValue = QString::fromLatin1("ComputeZAutoSpectrumValue");
QString WindLabUtils::ComputeZAutoSpectrumVectorF = QString::fromLatin1("ComputeZAutoSpectrumVectorF");
QString WindLabUtils::ComputeZAutoSpectrumVectorT = QString::fromLatin1("ComputeZAutoSpectrumVectorT");

