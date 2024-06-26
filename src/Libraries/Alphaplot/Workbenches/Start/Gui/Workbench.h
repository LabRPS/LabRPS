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


#ifndef STARTGUI_WORKBENCH_H
#define STARTGUI_WORKBENCH_H

#include <Gui/Workbench.h>

namespace StartGui {

/**
 * @author Werner Mayer
 */
class Workbench : public Gui::StdWorkbench
{
    TYPESYSTEM_HEADER();

public:
    Workbench();
    virtual ~Workbench();

    /** Defines the standard context menu. */
    virtual void setupContextMenu(const char* recipient,Gui::MenuItem*) const;
    /** Run some actions when the workbench gets activated. */
    virtual void activated();

    static void loadStartPage();

    const char* getClassName() const {
        return "StartGui::Workbench";
    }

    QString getToolTip() const
    {
        return QString::fromLatin1("Start workbench");
    }

    QString getMenuText() const
    {
        return QString::fromLatin1("Start");
    }

protected:
    /** Defines the standard menus. */
    virtual Gui::MenuItem* setupMenuBar() const;
    /** Defines the standard toolbars. */
    virtual Gui::ToolBarItem* setupToolBars() const;
    /** Defines the standard command bars. */
    virtual Gui::ToolBarItem* setupCommandBars() const;
    /** Returns a DockWindowItems structure of dock windows this workbench. */
    virtual Gui::DockWindowItems* setupDockWindows() const;

}; // namespace StartGui

}
#endif // START_WORKBENCH_H
