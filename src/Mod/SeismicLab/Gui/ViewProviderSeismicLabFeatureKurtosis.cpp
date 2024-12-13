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

#include "ViewProviderSeismicLabFeatureKurtosis.h"
#include "ViewProviderSeismicLabFeatureKurtosisPy.h"

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
#include <Mod/SeismicLabAPI/App/IrpsSLKurtosis.h>
#include <Mod/SeismicLab/Gui/SeismicLabAllFeaturesComputation.h>

using namespace SeismicLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(SeismicLabGui::ViewProviderSeismicLabFeatureKurtosis, Gui::ViewProviderRPSFeature)


ViewProviderSeismicLabFeatureKurtosis::ViewProviderSeismicLabFeatureKurtosis()
{
  sPixmap = ":/icons/SeismicLabFeatures/SeismicLab_Feature_KurtosisObj.svg";
}

ViewProviderSeismicLabFeatureKurtosis::~ViewProviderSeismicLabFeatureKurtosis()
{

}

bool ViewProviderSeismicLabFeatureKurtosis::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderSeismicLabFeatureKurtosis::ActivateFeature()
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

    parentSim->Kurtosis.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderSeismicLabFeatureKurtosis::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {

        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderSeismicLabFeatureKurtosis::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderSeismicLabFeatureKurtosis::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
   
    QAction* cvalue = menu->addAction(QObject::tr("ComputeKurtosisValue"));
    func->trigger(cvalue, boost::bind(&ViewProviderSeismicLabFeatureKurtosis::computeKurtosisValue, this));

    QAction* cvector = menu->addAction(QObject::tr("ComputeKurtosisVectorP"));
    func->trigger(cvector, boost::bind(&ViewProviderSeismicLabFeatureKurtosis::computeKurtosisVectorP, this));

    QAction* carray = menu->addAction(QObject::tr("ComputeKurtosisVectorT"));
    func->trigger(carray, boost::bind(&ViewProviderSeismicLabFeatureKurtosis::computeKurtosisVectorT, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderSeismicLabFeatureKurtosis::OnInitialSetting, this));

    QAction* act = menu->addAction(QObject::tr("Activate Feature"));
    func->trigger(act, boost::bind(&ViewProviderSeismicLabFeatureKurtosis::ActivateFeature, this));

    QAction* gtp = menu->addAction(QObject::tr("Go to Publication"));
    func->trigger(gtp, boost::bind(&ViewProviderSeismicLabFeatureKurtosis::goToPublication, this));
}


bool ViewProviderSeismicLabFeatureKurtosis::computeKurtosisValue()
{
    
    return runFeatureMethod(SeismicLab::SeismicLabUtils::ComputeKurtosisValue);
    
}



bool ViewProviderSeismicLabFeatureKurtosis::computeKurtosisVectorP()
{
    
    return runFeatureMethod(SeismicLab::SeismicLabUtils::ComputeKurtosisVectorP);
    
}


bool ViewProviderSeismicLabFeatureKurtosis::computeKurtosisVectorT()
{
     
    return runFeatureMethod(SeismicLab::SeismicLabUtils::ComputeKurtosisVectorT);
    
}
bool ViewProviderSeismicLabFeatureKurtosis::OnInitialSetting()
{
ActivateFeature();
    SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    sim->seismicLabFeatureInitalSetting(SeismicLab::SeismicLabUtils::objGroupKurtosis, QString::fromUtf8(sim->getSimulationData()->kurtosis.getValue()));
     
    return true;
}
PyObject* ViewProviderSeismicLabFeatureKurtosis::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderSeismicLabFeatureKurtosisPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool ViewProviderSeismicLabFeatureKurtosis::runFeatureMethod(const QString function, const char* complexNumberDisplay)
{  
ActivateFeature();
    SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

        SeismicLabGui::ViewProviderSeismicLabSimulation* vp = dynamic_cast<SeismicLabGui::ViewProviderSeismicLabSimulation*>(Gui::Application::Instance->getViewProvider(sim));
    if (vp) {
        auto computation = vp->getAllComputation();
        if (computation) {
            auto worker = vp->getAllComputation()->GetSeismicLabSimulationWorker();
            if (worker) {
                if (!vp->getAllComputation()->GetSeismicLabSimulationWorker()->isStopped()) {
                    Base::Console().Error("A simulation is running, please stop it first.\n");
                    return false;
                }
            }
        }
    }
    vp->setAllComputation(new SeismicLabAllFeaturesComputation(sim));
    vp->getAllComputation()->startSimulationWorker(function, complexNumberDisplay);
    vp->getAllComputation()->getSeismicLabSimulationThread()->start();

    return true;
    
}