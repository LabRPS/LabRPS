/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
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
#endif

#include "ViewProviderUserLabSimulationComparison.h"
#include "ViewProviderUserLabSimulationComparisonPy.h"

#include <Mod/UserLab/App/UserLabSimulationComparison.h>
#include <Mod/UserLab/Gui/DlgSimulationComparison.h>

#include <Gui/Control.h>
#include <Gui/ActionFunction.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include "UserLabSimulationObserver.h"



using namespace UserLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(UserLabGui::ViewProviderUserLabSimulationComparison,  Gui::ViewProviderDocumentObject)


ViewProviderUserLabSimulationComparison::ViewProviderUserLabSimulationComparison()
{
  sPixmap = ":/icons/parametric/Part_Line_Parametric.svg";
}

ViewProviderUserLabSimulationComparison::~ViewProviderUserLabSimulationComparison()
{

}

bool ViewProviderUserLabSimulationComparison::doubleClicked(void)
{
    Gui::Application::Instance->activeDocument()->setEdit(this);
    return true;
}

bool ViewProviderUserLabSimulationComparison::setEdit(int ModNum)
{
     if (ModNum != ViewProvider::Default ) {
      return ViewProviderDocumentObject::setEdit(ModNum);
    }

    if (Gui::Control().activeDialog())  {         //TaskPanel already open!
        return false;
    }

    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;

    auto obj = doc->getObject(this->getObject()->getNameInDocument());

    UserLab::UserLabSimulationComparison* comp = dynamic_cast<UserLab::UserLabSimulationComparison*>(obj);
    if (comp) {
        Gui::Control().showDialog(new UserLabGui::DlgSimulationComparisonEdit(comp));
    }

    return true;
}

void ViewProviderUserLabSimulationComparison::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderUserLabSimulationComparison::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* start = menu->addAction(QObject::tr("start"));
    func->trigger(start, boost::bind(&ViewProviderUserLabSimulationComparison::start, this));

    QAction* stop = menu->addAction(QObject::tr("stop"));
    func->trigger(stop, boost::bind(&ViewProviderUserLabSimulationComparison::stop, this));
}

bool ViewProviderUserLabSimulationComparison::start()
{ 
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;

    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    UserLab::UserLabSimulationComparison* comp = dynamic_cast<UserLab::UserLabSimulationComparison*>(obj);
    if (!comp)
        return false;

    UserLab::UserLabSimulation* sim1 = static_cast<UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->getSimulation(comp->SimulationCandidate1.getValue()));
    UserLab::UserLabSimulation* sim2 = static_cast<UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->getSimulation(comp->SimulationCandidate2.getValue()));

    if (!sim1 || !sim2)
        return false;
     UserLabAPI::UserLabFeature* feat1 = static_cast<UserLabAPI::UserLabFeature*>(doc->getObject(comp->FeatureCandidate1.getValue()));
     UserLabAPI::UserLabFeature* feat2 = static_cast<UserLabAPI::UserLabFeature*>(doc->getObject(comp->FeatureCandidate2.getValue()));

    if (!feat1 || !feat2)
        return false;

    sim1->setActiveFeature(feat1);
    sim2->setActiveFeature(feat2);

    sim1->getSimulationData()->comparisonMode.setValue(true);
    sim2->getSimulationData()->comparisonMode.setValue(true);

    userComparisonStarter = new UserLabComparisonStarter(sim1, sim2, comp->getNameInDocument());
    userComparisonStarter->startSimulationWorker(QString::fromLatin1(comp->ComparisonMethod.getValue()));
    userComparisonStarter->getUserLabSimulationThread1()->start();
    userComparisonStarter->getUserLabSimulationThread2()->start();

    return true; 
}

bool ViewProviderUserLabSimulationComparison::stop()
{ 
     if (userComparisonStarter) {
        userComparisonStarter->GetUserLabSimulationWorker1()->stop();
        userComparisonStarter->GetUserLabSimulationWorker2()->stop();

        return true;
    }
    return false;
}


PyObject* ViewProviderUserLabSimulationComparison::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderUserLabSimulationComparisonPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}
