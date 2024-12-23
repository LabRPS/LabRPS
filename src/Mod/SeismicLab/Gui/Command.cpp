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
#include "DlgSeismicLabFeaturesCreation.h"
#include "Base/Interpreter.h"
#include "SeismicLabSimulationObserver.h"
#include <App/Simulation.h>


using namespace std;

//===========================================================================
// SeismicLab_CreateSimulation
//===========================================================================
DEF_STD_CMD_A(CmdSeismicLabNewSimulation)

CmdSeismicLabNewSimulation::CmdSeismicLabNewSimulation() : Command("SeismicLab_CreateSimulation")
{
    sAppModule = "SeismicLab";
    sGroup = QT_TR_NOOP("SeismicLab");
    sMenuText = QT_TR_NOOP("New Simulation");
    sToolTipText = QT_TR_NOOP("Creation of new simulation");
    sWhatsThis = "SeismicLab_CreateSimulation";
    sStatusTip = sToolTipText;
    sPixmap = "SeismicLab_CreateSimulation";
}

void CmdSeismicLabNewSimulation::activated(int iMsg)
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
        SeismicLabGui::TaskNewSimulation* dlg = new SeismicLabGui::TaskNewSimulation();
        Gui::Control().showDialog(dlg);
    }
}

bool CmdSeismicLabNewSimulation::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// SeismicLab_CreateFeature
//===========================================================================
DEF_STD_CMD_A(CmdSeismicLabFeatures)

CmdSeismicLabFeatures::CmdSeismicLabFeatures() : Command("SeismicLab_CreateFeature")
{
    sAppModule = "SeismicLab";
    sGroup = QT_TR_NOOP("SeismicLab");
    sMenuText = QT_TR_NOOP("Create Features...");
    sToolTipText = QT_TR_NOOP("Creation of SeismicLab Features");
    sWhatsThis = "SeismicLab_CreateFeature";
    sStatusTip = sToolTipText;
    sPixmap = "SeismicLab_CreateFeature";
}

void CmdSeismicLabFeatures::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
        std::stringstream str;
        str << "Gui.runCommand('New_PythonSeismicLabFeature')" << std::endl;
        Base::Interpreter().runString(str.str().c_str());
    }
    else if (PlugLang == "C++") {
        SeismicLabGui::TaskSeismicLabFeatures* dlg = new SeismicLabGui::TaskSeismicLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdSeismicLabFeatures::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// SeismicLab_Features_LocationDistribution
//===========================================================================
DEF_STD_CMD_A(CmdSeismicLabFeaturesLocationDistribution)

CmdSeismicLabFeaturesLocationDistribution::CmdSeismicLabFeaturesLocationDistribution() : Command("SeismicLab_Features_LocationDistribution")
{
    sAppModule = "SeismicLab";
    sGroup = QT_TR_NOOP("SeismicLab");
    sMenuText = QT_TR_NOOP("Create Location Distribution...");
    sToolTipText = QT_TR_NOOP("Creation of Location Distribution Feature");
    sWhatsThis = "SeismicLab_Features_LocationDistribution";
    sStatusTip = sToolTipText;
    sPixmap = "SeismicLab_Features_LocationDistribution";
}

void CmdSeismicLabFeaturesLocationDistribution::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {

    }
    else if (PlugLang == "C++") {
        SeismicLabGui::TaskSeismicLabFeatures* dlg = new SeismicLabGui::TaskSeismicLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdSeismicLabFeaturesLocationDistribution::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// SeismicLab_Simulation_Start
//===========================================================================
DEF_STD_CMD_A(CmdSeismicLabSimulationStart)

CmdSeismicLabSimulationStart::CmdSeismicLabSimulationStart()
    : Command("SeismicLab_Simulation_Start")
{
    sAppModule = "SeismicLab";
    sGroup = QT_TR_NOOP("SeismicLab");
    sMenuText = QT_TR_NOOP("Start");
    sToolTipText = QT_TR_NOOP("Start the simulation");
    sWhatsThis = "SeismicLab_Simulation_Start";
    sStatusTip = sToolTipText;
    sPixmap = "SeismicLab_Simulation_Start";
}

void CmdSeismicLabSimulationStart::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    doCommand(Gui,"import SeismicLabGui\n"
                  "SeismicLabGui.getActiveSimulation().ViewObject.run()");
}

bool CmdSeismicLabSimulationStart::isActive(void)
{
    App::Simulation* sim = SeismicLabGui::SeismicLabSimulationObserver::instance()->active();
    return (hasActiveDocument() && sim && !sim->isRuning());
}

//===========================================================================
// SeismicLab_Simulation_Stop
//===========================================================================
DEF_STD_CMD_A(CmdSeismicLabSimulationStop)

CmdSeismicLabSimulationStop::CmdSeismicLabSimulationStop() : Command("SeismicLab_Simulation_Stop")
{
    sAppModule = "SeismicLab";
    sGroup = QT_TR_NOOP("SeismicLab");
    sMenuText = QT_TR_NOOP("Stop");
    sToolTipText = QT_TR_NOOP("Stop the simulation");
    sWhatsThis = "SeismicLab_Simulation_Stop";
    sStatusTip = sToolTipText;
    sPixmap = "SeismicLab_Simulation_Stop";
}

void CmdSeismicLabSimulationStop::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    doCommand(Gui,"import SeismicLabGui\n"
                  "SeismicLabGui.getActiveSimulation().ViewObject.stop()");
}

bool CmdSeismicLabSimulationStop::isActive(void)
{
    App::Simulation* sim = SeismicLabGui::SeismicLabSimulationObserver::instance()->active();
    return (hasActiveDocument() && sim && sim->isRuning());
}

void CreateSeismicLabCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdSeismicLabNewSimulation());
    rcCmdMgr.addCommand(new CmdSeismicLabFeatures());
    rcCmdMgr.addCommand(new CmdSeismicLabSimulationStart());
    rcCmdMgr.addCommand(new CmdSeismicLabSimulationStop());
}
