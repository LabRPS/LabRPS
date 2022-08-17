#include "RPSpluginManager.h"
#include <fstream>
#include <string>
#include <map>
#include <set>

#include <QLibrary>
#include <QByteArray>
#include <QMessageBox>
#include <QDirIterator>
#include <QTextStream>
#include <QFileInfo>
#include <QCoreApplication>
#include <QFile>


using namespace std;

class PluginInstance::Impl
{
public:

    // plugin name
	QString fileName;

	// the name of plugin as displayed in the plugin browser
	QString displayName;

	// a string 
	QString theString;

	// the plugin name in the application system
	QString systemName;

	// the random phenomenon for which the plugin is developed
	QString randomPhenomenon;

	// the name of the contributors to the plugin implementation
	QString pluginAuthor;

	// the description of the plugin
	QString pluginDescription;

	// the version of the plugin
	QString pluginVersion;

	// the version of LabRPS
	QString labRPSVersion;

	// the version of the api
	QString apiVersion;

	// the release date of the plugin
	QString pluginReleaseDate;

	// the name of the sub folder containing the plugin files
	QString pluginSubFolder;

	// the flag to show whether the plugin is installed
	bool isPluginInstalled;
	
	QLibrary library;

    typedef const int (*MyPrototypeOne)();
    typedef const char * (*MyPrototypeTwo)();

	bool Load()
	{
		// Load the plugin
		library.setFileName(pluginSubFolder);
		library.load();
		return !library.fileName().isEmpty();
	}

	bool Unload()
	{
		if (!library.isLoaded())
			return true;
		return library.unload();
	}

	MyPrototypeOne GetFunctionPrototypeOne(const char *name)
	{
		MyPrototypeOne fptr = (MyPrototypeOne)library.resolve(name);
		if (!fptr)
			return NULL;
		return fptr;
	}

	MyPrototypeTwo GetFunctionPrototypeTwo(const char *name)
	{
		MyPrototypeTwo fptr = (MyPrototypeTwo)library.resolve(name);
		if (!fptr)
			return NULL;
		return fptr;
	}
	
};


PluginInstance::PluginInstance(const QString &name)
{
	mImpl = new Impl;
	mImpl->displayName = name;
	mImpl->pluginSubFolder = name;
}

PluginInstance::~PluginInstance()
{
	delete mImpl;
}

bool PluginInstance::Initialize()
{
	//load the plugin
	if (!mImpl->Load())
	{
		return false;
	}

	// get the plugin initialization function
	Impl::MyPrototypeOne init_func = mImpl->GetFunctionPrototypeOne("PluginInit");
	if (!init_func)
		return false;

	// register the plugin
	(*init_func)();

	return true;
}

bool PluginInstance::Load()
{
	//load the plugin
	if (!mImpl->Load())
	{		
		return false;
	}
    
	// if the plugin is successfuly loaded
	// Call functions from the plungin (dll) to get information about the plugin
	mImpl->displayName = GetStringFromDllFunct("PluginDisplayName");
	mImpl->systemName = GetStringFromDllFunct("PluginSystemName");
	mImpl->randomPhenomenon = GetStringFromDllFunct("Phenomenon");
	mImpl->pluginAuthor = GetStringFromDllFunct("PluginAuthor");
	mImpl->pluginDescription = GetStringFromDllFunct("PluginDescription");
	mImpl->pluginVersion = GetStringFromDllFunct("PluginCurrentVersion");
	mImpl->pluginReleaseDate = GetStringFromDllFunct("PluginReleaseDate");
	mImpl->labRPSVersion = GetStringFromDllFunct("Labrpsversion");
	mImpl->apiVersion = GetStringFromDllFunct("Apiversion");

	// get the plugin installation function
	Impl::MyPrototypeOne install_func = mImpl->GetFunctionPrototypeOne("InstallPlugin");
	if (!install_func)
		return false;

	// install the plugin
	(*install_func)();
	mImpl->isPluginInstalled = true;

	return true;
}


bool PluginInstance::Unload()
{
	// get the plugin uninstallation function
	Impl::MyPrototypeOne Uninstal_func = mImpl->GetFunctionPrototypeOne("UninstallPlugin");
	
	if (!Uninstal_func)
		return false;

	// uninstall the plugin
	(*Uninstal_func)();

	return mImpl->Unload();
}

bool PluginInstance::IsLoaded()
{
	return mImpl->library.isLoaded();
}

QString PluginInstance::GetFileName()
{
	return mImpl->fileName;
}

QString PluginInstance::GetDisplayName()
{
	return mImpl->displayName;
}

QString PluginInstance::GetSystemName()
{
	return mImpl->systemName;
}

QString PluginInstance::GetRandomPhenomenon()
{
	return mImpl->randomPhenomenon;
}

QString PluginInstance::GetPluginAuthor()
{
	return mImpl->pluginAuthor;
}

QString PluginInstance::GetPluginDescription()
{
	return mImpl->pluginDescription;
}

QString PluginInstance::GetPluginVersion()
{
	return mImpl->pluginVersion;
}

QString PluginInstance::GetLabRPSVersion()
{
	return mImpl->labRPSVersion;
}

QString PluginInstance::GetAPIVersion()
{
	return mImpl->apiVersion;
}

QString PluginInstance::GetPluginSubFolder()
{
	return mImpl->pluginSubFolder;
}

QString PluginInstance::GetPluginReleaseDate()
{
	return mImpl->pluginReleaseDate;
}

PluginManager::PluginManager()
{
}

PluginManager::~PluginManager()
{
}

PluginManager &PluginManager::GetInstance()
{
	static PluginManager mgr;
	return mgr;
}

bool PluginManager::LoadAll()
{
	SearchPlugin();
	return true;
}

bool PluginManager::Load(const QString &name)
{
	// have we already loaded this plugin?
	static std::set<QString> loaded;
	if (loaded.find(name) != loaded.end())
		return true;

	// try to load this plugin
	PluginInstance *pi = new PluginInstance(name);
	if (!pi->Load())
	{
		delete pi;
		return false;
	}

	// success! add the plugin to our manager
	plugins.push_back(pi);

	// and don't try to load it again
	loaded.insert(name);
	return true;
}

bool PluginManager::UnloadAll()
{
	// not implemented yet
	return false;
}

bool PluginManager::Unload(const QString &name)
{
	return false;
}

QString PluginManager::GetPluginLacotionPath()
{
	// get the directory of the application
  QString appPath = QFileInfo(QCoreApplication::applicationFilePath()).path();

  // construct the plugin directory
  pluginLacotionPath =  appPath + "/plugins/";

	return pluginLacotionPath;
}

// search plugin
void PluginManager::SearchPlugin()
{
	
}

QString PluginInstance::GetStringFromDllFunct(const QString &name)
{
	QByteArray ba = name.toLocal8Bit();
    const char *c_str2 = ba.data();
	Impl::MyPrototypeTwo name_string = mImpl->GetFunctionPrototypeTwo(c_str2);
	if (name_string)
	{
		const char **ptr = (const char **)name_string;
		mImpl->theString = *ptr;

		return mImpl->theString;
	}

	return NULL;
}

void PluginManager::rpsOutputText(QString outputText)
{
	
}

bool PluginInstance::GetInstallationState()
{
	return mImpl->isPluginInstalled;
}

void PluginInstance::SetInstallationState(bool state)
{
   isInstalled = state;
}

bool PluginManager::InitializePlugin(const QString &name, int instUninstMOd)
{
		// have we already loaded this plugin?
		static std::set<QString> loaded;
		
		if ((1 == instUninstMOd) || (3 == instUninstMOd))
		{		
			// try to load this plugin
			PluginInstance *pi = new PluginInstance(name);
			
			if (!pi->Initialize())
			{
				delete pi;
				return false;
			}

			delete pi;
		}
			
	return true;
}

bool PluginManager::InstallPlugin(const QString &name)
{
	// have we already loaded this plugin?
	static std::set<QString> loaded;
	
	// try to load this plugin
	PluginInstance *pi = new PluginInstance(name);
	if (!pi->Load())
	{
		delete pi;
		return false;
	}

	// success! add the plugin to the installed plugins map
	installedPluginsMap[pi->GetPluginSubFolder()] = pi;
	allInstalledPluginsNamesMap[pi->GetDisplayName()] = pi;

	return true;
}


bool PluginManager::InstallPluginInReg(const QString &name)
{
	// try to load this plugin
	PluginInstance *pi = new PluginInstance(name);
	
	if (!pi->Load())
	{
		delete pi;
		return false;
	}

	// Success! add the plugin to the installed plugins map
	installedPluginsMap[pi->GetPluginSubFolder()] = pi;
	allInstalledPluginsNamesMap[pi->GetDisplayName()] = pi;

	return true;
}

bool PluginManager::UnInstallPlugin(const QString &name, bool remove)
{
	// Now make the file name
	QString filename = MakeFileNameFromFullPath(name);

	if (installedPluginsMap.find(name) != installedPluginsMap.end())
	{
		// Uninstall the plugin its corresponding map
		installedPluginsMap[name]->Unload();

		if (remove)
		{
			// Set it as not installed
			installedPluginsMap.erase(name);
		}
	}

	if (allInstalledPluginsNamesMap.find(filename) != allInstalledPluginsNamesMap.end())
	{
		// Uninstall the plugin its corresponding map
		allInstalledPluginsNamesMap[filename]->Unload();

		if (remove)
		{
			// Set it as not installed
			allInstalledPluginsNamesMap.erase(filename);
		}
	}

	return true;
}

bool PluginManager::ReadPlgTXT(const QString &path)
{
    QFile inputFile(path);

	CPluginDescription* Description = new CPluginDescription();

    if (inputFile.open(QIODevice::ReadOnly)){

	// Temporarly variable to contain each line
	QString line;
      
	  // start reading the file
	  QTextStream in(&inputFile);

	   while (!in.atEnd()){
       line = in.readLine();

	   if(!line.isNull()){

		if (true == line.contains("PluginFileName: "))
		{
			line.replace("PluginFileName: ", "");
			Description->fileName = line;
		}
		else if(true == line.contains("PluginName: "))
		{
			line.replace("PluginName: ", "");
			Description->name = line;
		}
		else if (true == line.contains("RandomPhenomenon: "))
		{
			line.replace("RandomPhenomenon: ", "");
			Description->type = line;
		}
		else if (true == line.contains("PluginReleaseDate: "))
		{
			line.replace("PluginReleaseDate: ", "");
			Description->releaseDate = line;
		}
		else if (true == line.contains("PluginAuthors: "))
		{
			line.replace("PluginAuthors: ", "");
			Description->authors = line;
		}
		else if (true == line.contains("PluginVersion: "))
		{
			line.replace("PluginVersion: ", "");
			Description->version = line;
		}
		else if (true == line.contains("PluginDescription: "))
		{
			line.replace("PluginDescription: ", "");
			Description->description = line;
		}
	   }
    
      }
        inputFile.close();
    }

	// Make the plugin full path
	QString fullpah = path;
	fullpah.replace(".txt", ".dll");

	// Save the plugin full path
	Description->fullPath = fullpah;

	pluginDescriptionMap[Description->fileName] = Description;

	return true;
}

std::vector<QString>& PluginManager::GetInstalledPluginsInRegVector()
{
	return installedPluginsInReg;
}


std::map<QString, CPluginDescription *>& PluginManager::GetPluginDescriptionsMap()
{
	return pluginDescriptionMap;
}

std::map<QString, PluginInstance *>& PluginManager::GetInstalledPluginsMap()
{
	return installedPluginsMap;
}

std::map<QString, PluginInstance *>& PluginManager::GetInstalledPluginsNameMap()
{
	return allInstalledPluginsNamesMap;
}

QString PluginManager::SearchPluginFolders(QString pluginpath)
{
}

void PluginManager::PrintDirs()
{
	QString pluginDir = GetPluginLacotionPath();
	SearchForAllPlugins(pluginDir);
}


QString PluginManager::SearchForAllPlugins(QString pstr)
{	
    QString nameFilter( "*.txt" ); 

	 QStringList filter;
    if (!nameFilter.isEmpty())
        filter << nameFilter;
    QDirIterator it(pstr, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
	int index = 0;
	QString str;
    while (it.hasNext())
	{
        files << it.next();
		str = files.at(index);
		ReadDescriptionFromFolder(str);
		index++;
	}
 
	return "";
}


void PluginManager::ReadDescriptionFromFolder(QString strPath)
{
	ReadPlgTXT(strPath);
}

QString PluginManager::GetPluginFullPath(QString fileName)
{
	// Get the plugin description
    CPluginDescription* InstallingPluginDescription = PluginManager::GetInstance().GetPluginDescriptionsMap()[fileName];

	// Get the full path of the plugin
	QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;
	
	delete InstallingPluginDescription;

    return InstallingPluginFullPath;
}


QString PluginManager::MakeFileNameFromFullPath(QString fullpath)
{
	QFileInfo fi(fullpath);
    
	QString filename = fi.fileName(); 
	
	return filename;
}

std::map<QString, QString>& PluginManager::GetAllPlugedObjectsMap()
{
	return allPlugedObjectsMap;
}

bool PluginManager::doesPluginStillExist(QString pluginName, QString& pluginFullPath)
{
	// get the path the plugins folder
  QString strPath = PluginManager::GetInstance().GetPluginLacotionPath();
  
  // search and find all available plugin and save their descriptions
  PluginManager::GetInstance().SearchForAllPlugins(strPath);

	std::map<QString, CPluginDescription *>::iterator it;
	for (it = PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it)
	{
		if(pluginName == it->second->fileName)
		{
			pluginFullPath = it->second->fullPath;
			PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
			return true;
		}
		      
    }

	return false;

PluginManager::GetInstance().GetPluginDescriptionsMap().clear();

}
