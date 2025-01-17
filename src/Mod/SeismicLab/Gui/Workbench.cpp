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
#include <Mod/SeismicLabAPI/App/RPSSeismicLabAPI.h>
#include <Mod/SeismicLab/App/SeismicLabUtils.h>
#include <Mod/SeismicLab/App/SeismicLabSimulation.h>
#include <Mod/SeismicLab/Gui/SeismicLabSimulationObserver.h>
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Mod/SeismicLab/Gui/ViewProviderSeismicLabFeatureLocationDistribution.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/MainWindow.h>
#include <Mod/SeismicLabAPI/App/RPSSeismicLabpluginAPI.h>
#include <App/RPSpluginManager.h>

#define GLWAVE 4558

using namespace SeismicLabGui;
using namespace SeismicLabAPI;


#if 0 // needed for Qt's lupdate utility
    qApp->translate("CommandGroup", "SeismicLab");

#endif

/// @namespace SeismicLabGui @class Workbench
TYPESYSTEM_SOURCE(SeismicLabGui::Workbench, Gui::StdWorkbench)

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

    // read install seismicLab from registry if any
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

    Gui::MenuItem* seismicLab = new Gui::MenuItem;
    root->insertItem(item, seismicLab);
    seismicLab->setCommand("&SeismicLab");
    *seismicLab << "SeismicLab_CreateSimulation"
             << "SeismicLab_CreateFeature"
             << "SeismicLab_Simulation_Start" 
             << "SeismicLab_Simulation_Stop";
    

    return root;
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();

     Gui::ToolBarItem* SeismicLabToolBar = new Gui::ToolBarItem(root);
    SeismicLabToolBar->setCommand("SeismicLab Features");
     *SeismicLabToolBar << "SeismicLab_CreateSimulation"
                     << "SeismicLab_CreateFeature"
                     << "SeismicLab_Simulation_Start" 
                     << "SeismicLab_Simulation_Stop";

     return root;
}

Gui::ToolBarItem* Workbench::setupCommandBars() const
{
    // SeismicLab tools
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    return root;
}

//--------------------------------------------------------------------------------------------------
//plugins and features storing staff
//---------------------------------------------------------------------------------

bool SeismicLabGui::Workbench::getToBeInstalledObjectsList(std::map<const std::string, std::string>& lstObject, QString pluginName) const
{
    lstObject.clear();

    try
    {
       SeismicLab::SeismicLabUtils::getObjects(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupSimulationMethod.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupLocationDistribution.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupSpectrum.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupCoherenceFunction.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupRandomnessProvider.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupModulationFunction.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsCorrelationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupCorrelationFunction.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupTableTool.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::MatrixToolCompute.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject.toStdString());

       SeismicLab::SeismicLabUtils::getObjects(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupKurtosis.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupPeakFactor.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupSkewness.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupStandardDeviation.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupVariance.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupWavePassageEffect.toStdString());

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool SeismicLabGui::Workbench::getToBeUninstalledObjectsList(std::map<const std::string, std::string>& lstObject, QString pluginName) const
{
    lstObject.clear();
    try
    {
       SeismicLab::SeismicLabUtils::getObjects(CrpsSimuMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupSimulationMethod.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupLocationDistribution.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupSpectrum.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsCoherenceFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupCoherenceFunction.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsRandomnessFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupRandomnessProvider.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsModulationFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupModulationFunction.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsMeanFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsCorrelationFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupCorrelationFunction.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsTableToolFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupTableTool.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsMatrixToolFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::MatrixToolCompute.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject.toStdString());

       SeismicLab::SeismicLabUtils::getObjects(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsKurtosisFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupKurtosis.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsPeakFactorFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupPeakFactor.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsSkewnessFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupSkewness.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupStandardDeviation.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsVarianceFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupVariance.toStdString());
       SeismicLab::SeismicLabUtils::getObjects(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), lstObject, pluginName.toStdString(), SeismicLab::SeismicLabUtils::objGroupWavePassageEffect.toStdString());

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool SeismicLabGui::Workbench::updateToBeInstalledObjectsMap(const QString& lstObject) const
{
    try
    {
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), lstObject);

       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), lstObject);
       SeismicLab::SeismicLabUtils::updateObjectsMap(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), lstObject);

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool SeismicLabGui::Workbench::updateToBeUninstalledObjectsMap(const QString name, const QString pluginName) const
{
    try
    {
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);

       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       SeismicLab::SeismicLabUtils::updateObjectToSkipMap(CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool SeismicLabGui::Workbench::isObjectInstalled(QString& object) const
{
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsSimuMethodFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsLocationDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsSpectrumFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsCoherenceFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsPSDdecomMethodFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsFrequencyDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsRandomnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsModulationFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsMeanFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }

    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsTableToolFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsMatrixToolFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsKurtosisFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsPeakFactorFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsSkewnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsStandardDeviationFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsVarianceFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (SeismicLab::SeismicLabUtils::isThisObjectInstalled(CrpsWavePassageEffectFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }

    return false;
}

void SeismicLabGui::Workbench::emptyAllToBeUninstalledObjectsMap() const
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

bool SeismicLabGui::Workbench::isThisPluginInstalled(const QString& pluginName) const
{
    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsSimuMethodFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsSpectrumFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsCoherenceFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsRandomnessFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsModulationFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsCorrelationFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsMeanFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsTableToolFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsMatrixToolFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsKurtosisFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsPeakFactorFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsSkewnessFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsVarianceFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (SeismicLab::SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    return false;
}

QString SeismicLabGui::Workbench::getPhenomenonName() const
{
    return SeismicLab::SeismicLabUtils::rpsPhenomenonWindVelocity;
}

void SeismicLabGui::Workbench::WLReadAllTobeInstallObjectsFromRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethod"), count = 1;
    ReadMapFromRegistry2(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLoc"), count = 1;
    ReadMapFromRegistry2(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSD"), count = 1;
    ReadMapFromRegistry2(CrpsSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCoh"), count = 1;
    ReadMapFromRegistry2(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecomp"), count = 1;
    ReadMapFromRegistry2(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("SLFreq"), count = 1;
    ReadMapFromRegistry2(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRand"), count = 1;
    ReadMapFromRegistry2(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMod"), count = 1;
    ReadMapFromRegistry2(CrpsModulationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorr"), count = 1;
    ReadMapFromRegistry2(CrpsCorrelationFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("SLMean"), count = 1;
    ReadMapFromRegistry2(CrpsMeanFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableTool"), count = 1;
    ReadMapFromRegistry2(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixTool"), count = 1;
    ReadMapFromRegistry2(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObj"), count = 1;
    ReadMapFromRegistry2(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistribution"), count = 1;
    ReadMapFromRegistry2(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLKurtosis"), count = 1;
    ReadMapFromRegistry2(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactor"), count = 1;
    ReadMapFromRegistry2(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunction"), count = 1;
    ReadMapFromRegistry2(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlow"), count = 1;
    ReadMapFromRegistry2(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewness"), count = 1;
    ReadMapFromRegistry2(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviation"), count = 1;
    ReadMapFromRegistry2(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("SLVariance"), count = 1;
    ReadMapFromRegistry2(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffect"), count = 1;
    ReadMapFromRegistry2(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);
}

void SeismicLabGui::Workbench::WLWriteAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethodTitle"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocTitle"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDTitle"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohTitle"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompTitle"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqTitle"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandTitle"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModTitle"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrTitle"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanTitle"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolTitle"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolTitle"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjTitle"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionTitle"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetTitleMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("SLKurtosisTitle"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorTitle"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionTitle"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowTitle"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessTitle"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationTitle"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceTitle"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectTitle"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetTitleMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WLReadAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethodTitle"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocTitle"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDTitle"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohTitle"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompTitle"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqTitle"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandTitle"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModTitle"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrTitle"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanTitle"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolTitle"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolTitle"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjTitle"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionTitle"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetTitleMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("SLKurtosisTitle"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorTitle"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionTitle"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowTitle"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessTitle"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationTitle"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceTitle"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectTitle"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetTitleMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WLWriteAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethodLink"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocLink"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDLink"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohLink"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompLink"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqLink"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandLink"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModLink"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrLink"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanLink"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolLink"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolLink"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjLink"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionLink"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetLinkMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("SLKurtosisLink"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorLink"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionLink"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowLink"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessLink"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationLink"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceLink"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectLink"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetLinkMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WLReadAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethodLink"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocLink"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDLink"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohLink"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompLink"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqLink"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandLink"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModLink"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrLink"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanLink"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolLink"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolLink"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjLink"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionLink"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLKurtosisLink"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorLink"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionLink"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowLink"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessLink"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationLink"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceLink"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectLink"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetLinkMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WLWriteAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethodAuthor"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocAuthor"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDAuthor"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohAuthor"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompAuthor"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqAuthor"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandAuthor"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModAuthor"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrAuthor"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanAuthor"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolAuthor"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolAuthor"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjAuthor"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionAuthor"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLKurtosisAuthor"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorAuthor"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionAuthor"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowAuthor"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessAuthor"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationAuthor"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceAuthor"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectAuthor"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetAuthorMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WLReadAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethodAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocAuthor"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompAuthor"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqAuthor"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandAuthor"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModAuthor"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanAuthor"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolAuthor"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolAuthor"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjAuthor"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap(), settingsGroup,  count);

    settingsGroup = QString::fromLatin1("SLKurtosisAuthor"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorAuthor"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionAuthor"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetAuthorMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowAuthor"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationAuthor"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceAuthor"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectAuthor"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetAuthorMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WLWriteAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethodDate"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocDate"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDDate"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohDate"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompDate"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqDate"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandDate"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModDate"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrDate"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanDate"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolDate"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolDate"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjDate"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionDate"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLKurtosisDate"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorDate"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionDate"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowDate"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessDate"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationDate"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceDate"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectDate"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetDateMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WLReadAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethodDate"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocDate"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDDate"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohDate"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompDate"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqDate"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandDate"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModDate"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrDate"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanDate"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolDate"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolDate"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjDate"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionDate"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLKurtosisDate"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorDate"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionDate"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowDate"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessDate"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationDate"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceDate"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectDate"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetDateMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WriteMapToRegistry(std::map<const std::string, std::string>& map,
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

void SeismicLabGui::Workbench::ReadMapFromRegistry(std::map<const const std::string, std::string>& map,
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

void SeismicLabGui::Workbench::WriteMapToRegistry2(std::map<const const std::string, std::string>& map,
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

void SeismicLabGui::Workbench::ReadMapFromRegistry2(
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

void SeismicLabGui::Workbench::WLWriteAllTobeInstallObjectsToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethod"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLoc"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSD"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCoh"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecomp"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreq"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("SLRand"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMod"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorr"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMean"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableTool"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixTool"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObj"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistribution"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLKurtosis"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactor"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunction"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlow"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewness"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviation"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVariance"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffect"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), settingsGroup, count);
}


void SeismicLabGui::Workbench::WLWriteAllTobeInstallObjVersionToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethodVersion"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocVersion"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDVersion"), count = 1;
    WriteMapToRegistry(CrpsSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohVersion"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompVersion"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqVersion"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandVersion"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModVersion"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrVersion"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanVersion"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolVersion"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolVersion"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjVersion"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionVersion"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLKurtosisVersion"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorVersion"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionVersion"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowVersion"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessVersion"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationVersion"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceVersion"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectVersion"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetVersionMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WLReadAllTobeInstallObjVersionToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethod"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLLocVersion"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLXPSDVersion"), count = 1;
    ReadMapFromRegistry(CrpsSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCohVersion"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLDecompVersion"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLFreqVersion"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLRandVersion"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLModVersion"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCorrVersion"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMeanVersion"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLTableToolVersion"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLMatrixToolVersion"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjVersion"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionVersion"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLKurtosisVersion"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLPeakFactorVersion"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionVersion"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowVersion"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLSkewnessVersion"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLStandardDeviationVersion"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLVarianceVersion"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectVersion"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetVersionMap(), settingsGroup, count);
}

void SeismicLabGui::Workbench::WLClearAllTobeInstallObjectsFromRegistry()
{
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("SLSimMethod");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLLoc");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLXPSD");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCoh");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLDecomp");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLFreq");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLRand");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMod");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCorr");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMean");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLTableTool");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMatrixTool");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObj");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = QString::fromLatin1("SLSimMethodTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLLocTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLXPSDTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCohTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLDecompTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLFreqTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLRandTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLModTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCorrTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMeanTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLTableToolTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMatrixToolTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjTitle");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("SLSimMethodLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLLocLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLXPSDLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCohLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLDecompLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLFreqLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLRandLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLModLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCorrLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMeanLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLTableToolLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMatrixToolLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjLink");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("SLSimMethodAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLLocAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLXPSDAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCohAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLDecompAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLFreqAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLRandAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLModAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCorrAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMeanAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLTableToolAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMatrixToolAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjAuthor");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("SLSimMethodDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLLocDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLXPSDDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCohDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLDecompDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLFreqDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLRandDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLModDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCorrDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMeanDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLTableToolDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMatrixToolDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjDate");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("SLSimMethodVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLLocVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLXPSDVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCohVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLDecompVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLFreqVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLRandVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLModVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCorrVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMeanVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLTableToolVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLMatrixToolVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLUserDefinedRPSObjVersion");
    ClearMapFromRegistry(settingsGroup);

    //////////////////////////////////////////////////////

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistribution");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLKurtosis");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLPeakFactor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunction");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlow");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLSkewness");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLStandardDeviation");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLVariance");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLWavePassageEffect");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLKurtosisTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLPeakFactorTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLSkewnessTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLStandardDeviationTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLVarianceTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLKurtosisLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLPeakFactorLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLSkewnessLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLStandardDeviationLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLVarianceLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLKurtosisAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLPeakFactorAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLSkewnessAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLStandardDeviationAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLVarianceAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLKurtosisDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLPeakFactorDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLSkewnessDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLStandardDeviationDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLVarianceDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLCumulativeProbabilityDistributionVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLKurtosisVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLPeakFactorVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLProbabilityDensityFunctionVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLShearVelocityOfFlowVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLSkewnessVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLStandardDeviationVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLVarianceVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("SLWavePassageEffectVersion");
    ClearMapFromRegistry(settingsGroup);
}



void SeismicLabGui::Workbench::ClearMapFromRegistry(QString& settingsGroup)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.remove(QString::fromLatin1(""));// removes the group, and all it keys
    settings.endGroup();
}



int SeismicLabGui::Workbench::RPSWriteInstalledPluginsToRegistry()
{
    int i = 1;
    QString PlgName;
    QString Descript;

    // number of plugins to be installed
    int NberOfInstalledPlugins = App::PluginManager::GetInstance().GetInstalledPluginsMap().size();

    QSettings settings;
    settings.beginGroup(QLatin1String("SeismicLabToBeInstalledPlugins"));
    settings.setValue(QLatin1String("SeismicLabToBeInstalledPluginsNumber"), NberOfInstalledPlugins);

    std::map<QString, App::PluginInstance*>::iterator it;
    for (it = App::PluginManager::GetInstance().GetInstalledPluginsMap().begin();
         it != App::PluginManager::GetInstance().GetInstalledPluginsMap().end(); ++it) {
        // Get the plugin names
        Descript = it->second->GetPluginSubFolder();// second veut dire "b", first sera "a" map<a,b>
        if (Descript.contains(QString::fromLatin1("SeismicLab")))
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

bool SeismicLabGui::Workbench::IntallRegistryPlugins()
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

int SeismicLabGui::Workbench::RPSReadInstalledPluginsFromRegistry()
{
    RPSReadInstalledPluginsFromRegistryCommon();

    return 1;
}

int SeismicLabGui::Workbench::RPSReadInstalledPluginsFromRegistryCommon()
{
    int i = 1;
    QString PlgName;
    QString Descript;

    QSettings settings;

    settings.beginGroup(QLatin1String("SeismicLabToBeInstalledPlugins"));
    int NberOfInstalledPlugins = settings.value(QLatin1String("SeismicLabToBeInstalledPluginsNumber")).toInt();

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


std::list<std::string> SeismicLabGui::Workbench::getAllPlugins() const
{ 
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("SeismicLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("SeismicLabWorkbench"));

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
std::list<std::string> SeismicLabGui::Workbench::getAllInstalledPlugins() const
{
    std::list<std::string> list;
    std::list<std::string> items = getAllPlugins();
    for (std::list<std::string>::const_iterator item = items.begin(); item != items.end(); ++item)
         if (isThisPluginInstalled(QString::fromLatin1((*item).c_str())))
         list.push_back(*item);
    return list;
}

bool SeismicLabGui::Workbench::installPlugin(const std::string pluginName)
{
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("SeismicLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("SeismicLabWorkbench"));

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

bool SeismicLabGui::Workbench::unInstallPlugin(const std::string pluginName)
{ 
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("SeismicLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("SeismicLabWorkbench"));

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

void SeismicLabGui::Workbench::createSimulation(const std::string simulationName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
    {
        Base::Console().Error("No valid active document found.\n");
        return;
    }
    std::string uniqueName = doc->getUniqueObjectName(simulationName.c_str());
	 SeismicLab::SeismicLabSimulation* newSim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->createSimulation(uniqueName, "SeismicLab::SeismicLabSimulation"));
	SeismicLabGui::SeismicLabSimulationObserver::instance()->setActiveSimulation(newSim);
	App::GetApplication().getActiveDocument()->recompute();
}

void SeismicLabGui::Workbench::createFeature(const std::string simulationName, const std::string featureTypeName, const std::string featureName, const std::string featureGroup, const int featureType)
{
    //get the simulation for which this feature will created
	SeismicLab::SeismicLabSimulation* simParent = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->getSimulation(simulationName));
	if (!simParent)
		return;
	//get all SeismicLab feature type
	std::vector<Base::Type> types = simParent->getRPSTypesOfPluggableFeatures();

	//get the type of the creating feature
    Base::Type type = types[featureType];

	//create the feature
	SeismicLabAPI::SeismicLabFeature* newFeature = simParent->createFeature(type, featureGroup, featureName);

	if (!newFeature)
		return;

	//set the feature properties
    auto featureProperties = simParent->GetSeismicLabPluggedSeismicLabFeatureDescription(QString::fromLatin1(featureTypeName.c_str()), QString::fromLatin1(featureGroup.c_str()));
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
    newFeature->Description.setValue(featureProperties->Description.getValue());
    newFeature->LabrpsVersion.setValue(featureProperties->LabRPSVersion.getValue());
    newFeature->Path.setValue(featureProperties->Path.getValue());

	App::DocumentObjectGroup* group = static_cast<App::DocumentObjectGroup*>(static_cast<App::DocumentObject*>(simParent));

    newFeature->recomputeFeature();
	group->addObject(newFeature);

    //show change in the property editor
    simParent->setEnums(type);
}