

#ifndef RPSUSERDEFINEDPHENOMENONPLUGINAPI_H
#define RPSUSERDEFINEDPHENOMENONPLUGINAPI_H

#include "RPSUserDefinedPhenomenonAPIdefines.h"
#include "IrpsUserDefinedPhenomenon.h"

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
class RPS_CORE_API RPSUserDefinedPhenomenonPluginAPIInfo
{
public:

    static const char * getUserDefinedPhenomenonPluginAPIVersion();
};

////////////////////////////////////UserDefinedPhenomenon//////////////////////////////////////////

// Register and build UserDefinedPhenomenon object
/// The function signature for a routine that creates a random process
typedef IrpsUserDefinedPhenomenon *(*UserDefinedPhenomenonInitFunc)();

/// The function signature for a routine that destroys a random process
typedef void(*UserDefinedPhenomenonFreeFunc)(IrpsUserDefinedPhenomenon *);

/// A routine to let a plugin register a new renderer name
RPS_CORE_FUNC void RegisterUserDefinedPhenomenon(const QString name, const QString &description, const QString &pluginName,
	UserDefinedPhenomenonInitFunc init_cb,
	UserDefinedPhenomenonFreeFunc free_cb);

/// A routine to let a plugin install new location distribution
RPS_CORE_FUNC void InitializeUserDefinedPhenomenon(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

/// This uninstall the location distribution
RPS_CORE_FUNC void UnregisterUserDefinedPhenomenon(const QString name, const QString &pluginName);


#endif
