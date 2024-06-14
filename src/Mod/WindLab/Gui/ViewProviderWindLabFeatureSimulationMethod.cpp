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

#include "ViewProviderWindLabFeatureSimulationMethod.h"
#include "ViewProviderWindLabFeatureSimulationMethodPy.h"

#include <App/Application.h>
#include <Mod/WindLab/App/WindLabSimulation.h>
#include <Mod/WindLab/Gui/DlgWindLabFeaturesCreation.h>
#include <Gui/Control.h>
#include <Mod/WindLab/Gui/WindLabSimulationObserver.h>
#include <App/Document.h>
#include <Gui/ActionFunction.h>
#include "ViewProviderWindLabSimulation.h"
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Mod/WindLab/App/WindLabUtils.h>
#include <Gui/AlphaPlot.h>
#include <Gui/MainWindow.h>
#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>

using namespace WindLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(WindLabGui::ViewProviderWindLabFeatureSimulationMethod, Gui::ViewProviderDocumentObject)


ViewProviderWindLabFeatureSimulationMethod::ViewProviderWindLabFeatureSimulationMethod()
{
  sPixmap = ":/icons/WindLabFeatures/WindLab_Feature_SimulationMethodObj.svg";
}

ViewProviderWindLabFeatureSimulationMethod::~ViewProviderWindLabFeatureSimulationMethod()
{

}

bool ViewProviderWindLabFeatureSimulationMethod::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderWindLabFeatureSimulationMethod::ActivateFeature()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    if (!obj)
        return false;
    std::string parentSimName = this->getObject()->getGroup()->getNameInDocument();
    
    //get the corresponding view provider
    WindLabGui::ViewProviderWindLabSimulation* vp = dynamic_cast<WindLabGui::ViewProviderWindLabSimulation*>(Gui::Application::Instance->getViewProvider(this->getObject()->getGroup()));

    if (!vp) {
        return false;
    }

    //activate the paraent simulation
    vp->doubleClicked();

    WindLab::WindLabSimulation* parentSim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(parentSimName));
    if (!parentSim) {Base::Console().Warning("The parent simulation of the selected feature couldn't be actived.\n");return false;}

    bool isfeatureStationary = static_cast<WindLabAPI::WindLabFeature*>(obj)->IsStationary.getValue();
    if (parentSim->Stationarity.getValue() != isfeatureStationary)
    {
        Base::Console().Warning("Simulation stationarity and that of the feature does not match. The feature couldn't be activated.\n");
        return false;
    }

    WindLabGui::WindLabSimulationObserver::instance()->setActiveSimulation(parentSim);

    parentSim->SimulationMethod.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderWindLabFeatureSimulationMethod::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderWindLabFeatureSimulationMethod::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderWindLabFeatureSimulationMethod::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);

    QAction* simulate = menu->addAction(QObject::tr("Simulate"));
    func->trigger(simulate, boost::bind(&ViewProviderWindLabFeatureSimulationMethod::simulate, this));

    QAction* simulateLargeScale = menu->addAction(QObject::tr("SimulateInLargeScaleMode"));
    func->trigger(simulateLargeScale, boost::bind(&ViewProviderWindLabFeatureSimulationMethod::simulateInLargeScaleMode, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderWindLabFeatureSimulationMethod::OnInitialSetting, this));

    QAction* stop = menu->addAction(QObject::tr("Stop"));
    func->trigger(stop, boost::bind(&ViewProviderWindLabFeatureSimulationMethod::stop, this));
}

bool ViewProviderWindLabFeatureSimulationMethod::simulate()
{
    return runFeatureMethod(WindLab::WindLabUtils::Simulate);   
}

bool ViewProviderWindLabFeatureSimulationMethod::stop()
{ 
    if (windLabAllFeaturesComputation) {
        windLabAllFeaturesComputation->GetWindLabSimulationWorker()->stop();
        return true;
    }
    return false;
}

bool ViewProviderWindLabFeatureSimulationMethod::simulateInLargeScaleMode()
{
   
    return runFeatureMethod(WindLab::WindLabUtils::SimulateInLargeScaleMode);
    
}

bool ViewProviderWindLabFeatureSimulationMethod::OnInitialSetting()
{
ActivateFeature();
    WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    sim->windLabFeatureInitalSetting(WindLab::WindLabUtils::objGroupSimulationMethod, QString::fromUtf8(sim->getSimulationData()->simulationMethod.getValue()));
     
    return true;
}

PyObject* ViewProviderWindLabFeatureSimulationMethod::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderWindLabFeatureSimulationMethodPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool ViewProviderWindLabFeatureSimulationMethod::runFeatureMethod(const QString function, const char* complexNumberDisplay)
{  
ActivateFeature();
    WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    windLabAllFeaturesComputation = new WindLabAllFeaturesComputation(sim);
    windLabAllFeaturesComputation->startSimulationWorker(function, complexNumberDisplay);
    windLabAllFeaturesComputation->getWindLabSimulationThread()->start();
    return true;
}