
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

#ifndef RPSSEISMICLABPLUGINAPI_H
#define RPSSEISMICLABPLUGINAPI_H

#include "RPSSeismicLabAPIdefines.h"
#include "IrpsSLLocationDistribution.h"
#include "IrpsSLMeanAcceleration.h"
#include "IrpsSLSpectrum.h"
#include "IrpsSLCoherence.h"
#include "IrpsSLSimulationMethod.h"
#include "IrpsSLFrequencyDistribution.h"
#include "IrpsSLRandomness.h"
#include "IrpsSLPSDdecompositionMethod.h"
#include "IrpsSLCorrelation.h"
#include "IrpsSLModulation.h"
#include "IrpsSLTableTool.h"
#include "IrpsSLMatrixTool.h"
#include "IrpsSLUserDefinedRPSObject.h"
#include "IrpsSLCumulativeProbabilityDistribution.h"
#include "IrpsSLKurtosis.h"
#include "IrpsSLPeakFactor.h"
#include "IrpsSLProbabilityDensityFunction.h"
#include "IrpsSLShearVelocityOfFlow.h"
#include "IrpsSLSkewness.h"
#include "IrpsSLStandardDeviation.h"
#include "IrpsSLVariance.h"
#include "IrpsSLWavePassageEffect.h"


#define PLUGIN_API_VERSION  0.1

#define RPS_CORE_FUNC     extern "C" RPS_CORE_API
#define RPS_PLUGIN_FUNC   extern "C" RPS_PLUGIN_API

/// declare the initialization routine for a plugin
#define PLUGIN_INIT() \
    const int &PluginVersion = PLUGIN_API_VERSION; \
    RPS_PLUGIN_FUNC const int &PluginInit()

#define PLUGIN_INIT_TYPE() \
    RPS_PLUGIN_FUNC const int &PluginInitType()

// Install a plugin
#define INSTALL_PLUGIN() \
    RPS_PLUGIN_FUNC const int &InstallPlugin()

// Uninstall a plugin
#define UNINSTALL_PLUGIN() \
    RPS_PLUGIN_FUNC const int &UninstallPlugin()

/// declare the cleanup routine for a plugin
#define PLUGIN_FREE() \
	RPS_PLUGIN_FUNC const int &PluginFree()

/// declare the display name for a plugin
#define PLUGIN_NAME(pluginname) \
	RPS_PLUGIN_FUNC const char* PluginName = pluginname

/// declare the file name for a plugin
#define PLUGIN_FILE_NAME(filename) \
	RPS_PLUGIN_FUNC const char * PluginFileName = filename

/// declare the plugin name
#define RANDOM_PHENOMENON(phenomenon) \
	RPS_PLUGIN_FUNC const char * Phenomenon = phenomenon

/// declare the plugin Author
#define PLUGIN_AUTHOR(pluginauthor) \
	RPS_PLUGIN_FUNC const char * PluginAuthor = pluginauthor

/// declare the plugin Author
#define PLUGIN_DESCRIPTION(plugindescription) \
	RPS_PLUGIN_FUNC const char * PluginDescription = plugindescription

/// declare the minimum required Plugin API version for a plugin
#define PLUGIN_MIN_VERSION(version) \
	RPS_PLUGIN_API const char *  PluginMinVersion = version

/// declare the maximum supported Plugin API version for a plugin
#define PLUGIN_MAX_VERSION(version) \
	RPS_PLUGIN_API const char *  PluginMaxVersion = version

/// declare the maximum supported Plugin API version for a plugin
#define PLUGIN_VERSION(currentversion) \
	RPS_PLUGIN_FUNC const char *  PluginCurrentVersion = currentversion

/// declare the release date for a plugin
#define PLUGIN_RELEASE_DATE(releasedate) \
	RPS_PLUGIN_FUNC const char *  PluginReleaseDate = releasedate

/// declare the wiki link for a plugin
#define PLUGIN_WIKI_LINK(wikilink) \
	RPS_PLUGIN_FUNC const char* PluginWikiLink = wikilink

/// the LabRPS version
#define LABRPS_VERSION(labrpsversion) \
	RPS_PLUGIN_FUNC const char *  Labrpsversion = labrpsversion

/// the API version
#define API_VERSION(apiversion) \
	RPS_PLUGIN_FUNC const char *  Apiversion = apiversion

namespace SeismicLabAPI {
////////////////////////////////////////////////////////////////
class RPS_CORE_API RPSSeismicLabPluginAPIInfo
{
public:

	static const char * getSeismicLabPluginAPIVersion();
};

} //namespace SeismicLabAPI

////////////////////////////////////coherence//////////////////////////////////////////


typedef SeismicLabAPI::IrpsSLCoherence *(*CoherenceInitFunc)();
typedef void(*CoherenceFreeFunc)(SeismicLabAPI::IrpsSLCoherence *);
RPS_CORE_FUNC void RegisterCoherence(const std::string name, const std::string& description, const std::string& pluginName,
	CoherenceInitFunc init_cb,
	CoherenceFreeFunc free_cb);

RPS_CORE_FUNC void InitializeCoherence(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterCoherence(const std::string name, const std::string& pluginName);

/////////////////////////////////Location distribution///////////////////
typedef  SeismicLabAPI::IrpsSLLocationDistribution *(*LocationDistributionInitFunc)();
typedef void(*LocationDistributionFreeFunc)(SeismicLabAPI::IrpsSLLocationDistribution *);
RPS_CORE_FUNC void RegisterLocationDistribution(const std::string name, const std::string& pluginName, const std::string& description,
	LocationDistributionInitFunc init_cb,
	LocationDistributionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeLocationDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterLocationDistribution(const std::string name, const std::string& pluginName);


/////////////////////////////////mean d///////////////////
typedef SeismicLabAPI::IrpsSLMeanAcceleration *(*MeanInitFunc)();
typedef void(*MeanFreeFunc)(SeismicLabAPI::IrpsSLMeanAcceleration *);
RPS_CORE_FUNC void RegisterMean(const std::string name, const std::string& pluginName, const std::string& description,
	MeanInitFunc init_cb,
	MeanFreeFunc free_cb);
RPS_CORE_FUNC void InitializeMean(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterMean(const std::string name, const std::string& pluginName);


/////////////////////////////////Along wind spectrum target///////////////////
typedef SeismicLabAPI::IrpsSLSpectrum *(*SpectrumInitFunc)();
typedef void(*SpectrumFreeFunc)(SeismicLabAPI::IrpsSLSpectrum *);
RPS_CORE_FUNC void RegisterSpectrum(const std::string name, const std::string& pluginName, const std::string& description,
	SpectrumInitFunc init_cb,
	SpectrumFreeFunc free_cb);
RPS_CORE_FUNC void InitializeSpectrum(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterSpectrum(const std::string name, const std::string& pluginName);

/////////////////////////////////Simulation Method///////////////////
typedef SeismicLabAPI::IrpsSLSimulationMethod *(*SimuMethodInitFunc)();
typedef void(*SimuMethodFreeFunc)(SeismicLabAPI::IrpsSLSimulationMethod *);
RPS_CORE_FUNC void RegisterSimuMethod(const std::string name, const std::string& pluginName, const std::string& description,
	SimuMethodInitFunc init_cb,
	SimuMethodFreeFunc free_cb);
RPS_CORE_FUNC void InitializeSimuMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterSimuMethod(const std::string name, const std::string& pluginName);


/////////////////////////////////Frequency distribution///////////////////
typedef SeismicLabAPI::IrpsSLFrequencyDistribution *(*FrequencyDistributionInitFunc)();
typedef void(*FrequencyDistributionFreeFunc)(SeismicLabAPI::IrpsSLFrequencyDistribution *);
RPS_CORE_FUNC void RegisterFrequencyDistribution(const std::string name, const std::string& pluginName, const std::string& description,
	FrequencyDistributionInitFunc init_cb,
	FrequencyDistributionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeFrequencyDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterFrequencyDistribution(const std::string name, const std::string& pluginName);



/////////////////////////////////Randomness///////////////////
typedef SeismicLabAPI::IrpsSLRandomness *(*RandomnessInitFunc)();
typedef void(*RandomnessFreeFunc)(SeismicLabAPI::IrpsSLRandomness *);
RPS_CORE_FUNC void RegisterRandomness(const std::string name, const std::string& pluginName, const std::string& description,
	RandomnessInitFunc init_cb,
	RandomnessFreeFunc free_cb);
RPS_CORE_FUNC void InitializeRandomness(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterRandomness(const std::string name, const std::string& pluginName);


/////////////////////////////////psd decomposition///////////////////
typedef SeismicLabAPI::IrpsSLPSDdecompositionMethod *(*PSDdecomMethodInitFunc)();
typedef void(*PSDdecomMethodFreeFunc)(SeismicLabAPI::IrpsSLPSDdecompositionMethod *);
RPS_CORE_FUNC void RegisterPSDdecomMethod(const std::string name, const std::string& pluginName, const std::string& description,
	PSDdecomMethodInitFunc init_cb,
	PSDdecomMethodFreeFunc free_cb);
RPS_CORE_FUNC void InitializePSDdecomMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterPSDdecomMethod(const std::string name, const std::string& pluginName);


/////////////////////////////////Correlation///////////////////
typedef SeismicLabAPI::IrpsSLCorrelation *(*CorrelationInitFunc)();
typedef void(*CorrelationFreeFunc)(SeismicLabAPI::IrpsSLCorrelation *);
RPS_CORE_FUNC void RegisterCorrelation(const std::string name, const std::string& pluginName, const std::string& description,
	CorrelationInitFunc init_cb,
	CorrelationFreeFunc free_cb);
RPS_CORE_FUNC void InitializeCorrelation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterCorrelation(const std::string name, const std::string& pluginName);


/////////////////////////////////Modulation///////////////////
typedef SeismicLabAPI::IrpsSLModulation *(*ModulationInitFunc)();
typedef void(*ModulationFreeFunc)(SeismicLabAPI::IrpsSLModulation *);
RPS_CORE_FUNC void RegisterModulation(const std::string name, const std::string& pluginName, const std::string& description,
	ModulationInitFunc init_cb,
	ModulationFreeFunc free_cb);
RPS_CORE_FUNC void InitializeModulation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterModulation(const std::string name, const std::string& pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////
typedef SeismicLabAPI::IrpsSLTableTool *(*TableToolInitFunc)();
typedef void(*TableToolFreeFunc)(SeismicLabAPI::IrpsSLTableTool *);
RPS_CORE_FUNC void RegisterTableTool(const std::string name, const std::string& description, const std::string& pluginName,
	TableToolInitFunc init_cb,
	TableToolFreeFunc free_cb);
RPS_CORE_FUNC void InitializeTableTool(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterTableTool(const std::string name, const std::string& pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////
typedef SeismicLabAPI::IrpsSLMatrixTool *(*MatrixToolInitFunc)();
typedef void(*MatrixToolFreeFunc)(SeismicLabAPI::IrpsSLMatrixTool *);
RPS_CORE_FUNC void RegisterMatrixTool(const std::string name, const std::string& description, const std::string& pluginName,
	MatrixToolInitFunc init_cb,
	MatrixToolFreeFunc free_cb);
RPS_CORE_FUNC void InitializeMatrixTool(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterMatrixTool(const std::string name, const std::string& pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////
typedef SeismicLabAPI::IrpsSLUserDefinedRPSObject *(*UserDefinedRPSObjectInitFunc)();
typedef void(*UserDefinedRPSObjectFreeFunc)(SeismicLabAPI::IrpsSLUserDefinedRPSObject *);
RPS_CORE_FUNC void RegisterUserDefinedRPSObject(const std::string name, const std::string& description, const std::string& pluginName,
	UserDefinedRPSObjectInitFunc init_cb,
	UserDefinedRPSObjectFreeFunc free_cb);
RPS_CORE_FUNC void InitializeUserDefinedRPSObject(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterUserDefinedRPSObject(const std::string name, const std::string& pluginName);

/////////////////////cumulative probability distribution///////////////
typedef SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution *(*CumulativeProbabilityDistributionInitFunc)();
typedef void(*CumulativeProbabilityDistributionFreeFunc)(SeismicLabAPI::IrpsSLCumulativeProbabilityDistribution *);
RPS_CORE_FUNC void RegisterCumulativeProbabilityDistribution(const std::string name, const std::string& description, const std::string& pluginName,
	CumulativeProbabilityDistributionInitFunc init_cb,
	CumulativeProbabilityDistributionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeCumulativeProbabilityDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterCumulativeProbabilityDistribution(const std::string name, const std::string& pluginName);

/////////////////////Kurtosis/////////////////////////
typedef SeismicLabAPI::IrpsSLKurtosis *(*KurtosisInitFunc)();
typedef void(*KurtosisFreeFunc)(SeismicLabAPI::IrpsSLKurtosis *);
RPS_CORE_FUNC void RegisterKurtosis(const std::string name, const std::string& description, const std::string& pluginName,
	KurtosisInitFunc init_cb,
	KurtosisFreeFunc free_cb);
RPS_CORE_FUNC void InitializeKurtosis(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterKurtosis(const std::string name, const std::string& pluginName);

/////////////////////Peak factor//////////////////
typedef SeismicLabAPI::IrpsSLPeakFactor *(*PeakFactorInitFunc)();
typedef void(*PeakFactorFreeFunc)(SeismicLabAPI::IrpsSLPeakFactor *);
RPS_CORE_FUNC void RegisterPeakFactor(const std::string name, const std::string& description, const std::string& pluginName,
	PeakFactorInitFunc init_cb,
	PeakFactorFreeFunc free_cb);
RPS_CORE_FUNC void InitializePeakFactor(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterPeakFactor(const std::string name, const std::string& pluginName);


/////////////////////Probability density function///////////////
typedef SeismicLabAPI::IrpsSLProbabilityDensityFunction *(*ProbabilityDensityFunctionInitFunc)();
typedef void(*ProbabilityDensityFunctionFreeFunc)(SeismicLabAPI::IrpsSLProbabilityDensityFunction *);
RPS_CORE_FUNC void RegisterProbabilityDensityFunction(const std::string name, const std::string& description, const std::string& pluginName,
	ProbabilityDensityFunctionInitFunc init_cb,
	ProbabilityDensityFunctionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeProbabilityDensityFunction(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterProbabilityDensityFunction(const std::string name, const std::string& pluginName);

/////////////////////Shear velocity of flow///////////////
typedef SeismicLabAPI::IrpsSLShearVelocityOfFlow *(*ShearVelocityOfFlowInitFunc)();
typedef void(*ShearVelocityOfFlowFreeFunc)(SeismicLabAPI::IrpsSLShearVelocityOfFlow *);
RPS_CORE_FUNC void RegisterShearVelocityOfFlow(const std::string name, const std::string& description, const std::string& pluginName,
	ShearVelocityOfFlowInitFunc init_cb,
	ShearVelocityOfFlowFreeFunc free_cb);
RPS_CORE_FUNC void InitializeShearVelocityOfFlow(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterShearVelocityOfFlow(const std::string name, const std::string& pluginName);

/////////////////////skewness///////////////
typedef SeismicLabAPI::IrpsSLSkewness *(*SkewnessInitFunc)();
typedef void(*SkewnessFreeFunc)(SeismicLabAPI::IrpsSLSkewness *);
RPS_CORE_FUNC void RegisterSkewness(const std::string name, const std::string& description, const std::string& pluginName,
	SkewnessInitFunc init_cb,
	SkewnessFreeFunc free_cb);
RPS_CORE_FUNC void InitializeSkewness(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterSkewness(const std::string name, const std::string& pluginName);

/////////////////////Standard deviation///////////////
typedef SeismicLabAPI::IrpsSLStandardDeviation *(*StandardDeviationInitFunc)();
typedef void(*StandardDeviationFreeFunc)(SeismicLabAPI::IrpsSLStandardDeviation *);
RPS_CORE_FUNC void RegisterStandardDeviation(const std::string name, const std::string& description, const std::string& pluginName,
	StandardDeviationInitFunc init_cb,
	StandardDeviationFreeFunc free_cb);
RPS_CORE_FUNC void InitializeStandardDeviation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterStandardDeviation(const std::string name, const std::string& pluginName);

/////////////////////Variance///////////////
typedef SeismicLabAPI::IrpsSLVariance *(*VarianceInitFunc)();
typedef void(*VarianceFreeFunc)(SeismicLabAPI::IrpsSLVariance *);
RPS_CORE_FUNC void RegisterVariance(const std::string name, const std::string& description, const std::string& pluginName,
	VarianceInitFunc init_cb,
	VarianceFreeFunc free_cb);
RPS_CORE_FUNC void InitializeVariance(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterVariance(const std::string name, const std::string& pluginName);

/////////////////////Wave passage effect///////////////

typedef SeismicLabAPI::IrpsSLWavePassageEffect *(*WavePassageEffectInitFunc)();
typedef void(*WavePassageEffectFreeFunc)(SeismicLabAPI::IrpsSLWavePassageEffect *);
RPS_CORE_FUNC void RegisterWavePassageEffect(const std::string name, const std::string& description, const std::string& pluginName,
	WavePassageEffectInitFunc init_cb,
	WavePassageEffectFreeFunc free_cb);
RPS_CORE_FUNC void InitializeWavePassageEffect(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterWavePassageEffect(const std::string name, const std::string& pluginName);

#endif
