/***************************************************************************
 *   Copyright (c) 2008 Jürgen Riegel <juergen.riegel@web.de>              *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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
#include "DlgSimulationComparison.h"
#include "Base/Interpreter.h"


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
// WindLab_Comparison
//===========================================================================
DEF_STD_CMD_A(CmdWindLabComparison)

CmdWindLabComparison::CmdWindLabComparison() : Command("WindLab_Comparison")
{
    sAppModule = "WindLab";
    sGroup = QT_TR_NOOP("WindLab");
    sMenuText = QT_TR_NOOP("Compare");
    sToolTipText = QT_TR_NOOP("Compare two WindLab features in terms of accuracy, computation time and memory consumption");
    sWhatsThis = "WindLab_Comparison";
    sStatusTip = sToolTipText;
    sPixmap = "WindLab_Comparison";
}

void CmdWindLabComparison::activated(int iMsg)
{
    Q_UNUSED(iMsg);

     std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
        std::stringstream str;
        str << "Gui.runCommand('WindLab_PythonComparison')" << std::endl;
        Base::Interpreter().runString(str.str().c_str());
    }
    else if (PlugLang == "C++") {
        WindLabGui::DlgSimulationComparisonEdit* dlg = new WindLabGui::DlgSimulationComparisonEdit(nullptr);
        Gui::Control().showDialog(dlg);

       /* WindLabGui::DlgSimulationComparison* dlg = new WindLabGui::DlgSimulationComparison();
        dlg->show();*/

    }
}

bool CmdWindLabComparison::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}
void CreateWindLabCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdWindLabNewSimulation());
    rcCmdMgr.addCommand(new CmdWindLabFeatures());
    //rcCmdMgr.addCommand(new CmdWindLabFeaturesLocationDistribution());
    //rcCmdMgr.addCommand(new CmdWindLabComparison());

}
