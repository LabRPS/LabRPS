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

#include "ViewProviderSeaLabSimulationComparison.h"
#include "ViewProviderSeaLabSimulationComparisonPy.h"

#include <Mod/SeaLab/App/SeaLabSimulationComparison.h>
#include <Mod/SeaLab/Gui/DlgSimulationComparison.h>

#include <Gui/Control.h>
#include <Gui/ActionFunction.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include "SeaLabSimulationObserver.h"



using namespace SeaLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(SeaLabGui::ViewProviderSeaLabSimulationComparison, Gui::ViewProviderDocumentObject)


ViewProviderSeaLabSimulationComparison::ViewProviderSeaLabSimulationComparison()
{
  sPixmap = ":/icons/parametric/Part_Line_Parametric.svg";
}

ViewProviderSeaLabSimulationComparison::~ViewProviderSeaLabSimulationComparison()
{

}

bool ViewProviderSeaLabSimulationComparison::doubleClicked(void)
{
    Gui::Application::Instance->activeDocument()->setEdit(this);
    return true;
}

bool ViewProviderSeaLabSimulationComparison::setEdit(int ModNum)
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

    SeaLab::SeaLabSimulationComparison* comp = dynamic_cast<SeaLab::SeaLabSimulationComparison*>(obj);
    if (comp) {
        Gui::Control().showDialog(new SeaLabGui::DlgSimulationComparisonEdit(comp));
    }

    return true;
}

void ViewProviderSeaLabSimulationComparison::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderSeaLabSimulationComparison::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* start = menu->addAction(QObject::tr("start"));
    func->trigger(start, boost::bind(&ViewProviderSeaLabSimulationComparison::start, this));

    QAction* stop = menu->addAction(QObject::tr("stop"));
    func->trigger(stop, boost::bind(&ViewProviderSeaLabSimulationComparison::stop, this));
}

bool ViewProviderSeaLabSimulationComparison::start()
{ 
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;

    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    SeaLab::SeaLabSimulationComparison* comp = dynamic_cast<SeaLab::SeaLabSimulationComparison*>(obj);
    if (!comp)
        return false;

    SeaLab::SeaLabSimulation* sim1 = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->getSimulation(comp->SimulationCandidate1.getValue()));
    SeaLab::SeaLabSimulation* sim2 = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->getSimulation(comp->SimulationCandidate2.getValue()));

    if (!sim1 || !sim2)
        return false;
     SeaLabAPI::SeaLabFeature* feat1 = static_cast<SeaLabAPI::SeaLabFeature*>(doc->getObject(comp->FeatureCandidate1.getValue()));
     SeaLabAPI::SeaLabFeature* feat2 = static_cast<SeaLabAPI::SeaLabFeature*>(doc->getObject(comp->FeatureCandidate2.getValue()));

    if (!feat1 || !feat2)
        return false;

    sim1->setActiveFeature(feat1);
    sim2->setActiveFeature(feat2);

    sim1->getSimulationData()->comparisonMode.setValue(true);
    sim2->getSimulationData()->comparisonMode.setValue(true);

    seaLabComparisonStarter = new SeaLabComparisonStarter(sim1, sim2, comp->getNameInDocument());
    seaLabComparisonStarter->startSimulationWorker(QString::fromLatin1(comp->ComparisonMethod.getValue()));
    seaLabComparisonStarter->getSeaLabSimulationThread1()->start();
    seaLabComparisonStarter->getSeaLabSimulationThread2()->start();

    return true; 
}

bool ViewProviderSeaLabSimulationComparison::stop()
{ 
     if (seaLabComparisonStarter) {
        seaLabComparisonStarter->GetSeaLabSimulationWorker1()->stop();
        seaLabComparisonStarter->GetSeaLabSimulationWorker2()->stop();

        return true;
    }
    return false;
}


PyObject* ViewProviderSeaLabSimulationComparison::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderSeaLabSimulationComparisonPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}
