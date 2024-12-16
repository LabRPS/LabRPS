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

#include "ViewProviderSeismicLabFeatureShearVelocityOfFlow.h"
#include "ViewProviderSeismicLabFeatureShearVelocityOfFlowPy.h"

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
#include <Mod/SeismicLabAPI/App/IrpsSLShearVelocityOfFlow.h>
#include <Mod/SeismicLab/Gui/SeismicLabAllFeaturesComputation.h>

using namespace SeismicLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(SeismicLabGui::ViewProviderSeismicLabFeatureShearVelocityOfFlow, Gui::ViewProviderRPSFeature)


ViewProviderSeismicLabFeatureShearVelocityOfFlow::ViewProviderSeismicLabFeatureShearVelocityOfFlow()
{
  sPixmap = ":/icons/SeismicLabFeatures/SeismicLab_Feature_ShearVelocityObj.svg";
}

ViewProviderSeismicLabFeatureShearVelocityOfFlow::~ViewProviderSeismicLabFeatureShearVelocityOfFlow()
{

}

bool ViewProviderSeismicLabFeatureShearVelocityOfFlow::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderSeismicLabFeatureShearVelocityOfFlow::ActivateFeature()
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
    if (!parentSim) {Base::Console().Warning("The parent simulation of the selected feature couldn't be actived.\n");return false;}

    bool isfeatureStationary = static_cast<SeismicLabAPI::SeismicLabFeature*>(obj)->IsStationary.getValue();
    if (true == parentSim->Stationarity.getValue() && false == isfeatureStationary)
    {
        Base::Console().Warning("Simulation stationarity and that of the feature does not match. The feature couldn't be activated.\n");
        return false;
    }

    SeismicLabGui::SeismicLabSimulationObserver::instance()->setActiveSimulation(parentSim);

    parentSim->ShearVelocityOfFlow.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderSeismicLabFeatureShearVelocityOfFlow::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {

        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderSeismicLabFeatureShearVelocityOfFlow::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderSeismicLabFeatureShearVelocityOfFlow::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);

    QAction* cvalue = menu->addAction(QObject::tr("ComputeShearVelocityOfFlowValue"));
    func->trigger(cvalue, boost::bind(&ViewProviderSeismicLabFeatureShearVelocityOfFlow::computeShearVelocityOfFlowValue, this));

    QAction* cvectorP = menu->addAction(QObject::tr("ComputeShearVelocityOfFlowVectorP"));
    func->trigger(cvectorP, boost::bind(&ViewProviderSeismicLabFeatureShearVelocityOfFlow::computeShearVelocityOfFlowVectorP, this));

    QAction* cvectorT = menu->addAction(QObject::tr("ComputeShearVelocityOfFlowVectorT"));
    func->trigger(cvectorT, boost::bind(&ViewProviderSeismicLabFeatureShearVelocityOfFlow::computeShearVelocityOfFlowVectorT, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderSeismicLabFeatureShearVelocityOfFlow::OnInitialSetting, this));

    QAction* act = menu->addAction(QObject::tr("Activate Feature"));
    func->trigger(act, boost::bind(&ViewProviderSeismicLabFeatureShearVelocityOfFlow::ActivateFeature, this));

    QAction* gtp = menu->addAction(QObject::tr("Go to Publication"));
    func->trigger(gtp, boost::bind(&ViewProviderSeismicLabFeatureShearVelocityOfFlow::goToPublication, this));
}

bool ViewProviderSeismicLabFeatureShearVelocityOfFlow::computeShearVelocityOfFlowValue()
{
     
    return runFeatureMethod(SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowValue);
    
}

bool ViewProviderSeismicLabFeatureShearVelocityOfFlow::computeShearVelocityOfFlowVectorT()
{
    
    return runFeatureMethod(SeismicLab::SeismicLabUtils::ComputeCrossCoherenceVectorT);
    
}

bool ViewProviderSeismicLabFeatureShearVelocityOfFlow::computeShearVelocityOfFlowVectorP()
{
    
    return runFeatureMethod(SeismicLab::SeismicLabUtils::ComputeCrossCoherenceVectorT);
    
}

bool ViewProviderSeismicLabFeatureShearVelocityOfFlow::OnInitialSetting()
{
ActivateFeature();
    SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    sim->seismicLabFeatureInitalSetting(SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow, QString::fromUtf8(sim->getSimulationData()->shearVelocityOfFlow.getValue()));
     
    return true;
}

PyObject* ViewProviderSeismicLabFeatureShearVelocityOfFlow::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderSeismicLabFeatureShearVelocityOfFlowPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool ViewProviderSeismicLabFeatureShearVelocityOfFlow::runFeatureMethod(const QString function, const char* complexNumberDisplay)
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