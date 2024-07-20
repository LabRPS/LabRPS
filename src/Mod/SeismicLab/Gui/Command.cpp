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
#include "DlgSimulationComparison.h"
#include "Base/Interpreter.h"


using namespace std;

//===========================================================================
// SeismicLab_NewSimulation
//===========================================================================
DEF_STD_CMD_A(CmdSeismicLabNewSimulation)

CmdSeismicLabNewSimulation::CmdSeismicLabNewSimulation() : Command("SeismicLab_NewSimulation")
{
    sAppModule = "SeismicLab";
    sGroup = QT_TR_NOOP("SeismicLab");
    sMenuText = QT_TR_NOOP("New Simulation");
    sToolTipText = QT_TR_NOOP("Creation of new simulation");
    sWhatsThis = "SeismicLab_NewSimulation";
    sStatusTip = sToolTipText;
    sPixmap = "SeismicLab_NewSimulation";
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
// SeismicLab_Features
//===========================================================================
DEF_STD_CMD_A(CmdSeismicLabFeatures)

CmdSeismicLabFeatures::CmdSeismicLabFeatures() : Command("SeismicLab_Features")
{
    sAppModule = "SeismicLab";
    sGroup = QT_TR_NOOP("SeismicLab");
    sMenuText = QT_TR_NOOP("Create Features...");
    sToolTipText = QT_TR_NOOP("Creation of SeismicLab Features");
    sWhatsThis = "SeismicLab_Features";
    sStatusTip = sToolTipText;
    sPixmap = "SeismicLab_Features";
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
// SeismicLab_Comparison
//===========================================================================
DEF_STD_CMD_A(CmdSeismicLabComparison)

CmdSeismicLabComparison::CmdSeismicLabComparison() : Command("SeismicLab_Comparison")
{
    sAppModule = "SeismicLab";
    sGroup = QT_TR_NOOP("SeismicLab");
    sMenuText = QT_TR_NOOP("Compare");
    sToolTipText = QT_TR_NOOP("Compare two SeismicLab features in terms of accuracy, computation time and memory consumption");
    sWhatsThis = "SeismicLab_Comparison";
    sStatusTip = sToolTipText;
    sPixmap = "SeismicLab_Comparison";
}

void CmdSeismicLabComparison::activated(int iMsg)
{
    Q_UNUSED(iMsg);

     std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
        std::stringstream str;
        str << "Gui.runCommand('SeismicLab_PythonComparison')" << std::endl;
        Base::Interpreter().runString(str.str().c_str());
    }
    else if (PlugLang == "C++") {
        SeismicLabGui::DlgSimulationComparisonEdit* dlg = new SeismicLabGui::DlgSimulationComparisonEdit(nullptr);
        Gui::Control().showDialog(dlg);
    }
}

bool CmdSeismicLabComparison::isActive(void)
{
    return (hasActiveDocument() && !Gui::Control().activeDialog());
}
void CreateSeismicLabCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdSeismicLabNewSimulation());
    rcCmdMgr.addCommand(new CmdSeismicLabFeatures());
    rcCmdMgr.addCommand(new CmdSeismicLabComparison());

}
