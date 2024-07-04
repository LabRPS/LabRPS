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


#ifndef WINDLAB_WORKBENCH_H
#define WINDLAB_WORKBENCH_H

#include <Gui/Workbench.h>
#include <Gui/MenuManager.h>
#include <Gui/ToolBarManager.h>
#include <Mod/WindLab/WindLabGlobal.h>

namespace WindLabGui {

/**
 * @author Werner Mayer
 */
class WindLabGuiExport Workbench : public Gui::StdWorkbench
{
    TYPESYSTEM_HEADER();

public:
    Workbench();
    virtual ~Workbench();

    virtual bool getToBeInstalledObjectsList(std::map<const std::string, std::string>& lstObject, QString pluginName) const;
    virtual bool getToBeUninstalledObjectsList(std::map<const std::string, std::string>& lstObject, QString pluginName) const;
    virtual bool isObjectInstalled(QString& object) const;
    virtual bool updateToBeInstalledObjectsMap(const QString& lstObject) const;
    virtual bool updateToBeUninstalledObjectsMap(const QString name, const QString pluginName) const;
    virtual void emptyAllToBeUninstalledObjectsMap() const;
    virtual bool isThisPluginInstalled(const QString& pluginName) const;
    virtual QString getPhenomenonName() const;
    
    virtual std::list<std::string> getAllPlugins() const;
    virtual std::list<std::string> getAllInstalledPlugins() const;
    virtual bool installPlugin(const std::string pluginName);
    virtual bool unInstallPlugin(const std::string pluginName);
    virtual void createSimulation(const std::string simulationName);
    virtual void createFeature(const std::string simulationName, const std::string featureTypeName, const std::string featureName, const std::string featureGroup, const int featureType = 0);


private:
    
    void WriteMapToRegistry(std::map<const const std::string, std::string>& map,
                            QString& settingsGroup, int& count);
    void ReadMapFromRegistry(std::map<const const std::string, std::string>& map,
                             QString& settingsGroup, int& count);
    void WriteMapToRegistry2(std::map<const const std::string, std::string>& map,
                             QString& settingsGroup, int& count);
    void ReadMapFromRegistry2(std::map<const const std::string, std::string>& map,
                              QString& settingsGroup, int& count);

    void WLWriteAllTobeInstallObjectsToRegistry();
    void WLReadAllTobeInstallObjectsFromRegistry();

    void WLWriteAllTobeInstallObjPublicationTitleToRegistry();
    void WLReadAllTobeInstallObjPublicationTitleToRegistry();

    void WLWriteAllTobeInstallObjPublicationLinkToRegistry();
    void WLReadAllTobeInstallObjPublicationLinkToRegistry();

    void WLWriteAllTobeInstallObjPublicationAuthorToRegistry();
    void WLReadAllTobeInstallObjPublicationAuthorToRegistry();

    void WLWriteAllTobeInstallObjPublicationDateToRegistry();
    void WLReadAllTobeInstallObjPublicationDateToRegistry();

    void WLWriteAllTobeInstallObjVersionToRegistry();
    void WLReadAllTobeInstallObjVersionToRegistry();
    void WLClearAllTobeInstallObjectsFromRegistry();
    void ClearMapFromRegistry(QString& settingsGroupt);

    int RPSWriteInstalledPluginsToRegistry();
    int RPSReadInstalledPluginsFromRegistry();
    int RPSReadInstalledPluginsFromRegistryCommon();
    bool IntallRegistryPlugins();


protected:
    Gui::MenuItem* setupMenuBar() const;
    Gui::ToolBarItem* setupToolBars() const;
    Gui::ToolBarItem* setupCommandBars() const;
};

} // namespace WindLabGui

#endif // WINDLAB_WORKBENCH_H
