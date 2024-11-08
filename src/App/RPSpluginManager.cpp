#include "PreCompiled.h"
#include "RPSpluginManager.h"
#include <fstream>
#include <string>
#include <map>
#include <set>

#include <QLibrary>
#include <QByteArray>
#include <QDirIterator>
#include <QTextStream>
#include <QFileInfo>
#include <QCoreApplication>
#include <QFile>
#include <QSettings>

#include <App/Application.h>
#include <App/WindLabUtils.h>
#include <App/SeismicLabUtils.h>
#include <App/SeaLabUtils.h>

using namespace std;
using namespace App;

class AppExport PluginInstance::Impl
{
public:

    // plugin name
	QString pluginName;

	// plugin file name
    QString fileName;

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

    // a string
    QString theString;

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

    QString getLabRPSVersion()
    {
        return QString::fromLatin1("0.1");
    }

    QString getWindLabAPIVersion()
    {
        return QString::fromLatin1("0.1");
    }
	QString getSeismicLabAPIVersion()
    {
        return QString::fromLatin1("0.1");
    }
	QString getSeaLabAPIVersion()
    {
        return QString::fromLatin1("0.1");
    }
    QString getUserAPIVersion()
    {
        return QString::fromLatin1("0.1");
    }

};


PluginInstance::PluginInstance(const QString &name)
{
	mImpl = new Impl;
	mImpl->pluginSubFolder = name;
}

PluginInstance::~PluginInstance()
{
	delete mImpl;
}

bool PluginInstance::Initialize(QString &information)
{
    //load the plugin
    if (!mImpl->Load()) {
        return false;
    }

	const QString pluginName = GetStringFromDllFunct(QString::fromLatin1("PluginName"));
    const QString labRPSVersion = GetStringFromDllFunct(QString::fromLatin1("Labrpsversion"));
    const QString apiVersion = GetStringFromDllFunct(QString::fromLatin1("Apiversion"));
    const QString randomPhenomenon = GetStringFromDllFunct(QString::fromLatin1("Phenomenon"));

    Impl::MyPrototypeOne init_func = mImpl->GetFunctionPrototypeOne("PluginInit");

	if (!checkVersion(labRPSVersion.toStdString(), mImpl->getLabRPSVersion().toStdString()))
	{
		Base::Console().Warning("The LabRPS version(%s) of your plugin '%s' is not compatible with the current version(%s) of LabRPS.\n", labRPSVersion.toStdString().c_str(), pluginName.toStdString().c_str(), mImpl->getLabRPSVersion().toStdString().c_str());
        return false;
	}

	if (randomPhenomenon == App::WindLabUtils::rpsPhenomenonWindVelocity)
	{
		if (!checkVersion(apiVersion.toStdString(), mImpl->getWindLabAPIVersion().toStdString()))
		{
			Base::Console().Warning("The plugin API version(%s) of your plugin '%s' is not compatible with the current version(%s) of Plugin API.\n", apiVersion.toStdString().c_str(), pluginName.toStdString().c_str(), mImpl->getWindLabAPIVersion().toStdString().c_str());
			return false;
		}
	}
	else if (randomPhenomenon == App::SeismicLabUtils::rpsPhenomenonGroundMotion)
	{
		if (!checkVersion(apiVersion.toStdString(), mImpl->getSeismicLabAPIVersion().toStdString()))
		{
			Base::Console().Warning("The plugin API version(%s) of your plugin '%s' is not compatible with the current version(%s) of Plugin API.\n", apiVersion.toStdString().c_str(), pluginName.toStdString().c_str(), mImpl->getSeismicLabAPIVersion().toStdString().c_str());
			return false;
		}
	}
	else if (randomPhenomenon == App::SeaLabUtils::rpsPhenomenonSeaSurface)
	{
		if (!checkVersion(apiVersion.toStdString(), mImpl->getSeaLabAPIVersion().toStdString()))
		{
			Base::Console().Warning("The plugin API version(%s) of your plugin '%s' is not compatible with the current version(%s) of Plugin API.\n", apiVersion.toStdString().c_str(), pluginName.toStdString().c_str(), mImpl->getSeaLabAPIVersion().toStdString().c_str());
			return false;
		}
	}

	if (!init_func)
        return false;

    // register the plugin
    (*init_func)();
    return true;
}

bool PluginInstance::InitializeType()
{
    if (!mImpl->Load()) {
        return false;
    }

    Impl::MyPrototypeOne init_func_type = mImpl->GetFunctionPrototypeOne("PluginInitType");
    
	if (!init_func_type)
        return false;

    // register the plugin object type
    (*init_func_type)();
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
    mImpl->pluginName = GetStringFromDllFunct(QString::fromLatin1("PluginName"));
    mImpl->randomPhenomenon = GetStringFromDllFunct(QString::fromLatin1("Phenomenon"));
    mImpl->pluginAuthor = GetStringFromDllFunct(QString::fromLatin1("PluginAuthor"));
    mImpl->pluginDescription = GetStringFromDllFunct(QString::fromLatin1("PluginDescription"));
    mImpl->pluginVersion = GetStringFromDllFunct(QString::fromLatin1("PluginCurrentVersion"));
    mImpl->pluginReleaseDate = GetStringFromDllFunct(QString::fromLatin1("PluginReleaseDate"));
    mImpl->labRPSVersion = GetStringFromDllFunct(QString::fromLatin1("Labrpsversion"));
    mImpl->apiVersion = GetStringFromDllFunct(QString::fromLatin1("Apiversion"));
    
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

QString PluginInstance::GetPluginName()
{
	return mImpl->pluginName;
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


bool PluginManager::Unload(const QString &name)
{
	return false;
}

QString PluginManager::GetPluginLacotionPath(const QString& workbenchName)
{
	// get the directory of the application
  //QString appPath = QFileInfo(QCoreApplication::applicationFilePath()).path();
    //QString appPath = qApp->applicationDirPath();
    QString homePath = QString::fromStdString(App::Application::getHomePath());

	std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {

		pluginLacotionPath =  homePath+ QString::fromLatin1("Plugins/") + workbenchName ;

    }
    else if (PlugLang == "C++") {

		pluginLacotionPath =  homePath+ QString::fromLatin1("Plugins/") + workbenchName ;

    }

	return pluginLacotionPath;
}

QString PluginManager::GetOnlinePluginLacotionPath(const QString& workbenchName)
{

    QString pluginLacotionPath = QString::fromStdString(App::Application::getUserPluginDir());

	return pluginLacotionPath;
}

QString PluginInstance::GetStringFromDllFunct(const QString &name)
{
	QByteArray ba = name.toLocal8Bit();
    const char *c_str = ba.data();
	Impl::MyPrototypeTwo name_string = mImpl->GetFunctionPrototypeTwo(c_str);
	if (name_string)
	{
		const char **ptr = (const char **)name_string;
		mImpl->theString = QString::fromLatin1(*ptr);
		return mImpl->theString;
	}

	return QString::fromLatin1("");
}

bool PluginInstance::GetInstallationState()
{
	return mImpl->isPluginInstalled;
}

void PluginInstance::SetInstallationState(bool state)
{
   isInstalled = state;
}

bool PluginInstance::checkVersion(std::string versions, std::string currentVersion) {
    std::string myVersion = versions; 
	transform(versions.begin(), versions.end(), versions.begin(), ::tolower);
	if (strcmp(versions.c_str(), "all") == 0)
        return true;

	// Tokenize the comma-separated list
    std::stringstream stream(versions);
    std::string version;
    while (std::getline(stream, version, ','))
        if (strcmp(version.c_str(), currentVersion.c_str()) == 0)
            return true;
    return false;
}

bool PluginManager::InitializePlugin(const QString &name, int instUninstMOd, QString &information)
{
		// have we already loaded this plugin?
		static std::set<QString> loaded;
		
		if ((1 == instUninstMOd) || (3 == instUninstMOd))
		{		
			// try to load this plugin
			PluginInstance *pi = new PluginInstance(name);
			
            if (!pi->Initialize(information))
			{
				delete pi;
				return false;
			}
			delete pi;
		}
			
	return true;
}

bool PluginManager::InitializePluginType(const QString &name, int instUninstMOd)
{ 
	
		if ((1 == instUninstMOd) || (3 == instUninstMOd))
		{		
			// try to load this plugin
			PluginInstance *pi = new PluginInstance(name);
			
            if (!pi->InitializeType())
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
    allInstalledPluginsNamesMap[pi->GetPluginName()] = pi;

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
    allInstalledPluginsNamesMap[pi->GetPluginName()] = pi;

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

bool PluginManager::ReadPlgTXT(const QString& path, const QString& phenomenon, const int& source)
{
    QFile inputFile(path);

	PluginDescription* Description = new PluginDescription();

    if (inputFile.open(QIODevice::ReadOnly)){

	// Temporarly variable to contain each line
	QString line;
      
	  // start reading the file
	  QTextStream in(&inputFile);

	   while (!in.atEnd()){
       line = in.readLine();

	   if(!line.isNull()){

		if (true == line.contains(QString::fromLatin1("__Name__ = ")))
		{
			line.replace(QString::fromLatin1("__Name__ = "), QString::fromLatin1(""));
            Description->fileName = line.remove(QChar::fromLatin1('"'), Qt::CaseInsensitive);
            Description->name = line.remove(QChar::fromLatin1('"'), Qt::CaseInsensitive);
		}
		else if (true == line.contains(QString::fromLatin1("__Phenomenon__ = ")))
		{
			line.replace(QString::fromLatin1("__Phenomenon__ = "), QString::fromLatin1(""));
            Description->type = line.remove(QChar::fromLatin1('"'), Qt::CaseInsensitive);
		}
		else if (true == line.contains(QString::fromLatin1("__Date__ = ")))
		{
			line.replace(QString::fromLatin1("__Date__ = "), QString::fromLatin1(""));
            Description->releaseDate = line.remove(QChar::fromLatin1('"'), Qt::CaseInsensitive);
		}
		else if (true == line.contains(QString::fromLatin1("__Author__ = ")))
		{
			line.replace(QString::fromLatin1("__Author__ = "), QString::fromLatin1(""));
            Description->authors = line.remove(QChar::fromLatin1('"'), Qt::CaseInsensitive);
		}
		else if (true == line.contains(QString::fromLatin1("__Version__ = ")))
		{
			line.replace(QString::fromLatin1("__Version__ = "), QString::fromLatin1(""));
            Description->version = line.remove(QChar::fromLatin1('"'), Qt::CaseInsensitive);
		}
		else if (true == line.contains(QString::fromLatin1("__Comment__ = ")))
		{
			line.replace(QString::fromLatin1("__Comment__ = "), QString::fromLatin1(""));
            Description->description = line.remove(QChar::fromLatin1('"'), Qt::CaseInsensitive);
		}
	   }
    
      }
        inputFile.close();
    }

	// Make the plugin full path
	QString fullpah = path;
	fullpah.replace(QString::fromLatin1(".txt"), QString::fromLatin1(".dll"));

	// Save the plugin full path
	Description->fullPath = fullpah;

	if (source == 1)
	{
        Description->source = QString::fromLatin1("Local");
	}
    else if (source == 2) {
        Description->source = QString::fromLatin1("Online");
    }
    else if (source == 3) {
        Description->source = QString::fromLatin1("Custom");
    }

    if (strcmp(Description->type.toUtf8().constData(), phenomenon.toUtf8().constData()) != 0)
    {
        return false;
    }


	pluginDescriptionMap[Description->fileName] = Description;

	return true;
}

std::vector<QString>& PluginManager::GetInstalledPluginsInRegVector()
{
	return installedPluginsInReg;
}


std::map<QString, PluginDescription *>& PluginManager::GetPluginDescriptionsMap()
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

void PluginManager::SearchForAllPlugins(QString pstr, const QString& phenomenon, const int& source)
{
    QString nameFilter(QString::fromLatin1("*.txt") );

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
        ReadDescriptionFromFolder(str,phenomenon, source);
		index++;
	}
 }


void PluginManager::ReadDescriptionFromFolder(QString strPath, const QString& phenomenon, const int & source)
{
    ReadPlgTXT(strPath, phenomenon, source);
}

QString PluginManager::GetPluginFullPath(QString fileName)
{
	// Get the plugin description
    PluginDescription* InstallingPluginDescription = PluginManager::GetInstance().GetPluginDescriptionsMap()[fileName];

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

bool PluginManager::doesPluginStillExist(QString pluginName, QString& pluginFullPath, const QString& workbenchName, const QString& phenomenon, const int& source)
{
	// get the path to the plugins folder
  QString strPath = PluginManager::GetInstance().GetPluginLacotionPath(workbenchName);
  
  // search and find all available plugin and save their descriptions
  PluginManager::GetInstance().SearchForAllPlugins(strPath, phenomenon, source);

	std::map<QString, PluginDescription *>::iterator it;
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
}
