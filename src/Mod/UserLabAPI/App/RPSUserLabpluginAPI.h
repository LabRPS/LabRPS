
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

#ifndef RPSUSERLABPLUGINAPI_H
#define RPSUSERLABPLUGINAPI_H

#include "RPSUserLabAPIdefines.h"
#include "IrpsULSimulationMethod.h"

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

namespace UserLabAPI {
////////////////////////////////////////////////////////////////
class RPS_CORE_API RPSUserLabPluginAPIInfo
{
public:

	static const char * getUserLabPluginAPIVersion();
};

} //namespace UserLabAPI

typedef UserLabAPI::IrpsULSimulationMethod *(*SimulationMethodInitFunc)();
typedef void(*SimulationMethodFreeFunc)(UserLabAPI::IrpsULSimulationMethod *);
RPS_CORE_FUNC void RegisterSimulationMethod(const std::string name, const std::string& pluginName, const std::string& description,
	SimulationMethodInitFunc init_cb,
	SimulationMethodFreeFunc free_cb);
RPS_CORE_FUNC void InitializeSimulationMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);
RPS_CORE_FUNC void UnregisterSimulationMethod(const std::string name, const std::string& pluginName);

#endif
