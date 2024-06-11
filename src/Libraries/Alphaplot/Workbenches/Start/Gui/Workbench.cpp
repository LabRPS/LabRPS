/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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
# include <QCoreApplication>
#endif

#include "Workbench.h"

#include <Base/Console.h>
#include <Base/Exception.h>
#include <Base/Tools.h>

#include <Gui/ToolBarManager.h>
#include <Gui/DockWindowManager.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/MainWindow.h>
#include <Gui/MDIView.h>


using namespace StartGui;

TYPESYSTEM_SOURCE(StartGui::Workbench, Gui::StdWorkbench)

StartGui::Workbench::Workbench()
{
}

StartGui::Workbench::~Workbench()
{
}

void StartGui::Workbench::activated()
{
    // Automatically display the StartPage only the very first time
    static bool first = true;
    if (first) {
        loadStartPage();
        first = false;
    }
}

void StartGui::Workbench::loadStartPage()
{
    // Ensure that we don't open the Start page multiple times
    QString title = QCoreApplication::translate("Workbench", "Start page");
    QList<QWidget*> ch = Gui::getMainWindow()->windows();
    for (QList<QWidget*>::const_iterator c = ch.cbegin(); c != ch.cend(); ++c) {
        if ((*c)->windowTitle() == title) {
            Gui::MDIView* mdi = qobject_cast<Gui::MDIView*>((*c));
            if (mdi)
                Gui::getMainWindow()->setActiveWindow(mdi);
            return;
        }
    }

    try {
        QByteArray utf8Title = title.toUtf8();
        std::string escapedstr = Base::Tools::escapedUnicodeFromUtf8(utf8Title);
        std::stringstream str;
       
    }
    catch (const Base::Exception& e) {
        Base::Console().Error("%s\n", e.what());
    }
}

void StartGui::Workbench::setupContextMenu(const char* recipient, Gui::MenuItem* item) const
{
    Q_UNUSED(recipient);
    Q_UNUSED(item);
}

Gui::MenuItem* StartGui::Workbench::setupMenuBar() const
{
    return Gui::StdWorkbench::setupMenuBar();
}

Gui::ToolBarItem* StartGui::Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();

    //// web navigation toolbar
    //Gui::ToolBarItem* navigation = new Gui::ToolBarItem(root);
    //navigation->setCommand("Navigation");
    //*navigation << "Web_BrowserSetURL"
    //            << "Separator"
    //            << "Web_OpenWebsite"
    //            << "Start_StartPage"
    //            << "Separator"
    //            << "Web_BrowserBack"
    //            << "Web_BrowserNext"
    //            << "Web_BrowserRefresh"
    //            << "Web_BrowserStop"
    //            << "Separator"
    //            << "Web_BrowserZoomIn"
    //            << "Web_BrowserZoomOut";

    return root;

}

Gui::ToolBarItem* StartGui::Workbench::setupCommandBars() const
{
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    return root;
}

Gui::DockWindowItems* StartGui::Workbench::setupDockWindows() const
{
    Gui::DockWindowItems* root = Gui::StdWorkbench::setupDockWindows();
    root->setVisibility(false); // hide all dock windows by default
    root->setVisibility("Std_ComboView",true); // except of the combo view
    return root;
}
