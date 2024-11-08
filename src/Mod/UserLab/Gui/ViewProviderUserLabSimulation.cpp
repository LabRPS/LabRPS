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
#include "ViewProviderUserLabSimulation.h"
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/MainWindow.h>

#include <Mod/UserLab/Gui/UserLabSimulationObserver.h>
#include <App/Simulation.h>
#include <Mod/UserLab/App/UserLabSimulation.h>
#include <Mod/UserLabAPI/App/UserLabFeature.h>
#include <Gui/Document.h>
#include <Gui/Application.h>
#include <App/Document.h>
#include "Control.h"
#include "ViewProviderUserLabFeatureSimulationMethod.h"
#include <Mod/UserLabAPI/App/UserLabFeatureSimulationMethod.h>
#include <Gui/Command.h>
#include <App/AutoTransaction.h>
#include <Mod/UserLabAPI/App/IrpsULSimulationMethod.h>

using namespace UserLabGui;
using namespace Gui;

// ----------------------------------------------------------------------------

/* TRANSLATOR UserLabGui::ViewProviderUserLabSimulation */

PROPERTY_SOURCE(UserLabGui::ViewProviderUserLabSimulation, Gui::ViewProviderDocumentObjectGroup)


ViewProviderUserLabSimulation::ViewProviderUserLabSimulation()
{
    sPixmap = "UserLab_NewSimulation";
}

ViewProviderUserLabSimulation::~ViewProviderUserLabSimulation()
{

}

void ViewProviderUserLabSimulation::attach(App::DocumentObject* obj)
{
    Gui::ViewProviderDocumentObjectGroup::attach(obj);
}

void ViewProviderUserLabSimulation::highlightView(Gui::ViewProviderDocumentObject* view)
{
}

bool ViewProviderUserLabSimulation::doubleClicked(void)
{
    Gui::Command::assureWorkbench("UserLabWorkbench");
    Gui::Command::addModule(Gui::Command::Gui, "UserLabGui");
    Gui::Command::doCommand(Gui::Command::Gui,
                            "UserLabGui.setActiveSimulation(App.activeDocument().%s)",
                            this->getObject()->getNameInDocument());
    Gui::Command::doCommand(Gui::Command::Gui, "Gui.Selection.clearSelection()");
    std::vector<App::DocumentObject*> selVector {};
    selVector.push_back(this->getObject());
    auto *docName = this->getObject()->getDocument()->getName();
    Gui::Selection().setSelection(docName, selVector);
    return true;
}

bool ViewProviderUserLabSimulation::run()
{
     UserLab::UserLabSimulation* sim = static_cast<UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    auto activeMethod = sim->getActiveSimulationMethod();

    //UserLabAPI::IrpsWLSimuMethod* activeSimMethod = static_cast<UserLabAPI::IrpsWLSimuMethod*>(sim->getActiveSimulationMethod());
    if (!activeMethod) {
        return false;
    }
    UserLabGui::ViewProviderUserLabFeatureSimulationMethod* vp = dynamic_cast<UserLabGui::ViewProviderUserLabFeatureSimulationMethod*>(Gui::Application::Instance->getViewProvider(activeMethod));

    if (!vp) {
        return false;
    }

    vp->simulate();

    return true;
}

bool ViewProviderUserLabSimulation::stop()
{
     UserLab::UserLabSimulation* sim = static_cast<UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    //get the corresponding view provider
    UserLabGui::ViewProviderUserLabFeatureSimulationMethod* vp = dynamic_cast<UserLabGui::ViewProviderUserLabFeatureSimulationMethod*>(Gui::Application::Instance->getViewProvider(sim));

    vp->stop();

    return true;
}

bool ViewProviderUserLabSimulation::activateSimulation() { return doubleClicked(); }

std::vector<App::DocumentObject*> ViewProviderUserLabSimulation::claimChildren(void)const
{
    return Gui::ViewProviderDocumentObjectGroup::claimChildren();
}

std::vector<std::string> ViewProviderUserLabSimulation::getDisplayModes(void) const
{
    return { "UserLabSimulation" };
}

bool ViewProviderUserLabSimulation::refresh() {
    std::vector<App::Simulation*> sims = UserLabGui::UserLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<UserLab::UserLabSimulation*>(*it)->resetAllEnums();
    }

    Gui::Document* doc = Gui::Application::Instance->activeDocument();

	App::AutoTransaction trans("Recompute");
    Command::doCommand(Command::Doc, "App.getDocument(\"%s\").recompute()", doc->getDocument()->getName());

    return true;
}

void ViewProviderUserLabSimulation::hide(void)
{
    Gui::ViewProviderDocumentObjectGroup::hide();
}

void ViewProviderUserLabSimulation::show(void)
{
    Gui::ViewProviderDocumentObjectGroup::show();
}

void ViewProviderUserLabSimulation::setupContextMenu(QMenu* menu, QObject* , const char* )
{
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* act = menu->addAction(QString::fromLatin1("Activate Simulation"));
    func->trigger(act, boost::bind(&ViewProviderUserLabSimulation::doubleClicked, this));

    QAction* run = menu->addAction(QString::fromLatin1("Run"));
    func->trigger(run, boost::bind(&ViewProviderUserLabSimulation::run, this));

    QAction* stop = menu->addAction(QString::fromLatin1("Stop"));
    func->trigger(stop, boost::bind(&ViewProviderUserLabSimulation::stop, this));

     QAction* refresh = menu->addAction(QString::fromLatin1("Refresh"));
    func->trigger(refresh, boost::bind(&ViewProviderUserLabSimulation::refresh, this));
}


bool ViewProviderUserLabSimulation::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default ) {        
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObjectGroup::setEdit(ModNum);
    }
}

void ViewProviderUserLabSimulation::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObjectGroup::unsetEdit(ModNum);
    }
}

bool ViewProviderUserLabSimulation::canDragObjects() const
{
    return true;
}

bool ViewProviderUserLabSimulation::canDragObject(App::DocumentObject* obj) const
{
     if (!obj)
        return false;

    if (obj->getTypeId().isDerivedFrom( UserLabAPI::UserLabFeatureSimulationMethod::getClassTypeId())) 
        return true;
    else if (obj->getTypeId().isDerivedFrom(Base::Type::fromName("App::FeaturePython")))
        return true;
    else if (obj->getTypeId().isDerivedFrom(App::TextDocument::getClassTypeId()))
        return true;
    else
        return false;
}

void ViewProviderUserLabSimulation::dragObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dragObject(obj);
}

bool ViewProviderUserLabSimulation::canDropObjects() const
{
    return true;
}

bool ViewProviderUserLabSimulation::canDropObject(App::DocumentObject* obj) const
{
    return canDragObject(obj);
}

void ViewProviderUserLabSimulation::dropObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dropObject(obj);
   
    std::vector<App::Simulation*> sims = UserLabGui::UserLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<UserLab::UserLabSimulation*>(*it)->resetAllEnums();
    }
}

bool ViewProviderUserLabSimulation::onDelete(const std::vector<std::string>&)
{
    // warn the user if the object has unselected children
    auto objs = claimChildren();
    return checkSelectedChildren(objs, this->getDocument(), "UserLab simulation");
}

bool ViewProviderUserLabSimulation::canDelete(App::DocumentObject* obj) const
{
    // deletions of objects from a UserLabSimulation don't necessarily destroy anything
    // thus we can pass this action
    // we can warn the user if necessary in the object's ViewProvider in the onDelete() function
    Q_UNUSED(obj)
    return true;
}

bool ViewProviderUserLabSimulation::checkSelectedChildren(const std::vector<App::DocumentObject*> objs,
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
