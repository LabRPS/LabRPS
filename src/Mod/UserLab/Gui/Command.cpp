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
#include "DlgUserLabFeaturesCreation.h"
#include "Base/Interpreter.h"


using namespace std;

//===========================================================================
// UserLab_NewSimulation
//===========================================================================
DEF_STD_CMD_A(CmdUserLabNewSimulation)

CmdUserLabNewSimulation::CmdUserLabNewSimulation() : Command("UserLab_NewSimulation")
{
    sAppModule = "UserLab";
    sGroup = QT_TR_NOOP("UserLab");
    sMenuText = QT_TR_NOOP("New Simulation");
    sToolTipText = QT_TR_NOOP("Creation of new simulation");
    sWhatsThis = "UserLab_NewSimulation";
    sStatusTip = sToolTipText;
    sPixmap = "UserLab_NewSimulation";
}

void CmdUserLabNewSimulation::activated(int iMsg)
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
        UserLabGui::TaskNewSimulation* dlg = new UserLabGui::TaskNewSimulation();
        Gui::Control().showDialog(dlg);
    }
}

bool CmdUserLabNewSimulation::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// UserLab_Features
//===========================================================================
DEF_STD_CMD_A(CmdUserLabFeatures)

CmdUserLabFeatures::CmdUserLabFeatures() : Command("UserLab_Features")
{
    sAppModule = "UserLab";
    sGroup = QT_TR_NOOP("UserLab");
    sMenuText = QT_TR_NOOP("Create Features...");
    sToolTipText = QT_TR_NOOP("Creation of UserLab Features");
    sWhatsThis = "UserLab_Features";
    sStatusTip = sToolTipText;
    sPixmap = "UserLab_Features";
}

void CmdUserLabFeatures::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
        std::stringstream str;
        str << "Gui.runCommand('New_PythonUserLabFeature')" << std::endl;
        Base::Interpreter().runString(str.str().c_str());
    }
    else if (PlugLang == "C++") {
        UserLabGui::TaskUserLabFeatures* dlg = new UserLabGui::TaskUserLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdUserLabFeatures::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// UserLab_Features_LocationDistribution
//===========================================================================
DEF_STD_CMD_A(CmdUserLabFeaturesLocationDistribution)

CmdUserLabFeaturesLocationDistribution::CmdUserLabFeaturesLocationDistribution() : Command("UserLab_Features_LocationDistribution")
{
    sAppModule = "UserLab";
    sGroup = QT_TR_NOOP("UserLab");
    sMenuText = QT_TR_NOOP("Create Location Distribution...");
    sToolTipText = QT_TR_NOOP("Creation of Location Distribution Feature");
    sWhatsThis = "UserLab_Features_LocationDistribution";
    sStatusTip = sToolTipText;
    sPixmap = "UserLab_Features_LocationDistribution";
}

void CmdUserLabFeaturesLocationDistribution::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {

    }
    else if (PlugLang == "C++") {
        UserLabGui::TaskUserLabFeatures* dlg = new UserLabGui::TaskUserLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdUserLabFeaturesLocationDistribution::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}


void CreateUserLabCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdUserLabNewSimulation());
    rcCmdMgr.addCommand(new CmdUserLabFeatures());
}
