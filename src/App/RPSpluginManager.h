

#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <RPSGlobal.h>

#include <map>
#include <vector>
#include <QString>

namespace App
{

class AppExport PluginDescription
{
public:

    // the name of the plugin
	QString name;

	// the source the plugin is coming from (local or online)
    QString source;

	// the type of the plugin
	QString type;

	// the date the plugin has been released
	QString releaseDate;

	// the authors, those who contribute to the implementatio of the plugin
	QString authors;

	// the plugin version
	QString version;

	// the description showing what the plugin does
	QString description;

	// the plugin file name
	QString fileName;

	// the full path to the plugin file
	QString fullPath;
};


///
/// An object to represent a single plugin in the system
///
class GuiExport PluginInstance
{
public:
	explicit PluginInstance(const QString &name);
	~PluginInstance();

	// Initialize the plugin
    bool Initialize(QString &information);

	bool InitializeType();

	// Load the plugin
	bool Load();

	// Unload the plugin
	bool Unload();

	/// Return true if the plugin is loaded
	bool IsLoaded();

	/// Return the path to the plugin file on disk
	QString GetFileName();

	/// Return the plugin name for the plugin
	QString GetPluginName();

	/// Return the type of the plugin
	QString GetRandomPhenomenon();

	/// Return the plugin's Author
	QString GetPluginAuthor();

	/// Return the plugin's description
	QString GetPluginDescription();

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
	
	// Get the installation state of the plugin (true = installed)
	bool GetInstallationState();

	// Set the installation state of the plugin (true = installed)
	void SetInstallationState(bool state);

	bool checkVersion(std::string versions, std::string currentVersion);

private:
	// Make this object be noncopyable as it holds a pointer
    PluginInstance(const PluginInstance &);
    const PluginInstance &operator =(const PluginInstance &);

	class Impl;
	Impl *mImpl;
	bool isInstalled;
};

///
/// A manger for all plugins in the Core API
///
class GuiExport PluginManager
{
public:
	/// Return the single instance of the plugin manager
	static PluginManager &GetInstance();

	/// Load a single named plugin
	bool Load(const QString &name);

	/// Unload a single named plugin
	bool Unload(const QString &name);

	// This function determine the plugins location
	QString GetPluginLacotionPath(const QString& workBenchName);
    QString GetOnlinePluginLacotionPath(const QString& workBenchName);

	// this function install a plugin
    bool InitializePlugin(const QString &name, int instUninstMOd, QString &information);
    bool InitializePluginType(const QString& name, int instUninstMOd);
	
	// This function install a plugin
	bool InstallPlugin(const QString &name);

	// Install one by one plugin saved in registry
	bool InstallPluginInReg(const QString &name);

	// This function uninstall a plugin
	bool UnInstallPlugin(const QString &name, bool remove = true);

	// Read a text files
    bool ReadPlgTXT(const QString& name, const QString& phenomenon, const int& source);

	// Get installed plugins vector
	std::vector<QString>& GetInstalledPluginsInRegVector();
	
	// Get installed plugin map
	std::map<QString, PluginInstance *>& GetInstalledPluginsMap();

	// Get plugin descriptions map
	std::map<QString, PluginDescription*>& GetPluginDescriptionsMap();

	// Get installed plugin name map
	std::map<QString, PluginInstance *>& GetInstalledPluginsNameMap();
	
	// Get the name of each plugin
    void SearchForAllPlugins(QString pluginpath, const QString& phenomenon, const int& source);

	// Read plugin descriptions from each plugin folder
    void ReadDescriptionFromFolder(QString strPath, const QString& phenomenon, const int& source);

	// Get the full path of plugin
	QString GetPluginFullPath(QString fileName);

	// Make the file name from the plugin full name
	QString MakeFileNameFromFullPath(QString fullpath);

	// Get all added objects map
	std::map<QString, QString>& GetAllPlugedObjectsMap();
	bool doesPluginStillExist(QString pluginName, QString& pluginFullPath, const QString& workbenchName, const QString& phenomenon, const int& source);


private:
	PluginManager();
	~PluginManager();
	PluginManager(const PluginManager &);
	const PluginManager &operator =(const PluginManager &);

	// A vector containing instances of all plugins
	std::vector<PluginInstance *> plugins;

	// A map containing instances of all plugin: first = plugin file full path, second = the plugin instance
	std::map<QString, PluginInstance *> installedPluginsMap;

	// A map containing description of all plugin
	std::map<QString, PluginDescription*> pluginDescriptionMap;
	
	// A vector containing names of all installed plugins
	std::vector<QString> installedPluginsInReg;

	// All pluged ojects map: first = object name, second = its plugin full path
	std::map<QString, QString> allPlugedObjectsMap;

	// A map containing instances of all plugin: first = plugin name, second = the plugin instance
	std::map<QString, PluginInstance *> allInstalledPluginsNamesMap;

	// The path of the plugins location
	QString pluginLacotionPath;
 
};

} // namespace App

#endif
