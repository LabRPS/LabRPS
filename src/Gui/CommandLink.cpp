/****************************************************************************
 *   Copyright (c) 2017 Zheng Lei (realthunder) <realthunder.dev@gmail.com> *
 *                                                                          *
 *   This file is part of the LabRPS CAx development system.               *
 *                                                                          *
 *   This library is free software; you can redistribute it and/or          *
 *   modify it under the terms of the GNU Library General Public            *
 *   License as published by the Free Software Foundation; either           *
 *   version 2 of the License, or (at your option) any later version.       *
 *                                                                          *
 *   This library  is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Library General Public License for more details.                   *
 *                                                                          *
 *   You should have received a copy of the GNU Library General Public      *
 *   License along with this library; see the file COPYING.LIB. If not,     *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,          *
 *   Suite 330, Boston, MA  02111-1307, USA                                 *
 *                                                                          *
 ****************************************************************************/

#include "PreCompiled.h"

#ifndef _PreComp_
# include <sstream>
# include <QMessageBox>
#endif

#include <App/Application.h>
#include <App/Document.h>
#include <App/DocumentObject.h>
#include <App/Link.h>
#include <Base/Exception.h>

#include "Action.h"
#include "Application.h"
#include "Command.h"
#include "Document.h"
#include "MainWindow.h"
#include "Selection.h"
#include "Tree.h"
#include "ViewProviderDocumentObject.h"
#include "WaitCursor.h"


RPS_LOG_LEVEL_INIT("CommandLink", true, true)

using namespace Gui;

static void setLinkLabel(App::DocumentObject *obj, const char *doc, const char *name) {
    const char *label = obj->Label.getValue();
    Command::doCommand(Command::Doc,"App.getDocument('%s').getObject('%s').Label='%s'",doc,name,label);
}

////////////////////////////////////////////////////////////////////////////////////////////

class StdCmdLinkMakeGroup : public Gui::Command
{
public:
    StdCmdLinkMakeGroup();
    const char* className() const
    { return "StdCmdLinkMakeGroup"; }

protected:
    virtual void activated(int iMsg);
    virtual bool isActive();
    virtual Action * createAction();
    virtual void languageChange();
};

StdCmdLinkMakeGroup::StdCmdLinkMakeGroup()
  : Command("Std_LinkMakeGroup")
{
    sGroup        = "Link";
    sMenuText     = QT_TR_NOOP("Make link group");
    sToolTipText  = QT_TR_NOOP("Create a group of links");
    sWhatsThis    = "Std_LinkMakeGroup";
    sStatusTip    = sToolTipText;
    eType         = AlterDoc;
    sPixmap       = "LinkGroup";
}

bool StdCmdLinkMakeGroup::isActive() {
    return !!App::GetApplication().getActiveDocument();
}

Action * StdCmdLinkMakeGroup::createAction()
{
    ActionGroup* pcAction = new ActionGroup(this, getMainWindow());
    pcAction->setDropDownMenu(true);
    applyCommandData(this->className(), pcAction);

    // add the action items
    QAction* action = nullptr;
    action = pcAction->addAction(QObject::tr("Simple group"));
    action->setWhatsThis(QString::fromLatin1(getWhatsThis()));
    return pcAction;
}

void StdCmdLinkMakeGroup::languageChange()
{
    Command::languageChange();

    if (!_pcAction)
        return;
    ActionGroup* pcAction = qobject_cast<ActionGroup*>(_pcAction);
    QList<QAction*> acts = pcAction->actions();
    acts[0]->setText(QObject::tr("Simple group"));
}


void StdCmdLinkMakeGroup::activated(int option) {

    std::vector<App::DocumentObject*> objs;
    std::set<App::DocumentObject*> objset;

    auto doc = App::GetApplication().getActiveDocument();
    if(!doc) {
        RPS_ERR("no active document");
        return;
    }

    for(auto &sel : Selection().getCompleteSelection()) {
        if(sel.pObject && sel.pObject->getNameInDocument() &&
           objset.insert(sel.pObject).second)
            objs.push_back(sel.pObject);
    }

    Selection().selStackPush();
    Selection().clearCompleteSelection();

    Command::openCommand(QT_TRANSLATE_NOOP("Command", "Make link group"));
    try {
        std::string groupName = doc->getUniqueObjectName("LinkGroup");
        Command::doCommand(Command::Doc,
            "App.getDocument('%s').addObject('App::LinkGroup','%s')",doc->getName(),groupName.c_str());
        if(objs.empty()) {
            Selection().addSelection(doc->getName(),groupName.c_str());
            Selection().selStackPush();
        }else{
            Command::doCommand(Command::Doc,"__objs__ = []");
            for(auto obj : objs) {
                std::string name;
                if(option!=0 || doc!=obj->getDocument()) {
                    name = doc->getUniqueObjectName("Link");
                    Command::doCommand(Command::Doc,
                        "App.getDocument('%s').addObject('App::Link','%s').setLink("
                            "App.getDocument('%s').getObject('%s'))",
                        doc->getName(),name.c_str(),obj->getDocument()->getName(),obj->getNameInDocument());
                    setLinkLabel(obj,doc->getName(),name.c_str());
                    if(option==2)
                        Command::doCommand(Command::Doc,
                            "App.getDocument('%s').getObject('%s').LinkTransform = True",
                            doc->getName(),name.c_str());
                    else if(obj->getPropertyByName("Placement"))
                        Command::doCommand(Command::Doc,
                            "App.getDocument('%s').getObject('%s').Placement = "
                                "App.getDocument('%s').getObject('%s').Placement",
                            doc->getName(),name.c_str(),obj->getDocument()->getName(),obj->getNameInDocument());
                }else
                    name = obj->getNameInDocument();
                Command::doCommand(Command::Doc,"__objs__.append(App.getDocument('%s').getObject('%s'))",
                        doc->getName(),name.c_str());
                Command::doCommand(Command::Doc,
                        "App.getDocument('%s').getObject('%s').ViewObject.Visibility=False",
                        doc->getName(),name.c_str());
            }
            Command::doCommand(Command::Doc,"App.getDocument('%s').getObject('%s').setLink(__objs__)",
                    doc->getName(),groupName.c_str());
            Command::doCommand(Command::Doc,"del __objs__");

            for(size_t i=0;i<objs.size();++i) {
                auto name = std::to_string(i)+".";
                Selection().addSelection(doc->getName(),groupName.c_str(),name.c_str());
            }
            Selection().selStackPush();
        }
        if(option!=0) {
            Command::doCommand(Command::Doc,
                    "App.getDocument('%s').getObject('%s').LinkMode = 'Auto Delete'",
                    doc->getName(),groupName.c_str());
        }
        Command::commitCommand();
    } catch (const Base::Exception& e) {
        QMessageBox::critical(getMainWindow(), QObject::tr("Create link group failed"),
            QString::fromLatin1(e.what()));
        Command::abortCommand();
        e.ReportException();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

//===========================================================================
// Instantiation
//===========================================================================


namespace Gui {

void CreateLinkCommands()
{
    CommandManager &rcCmdMgr = Application::Instance->commandManager();
    rcCmdMgr.addCommand(new StdCmdLinkMakeGroup());
}

} // namespace Gui

