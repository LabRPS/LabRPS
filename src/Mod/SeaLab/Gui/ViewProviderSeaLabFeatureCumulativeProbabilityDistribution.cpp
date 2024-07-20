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

#include "ViewProviderSeaLabFeatureCumulativeProbabilityDistribution.h"
#include "ViewProviderSeaLabFeatureCumulativeProbabilityDistributionPy.h"

#include <App/Application.h>
#include <Mod/SeaLab/App/SeaLabSimulation.h>
#include <Mod/SeaLab/Gui/DlgSeaLabFeaturesCreation.h>
#include <Gui/Control.h>
#include <Mod/SeaLab/Gui/SeaLabSimulationObserver.h>
#include <App/Document.h>
#include <Gui/ActionFunction.h>
#include "ViewProviderSeaLabSimulation.h"
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Mod/SeaLab/App/SeaLabUtils.h>
#include <Gui/AlphaPlot.h>
#include <Gui/MainWindow.h>
#include <Mod/SeaLabAPI/App/IrpsSeLCumulativeProbabilityDistribution.h>

using namespace SeaLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(SeaLabGui::ViewProviderSeaLabFeatureCumulativeProbabilityDistribution, Gui::ViewProviderDocumentObject)


ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::ViewProviderSeaLabFeatureCumulativeProbabilityDistribution()
{
  sPixmap = ":/icons/SeaLabFeatures/SeaLab_Feature_CPDObj.svg";
}

ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::~ViewProviderSeaLabFeatureCumulativeProbabilityDistribution()
{

}

bool ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::ActivateFeature()
{
auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    if (!obj)
        return false;
    std::string parentSimName = this->getObject()->getGroup()->getNameInDocument();
    
    //get the corresponding view provider
    SeaLabGui::ViewProviderSeaLabSimulation* vp = dynamic_cast<SeaLabGui::ViewProviderSeaLabSimulation*>(Gui::Application::Instance->getViewProvider(this->getObject()->getGroup()));

    if (!vp) {
        return false;
    }

    //activate the paraent simulation
    vp->doubleClicked();

    SeaLab::SeaLabSimulation* parentSim = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->getSimulation(parentSimName));
    if (!parentSim) {Base::Console().Warning("The parent simulation of the selected feature couldn't be actived.\n");return false;}

    bool isfeatureStationary = static_cast<SeaLabAPI::SeaLabFeature*>(obj)->IsStationary.getValue();
    if (parentSim->Stationarity.getValue() != isfeatureStationary)
    {
        Base::Console().Warning("Simulation stationarity and that of the feature does not match. The feature couldn't be activated.\n");
        return false;
    }

    SeaLabGui::SeaLabSimulationObserver::instance()->setActiveSimulation(parentSim);

    parentSim->CumulativeProbabilityDistribution.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);

     QAction* cvalue = menu->addAction(QObject::tr("ComputeCPDValue"));
    func->trigger(cvalue, boost::bind(&ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::computeCPDValue, this));

    QAction* cvector = menu->addAction(QObject::tr("ComputeCPDVectorX"));
    func->trigger(cvector, boost::bind(&ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::computeCPDVectorX, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::OnInitialSetting, this));

    QAction* act = menu->addAction(QObject::tr("Activate Feature"));
    func->trigger(act, boost::bind(&ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::ActivateFeature, this));
}

bool ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::computeCPDVectorX()
{
    
    return runFeatureMethod(SeaLab::SeaLabUtils::ComputeCPDVectorX);

}

bool ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::computeCPDValue()
{
    
    return runFeatureMethod(SeaLab::SeaLabUtils::ComputeCPDValue);
    
}

bool ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::OnInitialSetting()
{
ActivateFeature();
    SeaLab::SeaLabSimulation* sim = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    sim->seaLabFeatureInitalSetting(SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution, QString::fromUtf8(sim->getSimulationData()->cumulativeProbabilityDistribution.getValue()));
     
    return true;
}

PyObject* ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderSeaLabFeatureCumulativeProbabilityDistributionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::runFeatureMethod(const QString function, const char* complexNumberDisplay)
{
     
ActivateFeature();
    SeaLab::SeaLabSimulation* sim = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    seaLabAllFeaturesComputation = new SeaLabAllFeaturesComputation(sim);
    seaLabAllFeaturesComputation->startSimulationWorker(function, complexNumberDisplay);
    seaLabAllFeaturesComputation->getSeaLabSimulationThread()->start();
    return true;
    
}