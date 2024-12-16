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

#include "ViewProviderUserLabFeatureSimulationMethod.h"
#include "ViewProviderUserLabFeatureSimulationMethodPy.h"

#include <App/Application.h>
#include <Mod/UserLab/App/UserLabSimulation.h>
#include <Mod/UserLab/Gui/DlgUserLabFeaturesCreation.h>
#include <Gui/Control.h>
#include <Mod/UserLab/Gui/UserLabSimulationObserver.h>
#include <App/Document.h>
#include <Gui/ActionFunction.h>
#include "ViewProviderUserLabSimulation.h"
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Mod/UserLab/App/UserLabUtils.h>
#include <Gui/AlphaPlot.h>
#include <Gui/MainWindow.h>
#include <Mod/UserLabAPI/App/IrpsULSimulationMethod.h>

using namespace UserLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(UserLabGui::ViewProviderUserLabFeatureSimulationMethod, Gui::ViewProviderRPSFeature)


ViewProviderUserLabFeatureSimulationMethod::ViewProviderUserLabFeatureSimulationMethod()
{
  sPixmap = ":/icons/UserLabFeatures/UserLab_Feature_SimulationMethodObj.svg";
}

ViewProviderUserLabFeatureSimulationMethod::~ViewProviderUserLabFeatureSimulationMethod()
{

}

bool ViewProviderUserLabFeatureSimulationMethod::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderUserLabFeatureSimulationMethod::ActivateFeature()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    if (!obj)
        return false;
    std::string parentSimName = this->getObject()->getGroup()->getNameInDocument();
    
    //get the corresponding view provider
    UserLabGui::ViewProviderUserLabSimulation* vp = dynamic_cast<UserLabGui::ViewProviderUserLabSimulation*>(Gui::Application::Instance->getViewProvider(this->getObject()->getGroup()));

    if (!vp) {
        return false;
    }

    //activate the paraent simulation
    vp->doubleClicked();

    UserLab::UserLabSimulation* parentSim = static_cast<UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->getSimulation(parentSimName));
    if (!parentSim) {Base::Console().Warning("The parent simulation of the selected feature couldn't be actived.\n");return false;}

    bool isfeatureStationary = static_cast<UserLabAPI::UserLabFeature*>(obj)->IsStationary.getValue();
    if (true == parentSim->Stationarity.getValue() && false == isfeatureStationary)
    {
        Base::Console().Warning("Simulation stationarity and that of the feature does not match. The feature couldn't be activated.\n");
        return false;
    }

    UserLabGui::UserLabSimulationObserver::instance()->setActiveSimulation(parentSim);

    parentSim->SimulationMethod.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderUserLabFeatureSimulationMethod::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderUserLabFeatureSimulationMethod::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderUserLabFeatureSimulationMethod::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);

    QAction* simulate = menu->addAction(QObject::tr("Simulate"));
    func->trigger(simulate, boost::bind(&ViewProviderUserLabFeatureSimulationMethod::simulate, this));

    QAction* simulateLargeScale = menu->addAction(QObject::tr("SimulateInLargeScaleMode"));
    func->trigger(simulateLargeScale, boost::bind(&ViewProviderUserLabFeatureSimulationMethod::simulateInLargeScaleMode, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderUserLabFeatureSimulationMethod::OnInitialSetting, this));

    QAction* stop = menu->addAction(QObject::tr("Stop"));
    func->trigger(stop, boost::bind(&ViewProviderUserLabFeatureSimulationMethod::stop, this));

    QAction* gtp = menu->addAction(QObject::tr("Go to Publication"));
    func->trigger(gtp, boost::bind(&ViewProviderUserLabFeatureSimulationMethod::goToPublication, this));

}

bool ViewProviderUserLabFeatureSimulationMethod::simulate()
{
    return runFeatureMethod(UserLab::UserLabUtils::Simulate);   
}

bool ViewProviderUserLabFeatureSimulationMethod::stop()
{ 
    UserLab::UserLabSimulation* sim = static_cast<UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    UserLabGui::ViewProviderUserLabSimulation* vp = dynamic_cast<UserLabGui::ViewProviderUserLabSimulation*>(Gui::Application::Instance->getViewProvider(sim));
    if (sim->isRuning())
    {
        Base::Console().Error("A simulation is running, please stop it first.\n");
        return false;
    }

    return false;
}

bool ViewProviderUserLabFeatureSimulationMethod::simulateInLargeScaleMode()
{
   
    return runFeatureMethod(UserLab::UserLabUtils::SimulateInLargeScaleMode);
    
}

bool ViewProviderUserLabFeatureSimulationMethod::OnInitialSetting()
{
ActivateFeature();
    UserLab::UserLabSimulation* sim = static_cast<UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    sim->userFeatureInitalSetting(UserLab::UserLabUtils::objGroupSimulationMethod, QString::fromUtf8(sim->getSimulationData()->simulationMethod.getValue()));
     
    return true;
}

PyObject* ViewProviderUserLabFeatureSimulationMethod::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderUserLabFeatureSimulationMethodPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool ViewProviderUserLabFeatureSimulationMethod::runFeatureMethod(const QString function, const char* complexNumberDisplay)
{  
ActivateFeature();
    UserLab::UserLabSimulation* sim = static_cast<UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    UserLabGui::ViewProviderUserLabSimulation* vp = dynamic_cast<UserLabGui::ViewProviderUserLabSimulation*>(Gui::Application::Instance->getViewProvider(sim));
    if (vp) {
        auto computation = vp->getAllComputation();
        if (computation) {
            auto worker = vp->getAllComputation()->GetUserLabSimulationWorker();
            if (worker) {
                if (!vp->getAllComputation()->GetUserLabSimulationWorker()->isStopped()) {
                    Base::Console().Error("A simulation is running, please stop it first.\n");
                    return false;
                }
            }
        }
    }
    vp->setAllComputation(new UserLabAllFeaturesComputation(sim));
    vp->getAllComputation()->startSimulationWorker(function, complexNumberDisplay);
    vp->getAllComputation()->getUserLabSimulationThread()->start();

    return true;
}