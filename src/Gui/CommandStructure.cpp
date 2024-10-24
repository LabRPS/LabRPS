/***************************************************************************
 *   Copyright (c) 2017 Stefan Tröger <stefantroeger@gmx.net>              *
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
#include <QApplication>
#endif

#include "App/Document.h"

#include "Command.h"
#include "ActiveObjectList.h"
#include "Application.h"
#include "Document.h"
#include "ViewProviderDocumentObject.h"


using namespace Gui;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// Std_Group
//===========================================================================
DEF_STD_CMD_A(StdCmdGroup)

StdCmdGroup::StdCmdGroup()
  : Command("Std_Group")
{
    sGroup        = "Structure";
    sMenuText     = QT_TR_NOOP("Create group");
    sToolTipText  = QT_TR_NOOP("Create a new group for ordering objects");
    sWhatsThis    = "Std_Group";
    sStatusTip    = sToolTipText;
    sPixmap       = "folder";
}

void StdCmdGroup::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    openCommand(QT_TRANSLATE_NOOP("Command", "Add a group"));

    std::string GroupName;
    GroupName = getUniqueObjectName("Group");
    QString label = QApplication::translate("Std_Group", "Group");
    doCommand(Doc,"App.activeDocument().Tip = App.activeDocument().addObject('App::DocumentObjectGroup','%s')",GroupName.c_str());
    doCommand(Doc,"App.activeDocument().%s.Label = '%s'", GroupName.c_str(),
              label.toUtf8().data());
    commitCommand();

    Gui::Document* gui = Application::Instance->activeDocument();
    App::Document* app = gui->getDocument();
    ViewProvider* vp = gui->getViewProvider(app->getActiveObject());
    if (vp && vp->getTypeId().isDerivedFrom(ViewProviderDocumentObject::getClassTypeId()))
        gui->signalScrollToObject(*static_cast<ViewProviderDocumentObject*>(vp));
}

bool StdCmdGroup::isActive()
{
    return hasActiveDocument();
}

namespace Gui {

void CreateStructureCommands()
{
    CommandManager &rcCmdMgr = Application::Instance->commandManager();
    rcCmdMgr.addCommand(new StdCmdGroup());
}

} // namespace Gui
