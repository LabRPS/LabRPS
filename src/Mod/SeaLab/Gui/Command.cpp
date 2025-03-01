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
# include <QApplication>
# include <QInputDialog>
# include <QMessageBox>
#endif

#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Gui/CommandT.h>
#include <Gui/Control.h>
#include <Gui/MainWindow.h>

#include "DlgNewSimulation.h"
#include "DlgSeaLabFeaturesCreation.h"
#include "Base/Interpreter.h"
#include "SeaLabSimulationObserver.h"
#include <App/Simulation.h>


using namespace std;

//===========================================================================
// SeaLab_CreateSimulation
//===========================================================================
DEF_STD_CMD_A(CmdSeaLabNewSimulation)

CmdSeaLabNewSimulation::CmdSeaLabNewSimulation() : Command("SeaLab_CreateSimulation")
{
    sAppModule = "SeaLab";
    sGroup = QT_TR_NOOP("SeaLab");
    sMenuText = QT_TR_NOOP("New Simulation");
    sToolTipText = QT_TR_NOOP("Creation of new simulation");
    sWhatsThis = "SeaLab_CreateSimulation";
    sStatusTip = sToolTipText;
    sPixmap = "SeaLab_CreateSimulation";
}

void CmdSeaLabNewSimulation::activated(int iMsg)
{
    Q_UNUSED(iMsg);

     std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
        std::stringstream str;
        str << "Gui.runCommand('New_PythonSimulation')" << std::endl;
        Base::Interpreter().runString(str.str().c_str());
    }
    else if (PlugLang == "C++") {
        SeaLabGui::TaskNewSimulation* dlg = new SeaLabGui::TaskNewSimulation();
        Gui::Control().showDialog(dlg);
    }
}

bool CmdSeaLabNewSimulation::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// SeaLab_CreateFeature
//===========================================================================
DEF_STD_CMD_A(CmdSeaLabFeatures)

CmdSeaLabFeatures::CmdSeaLabFeatures() : Command("SeaLab_CreateFeature")
{
    sAppModule = "SeaLab";
    sGroup = QT_TR_NOOP("SeaLab");
    sMenuText = QT_TR_NOOP("Create Features...");
    sToolTipText = QT_TR_NOOP("Creation of SeaLab Features");
    sWhatsThis = "SeaLab_CreateFeature";
    sStatusTip = sToolTipText;
    sPixmap = "SeaLab_CreateFeature";
}

void CmdSeaLabFeatures::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
        std::stringstream str;
        str << "Gui.runCommand('New_PythonSeaLabFeature')" << std::endl;
        Base::Interpreter().runString(str.str().c_str());
    }
    else if (PlugLang == "C++") {
        SeaLabGui::TaskSeaLabFeatures* dlg = new SeaLabGui::TaskSeaLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdSeaLabFeatures::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// SeaLab_Features_LocationDistribution
//===========================================================================
DEF_STD_CMD_A(CmdSeaLabFeaturesLocationDistribution)

CmdSeaLabFeaturesLocationDistribution::CmdSeaLabFeaturesLocationDistribution() : Command("SeaLab_Features_LocationDistribution")
{
    sAppModule = "SeaLab";
    sGroup = QT_TR_NOOP("SeaLab");
    sMenuText = QT_TR_NOOP("Create Location Distribution...");
    sToolTipText = QT_TR_NOOP("Creation of Location Distribution Feature");
    sWhatsThis = "SeaLab_Features_LocationDistribution";
    sStatusTip = sToolTipText;
    sPixmap = "SeaLab_Features_LocationDistribution";
}

void CmdSeaLabFeaturesLocationDistribution::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {

    }
    else if (PlugLang == "C++") {
        SeaLabGui::TaskSeaLabFeatures* dlg = new SeaLabGui::TaskSeaLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdSeaLabFeaturesLocationDistribution::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// SeaLab_Simulation_Start
//===========================================================================
DEF_STD_CMD_A(CmdSeaLabSimulationStart)

CmdSeaLabSimulationStart::CmdSeaLabSimulationStart()
    : Command("SeaLab_Simulation_Start")
{
    sAppModule = "SeaLab";
    sGroup = QT_TR_NOOP("SeaLab");
    sMenuText = QT_TR_NOOP("Start");
    sToolTipText = QT_TR_NOOP("Start the simulation");
    sWhatsThis = "SeaLab_Simulation_Start";
    sStatusTip = sToolTipText;
    sPixmap = "SeaLab_Simulation_Start";
}

void CmdSeaLabSimulationStart::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    doCommand(Gui,"import SeaLabGui\n"
                  "SeaLabGui.getActiveSimulation().ViewObject.run()");
}

bool CmdSeaLabSimulationStart::isActive(void)
{
    App::Simulation* sim = SeaLabGui::SeaLabSimulationObserver::instance()->active();
    return (hasActiveDocument() && sim && !sim->isRuning());
}

//===========================================================================
// SeaLab_Simulation_Stop
//===========================================================================
DEF_STD_CMD_A(CmdSeaLabSimulationStop)

CmdSeaLabSimulationStop::CmdSeaLabSimulationStop() : Command("SeaLab_Simulation_Stop")
{
    sAppModule = "SeaLab";
    sGroup = QT_TR_NOOP("SeaLab");
    sMenuText = QT_TR_NOOP("Stop");
    sToolTipText = QT_TR_NOOP("Stop the simulation");
    sWhatsThis = "SeaLab_Simulation_Stop";
    sStatusTip = sToolTipText;
    sPixmap = "SeaLab_Simulation_Stop";
}

void CmdSeaLabSimulationStop::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    doCommand(Gui,"import SeaLabGui\n"
                  "SeaLabGui.getActiveSimulation().ViewObject.stop()");
}

bool CmdSeaLabSimulationStop::isActive(void)
{
    App::Simulation* sim = SeaLabGui::SeaLabSimulationObserver::instance()->active();
    return (hasActiveDocument() && sim && sim->isRuning());
}

void CreateSeaLabCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdSeaLabNewSimulation());
    rcCmdMgr.addCommand(new CmdSeaLabFeatures());
    rcCmdMgr.addCommand(new CmdSeaLabSimulationStart());
    rcCmdMgr.addCommand(new CmdSeaLabSimulationStop());
}
