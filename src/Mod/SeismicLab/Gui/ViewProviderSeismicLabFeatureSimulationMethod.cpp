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

#include "ViewProviderSeismicLabFeatureSimulationMethod.h"
#include "ViewProviderSeismicLabFeatureSimulationMethodPy.h"

#include <App/Application.h>
#include <Mod/SeismicLab/App/SeismicLabSimulation.h>
#include <Mod/SeismicLab/Gui/DlgSeismicLabFeaturesCreation.h>
#include <Gui/Control.h>
#include <Mod/SeismicLab/Gui/SeismicLabSimulationObserver.h>
#include <App/Document.h>
#include <Gui/ActionFunction.h>
#include "ViewProviderSeismicLabSimulation.h"
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Mod/SeismicLab/App/SeismicLabUtils.h>
#include <Gui/AlphaPlot.h>
#include <Gui/MainWindow.h>
#include <Mod/SeismicLabAPI/App/IrpsSLSimulationMethod.h>

using namespace SeismicLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(SeismicLabGui::ViewProviderSeismicLabFeatureSimulationMethod, Gui::ViewProviderRPSFeature)


ViewProviderSeismicLabFeatureSimulationMethod::ViewProviderSeismicLabFeatureSimulationMethod()
{
  sPixmap = ":/icons/SeismicLabFeatures/SeismicLab_Feature_SimulationMethodObj.svg";
}

ViewProviderSeismicLabFeatureSimulationMethod::~ViewProviderSeismicLabFeatureSimulationMethod()
{

}

bool ViewProviderSeismicLabFeatureSimulationMethod::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderSeismicLabFeatureSimulationMethod::ActivateFeature()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    if (!obj)
        return false;
    std::string parentSimName = this->getObject()->getGroup()->getNameInDocument();
    
    //get the corresponding view provider
    SeismicLabGui::ViewProviderSeismicLabSimulation* vp = dynamic_cast<SeismicLabGui::ViewProviderSeismicLabSimulation*>(Gui::Application::Instance->getViewProvider(this->getObject()->getGroup()));

    if (!vp) {
        return false;
    }

    //activate the paraent simulation
    vp->doubleClicked();

    SeismicLab::SeismicLabSimulation* parentSim = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->getSimulation(parentSimName));
    if (!parentSim) {Base::Console().Error("The parent simulation of the selected feature couldn't be actived.\n");return false;}

    bool isfeatureStationary = static_cast<SeismicLabAPI::SeismicLabFeature*>(obj)->IsStationary.getValue();
    if (true == parentSim->Stationarity.getValue() && false == isfeatureStationary)
    {
        Base::Console().Error("Simulation stationarity and that of the feature does not match. The feature couldn't be activated.\n");
        return false;
    }

    SeismicLabGui::SeismicLabSimulationObserver::instance()->setActiveSimulation(parentSim);

    parentSim->SimulationMethod.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderSeismicLabFeatureSimulationMethod::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderSeismicLabFeatureSimulationMethod::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderSeismicLabFeatureSimulationMethod::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);

    QAction* simulate = menu->addAction(QObject::tr("Simulate"));
    func->trigger(simulate, boost::bind(&ViewProviderSeismicLabFeatureSimulationMethod::simulate, this));

    QAction* simulateLargeScale = menu->addAction(QObject::tr("SimulateInLargeScaleMode"));
    func->trigger(simulateLargeScale, boost::bind(&ViewProviderSeismicLabFeatureSimulationMethod::simulateInLargeScaleMode, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderSeismicLabFeatureSimulationMethod::OnInitialSetting, this));

    QAction* stop = menu->addAction(QObject::tr("Stop"));
    func->trigger(stop, boost::bind(&ViewProviderSeismicLabFeatureSimulationMethod::stop, this));

    QAction* gtp = menu->addAction(QObject::tr("Go to Publication"));
    func->trigger(gtp, boost::bind(&ViewProviderSeismicLabFeatureSimulationMethod::goToPublication, this));

}

bool ViewProviderSeismicLabFeatureSimulationMethod::simulate()
{
    return runFeatureMethod(SeismicLab::SeismicLabUtils::Simulate);   
}

bool ViewProviderSeismicLabFeatureSimulationMethod::stop()
{
    SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    SeismicLabGui::ViewProviderSeismicLabSimulation* vp = dynamic_cast<SeismicLabGui::ViewProviderSeismicLabSimulation*>(Gui::Application::Instance->getViewProvider(sim));
    if (sim->isRuning())
    {
        Base::Console().Error("A simulation is running, please stop it first.\n");
        return false;
    }


    return false;
}

bool ViewProviderSeismicLabFeatureSimulationMethod::simulateInLargeScaleMode()
{
   
    return runFeatureMethod(SeismicLab::SeismicLabUtils::SimulateInLargeScaleMode);
    
}

bool ViewProviderSeismicLabFeatureSimulationMethod::OnInitialSetting()
{
    ActivateFeature();
    SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    sim->seismicLabFeatureInitalSetting(SeismicLab::SeismicLabUtils::objGroupSimulationMethod, QString::fromUtf8(sim->getSimulationData()->simulationMethod.getValue()));
     
    return true;
}

PyObject* ViewProviderSeismicLabFeatureSimulationMethod::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderSeismicLabFeatureSimulationMethodPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool ViewProviderSeismicLabFeatureSimulationMethod::runFeatureMethod(const QString function, const char* complexNumberDisplay)
{  
ActivateFeature();
    SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    SeismicLabGui::ViewProviderSeismicLabSimulation* vp = dynamic_cast<SeismicLabGui::ViewProviderSeismicLabSimulation*>(Gui::Application::Instance->getViewProvider(sim));
    if (sim->isRuning())
    {
        Base::Console().Error("A simulation is running, please stop it first.\n");
        return false;
    }

    vp->setAllComputation(new SeismicLabAllFeaturesComputation(sim));
    vp->getAllComputation()->startSimulationWorker(function, complexNumberDisplay);
    vp->getAllComputation()->getSeismicLabSimulationThread()->start();

    return true;
}