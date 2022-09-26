#ifndef RPSSLPLUGINAPI_H
#define RPSSLPLUGINAPI_H

#include "RPSSeaLabAPIdefines.h"
#include "IrpsSeLSimulationMethod.h"
#include "IrpsSeLMean.h"
#include "IrpsSeLLocationDistribution.h"
#include "IrpsSeLSpectrum.h"
#include "IrpsSeLCoherence.h"
#include "IrpsSeLFrequencyDistribution.h"
#include "IrpsSeLRandomness.h"
#include "IrpsSeLPSDdecompositionMethod.h"
#include "IrpsSeLCorrelation.h"
#include "IrpsSeLModulation.h"
#include "IrpsSeLDirectionSpreadingFunction.h"
#include "IrpsSeLDirectionDistribution.h"
#include "IrpsSeLDirectionalSpectrum.h"


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



// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsSeLSimulationMethod *(*SLSimulationMethodInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*SLSimulationMethodFreeFunc)(IrpsSeLSimulationMethod *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterSLSimulationMethod(const QString name, const QString &pluginName, const QString &description,
	SLSimulationMethodInitFunc init_cb,
	SLSimulationMethodFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeSLSimulationMethod(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnRegisterSLSimulationMethod(const QString name, const QString &pluginName);


////////////////////////////////////////////////////////////////////////////////////////////////////////////kkkkkkk

////////////////////////////////////coherence//////////////////////////////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsSeLCoherence *(*CoherenceInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*CoherenceFreeFunc)(IrpsSeLCoherence *);

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
typedef IrpsSeLLocationDistribution *(*LocationDistributionInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*LocationDistributionFreeFunc)(IrpsSeLLocationDistribution *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterLocationDistribution(const QString name, const QString &pluginName, const QString &description,
	LocationDistributionInitFunc init_cb,
	LocationDistributionFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeLocationDistribution(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterLocationDistribution(const QString name, const QString &pluginName);


/////////////////////////////////mean d///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsSeLMean *(*MeanInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*MeanFreeFunc)(IrpsSeLMean *);

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
typedef IrpsSeLSpectrum *(*XSpectrumInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*XSpectrumFreeFunc)(IrpsSeLSpectrum *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterXSpectrum(const QString name, const QString &pluginName, const QString &description,
	XSpectrumInitFunc init_cb,
	XSpectrumFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeXSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterXSpectrum(const QString name, const QString &pluginName);


/////////////////////////////////Wind Coherence///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsSeLCoherence *(*CoherenceInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*CoherenceFreeFunc)(IrpsSeLCoherence *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterCoherence(const QString name, const QString &pluginName, const QString &description,
	CoherenceInitFunc init_cb,
	CoherenceFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeCoherence(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterCoherence(const QString name, const QString &pluginName);



/////////////////////////////////Frequency distribution///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsSeLFrequencyDistribution *(*FrequencyDistributionInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*FrequencyDistributionFreeFunc)(IrpsSeLFrequencyDistribution *);

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
typedef IrpsSeLRandomness *(*RandomnessInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*RandomnessFreeFunc)(IrpsSeLRandomness *);

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
typedef IrpsSeLPSDdecompositionMethod *(*PSDdecomMethodInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*PSDdecomMethodFreeFunc)(IrpsSeLPSDdecompositionMethod *);

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
typedef IrpsSeLCorrelation *(*CorrelationInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*CorrelationFreeFunc)(IrpsSeLCorrelation *);

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
typedef IrpsSeLModulation *(*ModulationInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*ModulationFreeFunc)(IrpsSeLModulation *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterModulation(const QString name, const QString &pluginName, const QString &description,
	ModulationInitFunc init_cb,
	ModulationFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeModulation(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterModulation(const QString name, const QString &pluginName);

/////////////////////////////////Directional spectrum///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsSeLDirectionalSpectrum *(*DirectionalSpectrumInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*DirectionalSpectrumFreeFunc)(IrpsSeLDirectionalSpectrum *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterDirectionalSpectrum(const QString name, const QString &pluginName, const QString &description,
	DirectionalSpectrumInitFunc init_cb,
	DirectionalSpectrumFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeDirectionalSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterDirectionalSpectrum(const QString name, const QString &pluginName);

/////////////////////////////////Directional ///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsSeLDirectionDistribution *(*DirectionDistributionInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*DirectionDistributionFreeFunc)(IrpsSeLDirectionDistribution *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterDirectionDistribution(const QString name, const QString &pluginName, const QString &description,
	DirectionDistributionInitFunc init_cb,
	DirectionDistributionFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeDirectionDistribution(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterDirectionDistribution(const QString name, const QString &pluginName);

/////////////////////////////////DirectionSpreadingFunction///////////////////

// Register and build Coherence object
/// The function signature for a routine that creates a random process
typedef IrpsSeLDirectionSpreadingFunction *(*DirectionSpreadingFunctionInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*DirectionSpreadingFunctionFreeFunc)(IrpsSeLDirectionSpreadingFunction *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterDirectionSpreadingFunction(const QString name, const QString &pluginName, const QString &description,
	DirectionSpreadingFunctionInitFunc init_cb,
	DirectionSpreadingFunctionFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeDirectionSpreadingFunction(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterDirectionSpreadingFunction(const QString name, const QString &pluginName);
#endif
