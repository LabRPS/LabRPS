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

#include "ViewProviderSeismicLabSimulationComparison.h"
#include "ViewProviderSeismicLabSimulationComparisonPy.h"

#include <Mod/SeismicLab/App/SeismicLabSimulationComparison.h>
#include <Mod/SeismicLab/Gui/DlgSimulationComparison.h>

#include <Gui/Control.h>
#include <Gui/ActionFunction.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include "SeismicLabSimulationObserver.h"



using namespace SeismicLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(SeismicLabGui::ViewProviderSeismicLabSimulationComparison,  Gui::ViewProviderDocumentObject)


ViewProviderSeismicLabSimulationComparison::ViewProviderSeismicLabSimulationComparison()
{
  sPixmap = ":/icons/parametric/Part_Line_Parametric.svg";
}

ViewProviderSeismicLabSimulationComparison::~ViewProviderSeismicLabSimulationComparison()
{

}

bool ViewProviderSeismicLabSimulationComparison::doubleClicked(void)
{
    Gui::Application::Instance->activeDocument()->setEdit(this);
    return true;
}

bool ViewProviderSeismicLabSimulationComparison::setEdit(int ModNum)
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

    SeismicLab::SeismicLabSimulationComparison* comp = dynamic_cast<SeismicLab::SeismicLabSimulationComparison*>(obj);
    if (comp) {
        Gui::Control().showDialog(new SeismicLabGui::DlgSimulationComparisonEdit(comp));
    }

    return true;
}

void ViewProviderSeismicLabSimulationComparison::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderSeismicLabSimulationComparison::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* start = menu->addAction(QObject::tr("start"));
    func->trigger(start, boost::bind(&ViewProviderSeismicLabSimulationComparison::start, this));

    QAction* stop = menu->addAction(QObject::tr("stop"));
    func->trigger(stop, boost::bind(&ViewProviderSeismicLabSimulationComparison::stop, this));
}

bool ViewProviderSeismicLabSimulationComparison::start()
{ 
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;

    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    SeismicLab::SeismicLabSimulationComparison* comp = dynamic_cast<SeismicLab::SeismicLabSimulationComparison*>(obj);
    if (!comp)
        return false;

    SeismicLab::SeismicLabSimulation* sim1 = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->getSimulation(comp->SimulationCandidate1.getValue()));
    SeismicLab::SeismicLabSimulation* sim2 = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->getSimulation(comp->SimulationCandidate2.getValue()));

    if (!sim1 || !sim2)
        return false;
     SeismicLabAPI::SeismicLabFeature* feat1 = static_cast<SeismicLabAPI::SeismicLabFeature*>(doc->getObject(comp->FeatureCandidate1.getValue()));
     SeismicLabAPI::SeismicLabFeature* feat2 = static_cast<SeismicLabAPI::SeismicLabFeature*>(doc->getObject(comp->FeatureCandidate2.getValue()));

    if (!feat1 || !feat2)
        return false;

    sim1->setActiveFeature(feat1);
    sim2->setActiveFeature(feat2);

    sim1->getSimulationData()->comparisonMode.setValue(true);
    sim2->getSimulationData()->comparisonMode.setValue(true);

    seismicLabComparisonStarter = new SeismicLabComparisonStarter(sim1, sim2, comp->getNameInDocument());
    seismicLabComparisonStarter->startSimulationWorker(QString::fromLatin1(comp->ComparisonMethod.getValue()));
    seismicLabComparisonStarter->getSeismicLabSimulationThread1()->start();
    seismicLabComparisonStarter->getSeismicLabSimulationThread2()->start();

    return true; 
}

bool ViewProviderSeismicLabSimulationComparison::stop()
{ 
     if (seismicLabComparisonStarter) {
        seismicLabComparisonStarter->GetSeismicLabSimulationWorker1()->stop();
        seismicLabComparisonStarter->GetSeismicLabSimulationWorker2()->stop();

        return true;
    }
    return false;
}


PyObject* ViewProviderSeismicLabSimulationComparison::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderSeismicLabSimulationComparisonPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}
