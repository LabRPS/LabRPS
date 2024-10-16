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
#include "DlgUserDefinedPhenomenonLabFeaturesCreation.h"
#include "DlgSimulationComparison.h"
#include "Base/Interpreter.h"


using namespace std;

//===========================================================================
// UserDefinedPhenomenonLab_NewSimulation
//===========================================================================
DEF_STD_CMD_A(CmdUserDefinedPhenomenonLabNewSimulation)

CmdUserDefinedPhenomenonLabNewSimulation::CmdUserDefinedPhenomenonLabNewSimulation() : Command("UserDefinedPhenomenonLab_NewSimulation")
{
    sAppModule = "UserDefinedPhenomenonLab";
    sGroup = QT_TR_NOOP("UserDefinedPhenomenonLab");
    sMenuText = QT_TR_NOOP("New Simulation");
    sToolTipText = QT_TR_NOOP("Creation of new simulation");
    sWhatsThis = "UserDefinedPhenomenonLab_NewSimulation";
    sStatusTip = sToolTipText;
    sPixmap = "UserDefinedPhenomenonLab_NewSimulation";
}

void CmdUserDefinedPhenomenonLabNewSimulation::activated(int iMsg)
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
        UserDefinedPhenomenonLabGui::TaskNewSimulation* dlg = new UserDefinedPhenomenonLabGui::TaskNewSimulation();
        Gui::Control().showDialog(dlg);
    }
}

bool CmdUserDefinedPhenomenonLabNewSimulation::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// UserDefinedPhenomenonLab_Features
//===========================================================================
DEF_STD_CMD_A(CmdUserDefinedPhenomenonLabFeatures)

CmdUserDefinedPhenomenonLabFeatures::CmdUserDefinedPhenomenonLabFeatures() : Command("UserDefinedPhenomenonLab_Features")
{
    sAppModule = "UserDefinedPhenomenonLab";
    sGroup = QT_TR_NOOP("UserDefinedPhenomenonLab");
    sMenuText = QT_TR_NOOP("Create Features...");
    sToolTipText = QT_TR_NOOP("Creation of UserDefinedPhenomenonLab Features");
    sWhatsThis = "UserDefinedPhenomenonLab_Features";
    sStatusTip = sToolTipText;
    sPixmap = "UserDefinedPhenomenonLab_Features";
}

void CmdUserDefinedPhenomenonLabFeatures::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
        std::stringstream str;
        str << "Gui.runCommand('New_PythonUserDefinedPhenomenonLabFeature')" << std::endl;
        Base::Interpreter().runString(str.str().c_str());
    }
    else if (PlugLang == "C++") {
        UserDefinedPhenomenonLabGui::TaskUserDefinedPhenomenonLabFeatures* dlg = new UserDefinedPhenomenonLabGui::TaskUserDefinedPhenomenonLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdUserDefinedPhenomenonLabFeatures::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// UserDefinedPhenomenonLab_Features_LocationDistribution
//===========================================================================
DEF_STD_CMD_A(CmdUserDefinedPhenomenonLabFeaturesLocationDistribution)

CmdUserDefinedPhenomenonLabFeaturesLocationDistribution::CmdUserDefinedPhenomenonLabFeaturesLocationDistribution() : Command("UserDefinedPhenomenonLab_Features_LocationDistribution")
{
    sAppModule = "UserDefinedPhenomenonLab";
    sGroup = QT_TR_NOOP("UserDefinedPhenomenonLab");
    sMenuText = QT_TR_NOOP("Create Location Distribution...");
    sToolTipText = QT_TR_NOOP("Creation of Location Distribution Feature");
    sWhatsThis = "UserDefinedPhenomenonLab_Features_LocationDistribution";
    sStatusTip = sToolTipText;
    sPixmap = "UserDefinedPhenomenonLab_Features_LocationDistribution";
}

void CmdUserDefinedPhenomenonLabFeaturesLocationDistribution::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {

    }
    else if (PlugLang == "C++") {
        UserDefinedPhenomenonLabGui::TaskUserDefinedPhenomenonLabFeatures* dlg = new UserDefinedPhenomenonLabGui::TaskUserDefinedPhenomenonLabFeatures();
        Gui::Control().showDialog(dlg);
    }

}

bool CmdUserDefinedPhenomenonLabFeaturesLocationDistribution::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}

//===========================================================================
// UserDefinedPhenomenonLab_Comparison
//===========================================================================
DEF_STD_CMD_A(CmdUserDefinedPhenomenonLabComparison)

CmdUserDefinedPhenomenonLabComparison::CmdUserDefinedPhenomenonLabComparison() : Command("UserDefinedPhenomenonLab_Comparison")
{
    sAppModule = "UserDefinedPhenomenonLab";
    sGroup = QT_TR_NOOP("UserDefinedPhenomenonLab");
    sMenuText = QT_TR_NOOP("Compare");
    sToolTipText = QT_TR_NOOP("Compare two UserDefinedPhenomenonLab features in terms of accuracy, computation time and memory consumption");
    sWhatsThis = "UserDefinedPhenomenonLab_Comparison";
    sStatusTip = sToolTipText;
    sPixmap = "UserDefinedPhenomenonLab_Comparison";
}

void CmdUserDefinedPhenomenonLabComparison::activated(int iMsg)
{
    Q_UNUSED(iMsg);

     std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
        std::stringstream str;
        str << "Gui.runCommand('UserDefinedPhenomenonLab_PythonComparison')" << std::endl;
        Base::Interpreter().runString(str.str().c_str());
    }
    else if (PlugLang == "C++") {
        UserDefinedPhenomenonLabGui::DlgSimulationComparisonEdit* dlg = new UserDefinedPhenomenonLabGui::DlgSimulationComparisonEdit(nullptr);
        Gui::Control().showDialog(dlg);
    }
}

bool CmdUserDefinedPhenomenonLabComparison::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}
void CreateUserDefinedPhenomenonLabCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdUserDefinedPhenomenonLabNewSimulation());
    rcCmdMgr.addCommand(new CmdUserDefinedPhenomenonLabFeatures());
    rcCmdMgr.addCommand(new CmdUserDefinedPhenomenonLabComparison());

}
