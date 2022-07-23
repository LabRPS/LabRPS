#pragma once

#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <map>
#include <vector>
#include <QString>
#include "RPSdefines.h"

class CPluginDescription
{
public:
	QString m_strName;
	QString m_strType;
	QString m_strReleaseDate;
	QString m_strAuthors;
	QString m_strVersion;
	QString m_strDescription;
	QString m_strFileName;
	QString m_strFullPath;
};


///
/// An object to represent a single plugin in the system
///
class RPS_CORE_API PluginInstance
{
public:
	explicit PluginInstance(const QString &name);
	~PluginInstance();

	/// Initialize the plugin
	bool Initialize();

	/// Load the plugin
	bool Load();

	/// Unload the plugin
	bool Unload();

	/// Return true if the plugin is loaded
	bool IsLoaded();

	/// Return the path to the plugin file on disk
	QString GetFileName();

	/// Return the display name for the plugin
	QString GetDisplayName();

	/// Return the system name for the plugin
	QString GetSystemName();

	/// Return the type of the plugin
	QString GetRandomPhenomenon();

	/// Return the plugin's Author
	QString GetPluginAuthor();

	/// Return the plugin's description
	QString GetPluginDescription();

	/// Return the version of plugin api used 
	int GetPluginApiVersion();

	/// Return the version for the plugin
	QString GetPluginVersion();

	/// Return the release date for the plugin
	QString GetLabRPSVersion();

	/// Return the release date for the plugin
	QString GetAPIVersion();

	/// Return the release date for the plugin
	QString GetPluginReleaseDate();

	// Get the subfolder containing the plugin
	QString GetPluginSubFolder();

	// Retrieve string from dll function address
	QString GetStringFromDllFunct(const QString &name);

	// Get the location of the plugin
	QString GetPluginLacotionPath();

	// Get the location of the plugin
	QString GetPluginRPName();
	
	// Get the installation state of the plugin (true = installed)
	bool GetInstallationState();

	// Set the installation state of the plugin (true = installed)
	void SetInstallationState(bool state);

private:
	// Make this object be noncopyable as it holds a pointer
	PluginInstance(const PluginInstance &);
	const PluginInstance &operator =(const PluginInstance &);

	class Impl;
	Impl *mImpl;
	bool bIsInstalled;
};

///
/// A manger for all plugins in the Core API
///
class RPS_CORE_API PluginManager
{
public:
	/// Return the single instance of the plugin manager
	static PluginManager &GetInstance();

	/// Load all plugins
	bool LoadAll();

	/// Load a single named plugin
	bool Load(const QString &name);

	/// Unload all plugins
	bool UnloadAll();

	/// Unload a single named plugin
	bool Unload(const QString &name);

	/// Return a list of all plugins
	std::vector<PluginInstance *> GetAllPlugins();

	// send text to output pane
	void rpsOutputText(QString outputText);

	// This function determine the plugins location
	QString GetPluginLacotionPath();

	// This function search for plugins
	void SearchPlugin();

	// Function that determine the application path
	QString GetApplicationPath();

	// This function install a plugin
	bool InitializePlugin(const QString &name, int instUninstMOd);

	// This function install a plugin
	bool InstallPlugin(const QString &name);

	// Install one by one plugin saved in registry
	bool InstallPluginInReg(const QString &name);

	// This function uninstall a plugin
	bool UnInstallPlugin(const QString &name);

	/// Read plugin descriptions from description files
	void ReadDescription();

	// Read a text files
	bool ReadPlgTXT(const QString &name);

	//// Get plugin descriptions vector
	//std::vector<CPluginDescription *>& GetPluginDescriptionsVector();

	//// Get installed plugins vector
	//std::vector<PluginInstance *>& GetInstalledPluginsVector();

	// Get installed plugins vector
	std::vector<QString>& GetInstalledPluginsInRegVector();
	
	// Get installed plugin map
	std::map<QString, PluginInstance *>& GetInstalledPluginsMap();

	// Get plugin descriptions map
	std::map<QString, CPluginDescription *>& GetPluginDescriptionsMap();

	// Get installed plugin name map
	std::map<QString, PluginInstance *>& GetInstalledPluginsNameMap();


	//// Get the map containing all the RP
	//std::map<QString, QString>& GetAllRPMap();

	// // Write the intalled plugins to registry
	// int RPSWriteInstalledPluginsToRegistry();

	// int RPSWriteToBeInstallObjectsToRegistry();

	// // Read the intalled plugin to registry
	// int RPSReadInstalledPluginsFromRegistry();

	// // common function to all rp to Read the intalled plugin to registry
	// int RPSReadInstalledPluginsFromRegistryCommon();

	// // Check if regiskey exists already for installed plugins
	// int CheckIfInstalledPlgsRegKeyExist();

	//// Insert all RP the the combo box
	//void InstallPRPL(PluginInstance * pi);

	//// Get the map containing all the RP
	//std::map<QString, QString>& GetAllRPMap();

	// This function find each folder in the plugin folder
	QString SearchPluginFolders(QString pluginpath);
	
	// Get the name of each plugin folder
	QString SearchForAllPlugins(QString pluginpath);

	// Read plugin descriptions from each plugin folder
	void ReadDescriptionFromFolder(QString strPath);

	// Get the full path of plugin
	QString GetPluginFullPath(QString FileName);

	// Make the file name from the plugin full name
	QString MakeFileNameFromFullPath(QString fullpath);

	// This function install the plugins of type POLR (Put it in appropriate map)
	void InstallPOLR(PluginInstance * pi);

	// Get all added objects map
	std::map<QString, QString>& GetAllPlugedObjectsMap();

	// These functions are just for testing
	void Recurse(QString pstr);
	void PrintDirs();

	bool doesPluginStillExist(QString pluginName, QString& pluginFullPath);


private:
	PluginManager();
	~PluginManager();
	PluginManager(const PluginManager &);
	const PluginManager &operator =(const PluginManager &);

	// A vector containing instances of all plugins
	std::vector<PluginInstance *> mPlugins;

	//// A vector containing descriptions of all plugins
	//std::vector<CPluginDescription *> mPluginDescriptions;

	//// A vector containing instances of all plugins
	//std::vector<PluginInstance *> mInstalledPlugins;

	
	// A map containing instances of all plugin: first = plugin file full path, second = the plugin instance
	std::map<QString, PluginInstance *> mInstalledPluginsMap;

	// A map containing description of all plugin
	std::map<QString, CPluginDescription *> PluginDescriptionMap;

	//// A map containing description of all plugin
	//std::map<QString, QString> mAllRPMap;
	
	// A vector containing names of all installed plugins
	std::vector<QString> mInstalledPluginsInReg;

	// All pluged ojects map: first = object name, second = its plugin full path
	std::map<QString, QString> mAllPlugedObjectsMap;

	// A map containing instances of all plugin: first = plugin name, second = the plugin instance
	std::map<QString, PluginInstance *> mAllInstalledPluginsNamesMap;

	// The path of the plugins location
	QString m_strPluginLacotionPath;

	// 
};


#endif