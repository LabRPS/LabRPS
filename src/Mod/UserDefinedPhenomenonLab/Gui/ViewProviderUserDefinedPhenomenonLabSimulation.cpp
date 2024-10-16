/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>          *
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
# include <boost_bind_bind.hpp>
# include <QAction>
# include <QApplication>
# include <QMenu>
# include <QMessageBox>
# include <QTextStream>
#endif

#include <App/TextDocument.h>
#include <Gui/ActionFunction.h>
#include "ViewProviderUserDefinedPhenomenonLabSimulation.h"
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/MainWindow.h>

#include <Mod/UserDefinedPhenomenonLab/Gui/UserDefinedPhenomenonLabSimulationObserver.h>
#include <App/Simulation.h>
#include <Mod/UserDefinedPhenomenonLab/App/UserDefinedPhenomenonLabSimulation.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/UserDefinedPhenomenonLabFeature.h>
#include <Gui/Document.h>
#include <Gui/Application.h>
#include <App/Document.h>
#include "Control.h"
#include "ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod.h"
#include <Mod/UserDefinedPhenomenonLabAPI/App/UserDefinedPhenomenonLabFeatureSimulationMethod.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <Gui/Command.h>
#include <App/AutoTransaction.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/IrpsULSimulationMethod.h>

using namespace UserDefinedPhenomenonLabGui;
using namespace Gui;

// ----------------------------------------------------------------------------

/* TRANSLATOR UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabSimulation */

PROPERTY_SOURCE(UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabSimulation, Gui::ViewProviderDocumentObjectGroup)


ViewProviderUserDefinedPhenomenonLabSimulation::ViewProviderUserDefinedPhenomenonLabSimulation()
{
    sPixmap = "UserDefinedPhenomenonLab_NewSimulation";
}

ViewProviderUserDefinedPhenomenonLabSimulation::~ViewProviderUserDefinedPhenomenonLabSimulation()
{

}

void ViewProviderUserDefinedPhenomenonLabSimulation::attach(App::DocumentObject* obj)
{
    Gui::ViewProviderDocumentObjectGroup::attach(obj);
}

void ViewProviderUserDefinedPhenomenonLabSimulation::highlightView(Gui::ViewProviderDocumentObject* view)
{
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::doubleClicked(void)
{
    Gui::Command::assureWorkbench("UserDefinedPhenomenonLabWorkbench");
    Gui::Command::addModule(Gui::Command::Gui, "UserDefinedPhenomenonLabGui");
    Gui::Command::doCommand(Gui::Command::Gui,
                            "UserDefinedPhenomenonLabGui.setActiveSimulation(App.activeDocument().%s)",
                            this->getObject()->getNameInDocument());
    Gui::Command::doCommand(Gui::Command::Gui, "Gui.Selection.clearSelection()");
    std::vector<App::DocumentObject*> selVector {};
    selVector.push_back(this->getObject());
    auto *docName = this->getObject()->getDocument()->getName();
    Gui::Selection().setSelection(docName, selVector);
    return true;
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::run()
{
     UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim = static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    auto activeMethod = sim->getActiveSimulationMethod();

    //UserDefinedPhenomenonLabAPI::IrpsWLSimuMethod* activeSimMethod = static_cast<UserDefinedPhenomenonLabAPI::IrpsWLSimuMethod*>(sim->getActiveSimulationMethod());
    if (!activeMethod) {
        return false;
    }
    UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod* vp = dynamic_cast<UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod*>(Gui::Application::Instance->getViewProvider(activeMethod));

    if (!vp) {
        return false;
    }

    vp->simulate();

    return true;
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::stop()
{
     UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim = static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    //get the corresponding view provider
    UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod* vp = dynamic_cast<UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod*>(Gui::Application::Instance->getViewProvider(sim));

    vp->stop();

    return true;
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::activateSimulation() { return doubleClicked(); }

std::vector<App::DocumentObject*> ViewProviderUserDefinedPhenomenonLabSimulation::claimChildren(void)const
{
    return Gui::ViewProviderDocumentObjectGroup::claimChildren();
}

std::vector<std::string> ViewProviderUserDefinedPhenomenonLabSimulation::getDisplayModes(void) const
{
    return { "UserDefinedPhenomenonLabSimulation" };
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::refresh() {
    std::vector<App::Simulation*> sims = UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(*it)->resetAllEnums();
    }

    Gui::Document* doc = Gui::Application::Instance->activeDocument();
    if (doc) {
        Gui::View3DInventor* view = static_cast<Gui::View3DInventor*>(doc->getActiveView());
        Gui::View3DInventorViewer* viewer = view->getViewer();
        viewer->viewAll();
    }

	App::AutoTransaction trans("Recompute");
    Command::doCommand(Command::Doc, "App.getDocument(\"%s\").recompute()", doc->getDocument()->getName());

    return true;
}

void ViewProviderUserDefinedPhenomenonLabSimulation::hide(void)
{
    Gui::ViewProviderDocumentObjectGroup::hide();
}

void ViewProviderUserDefinedPhenomenonLabSimulation::show(void)
{
    Gui::ViewProviderDocumentObjectGroup::show();
}

void ViewProviderUserDefinedPhenomenonLabSimulation::setupContextMenu(QMenu* menu, QObject* , const char* )
{
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* act = menu->addAction(QString::fromLatin1("Activate Simulation"));
    func->trigger(act, boost::bind(&ViewProviderUserDefinedPhenomenonLabSimulation::doubleClicked, this));

    QAction* run = menu->addAction(QString::fromLatin1("Run"));
    func->trigger(run, boost::bind(&ViewProviderUserDefinedPhenomenonLabSimulation::run, this));

    QAction* stop = menu->addAction(QString::fromLatin1("Stop"));
    func->trigger(stop, boost::bind(&ViewProviderUserDefinedPhenomenonLabSimulation::stop, this));

     QAction* refresh = menu->addAction(QString::fromLatin1("Refresh"));
    func->trigger(refresh, boost::bind(&ViewProviderUserDefinedPhenomenonLabSimulation::refresh, this));
}


bool ViewProviderUserDefinedPhenomenonLabSimulation::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default ) {        
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObjectGroup::setEdit(ModNum);
    }
}

void ViewProviderUserDefinedPhenomenonLabSimulation::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObjectGroup::unsetEdit(ModNum);
    }
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::canDragObjects() const
{
    return true;
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::canDragObject(App::DocumentObject* obj) const
{
     if (!obj)
        return false;

    if (obj->getTypeId().isDerivedFrom( UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeatureSimulationMethod::getClassTypeId())) 
        return true;
    else if (obj->getTypeId().isDerivedFrom(Base::Type::fromName("App::FeaturePython")))
        return true;
    else if (obj->getTypeId().isDerivedFrom(App::TextDocument::getClassTypeId()))
        return true;
    else
        return false;
}

void ViewProviderUserDefinedPhenomenonLabSimulation::dragObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dragObject(obj);
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::canDropObjects() const
{
    return true;
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::canDropObject(App::DocumentObject* obj) const
{
    return canDragObject(obj);
}

void ViewProviderUserDefinedPhenomenonLabSimulation::dropObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dropObject(obj);
   
    std::vector<App::Simulation*> sims = UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(*it)->resetAllEnums();
    }
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::onDelete(const std::vector<std::string>&)
{
    // warn the user if the object has unselected children
    auto objs = claimChildren();
    return checkSelectedChildren(objs, this->getDocument(), "UserDefinedPhenomenonLab simulation");
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::canDelete(App::DocumentObject* obj) const
{
    // deletions of objects from a UserDefinedPhenomenonLabSimulation don't necessarily destroy anything
    // thus we can pass this action
    // we can warn the user if necessary in the object's ViewProvider in the onDelete() function
    Q_UNUSED(obj)
    return true;
}

bool ViewProviderUserDefinedPhenomenonLabSimulation::checkSelectedChildren(const std::vector<App::DocumentObject*> objs,
                                                    Gui::Document* docGui, std::string objectName)
{
    // warn the user if the object has unselected children
    if (!objs.empty()) {
        // check if all children are in the selection
        bool found = false;
        auto selectionList = Gui::Selection().getSelectionEx(docGui->getDocument()->getName());
        for (auto child : objs) {
            found = false;
            for (Gui::SelectionObject selection : selectionList) {
                if (std::string(child->getNameInDocument())
                    == std::string(selection.getFeatName())) {
                    found = true;
                    break;
                }
            }
            if (!found)
                break;
        }
        if (found)// all children are selected too
            return true;

        // generate dialog
        QString bodyMessage;
        QTextStream bodyMessageStream(&bodyMessage);
        bodyMessageStream << qApp->translate("Std_Delete",
            ("The " + objectName + " is not empty, therefore the\nfollowing "
             "referencing objects might be lost:").c_str());
        bodyMessageStream << '\n';
        for (auto ObjIterator : objs)
            bodyMessageStream << '\n' << QString::fromUtf8(ObjIterator->Label.getValue());
        bodyMessageStream << "\n\n" << QObject::tr("Are you sure you want to continue?");
        // show and evaluate the dialog
        int DialogResult = QMessageBox::warning(Gui::getMainWindow(),
            qApp->translate("Std_Delete", "Object dependencies"), bodyMessage,
            QMessageBox::Yes, QMessageBox::No);
        if (DialogResult == QMessageBox::Yes)
            return true;
        else
            return false;
    }
    else {
        return true;
    }
}
