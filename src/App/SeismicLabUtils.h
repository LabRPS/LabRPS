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

#ifndef APP_SEISMICLAB_UTILS_H
#define APP_SEISMICLAB_UTILS_H

#include <RPSGlobal.h>
#include <QString>

namespace App {

//! Definition of global constants and enums
/**
 * This class must not be instanced. All members are static.
 */
class AppExport SeismicLabUtils {

 private:
    SeismicLabUtils() {}// don't allow instancing

 public:
    virtual ~SeismicLabUtils() {}// avoid the warning message

  // phenomena
  static QString rpsPhenomenonGroundMotion;

  // object groups
  static QString objGroupLocationDistribution;
  static QString objGroupMeanAcceleration;
  static QString objGroupSpectrum;
  static QString objGroupSpectrumDecompositionMethod;
  static QString objGroupCoherenceFunction;
  static QString objGroupSimulationMethod;
  static QString objGroupFrequencyDistribution;
  static QString objGroupRandomnessProvider;
  static QString objGroupModulationFunction;
  static QString objGroupCorrelationFunction;
  static QString objGroupTableTool;
  static QString objGroupMatrixTool;
  static QString objGroupUserDefinedRPSObject;
  static QString objGroupUserObject;
  static QString objGroupCumulativeProbabilityDistribution;
  static QString objGroupKurtosis;
  static QString objGroupPeakFactor;
  static QString objGroupProbabilityDensityFunction;
  static QString objGroupShearVelocityOfFlow;
  static QString objGroupSkewness;
  static QString objGroupStandardDeviation;
  static QString objGroupVariance;
  static QString objGroupWavePassageEffect;
  static QString docRPSFeatures;
  static QString docSimulations;

  
  // available comparison categories
  static QString ComputeLocationCoordinateMatrixP3;

  static QString ComputeCrossCoherenceValue;
  static QString ComputeCrossCoherenceVectorF;
  static QString ComputeCrossCoherenceVectorT;
  static QString ComputeCrossCoherenceMatrixPP;

  static QString ComputeCrossCorrelationValue;
  static QString ComputeCrossCorrelationVectorT;
  static QString ComputeCrossCorrelationMatrixPP;

  static QString ComputeCPDValue;
  static QString ComputeCPDVectorX;

  static QString ComputeFrequencyValue;
  static QString ComputeFrequenciesVectorF;
  static QString ComputeFrequenciesMatrixFP;

  static QString ComputeKurtosisValue;
  static QString ComputeKurtosisVectorP;
  static QString ComputeKurtosisVectorT;

  static QString MatrixToolCompute;

  static QString ComputeMeanAccelerationValue;
  static QString ComputeMeanAccelerationVectorP;
  static QString ComputeMeanAccelerationVectorT;

  static QString ComputeModulationValue;
  static QString ComputeModulationVectorP;
  static QString ComputeModulationVectorT;

  static QString ComputePeakFactorValue;
  static QString ComputePeakFactorVectorP;
  static QString ComputePeakFactorVectorT;

  static QString ComputePDFValue;
  static QString ComputePDFVectorX;

  static QString ComputeDecomposedPSDValue;
  static QString ComputeDecomposedCrossSpectrumVectorF;
  static QString ComputeDecomposedCrossSpectrumVectorT;
  static QString ComputeDecomposedCrossSpectrumMatrixPP;

  static QString ComputeRandomValue;
  static QString GenerateRandomMatrixFP;
  static QString GenerateRandomCubeFPS;

  static QString ComputeShearVelocityOfFlowValue;
  static QString ComputeShearVelocityOfFlowVectorT;
  static QString ComputeShearVelocityOfFlowVectorP;

  static QString Simulate;
  static QString SimulateInLargeScaleMode;

  static QString ComputeSkewnessValue;
  static QString ComputeSkewnessVectorP;
  static QString ComputeSkewnessVectorT;

  static QString ComputeStandardDeviationValue;
  static QString ComputeStandardDeviationVectorP;
  static QString ComputeStandardDeviationVectorT;

  static QString TableToolCompute;

  static QString UserDefinedRPSObjectCompute;

  static QString ComputeVarianceValue;
  static QString ComputeVarianceVectorP;
  static QString ComputeVarianceVectorT;

  static QString ComputeWavePassageEffectValue;
  static QString ComputeWavePassageEffectVectorF;
  static QString ComputeWavePassageEffectVectorT;
  static QString ComputeWavePassageEffectMatrixPP;

  static QString ComputeCrossSpectrumValue;
  static QString ComputeCrossSpectrumVectorF;
  static QString ComputeCrossSpectrumVectorT;
  static QString ComputeCrossSpectrumMatrixPP;
  static QString ComputeAutoSpectrumValue;
  static QString ComputeAutoSpectrumVectorF;
  static QString ComputeAutoSpectrumVectorT;
};

} // namespace Gui

#endif  // APP_SEISMICLAB_UTILS_H
