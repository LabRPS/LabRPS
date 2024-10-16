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

#include "ViewProviderUserDefinedPhenomenonLabSimulationComparison.h"
#include "ViewProviderUserDefinedPhenomenonLabSimulationComparisonPy.h"

#include <Mod/UserDefinedPhenomenonLab/App/UserDefinedPhenomenonLabSimulationComparison.h>
#include <Mod/UserDefinedPhenomenonLab/Gui/DlgSimulationComparison.h>

#include <Gui/Control.h>
#include <Gui/ActionFunction.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include "UserDefinedPhenomenonLabSimulationObserver.h"



using namespace UserDefinedPhenomenonLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabSimulationComparison, Gui::ViewProviderDocumentObject)


ViewProviderUserDefinedPhenomenonLabSimulationComparison::ViewProviderUserDefinedPhenomenonLabSimulationComparison()
{
  sPixmap = ":/icons/parametric/Part_Line_Parametric.svg";
}

ViewProviderUserDefinedPhenomenonLabSimulationComparison::~ViewProviderUserDefinedPhenomenonLabSimulationComparison()
{

}

bool ViewProviderUserDefinedPhenomenonLabSimulationComparison::doubleClicked(void)
{
    Gui::Application::Instance->activeDocument()->setEdit(this);
    return true;
}

bool ViewProviderUserDefinedPhenomenonLabSimulationComparison::setEdit(int ModNum)
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

    UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulationComparison* comp = dynamic_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulationComparison*>(obj);
    if (comp) {
        Gui::Control().showDialog(new UserDefinedPhenomenonLabGui::DlgSimulationComparisonEdit(comp));
    }

    return true;
}

void ViewProviderUserDefinedPhenomenonLabSimulationComparison::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderUserDefinedPhenomenonLabSimulationComparison::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* start = menu->addAction(QObject::tr("start"));
    func->trigger(start, boost::bind(&ViewProviderUserDefinedPhenomenonLabSimulationComparison::start, this));

    QAction* stop = menu->addAction(QObject::tr("stop"));
    func->trigger(stop, boost::bind(&ViewProviderUserDefinedPhenomenonLabSimulationComparison::stop, this));
}

bool ViewProviderUserDefinedPhenomenonLabSimulationComparison::start()
{ 
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;

    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulationComparison* comp = dynamic_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulationComparison*>(obj);
    if (!comp)
        return false;

    UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim1 = static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->getSimulation(comp->SimulationCandidate1.getValue()));
    UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim2 = static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->getSimulation(comp->SimulationCandidate2.getValue()));

    if (!sim1 || !sim2)
        return false;
     UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature* feat1 = static_cast<UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature*>(doc->getObject(comp->FeatureCandidate1.getValue()));
     UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature* feat2 = static_cast<UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature*>(doc->getObject(comp->FeatureCandidate2.getValue()));

    if (!feat1 || !feat2)
        return false;

    sim1->setActiveFeature(feat1);
    sim2->setActiveFeature(feat2);

    sim1->getSimulationData()->comparisonMode.setValue(true);
    sim2->getSimulationData()->comparisonMode.setValue(true);

    userDefinedPhenomenonComparisonStarter = new UserDefinedPhenomenonLabComparisonStarter(sim1, sim2, comp->getNameInDocument());
    userDefinedPhenomenonComparisonStarter->startSimulationWorker(QString::fromLatin1(comp->ComparisonMethod.getValue()));
    userDefinedPhenomenonComparisonStarter->getUserDefinedPhenomenonLabSimulationThread1()->start();
    userDefinedPhenomenonComparisonStarter->getUserDefinedPhenomenonLabSimulationThread2()->start();

    return true; 
}

bool ViewProviderUserDefinedPhenomenonLabSimulationComparison::stop()
{ 
     if (userDefinedPhenomenonComparisonStarter) {
        userDefinedPhenomenonComparisonStarter->GetUserDefinedPhenomenonLabSimulationWorker1()->stop();
        userDefinedPhenomenonComparisonStarter->GetUserDefinedPhenomenonLabSimulationWorker2()->stop();

        return true;
    }
    return false;
}


PyObject* ViewProviderUserDefinedPhenomenonLabSimulationComparison::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderUserDefinedPhenomenonLabSimulationComparisonPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}
