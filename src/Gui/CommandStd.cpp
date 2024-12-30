/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *                                                                         *
 *   This file is part of the LabRPS CAx development system.              *
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
# include <QMessageBox>
# include <QWhatsThis>
#endif

#include <App/Document.h>
#include <Base/Exception.h>
#include <Base/Interpreter.h>
#include <Base/Sequencer.h>

#include "Action.h"
#include "BitmapFactory.h"
#include "Command.h"
#include "DlgCustomizeImp.h"
#include "DlgParameterImp.h"
#include "DlgPreferencesImp.h"
#include "DlgUnitsCalculatorImp.h"
#include "GuiConsole.h"
#include "MainWindow.h"
#include "OnlineDocumentation.h"
#include "Selection.h"
#include "Splashscreen.h"
#include "WhatsThis.h"
#include "Workbench.h"
#include "WorkbenchManager.h"
#include "AlphaPlot.h"
#include <Libraries/Alphaplot/2Dplot/Graph2DCommon.h>

using Base::Console;
using Base::Sequencer;
using namespace Gui;
namespace bp = boost::placeholders;


//===========================================================================
// Std_Workbench
//===========================================================================

DEF_STD_CMD_AC(StdCmdWorkbench)

StdCmdWorkbench::StdCmdWorkbench()
  : Command("Std_Workbench")
{
    sGroup        = "View";
    sMenuText     = QT_TR_NOOP("Workbench");
    sToolTipText  = QT_TR_NOOP("Switch between workbenches");
    sWhatsThis    = "Std_Workbench";
    sStatusTip    = QT_TR_NOOP("Switch between workbenches");
    sPixmap       = "labrps";
    eType         = 0;
}

void StdCmdWorkbench::activated(int i)
{
    try {
        Workbench* w = WorkbenchManager::instance()->active();
        QList<QAction*> items = static_cast<WorkbenchGroup*>(_pcAction)->actions();
        std::string switch_to = (const char*)items[i]->objectName().toLatin1();
        if (w) {
            std::string current_w = w->name();
            if (switch_to == current_w)
                return;
        }
        doCommand(Gui, "Gui.activateWorkbench(\"%s\")", switch_to.c_str());
    }
    catch(const Base::PyException& e) {
        QString msg(QLatin1String(e.what()));
        // ignore '<type 'exceptions.*Error'>' prefixes
        QRegExp rx;
        rx.setPattern(QLatin1String("^\\s*<type 'exceptions.\\w*'>:\\s*"));
        int pos = rx.indexIn(msg);
        if (pos != -1)
            msg = msg.mid(rx.matchedLength());
        QMessageBox::critical(getMainWindow(), QObject::tr("Cannot load workbench"), msg);
    }
    catch(...) {
        QMessageBox::critical(getMainWindow(), QObject::tr("Cannot load workbench"),
            QObject::tr("A general error occurred while loading the workbench"));
    }
}

bool StdCmdWorkbench::isActive()
{
    return true;
}

Action * StdCmdWorkbench::createAction()
{
    Action *pcAction;

    pcAction = new WorkbenchGroup(this,getMainWindow());
    pcAction->setShortcut(QString::fromLatin1(getAccel()));
    applyCommandData(this->className(), pcAction);
    if (getPixmap())
        pcAction->setIcon(Gui::BitmapFactory().iconFromTheme(getPixmap()));

    return pcAction;
}

//===========================================================================
// Std_RecentFiles
//===========================================================================

DEF_STD_CMD_C(StdCmdRecentFiles)

StdCmdRecentFiles::StdCmdRecentFiles()
  :Command("Std_RecentFiles")
{
    sGroup        = "File";
    sMenuText     = QT_TR_NOOP("Recent files");
    sToolTipText  = QT_TR_NOOP("Recent file list");
    sWhatsThis    = "Std_RecentFiles";
    sStatusTip    = QT_TR_NOOP("Recent file list");
    sPixmap       = "Std_RecentFiles";
    eType         = NoTransaction;
}

/**
 * Opens the recent file at position \a iMsg in the menu.
 * If the file does not exist or cannot be loaded this item is removed
 * from the list.
 */
void StdCmdRecentFiles::activated(int iMsg)
{
    RecentFilesAction* act = qobject_cast<RecentFilesAction*>(_pcAction);
    if (act) act->activateFile( iMsg );
}

/**
 * Creates the QAction object containing the recent files.
 */
Action * StdCmdRecentFiles::createAction()
{
    RecentFilesAction* pcAction = new RecentFilesAction(this, getMainWindow());
    pcAction->setObjectName(QLatin1String("recentFiles"));
    pcAction->setDropDownMenu(true);
    applyCommandData(this->className(), pcAction);
    return pcAction;
}

//===========================================================================
// Std_RecentMacros
//===========================================================================

DEF_STD_CMD_C(StdCmdRecentMacros)

StdCmdRecentMacros::StdCmdRecentMacros()
  :Command("Std_RecentMacros")
{
    sGroup        = "Macro";
    sMenuText     = QT_TR_NOOP("Recent macros");
    sToolTipText  = QT_TR_NOOP("Recent macro list");
    sWhatsThis    = "Std_RecentMacros";
    sStatusTip    = QT_TR_NOOP("Recent macro list");
    eType         = NoTransaction;
}

/**
 * Opens the recent macro at position \a iMsg in the menu.
 * If the macro does not exist or cannot be loaded this item is removed
 * from the list.
 */
void StdCmdRecentMacros::activated(int iMsg)
{
    RecentMacrosAction* act = qobject_cast<RecentMacrosAction*>(_pcAction);
    if (act) act->activateFile( iMsg );
}

/**
 * Creates the QAction object containing the recent macros.
 */
Action * StdCmdRecentMacros::createAction()
{
    RecentMacrosAction* pcAction = new RecentMacrosAction(this, getMainWindow());
    pcAction->setObjectName(QLatin1String("recentMacros"));
    pcAction->setDropDownMenu(true);
    applyCommandData(this->className(), pcAction);
    return pcAction;
}

//===========================================================================
// Std_About
//===========================================================================

DEF_STD_CMD_ACL(StdCmdAbout)

StdCmdAbout::StdCmdAbout()
  :Command("Std_About")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("&About %1");
    sToolTipText  = QT_TR_NOOP("About %1");
    sWhatsThis    = "Std_About";
    sStatusTip    = QT_TR_NOOP("About %1");
    eType         = 0;
}

Action * StdCmdAbout::createAction()
{
    Action *pcAction;

    QString exe = qApp->applicationName();
    pcAction = new Action(this,getMainWindow());
    pcAction->setText(QCoreApplication::translate(
        this->className(), getMenuText()).arg(exe));
    pcAction->setToolTip(QCoreApplication::translate(
        this->className(), getToolTipText()).arg(exe));
    pcAction->setStatusTip(QCoreApplication::translate(
        this->className(), getStatusTip()).arg(exe));
    pcAction->setWhatsThis(QLatin1String(getWhatsThis()));
    pcAction->setIcon(QApplication::windowIcon());
    pcAction->setShortcut(QString::fromLatin1(getAccel()));
    // Needs to have AboutRole set to avoid duplicates if adding the about action more than once on macOS
    pcAction->setMenuRole(QAction::AboutRole);
    return pcAction;
}

bool StdCmdAbout::isActive()
{
    return true;
}

/**
 * Shows information about the application.
 */
void StdCmdAbout::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    const Gui::Dialog::AboutDialogFactory* f = Gui::Dialog::AboutDialogFactory::defaultFactory();
    boost::scoped_ptr<QDialog> dlg(f->create(getMainWindow()));
    dlg->exec();
}

void StdCmdAbout::languageChange()
{
    if (_pcAction) {
        QString exe = qApp->applicationName();
        _pcAction->setText(QCoreApplication::translate(
            this->className(), getMenuText()).arg(exe));
        _pcAction->setToolTip(QCoreApplication::translate(
            this->className(), getToolTipText()).arg(exe));
        _pcAction->setStatusTip(QCoreApplication::translate(
            this->className(), getStatusTip()).arg(exe));
        _pcAction->setWhatsThis(QLatin1String(getWhatsThis()));
    }
}

//===========================================================================
// Std_AboutQt
//===========================================================================
DEF_STD_CMD(StdCmdAboutQt)

StdCmdAboutQt::StdCmdAboutQt()
  :Command("Std_AboutQt")
{
  sGroup        = "Help";
  sMenuText     = QT_TR_NOOP("About &Qt");
  sToolTipText  = QT_TR_NOOP("About Qt");
  sWhatsThis    = "Std_AboutQt";
  sStatusTip    = QT_TR_NOOP("About Qt");
  eType         = 0;
}

void StdCmdAboutQt::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    qApp->aboutQt();
}

//===========================================================================
// Std_WhatsThis
//===========================================================================
DEF_STD_CMD(StdCmdWhatsThis)

StdCmdWhatsThis::StdCmdWhatsThis()
  :Command("Std_WhatsThis")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("&What's This?");
    sToolTipText  = QT_TR_NOOP("What's This");
    sWhatsThis    = "Std_WhatsThis";
    sStatusTip    = QT_TR_NOOP("What's This");
    sAccel        = keySequenceToAccel(QKeySequence::WhatsThis);
    sPixmap       = "WhatsThis";
    eType         = 0;
}

void StdCmdWhatsThis::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    QWhatsThis::enterWhatsThisMode();
}

//===========================================================================
// Std_DlgParameter
//===========================================================================
DEF_STD_CMD(StdCmdDlgParameter)

StdCmdDlgParameter::StdCmdDlgParameter()
  :Command("Std_DlgParameter")
{
  sGroup        = "Tools";
  sMenuText     = QT_TR_NOOP("E&dit parameters ...");
  sToolTipText  = QT_TR_NOOP("Opens a Dialog to edit the parameters");
  sWhatsThis    = "Std_DlgParameter";
  sStatusTip    = QT_TR_NOOP("Opens a Dialog to edit the parameters");
  sPixmap       = "Std_DlgParameter";
  eType         = 0;
}

void StdCmdDlgParameter::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::Dialog::DlgParameterImp cDlg(getMainWindow());
    cDlg.resize(QSize(800, 600));
    cDlg.exec();
}

//===========================================================================
// Std_DlgPreferences
//===========================================================================
DEF_STD_CMD_C(StdCmdDlgPreferences)

StdCmdDlgPreferences::StdCmdDlgPreferences()
  :Command("Std_DlgPreferences")
{
    sGroup        = "Tools";
    sMenuText     = QT_TR_NOOP("&Preferences ...");
    sToolTipText  = QT_TR_NOOP("Opens a Dialog to edit the preferences");
    sWhatsThis    = "Std_DlgPreferences";
    sStatusTip    = QT_TR_NOOP("Opens a Dialog to edit the preferences");
    sPixmap     = "preferences-system";
    eType         = 0;
}

Action * StdCmdDlgPreferences::createAction()
{
    Action *pcAction = Command::createAction();
    pcAction->setMenuRole(QAction::PreferencesRole);

    return pcAction;
}

void StdCmdDlgPreferences::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::Dialog::DlgPreferencesImp cDlg(getMainWindow());
    cDlg.exec();
}

//===========================================================================
// Std_DlgCustomize
//===========================================================================
DEF_STD_CMD(StdCmdDlgCustomize)

StdCmdDlgCustomize::StdCmdDlgCustomize()
  :Command("Std_DlgCustomize")
{
    sGroup        = "Tools";
    sMenuText     = QT_TR_NOOP("Cu&stomize...");
    sToolTipText  = QT_TR_NOOP("Customize toolbars and command bars");
    sWhatsThis    = "Std_DlgCustomize";
    sStatusTip    = QT_TR_NOOP("Customize toolbars and command bars");
    sPixmap       = "applications-accessories";
    eType         = 0;
}

void StdCmdDlgCustomize::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    static QPointer<QDialog> dlg = nullptr;
    if (!dlg)
        dlg = new Gui::Dialog::DlgCustomizeImp(getMainWindow());
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

//===========================================================================
// Std_CommandLine
//===========================================================================
DEF_STD_CMD(StdCmdCommandLine)

StdCmdCommandLine::StdCmdCommandLine()
  :Command("Std_CommandLine")
{
    sGroup        = "Tools";
    sMenuText     = QT_TR_NOOP("Start command &line...");
    sToolTipText  = QT_TR_NOOP("Opens the command line in the console");
    sWhatsThis    = "Std_CommandLine";
    sStatusTip    = QT_TR_NOOP("Opens the command line in the console");
    sPixmap       = "utilities-terminal";
    eType         = 0;
}

void StdCmdCommandLine::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    bool show = getMainWindow()->isMaximized ();

    // pop up the Gui command window
    GUIConsole Wnd;

    getMainWindow()->showMinimized () ;
    qApp->processEvents();

    // create temporary console sequencer
    {
          Base::ConsoleSequencer seq;
          Base::Interpreter().runCommandLine("Console mode");
    }

#ifdef Q_WS_X11
    // On X11 this may not work. For further information see QWidget::showMaximized
    //
    // workaround for X11
    getMainWindow()->hide();
    getMainWindow()->show();
#endif

    // pop up the main window
    show ? getMainWindow()->showMaximized () : getMainWindow()->showNormal () ;
    qApp->processEvents();
}

//===========================================================================
// Std_OnlineHelp
//===========================================================================

DEF_STD_CMD(StdCmdOnlineHelp)

StdCmdOnlineHelp::StdCmdOnlineHelp()
  :Command("Std_OnlineHelp")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("Help");
    sToolTipText  = QT_TR_NOOP("Show help to the application");
    sWhatsThis    = "Std_OnlineHelp";
    sStatusTip    = QT_TR_NOOP("Help");
    sPixmap       = "help-browser";
    sAccel        = keySequenceToAccel(QKeySequence::HelpContents);
    eType         = 0;
}

void StdCmdOnlineHelp::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->showDocumentation(QString::fromLatin1("Online_Help_Startpage"));
}

//===========================================================================
// Std_OnlineHelpWebsite
//===========================================================================

DEF_STD_CMD(StdCmdOnlineHelpWebsite)

StdCmdOnlineHelpWebsite::StdCmdOnlineHelpWebsite()
  :Command("Std_OnlineHelpWebsite")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("Help Website");
    sToolTipText  = QT_TR_NOOP("The website where the help is maintained");
    sWhatsThis    = "Std_OnlineHelpWebsite";
    sStatusTip    = QT_TR_NOOP("Help Website");
    eType         = 0;
}

void StdCmdOnlineHelpWebsite::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    std::string defaulturl = QCoreApplication::translate(this->className(),"https://wiki.labrps.com/Online_Help_Toc").toStdString();
    ParameterGrp::handle hURLGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Websites");
    std::string url = hURLGrp->GetASCII("OnlineHelp", defaulturl.c_str());
    hURLGrp->SetASCII("OnlineHelp", url.c_str());
    OpenURLInBrowser(url.c_str());
}

//===========================================================================
// Std_LabRPSDonation
//===========================================================================

DEF_STD_CMD(StdCmdLabRPSDonation)

StdCmdLabRPSDonation::StdCmdLabRPSDonation()
  :Command("Std_LabRPSDonation")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("Donate");
    sToolTipText  = QT_TR_NOOP("Donate to LabRPS development");
    sWhatsThis    = "Std_LabRPSDonation";
    sStatusTip    = sToolTipText;
    sPixmap       = "internet-web-browser";
    eType         = 0;
}

void StdCmdLabRPSDonation::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    ParameterGrp::handle hURLGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Websites");
    std::string url = hURLGrp->GetASCII("DonatePage", "https://wiki.labrps.com/Donate");
    hURLGrp->SetASCII("DonatePage", url.c_str());
    OpenURLInBrowser(url.c_str());
}

//===========================================================================
// Std_LabRPSWebsite
//===========================================================================

DEF_STD_CMD(StdCmdLabRPSWebsite)

StdCmdLabRPSWebsite::StdCmdLabRPSWebsite()
  :Command("Std_Homepage")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("LabRPS Website");
    sToolTipText  = QT_TR_NOOP("The LabRPS website");
    sWhatsThis    = "Std_Homepage";
    sStatusTip    = QT_TR_NOOP("LabRPS Website");
    sPixmap       = "internet-web-browser";
    eType         = 0;
}

void StdCmdLabRPSWebsite::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    std::string defaulturl = QCoreApplication::translate(this->className(),"https://www.labrps.com").toStdString();
    ParameterGrp::handle hURLGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Websites");
    std::string url = hURLGrp->GetASCII("WebPage", defaulturl.c_str());
    hURLGrp->SetASCII("WebPage", url.c_str());
    OpenURLInBrowser(url.c_str());
}

//===========================================================================
// Std_LabRPSUserHub
//===========================================================================

DEF_STD_CMD(StdCmdLabRPSUserHub)

StdCmdLabRPSUserHub::StdCmdLabRPSUserHub()
  :Command("Std_LabRPSUserHub")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("Users documentation");
    sToolTipText  = QT_TR_NOOP("Documentation for users on the LabRPS website");
    sWhatsThis    = "Std_LabRPSUserHub";
    sStatusTip    = QT_TR_NOOP("Users documentation");
    sPixmap       = "internet-web-browser";
    eType         = 0;
}

void StdCmdLabRPSUserHub::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    std::string defaulturl = QCoreApplication::translate(this->className(),"https://wiki.labrps.com/User_hub").toStdString();
    ParameterGrp::handle hURLGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Websites");
    std::string url = hURLGrp->GetASCII("Documentation", defaulturl.c_str());
    hURLGrp->SetASCII("Documentation", url.c_str());
    OpenURLInBrowser(url.c_str());
}

//===========================================================================
// Std_LabRPSPowerUserHub
//===========================================================================

DEF_STD_CMD(StdCmdLabRPSPowerUserHub)

StdCmdLabRPSPowerUserHub::StdCmdLabRPSPowerUserHub()
  :Command("Std_LabRPSPowerUserHub")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("Python scripting documentation");
    sToolTipText  = QT_TR_NOOP("Python scripting documentation on the LabRPS website");
    sWhatsThis    = "Std_LabRPSPowerUserHub";
    sStatusTip    = QT_TR_NOOP("PowerUsers documentation");
    sPixmap       = "internet-web-browser";
    eType         = 0;
}

void StdCmdLabRPSPowerUserHub::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    std::string defaulturl = QCoreApplication::translate(this->className(),"https://wiki.labrps.com/Power_users_hub").toStdString();
    ParameterGrp::handle hURLGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Websites");
    std::string url = hURLGrp->GetASCII("PowerUsers", defaulturl.c_str());
    hURLGrp->SetASCII("PowerUsers", url.c_str());
    OpenURLInBrowser(url.c_str());
}

//===========================================================================
// Std_LabRPSForum
//===========================================================================

DEF_STD_CMD(StdCmdLabRPSForum)

StdCmdLabRPSForum::StdCmdLabRPSForum()
  :Command("Std_LabRPSForum")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("LabRPS Forum");
    sToolTipText  = QT_TR_NOOP("The LabRPS forum, where you can find help from other users");
    sWhatsThis    = "Std_LabRPSForum";
    sStatusTip    = QT_TR_NOOP("The LabRPS Forum");
    sPixmap       = "internet-web-browser";
    eType         = 0;
}

void StdCmdLabRPSForum::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    std::string defaulturl = QCoreApplication::translate(this->className(),"https://forum.labrps.com").toStdString();
    ParameterGrp::handle hURLGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Websites");
    std::string url = hURLGrp->GetASCII("UserForum", defaulturl.c_str());
    hURLGrp->SetASCII("UserForum", url.c_str());
    OpenURLInBrowser(url.c_str());
}

//===========================================================================
// Std_LabRPSFAQ
//===========================================================================

DEF_STD_CMD(StdCmdLabRPSFAQ)

StdCmdLabRPSFAQ::StdCmdLabRPSFAQ()
  :Command("Std_LabRPSFAQ")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("LabRPS FAQ");
    sToolTipText  = QT_TR_NOOP("Frequently Asked Questions on the LabRPS website");
    sWhatsThis    = "Std_LabRPSFAQ";
    sStatusTip    = QT_TR_NOOP("Frequently Asked Questions");
    sPixmap       = "internet-web-browser";
    eType         = 0;
}

void StdCmdLabRPSFAQ::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    std::string defaulturl = QCoreApplication::translate(this->className(),"https://wiki.labrps.com/Frequently_asked_questions").toStdString();
    ParameterGrp::handle hURLGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Websites");
    std::string url = hURLGrp->GetASCII("FAQ", defaulturl.c_str());
    hURLGrp->SetASCII("FAQ", url.c_str());
    OpenURLInBrowser(url.c_str());
}

//===========================================================================
// Std_PythonWebsite
//===========================================================================

DEF_STD_CMD(StdCmdPythonWebsite)

StdCmdPythonWebsite::StdCmdPythonWebsite()
  :Command("Std_PythonWebsite")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("Python Website");
    sToolTipText  = QT_TR_NOOP("The official Python website");
    sWhatsThis    = "Std_PythonWebsite";
    sStatusTip    = QT_TR_NOOP("Python Website");
    sPixmap       = "applications-python";
    eType         = 0;
}

void StdCmdPythonWebsite::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    OpenURLInBrowser("https://www.python.org");
}


//===========================================================================
// Std_ReportBug
//===========================================================================

DEF_STD_CMD(StdCmdReportBug)

StdCmdReportBug::StdCmdReportBug()
  :Command("Std_ReportBug")
{
    sGroup        = "Help";
    sMenuText     = QT_TR_NOOP("Report a bug");
    sToolTipText  = QT_TR_NOOP("Report a bug or suggest a feature");
    sWhatsThis    = "Std_ReportBug";
    sStatusTip    = QT_TR_NOOP("Report a bug or suggest a feature");
    sPixmap       = "internet-web-browser";
    eType         = 0;
}

void StdCmdReportBug::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    ParameterGrp::handle hURLGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Websites");
    std::string url = hURLGrp->GetASCII("IssuesPage", "https://github.com/LabRPS/LabRPS/issues");
    hURLGrp->SetASCII("IssuesPage", url.c_str());
    OpenURLInBrowser(url.c_str());
}


//===========================================================================
// Std_MeasurementSimple
//===========================================================================

DEF_STD_CMD(StdCmdMeasurementSimple)

StdCmdMeasurementSimple::StdCmdMeasurementSimple()
  :Command("Std_MeasurementSimple")
{
    sGroup        = "Tools";
    sMenuText     = QT_TR_NOOP("Measure distance");
    sToolTipText  = QT_TR_NOOP("Measures distance between two selected objects");
    sWhatsThis    = "Std_MeasurementSimple";
    sStatusTip    = QT_TR_NOOP("Measures distance between two selected objects");
    sPixmap       = "view-measurement";
    eType         = 0;
}

void StdCmdMeasurementSimple::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    unsigned int n = getSelection().countObjectsOfType(App::DocumentObject::getClassTypeId());

    if (n == 1) {
        QMessageBox::warning(Gui::getMainWindow(), QObject::tr("Wrong selection"),
            QObject::tr("Only one object selected. Please select two objects.\n"
                        "Be aware the point where you click matters."));
        return;
    }
    if (n < 1 || n > 2) {
        QMessageBox::warning(Gui::getMainWindow(), QObject::tr("Wrong selection"),
            QObject::tr("Please select two objects.\n"
                        "Be aware the point where you click matters."));
        return;
    }

    std::vector<Gui::SelectionSingleton::SelObj> Sel = getSelection().getSelection();

    std::string name;
    name += "Dist ";
    name += Sel[0].FeatName;
    name += "-";
    name += Sel[0].SubName;
    name += " to ";
    name += Sel[1].FeatName;
    name += "-";
    name += Sel[1].SubName;

    openCommand(QT_TRANSLATE_NOOP("Command", "Insert measurement"));
    doCommand(Doc,"_f = App.activeDocument().addObject(\"App::MeasureDistance\",\"%s\")","Measurement");
    doCommand(Doc,"_f.Label ='%s'",name.c_str());
    doCommand(Doc,"_f.P1 = LabRPS.Vector(%f,%f,%f)",Sel[0].x,Sel[0].y,Sel[0].z);
    doCommand(Doc,"_f.P2 = LabRPS.Vector(%f,%f,%f)",Sel[1].x,Sel[1].y,Sel[1].z);
    updateActive();
    commitCommand();
}

//===========================================================================
// Std_TextDocument
//===========================================================================

DEF_STD_CMD_A(StdCmdTextDocument)

StdCmdTextDocument::StdCmdTextDocument()
  :Command("Std_TextDocument")
{
    sGroup        = "Tools";
    sMenuText     = QT_TR_NOOP("Add text document");
    sToolTipText  = QT_TR_NOOP("Add text document to active document");
    sWhatsThis    = "Std_TextDocument";
    sStatusTip    = QT_TR_NOOP("Add text document to active document");
    sPixmap       = "TextDocument";
    eType         = 0;
}

void StdCmdTextDocument::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    openCommand(QT_TRANSLATE_NOOP("Command", "Insert text document"));
    doCommand(Doc, "App.ActiveDocument.addObject(\"App::TextDocument\",\"%s\").Label=\"%s\"","Text document","Text document");
    doCommand(Gui, "Gui.ActiveDocument.ActiveObject.doubleClicked()");
    updateActive();
    commitCommand();
}

bool StdCmdTextDocument::isActive()
{
    return hasActiveDocument();
}

//===========================================================================
// Std_UnitsCalculator
//===========================================================================
DEF_STD_CMD(StdCmdUnitsCalculator)

StdCmdUnitsCalculator::StdCmdUnitsCalculator()
  : Command("Std_UnitsCalculator")
{
    sGroup        = "Tools";
    sMenuText     = QT_TR_NOOP("&Units calculator...");
    sToolTipText  = QT_TR_NOOP("Start the units calculator");
    sWhatsThis    = "Std_UnitsCalculator";
    sStatusTip    = QT_TR_NOOP("Start the units calculator");
    sPixmap       = "accessories-calculator";
    eType         = 0;
}

void StdCmdUnitsCalculator::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::Dialog::DlgUnitsCalculator *dlg = new Gui::Dialog::DlgUnitsCalculator( getMainWindow() );
    dlg->show();
}

//===========================================================================
// StdCmdUserEditMode
//===========================================================================
class StdCmdUserEditMode : public Gui::Command
{
public:
    StdCmdUserEditMode();
    virtual ~StdCmdUserEditMode(){}
    virtual void languageChange();
    virtual const char* className() const {return "StdCmdUserEditMode";}
    void updateIcon(int mode);
protected:
    virtual void activated(int iMsg);
    virtual bool isActive();
    virtual Gui::Action * createAction();
};

StdCmdUserEditMode::StdCmdUserEditMode()
  : Command("Std_UserEditMode")
{
    sGroup        = "Edit";
    sMenuText     = QT_TR_NOOP("Edit mode");
    sToolTipText  = QT_TR_NOOP("Defines behavior when editing an object from tree");
    sStatusTip    = QT_TR_NOOP("Defines behavior when editing an object from tree");
    sWhatsThis    = "Std_UserEditMode";
    sPixmap       = "Std_UserEditModeDefault";
    eType         = ForEdit;

    this->getGuiApplication()->signalUserEditModeChanged.connect(boost::bind(&StdCmdUserEditMode::updateIcon, this, bp::_1));
}

Gui::Action * StdCmdUserEditMode::createAction()
{
    Gui::ActionGroup* pcAction = new Gui::ActionGroup(this, Gui::getMainWindow());
    pcAction->setDropDownMenu(true);
    pcAction->setIsMode(true);
    applyCommandData(this->className(), pcAction);

    for (auto const &uem : Gui::Application::Instance->listUserEditModes()) {
        QAction* act = pcAction->addAction(QString());
        auto modeName = QString::fromStdString(uem.second);
        act->setCheckable(true);
        act->setIcon(BitmapFactory().iconFromTheme(qPrintable(QString::fromLatin1("Std_UserEditMode")+modeName)));
        act->setObjectName(QString::fromLatin1("Std_UserEditMode")+modeName);
        act->setWhatsThis(QString::fromLatin1(getWhatsThis()));

        if (uem.first == 0) {
            pcAction->setIcon(act->icon());
            act->setChecked(true);
        }
    }

    _pcAction = pcAction;

    int lastMode = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")->
        GetInt("UserEditMode", 0);
    Gui::Application::Instance->setUserEditMode(lastMode);

    languageChange();
    return pcAction;
}

void StdCmdUserEditMode::languageChange()
{
    Command::languageChange();

    if (!_pcAction)
        return;
    Gui::ActionGroup* pcAction = qobject_cast<Gui::ActionGroup*>(_pcAction);
    QList<QAction*> a = pcAction->actions();

    for (int i = 0 ; i < a.count() ; i++) {
        auto modeName = QString::fromStdString(Gui::Application::Instance->getUserEditModeName(i));
        a[i]->setText(QCoreApplication::translate(
        "EditMode", qPrintable(modeName)));
        a[i]->setToolTip(QCoreApplication::translate(
        "EditMode", qPrintable(modeName+QString::fromLatin1(" mode"))));
    }
}

void StdCmdUserEditMode::updateIcon(int mode)
{
    Gui::ActionGroup *actionGroup = dynamic_cast<Gui::ActionGroup *>(_pcAction);
    if (!actionGroup)
        return;

    actionGroup->setCheckedAction(mode);
}

void StdCmdUserEditMode::activated(int iMsg)
{
    App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")->
            SetInt("UserEditMode", iMsg);
    Gui::Application::Instance->setUserEditMode(iMsg);
}

bool StdCmdUserEditMode::isActive()
{
    return true;
}

//===========================================================================
// Std_Scatter
//===========================================================================

DEF_STD_CMD_A(StdScatter)

StdScatter::StdScatter() : Command("Std_Plot_Scatters")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Scatter");
    sToolTipText = QT_TR_NOOP("Add Scatter Plot");
    sWhatsThis = "Std_Plot_Scatters";
    sStatusTip = QT_TR_NOOP("Add Scatter Plot");
    sPixmap = "Std_Plot_Scatters";
    eType = 0;
}

void StdScatter::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::Scatter));
}

bool StdScatter::isActive() { return true; }

//===========================================================================
// Std_ScatterWithXError
//===========================================================================

DEF_STD_CMD_A(StdScatterWithXError)

StdScatterWithXError::StdScatterWithXError() : Command("Std_Plot_Scatters_with_xerr")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Scatter With X Error");
    sToolTipText = QT_TR_NOOP("Scatter With X Error");
    sWhatsThis = "Std_Plot_Scatters_with_xerr";
    sStatusTip = QT_TR_NOOP("Scatter With X Error");
    sPixmap = nullptr;
    eType = 0;
}

void StdScatterWithXError::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(
        static_cast<int>(PlotStyle::Graph::ScatterXError));
}

bool StdScatterWithXError::isActive() { return true; }

//===========================================================================
// Std_ScatterWithYError
//===========================================================================

DEF_STD_CMD_A(StdScatterWithYError)

StdScatterWithYError::StdScatterWithYError() : Command("Std_Plot_Scatters_with_yerr")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Scatter With Y Error");
    sToolTipText = QT_TR_NOOP("Scatter With Y Error");
    sWhatsThis = "Std_Plot_Scatters_with_yerr";
    sStatusTip = QT_TR_NOOP("Scatter With Y Error");
    sPixmap = nullptr;
    eType = 0;
}

void StdScatterWithYError::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::ScatterYError));
}

bool StdScatterWithYError::isActive() { return true; }

//===========================================================================
// Std_ScatterWithXYError
//===========================================================================

DEF_STD_CMD_A(StdScatterWithXYError)

StdScatterWithXYError::StdScatterWithXYError() : Command("Std_Plot_Scatters_with_xyerr")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Scatter With XY Error");
    sToolTipText = QT_TR_NOOP("Scatter With XY Error");
    sWhatsThis = "Std_Plot_Scatters_with_xyerr";
    sStatusTip = QT_TR_NOOP("Scatter With XY Error");
    sPixmap = nullptr;
    eType = 0;
}

void StdScatterWithXYError::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::ScatterXYError));
}

bool StdScatterWithXYError::isActive() { return true; }

//======================================================================
// Std_StdScatters
//===========================================================================
//
class StdCmdScatters: public GroupCommand
{
public:
    StdCmdScatters() : GroupCommand("Std_StdScatters")
    {
        sGroup = "Alphaplot Table Tools";
        sMenuText = QT_TR_NOOP("Scatters");
        sToolTipText = QT_TR_NOOP("Create a scatter plot");
        sWhatsThis = "Std_StdScatters";
        sStatusTip = QT_TR_NOOP("Create a scatter plot");
        eType = 0;
        bCanLog = false;

        addCommand(new StdScatter());
        addCommand(new StdScatterWithXError());
        addCommand(new StdScatterWithYError());
        addCommand(new StdScatterWithXYError());

    }
    virtual const char* className() const { return "StdCmdScatters"; }
};

//===========================================================================
// Std_BoxPlot
//===========================================================================

DEF_STD_CMD_A(StdBoxPlot)

StdBoxPlot::StdBoxPlot() : Command("Std_Plot_SG_box_plot")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Box Plot");
    sToolTipText = QT_TR_NOOP("Box Plot");
    sWhatsThis = "Std_Plot_SG_box_plot";
    sStatusTip = QT_TR_NOOP("Box Plot");
    sPixmap = "Std_Plot_SG_box_plot";
    eType = 0;
}

void StdBoxPlot::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::Box));
}

bool StdBoxPlot::isActive() { return true; }

//===========================================================================
// Std_Histogram
//===========================================================================

DEF_STD_CMD_A(StdHistogram)

StdHistogram::StdHistogram() : Command("Std_Plot_SG_histogram")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Histogram");
    sToolTipText = QT_TR_NOOP("Histogram");
    sWhatsThis = "Std_Plot_SG_histogram";
    sStatusTip = QT_TR_NOOP("Histogram");
    sPixmap = "Std_Plot_SG_histogram";
    eType = 0;
}

void StdHistogram::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::Histogram));
}

bool StdHistogram::isActive() { return true; }

//===========================================================================
// Std_StackedHistogram
//===========================================================================

DEF_STD_CMD_A(StdStackedHistogram)

StdStackedHistogram::StdStackedHistogram() : Command("Std_Plot_SG_stacked_histogram")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Stacked Histogram");
    sToolTipText = QT_TR_NOOP("Stacked Histogram");
    sWhatsThis = "Std_Plot_SG_stacked_histogram";
    sStatusTip = QT_TR_NOOP("Stacked Histogram");
    // sPixmap = "stacked-histogram";
    eType = 0;
}

void StdStackedHistogram::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plotStackedHistograms();
}

bool StdStackedHistogram::isActive() { return true; }

//===========================================================================
// Std_VerticalTwoLayouts
//===========================================================================

DEF_STD_CMD_A(StdVerticalTwoLayouts)

StdVerticalTwoLayouts::StdVerticalTwoLayouts() : Command("Std_Plot_Layout_grids_vertical_2_layouts")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Vertical Two Layouts");
    sToolTipText = QT_TR_NOOP("Vertical Two Layouts");
    sWhatsThis = "Std_Plot_Layout_grids_vertical_2_layouts";
    sStatusTip = QT_TR_NOOP("Vertical Two Layouts");
    // sPixmap = "vertical-two-layouts";
    eType = 0;
}

void StdVerticalTwoLayouts::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->verticalTowLayers();
}

bool StdVerticalTwoLayouts::isActive() { return true; }
//===========================================================================
// Std_HorizontalTwoLayouts
//===========================================================================

DEF_STD_CMD_A(StdHorizontalTwoLayouts)

StdHorizontalTwoLayouts::StdHorizontalTwoLayouts() : Command("Std_Plot_Layout_grids_horizontal_2_layouts")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Horizontal Two Layouts");
    sToolTipText = QT_TR_NOOP("Horizontal Two Layouts");
    sWhatsThis = "Std_Plot_Layout_grids_horizontal_2_layouts";
    sStatusTip = QT_TR_NOOP("Horizontal Two Layouts");
    // sPixmap = "horizontal-two-layouts";
    eType = 0;
}

void StdHorizontalTwoLayouts::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->horizontalTowLayers();
}

bool StdHorizontalTwoLayouts::isActive() { return true; }

//===========================================================================
// Std_FourLayouts
//===========================================================================

DEF_STD_CMD_A(StdFourLayouts)

StdFourLayouts::StdFourLayouts() : Command("Std_Plot_Layout_grids_4_layouts")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Four Layouts");
    sToolTipText = QT_TR_NOOP("Four Layouts");
    sWhatsThis = "Std_Plot_Layout_grids_4_layouts";
    sStatusTip = QT_TR_NOOP("Four Layouts");
    // sPixmap = "four-layouts";
    eType = 0;
}

void StdFourLayouts::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->fourLayers();
}

bool StdFourLayouts::isActive() { return true; }

//===========================================================================
// Std_Line
//===========================================================================

DEF_STD_CMD_A(StdLine)

StdLine::StdLine() : Command("Std_Plot_Line")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Line");
    sToolTipText = QT_TR_NOOP("A line plot");
    sWhatsThis = "Std_Plot_Line";
    sStatusTip = QT_TR_NOOP("A line plot");
    sPixmap = "Std_Plot_Line";
    eType = 0;
}

void StdLine::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::Line));
}

bool StdLine::isActive() { return true; }

//===========================================================================
// Std_LineAndSymbol
//===========================================================================

DEF_STD_CMD_A(StdLineAndSymbol)

StdLineAndSymbol::StdLineAndSymbol() : Command("Std_Plot_LineSymbol")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Line + Symbol");
    sToolTipText = QT_TR_NOOP("A line and symbol plot");
    sWhatsThis = "Std_Plot_LineSymbol";
    sStatusTip = QT_TR_NOOP("A line and symbol plot");
    sPixmap = "Std_Plot_LineSymbol";
    eType = 0;
}

void StdLineAndSymbol::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::LineSymbols));
}

bool StdLineAndSymbol::isActive() { return true; }

//
////===========================================================================
//// Std_SpecialLineAndSymbol
////===========================================================================
//
//DEF_STD_CMD_A(StdSpecialLineAndSymbol)
//
//StdSpecialLineAndSymbol::StdSpecialLineAndSymbol() : Command("Std_Plot_Special_lineSymbol")
//{
//    sGroup = "Tools";
//    sMenuText = QT_TR_NOOP("Special Line + Symbol");
//    sToolTipText = QT_TR_NOOP("A special line and symbol plot");
//    sWhatsThis = "Std_Plot_Special_lineSymbol";
//    sStatusTip = QT_TR_NOOP("A special line and symbol plot");
//    sPixmap = "special-line-symbol-plot";
//    eType = 0;
//}
//
//void StdSpecialLineAndSymbol::activated(int iMsg)
//{
//    Q_UNUSED(iMsg);
//    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::VerticalDropLines));
//}
//
//bool StdSpecialLineAndSymbol::isActive() { return true; }

//===========================================================================
// Std_VerticalBars
//===========================================================================

DEF_STD_CMD_A(StdVerticalBars)

StdVerticalBars::StdVerticalBars() : Command("Std_Plot_Vertical_Bars")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Vertical Bars");
    sToolTipText = QT_TR_NOOP("Vertical bars plot");
    sWhatsThis = "Std_Plot_Vertical_Bars";
    sStatusTip = QT_TR_NOOP("Vertical bars plot");
    sPixmap = "Std_Plot_Vertical_Bars";
    eType = 0;
}

void StdVerticalBars::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::VerticalBars));
}

bool StdVerticalBars::isActive() { return true; }

//===========================================================================
// Std_VerticalStackedBars
//===========================================================================

DEF_STD_CMD_A(StdVerticalStackedBars)

StdVerticalStackedBars::StdVerticalStackedBars() : Command("Std_Plot_Vertical_Stacked_bars")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Vertical Stacked Bars");
    sToolTipText = QT_TR_NOOP("Vertical stacked bars plot");
    sWhatsThis = "Std_Plot_Vertical_Stacked_bars";
    sStatusTip = QT_TR_NOOP("Vertical stacked bars plot");
    sPixmap = "Std_Plot_Vertical_Stacked_bars";
    eType = 0;
}

void StdVerticalStackedBars::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::VerticalStackedBars));
}

bool StdVerticalStackedBars::isActive() { return true; }

//===========================================================================
// Std_VerticalGroupedBars
//===========================================================================

DEF_STD_CMD_A(StdVerticalGroupedBars)

StdVerticalGroupedBars::StdVerticalGroupedBars() : Command("Std_Plot_Vertical_Grouped_bars")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Vertical Grouped Bars");
    sToolTipText = QT_TR_NOOP("Vertical grouped bars plot");
    sWhatsThis = "Std_Plot_Vertical_Grouped_bars";
    sStatusTip = QT_TR_NOOP("Vertical stacked bars plot");
    sPixmap = "Std_Plot_Vertical_Grouped_bars";
    eType = 0;
}

void StdVerticalGroupedBars::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::VerticalGroupedBars));
}

bool StdVerticalGroupedBars::isActive() { return true; }

//===========================================================================
// Std_HorizontalBars
//===========================================================================

DEF_STD_CMD_A(StdHorizontalBars)

StdHorizontalBars::StdHorizontalBars() : Command("Std_Plot_Horizontal_Bars")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Horizontal Bars");
    sToolTipText = QT_TR_NOOP("Horizontal bars plot");
    sWhatsThis = "Std_Plot_Horizontal_Bars";
    sStatusTip = QT_TR_NOOP("Horizontal bars plot");
    sPixmap = "Std_Plot_Horizontal_Bars";
    eType = 0;
}

void StdHorizontalBars::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::HorizontalBars));
}

bool StdHorizontalBars::isActive() { return true; }

//===========================================================================
// Std_HorizontalStackedBars
//===========================================================================

DEF_STD_CMD_A(StdHorizontalStackedBars)

StdHorizontalStackedBars::StdHorizontalStackedBars() : Command("Std_Plot_Horizontal_Stacked_bars")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Horizontal Stacked Bars");
    sToolTipText = QT_TR_NOOP("Horizontal stacked bars plot");
    sWhatsThis = "Std_Plot_Horizontal_Stacked_bars";
    sStatusTip = QT_TR_NOOP("Horizontal stacked bars plot");
    sPixmap = "Std_Plot_Horizontal_Stacked_bars";
    eType = 0;
}

void StdHorizontalStackedBars::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::HorizontalStackedBars));
}

bool StdHorizontalStackedBars::isActive() { return true; }

//===========================================================================
// Std_HorizontalGroupedBars
//===========================================================================

DEF_STD_CMD_A(StdHorizontalGroupedBars)

StdHorizontalGroupedBars::StdHorizontalGroupedBars() : Command("Std_Plot_Horizontal_Grouped_bars")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Horizontal Grouped Bars");
    sToolTipText = QT_TR_NOOP("Horizontal grouped bars plot");
    sWhatsThis = "Std_Plot_Horizontal_Grouped_bars";
    sStatusTip = QT_TR_NOOP("Horizontal grouped bars plot");
    sPixmap = "Std_Plot_Horizontal_Grouped_bars";
    eType = 0;
}

void StdHorizontalGroupedBars::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::HorizontalGroupedBars));
}

bool StdHorizontalGroupedBars::isActive() { return hasActiveDocument(); }

//===========================================================================
// Std_Area
//===========================================================================

DEF_STD_CMD_A(StdArea)

StdArea::StdArea() : Command("Std_Plot_Area")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Area");
    sToolTipText = QT_TR_NOOP("Area plot");
    sWhatsThis = "Std_Plot_Area";
    sStatusTip = QT_TR_NOOP("Area plot");
    sPixmap = "Std_Plot_Area";
    eType = 0;
}

void StdArea::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::Area));
}

bool StdArea::isActive() { return true; }

//===========================================================================
// Std_ChannelFill
//===========================================================================

DEF_STD_CMD_A(StdChannelFill)

StdChannelFill::StdChannelFill() : Command("Std_Plot_Channel_fil")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Channel Fill");
    sToolTipText = QT_TR_NOOP("Channel fill plot");
    sWhatsThis = "Std_Plot_Channel_fil";
    sStatusTip = QT_TR_NOOP("Channel fill plot");
    sPixmap = "Std_Plot_Channel_fil";
    eType = 0;
}

void StdChannelFill::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::Channel));
}

bool StdChannelFill::isActive() { return true; }

//===========================================================================
// Std_Pie
//===========================================================================

DEF_STD_CMD_A(StdPie)

StdPie::StdPie() : Command("Std_Plot_Pie")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Pie");
    sToolTipText = QT_TR_NOOP("Pie plot");
    sWhatsThis = "Std_Plot_Pie";
    sStatusTip = QT_TR_NOOP("Pie plot");
    sPixmap = "Std_Plot_Pie";
    eType = 0;
}

void StdPie::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plotPie(Graph2DCommon::PieStyle::Pie);
}

bool StdPie::isActive() { return true; }

//===========================================================================
// Std_HalfPie
//===========================================================================

DEF_STD_CMD_A(StdHalfPie)

StdHalfPie::StdHalfPie() : Command("Std_Plot_Half_pie")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Half Pie");
    sToolTipText = QT_TR_NOOP("Half pie plot");
    sWhatsThis = "Std_Plot_Half_pie";
    sStatusTip = QT_TR_NOOP("Half pie plot");
    sPixmap = "Std_Plot_Half_pie";
    eType = 0;
}

void StdHalfPie::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plotPie(Graph2DCommon::PieStyle::HalfPie);
}

bool StdHalfPie::isActive() { return true; }

//===========================================================================
// Std_VectorsXYXY
//===========================================================================

DEF_STD_CMD_A(StdVectorsXYXY)

StdVectorsXYXY::StdVectorsXYXY() : Command("Std_Plot_Vectors_XYXY")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Vectors XYXY");
    sToolTipText = QT_TR_NOOP("Vectors XYXY plot");
    sWhatsThis = "Std_Plot_Vectors_XYXY";
    sStatusTip = QT_TR_NOOP("Vectors XYXY plot");
    sPixmap = "Std_Plot_Vectors_XYXY";
    eType = 0;
}

void StdVectorsXYXY::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plotVectXYXY();
}

bool StdVectorsXYXY::isActive() { return true; }

//===========================================================================
// Std_VectorsXYAM
//===========================================================================

DEF_STD_CMD_A(StdVectorsXYAM)

StdVectorsXYAM::StdVectorsXYAM() : Command("Std_Plot_Vectors_XYAM")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Vectors XYAM");
    sToolTipText = QT_TR_NOOP("Vectors XYAM plot");
    sWhatsThis = "Std_Plot_Vectors_XYAM";
    sStatusTip = QT_TR_NOOP("Vectors XYAM plot");
    sPixmap = "Std_Plot_Vectors_XYAM";
    eType = 0;
}

void StdVectorsXYAM::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plotVectXYAM();
}

bool StdVectorsXYAM::isActive() { return true; }

//===========================================================================
// Std_3DWireFrame
//===========================================================================

DEF_STD_CMD_A(Std3DWireFrame)

Std3DWireFrame::Std3DWireFrame() : Command("Std_3DPlot_3D_Wire_frame")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("3D Wire Frame");
    sToolTipText = QT_TR_NOOP("3D wire frame plot");
    sWhatsThis = "Std_3DPlot_3D_Wire_frame";
    sStatusTip = QT_TR_NOOP("3D wire frame plot");
    sPixmap = "Std_3DPlot_3D_Wire_frame";
    eType = 0;
}

void Std3DWireFrame::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->treeDWireFrame();
}

bool Std3DWireFrame::isActive() { return true; }

//===========================================================================
// Std_3DSurface
//===========================================================================

DEF_STD_CMD_A(Std3DSurface)

Std3DSurface::Std3DSurface() : Command("Std_3DPlot_3D_Surface")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("3D Surface");
    sToolTipText = QT_TR_NOOP("3D surface plot");
    sWhatsThis = "Std_3DPlot_3D_Surface";
    sStatusTip = QT_TR_NOOP("3D surface plot");
    sPixmap = "Std_3DPlot_3D_Surface";
    eType = 0;
}

void Std3DSurface::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->treeDSurface();
}

bool Std3DSurface::isActive() { return true; }

//===========================================================================
// Std_3DWireFrameSurface
//===========================================================================

DEF_STD_CMD_A(Std3DWireFrameSurface)

Std3DWireFrameSurface::Std3DWireFrameSurface() : Command("Std_3DPlot_3D_Wire_frame_surface")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("3D wire frame Surface");
    sToolTipText = QT_TR_NOOP("3D surface plot");
    sWhatsThis = "Std_3DPlot_3D_Wire_frame_surface";
    sStatusTip = QT_TR_NOOP("3D surface plot");
    sPixmap = "Std_3DPlot_3D_Wire_frame_surface";
    eType = 0;
}

void Std3DWireFrameSurface::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->treeDWireSurface();
}

bool Std3DWireFrameSurface::isActive() { return true; }

//===========================================================================
// Std_Bar
//===========================================================================

DEF_STD_CMD_A(Std3DPlotBar)

Std3DPlotBar::Std3DPlotBar() : Command("Std_3DPlot_Bar")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Bar");
    sToolTipText = QT_TR_NOOP("Bar plot");
    sWhatsThis = "Std_Bar";
    sStatusTip = QT_TR_NOOP("Bar plot");
    sPixmap = "Std_3DPlot_Bar";
    eType = 0;
}

void Std3DPlotBar::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plot3DBars();
}

bool Std3DPlotBar::isActive() { return true; }

//===========================================================================
// Std_3DScatter
//===========================================================================

DEF_STD_CMD_A(Std3DPlotScatter)

Std3DPlotScatter::Std3DPlotScatter() : Command("Std_3DPlot_Scatter")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Scatter");
    sToolTipText = QT_TR_NOOP("3D Scatter plot");
    sWhatsThis = "Std_3DScatter";
    sStatusTip = QT_TR_NOOP("3D Scatter plot");
    sPixmap = "Std_Plot_3D_plot_scatter";
    eType = 0;
}

void Std3DPlotScatter::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plot3DScatter();
}

bool Std3DPlotScatter::isActive() { return true; }

//===========================================================================
// Std_ContourAndColourFill
//===========================================================================

DEF_STD_CMD_A(StdContourAndColourFill)

StdContourAndColourFill::StdContourAndColourFill() : Command("Std_3DPlot_Countour_color_fill")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Contour/Colour Fill");
    sToolTipText = QT_TR_NOOP("Contour and colour fill plot");
    sWhatsThis = "Std_3DPlot_Countour_color_fill";
    sStatusTip = QT_TR_NOOP("Contour and colour fill plot");
    sPixmap = "Std_3DPlot_Countour_color_fill";
    eType = 0;
}

void StdContourAndColourFill::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plotColorMap();
}

bool StdContourAndColourFill::isActive() { return true; }

//===========================================================================
// Std_ContourLines
//===========================================================================

DEF_STD_CMD_A(StdContourLines)

StdContourLines::StdContourLines() : Command("Std_3DPlot_Countour_lines")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Contour Lines");
    sToolTipText = QT_TR_NOOP("Contour lines plot");
    sWhatsThis = "Std_3DPlot_Countour_lines";
    sStatusTip = QT_TR_NOOP("Contour lines plot");
    sPixmap = "Std_3DPlot_Countour_lines";
    eType = 0;
}

void StdContourLines::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plotContour();
}

bool StdContourLines::isActive() { return true; }

//===========================================================================
// Std_GrayScaleMap
//===========================================================================

DEF_STD_CMD_A(StdGrayScaleMap)

StdGrayScaleMap::StdGrayScaleMap() : Command("Std_3DPlot_Gray_scale_map")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Gray Scale Map");
    sToolTipText = QT_TR_NOOP("Gray scale map plot");
    sWhatsThis = "Std_3DPlot_Gray_scale_map";
    sStatusTip = QT_TR_NOOP("Gray scale map plot");
    sPixmap = "Std_3DPlot_Gray_scale_map";
    eType = 0;
}

void StdGrayScaleMap::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->plotGrayScale();
}

bool StdGrayScaleMap::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotPlot3dModecolumnSelect
//===========================================================================

DEF_STD_CMD_A(StdPlotPlot3dModecolumnSelect)

StdPlotPlot3dModecolumnSelect::StdPlotPlot3dModecolumnSelect()
    : Command("Std_PlotPlot3dModecolumnSelect")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Column Select");
    sToolTipText = QT_TR_NOOP("Column select");
    sWhatsThis = "Std_PlotPlot3dModecolumnSelect";
    sStatusTip = QT_TR_NOOP("Column select");
    sPixmap = "Std_Plot3d_ColumnSelect";
    eType = 0;
}

void StdPlotPlot3dModecolumnSelect::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickSelectionType(this->getAction()->action());
}

bool StdPlotPlot3dModecolumnSelect::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotPlot3dModeRowSelect
//===========================================================================

DEF_STD_CMD_A(StdPlotPlot3dModeRowSelect)

StdPlotPlot3dModeRowSelect::StdPlotPlot3dModeRowSelect() : Command("Std_PlotPlot3dModeRowSelect")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Row Select");
    sToolTipText = QT_TR_NOOP("Row select");
    sWhatsThis = "Std_PlotPlot3dModeRowSelect";
    sStatusTip = QT_TR_NOOP("Row select");
    sPixmap = "Std_Plot3d_RowSelect";
    eType = 0;
}

void StdPlotPlot3dModeRowSelect::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickSelectionType(this->getAction()->action());
}

bool StdPlotPlot3dModeRowSelect::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotPlot3dModeItemSelect
//===========================================================================

DEF_STD_CMD_A(StdPlotPlot3dModeItemSelect)

StdPlotPlot3dModeItemSelect::StdPlotPlot3dModeItemSelect() : Command("Std_PlotPlot3dModeItemSelect")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Item Select");
    sToolTipText = QT_TR_NOOP("Point select");
    sWhatsThis = "Std_PlotPlot3dModeItemSelect";
    sStatusTip = QT_TR_NOOP("Point select");
    sPixmap = "Std_Plot3d_PointSelect";
    eType = 0;
}

void StdPlotPlot3dModeItemSelect::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickSelectionType(this->getAction()->action());
}

bool StdPlotPlot3dModeItemSelect::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotPlot3dModeNoneSelect
//===========================================================================

DEF_STD_CMD_A(StdPlotPlot3dModeNoneSelect)

StdPlotPlot3dModeNoneSelect::StdPlotPlot3dModeNoneSelect() : Command("Std_PlotPlot3dModeNoneSelect")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("No Selection");
    sToolTipText = QT_TR_NOOP("No selection");
    sWhatsThis = "Std_PlotPlot3dModeNoneSelect";
    sStatusTip = QT_TR_NOOP("No selection");
    sPixmap = "no-selection";
    eType = 0;
}

void StdPlotPlot3dModeNoneSelect::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickSelectionType(this->getAction()->action());
}

bool StdPlotPlot3dModeNoneSelect::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotPlot3dAnimate
//===========================================================================

DEF_STD_CMD_A(StdPlotPlot3dAnimate)

StdPlotPlot3dAnimate::StdPlotPlot3dAnimate() : Command("Std_PlotPlot3dAnimate")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Animate");
    sToolTipText = QT_TR_NOOP("Plot 3D animate");
    sWhatsThis = "Std_PlotPlot3dAnimate";
    sStatusTip = QT_TR_NOOP("Plot 3D animate");
    sPixmap = "Std_Plot_3D_animate";
    eType = 0;
}

void StdPlotPlot3dAnimate::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->toggle3DAnimation();
}

bool StdPlotPlot3dAnimate::isActive() { return true; }

//======================================================================
// Std_3DSurfaceTools
//===========================================================================
//
class Std3DSurfaceTools: public GroupCommand
{
public:
    Std3DSurfaceTools() : GroupCommand("Std_3DSurfaceTools")
    {
        sGroup = "Alphaplot Table Tools";
        sMenuText = QT_TR_NOOP("3D Surface Tools");
        sToolTipText = QT_TR_NOOP("3D Surface Tools");
        sWhatsThis = "Std_3DSurfaceTools";
        sStatusTip = QT_TR_NOOP("3D Surface Tools");
        eType = 0;
        bCanLog = false;

        addCommand(new Std3DWireFrame());
        addCommand(new Std3DSurface());
        addCommand(new Std3DWireFrameSurface());
        addCommand(new Std3DPlotBar());
        addCommand(new Std3DPlotScatter());
        addCommand(new StdContourAndColourFill());
        addCommand(new StdContourLines());
        addCommand(new StdGrayScaleMap());
        addCommand(new StdPlotPlot3dModecolumnSelect());
        addCommand(new StdPlotPlot3dModeRowSelect());
        addCommand(new StdPlotPlot3dModeItemSelect());
        // addCommand(new StdPlotPlot3dModeNoneSelect());
        addCommand(new StdPlotPlot3dAnimate());
     
    }
    virtual const char* className() const { return "Std3DSurfaceTools"; }
};

//===========================================================================
// Std_3DWireFramePolar
//===========================================================================

DEF_STD_CMD_A(Std3DWireFramePolar)

Std3DWireFramePolar::Std3DWireFramePolar() : Command("Std_3DPlot_3D_Wire_frame_polar")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("3D Wire Frame Polar");
    sToolTipText = QT_TR_NOOP("3D wire frame polar plot");
    sWhatsThis = "Std_3DPlot_3D_Wire_frame_polar";
    sStatusTip = QT_TR_NOOP("3D wire frame polar plot");
    sPixmap = nullptr;
    eType = 0;
}

void Std3DWireFramePolar::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->treeDWireFramePolar();
}

bool Std3DWireFramePolar::isActive() { return true; }

//===========================================================================
// Std_3DWireSurfacePolar
//===========================================================================

DEF_STD_CMD_A(Std3DWireSurfacePolar)

Std3DWireSurfacePolar::Std3DWireSurfacePolar() : Command("Std_3DPlot_3D_Surface_polar")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("3D Wire Surface Polar");
    sToolTipText = QT_TR_NOOP("3D wire surface polar plot");
    sWhatsThis = "Std_3DPlot_3D_Surface_polar";
    sStatusTip = QT_TR_NOOP("3D wire surface polar plot");
    sPixmap = nullptr;
    eType = 0;
}

void Std3DWireSurfacePolar::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->treeDSurfacePolar();
}

bool Std3DWireSurfacePolar::isActive() { return true; }

//===========================================================================
// Std_3DWireFrameSurfacePolar
//===========================================================================

DEF_STD_CMD_A(Std3DWireFrameSurfacePolar)

Std3DWireFrameSurfacePolar::Std3DWireFrameSurfacePolar() : Command("Std_3DPlot_3D_Wire_frame_surface_polar")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("3D Wire Frame Surface Polar");
    sToolTipText = QT_TR_NOOP("3D wire frame surface polar plot");
    sWhatsThis = "Std_3DPlot_3D_Wire_frame_surface_polar";
    sStatusTip = QT_TR_NOOP("3D wire frame surface polar plot");
    sPixmap = nullptr;
    eType = 0;
}

void Std3DWireFrameSurfacePolar::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->treeDWireFrameSurfacePolar();
}

bool Std3DWireFrameSurfacePolar::isActive() { return true; }

//===========================================================================
// Std_3DScatterPolar
//===========================================================================

DEF_STD_CMD_A(Std3DScatterPolar)

Std3DScatterPolar::Std3DScatterPolar() : Command("Std_3DPlot_3D_Scatter_polar")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("3D Scatter Polar");
    sToolTipText = QT_TR_NOOP("3D scatter polar plot");
    sWhatsThis = "Std_3DPlot_3D_Scatter_polar";
    sStatusTip = QT_TR_NOOP("3D scatter polar plot");
    sPixmap = nullptr;
    eType = 0;
}

void Std3DScatterPolar::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->treeDScatterPolar();
}

bool Std3DScatterPolar::isActive() { return true; }

//===========================================================================
// Std_PolarSpectogram
//===========================================================================

DEF_STD_CMD_A(StdPolarSpectogram)

StdPolarSpectogram::StdPolarSpectogram() : Command("Std_3DPlot_Polar_spectrogram")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Polar Spectogram");
    sToolTipText = QT_TR_NOOP("Polar spectogram plot");
    sWhatsThis = "Std_3DPlot_Polar_spectrogram";
    sStatusTip = QT_TR_NOOP("Polar spectogram plot");
    sPixmap = nullptr;
    eType = 0;
}

void StdPolarSpectogram::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->treeDPolarSpectrogram();
}

bool StdPolarSpectogram::isActive() { return true; }

//===========================================================================
// Std_AddRemovePlotY
//===========================================================================

DEF_STD_CMD_A(StdAddRemovePlotY)

StdAddRemovePlotY::StdAddRemovePlotY() : Command("Std_Graph_AddRemove_other_plots_y")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add/Remove Plot Y...");
    sToolTipText = QT_TR_NOOP("Add or remove plot Y");
    sWhatsThis = "Std_Graph_AddRemove_other_plots_y";
    sStatusTip = QT_TR_NOOP("Add or remove plot Y");
    sPixmap = "Std_Graph_AddRemove_plot_xyxyy";
    eType = 0;
}

void StdAddRemovePlotY::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->showCurvesDialog(this->getAction()->action());
}

bool StdAddRemovePlotY::isActive() { return true; }

//===========================================================================
// Std_AddRemoveVectorPlot
//===========================================================================

DEF_STD_CMD_A(StdAddRemoveVectorPlot)

StdAddRemoveVectorPlot::StdAddRemoveVectorPlot() : Command("Std_Graph_AddRemove_other_plots_vector")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add/Remove Vector Plot...");
    sToolTipText = QT_TR_NOOP("Add or remove vector plot");
    sWhatsThis = "Std_Graph_AddRemove_other_plots_vector";
    sStatusTip = QT_TR_NOOP("Add or remove vector plot");
    // sPixmap = "add-remove-vector-plot";
    eType = 0;
}

void StdAddRemoveVectorPlot::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->showCurvesDialog(this->getAction()->action());
}

bool StdAddRemoveVectorPlot::isActive() { return true; }

//===========================================================================
// Std_AddLeftAxisValue
//===========================================================================

DEF_STD_CMD_A(StdAddLeftAxisValue)

StdAddLeftAxisValue::StdAddLeftAxisValue() : Command("Std_AddLeftAxisValue")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Value");
    sToolTipText = QT_TR_NOOP("Add left axis value");
    sWhatsThis = "Std_AddLeftAxisValue";
    sStatusTip = QT_TR_NOOP("Add left axis value");
    sPixmap = "graph2d-axis-left-value";
    eType = 0;
}

void StdAddLeftAxisValue::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddLeftAxisValue::isActive() { return true; }

//===========================================================================
// Std_AddLeftAxisLog
//===========================================================================

DEF_STD_CMD_A(StdAddLeftAxisLog)

StdAddLeftAxisLog::StdAddLeftAxisLog() : Command("Std_AddLeftAxisLog")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Log");
    sToolTipText = QT_TR_NOOP("Add left axis log");
    sWhatsThis = "Std_AddLeftAxisLog";
    sStatusTip = QT_TR_NOOP("Add left axis log");
    sPixmap = "graph2d-axis-left-log";
    eType = 0;
}

void StdAddLeftAxisLog::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddLeftAxisLog::isActive() { return true; }

//===========================================================================
// Std_AddLeftAxisPi
//===========================================================================

DEF_STD_CMD_A(StdAddLeftAxisPi)

StdAddLeftAxisPi::StdAddLeftAxisPi() : Command("Std_AddLeftAxisPi")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Pi");
    sToolTipText = QT_TR_NOOP("Add left axis pi");
    sWhatsThis = "Std_AddLeftAxisPi";
    sStatusTip = QT_TR_NOOP("Add left axis pi");
    sPixmap = "graph2d-axis-left-symbol";
    eType = 0;
}

void StdAddLeftAxisPi::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddLeftAxisPi::isActive() { return true; }

//===========================================================================
// Std_AddLeftAxisText
//===========================================================================

DEF_STD_CMD_A(StdAddLeftAxisText)

StdAddLeftAxisText::StdAddLeftAxisText() : Command("Std_AddLeftAxisText")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Text");
    sToolTipText = QT_TR_NOOP("Add left axis text");
    sWhatsThis = "Std_AddLeftAxisText";
    sStatusTip = QT_TR_NOOP("Add left axis text");
    sPixmap = "graph2d-axis-left-text";
    eType = 0;
}

void StdAddLeftAxisText::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddLeftAxisText::isActive() { return true; }

//===========================================================================
// Std_AddLeftAxisTime
//===========================================================================

DEF_STD_CMD_A(StdAddLeftAxisTime)

StdAddLeftAxisTime::StdAddLeftAxisTime() : Command("Std_AddLeftAxisTime")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Time");
    sToolTipText = QT_TR_NOOP("Add left axis time");
    sWhatsThis = "Std_AddLeftAxisTime";
    sStatusTip = QT_TR_NOOP("Add left axis time");
    sPixmap = "graph2d-axis-left-time";
    eType = 0;
}

void StdAddLeftAxisTime::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddLeftAxisTime::isActive() { return true; }

//===========================================================================
// Std_AddLeftAxisDateTime
//===========================================================================

DEF_STD_CMD_A(StdAddLeftAxisDateTime)

StdAddLeftAxisDateTime::StdAddLeftAxisDateTime() : Command("Std_AddLeftAxisDateTime")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Date Time");
    sToolTipText = QT_TR_NOOP("Add left axis date time");
    sWhatsThis = "Std_AddLeftAxisDateTime";
    sStatusTip = QT_TR_NOOP("Add left axis date time");
    sPixmap = "graph2d-axis-left-datetime";
    eType = 0;
}

void StdAddLeftAxisDateTime::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddLeftAxisDateTime::isActive() { return true; }
///////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_AddBottomAxisValue
//===========================================================================

DEF_STD_CMD_A(StdAddBottomAxisValue)

StdAddBottomAxisValue::StdAddBottomAxisValue() : Command("Std_AddBottomAxisValue")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Value");
    sToolTipText = QT_TR_NOOP("Add bottom axis value");
    sWhatsThis = "Std_AddBottomAxisValue";
    sStatusTip = QT_TR_NOOP("Add bottom axis value");
    sPixmap = "graph2d-axis-bottom-value";
    eType = 0;
}

void StdAddBottomAxisValue::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddBottomAxisValue::isActive() { return true; }

//===========================================================================
// Std_AddBottomAxisLog
//===========================================================================

DEF_STD_CMD_A(StdAddBottomAxisLog)

StdAddBottomAxisLog::StdAddBottomAxisLog() : Command("Std_AddBottomAxisLog")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Log");
    sToolTipText = QT_TR_NOOP("Add bottom axis log");
    sWhatsThis = "Std_AddBottomAxisLog";
    sStatusTip = QT_TR_NOOP("Add bottom axis log");
    sPixmap = "graph2d-axis-bottom-log";
    eType = 0;
}

void StdAddBottomAxisLog::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddBottomAxisLog::isActive() { return true; }

//===========================================================================
// Std_AddBottomAxisPi
//===========================================================================

DEF_STD_CMD_A(StdAddBottomAxisPi)

StdAddBottomAxisPi::StdAddBottomAxisPi() : Command("Std_AddBottomAxisPi")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Pi");
    sToolTipText = QT_TR_NOOP("Add bottom axis pi");
    sWhatsThis = "Std_AddBottomAxisPi";
    sStatusTip = QT_TR_NOOP("Add bottom axis pi");
    sPixmap = "graph2d-axis-bottom-symbol";
    eType = 0;
}

void StdAddBottomAxisPi::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddBottomAxisPi::isActive() { return true; }

//===========================================================================
// Std_AddBottomAxisText
//===========================================================================

DEF_STD_CMD_A(StdAddBottomAxisText)

StdAddBottomAxisText::StdAddBottomAxisText() : Command("Std_AddBottomAxisText")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Text");
    sToolTipText = QT_TR_NOOP("Add bottom axis text");
    sWhatsThis = "Std_AddBottomAxisText";
    sStatusTip = QT_TR_NOOP("Add bottom axis text");
    sPixmap = "graph2d-axis-bottom-text";
    eType = 0;
}

void StdAddBottomAxisText::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddBottomAxisText::isActive() { return true; }

//===========================================================================
// Std_AddBottomAxisTime
//===========================================================================

DEF_STD_CMD_A(StdAddBottomAxisTime)

StdAddBottomAxisTime::StdAddBottomAxisTime() : Command("Std_AddBottomAxisTime")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Time");
    sToolTipText = QT_TR_NOOP("Add bottom axis time");
    sWhatsThis = "Std_AddBottomAxisTime";
    sStatusTip = QT_TR_NOOP("Add bottom axis time");
    sPixmap = "graph2d-axis-bottom-time";
    eType = 0;
}

void StdAddBottomAxisTime::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddBottomAxisTime::isActive() { return true; }

//===========================================================================
// Std_AddBottomAxisDateTime
//===========================================================================

DEF_STD_CMD_A(StdAddBottomAxisDateTime)

StdAddBottomAxisDateTime::StdAddBottomAxisDateTime() : Command("Std_AddBottomAxisDateTime")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Date Time");
    sToolTipText = QT_TR_NOOP("Add bottom axis date time");
    sWhatsThis = "Std_AddBottomAxisDateTime";
    sStatusTip = QT_TR_NOOP("Add bottom axis date time");
    sPixmap = "graph2d-axis-bottom-datetime";
    eType = 0;
}

void StdAddBottomAxisDateTime::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddBottomAxisDateTime::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_AddRightAxisValue
//===========================================================================

DEF_STD_CMD_A(StdAddRightAxisValue)

StdAddRightAxisValue::StdAddRightAxisValue() : Command("Std_AddRightAxisValue")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Value");
    sToolTipText = QT_TR_NOOP("Add right axis value");
    sWhatsThis = "Std_AddRightAxisValue";
    sStatusTip = QT_TR_NOOP("Add right axis value");
    sPixmap = "graph2d-axis-right-value";
    eType = 0;
}

void StdAddRightAxisValue::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddRightAxisValue::isActive() { return true; }

//===========================================================================
// Std_AddRightAxisLog
//===========================================================================

DEF_STD_CMD_A(StdAddRightAxisLog)

StdAddRightAxisLog::StdAddRightAxisLog() : Command("Std_AddRightAxisLog")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Log");
    sToolTipText = QT_TR_NOOP("Add right axis log");
    sWhatsThis = "Std_AddRightAxisLog";
    sStatusTip = QT_TR_NOOP("Add right axis log");
    sPixmap = "graph2d-axis-right-log";
    eType = 0;
}

void StdAddRightAxisLog::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddRightAxisLog::isActive() { return true; }

//===========================================================================
// Std_AddRightAxisPi
//===========================================================================

DEF_STD_CMD_A(StdAddRightAxisPi)

StdAddRightAxisPi::StdAddRightAxisPi() : Command("Std_AddRightAxisPi")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Pi");
    sToolTipText = QT_TR_NOOP("Add right axis pi");
    sWhatsThis = "Std_AddRightAxisPi";
    sStatusTip = QT_TR_NOOP("Add right axis pi");
    sPixmap = "graph2d-axis-right-symbol";
    eType = 0;
}

void StdAddRightAxisPi::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddRightAxisPi::isActive() { return true; }

//===========================================================================
// Std_AddRightAxisText
//===========================================================================

DEF_STD_CMD_A(StdAddRightAxisText)

StdAddRightAxisText::StdAddRightAxisText() : Command("Std_AddRightAxisText")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Text");
    sToolTipText = QT_TR_NOOP("Add right axis text");
    sWhatsThis = "Std_AddRightAxisText";
    sStatusTip = QT_TR_NOOP("Add right axis text");
    sPixmap = "graph2d-axis-right-text";
    eType = 0;
}

void StdAddRightAxisText::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddRightAxisText::isActive() { return true; }

//===========================================================================
// Std_AddRightAxisTime
//===========================================================================

DEF_STD_CMD_A(StdAddRightAxisTime)

StdAddRightAxisTime::StdAddRightAxisTime() : Command("Std_AddRightAxisTime")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Time");
    sToolTipText = QT_TR_NOOP("Add right axis time");
    sWhatsThis = "Std_AddRightAxisTime";
    sStatusTip = QT_TR_NOOP("Add right axis time");
    sPixmap = "graph2d-axis-right-time";
    eType = 0;
}

void StdAddRightAxisTime::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddRightAxisTime::isActive() { return true; }

//===========================================================================
// Std_AddRightAxisDateTime
//===========================================================================

DEF_STD_CMD_A(StdAddRightAxisDateTime)

StdAddRightAxisDateTime::StdAddRightAxisDateTime() : Command("Std_AddRightAxisDateTime")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Date Time");
    sToolTipText = QT_TR_NOOP("Add right axis date time");
    sWhatsThis = "Std_AddRightAxisDateTime";
    sStatusTip = QT_TR_NOOP("Add right axis date time");
    sPixmap = "graph2d-axis-right-datetime";
    eType = 0;
}

void StdAddRightAxisDateTime::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddRightAxisDateTime::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_AddTopAxisValue
//===========================================================================

DEF_STD_CMD_A(StdAddTopAxisValue)

StdAddTopAxisValue::StdAddTopAxisValue() : Command("Std_AddTopAxisValue")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Value");
    sToolTipText = QT_TR_NOOP("Add top axis value");
    sWhatsThis = "Std_AddTopAxisValue";
    sStatusTip = QT_TR_NOOP("Add top axis value");
    sPixmap = "graph2d-axis-top-value";
    eType = 0;
}

void StdAddTopAxisValue::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddTopAxisValue::isActive() { return true; }

//===========================================================================
// Std_AddTopAxisLog
//===========================================================================

DEF_STD_CMD_A(StdAddTopAxisLog)

StdAddTopAxisLog::StdAddTopAxisLog() : Command("Std_AddTopAxisLog")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Log");
    sToolTipText = QT_TR_NOOP("Add top axis log");
    sWhatsThis = "Std_AddTopAxisLog";
    sStatusTip = QT_TR_NOOP("Add top axis log");
    sPixmap = "graph2d-axis-top-log";
    eType = 0;
}

void StdAddTopAxisLog::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddTopAxisLog::isActive() { return true; }

//===========================================================================
// Std_AddTopAxisPi
//===========================================================================

DEF_STD_CMD_A(StdAddTopAxisPi)

StdAddTopAxisPi::StdAddTopAxisPi() : Command("Std_AddTopAxisPi")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Pi");
    sToolTipText = QT_TR_NOOP("Add top axis pi");
    sWhatsThis = "Std_AddTopAxisPi";
    sStatusTip = QT_TR_NOOP("Add top axis pi");
    sPixmap = "graph2d-axis-top-symbol";
    eType = 0;
}

void StdAddTopAxisPi::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddTopAxisPi::isActive() { return true; }

//===========================================================================
// Std_AddTopAxisText
//===========================================================================

DEF_STD_CMD_A(StdAddTopAxisText)

StdAddTopAxisText::StdAddTopAxisText() : Command("Std_AddTopAxisText")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Text");
    sToolTipText = QT_TR_NOOP("Add top axis text");
    sWhatsThis = "Std_AddTopAxisText";
    sStatusTip = QT_TR_NOOP("Add top axis text");
    sPixmap = "graph2d-axis-top-text";
    eType = 0;
}

void StdAddTopAxisText::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddTopAxisText::isActive() { return true; }

//===========================================================================
// Std_AddTopAxisTime
//===========================================================================

DEF_STD_CMD_A(StdAddTopAxisTime)

StdAddTopAxisTime::StdAddTopAxisTime() : Command("Std_AddTopAxisTime")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Time");
    sToolTipText = QT_TR_NOOP("Add top axis time");
    sWhatsThis = "Std_AddTopAxisTime";
    sStatusTip = QT_TR_NOOP("Add top axis time");
    sPixmap = "graph2d-axis-top-time";
    eType = 0;
}

void StdAddTopAxisTime::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddTopAxisTime::isActive() { return true; }

//===========================================================================
// Std_AddTopAxisDateTime
//===========================================================================

DEF_STD_CMD_A(StdAddTopAxisDateTime)

StdAddTopAxisDateTime::StdAddTopAxisDateTime() : Command("Std_AddTopAxisDateTime")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Date Time");
    sToolTipText = QT_TR_NOOP("Add top axis date time");
    sWhatsThis = "Std_AddTopAxisDateTime";
    sStatusTip = QT_TR_NOOP("Add top axis date time");
    sPixmap = "graph2d-axis-top-datetime";
    eType = 0;
}

void StdAddTopAxisDateTime::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addGraph2DAxis(this->getAction()->action());
}

bool StdAddTopAxisDateTime::isActive() { return true; }

//===========================================================================
// Std_AddLayoutUp
//===========================================================================

DEF_STD_CMD_A(StdAddLayoutUp)

StdAddLayoutUp::StdAddLayoutUp() : Command("Std_Graph_Add_layout_up")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Layout Up");
    sToolTipText = QT_TR_NOOP("Add layout up");
    sWhatsThis = "Std_Graph_Add_layout_up";
    sStatusTip = QT_TR_NOOP("Add layout up");
    sPixmap = "Std_Graph_Add_layout_up";
    eType = 0;
}

void StdAddLayoutUp::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addLayout(Graph2DCommon::AddLayoutElement::Top);
}

bool StdAddLayoutUp::isActive() { return true; }

//===========================================================================
// Std_AddLayoutDown
//===========================================================================

DEF_STD_CMD_A(StdAddLayoutDown)

StdAddLayoutDown::StdAddLayoutDown() : Command("Std_Graph_Add_layout_down")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Layout Down");
    sToolTipText = QT_TR_NOOP("Add layout down");
    sWhatsThis = "Std_Graph_Add_layout_down";
    sStatusTip = QT_TR_NOOP("Add layout down");
    sPixmap = "Std_Graph_Add_layout_down";
    eType = 0;
}

void StdAddLayoutDown::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addLayout(Graph2DCommon::AddLayoutElement::Bottom);
}

bool StdAddLayoutDown::isActive() { return true; }

//===========================================================================
// Std_AddLayoutLeft
//===========================================================================

DEF_STD_CMD_A(StdAddLayoutLeft)

StdAddLayoutLeft::StdAddLayoutLeft() : Command("Std_Graph_Add_layout_left")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Layout Left");
    sToolTipText = QT_TR_NOOP("Add layout left");
    sWhatsThis = "Std_Graph_Add_layout_left";
    sStatusTip = QT_TR_NOOP("Add layout left");
    sPixmap = "Std_Graph_Add_layout_left";
    eType = 0;
}

void StdAddLayoutLeft::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addLayout(Graph2DCommon::AddLayoutElement::Left);
}

bool StdAddLayoutLeft::isActive() { return true; }

//===========================================================================
// Std_AddLayoutRight
//===========================================================================

DEF_STD_CMD_A(StdAddLayoutRight)

StdAddLayoutRight::StdAddLayoutRight() : Command("Std_Graph_Add_layout_right")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Layout Right");
    sToolTipText = QT_TR_NOOP("Add layout right");
    sWhatsThis = "Std_Graph_Add_layout_right";
    sStatusTip = QT_TR_NOOP("Add layout right");
    sPixmap = "Std_Graph_Add_layout_right";
    eType = 0;
}

void StdAddLayoutRight::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addLayout(Graph2DCommon::AddLayoutElement::Right);
}

bool StdAddLayoutRight::isActive() { return true; }

//===========================================================================
// Std_AddRemovePlotXYAndXYY
//===========================================================================

DEF_STD_CMD_A(StdAddRemovePlotXYAndXYY)

StdAddRemovePlotXYAndXYY::StdAddRemovePlotXYAndXYY() : Command("Std_Graph_AddRemove_plot_xyxyy")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add/Remove Plot XY/XYY...");
    sToolTipText = QT_TR_NOOP("Add/remove plot xy/xyy");
    sWhatsThis = "Std_Graph_AddRemove_plot_xyxyy";
    sStatusTip = QT_TR_NOOP("Add/remove plot xy/xyy");
    sPixmap = "Std_Graph_AddRemove_plot_xyxyy";
    eType = 0;
}

void StdAddRemovePlotXYAndXYY::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->showCurvesDialog(this->getAction()->action());
}

bool StdAddRemovePlotXYAndXYY::isActive() { return true; }

//===========================================================================
// Std_AddFunction
//===========================================================================

DEF_STD_CMD_A(StdAddFunction)

StdAddFunction::StdAddFunction() : Command("Std_Graph_Add_function")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Function");
    sToolTipText = QT_TR_NOOP("Add function");
    sWhatsThis = "Std_Graph_Add_function";
    sStatusTip = QT_TR_NOOP("Add function");
    sPixmap = "Std_Graph_Add_function";
    eType = 0;
}

void StdAddFunction::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addFunctionCurve();
}

bool StdAddFunction::isActive() { return true; }

//===========================================================================
// Std_AddErrorBars
//===========================================================================

DEF_STD_CMD_A(StdAddErrorBars)

StdAddErrorBars::StdAddErrorBars() : Command("Std_Graph_Add_error_bars")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Error Bars");
    sToolTipText = QT_TR_NOOP("Add error bars");
    sWhatsThis = "Std_Graph_Add_error_bars";
    sStatusTip = QT_TR_NOOP("Add error bars");
    sPixmap = "Std_Graph_Add_error_bars";
    eType = 0;
}

void StdAddErrorBars::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addErrorBars();
}

bool StdAddErrorBars::isActive() { return true; }

//===========================================================================
// Std_LegendReoder
//===========================================================================

DEF_STD_CMD_A(StdLegendReoder)

StdLegendReoder::StdLegendReoder() : Command("Std_Graph_Lengend_reorder")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Error Bars");
    sToolTipText = QT_TR_NOOP("Add error bars");
    sWhatsThis = "Std_Graph_Lengend_reorder";
    sStatusTip = QT_TR_NOOP("Add error bars");
    sPixmap = "Std_Graph_Lengend_reorder";
    eType = 0;
}

void StdLegendReoder::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->legendReorder();
}

bool StdLegendReoder::isActive() { return true; }

//===========================================================================
// Std_AddText
//===========================================================================

DEF_STD_CMD_A(StdAddText)

StdAddText::StdAddText() : Command("Std_Graph_Add_text")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Text");
    sToolTipText = QT_TR_NOOP("Add text");
    sWhatsThis = "Std_Graph_Add_text";
    sStatusTip = QT_TR_NOOP("Add text");
    sPixmap = "Std_Graph_Add_text";
    eType = 0;
}

void StdAddText::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addText();
}

bool StdAddText::isActive() { return true; }

//===========================================================================
// Std_AddTimeStamp
//===========================================================================

DEF_STD_CMD_A(StdAddTimeStamp)

StdAddTimeStamp::StdAddTimeStamp() : Command("Std_Graph_Add_time_stamp")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Time Stamp");
    sToolTipText = QT_TR_NOOP("Add time stamp");
    sWhatsThis = "Std_Graph_Add_time_stamp";
    sStatusTip = QT_TR_NOOP("Add time stamp");
    sPixmap = "Std_Graph_Add_time_stamp";
    eType = 0;
}

void StdAddTimeStamp::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addTimeStamp();
}

bool StdAddTimeStamp::isActive() { return true; }


//===========================================================================
// Std_AddImage
//===========================================================================

DEF_STD_CMD_A(StdAddImage)

StdAddImage::StdAddImage() : Command("Std_Graph_Add_image")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Image");
    sToolTipText = QT_TR_NOOP("Add image");
    sWhatsThis = "Std_Graph_Add_image";
    sStatusTip = QT_TR_NOOP("Add image");
    sPixmap = "Std_Graph_Add_image";
    eType = 0;
}

void StdAddImage::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addImage();
}

bool StdAddImage::isActive() { return true; }

//===========================================================================
// Std_AddLine
//===========================================================================

DEF_STD_CMD_A(StdAddLine)

StdAddLine::StdAddLine() : Command("Std_Graph_Draw_line")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Line");
    sToolTipText = QT_TR_NOOP("Add line");
    sWhatsThis = "Std_Graph_Draw_line";
    sStatusTip = QT_TR_NOOP("Add line");
    sPixmap = "Std_Graph_Draw_line";
    eType = 0;
}

void StdAddLine::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->drawLine();
}

bool StdAddLine::isActive() { return true; }

//===========================================================================
// Std_AddArrow
//===========================================================================

DEF_STD_CMD_A(StdAddArrow)

StdAddArrow::StdAddArrow() : Command("Std_Graph_Draw_arrow")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Arrow");
    sToolTipText = QT_TR_NOOP("Add arrow");
    sWhatsThis = "Std_Graph_Draw_arrow";
    sStatusTip = QT_TR_NOOP("Add arrow");
    sPixmap = "Std_Graph_Draw_arrow";
    eType = 0;
}

void StdAddArrow::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->drawArrow();
}

bool StdAddArrow::isActive() { return true; }

//===========================================================================
// Std_AddEllipse
//===========================================================================

DEF_STD_CMD_A(StdAddEllipse)

StdAddEllipse::StdAddEllipse() : Command("Std_Graph_Draw_ellipse")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Ellipse");
    sToolTipText = QT_TR_NOOP("Add ellipse");
    sWhatsThis = "Std_Graph_Draw_ellipse";
    sStatusTip = QT_TR_NOOP("Add ellipse");
    // sPixmap = "add-ellipse";
    eType = 0;
}

void StdAddEllipse::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->drawEllipse();
}

bool StdAddEllipse::isActive() { return true; }

//===========================================================================
// Std_AddNestedLayout
//===========================================================================

DEF_STD_CMD_A(StdAddNestedLayout)

StdAddNestedLayout::StdAddNestedLayout() : Command("Std_Graph_Add_nested_layout")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Nested Layout");
    sToolTipText = QT_TR_NOOP("Add nested layout");
    sWhatsThis = "Std_Graph_Add_nested_layout";
    sStatusTip = QT_TR_NOOP("Add nested layout");
    sPixmap = "Std_Graph_Add_nested_layout";
    eType = 0;
}

void StdAddNestedLayout::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addNestedLayout();
}

bool StdAddNestedLayout::isActive() { return true; }

//===========================================================================
// Std_RemoveLayout
//===========================================================================

DEF_STD_CMD_A(StdRemoveLayout)

StdRemoveLayout::StdRemoveLayout() : Command("Std_Graph_Remove_layout")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Remove Layout");
    sToolTipText = QT_TR_NOOP("Remove layout");
    sWhatsThis = "Std_Graph_Remove_layout";
    sStatusTip = QT_TR_NOOP("Remove layout");
    sPixmap = "Std_Graph_Remove_layout";
    eType = 0;
}

void StdRemoveLayout::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->deleteLayout();
}

bool StdRemoveLayout::isActive() { return true; }

//===========================================================================
// Std_SwapLayouts
//===========================================================================

DEF_STD_CMD_A(StdSwapLayouts)

StdSwapLayouts::StdSwapLayouts() : Command("Std_Graph_Swap_layouts")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Swap Layout");
    sToolTipText = QT_TR_NOOP("Swap layout");
    sWhatsThis = "Std_Graph_Swap_layouts";
    sStatusTip = QT_TR_NOOP("Swap layout");
    // sPixmap = "Std_Graph_Swap_layouts";
    eType = 0;
}

void StdSwapLayouts::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->showSwapLayoutDialog();
}

bool StdSwapLayouts::isActive() { return true; }

//===========================================================================
// Std_DisableTools
//===========================================================================

DEF_STD_CMD_A(StdDisableTools)

StdDisableTools::StdDisableTools() : Command("Std_Tools_Disable_tools")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Disable Tools");
    sToolTipText = QT_TR_NOOP("Disable Tools");
    sWhatsThis = "Std_Tools_Disable_tools";
    sStatusTip = QT_TR_NOOP("Disable Tools");
    sPixmap = "Std_Tools_Disable_tools";
    eType = 0;
}

void StdDisableTools::activated(int iMsg) 
{ 
    Q_UNUSED(iMsg); 
    Gui::getMainWindow()->getAlphaPlot()->pickGraphTool(this->getAction()->action());
}

bool StdDisableTools::isActive() { return true; }

//===========================================================================
// Std_DataReader
//===========================================================================

DEF_STD_CMD_A(StdDataReader)

StdDataReader::StdDataReader() : Command("Std_Tools_Data_reader")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Data Reader");
    sToolTipText = QT_TR_NOOP("Disable Reader");
    sWhatsThis = "Std_Tools_Data_reader";
    sStatusTip = QT_TR_NOOP("Disable Reader");
    sPixmap = "Std_Tools_Data_reader";
    eType = 0;
}

void StdDataReader::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickGraphTool(this->getAction()->action());
}

bool StdDataReader::isActive() { return true; }

//===========================================================================
// Std_ScreenReader
//===========================================================================

DEF_STD_CMD_A(StdScreenReader)

StdScreenReader::StdScreenReader() : Command("Std_Tools_Screen_reader")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Screen Reader");
    sToolTipText = QT_TR_NOOP("Screen Reader");
    sWhatsThis = "Std_Tools_Screen_reader";
    sStatusTip = QT_TR_NOOP("Screen Reader");
    sPixmap = "Std_Tools_Screen_reader";
    eType = 0;
}

void StdScreenReader::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickGraphTool(this->getAction()->action());
}

bool StdScreenReader::isActive() { return true; }

//===========================================================================
// Std_SelectDataRange
//===========================================================================

DEF_STD_CMD_A(StdSelectDataRange)

StdSelectDataRange::StdSelectDataRange() : Command("Std_Tools_Select_data_range")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Select Data Range");
    sToolTipText = QT_TR_NOOP("Select Data Range");
    sWhatsThis = "Std_Tools_Select_data_range";
    sStatusTip = QT_TR_NOOP("Select Data Range");
    sPixmap = "Std_Tools_Select_data_range";
    eType = 0;
}

void StdSelectDataRange::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickGraphTool(this->getAction()->action());
}

bool StdSelectDataRange::isActive() { return true; }

//===========================================================================
// Std_MoveDataPoints
//===========================================================================

DEF_STD_CMD_A(StdMoveDataPoints)

StdMoveDataPoints::StdMoveDataPoints() : Command("Std_Tools_Move_data_points")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Move Data Points...");
    sToolTipText = QT_TR_NOOP("Move Data Points");
    sWhatsThis = "Std_Tools_Move_data_points";
    sStatusTip = QT_TR_NOOP("Move Data Points");
    sPixmap = "Std_Tools_Move_data_points";
    eType = 0;
}

void StdMoveDataPoints::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickGraphTool(this->getAction()->action());
}

bool StdMoveDataPoints::isActive() { return true; }

//===========================================================================
// Std_RemoveBadDataPoints
//===========================================================================

DEF_STD_CMD_A(StdRemoveBadDataPoints)

StdRemoveBadDataPoints::StdRemoveBadDataPoints() : Command("Std_Tools_Remove_bad_data_points")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Remove Bad Data Points...");
    sToolTipText = QT_TR_NOOP("Remove bad data points");
    sWhatsThis = "Std_Tools_Remove_bad_data_points";
    sStatusTip = QT_TR_NOOP("Remove bad data points");
    sPixmap = "Std_Tools_Remove_bad_data_points";
    eType = 0;
}

void StdRemoveBadDataPoints::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickGraphTool(this->getAction()->action());
}

bool StdRemoveBadDataPoints::isActive() { return true; }

//===========================================================================
// Std_DragRange
//===========================================================================

DEF_STD_CMD_A(StdDragRange)

StdDragRange::StdDragRange() : Command("Std_Graph_Drag_range")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Drag Range");
    sToolTipText = QT_TR_NOOP("Drag range");
    sWhatsThis = "Std_Graph_Drag_range";
    sStatusTip = QT_TR_NOOP("Drag range");
    sPixmap = "Std_Graph_Drag_range";
    eType = 0;
}

void StdDragRange::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickGraphTool(this->getAction()->action());
}

bool StdDragRange::isActive() { return true; }

//===========================================================================
// Std_ZoomRang
//===========================================================================

DEF_STD_CMD_A(StdZoomRang)

StdZoomRang::StdZoomRang() : Command("Std_Tools_Zoom_range")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Zoom Rang");
    sToolTipText = QT_TR_NOOP("Zoom range");
    sWhatsThis = "Std_Tools_Zoom_range";
    sStatusTip = QT_TR_NOOP("Zoom range");
    sPixmap = "Std_Tools_Zoom_range";
    eType = 0;
}

void StdZoomRang::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pickGraphTool(this->getAction()->action());
}

bool StdZoomRang::isActive() { return true; }

//===========================================================================
// Std_RescaleToShowAll
//===========================================================================

DEF_STD_CMD_A(StdRescaleToShowAll)

StdRescaleToShowAll::StdRescaleToShowAll() : Command("Std_Tools_Rescale_to_show_all")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Rescale to Show All");
    sToolTipText = QT_TR_NOOP("Rescale to show all");
    sWhatsThis = "Std_Tools_Rescale_to_show_all";
    sStatusTip = QT_TR_NOOP("Rescale to show all");
    sPixmap = "Std_Tools_Rescale_to_show_all";
    eType = 0;
}

void StdRescaleToShowAll::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->setAutoScale();
}

bool StdRescaleToShowAll::isActive() { return true; }

//===========================================================================
// Std_DuplicateWindow
//===========================================================================

DEF_STD_CMD_A(StdDuplicateWindow)

StdDuplicateWindow::StdDuplicateWindow() : Command("Std_DuplicateWindow")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Duplicate Window");
    sToolTipText = QT_TR_NOOP("Duplicate Window");
    sWhatsThis = "Std_DuplicateWindow";
    sStatusTip = QT_TR_NOOP("Duplicate Window");
    // sPixmap = "duplicate-window";
    eType = 0;
}

void StdDuplicateWindow::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->clone();
}

bool StdDuplicateWindow::isActive() { return true; }

//===========================================================================
// Std_PrintTableMatrixGhraph
//===========================================================================

DEF_STD_CMD_A(StdPrintTableMatrixGhraph)

StdPrintTableMatrixGhraph::StdPrintTableMatrixGhraph() : Command("Std_PrintTableMatrixGhraph")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Print Table/Matrix/Ghraph");
    sToolTipText = QT_TR_NOOP("Print table, matrix or graph");
    sWhatsThis = "Std_PrintTableMatrixGhraph";
    sStatusTip = QT_TR_NOOP("Print table, matrix or graph");
    sPixmap = "Print-table-matrix-graph";
    eType = 0;
}

void StdPrintTableMatrixGhraph::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->printWindow();
}

bool StdPrintTableMatrixGhraph::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotEditCurveRange
//===========================================================================

DEF_STD_CMD_A(StdPlotEditCurveRange)

StdPlotEditCurveRange::StdPlotEditCurveRange() : Command("Std_PlotEditCurveRange")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Edit Curve Range");
    sToolTipText = QT_TR_NOOP("Edit Curve Range");
    sWhatsThis = "Std_PlotEditCurveRange";
    sStatusTip = QT_TR_NOOP("Edit Curve Range");
    sPixmap = "edit-curve-range";
    eType = 0;
}

void StdPlotEditCurveRange::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->showCurveRangeDialog();
}

bool StdPlotEditCurveRange::isActive() { return hasActiveDocument(); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_TableShowExportASCIIDialog
//===========================================================================

DEF_STD_CMD_A(StdPlotShowExportASCIIDialog)

StdPlotShowExportASCIIDialog::StdPlotShowExportASCIIDialog()
    : Command("Std_TableShowExportASCIIDialog")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Show Export ASCII Dialog");
    sToolTipText = QT_TR_NOOP("Show export ASCII dialog");
    sWhatsThis = "Std_TableShowExportASCIIDialog";
    sStatusTip = QT_TR_NOOP("Show export ASCII dialog");
    // sPixmap = "edit-curve-range";
    eType = 0;
}

void StdPlotShowExportASCIIDialog::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->showExportASCIIDialog();
}

bool StdPlotShowExportASCIIDialog::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_TableExportPDF
//===========================================================================

DEF_STD_CMD_A(StdPlotExportPDF)

StdPlotExportPDF::StdPlotExportPDF() : Command("Std_TableExportPDF")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Export PDF");
    sToolTipText = QT_TR_NOOP("Export table to PDF");
    sWhatsThis = "Std_TableExportPDF";
    sStatusTip = QT_TR_NOOP("Export table to PDF");
    // sPixmap = "edit-curve-range";
    eType = 0;
}

void StdPlotExportPDF::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->exportPDF();
}

bool StdPlotExportPDF::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotCloseAllWindows
//===========================================================================

DEF_STD_CMD_A(StdPlotCloseAllWindows)

StdPlotCloseAllWindows::StdPlotCloseAllWindows() : Command("Std_PlotCloseAllWindows")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Close all Windows");
    sToolTipText = QT_TR_NOOP("Close all windows");
    sWhatsThis = "Std_PlotCloseAllWindows";
    sStatusTip = QT_TR_NOOP("Close all windows");
    sPixmap = "close-all-windows";
    eType = 0;
}

void StdPlotCloseAllWindows::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    qApp->closeAllWindows();
}

bool StdPlotCloseAllWindows::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_TableConvertToMatrix
//===========================================================================

DEF_STD_CMD_A(StdPlotConvertTable)

StdPlotConvertTable::StdPlotConvertTable() : Command("Std_Table_Convert_to_matrix")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Convert to Matrix");
    sToolTipText = QT_TR_NOOP("Convert table to matrix");
    sWhatsThis = "Std_Table_Convert_to_matrix";
    sStatusTip = QT_TR_NOOP("Convert table to matrix");
    // sPixmap = "convert-table";
    eType = 0;
}

void StdPlotConvertTable::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->convertTableToMatrix();
}

bool StdPlotConvertTable::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_TableAddColToTable
//===========================================================================

DEF_STD_CMD_A(StdPlotAddColToTable)

StdPlotAddColToTable::StdPlotAddColToTable() : Command("Std_Table_Add_column")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add Col to Table");
    sToolTipText = QT_TR_NOOP("Add col to table");
    sWhatsThis = "Std_Table_Add_column";
    sStatusTip = QT_TR_NOOP("Add col to table");
    // sPixmap = "add-col-to-table";
    eType = 0;
}

void StdPlotAddColToTable::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->addColToTable();
}

bool StdPlotAddColToTable::isActive() { return true; }

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //===========================================================================
// // Std_PlotHideActiveWindow
// //===========================================================================

// DEF_STD_CMD_A(StdPlotHideActiveWindow)

// StdPlotHideActiveWindow::StdPlotHideActiveWindow() : Command("Std_PlotHideActiveWindow")
// {
//     sGroup = "Tools";
//     sMenuText = QT_TR_NOOP("Hide Active Window");
//     sToolTipText = QT_TR_NOOP("Hide active window");
//     sWhatsThis = "Std_PlotHideActiveWindow";
//     sStatusTip = QT_TR_NOOP("Hide active window");
//     sPixmap = "hide-active-window";
//     eType = 0;
// }

// void StdPlotHideActiveWindow::activated(int iMsg)
// {
//     Q_UNUSED(iMsg);
//     Gui::getMainWindow()->getAlphaPlot()->hideActiveWindow();
// }

// bool StdPlotHideActiveWindow::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotShowMoreWindows
//===========================================================================

DEF_STD_CMD_A(StdPlotShowMoreWindows)

StdPlotShowMoreWindows::StdPlotShowMoreWindows() : Command("Std_PlotShowMoreWindows")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Show More Windows");
    sToolTipText = QT_TR_NOOP("Show more windows");
    sWhatsThis = "Std_PlotShowMoreWindows";
    sStatusTip = QT_TR_NOOP("Show more windows");
    sPixmap = "Show-more-windows";
    eType = 0;
}

void StdPlotShowMoreWindows::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->showMoreWindows();
}

bool StdPlotShowMoreWindows::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotPixelLineProfile
//===========================================================================

DEF_STD_CMD_A(StdPlotPixelLineProfile)

StdPlotPixelLineProfile::StdPlotPixelLineProfile() : Command("Std_PlotPixelLineProfile")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Pixel Line Profile");
    sToolTipText = QT_TR_NOOP("Pixel line profile");
    sWhatsThis = "Std_PlotPixelLineProfile";
    sStatusTip = QT_TR_NOOP("Pixel line profile");
    sPixmap = "pixel-line-profile";
    eType = 0;
}

void StdPlotPixelLineProfile::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->pixelLineProfile();
}

bool StdPlotPixelLineProfile::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotIntensityTable
//===========================================================================

DEF_STD_CMD_A(StdPlotIntensityTable)

StdPlotIntensityTable::StdPlotIntensityTable() : Command("Std_PlotIntensityTable")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Intensity Table");
    sToolTipText = QT_TR_NOOP("Intensity table");
    sWhatsThis = "Std_PlotIntensityTable";
    sStatusTip = QT_TR_NOOP("Intensity table");
    sPixmap = "intensity-table";
    eType = 0;
}

void StdPlotIntensityTable::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->intensityTable();
}

bool StdPlotIntensityTable::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotEditSurfacePlot
//===========================================================================

DEF_STD_CMD_A(StdPlotEditSurfacePlot)

StdPlotEditSurfacePlot::StdPlotEditSurfacePlot() : Command("Std_PlotEditSurfacePlot")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Edit Surface Plot");
    sToolTipText = QT_TR_NOOP("Edit surface plot");
    sWhatsThis = "Std_PlotEditSurfacePlot";
    sStatusTip = QT_TR_NOOP("Edit surface plot");
    sPixmap = "edit-surface-plot";
    eType = 0;
}

void StdPlotEditSurfacePlot::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->editSurfacePlot();
}

bool StdPlotEditSurfacePlot::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotMinimizeWindow
//===========================================================================

DEF_STD_CMD_A(StdPlotMinimizeWindow)

StdPlotMinimizeWindow::StdPlotMinimizeWindow() : Command("Std_PlotMinimizeWindow")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Minimize Window");
    sToolTipText = QT_TR_NOOP("Minimize window");
    sWhatsThis = "Std_PlotMinimizeWindow";
    sStatusTip = QT_TR_NOOP("Minimize window");
    sPixmap = "minimize-window";
    eType = 0;
}

void StdPlotMinimizeWindow::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->minimizeWindow();
}

bool StdPlotMinimizeWindow::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotMaximizeWindow
//===========================================================================

DEF_STD_CMD_A(StdPlotMaximizeWindow)

StdPlotMaximizeWindow::StdPlotMaximizeWindow() : Command("Std_PlotMaximizeWindow")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Maximize Window");
    sToolTipText = QT_TR_NOOP("Maximize window");
    sWhatsThis = "Std_PlotMaximizeWindow";
    sStatusTip = QT_TR_NOOP("Maximize window");
    sPixmap = "maximize-window";
    eType = 0;
}

void StdPlotMaximizeWindow::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->maximizeWindow();
}

bool StdPlotMaximizeWindow::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotPrintWindow
//===========================================================================

DEF_STD_CMD_A(StdPlotPrintWindow)

StdPlotPrintWindow::StdPlotPrintWindow() : Command("Std_PlotPrintWindow")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Print Window");
    sToolTipText = QT_TR_NOOP("Print window");
    sWhatsThis = "Std_PlotPrintWindow";
    sStatusTip = QT_TR_NOOP("Print window");
    sPixmap = "print-window";
    eType = 0;
}

void StdPlotPrintWindow::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->printWindow();
}

bool StdPlotPrintWindow::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotAdd3DData
//===========================================================================

DEF_STD_CMD_A(StdPlotAdd3DData)

StdPlotAdd3DData::StdPlotAdd3DData() : Command("Std_PlotAdd3DData")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Add 3D Data");
    sToolTipText = QT_TR_NOOP("Add 3D data");
    sWhatsThis = "Std_PlotAdd3DData";
    sStatusTip = QT_TR_NOOP("Add 3D data");
    sPixmap = "add-3D-data";
    eType = 0;
}

void StdPlotAdd3DData::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->add3DData();
}

bool StdPlotAdd3DData::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_MatrixDeterminant
//===========================================================================

DEF_STD_CMD_A(StdPlotMatrixDeterminant)

StdPlotMatrixDeterminant::StdPlotMatrixDeterminant() : Command("Std_Matrix_Determinant")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Matrix Determinant");
    sToolTipText = QT_TR_NOOP("Matrix determinant");
    sWhatsThis = "Std_Matrix_Determinant";
    sStatusTip = QT_TR_NOOP("Matrix determinant");
    // sPixmap = "matrix-determinant";
    eType = 0;
}

void StdPlotMatrixDeterminant::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->matrixDeterminant();
}

bool StdPlotMatrixDeterminant::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_Matrix_Transpose
//===========================================================================

DEF_STD_CMD_A(StdMatrixTranspose)

StdMatrixTranspose::StdMatrixTranspose() : Command("Std_Matrix_Transpose")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Transpose");
    sToolTipText = QT_TR_NOOP("Transpose the active matrix");
    sWhatsThis = "Std_Matrix_Transpose";
    sStatusTip = QT_TR_NOOP("Transpose the active matrix");
    // sPixmap = "matrix-transpose";
    eType = 0;
}

void StdMatrixTranspose::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->transposeMatrix();
}

bool StdMatrixTranspose::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_Matrix_MirrorHorizontally
//===========================================================================

DEF_STD_CMD_A(StdMatrixMirrorHorizontally)

StdMatrixMirrorHorizontally::StdMatrixMirrorHorizontally() : Command("Std_Matrix_MirrorHorizontally")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Mirror Horizontally");
    sToolTipText = QT_TR_NOOP("Mirror horizontally the columns of the active matrix");
    sWhatsThis = "Std_Matrix_MirrorHorizontally";
    sStatusTip = QT_TR_NOOP("Mirror horizontally the columns of the active matrix");
    // sPixmap = "matrix-mirror-horizontally";
    eType = 0;
}

void StdMatrixMirrorHorizontally::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->mirrorHorizontally();
}

bool StdMatrixMirrorHorizontally::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_Matrix_MirrorVertically
//===========================================================================

DEF_STD_CMD_A(StdMatrixMirrorVertically)

StdMatrixMirrorVertically::StdMatrixMirrorVertically()
    : Command("Std_Matrix_MirrorVertically")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Mirror Vertically");
    sToolTipText = QT_TR_NOOP("Mirror vertically the columns of the active matrix");
    sWhatsThis = "Std_Matrix_MirrorVertically";
    sStatusTip = QT_TR_NOOP("Mirror vertically the columns of the active matrix");
    // sPixmap = "matrix-mirror-vertically";
    eType = 0;
}

void StdMatrixMirrorVertically::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->mirrorVertically();
}

bool StdMatrixMirrorVertically::isActive() { return true; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_MatrixConvertToTable
//===========================================================================

DEF_STD_CMD_A(StdPlotConvertMatrix)

StdPlotConvertMatrix::StdPlotConvertMatrix() : Command("Std_Matrix_Convert_to_table")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Convert to Table");
    sToolTipText = QT_TR_NOOP("Convert matrix");
    sWhatsThis = "Std_Matrix_Convert_to_table";
    sStatusTip = QT_TR_NOOP("Convert matrix");
    // sPixmap = "convert-matrix";
    eType = 0;
}

void StdPlotConvertMatrix::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->convertMatrixToTable();
}

bool StdPlotConvertMatrix::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_InvertMatrix
//===========================================================================

DEF_STD_CMD_A(StdPlotInvertMatrix)

StdPlotInvertMatrix::StdPlotInvertMatrix() : Command("Std_Matrix_Invert")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Invert Matrix");
    sToolTipText = QT_TR_NOOP("Invert matrix");
    sWhatsThis = "Std_Matrix_Invert";
    sStatusTip = QT_TR_NOOP("Invert matrix");
    // sPixmap = "invert-matrix";
    eType = 0;
}

void StdPlotInvertMatrix::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->invertMatrix();
}

bool StdPlotInvertMatrix::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_ClearTable
//===========================================================================

DEF_STD_CMD_A(StdPlotClearTable)

StdPlotClearTable::StdPlotClearTable() : Command("Std_Table_Clear_table")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Clear Table");
    sToolTipText = QT_TR_NOOP("Clear table");
    sWhatsThis = "Std_Table_Clear_table";
    sStatusTip = QT_TR_NOOP("Clear table");
    // sPixmap = "clear-table";
    eType = 0;
}

void StdPlotClearTable::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->clearTable();
}

bool StdPlotClearTable::isActive() { return hasActiveDocument(); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotGoToCell
//===========================================================================

DEF_STD_CMD_A(StdPlotGoToCell)

StdPlotGoToCell::StdPlotGoToCell() : Command("Std_PlotGoToCell")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Go to Cell");
    sToolTipText = QT_TR_NOOP("Go to cell");
    sWhatsThis = "Std_PlotGoToCell";
    sStatusTip = QT_TR_NOOP("Go to cell");
    sPixmap = "Go-to-Cell";
    eType = 0;
}

void StdPlotGoToCell::activated(int iMsg)
{
    Q_UNUSED(iMsg);
}

bool StdPlotGoToCell::isActive() { return true; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotSaveNote
//===========================================================================

DEF_STD_CMD_A(StdPlotSaveNote)

StdPlotSaveNote::StdPlotSaveNote() : Command("Std_PlotSaveNote")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Save Note");
    sToolTipText = QT_TR_NOOP("Save note");
    sWhatsThis = "Std_PlotSaveNote";
    sStatusTip = QT_TR_NOOP("Save note");
    sPixmap = "Save-note";
    eType = 0;
}

void StdPlotSaveNote::activated(int iMsg) { Q_UNUSED(iMsg); }

bool StdPlotSaveNote::isActive() { return hasActiveDocument(); }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotResetCameraFront
//===========================================================================

DEF_STD_CMD_A(StdPlotResetCameraFront)

StdPlotResetCameraFront::StdPlotResetCameraFront() : Command("Std_PlotResetCameraFront")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Reset Camera Front");
    sToolTipText = QT_TR_NOOP("Reset camera front");
    sWhatsThis = "Std_PlotResetCameraFront";
    sStatusTip = QT_TR_NOOP("Reset camera front");
    sPixmap = "reset-camera-front";
    eType = 0;
}

void StdPlotResetCameraFront::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->setCameraPresetFront();
}

bool StdPlotResetCameraFront::isActive() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Std_PlotResetZoomFactor
//===========================================================================

DEF_STD_CMD_A(StdPlotResetZoomFactor)

StdPlotResetZoomFactor::StdPlotResetZoomFactor() : Command("Std_PlotResetZoomFactor")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Reset Zoom Factor");
    sToolTipText = QT_TR_NOOP("Reset zoom factor");
    sWhatsThis = "Std_PlotResetZoomFactor";
    sStatusTip = QT_TR_NOOP("Reset zoom factor");
    sPixmap = "reset-zoom-factor";
    eType = 0;
}

void StdPlotResetZoomFactor::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->resetZoomfactor();
}

bool StdPlotResetZoomFactor::isActive() { return true; }

//===========================================================================
// Std_PlotActivateWindow
//===========================================================================

DEF_STD_CMD_A(StdPlotActivateWindow)

StdPlotActivateWindow::StdPlotActivateWindow() : Command("Std_PlotActivateWindow")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Activate Window");
    sToolTipText = QT_TR_NOOP("Activate window");
    sWhatsThis = "Std_PlotActivateWindow";
    sStatusTip = QT_TR_NOOP("Activate window");
    sPixmap = "activate-window";
    eType = 0;
}

void StdPlotActivateWindow::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->activateWindow();
}

bool StdPlotActivateWindow::isActive() { return true; }

//===========================================================================
// Std_New_Table
//===========================================================================
DEF_STD_CMD(StdCmdNewTable)

StdCmdNewTable::StdCmdNewTable() : Command("Std_New_Table")
{
    // setting the
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("&Table");
    sToolTipText = QT_TR_NOOP("Create a new table");
    sWhatsThis = "Std_New_Table";
    sStatusTip = QT_TR_NOOP("Create a new table");
    sPixmap = "Std_New_Table";
    eType = NoTransaction;
    sAccel        = "Ctrl+T";

}

void StdCmdNewTable::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->newTable();
}

//===========================================================================
// Std_New_Matrix
//===========================================================================
DEF_STD_CMD(StdCmdNewMatrix)

StdCmdNewMatrix::StdCmdNewMatrix() : Command("Std_New_Matrix")
{
    // setting the
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("&Matrix");
    sToolTipText = QT_TR_NOOP("Create a new Matrix");
    sWhatsThis = "Std_New_Matrix";
    sStatusTip = QT_TR_NOOP("Create a new Matrix");
    sPixmap = "Std_New_Matrix";
    eType = NoTransaction;
    sAccel        = "Ctrl+M";

}

void StdCmdNewMatrix::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->newMatrix();
}

//===========================================================================
// Std_NewScene
//===========================================================================
DEF_STD_CMD(StdCmdNewScene)

StdCmdNewScene::StdCmdNewScene() : Command("Std_NewScene")
{
    // setting the
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("&Scene");
    sToolTipText = QT_TR_NOOP("Create a new Scene");
    sWhatsThis = "Std_NewScene";
    sStatusTip = QT_TR_NOOP("Create a new Scene");
    sPixmap = "Std_File_New_scene";
    eType = NoTransaction;

}

void StdCmdNewScene::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    // Gui::getMainWindow()->getAlphaPlot()->newScene();
}

//===========================================================================
// Std_New_Graph
//===========================================================================
DEF_STD_CMD(StdNewGraph)

StdNewGraph::StdNewGraph() : Command("Std_New_Graph")
{
    // setting the
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("&Graph");
    sToolTipText = QT_TR_NOOP("Create a new graph");
    sWhatsThis = "Std_New_Graph";
    sStatusTip = QT_TR_NOOP("Create a new graph");
    sPixmap = "Std_New_Graph";
    eType = NoTransaction;
    sAccel        = "Ctrl+G";

}

void StdNewGraph::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->newGraph2D();
}

//===========================================================================
// Std_New_2DPlot
//===========================================================================
DEF_STD_CMD_A(StdNew2DPlot)

StdNew2DPlot::StdNew2DPlot() : Command("Std_New_2DPlot")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("2D Plot");
    sToolTipText = QT_TR_NOOP("Create new function plot");
    sWhatsThis = "Std_New_2DPlot";
    sStatusTip = QT_TR_NOOP("Create new function plot");
    sPixmap = "Std_New_2DPlot";
    eType = 0;

}

void StdNew2DPlot::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->functionDialog();
}

bool StdNew2DPlot::isActive() { return true; }
//===========================================================================
// Std_New_3DPlot
//===========================================================================

DEF_STD_CMD_A(StdNew3DPlot)

StdNew3DPlot::StdNew3DPlot() : Command("Std_New_3DPlot")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("3D Plot");
    sToolTipText = QT_TR_NOOP("Create new 3D plot");
    sWhatsThis = "Std_New_3DPlot";
    sStatusTip = QT_TR_NOOP("Create new 2D plot");
    sPixmap = "Std_New_3DPlot";
    eType = 0;
}

void StdNew3DPlot::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::getMainWindow()->getAlphaPlot()->newSurfacePlot();
}

bool StdNew3DPlot::isActive() { return true; }

//======================================================================
// Std_File_New_aspect
//===========================================================================
//
class StdCmdNewAspects: public GroupCommand
{
public:
    StdCmdNewAspects()
        :GroupCommand("Std_File_New_aspect")
    {
        sGroup        = "File";
        sMenuText     = QT_TR_NOOP("AlphaPlot");
        sToolTipText  = QT_TR_NOOP("Create new aspect");
        sWhatsThis    = "Std_File_New_aspect";
        sStatusTip    = QT_TR_NOOP("Create new aspect");
        eType         = 0;
        bCanLog       = false;

        addCommand(new StdCmdNewTable());
        addCommand(new StdCmdNewMatrix());
        // addCommand(new StdCmdNewScene());
        addCommand(new StdNewGraph());
        addCommand(new StdNew2DPlot());
        addCommand(new StdNew3DPlot());

    }
    virtual const char* className() const {return "StdCmdNewAspects";}
};



//===========================================================================
// StdCmdPlugins
//===========================================================================
DEF_STD_CMD(StdCmdPlugins)

StdCmdPlugins::StdCmdPlugins() : Command("Std_DlgRPSFeatures")
{
    sGroup = "Tools";
    sMenuText = QT_TR_NOOP("Feature Manager ...");
    sToolTipText = QT_TR_NOOP("Opens a dialog to show the list of plugins available for the active workbench");
    sWhatsThis = "Std_DlgRPSFeatures";
    sStatusTip = QT_TR_NOOP("Opens a dialog to show the list of plugins available for the active workbench");
    sPixmap = "Std_DlgRPSFeatures";
    eType = 0;
}

void StdCmdPlugins::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Gui::Application::Instance->showPluginList();
}

//===========================================================================
// Std_VerticaDropLine
//===========================================================================

DEF_STD_CMD_A(StdVerticaDropLine)

StdVerticaDropLine::StdVerticaDropLine() : Command("Std_Plot_Vertical_drop_lines")
{
    sGroup = "Alphaplot Table Tools";
    sMenuText = QT_TR_NOOP("Vertical Drop Line");
    sToolTipText = QT_TR_NOOP("A vertical drop line plot");
    sWhatsThis = "Std_Plot_Vertical_drop_lines";
    sStatusTip = QT_TR_NOOP("A vertical drop line plot");
    sPixmap = "Std_Plot_Vertical_drop_lines";
    eType = 0;
}

void StdVerticaDropLine::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(static_cast<int>(PlotStyle::Graph::VerticalDropLines));
}

bool StdVerticaDropLine::isActive() { return true; }

//===========================================================================
// Std_Spline
//===========================================================================

DEF_STD_CMD_A(StdSpLine)

StdSpLine::StdSpLine() : Command("Std_Plot_Spline")
{
    sGroup = "Alphaplot Table Tools";
    sMenuText = QT_TR_NOOP("Spline");
    sToolTipText = QT_TR_NOOP("A spline plot");
    sWhatsThis = "Std_Plot_Spline";
    sStatusTip = QT_TR_NOOP("A spline plot");
    sPixmap = "Std_Plot_Spline";
    eType = 0;
}

void StdSpLine::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(
        static_cast<int>(PlotStyle::Graph::Spline));
}

bool StdSpLine::isActive() { return true; }

//===========================================================================
// Std_VerticalStep
//===========================================================================

DEF_STD_CMD_A(StdVerticalStep)

StdVerticalStep::StdVerticalStep() : Command("Std_Plot_Vertical_steps")
{
    sGroup = "Alphaplot Table Tools";
    sMenuText = QT_TR_NOOP("Verticall Step");
    sToolTipText = QT_TR_NOOP("A verticall step plot");
    sWhatsThis = "Std_Plot_Vertical_steps";
    sStatusTip = QT_TR_NOOP("A verticall step plot");
    sPixmap = "Std_Plot_Vertical_steps";
    eType = 0;
}

void StdVerticalStep::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(
        static_cast<int>(PlotStyle::Graph::VerticalSteps));
}

bool StdVerticalStep::isActive() { return true; }

//===========================================================================
// Std_HorizontalStep
//===========================================================================

DEF_STD_CMD_A(StdHorizontalStep)

StdHorizontalStep::StdHorizontalStep() : Command("Std_Plot_Horizontal_steps")
{
    sGroup = "Alphaplot Table Tools";
    sMenuText = QT_TR_NOOP("Horizontall Step");
    sToolTipText = QT_TR_NOOP("A horizontall step plot");
    sWhatsThis = "Std_Plot_Horizontal_steps";
    sStatusTip = QT_TR_NOOP("A horizontall step plot");
    sPixmap = "Std_Plot_Horizontal_steps";
    eType = 0;
}

void StdHorizontalStep::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->selectPlotType(
        static_cast<int>(PlotStyle::Graph::HorizontalSteps));
}

bool StdHorizontalStep::isActive() { return true; }

//======================================================================
// Std_LinesAndSteps
//===========================================================================
//
class StdLinesAndSteps: public GroupCommand
{
public:
    StdLinesAndSteps() : GroupCommand("Std_LinesAndSteps")
    {
        sGroup = "Alphaplot Table Tools";
        sMenuText = QT_TR_NOOP("Lines and Steps");
        sToolTipText = QT_TR_NOOP("Create lines or steps plot");
        sWhatsThis = "Std_LinesAndSteps";
        sStatusTip = QT_TR_NOOP("Create lines or steps plot");
        eType = 0;
        bCanLog = false;

        addCommand(new StdLine());
        addCommand(new StdLineAndSymbol());
        addCommand(new StdVerticaDropLine());
        addCommand(new StdSpLine());
        addCommand(new StdVerticalStep());
        addCommand(new StdHorizontalStep());

    }
    virtual const char* className() const { return "StdLinesAndSteps"; }
};

//======================================================================
// Std_VerticalAndHorizontalBars
//===========================================================================
//
class StdVerticalAndHorizontalBars: public GroupCommand
{
public:
    StdVerticalAndHorizontalBars() : GroupCommand("Std_VerticalAndHorizontalBars")
    {
        sGroup = "Alphaplot Table Tools";
        sMenuText = QT_TR_NOOP("Vertical and Horizontal Bars");
        sToolTipText = QT_TR_NOOP("Create vertical and horizontal bar plot");
        sWhatsThis = "Std_VerticalAndHorizontalBars";
        sStatusTip = QT_TR_NOOP("Create vertical and horizontal bar plot");
        eType = 0;
        bCanLog = false;

        addCommand(new StdVerticalBars());
        addCommand(new StdVerticalStackedBars());
        addCommand(new StdVerticalGroupedBars());
        addCommand(new StdHorizontalBars());
        addCommand(new StdHorizontalStackedBars());
        addCommand(new StdHorizontalGroupedBars());
    }
    virtual const char* className() const { return "StdVerticalAndHorizontalBars"; }
};

//======================================================================
// Std_SpecialLineAndSymbol
//===========================================================================
//
class StdSpecialLineAndSymbol: public GroupCommand
{
public:
    StdSpecialLineAndSymbol() : GroupCommand("Std_Plot_Special_lineSymbol")
    {
        sGroup = "Tools";
        sMenuText = QT_TR_NOOP("Special Line + Symbol");
        sToolTipText = QT_TR_NOOP("A special line and symbol plot");
        sWhatsThis = "Std_Plot_Special_lineSymbol";
        sStatusTip = QT_TR_NOOP("A special line and symbol plot");
        eType = 0;
        bCanLog = false;

        addCommand(new StdVerticaDropLine());
        addCommand(new StdSpLine());
        addCommand(new StdVerticalStep());
        addCommand(new StdHorizontalStep());
    }
    virtual const char* className() const { return "Std_Plot_Special_lineSymbol"; }
};

//======================================================================
// Std_VectorPlots
//===========================================================================
//
class StdVectorPlots: public GroupCommand
{
public:
    StdVectorPlots() : GroupCommand("Std_VectorPlots")
    {
        sGroup = "Alphaplot Table Tools";
        sMenuText = QT_TR_NOOP("Vector Plot");
        sToolTipText = QT_TR_NOOP("Create vector plot");
        sWhatsThis = "Std_VectorPlots";
        sStatusTip = QT_TR_NOOP("Create vector plot");
        eType = 0;
        bCanLog = false;

        addCommand(new StdVectorsXYXY());
        addCommand(new StdVectorsXYAM());
    }
    virtual const char* className() const { return "StdVectorPlots"; }
};

//======================================================================
// Std_PiePlots
//===========================================================================
//
class StdPiePlots: public GroupCommand
{
public:
    StdPiePlots() : GroupCommand("Std_PiePlots")
    {
        sGroup = "Alphaplot Table Tools";
        sMenuText = QT_TR_NOOP("Pie Plots");
        sToolTipText = QT_TR_NOOP("Create pie plot");
        sWhatsThis = "Std_PiePlots";
        sStatusTip = QT_TR_NOOP("Create pie plot");
        eType = 0;
        bCanLog = false;

        addCommand(new StdPie());
        addCommand(new StdHalfPie());
    }
    virtual const char* className() const { return "StdPiePlots"; }
};

//===========================================================================
// Std_AppendNewColumnToTable
//===========================================================================

DEF_STD_CMD_A(StdAppendNewColumnToTable)

StdAppendNewColumnToTable::StdAppendNewColumnToTable() : Command("Std_AppendNewColumnToTable")
{
    sGroup = "Table Statistics";
    sMenuText = QT_TR_NOOP("Append New Column");
    sToolTipText = QT_TR_NOOP("Append New Column to Table");
    sWhatsThis = "Std_AppendNewColumnToTable";
    sStatusTip = QT_TR_NOOP("Append New Column to Table");
    sPixmap = "Std_Table_Add_column";
    eType = 0;
}

void StdAppendNewColumnToTable::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->addColToTable();

   /* QString logInfo = QString::fromLatin1("<b>[") + QDateTime::currentDateTime().toString(Qt::LocalDate) + QString::fromLatin1("&emsp;")
        + QString::fromLatin1("Plot") + QString::fromLatin1(": ''");
    getMainWindow()->setResultLogInfo(logInfo);
    getMainWindow()->showResults(true);*/
}

bool StdAppendNewColumnToTable::isActive() { return true; }


//===========================================================================
// Std_ShowColumnStatistics
//===========================================================================

DEF_STD_CMD_A(StdShowColumnStatistics)

StdShowColumnStatistics::StdShowColumnStatistics() : Command("Std_ShowColumnStatistics")
{
    sGroup = "Table Statistics";
    sMenuText = QT_TR_NOOP("Column Statiscs");
    sToolTipText = QT_TR_NOOP("Show column statistics");
    sWhatsThis = "Std_ShowColumnStatistics";
    sStatusTip = QT_TR_NOOP("Show column statistics");
    sPixmap = "Std_Analysis_Statistics_on_columns";
    eType = 0;
}

void StdShowColumnStatistics::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->showColumnStatistics();
}

bool StdShowColumnStatistics::isActive() { return true; }


//===========================================================================
// Std_ShowRowStatistics
//===========================================================================

DEF_STD_CMD_A(StdShowRowStatistics)

StdShowRowStatistics::StdShowRowStatistics() : Command("Std_ShowRowStatistics")
{
    sGroup = "Table Statistics";
    sMenuText = QT_TR_NOOP("Row Statiscs");
    sToolTipText = QT_TR_NOOP("Show row statistics");
    sWhatsThis = "Std_ShowRowStatistics";
    sStatusTip = QT_TR_NOOP("Show row statistics");
    sPixmap = "Std_Analysis_Statistics_on_rows";
    eType = 0;
}

void StdShowRowStatistics::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->showRowStatistics();
}

bool StdShowRowStatistics::isActive() { return true; }

//===========================================================================
// Std_ExportTableASCII
//===========================================================================

DEF_STD_CMD_A(StdExportTableASCII)

StdExportTableASCII::StdExportTableASCII() : Command("Std_Table_Export_ASCII")
{
    sGroup = "Alphaplot Tools";
    sMenuText = QT_TR_NOOP("Export Table ASCII...");
    sToolTipText = QT_TR_NOOP("Export table as ASCII");
    sWhatsThis = "Std_Table_Export_ASCII";
    sStatusTip = QT_TR_NOOP("Export Alphaplot data as ASCII");
    // sPixmap = "Std_Table_Export_ASCII";
    eType = 0;
}

void StdExportTableASCII::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->showExportASCIIDialog();
}

bool StdExportTableASCII::isActive() { return true; }

//===========================================================================
// Std_ImportTableASCII
//===========================================================================

DEF_STD_CMD_A(StdImportTableASCII)

StdImportTableASCII::StdImportTableASCII() : Command("Std_ImportTableASCII")
{
    sGroup = "Alphaplot Tools";
    sMenuText = QT_TR_NOOP("Import Table ASCII...");
    sToolTipText = QT_TR_NOOP("Import table as ASCII");
    sWhatsThis = "Std_ImportTableASCII";
    sStatusTip = QT_TR_NOOP("Import Alphaplot data as ASCII");
    // sPixmap = "Std_ImportTableASCII";
    eType = 0;
}

void StdImportTableASCII::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->importASCII();
}

bool StdImportTableASCII::isActive() { return true; }

//===========================================================================
// Std_SaveAlphaplotData
//===========================================================================

DEF_STD_CMD_A(StdSaveAlphaplotData)

StdSaveAlphaplotData::StdSaveAlphaplotData() : Command("Std_SaveAlphaplotData")
{
    sGroup = "Alphaplot Tools";
    sMenuText = QT_TR_NOOP("Save");
    sToolTipText = QT_TR_NOOP("Save the alphaplot data to disc");
    sWhatsThis = "Std_SaveAlphaplotData";
    sStatusTip = QT_TR_NOOP("Save the alphaplot data to disc");
    // sPixmap = "Std_SaveAlphaplotData";
    eType = 0;
}

void StdSaveAlphaplotData::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->saveProject();
}

bool StdSaveAlphaplotData::isActive() { return true; }

//===========================================================================
// Std_LoadAlphaplotData
//===========================================================================

DEF_STD_CMD_A(StdLoadAlphaplotData)

StdLoadAlphaplotData::StdLoadAlphaplotData() : Command("Std_LoadAlphaplotData")
{
    sGroup = "Alphaplot Tools";
    sMenuText = QT_TR_NOOP("Load");
    sToolTipText = QT_TR_NOOP("Load the alphaplot data to disc");
    sWhatsThis = "Std_LoadAlphaplotData";
    sStatusTip = QT_TR_NOOP("Load the alphaplot data to disc");
    // sPixmap = "Std_LoadAlphaplotData";
    eType = 0;
}

void StdLoadAlphaplotData::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    getMainWindow()->getAlphaPlot()->openAproj();
}

bool StdLoadAlphaplotData::isActive() { return true; }




namespace Gui {

void CreateStdCommands()
{
    CommandManager &rcCmdMgr = Application::Instance->commandManager();

    rcCmdMgr.addCommand(new StdCmdAbout());
    rcCmdMgr.addCommand(new StdCmdAboutQt());

    rcCmdMgr.addCommand(new StdCmdDlgParameter());
    rcCmdMgr.addCommand(new StdCmdDlgPreferences());
    rcCmdMgr.addCommand(new StdCmdDlgCustomize());
    rcCmdMgr.addCommand(new StdCmdCommandLine());
    rcCmdMgr.addCommand(new StdCmdWorkbench());
    rcCmdMgr.addCommand(new StdCmdRecentFiles());
    rcCmdMgr.addCommand(new StdCmdRecentMacros());
    rcCmdMgr.addCommand(new StdCmdWhatsThis());
    rcCmdMgr.addCommand(new StdCmdPythonHelp());
    rcCmdMgr.addCommand(new StdCmdOnlineHelp());
    rcCmdMgr.addCommand(new StdCmdOnlineHelpWebsite());
    rcCmdMgr.addCommand(new StdCmdLabRPSWebsite());
    rcCmdMgr.addCommand(new StdCmdLabRPSDonation());
    rcCmdMgr.addCommand(new StdCmdLabRPSUserHub());
    rcCmdMgr.addCommand(new StdCmdLabRPSPowerUserHub());
    rcCmdMgr.addCommand(new StdCmdLabRPSForum());
    rcCmdMgr.addCommand(new StdCmdLabRPSFAQ());
    rcCmdMgr.addCommand(new StdCmdPythonWebsite());
    rcCmdMgr.addCommand(new StdCmdReportBug());
    rcCmdMgr.addCommand(new StdCmdTextDocument());
    rcCmdMgr.addCommand(new StdCmdUnitsCalculator());
    rcCmdMgr.addCommand(new StdCmdUserEditMode());
    //rcCmdMgr.addCommand(new StdCmdMeasurementSimple());
    //rcCmdMgr.addCommand(new StdCmdDownloadOnlineHelp());
    //rcCmdMgr.addCommand(new StdCmdDescription());

    rcCmdMgr.addCommand(new StdScatter());
    rcCmdMgr.addCommand(new StdScatterWithXError());
    rcCmdMgr.addCommand(new StdScatterWithYError());
    rcCmdMgr.addCommand(new StdScatterWithXYError());
    rcCmdMgr.addCommand(new StdBoxPlot());
    rcCmdMgr.addCommand(new StdHistogram());
    rcCmdMgr.addCommand(new StdStackedHistogram());
    rcCmdMgr.addCommand(new StdVerticalTwoLayouts());
    rcCmdMgr.addCommand(new StdHorizontalTwoLayouts());
    rcCmdMgr.addCommand(new StdFourLayouts());
    rcCmdMgr.addCommand(new StdLine());
    rcCmdMgr.addCommand(new StdLineAndSymbol());
    rcCmdMgr.addCommand(new StdSpecialLineAndSymbol());
    rcCmdMgr.addCommand(new StdVerticalBars());
    rcCmdMgr.addCommand(new StdVerticalStackedBars());
    rcCmdMgr.addCommand(new StdVerticalGroupedBars());
    rcCmdMgr.addCommand(new StdHorizontalBars());
    rcCmdMgr.addCommand(new StdHorizontalStackedBars());
    rcCmdMgr.addCommand(new StdHorizontalGroupedBars());
    rcCmdMgr.addCommand(new StdArea());
    rcCmdMgr.addCommand(new StdChannelFill());
    rcCmdMgr.addCommand(new StdPie());
    rcCmdMgr.addCommand(new StdHalfPie());
    rcCmdMgr.addCommand(new StdVectorsXYXY());
    rcCmdMgr.addCommand(new StdVectorsXYAM());
    // rcCmdMgr.addCommand(new Std3DWireFrame());
    // rcCmdMgr.addCommand(new Std3DSurface());
    // rcCmdMgr.addCommand(new Std3DWireFrameSurface());
    // rcCmdMgr.addCommand(new Std3DPlotBar());
    // rcCmdMgr.addCommand(new Std3DPlotScatter());
    // rcCmdMgr.addCommand(new StdContourAndColourFill());
    // rcCmdMgr.addCommand(new StdContourLines());
    // rcCmdMgr.addCommand(new StdGrayScaleMap());
    rcCmdMgr.addCommand(new Std3DWireFramePolar());
    rcCmdMgr.addCommand(new Std3DWireSurfacePolar());
    rcCmdMgr.addCommand(new Std3DWireFrameSurfacePolar());
    rcCmdMgr.addCommand(new Std3DScatterPolar());
    rcCmdMgr.addCommand(new StdPolarSpectogram());
    rcCmdMgr.addCommand(new StdAddRemovePlotY());
    rcCmdMgr.addCommand(new StdAddRemoveVectorPlot());
    rcCmdMgr.addCommand(new StdAddLeftAxisValue());
    rcCmdMgr.addCommand(new StdAddLeftAxisLog());
    rcCmdMgr.addCommand(new StdAddLeftAxisPi());
    rcCmdMgr.addCommand(new StdAddLeftAxisText());
    rcCmdMgr.addCommand(new StdAddLeftAxisTime());
    rcCmdMgr.addCommand(new StdAddLeftAxisDateTime());
    rcCmdMgr.addCommand(new StdAddBottomAxisValue());
    rcCmdMgr.addCommand(new StdAddBottomAxisLog());
    rcCmdMgr.addCommand(new StdAddBottomAxisPi());
    rcCmdMgr.addCommand(new StdAddBottomAxisText());
    rcCmdMgr.addCommand(new StdAddBottomAxisTime());
    rcCmdMgr.addCommand(new StdAddBottomAxisDateTime());
    rcCmdMgr.addCommand(new StdAddRightAxisValue());
    rcCmdMgr.addCommand(new StdAddRightAxisLog());
    rcCmdMgr.addCommand(new StdAddRightAxisPi());
    rcCmdMgr.addCommand(new StdAddRightAxisText());
    rcCmdMgr.addCommand(new StdAddRightAxisTime());
    rcCmdMgr.addCommand(new StdAddRightAxisDateTime());
    rcCmdMgr.addCommand(new StdAddTopAxisValue());
    rcCmdMgr.addCommand(new StdAddTopAxisLog());
    rcCmdMgr.addCommand(new StdAddTopAxisPi());
    rcCmdMgr.addCommand(new StdAddTopAxisText());
    rcCmdMgr.addCommand(new StdAddTopAxisTime());
    rcCmdMgr.addCommand(new StdAddTopAxisDateTime());
    rcCmdMgr.addCommand(new StdAddLayoutUp());
    rcCmdMgr.addCommand(new StdAddLayoutDown());
    rcCmdMgr.addCommand(new StdAddLayoutLeft());
    rcCmdMgr.addCommand(new StdAddLayoutRight());
    rcCmdMgr.addCommand(new StdAddRemovePlotXYAndXYY());
    rcCmdMgr.addCommand(new StdAddFunction());
    rcCmdMgr.addCommand(new StdAddErrorBars());
    rcCmdMgr.addCommand(new StdLegendReoder());
    rcCmdMgr.addCommand(new StdAddText());
    rcCmdMgr.addCommand(new StdAddTimeStamp());
    rcCmdMgr.addCommand(new StdAddImage());
    rcCmdMgr.addCommand(new StdAddLine());
    rcCmdMgr.addCommand(new StdAddArrow());
    rcCmdMgr.addCommand(new StdAddEllipse());
    rcCmdMgr.addCommand(new StdAddNestedLayout());
    rcCmdMgr.addCommand(new StdRemoveLayout());
    rcCmdMgr.addCommand(new StdSwapLayouts());
    rcCmdMgr.addCommand(new StdDisableTools());
    rcCmdMgr.addCommand(new StdDataReader());
    rcCmdMgr.addCommand(new StdScreenReader());
    rcCmdMgr.addCommand(new StdSelectDataRange());
    rcCmdMgr.addCommand(new StdMoveDataPoints());
    rcCmdMgr.addCommand(new StdRemoveBadDataPoints());
    rcCmdMgr.addCommand(new StdDragRange());
    rcCmdMgr.addCommand(new StdZoomRang());
    rcCmdMgr.addCommand(new StdRescaleToShowAll());
    rcCmdMgr.addCommand(new StdDuplicateWindow());
    rcCmdMgr.addCommand(new StdPrintTableMatrixGhraph());
    rcCmdMgr.addCommand(new StdPlotEditCurveRange());
    rcCmdMgr.addCommand(new StdPlotShowExportASCIIDialog());
    rcCmdMgr.addCommand(new StdPlotExportPDF());
    rcCmdMgr.addCommand(new StdPlotCloseAllWindows());
    rcCmdMgr.addCommand(new StdPlotConvertTable());
    rcCmdMgr.addCommand(new StdPlotAddColToTable());
    //rcCmdMgr.addCommand(new StdPlotHideActiveWindow());
    rcCmdMgr.addCommand(new StdPlotShowMoreWindows());
    rcCmdMgr.addCommand(new StdPlotPixelLineProfile());
    rcCmdMgr.addCommand(new StdPlotIntensityTable());
    rcCmdMgr.addCommand(new StdPlotEditSurfacePlot());
    rcCmdMgr.addCommand(new StdPlotMinimizeWindow());
    rcCmdMgr.addCommand(new StdPlotMaximizeWindow());
    rcCmdMgr.addCommand(new StdPlotPrintWindow());
    rcCmdMgr.addCommand(new StdPlotAdd3DData());
    rcCmdMgr.addCommand(new StdPlotMatrixDeterminant());
    rcCmdMgr.addCommand(new StdMatrixTranspose());
    rcCmdMgr.addCommand(new StdMatrixMirrorHorizontally());
    rcCmdMgr.addCommand(new StdMatrixMirrorVertically());
    rcCmdMgr.addCommand(new StdPlotConvertMatrix());
    rcCmdMgr.addCommand(new StdPlotInvertMatrix());
    rcCmdMgr.addCommand(new StdPlotClearTable());
    rcCmdMgr.addCommand(new StdPlotGoToCell());
    rcCmdMgr.addCommand(new StdPlotSaveNote());
    rcCmdMgr.addCommand(new StdPlotResetCameraFront());
    rcCmdMgr.addCommand(new StdPlotResetZoomFactor());
    // rcCmdMgr.addCommand(new StdPlotPlot3dModecolumnSelect());
    // rcCmdMgr.addCommand(new StdPlotPlot3dModeRowSelect());
    // rcCmdMgr.addCommand(new StdPlotPlot3dModeItemSelect());
    // rcCmdMgr.addCommand(new StdPlotPlot3dModeNoneSelect());
    // rcCmdMgr.addCommand(new StdPlotPlot3dAnimate());
    rcCmdMgr.addCommand(new StdPlotActivateWindow());

    rcCmdMgr.addCommand(new StdCmdNewTable());
    rcCmdMgr.addCommand(new StdCmdNewMatrix());
    rcCmdMgr.addCommand(new StdCmdNewScene());
    rcCmdMgr.addCommand(new StdNewGraph());
    rcCmdMgr.addCommand(new StdNew2DPlot());
    rcCmdMgr.addCommand(new StdNew3DPlot());
    rcCmdMgr.addCommand(new StdCmdNewAspects());
    rcCmdMgr.addCommand(new StdCmdScatters());

    rcCmdMgr.addCommand(new StdVerticaDropLine());
    rcCmdMgr.addCommand(new StdSpLine());
    rcCmdMgr.addCommand(new StdVerticalStep());
    rcCmdMgr.addCommand(new StdHorizontalStep());
    rcCmdMgr.addCommand(new StdLinesAndSteps());
    rcCmdMgr.addCommand(new StdVerticalAndHorizontalBars());
    rcCmdMgr.addCommand(new StdVectorPlots());
    rcCmdMgr.addCommand(new StdPiePlots());
    rcCmdMgr.addCommand(new Std3DSurfaceTools());


    rcCmdMgr.addCommand(new StdAppendNewColumnToTable());
    rcCmdMgr.addCommand(new StdShowColumnStatistics());
    rcCmdMgr.addCommand(new StdShowRowStatistics());
    rcCmdMgr.addCommand(new StdExportTableASCII());
    rcCmdMgr.addCommand(new StdImportTableASCII());
    rcCmdMgr.addCommand(new StdSaveAlphaplotData());
    rcCmdMgr.addCommand(new StdLoadAlphaplotData());

   

    rcCmdMgr.addCommand(new StdCmdPlugins());
}

} // namespace Gui
