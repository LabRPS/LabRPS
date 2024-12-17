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

#ifndef RPS_GLOBALS_H
#define RPS_GLOBALS_H

#include <Mod/WindLab/WindLabGlobal.h>
#include <map>
#include <QString>

namespace WindLab {

//! Definition of global constants and enums
/**
 * This class must not be instanced. All members are static.
 */
class WindLabExport WindLabUtils {

 private:
     WindLabUtils() {}  // don't allow instancing

 public:
  virtual ~WindLabUtils() {}  // avoid the warning message

  // phenomena
  static QString rpsPhenomenonWindVelocity;

  // object groups
  static QString objGroupLocationDistribution;
  static QString objGroupMeanWindProfile;
  static QString objGroupAlongWindSpectrum;
  static QString objGroupVerticalWindSpectrum;
  static QString objGroupAcrossWindSpectrum;
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
  static QString objGroupGustFactor;
  static QString objGroupKurtosis;
  static QString objGroupPeakFactor;
  static QString objGroupProbabilityDensityFunction;
  static QString objGroupRoughness;
  static QString objGroupShearVelocityOfFlow;
  static QString objGroupSkewness;
  static QString objGroupStandardDeviation;
  static QString objGroupTurbulenceIntensity;
  static QString objGroupTurbulenceScale;
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

  static QString ComputeGustFactorValue;
  static QString ComputeGustFactorVectorP;
  static QString ComputeGustFactorVectorT;

  static QString ComputeKurtosisValue;
  static QString ComputeKurtosisVectorP;
  static QString ComputeKurtosisVectorT;

  static QString MatrixToolCompute;

  static QString ComputeMeanWindSpeedValue;
  static QString ComputeMeanWindSpeedVectorP;
  static QString ComputeMeanWindSpeedVectorT;

  static QString ComputeModulationValue;
  static QString ComputeModulationVectorP;
  static QString ComputeModulationVectorT;
  static QString ComputeModulationVectorF;

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

  static QString ComputeRoughnessValue;
  static QString ComputeRoughnessVectorP;
  static QString ComputeRoughnessVectorT;

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

  static QString ComputeTurbulenceIntensityValue;
  static QString ComputeTurbulenceIntensityVectorP;
  static QString ComputeTurbulenceIntensityVectorT;

  static QString ComputeTurbulenceScaleValue;
  static QString ComputeTurbulenceScaleVectorP;
  static QString ComputeTurbulenceScaleVectorT;

  static QString UserDefinedRPSObjectCompute;

  static QString ComputeVarianceValue;
  static QString ComputeVarianceVectorP;
  static QString ComputeVarianceVectorT;

  static QString ComputeWavePassageEffectValue;
  static QString ComputeWavePassageEffectVectorF;
  static QString ComputeWavePassageEffectVectorT;
  static QString ComputeWavePassageEffectMatrixPP;

  static QString ComputeXCrossSpectrumValue;
  static QString ComputeXCrossSpectrumVectorF;
  static QString ComputeXCrossSpectrumVectorT;
  static QString ComputeXCrossSpectrumMatrixPP;
  static QString ComputeXAutoSpectrumValue;
  static QString ComputeXAutoSpectrumVectorF;
  static QString ComputeXAutoSpectrumVectorT;

  
  static QString ComputeYCrossSpectrumValue;
  static QString ComputeYCrossSpectrumVectorF;
  static QString ComputeYCrossSpectrumVectorT;
  static QString ComputeYCrossSpectrumMatrixPP;
  static QString ComputeYAutoSpectrumValue;
  static QString ComputeYAutoSpectrumVectorF;
  static QString ComputeYAutoSpectrumVectorT;

  static QString ComputeZCrossSpectrumValue;
  static QString ComputeZCrossSpectrumVectorF;
  static QString ComputeZCrossSpectrumVectorT;
  static QString ComputeZCrossSpectrumMatrixPP;
  static QString ComputeZAutoSpectrumValue;
  static QString ComputeZAutoSpectrumVectorF;
  static QString ComputeZAutoSpectrumVectorT;

  static bool getObjects(std::map<const std::string, std::string>& map, std::map<const std::string, std::string>& lstObject, const std::string& pluginName, const std::string& objectGroup);
  static bool updateObjectsMap(std::map<const std::string, std::string>& map, const QString& lstObject);
  static bool updateObjectToSkipMap(std::map<const std::string, std::string>& map, const QString name, const QString pluginName);
  static bool isThisObjectGroupPluggedInThisPlugin(const std::map<const std::string, std::string>& map,const QString& pluginName);
  static bool isThisObjectInstalled(std::map<const std::string, std::string>& map, QString& object);

public:
  enum class ColorPal { Light, Dark };
  enum class TableColorProfile { Success, Failure, Generic };
  static int getWordSizeApp();
  static QString getOperatingSystem();
  static int getWordSizeOfOS();
  static QString splitstring(const QString &string);
  static QString joinstring(const QString &string);

  // html Formatting
  static QString makeHtmlTable(const int row, const int column,
                               const bool hasheader,
                               const TableColorProfile &profile);

 private:
  static double rgbRandomSeed_;
  static int rgbCounter_;
};

} // namespace Gui

#endif  // RPS_GLOBALS_H
