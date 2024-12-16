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
#include "DlgWindLabFeaturesCreation.h"
#include "Base/Interpreter.h"
#include "WindLabSimulationObserver.h"
#include <App/Simulation.h>


using namespace std;

//===========================================================================
// WindLab_NewSimulation
//===========================================================================
DEF_STD_CMD_A(CmdWindLabNewSimulation)

CmdWindLabNewSimulation::CmdWindLabNewSimulation() : Command("WindLab_NewSimulation")
{
    sAppModule = "WindLab";
    sGroup = QT_TR_NOOP("WindLab");
    sMenuText = QT_TR_NOOP("New Simulation");
    sToolTipText = QT_TR_NOOP("Creation of new simulation");
    sWhatsThis = "WindLab_NewSimulation";
    sStatusTip = sToolTipText;
    sPixmap = "WindLab_NewSimulation";
}

void CmdWindLabNewSimulation::activated(int iMsg)
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
        WindLabGui::TaskNewSimulation* dlg = new WindLabGui::TaskNewSimulation();
        Gui::Control().showDialog(dlg);
    }
}

bool CmdWindLabNewSimulation::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// WindLab_Features
//===========================================================================
DEF_STD_CMD_A(CmdWindLabFeatures)

CmdWindLabFeatures::CmdWindLabFeatures() : Command("WindLab_Features")
{
    sAppModule = "WindLab";
    sGroup = QT_TR_NOOP("WindLab");
    sMenuText = QT_TR_NOOP("Create Features...");
    sToolTipText = QT_TR_NOOP("Creation of WindLab Features");
    sWhatsThis = "WindLab_Features";
    sStatusTip = sToolTipText;
    sPixmap = "WindLab_Features";
}

void CmdWindLabFeatures::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
        std::stringstream str;
        str << "Gui.runCommand('New_PythonWindLabFeature')" << std::endl;
        Base::Interpreter().runString(str.str().c_str());
    }
    else if (PlugLang == "C++") {
        WindLabGui::TaskWindLabFeatures* dlg = new WindLabGui::TaskWindLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdWindLabFeatures::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// WindLab_Features_LocationDistribution
//===========================================================================
DEF_STD_CMD_A(CmdWindLabFeaturesLocationDistribution)

CmdWindLabFeaturesLocationDistribution::CmdWindLabFeaturesLocationDistribution() : Command("WindLab_Features_LocationDistribution")
{
    sAppModule = "WindLab";
    sGroup = QT_TR_NOOP("WindLab");
    sMenuText = QT_TR_NOOP("Create Location Distribution...");
    sToolTipText = QT_TR_NOOP("Creation of Location Distribution Feature");
    sWhatsThis = "WindLab_Features_LocationDistribution";
    sStatusTip = sToolTipText;
    sPixmap = "WindLab_Features_LocationDistribution";
}

void CmdWindLabFeaturesLocationDistribution::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {

    }
    else if (PlugLang == "C++") {
        WindLabGui::TaskWindLabFeatures* dlg = new WindLabGui::TaskWindLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdWindLabFeaturesLocationDistribution::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// WindLab_Simulation_Start
//===========================================================================
DEF_STD_CMD_A(CmdWindLabSimulationStart)

CmdWindLabSimulationStart::CmdWindLabSimulationStart()
    : Command("WindLab_Simulation_Start")
{
    sAppModule = "WindLab";
    sGroup = QT_TR_NOOP("WindLab");
    sMenuText = QT_TR_NOOP("Start");
    sToolTipText = QT_TR_NOOP("Start the simulation");
    sWhatsThis = "WindLab_Simulation_Start";
    sStatusTip = sToolTipText;
    sPixmap = "WindLab_Simulation_Start";
}

void CmdWindLabSimulationStart::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    doCommand(Gui,"import WindLabGui\n"
                  "WindLabGui.getActiveSimulation().ViewObject.run()");
}

bool CmdWindLabSimulationStart::isActive(void)
{
    App::Simulation* sim = WindLabGui::WindLabSimulationObserver::instance()->active();
    return (hasActiveDocument() && sim && !sim->isRuning());
}

//===========================================================================
// WindLab_Simulation_Stop
//===========================================================================
DEF_STD_CMD_A(CmdWindLabSimulationStop)

CmdWindLabSimulationStop::CmdWindLabSimulationStop() : Command("WindLab_Simulation_Stop")
{
    sAppModule = "WindLab";
    sGroup = QT_TR_NOOP("WindLab");
    sMenuText = QT_TR_NOOP("Stop");
    sToolTipText = QT_TR_NOOP("Stop the simulation");
    sWhatsThis = "WindLab_Simulation_Stop";
    sStatusTip = sToolTipText;
    sPixmap = "WindLab_Simulation_Stop";
}

void CmdWindLabSimulationStop::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    doCommand(Gui,"import WindLabGui\n"
                  "WindLabGui.getActiveSimulation().ViewObject.stop()");
}

bool CmdWindLabSimulationStop::isActive(void)
{
    App::Simulation* sim = WindLabGui::WindLabSimulationObserver::instance()->active();  
    return (hasActiveDocument() && sim && sim->isRuning());
}

void CreateWindLabCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdWindLabNewSimulation());
    rcCmdMgr.addCommand(new CmdWindLabFeatures());
    rcCmdMgr.addCommand(new CmdWindLabSimulationStart());
    rcCmdMgr.addCommand(new CmdWindLabSimulationStop());
}
