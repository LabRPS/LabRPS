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


#include "PreCompiled.h"

#ifndef _PreComp_
# include <qobject.h>
#endif

#include "Workbench.h"
#include <Gui/MenuManager.h>
#include <Gui/ToolBarManager.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/RPSUserDefinedPhenomenonLabAPI.h>
#include <Mod/UserDefinedPhenomenonLab/App/UserDefinedPhenomenonLabUtils.h>
#include <Mod/UserDefinedPhenomenonLab/App/UserDefinedPhenomenonLabSimulation.h>
#include <Mod/UserDefinedPhenomenonLab/Gui/UserDefinedPhenomenonLabSimulationObserver.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/MainWindow.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/RPSUserDefinedPhenomenonLabpluginAPI.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/UserDefinedPhenomenonLabFeatureDescription.h>

#include <App/RPSpluginManager.h>

#define GLWAVE 4558

using namespace UserDefinedPhenomenonLabGui;
using namespace UserDefinedPhenomenonLabAPI;


#if 0 // needed for Qt's lupdate utility
    qApp->translate("CommandGroup", "UserDefinedPhenomenonLab");

#endif

/// @namespace UserDefinedPhenomenonLabGui @class Workbench
TYPESYSTEM_SOURCE(UserDefinedPhenomenonLabGui::Workbench, Gui::StdWorkbench)

Workbench::Workbench()
{
    ParameterGrp::handle hGrp;

    hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Plugins");
    hGrp->SetASCII("Installed Plugins", "Plugin 1");

    ULReadAllTobeInstallObjVersionToRegistry();
    ULReadAllTobeInstallObjPublicationTitleToRegistry();
    ULReadAllTobeInstallObjPublicationLinkToRegistry();
    ULReadAllTobeInstallObjPublicationAuthorToRegistry();
    ULReadAllTobeInstallObjPublicationDateToRegistry();

    // read install userDefinedPhenomenon from registry if any
    ULReadAllTobeInstallObjectsFromRegistry();
    ULClearAllTobeInstallObjectsFromRegistry();

    IntallRegistryPlugins();
}

Workbench::~Workbench()
{
    RPSWriteInstalledPluginsToRegistry();

    ULWriteAllTobeInstallObjPublicationTitleToRegistry();
    ULWriteAllTobeInstallObjPublicationLinkToRegistry();
    ULWriteAllTobeInstallObjPublicationAuthorToRegistry();
    ULWriteAllTobeInstallObjPublicationDateToRegistry();
    ULWriteAllTobeInstallObjVersionToRegistry();

    ULWriteAllTobeInstallObjectsToRegistry();

}

Gui::MenuItem* Workbench::setupMenuBar() const
{
    Gui::MenuItem* root = StdWorkbench::setupMenuBar();
    Gui::MenuItem* item = root->findItem("&Windows");

    Gui::MenuItem* userDefinedPhenomenon = new Gui::MenuItem;
    root->insertItem(item, userDefinedPhenomenon);
    userDefinedPhenomenon->setCommand("&UserDefinedPhenomenonLab");
    *userDefinedPhenomenon << "UserDefinedPhenomenonLab_NewSimulation"
             << "UserDefinedPhenomenonLab_Features"
            //  << "UserDefinedPhenomenonLab_Comparison"
             << "UserDefinedPhenomenonLab_Examples";
    

    return root;
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();

     Gui::ToolBarItem* UserDefinedPhenomenonLabToolBar = new Gui::ToolBarItem(root);
    UserDefinedPhenomenonLabToolBar->setCommand("UserDefinedPhenomenonLab Features");
     *UserDefinedPhenomenonLabToolBar << "UserDefinedPhenomenonLab_NewSimulation"
                     << "UserDefinedPhenomenonLab_Features"
                    //  << "UserDefinedPhenomenonLab_Comparison"
                     << "UserDefinedPhenomenonLab_Examples";

     return root;
}

Gui::ToolBarItem* Workbench::setupCommandBars() const
{
    // UserDefinedPhenomenonLab tools
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    return root;
}

//--------------------------------------------------------------------------------------------------
//plugins and features storing staff
//---------------------------------------------------------------------------------

bool UserDefinedPhenomenonLabGui::Workbench::getToBeInstalledObjectsList(std::map<const std::string, std::string>& lstObject, QString pluginName) const
{
    lstObject.clear();

    try
    {
       UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::getObjects(CrpsSimulationMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::objGroupSimulationMethod.toStdString());
    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool UserDefinedPhenomenonLabGui::Workbench::getToBeUninstalledObjectsList(std::map<const std::string, std::string>& lstObject, QString pluginName) const
{
    lstObject.clear();
    try
    {
       UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::getObjects(CrpsSimulationMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::objGroupSimulationMethod.toStdString());
    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool UserDefinedPhenomenonLabGui::Workbench::updateToBeInstalledObjectsMap(const QString& lstObject) const
{
    try
    {
       UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::updateObjectsMap(CrpsSimulationMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool UserDefinedPhenomenonLabGui::Workbench::updateToBeUninstalledObjectsMap(const QString name, const QString pluginName) const
{
    try
    {
       UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::updateObjectToSkipMap(CrpsSimulationMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool UserDefinedPhenomenonLabGui::Workbench::isObjectInstalled(QString& object) const
{
    if (UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::isThisObjectInstalled(CrpsSimulationMethodFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    
    return false;
}

void UserDefinedPhenomenonLabGui::Workbench::emptyAllToBeUninstalledObjectsMap() const
{
    try
    {
        CrpsSimulationMethodFactory::GetOjectsSkipDuringUnintallationMap().clear();
    }
    catch (const std::exception& e)
    {

    }
}

bool UserDefinedPhenomenonLabGui::Workbench::isThisPluginInstalled(const QString& pluginName) const
{
    if (UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsSimulationMethodFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    return false;
}

QString UserDefinedPhenomenonLabGui::Workbench::getPhenomenonName() const
{
    return UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::rpsPhenomenonWindVelocity;
}

void UserDefinedPhenomenonLabGui::Workbench::ULReadAllTobeInstallObjectsFromRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethod"), count = 1;
    ReadMapFromRegistry2(CrpsSimulationMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULWriteAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethodTitle"), count = 1;
    WriteMapToRegistry(CrpsSimulationMethodFactory::GetTitleMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULReadAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethodTitle"), count = 1;
    ReadMapFromRegistry(CrpsSimulationMethodFactory::GetTitleMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULWriteAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethodLink"), count = 1;
    WriteMapToRegistry(CrpsSimulationMethodFactory::GetLinkMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULReadAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethodLink"), count = 1;
    ReadMapFromRegistry(CrpsSimulationMethodFactory::GetLinkMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULWriteAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethodAuthor"), count = 1;
    WriteMapToRegistry(CrpsSimulationMethodFactory::GetAuthorMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULReadAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethodAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSimulationMethodFactory::GetAuthorMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULWriteAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethodDate"), count = 1;
    WriteMapToRegistry(CrpsSimulationMethodFactory::GetDateMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULReadAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethodDate"), count = 1;
    ReadMapFromRegistry(CrpsSimulationMethodFactory::GetDateMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::WriteMapToRegistry(std::map<const std::string, std::string>& map,
                                              QString& settingsGroup, int& count)
{

    if (map.empty()) {
        return;
    }

    QStringList mapkeylst;
    QStringList mapvaluelst;

    // Iterate though the map
    for (auto it1 = map.begin(); it1 != map.end(); ++it1) {
        mapkeylst.append(QLatin1String(it1->first.c_str()));
        mapvaluelst.append(QLatin1String(it1->second.c_str()));
    }

    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.setValue(QLatin1String("mapkey"), mapkeylst);
    settings.setValue(QLatin1String("mapValue"), mapvaluelst);
    settings.endGroup();

    count++;
}

void UserDefinedPhenomenonLabGui::Workbench::ReadMapFromRegistry(std::map<const const std::string, std::string>& map,
                                               QString& settingsGroup, int& count)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    QStringList mapkeylst = settings.value(QLatin1String("mapkey")).toStringList();
    QStringList mapvaluelst = settings.value(QLatin1String("mapValue")).toStringList();
    settings.endGroup();

    if (mapkeylst.isEmpty()) {
        return;
    }

    for (int i = 0; i < mapkeylst.size(); ++i) {
        std::string key = mapkeylst.at(i).toUtf8().constData();
        std::string value = mapvaluelst.at(i).toUtf8().constData();

        map[key] = value;
    }

    count++;
}

void UserDefinedPhenomenonLabGui::Workbench::WriteMapToRegistry2(std::map<const const std::string, std::string>& map,
                                               QString& settingsGroup, int& count)
{

    if (map.empty()) {
        return;
    }

    QStringList mapkeylst;
    QStringList mapvaluelst;

    // Iterate though the map
    for (auto it1 = map.begin(); it1 != map.end(); ++it1) {
        mapkeylst.append(QString::fromUtf8(it1->first.c_str()));
        mapvaluelst.append(QString::fromUtf8(it1->second.c_str()));
    }

    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.setValue(QString::fromLatin1("mapkey"), mapkeylst);
    settings.setValue(QString::fromLatin1("mapValue"), mapvaluelst);
    settings.endGroup();

    count++;
}

void UserDefinedPhenomenonLabGui::Workbench::ReadMapFromRegistry2(std::map<const const std::string, std::string>& map, QString& settingsGroup, int& count)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    QStringList mapkeylst = settings.value(QString::fromLatin1("mapkey")).toStringList();
    QStringList mapvaluelst = settings.value(QString::fromLatin1("mapValue")).toStringList();
    settings.endGroup();

    if (mapkeylst.isEmpty()) {
        return;
    }

    for (int i = 0; i < mapkeylst.size(); ++i) {
        std::string key = mapkeylst.at(i).toUtf8().constData();
        std::string value = mapvaluelst.at(i).toUtf8().constData();

        map[key] = value;
        App::PluginManager::GetInstance().GetAllPlugedObjectsMap()[mapkeylst.at(i)] = mapvaluelst.at(i);
    }

    count++;
}

void UserDefinedPhenomenonLabGui::Workbench::ULWriteAllTobeInstallObjectsToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethod"), count = 1;
    WriteMapToRegistry(CrpsSimulationMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);
}


void UserDefinedPhenomenonLabGui::Workbench::ULWriteAllTobeInstallObjVersionToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethodVersion"), count = 1;
    WriteMapToRegistry(CrpsSimulationMethodFactory::GetVersionMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULReadAllTobeInstallObjVersionToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethod"), count = 1;
    ReadMapFromRegistry(CrpsSimulationMethodFactory::GetVersionMap(), settingsGroup, count);
}

void UserDefinedPhenomenonLabGui::Workbench::ULClearAllTobeInstallObjectsFromRegistry()
{
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("ULSimMethod");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = QString::fromLatin1("ULSimMethodLink");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = QString::fromLatin1("ULSimMethodAuthor");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = QString::fromLatin1("ULSimMethodDate");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = QString::fromLatin1("ULSimMethodVersion");
    ClearMapFromRegistry(settingsGroup);

}



void UserDefinedPhenomenonLabGui::Workbench::ClearMapFromRegistry(QString& settingsGroup)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.remove(QString::fromLatin1(""));// removes the group, and all it keys
    settings.endGroup();
}



int UserDefinedPhenomenonLabGui::Workbench::RPSWriteInstalledPluginsToRegistry()
{
    int i = 1;
    QString PlgName;
    QString Descript;

    // number of plugins to be installed
    int NberOfInstalledPlugins = App::PluginManager::GetInstance().GetInstalledPluginsMap().size();

    QSettings settings;
    settings.beginGroup(QLatin1String("UserDefinedPhenomenonLabToBeInstalledPlugins"));
    settings.setValue(QLatin1String("UserDefinedPhenomenonLabToBeInstalledPluginsNumber"), NberOfInstalledPlugins);

    std::map<QString, App::PluginInstance*>::iterator it;
    for (it = App::PluginManager::GetInstance().GetInstalledPluginsMap().begin();
         it != App::PluginManager::GetInstance().GetInstalledPluginsMap().end(); ++it) {
        // Get the plugin names
        Descript = it->second->GetPluginSubFolder();// 
        if (Descript.contains(QString::fromLatin1("UserDefinedPhenomenonLab")))
        {
            // Make a name of each plugin to be saved
            PlgName = QLatin1String("%1").arg(i);

            settings.setValue(PlgName, Descript);
        }

        i++;
    }

    settings.endGroup();

    return 1;
}

bool UserDefinedPhenomenonLabGui::Workbench::IntallRegistryPlugins()
{
    // Read the installed plugins from registry
    RPSReadInstalledPluginsFromRegistry();
    QString str;

    // Install each of them
    for (int i = 0; i < App::PluginManager::GetInstance().GetInstalledPluginsInRegVector().size(); i++) {
        QString PluginFromReg =
            App::PluginManager::GetInstance().GetInstalledPluginsInRegVector().at(i);

        App::PluginManager::GetInstance().InitializePlugin(PluginFromReg, 1, str);
        App::PluginManager::GetInstance().InitializePluginType(PluginFromReg, 1);
        App::PluginManager::GetInstance().InstallPlugin(PluginFromReg);
    }

    return true;
}

int UserDefinedPhenomenonLabGui::Workbench::RPSReadInstalledPluginsFromRegistry()
{
    RPSReadInstalledPluginsFromRegistryCommon();

    return 1;
}

int UserDefinedPhenomenonLabGui::Workbench::RPSReadInstalledPluginsFromRegistryCommon()
{
    int i = 1;
    QString PlgName;
    QString Descript;

    QSettings settings;

    settings.beginGroup(QLatin1String("UserDefinedPhenomenonLabToBeInstalledPlugins"));
    int NberOfInstalledPlugins = settings.value(QLatin1String("UserDefinedPhenomenonLabToBeInstalledPluginsNumber")).toInt();

    // Read one by one plugins saved in registry
    for (int i = 1; i <= NberOfInstalledPlugins; i++) {
        // Make a name of each plugin to be saved
        PlgName = QLatin1String("%1").arg(i);

        QString value = settings.value(PlgName).toString();

        App::PluginManager::GetInstance().GetInstalledPluginsInRegVector().push_back(value);
    }

    settings.endGroup();

    return 1;
}


std::list<std::string> UserDefinedPhenomenonLabGui::Workbench::getAllPlugins() const
{ 
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("UserDefinedPhenomenonLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("UserDefinedPhenomenonLabWorkbench"));

    QString phenomenon = getPhenomenonName();

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }

    std::map<QString, App::PluginDescription*>::iterator it;
    std::list<std::string> list;
    for (it = App::PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != App::PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it) {
         list.push_back(it->second->name.toUtf8().constData());
     }

    return list; 
}
std::list<std::string> UserDefinedPhenomenonLabGui::Workbench::getAllInstalledPlugins() const
{
    std::list<std::string> list;
    std::list<std::string> items = getAllPlugins();
    for (std::list<std::string>::const_iterator item = items.begin(); item != items.end(); ++item)
         if (isThisPluginInstalled(QString::fromLatin1((*item).c_str())))
         list.push_back(*item);
    return list;
}

bool UserDefinedPhenomenonLabGui::Workbench::installPlugin(const std::string pluginName)
{
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("UserDefinedPhenomenonLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("UserDefinedPhenomenonLabWorkbench"));

    QString phenomenon = getPhenomenonName();

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }

	auto InstallingPluginDescription = App::PluginManager::GetInstance().GetPluginDescriptionsMap()[QString::fromLatin1(pluginName.c_str())];
    if (!InstallingPluginDescription)
         return false;
	QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;
    QString info;
	const bool result = Gui::Application::Instance->InitializePlugin(InstallingPluginFullPath, 1, info);
    if((!result) || (!info.isNull()))
    {
        return false;
    }

     return Gui::Application::Instance->InstallPlugin(InstallingPluginFullPath);

}

bool UserDefinedPhenomenonLabGui::Workbench::unInstallPlugin(const std::string pluginName)
{ 
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("UserDefinedPhenomenonLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("UserDefinedPhenomenonLabWorkbench"));

    QString phenomenon = getPhenomenonName();

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }
    auto InstallingPluginDescription = App::PluginManager::GetInstance().GetPluginDescriptionsMap()[QString::fromLatin1(pluginName.c_str())];
     if (!InstallingPluginDescription)
        return false;
    QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;
    bool ret = Gui::Application::Instance->UnInstallPlugin(InstallingPluginFullPath);
    Gui::Application::Instance->emptyAllToBeUninstalledObjectsMap();
    return ret;
}

void UserDefinedPhenomenonLabGui::Workbench::createSimulation(const std::string simulationName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
    {
        Base::Console().Warning("No valid active document found.\n");
        return;
    }
    std::string uniqueName = doc->getUniqueObjectName(simulationName.c_str());
	 UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* newSim = static_cast< UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->createSimulation(uniqueName, "UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation"));
	UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->setActiveSimulation(newSim);
	App::GetApplication().getActiveDocument()->recompute();
}

void UserDefinedPhenomenonLabGui::Workbench::createFeature(const std::string simulationName, const std::string featureTypeName, const std::string featureName, const std::string featureGroup, const int featureType)
{
    //get the simulation for which this feature will created
	UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* simParent = static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->getSimulation(simulationName));
	if (!simParent)
		return;
	//get all UserDefinedPhenomenonLab feature type
	std::vector<Base::Type> types = simParent->getRPSTypesOfPluggableFeatures();

	//get the type of the creating feature
    Base::Type type = types[featureType];

	//create the feature
	UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature* newFeature = simParent->createFeature(type, featureGroup, featureName);

	if (!newFeature)
		return;

	//set the feature properties
    auto featureProperties = simParent->GetUserDefinedPhenomenonLabFeatureDescription(QString::fromLatin1(featureTypeName.c_str()), QString::fromLatin1(featureGroup.c_str()));
    newFeature->FeatureGroup.setValue(featureTypeName);
    newFeature->FeatureType.setValue(featureGroup);
    newFeature->Author.setValue(featureProperties->Author.getValue());
    newFeature->PublicationTopic.setValue(featureProperties->PublicationTitle.getValue());
    newFeature->PublicationDate.setValue(featureProperties->PublicationDate.getValue());
    newFeature->LinkToPublication.setValue(featureProperties->PublicationLink.getValue());
    newFeature->PublicationAuthor.setValue(featureProperties->PublicationAuthor.getValue());
    newFeature->Version.setValue(featureProperties->Version.getValue());
    newFeature->IsStationary.setValue(featureProperties->Stationarity.getValue());
    newFeature->PluginName.setValue(featureProperties->PluginName.getValue());
    newFeature->PluginVersion.setValue(featureProperties->PluginVersion.getValue());
    newFeature->APIVersion.setValue(featureProperties->APIVersion.getValue());
    newFeature->ReleaseDate.setValue(featureProperties->ReleaseDate.getValue());
	newFeature->Simulation.setValue(simParent->Label.getValue());

	App::DocumentObjectGroup* group = static_cast<App::DocumentObjectGroup*>(static_cast<App::DocumentObject*>(simParent));

    newFeature->recomputeFeature();
	group->addObject(newFeature);

    //show change in the property editor
    simParent->setEnums(type);
}