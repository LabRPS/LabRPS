#pragma once

#ifndef RPSPLUGINAPI_H
#define RPSPLUGINAPI_H

#include "RPSWindLabAPIdefines.h"
#include "IrpsWLLocationDistribution.h"
#include "IrpsWLMean.h"
#include "IrpsWLXSpectrum.h"
#include "IrpsWLZSpectrum.h"
#include "IrpsWLYSpectrum.h"
#include "IrpsWLCoherence.h"
#include "IrpsWLSimuMethod.h"
#include "IrpsWLFrequencyDistribution.h"
#include "IrpsWLRandomness.h"
#include "IrpsWLPSDdecompositionMethod.h"
#include "IrpsWLCorrelation.h"
#include "IrpsWLModulation.h"

#define PLUGIN_API_VERSION  2

#define RPS_CORE_FUNC     extern "C" RPS_CORE_API
#define RPS_PLUGIN_FUNC   extern "C" RPS_PLUGIN_API

/// declare the initialization routine for a plugin
#define PLUGIN_INIT() \
	const int &PluginVersion = PLUGIN_API_VERSION; \
	RPS_PLUGIN_FUNC const int &PluginInit()

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
#define PLUGIN_DISPLAY_NAME(displayname) \
	RPS_PLUGIN_FUNC const char * PluginDisplayName = displayname

/// declare the system name for a plugin
#define PLUGIN_SYSTEM_NAME(systemname) \
	RPS_PLUGIN_FUNC const char * PluginSystemName = systemname

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

/// the LabRPS version
#define LABRPS_VERSION(labrpsversion) \
	RPS_PLUGIN_FUNC const char *  Labrpsversion = labrpsversion

/// the API version
#define API_VERSION(apiversion) \
	RPS_PLUGIN_FUNC const char *  Apiversion = apiversion

////////////////////////////////////coherence//////////////////////////////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLCoherence *(*CoherenceInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*CoherenceFreeFunc)(IrpsWLCoherence *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterCoherence(const QString name, const QString &description, const QString &pluginName,
	CoherenceInitFunc init_cb,
	CoherenceFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeCoherence(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterCoherence(const QString name, const QString &pluginName);

/////////////////////////////////Location distribution///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLLocationDistribution *(*LocationDistributionInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*LocationDistributionFreeFunc)(IrpsWLLocationDistribution *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterLocationDistribution(const QString name, const QString &pluginName, const QString &description,
	LocationDistributionInitFunc init_cb,
	LocationDistributionFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeLocationDistribution(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterLocationDistribution(const QString name, const QString &pluginName);


//RPS_CORE_FUNC void SimulationOutputText(QString outputText);


/////////////////////////////////mean d///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLMean *(*MeanInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*MeanFreeFunc)(IrpsWLMean *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterMean(const QString name, const QString &pluginName, const QString &description,
	MeanInitFunc init_cb,
	MeanFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeMean(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterMean(const QString name, const QString &pluginName);


/////////////////////////////////Along wind spectrum target///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLXSpectrum *(*XSpectrumInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*XSpectrumFreeFunc)(IrpsWLXSpectrum *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterXSpectrum(const QString name, const QString &pluginName, const QString &description,
	XSpectrumInitFunc init_cb,
	XSpectrumFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeXSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterXSpectrum(const QString name, const QString &pluginName);


/////////////////////////////////Vertical wind spectrum target///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLZSpectrum *(*ZSpectrumInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*ZSpectrumFreeFunc)(IrpsWLZSpectrum *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterZSpectrum(const QString name, const QString &pluginName, const QString &description,
	ZSpectrumInitFunc init_cb,
	ZSpectrumFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeZSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterZSpectrum(const QString name, const QString &pluginName);


/////////////////////////////////Across wind spectrum target///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLYSpectrum *(*YSpectrumInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*YSpectrumFreeFunc)(IrpsWLYSpectrum *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterYSpectrum(const QString name, const QString &pluginName, const QString &description,
	YSpectrumInitFunc init_cb,
	YSpectrumFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeYSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterYSpectrum(const QString name, const QString &pluginName);


/////////////////////////////////Wind Coherence///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLCoherence *(*CoherenceInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*CoherenceFreeFunc)(IrpsWLCoherence *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterCoherence(const QString name, const QString &pluginName, const QString &description,
	CoherenceInitFunc init_cb,
	CoherenceFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeCoherence(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterCoherence(const QString name, const QString &pluginName);


/////////////////////////////////Simulation Method///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLSimuMethod *(*SimuMethodInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*SimuMethodFreeFunc)(IrpsWLSimuMethod *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterSimuMethod(const QString name, const QString &pluginName, const QString &description,
	SimuMethodInitFunc init_cb,
	SimuMethodFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeSimuMethod(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterSimuMethod(const QString name, const QString &pluginName);


/////////////////////////////////Frequency distribution///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLFrequencyDistribution *(*FrequencyDistributionInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*FrequencyDistributionFreeFunc)(IrpsWLFrequencyDistribution *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterFrequencyDistribution(const QString name, const QString &pluginName, const QString &description,
	FrequencyDistributionInitFunc init_cb,
	FrequencyDistributionFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeFrequencyDistribution(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterFrequencyDistribution(const QString name, const QString &pluginName);



/////////////////////////////////Randomness///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLRandomness *(*RandomnessInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*RandomnessFreeFunc)(IrpsWLRandomness *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterRandomness(const QString name, const QString &pluginName, const QString &description,
	RandomnessInitFunc init_cb,
	RandomnessFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeRandomness(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterRandomness(const QString name, const QString &pluginName);


/////////////////////////////////psd decomposition///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLPSDdecompositionMethod *(*PSDdecomMethodInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*PSDdecomMethodFreeFunc)(IrpsWLPSDdecompositionMethod *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterPSDdecomMethod(const QString name, const QString &pluginName, const QString &description,
	PSDdecomMethodInitFunc init_cb,
	PSDdecomMethodFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializePSDdecomMethod(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterPSDdecomMethod(const QString name, const QString &pluginName);


/////////////////////////////////Correlation///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLCorrelation *(*CorrelationInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*CorrelationFreeFunc)(IrpsWLCorrelation *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterCorrelation(const QString name, const QString &pluginName, const QString &description,
	CorrelationInitFunc init_cb,
	CorrelationFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeCorrelation(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterCorrelation(const QString name, const QString &pluginName);


/////////////////////////////////Modulation///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsWLModulation *(*ModulationInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*ModulationFreeFunc)(IrpsWLModulation *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterModulation(const QString name, const QString &pluginName, const QString &description,
	ModulationInitFunc init_cb,
	ModulationFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeModulation(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterModulation(const QString name, const QString &pluginName);

RPS_CORE_FUNC void SimulationOutputText(QString outputText);

#endif
