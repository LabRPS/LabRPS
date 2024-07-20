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
#include <Mod/SeaLabAPI/App/RPSSeaLabAPI.h>
#include <Mod/SeaLab/App/SeaLabUtils.h>
#include <Mod/SeaLab/App/SeaLabSimulation.h>
#include <Mod/SeaLab/Gui/SeaLabSimulationObserver.h>
#include <Mod/SeaLabAPI/App/RPSSeaLabFramework.h>
#include <Mod/SeaLab/Gui/ViewProviderSeaLabFeatureLocationDistribution.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/MainWindow.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <Mod/SeaLabAPI/App/RPSSeaLabpluginAPI.h>
#include <App/RPSpluginManager.h>

#define GLWAVE 4558

using namespace SeaLabGui;
using namespace SeaLabAPI;


#if 0 // needed for Qt's lupdate utility
    qApp->translate("CommandGroup", "SeaLab");

#endif

/// @namespace SeaLabGui @class Workbench
TYPESYSTEM_SOURCE(SeaLabGui::Workbench, Gui::StdWorkbench)

Workbench::Workbench()
{
    ParameterGrp::handle hGrp;

    hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Plugins");
    hGrp->SetASCII("Installed Plugins", "Plugin 1");

    WLReadAllTobeInstallObjVersionToRegistry();
    WLReadAllTobeInstallObjPublicationTitleToRegistry();
    WLReadAllTobeInstallObjPublicationLinkToRegistry();
    WLReadAllTobeInstallObjPublicationAuthorToRegistry();
    WLReadAllTobeInstallObjPublicationDateToRegistry();

    // read install seaLab from registry if any
    WLReadAllTobeInstallObjectsFromRegistry();
    WLClearAllTobeInstallObjectsFromRegistry();

    IntallRegistryPlugins();
}

Workbench::~Workbench()
{
    RPSWriteInstalledPluginsToRegistry();

    WLWriteAllTobeInstallObjPublicationTitleToRegistry();
    WLWriteAllTobeInstallObjPublicationLinkToRegistry();
    WLWriteAllTobeInstallObjPublicationAuthorToRegistry();
    WLWriteAllTobeInstallObjPublicationDateToRegistry();
    WLWriteAllTobeInstallObjVersionToRegistry();

    WLWriteAllTobeInstallObjectsToRegistry();

}

Gui::MenuItem* Workbench::setupMenuBar() const
{
    Gui::MenuItem* root = StdWorkbench::setupMenuBar();
    Gui::MenuItem* item = root->findItem("&Windows");

    Gui::MenuItem* seaLab = new Gui::MenuItem;
    root->insertItem(item, seaLab);
    seaLab->setCommand("&SeaLab");
    *seaLab << "SeaLab_NewSimulation"
             << "SeaLab_Features"
            //  << "SeaLab_Comparison"
             << "SeaLab_Examples";
    

    return root;
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();

     Gui::ToolBarItem* SeaLabToolBar = new Gui::ToolBarItem(root);
    SeaLabToolBar->setCommand("SeaLab Features");
     *SeaLabToolBar << "SeaLab_NewSimulation"
                     << "SeaLab_Features"
                    //  << "SeaLab_Comparison"
                     << "SeaLab_Examples";

     return root;
}

Gui::ToolBarItem* Workbench::setupCommandBars() const
{
    // SeaLab tools
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    return root;
}

//--------------------------------------------------------------------------------------------------
//plugins and features storing staff
//---------------------------------------------------------------------------------

bool SeaLabGui::Workbench::getToBeInstalledObjectsList(std::map<const std::string, std::string>& lstObject, QString pluginName) const
{
    lstObject.clear();

    try
    {
       SeaLab::SeaLabUtils::getObjects(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupSimulationMethod.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupLocationDistribution.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupSpectrum.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupCoherenceFunction.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupFrequencyDistribution.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupRandomnessProvider.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupModulationFunction.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsCorrelationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupCorrelationFunction.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupTableTool.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::MatrixToolCompute.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject.toStdString());

       SeaLab::SeaLabUtils::getObjects(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupKurtosis.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupPeakFactor.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupSkewness.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupStandardDeviation.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupVariance.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupWavePassageEffect.toStdString());

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool SeaLabGui::Workbench::getToBeUninstalledObjectsList(std::map<const std::string, std::string>& lstObject, QString pluginName) const
{
    lstObject.clear();
    try
    {
       SeaLab::SeaLabUtils::getObjects(CrpsSimuMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupSimulationMethod.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupLocationDistribution.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupSpectrum.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsCoherenceFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupCoherenceFunction.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupFrequencyDistribution.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsRandomnessFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupRandomnessProvider.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsModulationFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupModulationFunction.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsMeanFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsCorrelationFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupCorrelationFunction.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsTableToolFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupTableTool.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsMatrixToolFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::MatrixToolCompute.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject.toStdString());

       SeaLab::SeaLabUtils::getObjects(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsKurtosisFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupKurtosis.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsPeakFactorFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupPeakFactor.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsSkewnessFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupSkewness.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupStandardDeviation.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsVarianceFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupVariance.toStdString());
       SeaLab::SeaLabUtils::getObjects(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeaLab::SeaLabUtils::objGroupWavePassageEffect.toStdString());

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool SeaLabGui::Workbench::updateToBeInstalledObjectsMap(const QString& lstObject) const
{
    try
    {
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), lstObject);

       SeaLab::SeaLabUtils::updateObjectsMap(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeaLab::SeaLabUtils::updateObjectsMap(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), lstObject);

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool SeaLabGui::Workbench::updateToBeUninstalledObjectsMap(const QString name, const QString pluginName) const
{
    try
    {
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);

       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeaLab::SeaLabUtils::updateObjectToSkipMap(CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool SeaLabGui::Workbench::isObjectInstalled(QString& object) const
{
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsSimuMethodFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsLocationDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsSpectrumFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsCoherenceFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsPSDdecomMethodFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsFrequencyDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsRandomnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsModulationFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsMeanFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }

    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsTableToolFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsMatrixToolFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsKurtosisFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsPeakFactorFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsSkewnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsStandardDeviationFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsVarianceFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeaLab::SeaLabUtils::isThisObjectInstalled(CrpsWavePassageEffectFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }

    return false;
}

void SeaLabGui::Workbench::emptyAllToBeUninstalledObjectsMap() const
{
    try
    {
        CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsSpectrumFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap().clear();

        CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap().clear();



    }
    catch (const std::exception& e)
    {

    }
}

bool SeaLabGui::Workbench::isThisPluginInstalled(const QString& pluginName) const
{
    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsSimuMethodFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsSpectrumFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsCoherenceFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsRandomnessFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsModulationFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsCorrelationFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsMeanFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsTableToolFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsMatrixToolFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsKurtosisFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsPeakFactorFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsSkewnessFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsVarianceFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeaLab::SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    return false;
}

QString SeaLabGui::Workbench::getPhenomenonName() const
{
    return SeaLab::SeaLabUtils::rpsPhenomenonWindVelocity;
}

void SeaLabGui::Workbench::WLReadAllTobeInstallObjectsFromRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethod"), count = 1;
    ReadMapFromRegistry2(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLoc"), count = 1;
    ReadMapFromRegistry2(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSD"), count = 1;
    ReadMapFromRegistry2(CrpsSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCoh"), count = 1;
    ReadMapFromRegistry2(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecomp"), count = 1;
    ReadMapFromRegistry2(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("SeLFreq"), count = 1;
    ReadMapFromRegistry2(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRand"), count = 1;
    ReadMapFromRegistry2(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMod"), count = 1;
    ReadMapFromRegistry2(CrpsModulationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorr"), count = 1;
    ReadMapFromRegistry2(CrpsCorrelationFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("SeLMean"), count = 1;
    ReadMapFromRegistry2(CrpsMeanFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableTool"), count = 1;
    ReadMapFromRegistry2(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixTool"), count = 1;
    ReadMapFromRegistry2(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObj"), count = 1;
    ReadMapFromRegistry2(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistribution"), count = 1;
    ReadMapFromRegistry2(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLKurtosis"), count = 1;
    ReadMapFromRegistry2(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactor"), count = 1;
    ReadMapFromRegistry2(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunction"), count = 1;
    ReadMapFromRegistry2(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlow"), count = 1;
    ReadMapFromRegistry2(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewness"), count = 1;
    ReadMapFromRegistry2(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviation"), count = 1;
    ReadMapFromRegistry2(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("SeLVariance"), count = 1;
    ReadMapFromRegistry2(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffect"), count = 1;
    ReadMapFromRegistry2(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);
}

void SeaLabGui::Workbench::WLWriteAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethodTitle"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocTitle"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDTitle"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohTitle"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompTitle"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqTitle"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandTitle"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModTitle"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrTitle"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanTitle"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolTitle"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolTitle"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjTitle"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionTitle"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetTitleMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("SeLKurtosisTitle"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorTitle"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionTitle"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowTitle"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessTitle"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationTitle"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceTitle"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectTitle"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetTitleMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WLReadAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethodTitle"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocTitle"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDTitle"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohTitle"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompTitle"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqTitle"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandTitle"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModTitle"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrTitle"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanTitle"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolTitle"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolTitle"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjTitle"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionTitle"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetTitleMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("SeLKurtosisTitle"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorTitle"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionTitle"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowTitle"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessTitle"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationTitle"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceTitle"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectTitle"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetTitleMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WLWriteAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethodLink"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocLink"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDLink"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohLink"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompLink"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqLink"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandLink"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModLink"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrLink"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanLink"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolLink"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolLink"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjLink"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionLink"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetLinkMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("SeLKurtosisLink"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorLink"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionLink"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowLink"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessLink"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationLink"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceLink"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectLink"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetLinkMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WLReadAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethodLink"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocLink"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDLink"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohLink"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompLink"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqLink"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandLink"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModLink"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrLink"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanLink"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolLink"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolLink"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjLink"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionLink"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLKurtosisLink"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorLink"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionLink"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowLink"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessLink"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationLink"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceLink"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectLink"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetLinkMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WLWriteAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethodAuthor"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocAuthor"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDAuthor"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohAuthor"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompAuthor"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqAuthor"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandAuthor"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModAuthor"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrAuthor"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanAuthor"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolAuthor"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolAuthor"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjAuthor"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionAuthor"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLKurtosisAuthor"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorAuthor"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionAuthor"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowAuthor"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessAuthor"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationAuthor"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceAuthor"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectAuthor"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetAuthorMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WLReadAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethodAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocAuthor"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompAuthor"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqAuthor"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandAuthor"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModAuthor"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanAuthor"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolAuthor"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolAuthor"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjAuthor"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap(), settingsGroup,  count);

    settingsGroup = QString::fromLatin1("SeLKurtosisAuthor"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorAuthor"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionAuthor"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetAuthorMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowAuthor"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationAuthor"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceAuthor"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectAuthor"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetAuthorMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WLWriteAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethodDate"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocDate"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDDate"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohDate"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompDate"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqDate"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandDate"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModDate"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrDate"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanDate"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolDate"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolDate"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjDate"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionDate"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLKurtosisDate"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorDate"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionDate"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowDate"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessDate"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationDate"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceDate"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectDate"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetDateMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WLReadAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethodDate"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocDate"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDDate"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohDate"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompDate"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqDate"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandDate"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModDate"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrDate"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanDate"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolDate"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolDate"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjDate"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionDate"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLKurtosisDate"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorDate"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionDate"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowDate"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessDate"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationDate"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceDate"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectDate"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetDateMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WriteMapToRegistry(std::map<const std::string, std::string>& map,
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

void SeaLabGui::Workbench::ReadMapFromRegistry(std::map<const const std::string, std::string>& map,
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

void SeaLabGui::Workbench::WriteMapToRegistry2(std::map<const const std::string, std::string>& map,
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

void SeaLabGui::Workbench::ReadMapFromRegistry2(
    std::map<const const std::string, std::string>& map,
                                                QString& settingsGroup, int& count)
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

void SeaLabGui::Workbench::WLWriteAllTobeInstallObjectsToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethod"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLoc"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSD"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCoh"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecomp"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreq"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("SeLRand"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMod"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorr"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMean"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableTool"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixTool"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObj"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistribution"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLKurtosis"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactor"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunction"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlow"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewness"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviation"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVariance"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffect"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), settingsGroup, count);
}


void SeaLabGui::Workbench::WLWriteAllTobeInstallObjVersionToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethodVersion"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocVersion"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDVersion"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohVersion"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompVersion"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqVersion"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandVersion"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModVersion"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrVersion"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanVersion"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolVersion"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolVersion"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjVersion"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionVersion"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLKurtosisVersion"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorVersion"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionVersion"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowVersion"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessVersion"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationVersion"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceVersion"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectVersion"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetVersionMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WLReadAllTobeInstallObjVersionToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethod"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLLocVersion"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLXPSDVersion"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCohVersion"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLDecompVersion"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLFreqVersion"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLRandVersion"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLModVersion"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCorrVersion"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMeanVersion"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLTableToolVersion"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLMatrixToolVersion"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjVersion"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionVersion"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLKurtosisVersion"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLPeakFactorVersion"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionVersion"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowVersion"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLSkewnessVersion"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationVersion"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLVarianceVersion"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectVersion"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetVersionMap(), settingsGroup, count);
}

void SeaLabGui::Workbench::WLClearAllTobeInstallObjectsFromRegistry()
{
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SeLSimMethod");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLLoc");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLXPSD");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCoh");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLDecomp");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLFreq");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLRand");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMod");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCorr");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMean");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLTableTool");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMatrixTool");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObj");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = QString::fromLatin1("SeLSimMethodTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLLocTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLXPSDTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCohTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLDecompTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLFreqTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLRandTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLModTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCorrTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMeanTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLTableToolTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMatrixToolTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjTitle");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("SeLSimMethodLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLLocLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLXPSDLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCohLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLDecompLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLFreqLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLRandLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLModLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCorrLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMeanLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLTableToolLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMatrixToolLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjLink");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("SeLSimMethodAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLLocAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLXPSDAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCohAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLDecompAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLFreqAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLRandAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLModAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCorrAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMeanAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLTableToolAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMatrixToolAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjAuthor");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("SeLSimMethodDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLLocDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLXPSDDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCohDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLDecompDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLFreqDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLRandDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLModDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCorrDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMeanDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLTableToolDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMatrixToolDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjDate");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("SeLSimMethodVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLLocVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLXPSDVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCohVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLDecompVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLFreqVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLRandVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLModVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCorrVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMeanVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLTableToolVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLMatrixToolVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLUserDefinedRPSObjVersion");
    ClearMapFromRegistry(settingsGroup);

    //////////////////////////////////////////////////////

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistribution");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLKurtosis");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLPeakFactor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunction");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlow");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLSkewness");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLStandardDeviation");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLVariance");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffect");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLKurtosisTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLPeakFactorTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLSkewnessTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLVarianceTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLKurtosisLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLPeakFactorLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLSkewnessLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLVarianceLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLKurtosisAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLPeakFactorAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLSkewnessAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLVarianceAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLKurtosisDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLPeakFactorDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLSkewnessDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLVarianceDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLCumulativeProbabilityDistributionVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLKurtosisVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLPeakFactorVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLProbabilityDensityFunctionVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLShearVelocityOfFlowVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLSkewnessVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLStandardDeviationVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLVarianceVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SeLWavePassageEffectVersion");
    ClearMapFromRegistry(settingsGroup);
}



void SeaLabGui::Workbench::ClearMapFromRegistry(QString& settingsGroup)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.remove(QString::fromLatin1(""));// removes the group, and all it keys
    settings.endGroup();
}



int SeaLabGui::Workbench::RPSWriteInstalledPluginsToRegistry()
{
    int i = 1;
    QString PlgName;
    QString Descript;

    // number of plugins to be installed
    int NberOfInstalledPlugins = App::PluginManager::GetInstance().GetInstalledPluginsMap().size();

    QSettings settings;
    settings.beginGroup(QLatin1String("SeaLabToBeInstalledPlugins"));
    settings.setValue(QLatin1String("SeaLabToBeInstalledPluginsNumber"), NberOfInstalledPlugins);

    std::map<QString, App::PluginInstance*>::iterator it;
    for (it = App::PluginManager::GetInstance().GetInstalledPluginsMap().begin();
         it != App::PluginManager::GetInstance().GetInstalledPluginsMap().end(); ++it) {
        // Get the plugin names
        Descript = it->second->GetPluginSubFolder();// second veut dire "b", first sera "a" map<a,b>
        if (Descript.contains(QString::fromLatin1("SeaLab")))
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

bool SeaLabGui::Workbench::IntallRegistryPlugins()
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

int SeaLabGui::Workbench::RPSReadInstalledPluginsFromRegistry()
{
    RPSReadInstalledPluginsFromRegistryCommon();

    return 1;
}

int SeaLabGui::Workbench::RPSReadInstalledPluginsFromRegistryCommon()
{
    int i = 1;
    QString PlgName;
    QString Descript;

    QSettings settings;

    settings.beginGroup(QLatin1String("SeaLabToBeInstalledPlugins"));
    int NberOfInstalledPlugins = settings.value(QLatin1String("SeaLabToBeInstalledPluginsNumber")).toInt();

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


std::list<std::string> SeaLabGui::Workbench::getAllPlugins() const
{ 
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("SeaLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("SeaLabWorkbench"));

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
std::list<std::string> SeaLabGui::Workbench::getAllInstalledPlugins() const
{
    std::list<std::string> list;
    std::list<std::string> items = getAllPlugins();
    for (std::list<std::string>::const_iterator item = items.begin(); item != items.end(); ++item)
         if (isThisPluginInstalled(QString::fromLatin1((*item).c_str())))
         list.push_back(*item);
    return list;
}

bool SeaLabGui::Workbench::installPlugin(const std::string pluginName)
{
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("SeaLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("SeaLabWorkbench"));

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

bool SeaLabGui::Workbench::unInstallPlugin(const std::string pluginName)
{ 
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("SeaLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("SeaLabWorkbench"));

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

void SeaLabGui::Workbench::createSimulation(const std::string simulationName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
    {
        Base::Console().Warning("No valid active document found.\n");
        return;
    }
    std::string uniqueName = doc->getUniqueObjectName(simulationName.c_str());
	 SeaLab::SeaLabSimulation* newSim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->createSimulation(uniqueName, "SeaLab::SeaLabSimulation"));
	SeaLabGui::SeaLabSimulationObserver::instance()->setActiveSimulation(newSim);
	App::GetApplication().getActiveDocument()->recompute();
}

void SeaLabGui::Workbench::createFeature(const std::string simulationName, const std::string featureTypeName, const std::string featureName, const std::string featureGroup, const int featureType)
{
    //get the simulation for which this feature will created
	SeaLab::SeaLabSimulation* simParent = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->getSimulation(simulationName));
	if (!simParent)
		return;
	//get all SeaLab feature type
	std::vector<Base::Type> types = simParent->getRPSTypesOfPluggableFeatures();

	//get the type of the creating feature
    Base::Type type = types[featureType];

	//create the feature
	SeaLabAPI::SeaLabFeature* newFeature = simParent->createFeature(type, featureGroup, featureName);

	if (!newFeature)
		return;

	//set the feature properties
    auto featureProperties = simParent->GetSeaLabPluggedSeaLabFeatureDescription(QString::fromLatin1(featureTypeName.c_str()), QString::fromLatin1(featureGroup.c_str()));
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