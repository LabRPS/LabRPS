
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

#ifndef RPSSEALABPLUGINAPI_H
#define RPSSEALABPLUGINAPI_H

#include "RPSSeaLabAPIdefines.h"
#include "IrpsSeLLocationDistribution.h"
#include "IrpsSeLMeanAcceleration.h"
#include "IrpsSeLCoherence.h"
#include "IrpsSeLSimulationMethod.h"
#include "IrpsSeLFrequencyDistribution.h"
#include "IrpsSeLRandomness.h"
#include "IrpsSeLPSDdecompositionMethod.h"
#include "IrpsSeLCorrelation.h"
#include "IrpsSeLModulation.h"
#include "IrpsSeLTableTool.h"
#include "IrpsSeLMatrixTool.h"
#include "IrpsSeLUserDefinedRPSObject.h"
#include "IrpsSeLCumulativeProbabilityDistribution.h"
#include "IrpsSeLKurtosis.h"
#include "IrpsSeLPeakFactor.h"
#include "IrpsSeLProbabilityDensityFunction.h"
#include "IrpsSeLShearVelocityOfFlow.h"
#include "IrpsSeLSkewness.h"
#include "IrpsSeLStandardDeviation.h"
#include "IrpsSeLVariance.h"
#include "IrpsSeLWavePassageEffect.h"
#include "IrpsSeLFrequencySpectrum.h"
#include "IrpsSeLDirectionalSpectrum.h"
#include "IrpsSeLDirectionalSpreadingFunction.h"


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

namespace SeaLabAPI {
////////////////////////////////////////////////////////////////
class RPS_CORE_API RPSSeaLabPluginAPIInfo
{
public:

	static const char * getSeaLabPluginAPIVersion();
};

} //namespace SeaLabAPI

////////////////////////////////////coherence//////////////////////////////////////////


typedef SeaLabAPI::IrpsSeLCoherence *(*CoherenceInitFunc)();
typedef void(*CoherenceFreeFunc)(SeaLabAPI::IrpsSeLCoherence *);
RPS_CORE_FUNC void RegisterCoherence(const std::string name, const std::string& description, const std::string& pluginName,
	CoherenceInitFunc init_cb,
	CoherenceFreeFunc free_cb);

RPS_CORE_FUNC void InitializeCoherence(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterCoherence(const std::string name, const std::string& pluginName);

/////////////////////////////////Location distribution///////////////////
typedef  SeaLabAPI::IrpsSeLLocationDistribution *(*LocationDistributionInitFunc)();
typedef void(*LocationDistributionFreeFunc)(SeaLabAPI::IrpsSeLLocationDistribution *);
RPS_CORE_FUNC void RegisterLocationDistribution(const std::string name, const std::string& pluginName, const std::string& description,
	LocationDistributionInitFunc init_cb,
	LocationDistributionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeLocationDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterLocationDistribution(const std::string name, const std::string& pluginName);


/////////////////////////////////mean d///////////////////
typedef SeaLabAPI::IrpsSeLMeanAcceleration *(*MeanInitFunc)();
typedef void(*MeanFreeFunc)(SeaLabAPI::IrpsSeLMeanAcceleration *);
RPS_CORE_FUNC void RegisterMean(const std::string name, const std::string& pluginName, const std::string& description,
	MeanInitFunc init_cb,
	MeanFreeFunc free_cb);
RPS_CORE_FUNC void InitializeMean(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterMean(const std::string name, const std::string& pluginName);

/////////////////////////////////Simulation Method///////////////////
typedef SeaLabAPI::IrpsSeLSimulationMethod *(*SimuMethodInitFunc)();
typedef void(*SimuMethodFreeFunc)(SeaLabAPI::IrpsSeLSimulationMethod *);
RPS_CORE_FUNC void RegisterSimuMethod(const std::string name, const std::string& pluginName, const std::string& description,
	SimuMethodInitFunc init_cb,
	SimuMethodFreeFunc free_cb);
RPS_CORE_FUNC void InitializeSimuMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterSimuMethod(const std::string name, const std::string& pluginName);


/////////////////////////////////Frequency distribution///////////////////
typedef SeaLabAPI::IrpsSeLFrequencyDistribution *(*FrequencyDistributionInitFunc)();
typedef void(*FrequencyDistributionFreeFunc)(SeaLabAPI::IrpsSeLFrequencyDistribution *);
RPS_CORE_FUNC void RegisterFrequencyDistribution(const std::string name, const std::string& pluginName, const std::string& description,
	FrequencyDistributionInitFunc init_cb,
	FrequencyDistributionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeFrequencyDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterFrequencyDistribution(const std::string name, const std::string& pluginName);



/////////////////////////////////Randomness///////////////////
typedef SeaLabAPI::IrpsSeLRandomness *(*RandomnessInitFunc)();
typedef void(*RandomnessFreeFunc)(SeaLabAPI::IrpsSeLRandomness *);
RPS_CORE_FUNC void RegisterRandomness(const std::string name, const std::string& pluginName, const std::string& description,
	RandomnessInitFunc init_cb,
	RandomnessFreeFunc free_cb);
RPS_CORE_FUNC void InitializeRandomness(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterRandomness(const std::string name, const std::string& pluginName);


/////////////////////////////////psd decomposition///////////////////
typedef SeaLabAPI::IrpsSeLPSDdecompositionMethod *(*PSDdecomMethodInitFunc)();
typedef void(*PSDdecomMethodFreeFunc)(SeaLabAPI::IrpsSeLPSDdecompositionMethod *);
RPS_CORE_FUNC void RegisterPSDdecomMethod(const std::string name, const std::string& pluginName, const std::string& description,
	PSDdecomMethodInitFunc init_cb,
	PSDdecomMethodFreeFunc free_cb);
RPS_CORE_FUNC void InitializePSDdecomMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterPSDdecomMethod(const std::string name, const std::string& pluginName);


/////////////////////////////////Correlation///////////////////
typedef SeaLabAPI::IrpsSeLCorrelation *(*CorrelationInitFunc)();
typedef void(*CorrelationFreeFunc)(SeaLabAPI::IrpsSeLCorrelation *);
RPS_CORE_FUNC void RegisterCorrelation(const std::string name, const std::string& pluginName, const std::string& description,
	CorrelationInitFunc init_cb,
	CorrelationFreeFunc free_cb);
RPS_CORE_FUNC void InitializeCorrelation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterCorrelation(const std::string name, const std::string& pluginName);


/////////////////////////////////Modulation///////////////////
typedef SeaLabAPI::IrpsSeLModulation *(*ModulationInitFunc)();
typedef void(*ModulationFreeFunc)(SeaLabAPI::IrpsSeLModulation *);
RPS_CORE_FUNC void RegisterModulation(const std::string name, const std::string& pluginName, const std::string& description,
	ModulationInitFunc init_cb,
	ModulationFreeFunc free_cb);
RPS_CORE_FUNC void InitializeModulation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterModulation(const std::string name, const std::string& pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////
typedef SeaLabAPI::IrpsSeLTableTool *(*TableToolInitFunc)();
typedef void(*TableToolFreeFunc)(SeaLabAPI::IrpsSeLTableTool *);
RPS_CORE_FUNC void RegisterTableTool(const std::string name, const std::string& description, const std::string& pluginName,
	TableToolInitFunc init_cb,
	TableToolFreeFunc free_cb);
RPS_CORE_FUNC void InitializeTableTool(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterTableTool(const std::string name, const std::string& pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////
typedef SeaLabAPI::IrpsSeLMatrixTool *(*MatrixToolInitFunc)();
typedef void(*MatrixToolFreeFunc)(SeaLabAPI::IrpsSeLMatrixTool *);
RPS_CORE_FUNC void RegisterMatrixTool(const std::string name, const std::string& description, const std::string& pluginName,
	MatrixToolInitFunc init_cb,
	MatrixToolFreeFunc free_cb);
RPS_CORE_FUNC void InitializeMatrixTool(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterMatrixTool(const std::string name, const std::string& pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////
typedef SeaLabAPI::IrpsSeLUserDefinedRPSObject *(*UserDefinedRPSObjectInitFunc)();
typedef void(*UserDefinedRPSObjectFreeFunc)(SeaLabAPI::IrpsSeLUserDefinedRPSObject *);
RPS_CORE_FUNC void RegisterUserDefinedRPSObject(const std::string name, const std::string& description, const std::string& pluginName,
	UserDefinedRPSObjectInitFunc init_cb,
	UserDefinedRPSObjectFreeFunc free_cb);
RPS_CORE_FUNC void InitializeUserDefinedRPSObject(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterUserDefinedRPSObject(const std::string name, const std::string& pluginName);

/////////////////////cumulative probability distribution///////////////
typedef SeaLabAPI::IrpsSeLCumulativeProbabilityDistribution *(*CumulativeProbabilityDistributionInitFunc)();
typedef void(*CumulativeProbabilityDistributionFreeFunc)(SeaLabAPI::IrpsSeLCumulativeProbabilityDistribution *);
RPS_CORE_FUNC void RegisterCumulativeProbabilityDistribution(const std::string name, const std::string& description, const std::string& pluginName,
	CumulativeProbabilityDistributionInitFunc init_cb,
	CumulativeProbabilityDistributionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeCumulativeProbabilityDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterCumulativeProbabilityDistribution(const std::string name, const std::string& pluginName);

/////////////////////Kurtosis/////////////////////////
typedef SeaLabAPI::IrpsSeLKurtosis *(*KurtosisInitFunc)();
typedef void(*KurtosisFreeFunc)(SeaLabAPI::IrpsSeLKurtosis *);
RPS_CORE_FUNC void RegisterKurtosis(const std::string name, const std::string& description, const std::string& pluginName,
	KurtosisInitFunc init_cb,
	KurtosisFreeFunc free_cb);
RPS_CORE_FUNC void InitializeKurtosis(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterKurtosis(const std::string name, const std::string& pluginName);

/////////////////////Peak factor//////////////////
typedef SeaLabAPI::IrpsSeLPeakFactor *(*PeakFactorInitFunc)();
typedef void(*PeakFactorFreeFunc)(SeaLabAPI::IrpsSeLPeakFactor *);
RPS_CORE_FUNC void RegisterPeakFactor(const std::string name, const std::string& description, const std::string& pluginName,
	PeakFactorInitFunc init_cb,
	PeakFactorFreeFunc free_cb);
RPS_CORE_FUNC void InitializePeakFactor(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterPeakFactor(const std::string name, const std::string& pluginName);


/////////////////////Probability density function///////////////
typedef SeaLabAPI::IrpsSeLProbabilityDensityFunction *(*ProbabilityDensityFunctionInitFunc)();
typedef void(*ProbabilityDensityFunctionFreeFunc)(SeaLabAPI::IrpsSeLProbabilityDensityFunction *);
RPS_CORE_FUNC void RegisterProbabilityDensityFunction(const std::string name, const std::string& description, const std::string& pluginName,
	ProbabilityDensityFunctionInitFunc init_cb,
	ProbabilityDensityFunctionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeProbabilityDensityFunction(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterProbabilityDensityFunction(const std::string name, const std::string& pluginName);

/////////////////////Shear velocity of flow///////////////
typedef SeaLabAPI::IrpsSeLShearVelocityOfFlow *(*ShearVelocityOfFlowInitFunc)();
typedef void(*ShearVelocityOfFlowFreeFunc)(SeaLabAPI::IrpsSeLShearVelocityOfFlow *);
RPS_CORE_FUNC void RegisterShearVelocityOfFlow(const std::string name, const std::string& description, const std::string& pluginName,
	ShearVelocityOfFlowInitFunc init_cb,
	ShearVelocityOfFlowFreeFunc free_cb);
RPS_CORE_FUNC void InitializeShearVelocityOfFlow(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterShearVelocityOfFlow(const std::string name, const std::string& pluginName);

/////////////////////skewness///////////////
typedef SeaLabAPI::IrpsSeLSkewness *(*SkewnessInitFunc)();
typedef void(*SkewnessFreeFunc)(SeaLabAPI::IrpsSeLSkewness *);
RPS_CORE_FUNC void RegisterSkewness(const std::string name, const std::string& description, const std::string& pluginName,
	SkewnessInitFunc init_cb,
	SkewnessFreeFunc free_cb);
RPS_CORE_FUNC void InitializeSkewness(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterSkewness(const std::string name, const std::string& pluginName);

/////////////////////Standard deviation///////////////
typedef SeaLabAPI::IrpsSeLStandardDeviation *(*StandardDeviationInitFunc)();
typedef void(*StandardDeviationFreeFunc)(SeaLabAPI::IrpsSeLStandardDeviation *);
RPS_CORE_FUNC void RegisterStandardDeviation(const std::string name, const std::string& description, const std::string& pluginName,
	StandardDeviationInitFunc init_cb,
	StandardDeviationFreeFunc free_cb);
RPS_CORE_FUNC void InitializeStandardDeviation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterStandardDeviation(const std::string name, const std::string& pluginName);

/////////////////////Variance///////////////
typedef SeaLabAPI::IrpsSeLVariance *(*VarianceInitFunc)();
typedef void(*VarianceFreeFunc)(SeaLabAPI::IrpsSeLVariance *);
RPS_CORE_FUNC void RegisterVariance(const std::string name, const std::string& description, const std::string& pluginName,
	VarianceInitFunc init_cb,
	VarianceFreeFunc free_cb);
RPS_CORE_FUNC void InitializeVariance(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterVariance(const std::string name, const std::string& pluginName);

/////////////////////Wave passage effect///////////////

typedef SeaLabAPI::IrpsSeLWavePassageEffect *(*WavePassageEffectInitFunc)();
typedef void(*WavePassageEffectFreeFunc)(SeaLabAPI::IrpsSeLWavePassageEffect *);
RPS_CORE_FUNC void RegisterWavePassageEffect(const std::string name, const std::string& description, const std::string& pluginName,
	WavePassageEffectInitFunc init_cb,
	WavePassageEffectFreeFunc free_cb);
RPS_CORE_FUNC void InitializeWavePassageEffect(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterWavePassageEffect(const std::string name, const std::string& pluginName);

/////////////////////////////////frequency spectrum///////////////////
typedef SeaLabAPI::IrpsSeLFrequencySpectrum *(*FrequencySpectrumInitFunc)();
typedef void(*FrequencySpectrumFreeFunc)(SeaLabAPI::IrpsSeLFrequencySpectrum *);
RPS_CORE_FUNC void RegisterFrequencySpectrum(const std::string name, const std::string& pluginName, const std::string& description,
	FrequencySpectrumInitFunc init_cb,
	FrequencySpectrumFreeFunc free_cb);
RPS_CORE_FUNC void InitializeFrequencySpectrum(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterFrequencySpectrum(const std::string name, const std::string& pluginName);

/////////////////////////////////directional spectrum///////////////////
typedef SeaLabAPI::IrpsSeLDirectionalSpectrum *(*DirectionalSpectrumInitFunc)();
typedef void(*DirectionalSpectrumFreeFunc)(SeaLabAPI::IrpsSeLDirectionalSpectrum *);
RPS_CORE_FUNC void RegisterDirectionalSpectrum(const std::string name, const std::string& pluginName, const std::string& description,
	DirectionalSpectrumInitFunc init_cb,
	DirectionalSpectrumFreeFunc free_cb);
RPS_CORE_FUNC void InitializeDirectionalSpectrum(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterDirectionalSpectrum(const std::string name, const std::string& pluginName);

/////////////////////////////////directional spectrum///////////////////
typedef SeaLabAPI::IrpsSeLDirectionalSpreadingFunction *(*DirectionalSpreadingFunctionInitFunc)();
typedef void(*DirectionalSpreadingFunctionFreeFunc)(SeaLabAPI::IrpsSeLDirectionalSpreadingFunction *);
RPS_CORE_FUNC void RegisterDirectionalSpreadingFunction(const std::string name, const std::string& pluginName, const std::string& description,
	DirectionalSpreadingFunctionInitFunc init_cb,
	DirectionalSpreadingFunctionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeDirectionalSpreadingFunction(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterDirectionalSpreadingFunction(const std::string name, const std::string& pluginName);
#endif
