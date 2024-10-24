/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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

#include "Workbench.h"

#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/MenuManager.h>
#include <Gui/Selection.h>
#include <Gui/ToolBarManager.h>


using namespace WebGui;

#if 0 // needed for Qt's lupdate utility
    qApp->translate("Workbench", "Navigation");
#endif

/// @namespace WebGui @class Workbench
TYPESYSTEM_SOURCE(WebGui::Workbench, Gui::StdWorkbench)

Workbench::Workbench()
{
}

Workbench::~Workbench()
{
}

void Workbench::setupContextMenu(const char* recipient,Gui::MenuItem* item) const
{
    Q_UNUSED(recipient);
    Q_UNUSED(item);
    if (strcmp(recipient,"View") == 0)
    {
        if ( Gui::Selection().countObjectsOfType(App::DocumentObject::getClassTypeId()) > 0 )
            *item << "Separator" << "Std_TreeSelection" << "Std_Delete";
    }
    else if (strcmp(recipient,"Tree") == 0)
    {
        if ( Gui::Selection().countObjectsOfType(App::DocumentObject::getClassTypeId()) > 0 )
            *item << "Std_Delete";
    }
}

Gui::MenuItem* Workbench::setupMenuBar() const
{
    return Gui::StdWorkbench::setupMenuBar();
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();

    // web navigation toolbar
    Gui::ToolBarItem* navigation = new Gui::ToolBarItem(root);
    navigation->setCommand("Navigation");
    *navigation << "Web_BrowserSetURL"
                << "Separator"
                << "Web_OpenWebsite"
                << "Separator"
                << "Web_BrowserBack"
                << "Web_BrowserNext"
                << "Web_BrowserRefresh"
                << "Web_BrowserStop"
                << "Separator"
                << "Web_BrowserZoomIn"
                << "Web_BrowserZoomOut";

    return root;

}

Gui::ToolBarItem* Workbench::setupCommandBars() const
{
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    return root;
}

Gui::DockWindowItems* Workbench::setupDockWindows() const
{
    Gui::DockWindowItems* root = Gui::StdWorkbench::setupDockWindows();
    //root->setVisibility(false); // hide all dock windows by default
    //root->setVisibility("Std_ComboView",true); // except of the combo view
    return root;
}
