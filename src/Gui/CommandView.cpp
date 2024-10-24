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
# include <sstream>
# include <QApplication>
# include <QDialog>
# include <QDomDocument>
# include <QDomElement>
# include <QFile>
# include <QFileInfo>
# include <QFont>
# include <QFontMetrics>
# include <QMessageBox>
# include <QPainter>
# include <QPointer>
# include <QTextStream>
# include <boost_bind_bind.hpp>
#endif

#include <App/Document.h>
#include <App/DocumentObject.h>
#include <App/RPSFeature.h>
//#include <App/GeoFeatureGroupExtension.h>
#include <Base/Console.h>
#include <Base/Parameter.h>

#include "Command.h"
#include "Action.h"
#include "Application.h"
#include "BitmapFactory.h"
#include "Control.h"
#include "DlgDisplayPropertiesImp.h"
#include "DlgSettingsImageImp.h"
#include "Document.h"
#include "FileDialog.h"
#include "Macro.h"
#include "MainWindow.h"
#include "Selection.h"
#include "SelectionObject.h""
#include "Tools.h"
#include "Tree.h"
#include "Utilities.h"
#include "ViewParams.h"
#include "WaitCursor.h"
#include "MDIView.h"
#include "ViewProviderDocumentObject.h"


using namespace Gui;
using Gui::Dialog::DlgSettingsImageImp;
namespace bp = boost::placeholders;

namespace {
// A helper class to open a transaction when changing properties of view providers.
// It uses the same parameter key as the PropertyView to control the behaviour.
class TransactionView {
    Gui::Document* document;

public:
    static bool getDefault() {
        auto hGrp = App::GetApplication().GetParameterGroupByPath(
                "User parameter:BaseApp/Preferences/PropertyView");
        return hGrp->GetBool("AutoTransactionView", false);
    }
    TransactionView(Gui::Document* doc, const char* name, bool enable = getDefault())
        : document(doc)
    {
        if (document && enable) {
            document->openCommand(name);
        }
        else {
            document = nullptr;
        }
    }

    ~TransactionView() {
        if (document) {
            document->commitCommand();
        }
    }
};
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// Std_MainFullscreen
//===========================================================================
DEF_STD_CMD(StdMainFullscreen)

StdMainFullscreen::StdMainFullscreen()
  : Command("Std_MainFullscreen")
{
    sGroup       = "Standard-View";
    sMenuText    = QT_TR_NOOP("Fullscreen");
    sToolTipText = QT_TR_NOOP("Display the main window in fullscreen mode");
    sWhatsThis   = "Std_MainFullscreen";
    sStatusTip   = QT_TR_NOOP("Display the main window in fullscreen mode");
    sPixmap      = "view-fullscreen";
    sAccel       = "Alt+F11";
    eType        = Alter3DView;
}

void StdMainFullscreen::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    MDIView* view = getMainWindow()->activeWindow();

    if (view)
        view->setCurrentViewMode(MDIView::Child);

    if (getMainWindow()->isFullScreen())
        getMainWindow()->showNormal();
    else
        getMainWindow()->showFullScreen();
}

//===========================================================================
// Std_TreeSelection
//===========================================================================

DEF_STD_CMD(StdTreeSelection)

StdTreeSelection::StdTreeSelection()
  : Command("Std_TreeSelection")
{
    sGroup        = "TreeView";
    sMenuText     = QT_TR_NOOP("Go to selection");
    sToolTipText  = QT_TR_NOOP("Scroll to first selected item");
    sWhatsThis    = "Std_TreeSelection";
    sStatusTip    = QT_TR_NOOP("Scroll to first selected item");
    eType         = Alter3DView;
    sPixmap       = "tree-goto-sel";
    sAccel        = "T,G";
}

void StdTreeSelection::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    TreeWidget::scrollItemToTop();
}

//===========================================================================
// Std_TreeCollapse
//===========================================================================

DEF_STD_CMD(StdCmdTreeCollapse)

StdCmdTreeCollapse::StdCmdTreeCollapse()
  : Command("Std_TreeCollapse")
{
    sGroup        = "View";
    sMenuText     = QT_TR_NOOP("Collapse selected item");
    sToolTipText  = QT_TR_NOOP("Collapse currently selected tree items");
    sWhatsThis    = "Std_TreeCollapse";
    sStatusTip    = QT_TR_NOOP("Collapse currently selected tree items");
    eType         = Alter3DView;
}

void StdCmdTreeCollapse::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    QList<TreeWidget*> tree = Gui::getMainWindow()->findChildren<TreeWidget*>();
    for (QList<TreeWidget*>::iterator it = tree.begin(); it != tree.end(); ++it)
        (*it)->expandSelectedItems(TreeItemMode::CollapseItem);
}

//===========================================================================
// Std_TreeExpand
//===========================================================================

DEF_STD_CMD(StdCmdTreeExpand)

StdCmdTreeExpand::StdCmdTreeExpand()
  : Command("Std_TreeExpand")
{
    sGroup        = "View";
    sMenuText     = QT_TR_NOOP("Expand selected item");
    sToolTipText  = QT_TR_NOOP("Expand currently selected tree items");
    sWhatsThis    = "Std_TreeExpand";
    sStatusTip    = QT_TR_NOOP("Expand currently selected tree items");
    eType         = Alter3DView;
}

void StdCmdTreeExpand::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    QList<TreeWidget*> tree = Gui::getMainWindow()->findChildren<TreeWidget*>();
    for (QList<TreeWidget*>::iterator it = tree.begin(); it != tree.end(); ++it)
        (*it)->expandSelectedItems(TreeItemMode::ExpandItem);
}

//===========================================================================
// Std_TreeSelectAllInstance
//===========================================================================

DEF_STD_CMD_A(StdCmdTreeSelectAllInstances)

StdCmdTreeSelectAllInstances::StdCmdTreeSelectAllInstances()
  : Command("Std_TreeSelectAllInstances")
{
    sGroup        = "View";
    sMenuText     = QT_TR_NOOP("Select all instances");
    sToolTipText  = QT_TR_NOOP("Select all instances of the current selected object");
    sWhatsThis    = "Std_TreeSelectAllInstances";
    sStatusTip    = QT_TR_NOOP("Select all instances of the current selected object");
    sPixmap       = "sel-instance";
    eType         = AlterSelection;
}

bool StdCmdTreeSelectAllInstances::isActive()
{
    const auto &sels = Selection().getSelectionEx("*",App::DocumentObject::getClassTypeId(), ResolveMode::OldStyleElement, true);
    if(sels.empty())
        return false;
    auto obj = sels[0].getObject();
    if(!obj || !obj->getNameInDocument())
        return false;
    return dynamic_cast<ViewProviderDocumentObject*>(
            Application::Instance->getViewProvider(obj))!=nullptr;
}

void StdCmdTreeSelectAllInstances::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    const auto &sels = Selection().getSelectionEx("*",App::DocumentObject::getClassTypeId(), ResolveMode::OldStyleElement, true);
    if(sels.empty())
        return;
    auto obj = sels[0].getObject();
    if(!obj || !obj->getNameInDocument())
        return;
    auto vpd = dynamic_cast<ViewProviderDocumentObject*>(
            Application::Instance->getViewProvider(obj));
    if(!vpd)
        return;
    Selection().selStackPush();
    Selection().clearCompleteSelection();
    for(auto tree : getMainWindow()->findChildren<TreeWidget*>())
        tree->selectAllInstances(*vpd);
    Selection().selStackPush();
}

//===========================================================================
// Std_SelBack
//===========================================================================

DEF_STD_CMD_A(StdCmdSelBack)

StdCmdSelBack::StdCmdSelBack()
  :Command("Std_SelBack")
{
  sGroup        = "View";
  sMenuText     = QT_TR_NOOP("&Back");
  sToolTipText  = QT_TR_NOOP("Go back to previous selection");
  sWhatsThis    = "Std_SelBack";
  sStatusTip    = QT_TR_NOOP("Go back to previous selection");
  sPixmap       = "sel-back";
  sAccel        = "S, B";
  eType         = AlterSelection;
}

void StdCmdSelBack::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Selection().selStackGoBack();
}

bool StdCmdSelBack::isActive()
{
  return Selection().selStackBackSize()>1;
}

//===========================================================================
// Std_SelForward
//===========================================================================

DEF_STD_CMD_A(StdCmdSelForward)

StdCmdSelForward::StdCmdSelForward()
  :Command("Std_SelForward")
{
  sGroup        = "View";
  sMenuText     = QT_TR_NOOP("&Forward");
  sToolTipText  = QT_TR_NOOP("Repeat the backed selection");
  sWhatsThis    = "Std_SelForward";
  sStatusTip    = QT_TR_NOOP("Repeat the backed selection");
  sPixmap       = "sel-forward";
  sAccel        = "S, F";
  eType         = AlterSelection;
}

void StdCmdSelForward::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    Selection().selStackGoForward();
}

bool StdCmdSelForward::isActive()
{
  return !!Selection().selStackForwardSize();
}

//=======================================================================
// Std_TreeSingleDocument
//===========================================================================
#define TREEVIEW_DOC_CMD_DEF(_name,_v) \
DEF_STD_CMD_AC(StdTree##_name) \
void StdTree##_name::activated(int){ \
    TreeParams::Instance()->setDocumentMode(_v);\
    if(_pcAction) _pcAction->setChecked(true,true);\
}\
Action * StdTree##_name::createAction(void) {\
    Action *pcAction = Command::createAction();\
    pcAction->setCheckable(true);\
    pcAction->setIcon(QIcon());\
    _pcAction = pcAction;\
    isActive();\
    return pcAction;\
}\
bool StdTree##_name::isActive() {\
    bool checked = TreeParams::Instance()->DocumentMode()==_v;\
    if(_pcAction && _pcAction->isChecked()!=checked)\
        _pcAction->setChecked(checked,true);\
    return true;\
}

TREEVIEW_DOC_CMD_DEF(SingleDocument,0)

StdTreeSingleDocument::StdTreeSingleDocument()
  : Command("Std_TreeSingleDocument")
{
    sGroup       = "TreeView";
    sMenuText    = QT_TR_NOOP("Single document");
    sToolTipText = QT_TR_NOOP("Only display the active document in the tree view");
    sWhatsThis   = "Std_TreeSingleDocument";
    sStatusTip   = QT_TR_NOOP("Only display the active document in the tree view");
    sPixmap      = "tree-doc-single";
    eType        = 0;
}

//===========================================================================
// Std_TreeMultiDocument
//===========================================================================
TREEVIEW_DOC_CMD_DEF(MultiDocument,1)

StdTreeMultiDocument::StdTreeMultiDocument()
  : Command("Std_TreeMultiDocument")
{
    sGroup       = "TreeView";
    sMenuText    = QT_TR_NOOP("Multi document");
    sToolTipText = QT_TR_NOOP("Display all documents in the tree view");
    sWhatsThis   = "Std_TreeMultiDocument";
    sStatusTip   = QT_TR_NOOP("Display all documents in the tree view");
    sPixmap      = "tree-doc-multi";
    eType        = 0;
}

//===========================================================================
// Std_TreeCollapseDocument
//===========================================================================
TREEVIEW_DOC_CMD_DEF(CollapseDocument,2)

StdTreeCollapseDocument::StdTreeCollapseDocument()
  : Command("Std_TreeCollapseDocument")
{
    sGroup       = "TreeView";
    sMenuText    = QT_TR_NOOP("Collapse/Expand");
    sToolTipText = QT_TR_NOOP("Expand active document and collapse all others");
    sWhatsThis   = "Std_TreeCollapseDocument";
    sStatusTip   = QT_TR_NOOP("Expand active document and collapse all others");
    sPixmap      = "tree-doc-collapse";
    eType        = 0;
}

//===========================================================================
// Std_TreeSyncView
//===========================================================================
#define TREEVIEW_CMD_DEF(_name) \
DEF_STD_CMD_AC(StdTree##_name) \
void StdTree##_name::activated(int){ \
    auto checked = !TreeParams::Instance()->_name();\
    TreeParams::Instance()->set##_name(checked);\
    if(_pcAction) _pcAction->setChecked(checked,true);\
}\
Action * StdTree##_name::createAction(void) {\
    Action *pcAction = Command::createAction();\
    pcAction->setCheckable(true);\
    pcAction->setIcon(QIcon());\
    _pcAction = pcAction;\
    isActive();\
    return pcAction;\
}\
bool StdTree##_name::isActive() {\
    bool checked = TreeParams::Instance()->_name();\
    if(_pcAction && _pcAction->isChecked()!=checked)\
        _pcAction->setChecked(checked,true);\
    return true;\
}

TREEVIEW_CMD_DEF(SyncView)

StdTreeSyncView::StdTreeSyncView()
  : Command("Std_TreeSyncView")
{
    sGroup       = "TreeView";
    sMenuText    = QT_TR_NOOP("Sync view");
    sToolTipText = QT_TR_NOOP("Auto switch to the 3D view containing the selected item");
    sStatusTip   = sToolTipText;
    sWhatsThis   = "Std_TreeSyncView";
    sPixmap      = "tree-sync-view";
    sAccel       = "T,1";
    eType        = 0;
}

//===========================================================================
// Std_TreeSyncSelection
//===========================================================================
TREEVIEW_CMD_DEF(SyncSelection)

StdTreeSyncSelection::StdTreeSyncSelection()
  : Command("Std_TreeSyncSelection")
{
    sGroup       = "TreeView";
    sMenuText    = QT_TR_NOOP("Sync selection");
    sToolTipText = QT_TR_NOOP("Auto expand tree item when the corresponding object is selected in 3D view");
    sStatusTip   = sToolTipText;
    sWhatsThis   = "Std_TreeSyncSelection";
    sPixmap      = "tree-sync-sel";
    sAccel       = "T,2";
    eType        = 0;
}

//===========================================================================
// Std_TreeSyncPlacement
//===========================================================================
TREEVIEW_CMD_DEF(SyncPlacement)

StdTreeSyncPlacement::StdTreeSyncPlacement()
  : Command("Std_TreeSyncPlacement")
{
    sGroup       = "TreeView";
    sMenuText    = QT_TR_NOOP("Sync placement");
    sToolTipText = QT_TR_NOOP("Auto adjust placement on drag and drop objects across coordinate systems");
    sStatusTip   = sToolTipText;
    sWhatsThis   = "Std_TreeSyncPlacement";
    sPixmap      = "tree-sync-pla";
    sAccel       = "T,3";
    eType        = 0;
}

//===========================================================================
// Std_TreePreSelection
//===========================================================================
TREEVIEW_CMD_DEF(PreSelection)

StdTreePreSelection::StdTreePreSelection()
  : Command("Std_TreePreSelection")
{
    sGroup       = "TreeView";
    sMenuText    = QT_TR_NOOP("Pre-selection");
    sToolTipText = QT_TR_NOOP("Preselect the object in 3D view when mouse over the tree item");
    sStatusTip   = sToolTipText;
    sWhatsThis   = "Std_TreePreSelection";
    sPixmap      = "tree-pre-sel";
    sAccel       = "T,4";
    eType        = 0;
}

//===========================================================================
// Std_TreeRecordSelection
//===========================================================================
TREEVIEW_CMD_DEF(RecordSelection)

StdTreeRecordSelection::StdTreeRecordSelection()
  : Command("Std_TreeRecordSelection")
{
    sGroup       = "TreeView";
    sMenuText    = QT_TR_NOOP("Record selection");
    sToolTipText = QT_TR_NOOP("Record selection in tree view in order to go back/forward using navigation button");
    sStatusTip   = sToolTipText;
    sWhatsThis   = "Std_TreeRecordSelection";
    sPixmap      = "tree-rec-sel";
    sAccel       = "T,5";
    eType        = 0;
}

//===========================================================================
// Std_TreeDrag
//===========================================================================
DEF_STD_CMD(StdTreeDrag)

StdTreeDrag::StdTreeDrag()
  : Command("Std_TreeDrag")
{
    sGroup       = "TreeView";
    sMenuText    = QT_TR_NOOP("Initiate dragging");
    sToolTipText = QT_TR_NOOP("Initiate dragging of current selected tree items");
    sStatusTip   = sToolTipText;
    sWhatsThis   = "Std_TreeDrag";
    sPixmap      = "tree-item-drag";
    sAccel       = "T,D";
    eType        = 0;
}

void StdTreeDrag::activated(int)
{
    if(Gui::Selection().hasSelection()) {
        for(auto tree : getMainWindow()->findChildren<TreeWidget*>()) {
            if(tree->isVisible()) {
                tree->startDragging();
                break;
            }
        }
    }
}

//======================================================================
// Std_TreeViewActions
//===========================================================================
//
class StdCmdTreeViewActions : public GroupCommand
{
public:
    StdCmdTreeViewActions()
        :GroupCommand("Std_TreeViewActions")
    {
        sGroup        = "TreeView";
        sMenuText     = QT_TR_NOOP("TreeView actions");
        sToolTipText  = QT_TR_NOOP("TreeView behavior options and actions");
        sWhatsThis    = "Std_TreeViewActions";
        sStatusTip    = QT_TR_NOOP("TreeView behavior options and actions");
        eType         = 0;
        bCanLog       = false;

        addCommand(new StdTreeSyncView());
        addCommand(new StdTreeSyncSelection());
        addCommand(new StdTreeSyncPlacement());
        addCommand(new StdTreePreSelection());
        addCommand(new StdTreeRecordSelection());

        addCommand();

        addCommand(new StdTreeSingleDocument());
        addCommand(new StdTreeMultiDocument());
        addCommand(new StdTreeCollapseDocument());

        addCommand();

        addCommand(new StdTreeDrag(),cmds.size());
        addCommand(new StdTreeSelection(),cmds.size());
    }
    virtual const char* className() const {return "StdCmdTreeViewActions";}
};

//===========================================================================
// Instantiation
//===========================================================================


namespace Gui {

void CreateViewStdCommands()
{
    CommandManager &rcCmdMgr = Application::Instance->commandManager();

    // views
    rcCmdMgr.addCommand(new StdMainFullscreen());
    rcCmdMgr.addCommand(new StdCmdTreeExpand());
    rcCmdMgr.addCommand(new StdCmdTreeCollapse());
    rcCmdMgr.addCommand(new StdCmdTreeSelectAllInstances());
    rcCmdMgr.addCommand(new StdCmdSelBack());
    rcCmdMgr.addCommand(new StdCmdSelForward());
    rcCmdMgr.addCommand(new StdCmdTreeViewActions());


    auto hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/View");
    if(hGrp->GetASCII("GestureRollFwdCommand").empty())
        hGrp->SetASCII("GestureRollFwdCommand","Std_SelForward");
    if(hGrp->GetASCII("GestureRollBackCommand").empty())
        hGrp->SetASCII("GestureRollBackCommand","Std_SelBack");
}

} // namespace Gui
