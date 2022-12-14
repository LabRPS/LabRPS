

#ifndef RPSWINDLABPLUGINAPI_H
#define RPSWINDLABPLUGINAPI_H

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
#include "IrpsWLTableTool.h"
#include "IrpsWLMatrixTool.h"
#include "IrpsWLUserDefinedRPSObject.h"
#include "IrpsWLCumulativeProbabilityDistribution.h"
#include "IrpsWLGustFactor.h"
#include "IrpsWLKurtosis.h"
#include "IrpsWLPeakFactor.h"
#include "IrpsWLProbabilityDensityFunction.h"
#include "IrpsWLRoughness.h"
#include "IrpsWLShearVelocityOfFlow.h"
#include "IrpsWLSkewness.h"
#include "IrpsWLStandardDeviation.h"
#include "IrpsWLTurbulenceIntensity.h"
#include "IrpsWLTurbulenceScale.h"
#include "IrpsWLVariance.h"
#include "IrpsWLWavePassageEffect.h"


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

////////////////////////////////////////////////////////////////
class RPS_CORE_API RPSWindLabPluginAPIInfo
{
public:

	static const char * getWindLabPluginAPIVersion();
};

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
RPS_CORE_FUNC void InitializeCoherence(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializeLocationDistribution(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializeMean(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializeXSpectrum(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializeZSpectrum(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializeYSpectrum(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterYSpectrum(const QString name, const QString &pluginName);

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
RPS_CORE_FUNC void InitializeSimuMethod(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializeFrequencyDistribution(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializeRandomness(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializePSDdecomMethod(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializeCorrelation(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

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
RPS_CORE_FUNC void InitializeModulation(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterModulation(const QString name, const QString &pluginName);

RPS_CORE_FUNC void SimulationOutputText(QString outputText);

////////////////////////////////////user defined rps object//////////////////////////////////////////

// Register and build user defined rps object
/// The function signature for a routine that creates a random process
typedef IrpsWLTableTool *(*TableToolInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*TableToolFreeFunc)(IrpsWLTableTool *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterTableTool(const QString name, const QString &description, const QString &pluginName,
	TableToolInitFunc init_cb,
	TableToolFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeTableTool(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterTableTool(const QString name, const QString &pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////

// Register and build user defined rps object
/// The function signature for a routine that creates a random process
typedef IrpsWLMatrixTool *(*MatrixToolInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*MatrixToolFreeFunc)(IrpsWLMatrixTool *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterMatrixTool(const QString name, const QString &description, const QString &pluginName,
	MatrixToolInitFunc init_cb,
	MatrixToolFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeMatrixTool(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterMatrixTool(const QString name, const QString &pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////

// Register and build user defined rps object
/// The function signature for a routine that creates a random process
typedef IrpsWLUserDefinedRPSObject *(*UserDefinedRPSObjectInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*UserDefinedRPSObjectFreeFunc)(IrpsWLUserDefinedRPSObject *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterUserDefinedRPSObject(const QString name, const QString &description, const QString &pluginName,
	UserDefinedRPSObjectInitFunc init_cb,
	UserDefinedRPSObjectFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeUserDefinedRPSObject(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterUserDefinedRPSObject(const QString name, const QString &pluginName);

/////////////////////cumulative probability distribution///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLCumulativeProbabilityDistribution *(*CumulativeProbabilityDistributionInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*CumulativeProbabilityDistributionFreeFunc)(IrpsWLCumulativeProbabilityDistribution *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterCumulativeProbabilityDistribution(const QString name, const QString &description, const QString &pluginName,
	CumulativeProbabilityDistributionInitFunc init_cb,
	CumulativeProbabilityDistributionFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeCumulativeProbabilityDistribution(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterCumulativeProbabilityDistribution(const QString name, const QString &pluginName);


/////////////////////Gust factor///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLGustFactor *(*GustFactorInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*GustFactorFreeFunc)(IrpsWLGustFactor *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterGustFactor(const QString name, const QString &description, const QString &pluginName,
	GustFactorInitFunc init_cb,
	GustFactorFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeGustFactor(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterGustFactor(const QString name, const QString &pluginName);

/////////////////////Kurtosis/////////////////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLKurtosis *(*KurtosisInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*KurtosisFreeFunc)(IrpsWLKurtosis *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterKurtosis(const QString name, const QString &description, const QString &pluginName,
	KurtosisInitFunc init_cb,
	KurtosisFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeKurtosis(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterKurtosis(const QString name, const QString &pluginName);

/////////////////////Peak factor//////////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLPeakFactor *(*PeakFactorInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*PeakFactorFreeFunc)(IrpsWLPeakFactor *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterPeakFactor(const QString name, const QString &description, const QString &pluginName,
	PeakFactorInitFunc init_cb,
	PeakFactorFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializePeakFactor(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterPeakFactor(const QString name, const QString &pluginName);


/////////////////////Probability density function///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLProbabilityDensityFunction *(*ProbabilityDensityFunctionInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*ProbabilityDensityFunctionFreeFunc)(IrpsWLProbabilityDensityFunction *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterProbabilityDensityFunction(const QString name, const QString &description, const QString &pluginName,
	ProbabilityDensityFunctionInitFunc init_cb,
	ProbabilityDensityFunctionFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeProbabilityDensityFunction(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterProbabilityDensityFunction(const QString name, const QString &pluginName);


/////////////////////Roughness///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLRoughness *(*RoughnessInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*RoughnessFreeFunc)(IrpsWLRoughness *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterRoughness(const QString name, const QString &description, const QString &pluginName,
	RoughnessInitFunc init_cb,
	RoughnessFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeRoughness(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterRoughness(const QString name, const QString &pluginName);


/////////////////////Shear velocity of flow///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLShearVelocityOfFlow *(*ShearVelocityOfFlowInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*ShearVelocityOfFlowFreeFunc)(IrpsWLShearVelocityOfFlow *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterShearVelocityOfFlow(const QString name, const QString &description, const QString &pluginName,
	ShearVelocityOfFlowInitFunc init_cb,
	ShearVelocityOfFlowFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeShearVelocityOfFlow(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterShearVelocityOfFlow(const QString name, const QString &pluginName);

/////////////////////skewness///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLSkewness *(*SkewnessInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*SkewnessFreeFunc)(IrpsWLSkewness *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterSkewness(const QString name, const QString &description, const QString &pluginName,
	SkewnessInitFunc init_cb,
	SkewnessFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeSkewness(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterSkewness(const QString name, const QString &pluginName);

/////////////////////Standard deviation///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLStandardDeviation *(*StandardDeviationInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*StandardDeviationFreeFunc)(IrpsWLStandardDeviation *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterStandardDeviation(const QString name, const QString &description, const QString &pluginName,
	StandardDeviationInitFunc init_cb,
	StandardDeviationFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeStandardDeviation(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterStandardDeviation(const QString name, const QString &pluginName);

/////////////////////Turbulence intensity///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLTurbulenceIntensity *(*TurbulenceIntensityInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*TurbulenceIntensityFreeFunc)(IrpsWLTurbulenceIntensity *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterTurbulenceIntensity(const QString name, const QString &description, const QString &pluginName,
	TurbulenceIntensityInitFunc init_cb,
	TurbulenceIntensityFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeTurbulenceIntensity(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterTurbulenceIntensity(const QString name, const QString &pluginName);

/////////////////////Turbulence scale///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLTurbulenceScale *(*TurbulenceScaleInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*TurbulenceScaleFreeFunc)(IrpsWLTurbulenceScale *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterTurbulenceScale(const QString name, const QString &description, const QString &pluginName,
	TurbulenceScaleInitFunc init_cb,
	TurbulenceScaleFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeTurbulenceScale(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterTurbulenceScale(const QString name, const QString &pluginName);

/////////////////////Variance///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLVariance *(*VarianceInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*VarianceFreeFunc)(IrpsWLVariance *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterVariance(const QString name, const QString &description, const QString &pluginName,
	VarianceInitFunc init_cb,
	VarianceFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeVariance(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterVariance(const QString name, const QString &pluginName);

/////////////////////Wave passage effect///////////////

/// The function signature for a routine that creates a random process
typedef IrpsWLWavePassageEffect *(*WavePassageEffectInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*WavePassageEffectFreeFunc)(IrpsWLWavePassageEffect *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterWavePassageEffect(const QString name, const QString &description, const QString &pluginName,
	WavePassageEffectInitFunc init_cb,
	WavePassageEffectFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeWavePassageEffect(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterWavePassageEffect(const QString name, const QString &pluginName);

#endif
