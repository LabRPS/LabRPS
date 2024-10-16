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

#include "PreCompiled.h"

#include "RPSSeismicLabPluginAPI.h"
#include "RPSSeismicLabAPI.h"

using namespace SeismicLabAPI;

const char * RPSSeismicLabPluginAPIInfo::getSeismicLabPluginAPIVersion()
{
	return "0.1";
}


 /////////////////////////////////////coherence//////////////////////////////////////////

 void RegisterCoherence(const std::string name, const std::string& pluginName, const std::string& description, CoherenceInitFunc init_cb, CoherenceFreeFunc free_cb)
 {
	 if (CrpsCoherenceFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsCoherenceFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsCoherenceFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeCoherence(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsCoherenceFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterCoherence(const std::string name, const std::string& pluginName)
 {
     CrpsCoherenceFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////Location Distribution//////////////////////////////////////////

 void RegisterLocationDistribution(const std::string name, const std::string& pluginName, const std::string& description, LocationDistributionInitFunc init_cb, LocationDistributionFreeFunc free_cb)
 {
	 if (CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsLocationDistributionFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeLocationDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsLocationDistributionFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterLocationDistribution(const std::string name, const std::string& pluginName)
 {
     CrpsLocationDistributionFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Mean wind profile//////////////////////////////////////////

 void RegisterMean(const std::string name, const std::string& pluginName, const std::string& description,  MeanInitFunc init_cb, MeanFreeFunc free_cb)
 {
	 if (CrpsMeanFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsMeanFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsMeanFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeMean(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsMeanFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterMean(const std::string name, const std::string& pluginName)
 {
     CrpsMeanFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Along wind target spectrum//////////////////////////////////////////

 void RegisterSpectrum(const std::string name, const std::string& pluginName, const std::string& description, SpectrumInitFunc init_cb, SpectrumFreeFunc free_cb)
 {
	 if (CrpsSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSpectrumFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsSpectrumFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeSpectrum(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsSpectrumFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterSpectrum(const std::string name, const std::string& pluginName)
 {
     CrpsSpectrumFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Simulation method//////////////////////////////////////////

 void RegisterSimuMethod(const std::string name, const std::string& pluginName, const std::string& description, SimuMethodInitFunc init_cb, SimuMethodFreeFunc free_cb)
 {
	 if (CrpsSimuMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSimuMethodFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsSimuMethodFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeSimuMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsSimuMethodFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterSimuMethod(const std::string name, const std::string& pluginName)
 {
     CrpsSimuMethodFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Frequency distribution//////////////////////////////////////////

 void RegisterFrequencyDistribution(const std::string name, const std::string& pluginName, const std::string& description, FrequencyDistributionInitFunc init_cb, FrequencyDistributionFreeFunc free_cb)
 {
	 if (CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsFrequencyDistributionFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeFrequencyDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsFrequencyDistributionFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterFrequencyDistribution(const std::string name, const std::string& pluginName)
 {
     CrpsFrequencyDistributionFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Randomness//////////////////////////////////////////

 void RegisterRandomness(const std::string name, const std::string& pluginName, const std::string& description, RandomnessInitFunc init_cb, RandomnessFreeFunc free_cb)
 {
	 if (CrpsRandomnessFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsRandomnessFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsRandomnessFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeRandomness(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsRandomnessFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterRandomness(const std::string name, const std::string& pluginName)
 {
     CrpsRandomnessFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////psd decomposition//////////////////////////////////////////

 void RegisterPSDdecomMethod(const std::string name, const std::string& pluginName, const std::string& description, PSDdecomMethodInitFunc init_cb, PSDdecomMethodFreeFunc free_cb)
 {
	 if (CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsPSDdecomMethodFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializePSDdecomMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsPSDdecomMethodFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterPSDdecomMethod(const std::string name, const std::string& pluginName)
 {
     CrpsPSDdecomMethodFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////Correlation//////////////////////////////////////////

 void RegisterCorrelation(const std::string name, const std::string& pluginName, const std::string& description, CorrelationInitFunc init_cb, CorrelationFreeFunc free_cb)
 {
	 if (CrpsCorrelationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsCorrelationFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsCorrelationFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeCorrelation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsCorrelationFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterCorrelation(const std::string name, const std::string& pluginName)
 {
     CrpsCorrelationFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////Modulation//////////////////////////////////////////

 void RegisterModulation(const std::string name, const std::string& pluginName, const std::string& description, ModulationInitFunc init_cb, ModulationFreeFunc free_cb)
 {
	 if (CrpsModulationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsModulationFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsModulationFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeModulation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsModulationFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterModulation(const std::string name, const std::string& pluginName)
 {
     CrpsModulationFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////table tool object//////////////////////////////////////////

 void RegisterTableTool(const std::string name, const std::string& pluginName, const std::string& description, TableToolInitFunc init_cb, TableToolFreeFunc free_cb)
 {
	 if (CrpsTableToolFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsTableToolFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsTableToolFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeTableTool(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsTableToolFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterTableTool(const std::string name, const std::string& pluginName)
 {
     CrpsTableToolFactory::UnregisterObject(name, pluginName);
 }

////////////////////////////////////matrix tools object//////////////////////////////////////////

 void RegisterMatrixTool(const std::string name, const std::string& pluginName, const std::string& description, MatrixToolInitFunc init_cb, MatrixToolFreeFunc free_cb)
 {
	 if (CrpsMatrixToolFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsMatrixToolFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsMatrixToolFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeMatrixTool(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsMatrixToolFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterMatrixTool(const std::string name, const std::string& pluginName)
 {
     CrpsMatrixToolFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////user defined rps object//////////////////////////////////////////

 void RegisterUserDefinedRPSObject(const std::string name, const std::string& pluginName, const std::string& description, UserDefinedRPSObjectInitFunc init_cb, UserDefinedRPSObjectFreeFunc free_cb)
 {
	 if (CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsUserDefinedRPSObjectFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeUserDefinedRPSObject(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsUserDefinedRPSObjectFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterUserDefinedRPSObject(const std::string name, const std::string& pluginName)
 {
     CrpsUserDefinedRPSObjectFactory::UnregisterObject(name, pluginName);
 }


/////////////////////cumulative probability distribution///////////////

 void RegisterCumulativeProbabilityDistribution(const std::string name, const std::string& pluginName, const std::string& description, CumulativeProbabilityDistributionInitFunc init_cb, CumulativeProbabilityDistributionFreeFunc free_cb)
 {
	 if (CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsCumulativeProbabilityDistributionFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeCumulativeProbabilityDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsCumulativeProbabilityDistributionFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterCumulativeProbabilityDistribution(const std::string name, const std::string& pluginName)
 {
     CrpsCumulativeProbabilityDistributionFactory::UnregisterObject(name, pluginName);
 }
 

 /////////////////////Kurtosis/////////////////////////////

 void RegisterKurtosis(const std::string name, const std::string& pluginName, const std::string& description, KurtosisInitFunc init_cb, KurtosisFreeFunc free_cb)
 {
	 if (CrpsKurtosisFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsKurtosisFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsKurtosisFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeKurtosis(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsKurtosisFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterKurtosis(const std::string name, const std::string& pluginName)
 {
     CrpsKurtosisFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Peak factor//////////////////////////

 void RegisterPeakFactor(const std::string name, const std::string& pluginName, const std::string& description, PeakFactorInitFunc init_cb, PeakFactorFreeFunc free_cb)
 {
	 if (CrpsPeakFactorFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsPeakFactorFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsPeakFactorFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializePeakFactor(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsPeakFactorFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterPeakFactor(const std::string name, const std::string& pluginName)
 {
     CrpsPeakFactorFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Probability density function///////////////

 void RegisterProbabilityDensityFunction(const std::string name, const std::string& pluginName, const std::string& description, ProbabilityDensityFunctionInitFunc init_cb, ProbabilityDensityFunctionFreeFunc free_cb)
 {
	 if (CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsProbabilityDensityFunctionFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeProbabilityDensityFunction(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsProbabilityDensityFunctionFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterProbabilityDensityFunction(const std::string name, const std::string& pluginName)
 {
     CrpsProbabilityDensityFunctionFactory::UnregisterObject(name, pluginName);
 }


 /////////////////////Shear velocity of the flow///////////////

 void RegisterShearVelocityOfFlow(const std::string name, const std::string& pluginName, const std::string& description, ShearVelocityOfFlowInitFunc init_cb, ShearVelocityOfFlowFreeFunc free_cb)
 {
	 if (CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsShearVelocityOfFlowFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeShearVelocityOfFlow(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsShearVelocityOfFlowFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterShearVelocityOfFlow(const std::string name, const std::string& pluginName)
 {
     CrpsShearVelocityOfFlowFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Skewness///////////////

 void RegisterSkewness(const std::string name, const std::string& pluginName, const std::string& description, SkewnessInitFunc init_cb, SkewnessFreeFunc free_cb)
 {
	 if (CrpsSkewnessFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSkewnessFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsSkewnessFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeSkewness(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsSkewnessFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterSkewness(const std::string name, const std::string& pluginName)
 {
     CrpsSkewnessFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Standard deviation///////////////

 void RegisterStandardDeviation(const std::string name, const std::string& pluginName, const std::string& description, StandardDeviationInitFunc init_cb, StandardDeviationFreeFunc free_cb)
 {
	 if (CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsStandardDeviationFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeStandardDeviation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsStandardDeviationFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterStandardDeviation(const std::string name, const std::string& pluginName)
 {
     CrpsStandardDeviationFactory::UnregisterObject(name, pluginName);
 }

  void RegisterVariance(const std::string name, const std::string& pluginName, const std::string& description, VarianceInitFunc init_cb, VarianceFreeFunc free_cb)
 {
	 if (CrpsVarianceFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsVarianceFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsVarianceFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeVariance(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsVarianceFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterVariance(const std::string name, const std::string& pluginName)
 {
     CrpsVarianceFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Wave passage effect///////////////

 void RegisterWavePassageEffect(const std::string name, const std::string& pluginName, const std::string& description, WavePassageEffectInitFunc init_cb, WavePassageEffectFreeFunc free_cb)
 {
	 if (CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsWavePassageEffectFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; 
 }

 void InitializeWavePassageEffect(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
     CrpsWavePassageEffectFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterWavePassageEffect(const std::string name, const std::string& pluginName)
 {
     CrpsWavePassageEffectFactory::UnregisterObject(name, pluginName);
 }
