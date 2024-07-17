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

#include "SeismicLabUtils.h"
#include <QDateTime>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QSysInfo>
#include <cmath>

#ifdef Q_OS_WIN
#include <assert.h>
#include <windows.h>
#endif


using namespace App;

//phenomenon
QString SeismicLabUtils::rpsPhenomenonGroundMotion = QString::fromLatin1("Seismic Ground Motion");

// object groups
QString SeismicLabUtils::objGroupLocationDistribution =  QString::fromLatin1("Location Distribution");
QString SeismicLabUtils::objGroupMeanAcceleration =  QString::fromLatin1("Mean Acceleration");
QString SeismicLabUtils::objGroupSpectrum =  QString::fromLatin1("Spectrum");
QString SeismicLabUtils::objGroupSpectrumDecompositionMethod =  QString::fromLatin1("Spectrum Decomposition Method");
QString SeismicLabUtils::objGroupCoherenceFunction =  QString::fromLatin1("Coherence Function");
QString SeismicLabUtils::objGroupSimulationMethod =  QString::fromLatin1("Simulation Method");
QString SeismicLabUtils::objGroupFrequencyDistribution =  QString::fromLatin1("Frequency Distribution");
QString SeismicLabUtils::objGroupRandomnessProvider =  QString::fromLatin1("Randomness Provider");
QString SeismicLabUtils::objGroupModulationFunction =  QString::fromLatin1("Modulation Function");
QString SeismicLabUtils::objGroupCorrelationFunction =  QString::fromLatin1("Correlation Function");
QString SeismicLabUtils::objGroupTableTool =  QString::fromLatin1("Table Tool");
QString SeismicLabUtils::objGroupMatrixTool =  QString::fromLatin1("Matrix Tool");
QString SeismicLabUtils::objGroupUserDefinedRPSObject =  QString::fromLatin1("User Defined RPS object");
QString SeismicLabUtils::objGroupUserDefinedPhenomenonObject =  QString::fromLatin1("User Defined Phenomenon");
QString SeismicLabUtils::objGroupCumulativeProbabilityDistribution =  QString::fromLatin1("Cumulative Probability Distribution");
QString SeismicLabUtils::objGroupKurtosis =  QString::fromLatin1("Kurtosis");
QString SeismicLabUtils::objGroupPeakFactor =  QString::fromLatin1("Peak Factor");
QString SeismicLabUtils::objGroupProbabilityDensityFunction =  QString::fromLatin1("Probability Density Function");
QString SeismicLabUtils::objGroupShearVelocityOfFlow =  QString::fromLatin1("Shear Velocity of Flow");
QString SeismicLabUtils::objGroupSkewness =  QString::fromLatin1("Skewness");
QString SeismicLabUtils::objGroupStandardDeviation =  QString::fromLatin1("Standard Deviation");
QString SeismicLabUtils::objGroupVariance =  QString::fromLatin1("Variance");
QString SeismicLabUtils::objGroupWavePassageEffect =  QString::fromLatin1("Wave Passage Effect");

QString SeismicLabUtils::docRPSFeatures =  QString::fromLatin1("RPS Features");
QString SeismicLabUtils::docSimulations =  QString::fromLatin1("Simulations");

QString SeismicLabUtils::ComputeLocationCoordinateMatrixP3 = QString::fromLatin1("ComputeLocationCoordinateMatrixP3");

QString SeismicLabUtils::ComputeCrossCoherenceValue = QString::fromLatin1("ComputeCrossCoherenceValue");
QString SeismicLabUtils::ComputeCrossCoherenceVectorF =  QString::fromLatin1("ComputeCrossCoherenceVectorF");
QString SeismicLabUtils::ComputeCrossCoherenceVectorT = QString::fromLatin1("ComputeCrossCoherenceVectorT");
QString SeismicLabUtils::ComputeCrossCoherenceMatrixPP = QString::fromLatin1("ComputeCrossCoherenceMatrixPP");

QString SeismicLabUtils::ComputeCPDValue = QString::fromLatin1("ComputeCPDValue");
QString SeismicLabUtils::ComputeCPDVectorX = QString::fromLatin1("ComputeCPDVectorX");

QString SeismicLabUtils::ComputeCrossCorrelationValue = QString::fromLatin1("ComputeCrossCorrelationValue");
QString SeismicLabUtils::ComputeCrossCorrelationVectorT = QString::fromLatin1("ComputeCrossCorrelationVectorT");
QString SeismicLabUtils::ComputeCrossCorrelationMatrixPP = QString::fromLatin1("ComputeCrossCorrelationMatrixPP");

QString SeismicLabUtils::ComputeFrequencyValue = QString::fromLatin1("ComputeFrequencyValue");
QString SeismicLabUtils::ComputeFrequenciesVectorF = QString::fromLatin1("ComputeFrequenciesVectorF");
QString SeismicLabUtils::ComputeFrequenciesMatrixFP = QString::fromLatin1("ComputeFrequenciesMatrixFP");

QString SeismicLabUtils::ComputeKurtosisValue = QString::fromLatin1("ComputeKurtosisValue");
QString SeismicLabUtils::ComputeKurtosisVectorP = QString::fromLatin1("ComputeKurtosisVectorP");
QString SeismicLabUtils::ComputeKurtosisVectorT = QString::fromLatin1("ComputeKurtosisVectorT");

QString SeismicLabUtils::MatrixToolCompute = QString::fromLatin1("MatrixToolCompute");

QString SeismicLabUtils::ComputeMeanAccelerationValue =  QString::fromLatin1("ComputeMeanAccelerationValue");
QString SeismicLabUtils::ComputeMeanAccelerationVectorP =  QString::fromLatin1("ComputeMeanAccelerationVectorP");
QString SeismicLabUtils::ComputeMeanAccelerationVectorT =  QString::fromLatin1("ComputeMeanAccelerationVectorT");

QString SeismicLabUtils::ComputeModulationValue = QString::fromLatin1("ComputeModulationValue");
QString SeismicLabUtils::ComputeModulationVectorP = QString::fromLatin1("ComputeModulationVectorP");
QString SeismicLabUtils::ComputeModulationVectorT = QString::fromLatin1("ComputeModulationVectorT");

QString SeismicLabUtils::ComputePeakFactorValue = QString::fromLatin1("ComputePeakFactorValue");
QString SeismicLabUtils::ComputePeakFactorVectorP = QString::fromLatin1("ComputePeakFactorVectorP");
QString SeismicLabUtils::ComputePeakFactorVectorT = QString::fromLatin1("ComputePeakFactorVectorT");

QString SeismicLabUtils::ComputePDFValue = QString::fromLatin1("ComputePDFValue");
QString SeismicLabUtils::ComputePDFVectorX = QString::fromLatin1("ComputePDFVectorX");

QString SeismicLabUtils::ComputeDecomposedPSDValue = QString::fromLatin1("ComputeDecomposedPSDValue");
QString SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorF = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorF");
QString SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorT = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorT");
QString SeismicLabUtils::ComputeDecomposedCrossSpectrumMatrixPP = QString::fromLatin1("ComputeDecomposedCrossSpectrumMatrixPP");

QString SeismicLabUtils::ComputeRandomValue = QString::fromLatin1("ComputeRandomValue");
QString SeismicLabUtils::GenerateRandomMatrixFP = QString::fromLatin1("GenerateRandomMatrixFP");

QString SeismicLabUtils::ComputeShearVelocityOfFlowValue = QString::fromLatin1("ComputeShearVelocityOfFlowValue");
QString SeismicLabUtils::ComputeShearVelocityOfFlowVectorT = QString::fromLatin1("ComputeShearVelocityOfFlowVectorT");
QString SeismicLabUtils::ComputeShearVelocityOfFlowVectorP = QString::fromLatin1("ComputeShearVelocityOfFlowVectorP");

QString SeismicLabUtils::Simulate = QString::fromLatin1("Simulate");
QString SeismicLabUtils::SimulateInLargeScaleMode = QString::fromLatin1("SimulateInLargeScaleMode");

QString SeismicLabUtils::ComputeSkewnessValue = QString::fromLatin1("ComputeSkewnessValue");
QString SeismicLabUtils::ComputeSkewnessVectorP = QString::fromLatin1("ComputeSkewnessVectorP");
QString SeismicLabUtils::ComputeSkewnessVectorT = QString::fromLatin1("ComputeSkewnessVectorT");

QString SeismicLabUtils::ComputeStandardDeviationValue = QString::fromLatin1("ComputeStandardDeviationValue");
QString SeismicLabUtils::ComputeStandardDeviationVectorP = QString::fromLatin1("ComputeStandardDeviationVectorP");
QString SeismicLabUtils::ComputeStandardDeviationVectorT = QString::fromLatin1("ComputeStandardDeviationVectorT");

QString SeismicLabUtils::TableToolCompute = QString::fromLatin1("TableToolCompute");

QString SeismicLabUtils::UserDefinedRPSObjectCompute = QString::fromLatin1("UserDefinedRPSObjectCompute");

QString SeismicLabUtils::ComputeVarianceValue = QString::fromLatin1("ComputeVarianceValue");
QString SeismicLabUtils::ComputeVarianceVectorP = QString::fromLatin1("ComputeVarianceVectorP");
QString SeismicLabUtils::ComputeVarianceVectorT = QString::fromLatin1("ComputeVarianceVectorT");


QString SeismicLabUtils::ComputeWavePassageEffectValue = QString::fromLatin1("ComputeWavePassageEffectValue");
QString SeismicLabUtils::ComputeWavePassageEffectVectorF = QString::fromLatin1("ComputeWavePassageEffectVectorF");
QString SeismicLabUtils::ComputeWavePassageEffectVectorT = QString::fromLatin1("ComputeWavePassageEffectVectorT");
QString SeismicLabUtils::ComputeWavePassageEffectMatrixPP = QString::fromLatin1("ComputeWavePassageEffectMatrixPP");

QString SeismicLabUtils::ComputeCrossSpectrumValue = QString::fromLatin1("ComputeCrossSpectrumValue");
QString SeismicLabUtils::ComputeCrossSpectrumVectorF = QString::fromLatin1("ComputeCrossSpectrumVectorF");
QString SeismicLabUtils::ComputeCrossSpectrumVectorT = QString::fromLatin1("ComputeCrossSpectrumVectorT");
QString SeismicLabUtils::ComputeCrossSpectrumMatrixPP = QString::fromLatin1("ComputeCrossSpectrumMatrixPP");
QString SeismicLabUtils::ComputeAutoSpectrumValue = QString::fromLatin1("ComputeAutoSpectrumValue");
QString SeismicLabUtils::ComputeAutoSpectrumVectorF = QString::fromLatin1("ComputeAutoSpectrumVectorF");
QString SeismicLabUtils::ComputeAutoSpectrumVectorT = QString::fromLatin1("ComputeAutoSpectrumVectorT");


