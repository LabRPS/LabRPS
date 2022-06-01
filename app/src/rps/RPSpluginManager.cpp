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
	QString mFileName;
	QString mDisplayName;
	QString theString;
	QString mSystemName;
	QString mRandomPhenomenon;
	QString mPluginAuthor;
	QString mPluginDescription;
	QString mPluginVersion;
	QString mLabRPSVersion;
	QString mAPIVersion;
	QString mPluginReleaseDate;
	QString mPluginSubFolder;
	QString mPluginRPName;
	bool mIsPluginInstalled;
	int mPluginApiVersion;

	QLibrary library;

    typedef const int (*MyPrototypeOne)();
    typedef const char * (*MyPrototypeTwo)();

	bool Load()
	{
		// Load the plugin
		library.setFileName(mPluginSubFolder);
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
	mImpl->mDisplayName = name;
	//mImpl->mFileName = /*GetPluginLacotionPath() + */name /*+ tr(".dll")*/;
	mImpl->mPluginSubFolder = name;
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
		// QString str = tr("Plugin initialization fails");

		// PluginManager::GetInstance().rpsOutputText(str);
		// // AfxMessageBox(str);
		return false;
	}

	// Initialized the plugin
	Impl::MyPrototypeOne init_func = mImpl->GetFunctionPrototypeOne("PluginInit");
	if (!init_func)
		return false;

	// Register the plugin
	int retn = (*init_func)();

	return true;
}

bool PluginInstance::Load()
{
	//load the plugin
	if (!mImpl->Load())
	{		
		return false;
	}

	// Call functions from the plungin (dll) to get information about the plugin
	mImpl->mDisplayName = GetStringFromDllFunct("PluginDisplayName");
	mImpl->mSystemName = GetStringFromDllFunct("PluginSystemName");
	mImpl->mRandomPhenomenon = GetStringFromDllFunct("Phenomenon");
	mImpl->mPluginAuthor = GetStringFromDllFunct("PluginAuthor");
	mImpl->mPluginDescription = GetStringFromDllFunct("PluginDescription");
	mImpl->mPluginVersion = GetStringFromDllFunct("PluginCurrentVersion");
	mImpl->mPluginReleaseDate = GetStringFromDllFunct("PluginReleaseDate");
	mImpl->mLabRPSVersion = GetStringFromDllFunct("Labrpsversion");
	mImpl->mAPIVersion = GetStringFromDllFunct("Apiversion");
	mImpl->mPluginRPName = GetStringFromDllFunct("PlungInThisRP");

	// Initialized the plugin
	Impl::MyPrototypeOne init_func = mImpl->GetFunctionPrototypeOne("InstallPlugin");
	if (!init_func)
		return false;

	// Register the plugin
	mImpl->mPluginApiVersion = (*init_func)();
	mImpl->mIsPluginInstalled = true;

	return true;
}


bool PluginInstance::Unload()
{
	QMessageBox::warning(0,"1","from good");

	// Initialized the plugin
	Impl::MyPrototypeOne Uninstal_func = mImpl->GetFunctionPrototypeOne("UninstallPlugin");
	if (!Uninstal_func)
		return false;

	mImpl->mPluginApiVersion = (*Uninstal_func)();

	return mImpl->Unload();
}

bool PluginInstance::IsLoaded()
{
	return mImpl->library.isLoaded();
}

QString PluginInstance::GetFileName()
{
	return mImpl->mFileName;
}

QString PluginInstance::GetDisplayName()
{
	return mImpl->mDisplayName;
}

QString PluginInstance::GetSystemName()
{
	return mImpl->mSystemName;
}

QString PluginInstance::GetRandomPhenomenon()
{
	return mImpl->mRandomPhenomenon;
}

QString PluginInstance::GetPluginAuthor()
{
	return mImpl->mPluginAuthor;
}

QString PluginInstance::GetPluginDescription()
{
	return mImpl->mPluginDescription;
}

int PluginInstance::GetPluginApiVersion()
{
	return mImpl->mPluginApiVersion;
}

QString PluginInstance::GetPluginVersion()
{
	return mImpl->mPluginVersion;
}

QString PluginInstance::GetLabRPSVersion()
{
	return mImpl->mLabRPSVersion;
}

QString PluginInstance::GetAPIVersion()
{
	return mImpl->mAPIVersion;
}

QString PluginInstance::GetPluginSbubFolder()
{
	return mImpl->mPluginSubFolder;
}


QString PluginInstance::GetPluginReleaseDate()
{
	return mImpl->mPluginReleaseDate;
}

QString PluginInstance::GetPluginRPName()
{
	return mImpl->mPluginRPName;
}


QString PluginInstance::GetPluginLacotionPath()
{
// 	TCHAR szBuff[_MAX_PATH];
// 	::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH);
// 	QString filename(szBuff);
// 	filename.MakeUpper();

// #if defined _DEBUG
// 	QString exe_file = tr("DEBUG\\LABRPS.EXE");
// 	int loc;
// #else
// 	// if "Release" is in the path, remove it (this happens when testing release builds)
// 	int loc = filename.Find(tr("RELEASE\\"));
// 	if (loc != -1)
// 		filename.replace(("RELEASE\\"), tr(""));

// 	QString exe_file = tr("LABRPS.EXE");
// #endif
// 	loc = filename.Find(exe_file);
// 	if (loc == -1)
// 	{
// 		// something is wrong... that find should have succeeded
// 		// hard code the default install location so that there is a remote chance of success
// 		filename = tr("C:\\PROGRAM FILES\\LAB RPS\\LABRPS\\");
// 	}
// 	else
// 	{
// 		filename.Replace(exe_file, tr(""));
// 	}

// 	// Get the help file location path. Note that the help file should be added the INSTALLDIR in installshield when deploying
// 	QString strPluginLacotionPath = _tcsdup(filename + tr("Plugins\\"));

// 	return strPluginLacotionPath;
return "";
}


PluginManager::PluginManager()
{
	//QString pluginpath;
	////SearchPluginFolders(pluginpath);
	//PrintDirs();
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
	// hardcode loading our 2 example plugins
	// in reality, this would search for all plugins to load
	//Load(tr("plugin1"));
	SearchPlugin();
	return true;
}

bool PluginManager::Load(const QString &name)
{
	// have we already loaded this plugin?
	static std::set<QString> loaded;
	if (loaded.find(name) != loaded.end())
		return true;

	// Now make the file name
	QString filename = MakeFileNameFromFullPath(name);

	// // Send text to output pane
	// QString str;
	// str.LoadString(IDS_LOADING_PLUGIN);
	// rpsOutputText(filename + str);

	// try to load this plugin
	PluginInstance *pi = new PluginInstance(name);
	if (!pi->Load())
	{
		delete pi;
		return false;
	}

	// success! add the plugin to our manager
	mPlugins.push_back(pi);

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
	QMessageBox::warning(0,"1","from bad");
	// not implemented yet
	return false;
}

std::vector<PluginInstance *> PluginManager::GetAllPlugins()
{
	// If we had an external metadata file that described all of the
	// plugins, this would be the point where we load that file -
	// without loading the actual plugins.  Without that external
	// metadata, we need to load all plugins.
	LoadAll();
	
	return mPlugins;
}

QString PluginManager::GetPluginLacotionPath()
{
	// get the directory of the application
  QString appPath = QFileInfo(QCoreApplication::applicationFilePath()).path();

  // construct the plugin directory
  m_strPluginLacotionPath =  appPath + "/plugins/";

	return m_strPluginLacotionPath;
}

// search plugin
void PluginManager::SearchPlugin()
{
	// //QString strPath = GetApplicationPath();
	// QString strPath = GetPluginLacotionPath();
	// strPath += tr("*.dll");

	// CFileFind find;
	// BOOL bIsFind = find.FindFile(strPath);
	// while (bIsFind)
	// {
	// 	bIsFind = find.FindNextFile();

	// 	if (find.IsDots())
	// 		continue;
	// 	else if (find.IsDirectory())
	// 		continue;
	// 	else
	// 	{
	// 		QString strFileName = find.GetFileName();
	// 		// load dll
	// 		Load(strFileName);
	// 	}
	// }
}

QString PluginManager::GetApplicationPath()
{
	// TCHAR filename[_MAX_PATH];
	// TCHAR drive[_MAX_DRIVE];
	// TCHAR path[_MAX_PATH];

	// GetModuleFileName(AfxGetInstanceHandle(), filename, MAX_PATH);
	// _wsplitpath_s(filename, drive, _MAX_DRIVE, path, _MAX_PATH, NULL, 0, NULL, 0);

	// QString strLocation(drive);
	// strLocation += path;

	// return strLocation;

	return "";
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
	return mImpl->mIsPluginInstalled;
}

void PluginInstance::SetInstallationState(bool state)
{
   bIsInstalled = state;
}


bool PluginManager::InitializePlugin(const QString &name, int instUninstMOd)
{
		// have we already loaded this plugin?
		static std::set<QString> loaded;
		//if (loaded.find(name) != loaded.end())
		QString filename;

		if ((1 == instUninstMOd) || (3 == instUninstMOd))
		{
		
		
			// Now make the file name
			filename = MakeFileNameFromFullPath(name);

			// // Send text to output pane
			// QString str;
			// str.LoadString(IDS_STR_INSTALLING_PLG);
			// rpsOutputText(filename + str);

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
	
	//if (loaded.find(name) != loaded.end())
	QString filename;
	
	// Now make the file name
	filename = MakeFileNameFromFullPath(name);

	// // Send text to output pane
	// QString str;
	// str.LoadString(IDS_STR_INSTALLING_PLG);
	// rpsOutputText(filename + str);

	// try to load this plugin
	PluginInstance *pi = new PluginInstance(name);
	if (!pi->Load())
	{
		delete pi;
		return false;
	}

	//// success! add the plugin to the installed plugins vector
	//mInstalledPlugins.push_back(pi);

	// success! add the plugin to the installed plugins map
	mInstalledPluginsMap[pi->GetPluginSbubFolder()] = pi;
	mAllInstalledPluginsNamesMap[pi->GetDisplayName()] = pi;

	// Populate combo box containing RP
	/*InstallPRPL(pi);*/

	// and don't try to load it again
	//loaded.insert(name);

	// Now make the file name
	filename = MakeFileNameFromFullPath(name);

	// // Report sucess
	// // Send text to output pane
	// str.LoadString(IDS_STR_SUCESS_INSTALL);
	// rpsOutputText(filename + str);
	// AfxMessageBox(filename + str);

	// // Update the plugged objects tree
	// CLabRPSMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CLabRPSMainFrame, AfxGetMainWnd());

	// pMainFrame->GetPLuggedObjectPane().FillPluggedObjectsTree();

	return true;
}


bool PluginManager::InstallPluginInReg(const QString &name)
{
	// Now make the file name
	QString filename = MakeFileNameFromFullPath(name);

	// // Send text to output pane
	// QString str;
	// str.LoadString(IDS_STR_INSTALLING_PLG);
	// rpsOutputText(filename + str);

	// try to load this plugin
	PluginInstance *pi = new PluginInstance(name);
	if (!pi->Load())
	{
		delete pi;
		return false;
	}


	// Success! add the plugin to the installed plugins map
	mInstalledPluginsMap[pi->GetPluginSbubFolder()] = pi;
	mAllInstalledPluginsNamesMap[pi->GetDisplayName()] = pi;

	// // Report sucess
	// // Send text to output pane
	// str.LoadString(IDS_STR_SUCESS_INSTALL);
	// rpsOutputText(filename + str);

	// // Update the plugged objects tree
	// CLabRPSMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CLabRPSMainFrame, AfxGetMainWnd());
	// pMainFrame->GetPLuggedObjectPane().FillPluggedObjectsTree();

	return true;
}

bool PluginManager::UnInstallPlugin(const QString &name)
{
	// Now make the file name
	QString filename = MakeFileNameFromFullPath(name);

	if (mInstalledPluginsMap.find(name) != mInstalledPluginsMap.end())
	{
		// Uninstall the plugin its corresponding map
		mInstalledPluginsMap[name]->Unload();

		// Set it as not installed
		mInstalledPluginsMap.erase(name);
	}

	if (mAllInstalledPluginsNamesMap.find(filename) != mAllInstalledPluginsNamesMap.end())
	{
		// Uninstall the plugin its corresponding map
		mAllInstalledPluginsNamesMap[filename]->Unload();

		// Set it as not installed
		mAllInstalledPluginsNamesMap.erase(filename);
	}

	

	// QString str;
	// str.LoadString(IDS_STR_NOT_INSTALLED3);
	// rpsOutputText(filename + str);
	// AfxMessageBox(filename + str);


	// // Update the plugged objects tree
	// CLabRPSMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CLabRPSMainFrame, AfxGetMainWnd());
	// pMainFrame->GetPLuggedObjectPane().FillPluggedObjectsTree();

	return true;
}


void PluginManager::ReadDescription()
{
	// //QString strPath = GetApplicationPath();
	// QString strPath = GetPluginLacotionPath();
	// strPath += tr("*.txt");

	// CFileFind find;
	// BOOL bIsFind = find.FindFile(strPath);
	// while (bIsFind)
	// {
	// 	bIsFind = find.FindNextFile();

	// 	if (find.IsDots())
	// 		continue;
	// 	else if (find.IsDirectory())
	// 		continue;
	// 	else
	// 	{
	// 		QString strFileName = find.GetFileName();
	// 		// Read .txt
	// 		ReadPlgTXT(GetPluginLacotionPath() + strFileName);
	// 	}
	// }
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
			Description->m_strFileName = line;
		}
		else if(true == line.contains("PluginName: "))
		{
			line.replace("PluginName: ", "");
			Description->m_strName = line;
		}
		else if (true == line.contains("RandomPhenomenon: "))
		{
			line.replace("RandomPhenomenon: ", "");
			Description->m_strType = line;
		}
		else if (true == line.contains("PluginReleaseDate: "))
		{
			line.replace("PluginReleaseDate: ", "");
			Description->m_strReleaseDate = line;
		}
		else if (true == line.contains("PluginAuthors: "))
		{
			line.replace("PluginAuthors: ", "");
			Description->m_strAuthors = line;
		}
		else if (true == line.contains("PluginVersion: "))
		{
			line.replace("PluginVersion: ", "");
			Description->m_strVersion = line;
		}
		else if (true == line.contains("PluginDescription: "))
		{
			line.replace("PluginDescription: ", "");
			Description->m_strDescription = line;
		}
	   }
    
      }
        inputFile.close();
    }

	// Make the plugin full path
	QString fullpah = path;
	fullpah.replace(".txt", ".dll");

	// Save the plugin full path
	Description->m_strFullPath = fullpah;

	//// success! add the plugin descriptions to our manager
	//mPluginDescriptions.push_back(Description);

	PluginDescriptionMap[Description->m_strFileName] = Description;

	/*delete Description;*/
	return true;
}


//std::vector<CPluginDescription *>& PluginManager::GetPluginDescriptionsVector()
//{
//	return mPluginDescriptions;
//}

//std::vector<PluginInstance *>& PluginManager::GetInstalledPluginsVector()
//{
//	return mInstalledPlugins;
//}

std::vector<QString>& PluginManager::GetInstalledPluginsInRegVector()
{
	return mInstalledPluginsInReg;
}


std::map<QString, CPluginDescription *>& PluginManager::GetPluginDescriptionsMap()
{
	return PluginDescriptionMap;
}

std::map<QString, PluginInstance *>& PluginManager::GetInstalledPluginsMap()
{
	return mInstalledPluginsMap;
}

std::map<QString, PluginInstance *>& PluginManager::GetInstalledPluginsNameMap()
{
	return mAllInstalledPluginsNamesMap;
}

//std::map<QString, QString>& PluginManager::GetAllRPMap()
//{
//	return mAllRPMap;
//}
//void PluginManager::InstallPRPL(PluginInstance * pi)
//{
//		// If the plugin is of type PRPL then save it in the document
//		if (tr("PRPL") == pi->GetPluginType())
//		{
//			mAllRPMap[pi->GetPluginSbubFolder()] = pi->GetDisplayName();
//		}
//}

QString PluginManager::SearchPluginFolders(QString pluginpath)
{
	// WIN32_FIND_DATA FindFileData;
	// HANDLE hFind;
	// std::vector<QString> MyVect;

	// QString pluginDir = GetPluginLacotionPath();

	// hFind = FindFirstFile(pluginDir, &FindFileData);
	// do
	// {
	// 	if (FindFileData.dwFileAttributes == 16)
	// 	{
	// 		MyVect.push_back(FindFileData.cFileName);
	// 	}
	// } while (FindNextFile(hFind, &FindFileData));


	// //Now run in a loop of all the files and folders under this folder
	// while (hFind)
	// {
	// 	//Ignore system directories "." and ".." the good old MS-DOS days

	// 		//Check if the current object is a Folder or a File
	// 		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	// 		{

	// 		}
	// 		else if
	// 			(!((FindFileData.dwFileAttributes &  FILE_ATTRIBUTE_TEMPORARY)
	// 				|| (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)))
	// 		{
				
	// 		}

	// 	}
	// 	if (!FindNextFile(hFind, &FindFileData))
	// 	{
	// 		//If nothing is found , make hFile NULL so that
	// 		//we get out of the while loop
	// 		FindClose(hFind);
	// 		hFind = NULL;
	// 	}



	// FindClose(hFind);

	// return pluginDir;

	return "";

}


void PluginManager::Recurse(QString pstr)
{
	// CFileFind finder;

	// // build a string with wildcards
	// QString strWildcard(pstr);
	// strWildcard += tr("\\*.*");

	// // start working for files
	// BOOL bWorking = finder.FindFile(strWildcard);

	// while (bWorking)
	// {
	// 	bWorking = finder.FindNextFile();

	// 	// skip . and .. files; otherwise, we'd 
	// 	// recur infinitely! 

	// 	if (finder.IsDots())
	// 		continue;

	// 	// if it's a directory, recursively search it 

	// 	if (finder.IsDirectory())
	// 	{
	// 		QString str = finder.GetFilePath();
	// 		TRACE(tr("%s\n"), (LPCTSTR)str);
	// 		Recurse(str);
	// 	}
	// }

	// finder.Close();
}

void PluginManager::PrintDirs()
{
	QString pluginDir = GetPluginLacotionPath();
	SearchForAllPlugins(pluginDir);
}


QString PluginManager::SearchForAllPlugins(QString pstr)
{	
	//QString strPath = GetPluginLacotionPath();
	// QString strPath = "E:\\NewLabRPSProject\\Staffs\\LabRPS\\LabRPS\\plugins";
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

QString PluginManager::GetPluginFullPath(QString FileName)
{
	// Get the plugin description
	CPluginDescription* InstallingPluginDescription = PluginManager::GetInstance().GetPluginDescriptionsMap()[FileName];

	// Get the full path of the plugin
	QString InstallingPluginFullPath = InstallingPluginDescription->m_strFullPath;
	
	delete InstallingPluginDescription;

    return InstallingPluginFullPath;
}


QString PluginManager::MakeFileNameFromFullPath(QString fullpath)
{
	QFileInfo fi(fullpath);
    
	QString filename = fi.fileName(); 
	
	return filename;
}

void PluginManager::InstallPOLR(PluginInstance * pi)
{
	// If the plugin is of type PRPL then save it in the document
	if ("POLR" == pi->GetRandomPhenomenon())
	{

	}
}

std::map<QString, QString>& PluginManager::GetAllPlugedObjectsMap()
{
	return mAllPlugedObjectsMap;
}
