/***************************************************************************
 *   Copyright (c) 2013 Jürgen Riegel <LabRPS@juergen-riegel.net>         *
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
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/MainWindow.h>


#include "ViewProviderWindLabSimulation.h"
#include <Mod/WindLab/Gui/WindLabSimulationObserver.h>
#include <App/Simulation.h>
#include "Workbenches/WindLab/App/WindLabSimulation.h"
#include "App/WindLabFeatures/WindLabFeature.h"
#include <Gui/Document.h>
#include <Gui/Application.h>
#include "Workbenches/WindLab/Gui/DlgNewSimulation.h"
#include "Control.h"

using namespace WindLabGui;

// ----------------------------------------------------------------------------

/* TRANSLATOR WindLabGui::ViewProviderWindLabSimulation */

PROPERTY_SOURCE(WindLabGui::ViewProviderWindLabSimulation, Gui::ViewProviderDocumentObjectGroup)


ViewProviderWindLabSimulation::ViewProviderWindLabSimulation()
{
    sPixmap = ":/icons/parametric/Part_Plane_Parametric.svg";
}

ViewProviderWindLabSimulation::~ViewProviderWindLabSimulation()
{

}

void ViewProviderWindLabSimulation::attach(App::DocumentObject* obj)
{
    Gui::ViewProviderDocumentObjectGroup::attach(obj);
}

void ViewProviderWindLabSimulation::highlightView(Gui::ViewProviderDocumentObject* view)
{
}

bool ViewProviderWindLabSimulation::doubleClicked(void)
{
    WindLab::WindLabSimulation* newSim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    WindLabGui::WindLabSimulationObserver::instance()->setActiveSimulation(newSim);
    setEdit(0);
    return true;
}

std::vector<App::DocumentObject*> ViewProviderWindLabSimulation::claimChildren(void)const
{
    return Gui::ViewProviderDocumentObjectGroup::claimChildren();
}

std::vector<std::string> ViewProviderWindLabSimulation::getDisplayModes(void) const
{
    return { "Simulation" };
}

void ViewProviderWindLabSimulation::hide(void)
{
    Gui::ViewProviderDocumentObjectGroup::hide();
}

void ViewProviderWindLabSimulation::show(void)
{
    Gui::ViewProviderDocumentObjectGroup::show();
}

void ViewProviderWindLabSimulation::setupContextMenu(QMenu* menu, QObject* , const char* )
{
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* act = menu->addAction(tr("Activate Simulation"));
    func->trigger(act, boost::bind(&ViewProviderWindLabSimulation::doubleClicked, this));
}

bool ViewProviderWindLabSimulation::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default ) {

        WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

        //assign the simulation object to the windLab editing dialog for its possible edit
        WindLabGui::TaskNewSimulationEdit* dlg = new WindLabGui::TaskNewSimulationEdit(sim);
        Gui::Control().showDialog(dlg);
        
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObjectGroup::setEdit(ModNum);
    }
}

void ViewProviderWindLabSimulation::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObjectGroup::unsetEdit(ModNum);
    }
}

bool ViewProviderWindLabSimulation::canDragObjects() const
{
    return true;
}

bool ViewProviderWindLabSimulation::canDragObject(App::DocumentObject* obj) const
{
    if (!obj)
        return false;
   if (obj->getTypeId().isDerivedFrom(WindLabAPI::WindLabFeature::getClassTypeId()))
        return true;
    else if (obj->getTypeId().isDerivedFrom(App::TextDocument::getClassTypeId()))
        return true;
    else
        return false;
}

void ViewProviderWindLabSimulation::dragObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dragObject(obj);
}

bool ViewProviderWindLabSimulation::canDropObjects() const
{
    return true;
}

bool ViewProviderWindLabSimulation::canDropObject(App::DocumentObject* obj) const
{
    return canDragObject(obj);
}

void ViewProviderWindLabSimulation::dropObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dropObject(obj);
}

bool ViewProviderWindLabSimulation::onDelete(const std::vector<std::string>&)
{
    // warn the user if the object has childs

    auto objs = claimChildren();
    if (!objs.empty())
    {
        // generate dialog
        QString bodyMessage;
        QTextStream bodyMessageStream(&bodyMessage);
        bodyMessageStream << qApp->translate("Std_Delete",
            "The analysis is not empty, therefore the\nfollowing referencing objects might be lost:");
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

bool ViewProviderWindLabSimulation::canDelete(App::DocumentObject* obj) const
{
    // deletions of objects from a FemAnalysis don't necessarily destroy anything
    // thus we can pass this action
    // we can warn the user if necessary in the object's ViewProvider in the onDelete() function
    Q_UNUSED(obj)
    return true;
}

