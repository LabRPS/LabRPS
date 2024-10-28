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

#include "ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod.h"
#include "ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethodPy.h"

#include <App/Application.h>
#include <Mod/UserDefinedPhenomenonLab/App/UserDefinedPhenomenonLabSimulation.h>
#include <Mod/UserDefinedPhenomenonLab/Gui/DlgUserDefinedPhenomenonLabFeaturesCreation.h>
#include <Gui/Control.h>
#include <Mod/UserDefinedPhenomenonLab/Gui/UserDefinedPhenomenonLabSimulationObserver.h>
#include <App/Document.h>
#include <Gui/ActionFunction.h>
#include "ViewProviderUserDefinedPhenomenonLabSimulation.h"
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Mod/UserDefinedPhenomenonLab/App/UserDefinedPhenomenonLabUtils.h>
#include <Gui/AlphaPlot.h>
#include <Gui/MainWindow.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/IrpsULSimulationMethod.h>

using namespace UserDefinedPhenomenonLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod, Gui::ViewProviderDocumentObject)


ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod()
{
  sPixmap = ":/icons/UserDefinedPhenomenonLabFeatures/UserDefinedPhenomenonLab_Feature_SimulationMethodObj.svg";
}

ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::~ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod()
{

}

bool ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::ActivateFeature()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    if (!obj)
        return false;
    std::string parentSimName = this->getObject()->getGroup()->getNameInDocument();
    
    //get the corresponding view provider
    UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabSimulation* vp = dynamic_cast<UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabSimulation*>(Gui::Application::Instance->getViewProvider(this->getObject()->getGroup()));

    if (!vp) {
        return false;
    }

    //activate the paraent simulation
    vp->doubleClicked();

    UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* parentSim = static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->getSimulation(parentSimName));
    if (!parentSim) {Base::Console().Warning("The parent simulation of the selected feature couldn't be actived.\n");return false;}

    bool isfeatureStationary = static_cast<UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature*>(obj)->IsStationary.getValue();
    if (true == parentSim->Stationarity.getValue() && false == isfeatureStationary)
    {
        Base::Console().Warning("Simulation stationarity and that of the feature does not match. The feature couldn't be activated.\n");
        return false;
    }

    UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->setActiveSimulation(parentSim);

    parentSim->SimulationMethod.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);

    QAction* simulate = menu->addAction(QObject::tr("Simulate"));
    func->trigger(simulate, boost::bind(&ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::simulate, this));

    QAction* simulateLargeScale = menu->addAction(QObject::tr("SimulateInLargeScaleMode"));
    func->trigger(simulateLargeScale, boost::bind(&ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::simulateInLargeScaleMode, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::OnInitialSetting, this));

    QAction* stop = menu->addAction(QObject::tr("Stop"));
    func->trigger(stop, boost::bind(&ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::stop, this));
}

bool ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::simulate()
{
    return runFeatureMethod(UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::Simulate);   
}

bool ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::stop()
{ 
    if (userDefinedPhenomenonAllFeaturesComputation) {
        userDefinedPhenomenonAllFeaturesComputation->GetUserDefinedPhenomenonLabSimulationWorker()->stop();
        return true;
    }
    return false;
}

bool ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::simulateInLargeScaleMode()
{
   
    return runFeatureMethod(UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::SimulateInLargeScaleMode);
    
}

bool ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::OnInitialSetting()
{
ActivateFeature();
    UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim = static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    sim->userDefinedPhenomenonFeatureInitalSetting(UserDefinedPhenomenonLab::UserDefinedPhenomenonLabUtils::objGroupSimulationMethod, QString::fromUtf8(sim->getSimulationData()->simulationMethod.getValue()));
     
    return true;
}

PyObject* ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethodPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::runFeatureMethod(const QString function, const char* complexNumberDisplay)
{  
ActivateFeature();
    UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim = static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    userDefinedPhenomenonAllFeaturesComputation = new UserDefinedPhenomenonLabAllFeaturesComputation(sim);
    userDefinedPhenomenonAllFeaturesComputation->startSimulationWorker(function, complexNumberDisplay);
    userDefinedPhenomenonAllFeaturesComputation->getUserDefinedPhenomenonLabSimulationThread()->start();
    return true;
}