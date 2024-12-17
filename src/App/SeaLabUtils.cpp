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
#include "SeaLabUtils.h"



using namespace App;

//phenomenon
QString SeaLabUtils::rpsPhenomenonSeaSurface = QString::fromLatin1("Sea Surface");

// object groups
QString SeaLabUtils::objGroupLocationDistribution =  QString::fromLatin1("Location Distribution");
QString SeaLabUtils::objGroupMeanAcceleration =  QString::fromLatin1("Mean Acceleration");
QString SeaLabUtils::objGroupSpectrum =  QString::fromLatin1("Spectrum");
QString SeaLabUtils::objGroupSpectrumDecompositionMethod =  QString::fromLatin1("Spectrum Decomposition Method");
QString SeaLabUtils::objGroupCoherenceFunction =  QString::fromLatin1("Coherence Function");
QString SeaLabUtils::objGroupSimulationMethod =  QString::fromLatin1("Simulation Method");
QString SeaLabUtils::objGroupFrequencyDistribution =  QString::fromLatin1("Frequency Distribution");
QString SeaLabUtils::objGroupRandomnessProvider =  QString::fromLatin1("Randomness Provider");
QString SeaLabUtils::objGroupModulationFunction =  QString::fromLatin1("Modulation Function");
QString SeaLabUtils::objGroupCorrelationFunction =  QString::fromLatin1("Correlation Function");
QString SeaLabUtils::objGroupTableTool =  QString::fromLatin1("Table Tool");
QString SeaLabUtils::objGroupMatrixTool =  QString::fromLatin1("Matrix Tool");
QString SeaLabUtils::objGroupUserDefinedRPSObject =  QString::fromLatin1("User Defined RPS object");
QString SeaLabUtils::objGroupUserObject =  QString::fromLatin1("User Defined Phenomenon");
QString SeaLabUtils::objGroupCumulativeProbabilityDistribution =  QString::fromLatin1("Cumulative Probability Distribution");
QString SeaLabUtils::objGroupKurtosis =  QString::fromLatin1("Kurtosis");
QString SeaLabUtils::objGroupPeakFactor =  QString::fromLatin1("Peak Factor");
QString SeaLabUtils::objGroupProbabilityDensityFunction =  QString::fromLatin1("Probability Density Function");
QString SeaLabUtils::objGroupShearVelocityOfFlow =  QString::fromLatin1("Shear Velocity of Flow");
QString SeaLabUtils::objGroupSkewness =  QString::fromLatin1("Skewness");
QString SeaLabUtils::objGroupStandardDeviation =  QString::fromLatin1("Standard Deviation");
QString SeaLabUtils::objGroupVariance =  QString::fromLatin1("Variance");
QString SeaLabUtils::objGroupWavePassageEffect =  QString::fromLatin1("Wave Passage Effect");

QString SeaLabUtils::docRPSFeatures =  QString::fromLatin1("RPS Features");
QString SeaLabUtils::docSimulations =  QString::fromLatin1("Simulations");

QString SeaLabUtils::ComputeLocationCoordinateMatrixP3 = QString::fromLatin1("ComputeLocationCoordinateMatrixP3");

QString SeaLabUtils::ComputeCrossCoherenceValue = QString::fromLatin1("ComputeCrossCoherenceValue");
QString SeaLabUtils::ComputeCrossCoherenceVectorF =  QString::fromLatin1("ComputeCrossCoherenceVectorF");
QString SeaLabUtils::ComputeCrossCoherenceVectorT = QString::fromLatin1("ComputeCrossCoherenceVectorT");
QString SeaLabUtils::ComputeCrossCoherenceMatrixPP = QString::fromLatin1("ComputeCrossCoherenceMatrixPP");

QString SeaLabUtils::ComputeCPDValue = QString::fromLatin1("ComputeCPDValue");
QString SeaLabUtils::ComputeCPDVectorX = QString::fromLatin1("ComputeCPDVectorX");

QString SeaLabUtils::ComputeCrossCorrelationValue = QString::fromLatin1("ComputeCrossCorrelationValue");
QString SeaLabUtils::ComputeCrossCorrelationVectorT = QString::fromLatin1("ComputeCrossCorrelationVectorT");
QString SeaLabUtils::ComputeCrossCorrelationMatrixPP = QString::fromLatin1("ComputeCrossCorrelationMatrixPP");

QString SeaLabUtils::ComputeFrequencyValue = QString::fromLatin1("ComputeFrequencyValue");
QString SeaLabUtils::ComputeFrequenciesVectorF = QString::fromLatin1("ComputeFrequenciesVectorF");
QString SeaLabUtils::ComputeFrequenciesMatrixFP = QString::fromLatin1("ComputeFrequenciesMatrixFP");

QString SeaLabUtils::ComputeKurtosisValue = QString::fromLatin1("ComputeKurtosisValue");
QString SeaLabUtils::ComputeKurtosisVectorP = QString::fromLatin1("ComputeKurtosisVectorP");
QString SeaLabUtils::ComputeKurtosisVectorT = QString::fromLatin1("ComputeKurtosisVectorT");

QString SeaLabUtils::MatrixToolCompute = QString::fromLatin1("MatrixToolCompute");

QString SeaLabUtils::ComputeMeanAccelerationValue =  QString::fromLatin1("ComputeMeanAccelerationValue");
QString SeaLabUtils::ComputeMeanAccelerationVectorP =  QString::fromLatin1("ComputeMeanAccelerationVectorP");
QString SeaLabUtils::ComputeMeanAccelerationVectorT =  QString::fromLatin1("ComputeMeanAccelerationVectorT");

QString SeaLabUtils::ComputeModulationValue = QString::fromLatin1("ComputeModulationValue");
QString SeaLabUtils::ComputeModulationVectorP = QString::fromLatin1("ComputeModulationVectorP");
QString SeaLabUtils::ComputeModulationVectorT = QString::fromLatin1("ComputeModulationVectorT");
QString SeaLabUtils::ComputeModulationVectorF = QString::fromLatin1("ComputeModulationVectorF");

QString SeaLabUtils::ComputePeakFactorValue = QString::fromLatin1("ComputePeakFactorValue");
QString SeaLabUtils::ComputePeakFactorVectorP = QString::fromLatin1("ComputePeakFactorVectorP");
QString SeaLabUtils::ComputePeakFactorVectorT = QString::fromLatin1("ComputePeakFactorVectorT");

QString SeaLabUtils::ComputePDFValue = QString::fromLatin1("ComputePDFValue");
QString SeaLabUtils::ComputePDFVectorX = QString::fromLatin1("ComputePDFVectorX");

QString SeaLabUtils::ComputeDecomposedPSDValue = QString::fromLatin1("ComputeDecomposedPSDValue");
QString SeaLabUtils::ComputeDecomposedCrossSpectrumVectorF = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorF");
QString SeaLabUtils::ComputeDecomposedCrossSpectrumVectorT = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorT");
QString SeaLabUtils::ComputeDecomposedCrossSpectrumMatrixPP = QString::fromLatin1("ComputeDecomposedCrossSpectrumMatrixPP");

QString SeaLabUtils::ComputeRandomValue = QString::fromLatin1("ComputeRandomValue");
QString SeaLabUtils::GenerateRandomMatrixFP = QString::fromLatin1("GenerateRandomMatrixFP");
QString SeaLabUtils::GenerateRandomCubeFPS = QString::fromLatin1("GenerateRandomCubeFPS");

QString SeaLabUtils::ComputeShearVelocityOfFlowValue = QString::fromLatin1("ComputeShearVelocityOfFlowValue");
QString SeaLabUtils::ComputeShearVelocityOfFlowVectorT = QString::fromLatin1("ComputeShearVelocityOfFlowVectorT");
QString SeaLabUtils::ComputeShearVelocityOfFlowVectorP = QString::fromLatin1("ComputeShearVelocityOfFlowVectorP");

QString SeaLabUtils::Simulate = QString::fromLatin1("Simulate");
QString SeaLabUtils::SimulateInLargeScaleMode = QString::fromLatin1("SimulateInLargeScaleMode");

QString SeaLabUtils::ComputeSkewnessValue = QString::fromLatin1("ComputeSkewnessValue");
QString SeaLabUtils::ComputeSkewnessVectorP = QString::fromLatin1("ComputeSkewnessVectorP");
QString SeaLabUtils::ComputeSkewnessVectorT = QString::fromLatin1("ComputeSkewnessVectorT");

QString SeaLabUtils::ComputeStandardDeviationValue = QString::fromLatin1("ComputeStandardDeviationValue");
QString SeaLabUtils::ComputeStandardDeviationVectorP = QString::fromLatin1("ComputeStandardDeviationVectorP");
QString SeaLabUtils::ComputeStandardDeviationVectorT = QString::fromLatin1("ComputeStandardDeviationVectorT");

QString SeaLabUtils::TableToolCompute = QString::fromLatin1("TableToolCompute");

QString SeaLabUtils::UserDefinedRPSObjectCompute = QString::fromLatin1("UserDefinedRPSObjectCompute");

QString SeaLabUtils::ComputeVarianceValue = QString::fromLatin1("ComputeVarianceValue");
QString SeaLabUtils::ComputeVarianceVectorP = QString::fromLatin1("ComputeVarianceVectorP");
QString SeaLabUtils::ComputeVarianceVectorT = QString::fromLatin1("ComputeVarianceVectorT");


QString SeaLabUtils::ComputeWavePassageEffectValue = QString::fromLatin1("ComputeWavePassageEffectValue");
QString SeaLabUtils::ComputeWavePassageEffectVectorF = QString::fromLatin1("ComputeWavePassageEffectVectorF");
QString SeaLabUtils::ComputeWavePassageEffectVectorT = QString::fromLatin1("ComputeWavePassageEffectVectorT");
QString SeaLabUtils::ComputeWavePassageEffectMatrixPP = QString::fromLatin1("ComputeWavePassageEffectMatrixPP");

QString SeaLabUtils::ComputeCrossSpectrumValue = QString::fromLatin1("ComputeCrossSpectrumValue");
QString SeaLabUtils::ComputeCrossSpectrumVectorF = QString::fromLatin1("ComputeCrossSpectrumVectorF");
QString SeaLabUtils::ComputeCrossSpectrumVectorT = QString::fromLatin1("ComputeCrossSpectrumVectorT");
QString SeaLabUtils::ComputeCrossSpectrumMatrixPP = QString::fromLatin1("ComputeCrossSpectrumMatrixPP");
QString SeaLabUtils::ComputeAutoSpectrumValue = QString::fromLatin1("ComputeAutoSpectrumValue");
QString SeaLabUtils::ComputeAutoSpectrumVectorF = QString::fromLatin1("ComputeAutoSpectrumVectorF");
QString SeaLabUtils::ComputeAutoSpectrumVectorT = QString::fromLatin1("ComputeAutoSpectrumVectorT");


