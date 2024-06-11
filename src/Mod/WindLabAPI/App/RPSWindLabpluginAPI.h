

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

namespace WindLabAPI {
////////////////////////////////////////////////////////////////
class RPS_CORE_API RPSWindLabPluginAPIInfo
{
public:

	static const char * getWindLabPluginAPIVersion();
};

} //namespace WindLabAPI

////////////////////////////////////coherence//////////////////////////////////////////


typedef WindLabAPI::IrpsWLCoherence *(*CoherenceInitFunc)();
typedef void(*CoherenceFreeFunc)(WindLabAPI::IrpsWLCoherence *);
RPS_CORE_FUNC void RegisterCoherence(const std::string name, const std::string& description, const std::string& pluginName,
	CoherenceInitFunc init_cb,
	CoherenceFreeFunc free_cb);

RPS_CORE_FUNC void InitializeCoherence(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterCoherence(const std::string name, const std::string& pluginName);

/////////////////////////////////Location distribution///////////////////
typedef  WindLabAPI::IrpsWLLocationDistribution *(*LocationDistributionInitFunc)();
typedef void(*LocationDistributionFreeFunc)(WindLabAPI::IrpsWLLocationDistribution *);
RPS_CORE_FUNC void RegisterLocationDistribution(const std::string name, const std::string& pluginName, const std::string& description,
	LocationDistributionInitFunc init_cb,
	LocationDistributionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeLocationDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterLocationDistribution(const std::string name, const std::string& pluginName);


/////////////////////////////////mean d///////////////////
typedef WindLabAPI::IrpsWLMean *(*MeanInitFunc)();
typedef void(*MeanFreeFunc)(WindLabAPI::IrpsWLMean *);
RPS_CORE_FUNC void RegisterMean(const std::string name, const std::string& pluginName, const std::string& description,
	MeanInitFunc init_cb,
	MeanFreeFunc free_cb);
RPS_CORE_FUNC void InitializeMean(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterMean(const std::string name, const std::string& pluginName);


/////////////////////////////////Along wind spectrum target///////////////////
typedef WindLabAPI::IrpsWLXSpectrum *(*XSpectrumInitFunc)();
typedef void(*XSpectrumFreeFunc)(WindLabAPI::IrpsWLXSpectrum *);
RPS_CORE_FUNC void RegisterXSpectrum(const std::string name, const std::string& pluginName, const std::string& description,
	XSpectrumInitFunc init_cb,
	XSpectrumFreeFunc free_cb);
RPS_CORE_FUNC void InitializeXSpectrum(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterXSpectrum(const std::string name, const std::string& pluginName);


/////////////////////////////////Vertical wind spectrum target///////////////////
typedef WindLabAPI::IrpsWLZSpectrum *(*ZSpectrumInitFunc)();
typedef void(*ZSpectrumFreeFunc)(WindLabAPI::IrpsWLZSpectrum *);
RPS_CORE_FUNC void RegisterZSpectrum(const std::string name, const std::string& pluginName, const std::string& description,
	ZSpectrumInitFunc init_cb,
	ZSpectrumFreeFunc free_cb);
RPS_CORE_FUNC void InitializeZSpectrum(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterZSpectrum(const std::string name, const std::string& pluginName);


/////////////////////////////////Across wind spectrum target///////////////////
typedef WindLabAPI::IrpsWLYSpectrum *(*YSpectrumInitFunc)();
typedef void(*YSpectrumFreeFunc)(WindLabAPI::IrpsWLYSpectrum *);
RPS_CORE_FUNC void RegisterYSpectrum(const std::string name, const std::string& pluginName, const std::string& description,
	YSpectrumInitFunc init_cb,
	YSpectrumFreeFunc free_cb);
RPS_CORE_FUNC void InitializeYSpectrum(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterYSpectrum(const std::string name, const std::string& pluginName);

/////////////////////////////////Simulation Method///////////////////
typedef WindLabAPI::IrpsWLSimuMethod *(*SimuMethodInitFunc)();
typedef void(*SimuMethodFreeFunc)(WindLabAPI::IrpsWLSimuMethod *);
RPS_CORE_FUNC void RegisterSimuMethod(const std::string name, const std::string& pluginName, const std::string& description,
	SimuMethodInitFunc init_cb,
	SimuMethodFreeFunc free_cb);
RPS_CORE_FUNC void InitializeSimuMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterSimuMethod(const std::string name, const std::string& pluginName);


/////////////////////////////////Frequency distribution///////////////////
typedef WindLabAPI::IrpsWLFrequencyDistribution *(*FrequencyDistributionInitFunc)();
typedef void(*FrequencyDistributionFreeFunc)(WindLabAPI::IrpsWLFrequencyDistribution *);
RPS_CORE_FUNC void RegisterFrequencyDistribution(const std::string name, const std::string& pluginName, const std::string& description,
	FrequencyDistributionInitFunc init_cb,
	FrequencyDistributionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeFrequencyDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterFrequencyDistribution(const std::string name, const std::string& pluginName);



/////////////////////////////////Randomness///////////////////
typedef WindLabAPI::IrpsWLRandomness *(*RandomnessInitFunc)();
typedef void(*RandomnessFreeFunc)(WindLabAPI::IrpsWLRandomness *);
RPS_CORE_FUNC void RegisterRandomness(const std::string name, const std::string& pluginName, const std::string& description,
	RandomnessInitFunc init_cb,
	RandomnessFreeFunc free_cb);
RPS_CORE_FUNC void InitializeRandomness(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterRandomness(const std::string name, const std::string& pluginName);


/////////////////////////////////psd decomposition///////////////////
typedef WindLabAPI::IrpsWLPSDdecompositionMethod *(*PSDdecomMethodInitFunc)();
typedef void(*PSDdecomMethodFreeFunc)(WindLabAPI::IrpsWLPSDdecompositionMethod *);
RPS_CORE_FUNC void RegisterPSDdecomMethod(const std::string name, const std::string& pluginName, const std::string& description,
	PSDdecomMethodInitFunc init_cb,
	PSDdecomMethodFreeFunc free_cb);
RPS_CORE_FUNC void InitializePSDdecomMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterPSDdecomMethod(const std::string name, const std::string& pluginName);


/////////////////////////////////Correlation///////////////////
typedef WindLabAPI::IrpsWLCorrelation *(*CorrelationInitFunc)();
typedef void(*CorrelationFreeFunc)(WindLabAPI::IrpsWLCorrelation *);
RPS_CORE_FUNC void RegisterCorrelation(const std::string name, const std::string& pluginName, const std::string& description,
	CorrelationInitFunc init_cb,
	CorrelationFreeFunc free_cb);
RPS_CORE_FUNC void InitializeCorrelation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterCorrelation(const std::string name, const std::string& pluginName);


/////////////////////////////////Modulation///////////////////
typedef WindLabAPI::IrpsWLModulation *(*ModulationInitFunc)();
typedef void(*ModulationFreeFunc)(WindLabAPI::IrpsWLModulation *);
RPS_CORE_FUNC void RegisterModulation(const std::string name, const std::string& pluginName, const std::string& description,
	ModulationInitFunc init_cb,
	ModulationFreeFunc free_cb);
RPS_CORE_FUNC void InitializeModulation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterModulation(const std::string name, const std::string& pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////
typedef WindLabAPI::IrpsWLTableTool *(*TableToolInitFunc)();
typedef void(*TableToolFreeFunc)(WindLabAPI::IrpsWLTableTool *);
RPS_CORE_FUNC void RegisterTableTool(const std::string name, const std::string& description, const std::string& pluginName,
	TableToolInitFunc init_cb,
	TableToolFreeFunc free_cb);
RPS_CORE_FUNC void InitializeTableTool(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterTableTool(const std::string name, const std::string& pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////
typedef WindLabAPI::IrpsWLMatrixTool *(*MatrixToolInitFunc)();
typedef void(*MatrixToolFreeFunc)(WindLabAPI::IrpsWLMatrixTool *);
RPS_CORE_FUNC void RegisterMatrixTool(const std::string name, const std::string& description, const std::string& pluginName,
	MatrixToolInitFunc init_cb,
	MatrixToolFreeFunc free_cb);
RPS_CORE_FUNC void InitializeMatrixTool(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterMatrixTool(const std::string name, const std::string& pluginName);

////////////////////////////////////user defined rps object//////////////////////////////////////////
typedef WindLabAPI::IrpsWLUserDefinedRPSObject *(*UserDefinedRPSObjectInitFunc)();
typedef void(*UserDefinedRPSObjectFreeFunc)(WindLabAPI::IrpsWLUserDefinedRPSObject *);
RPS_CORE_FUNC void RegisterUserDefinedRPSObject(const std::string name, const std::string& description, const std::string& pluginName,
	UserDefinedRPSObjectInitFunc init_cb,
	UserDefinedRPSObjectFreeFunc free_cb);
RPS_CORE_FUNC void InitializeUserDefinedRPSObject(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterUserDefinedRPSObject(const std::string name, const std::string& pluginName);

/////////////////////cumulative probability distribution///////////////
typedef WindLabAPI::IrpsWLCumulativeProbabilityDistribution *(*CumulativeProbabilityDistributionInitFunc)();
typedef void(*CumulativeProbabilityDistributionFreeFunc)(WindLabAPI::IrpsWLCumulativeProbabilityDistribution *);
RPS_CORE_FUNC void RegisterCumulativeProbabilityDistribution(const std::string name, const std::string& description, const std::string& pluginName,
	CumulativeProbabilityDistributionInitFunc init_cb,
	CumulativeProbabilityDistributionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeCumulativeProbabilityDistribution(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterCumulativeProbabilityDistribution(const std::string name, const std::string& pluginName);


/////////////////////Gust factor///////////////
typedef WindLabAPI::IrpsWLGustFactor *(*GustFactorInitFunc)();
typedef void(*GustFactorFreeFunc)(WindLabAPI::IrpsWLGustFactor *);
RPS_CORE_FUNC void RegisterGustFactor(const std::string name, const std::string& description, const std::string& pluginName,
	GustFactorInitFunc init_cb,
	GustFactorFreeFunc free_cb);
RPS_CORE_FUNC void InitializeGustFactor(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterGustFactor(const std::string name, const std::string& pluginName);

/////////////////////Kurtosis/////////////////////////
typedef WindLabAPI::IrpsWLKurtosis *(*KurtosisInitFunc)();
typedef void(*KurtosisFreeFunc)(WindLabAPI::IrpsWLKurtosis *);
RPS_CORE_FUNC void RegisterKurtosis(const std::string name, const std::string& description, const std::string& pluginName,
	KurtosisInitFunc init_cb,
	KurtosisFreeFunc free_cb);
RPS_CORE_FUNC void InitializeKurtosis(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterKurtosis(const std::string name, const std::string& pluginName);

/////////////////////Peak factor//////////////////
typedef WindLabAPI::IrpsWLPeakFactor *(*PeakFactorInitFunc)();
typedef void(*PeakFactorFreeFunc)(WindLabAPI::IrpsWLPeakFactor *);
RPS_CORE_FUNC void RegisterPeakFactor(const std::string name, const std::string& description, const std::string& pluginName,
	PeakFactorInitFunc init_cb,
	PeakFactorFreeFunc free_cb);
RPS_CORE_FUNC void InitializePeakFactor(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterPeakFactor(const std::string name, const std::string& pluginName);


/////////////////////Probability density function///////////////
typedef WindLabAPI::IrpsWLProbabilityDensityFunction *(*ProbabilityDensityFunctionInitFunc)();
typedef void(*ProbabilityDensityFunctionFreeFunc)(WindLabAPI::IrpsWLProbabilityDensityFunction *);
RPS_CORE_FUNC void RegisterProbabilityDensityFunction(const std::string name, const std::string& description, const std::string& pluginName,
	ProbabilityDensityFunctionInitFunc init_cb,
	ProbabilityDensityFunctionFreeFunc free_cb);
RPS_CORE_FUNC void InitializeProbabilityDensityFunction(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterProbabilityDensityFunction(const std::string name, const std::string& pluginName);


/////////////////////Roughness///////////////
typedef WindLabAPI::IrpsWLRoughness *(*RoughnessInitFunc)();
typedef void(*RoughnessFreeFunc)(WindLabAPI::IrpsWLRoughness *);
RPS_CORE_FUNC void RegisterRoughness(const std::string name, const std::string& description, const std::string& pluginName,
	RoughnessInitFunc init_cb,
	RoughnessFreeFunc free_cb);
RPS_CORE_FUNC void InitializeRoughness(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterRoughness(const std::string name, const std::string& pluginName);


/////////////////////Shear velocity of flow///////////////
typedef WindLabAPI::IrpsWLShearVelocityOfFlow *(*ShearVelocityOfFlowInitFunc)();
typedef void(*ShearVelocityOfFlowFreeFunc)(WindLabAPI::IrpsWLShearVelocityOfFlow *);
RPS_CORE_FUNC void RegisterShearVelocityOfFlow(const std::string name, const std::string& description, const std::string& pluginName,
	ShearVelocityOfFlowInitFunc init_cb,
	ShearVelocityOfFlowFreeFunc free_cb);
RPS_CORE_FUNC void InitializeShearVelocityOfFlow(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterShearVelocityOfFlow(const std::string name, const std::string& pluginName);

/////////////////////skewness///////////////
typedef WindLabAPI::IrpsWLSkewness *(*SkewnessInitFunc)();
typedef void(*SkewnessFreeFunc)(WindLabAPI::IrpsWLSkewness *);
RPS_CORE_FUNC void RegisterSkewness(const std::string name, const std::string& description, const std::string& pluginName,
	SkewnessInitFunc init_cb,
	SkewnessFreeFunc free_cb);
RPS_CORE_FUNC void InitializeSkewness(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterSkewness(const std::string name, const std::string& pluginName);

/////////////////////Standard deviation///////////////
typedef WindLabAPI::IrpsWLStandardDeviation *(*StandardDeviationInitFunc)();
typedef void(*StandardDeviationFreeFunc)(WindLabAPI::IrpsWLStandardDeviation *);
RPS_CORE_FUNC void RegisterStandardDeviation(const std::string name, const std::string& description, const std::string& pluginName,
	StandardDeviationInitFunc init_cb,
	StandardDeviationFreeFunc free_cb);
RPS_CORE_FUNC void InitializeStandardDeviation(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterStandardDeviation(const std::string name, const std::string& pluginName);

/////////////////////Turbulence intensity///////////////
typedef WindLabAPI::IrpsWLTurbulenceIntensity *(*TurbulenceIntensityInitFunc)();
typedef void(*TurbulenceIntensityFreeFunc)(WindLabAPI::IrpsWLTurbulenceIntensity *);
RPS_CORE_FUNC void RegisterTurbulenceIntensity(const std::string name, const std::string& description, const std::string& pluginName,
	TurbulenceIntensityInitFunc init_cb,
	TurbulenceIntensityFreeFunc free_cb);
RPS_CORE_FUNC void InitializeTurbulenceIntensity(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterTurbulenceIntensity(const std::string name, const std::string& pluginName);

/////////////////////Turbulence scale///////////////
typedef WindLabAPI::IrpsWLTurbulenceScale *(*TurbulenceScaleInitFunc)();
typedef void(*TurbulenceScaleFreeFunc)(WindLabAPI::IrpsWLTurbulenceScale *);
RPS_CORE_FUNC void RegisterTurbulenceScale(const std::string name, const std::string& description, const std::string& pluginName,
	TurbulenceScaleInitFunc init_cb,
	TurbulenceScaleFreeFunc free_cb);
RPS_CORE_FUNC void InitializeTurbulenceScale(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterTurbulenceScale(const std::string name, const std::string& pluginName);

/////////////////////Variance///////////////
typedef WindLabAPI::IrpsWLVariance *(*VarianceInitFunc)();
typedef void(*VarianceFreeFunc)(WindLabAPI::IrpsWLVariance *);
RPS_CORE_FUNC void RegisterVariance(const std::string name, const std::string& description, const std::string& pluginName,
	VarianceInitFunc init_cb,
	VarianceFreeFunc free_cb);
RPS_CORE_FUNC void InitializeVariance(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterVariance(const std::string name, const std::string& pluginName);

/////////////////////Wave passage effect///////////////

typedef WindLabAPI::IrpsWLWavePassageEffect *(*WavePassageEffectInitFunc)();
typedef void(*WavePassageEffectFreeFunc)(WindLabAPI::IrpsWLWavePassageEffect *);
RPS_CORE_FUNC void RegisterWavePassageEffect(const std::string name, const std::string& description, const std::string& pluginName,
	WavePassageEffectInitFunc init_cb,
	WavePassageEffectFreeFunc free_cb);
RPS_CORE_FUNC void InitializeWavePassageEffect(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterWavePassageEffect(const std::string name, const std::string& pluginName);

#endif
