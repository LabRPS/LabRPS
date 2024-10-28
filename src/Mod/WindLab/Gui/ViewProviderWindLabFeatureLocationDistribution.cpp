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

#include "ViewProviderWindLabFeatureLocationDistribution.h"
#include "ViewProviderWindLabFeatureLocationDistributionPy.h"
#include "ViewProviderWindLabSimulation.h"
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
#include <Mod/WindLabAPI/App/IrpsWLLocationDistribution.h>
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLab/App/WindLabUtils.h>
#include <Gui/MainWindow.h>
#include <Gui/AlphaPlot.h>
#include <Gui/ViewParams.h>
#include <CXX/Objects.hxx>

using namespace WindLabGui;
namespace bp = boost::placeholders;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(WindLabGui::ViewProviderWindLabFeatureLocationDistribution, Gui::ViewProviderDocumentObject)

App::PropertyFloatConstraint::Constraints ViewProviderWindLabFeatureLocationDistribution::sizeRange = {1.0, 64.0, 1.0};

ViewProviderWindLabFeatureLocationDistribution::ViewProviderWindLabFeatureLocationDistribution()
{
  sPixmap = ":/icons/WindLabFeatures/WindLab_Feature_LocationObj.svg";

   ADD_PROPERTY_TYPE(ShowSimulationPoints, (false), "Points", App::Prop_Hidden, "Whether to show the simulation points in the 3D view or not.");
}

ViewProviderWindLabFeatureLocationDistribution::~ViewProviderWindLabFeatureLocationDistribution()
{

}

bool ViewProviderWindLabFeatureLocationDistribution::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderWindLabFeatureLocationDistribution::ActivateFeature()
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
    if (true == parentSim->Stationarity.getValue() && false == isfeatureStationary)
    {
        Base::Console().Warning("Simulation stationarity and that of the feature does not match. The feature couldn't be activated.\n");
        return false;
    }

    WindLabGui::WindLabSimulationObserver::instance()->setActiveSimulation(parentSim);

    parentSim->SpatialDistribution.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderWindLabFeatureLocationDistribution::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {

        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderWindLabFeatureLocationDistribution::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderWindLabFeatureLocationDistribution::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);

    QAction* cvector = menu->addAction(QObject::tr("Compute Location Array"));
    func->trigger(cvector, boost::bind(&ViewProviderWindLabFeatureLocationDistribution::ComputeLocationCoordinateMatrixP3, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderWindLabFeatureLocationDistribution::OnInitialSetting, this));

    QAction* act = menu->addAction(QObject::tr("Activate Feature"));
    func->trigger(act, boost::bind(&ViewProviderWindLabFeatureLocationDistribution::ActivateFeature, this));
}


bool ViewProviderWindLabFeatureLocationDistribution::ComputeLocationCoordinateMatrixP3()
{
    if (ShowSimulationPoints.getValue())
    {
        //compute and show the active simulation points in the 3D view and Alphaplot table
        Base::Interpreter().runString("import WindLabUtils");
        Base::Interpreter().runString("WindLabUtils.showSimulationPoints()");
        return true;
    }
    else
    {
        //compute and show the active simulation points in the Alphaplot table only
        return runFeatureMethod(WindLab::WindLabUtils::ComputeLocationCoordinateMatrixP3);
    }

}

bool ViewProviderWindLabFeatureLocationDistribution::OnInitialSetting()
{
    ActivateFeature();
    WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}
    sim->windLabFeatureInitalSetting(WindLab::WindLabUtils::objGroupLocationDistribution, QString::fromUtf8(sim->getSimulationData()->spatialDistribution.getValue()));
    return true;
}

void ViewProviderWindLabFeatureLocationDistribution::onChanged(const App::Property* prop)
{
   ViewProviderDocumentObject::onChanged(prop);
}


PyObject* ViewProviderWindLabFeatureLocationDistribution::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderWindLabFeatureLocationDistributionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool ViewProviderWindLabFeatureLocationDistribution::getComputationResultVariableVector(vec& resultVectorVar)
{
    if (!windLabAllFeaturesComputation)
        return false;
    resultVectorVar = windLabAllFeaturesComputation->GetWindLabSimulationWorker()->m_ResultVectorVar;
    return true;
}
bool ViewProviderWindLabFeatureLocationDistribution::getComputationResultValueVector(vec& resultVectorVal)
{
    if (!windLabAllFeaturesComputation)
        return false;
    resultVectorVal = windLabAllFeaturesComputation->GetWindLabSimulationWorker()->m_ResultVectorVal;
    return true;
}
bool ViewProviderWindLabFeatureLocationDistribution::getComputationResultComplexValueVector(cx_vec& resultVectorVal_cx)
{
    if (!windLabAllFeaturesComputation)
        return false;
    resultVectorVal_cx = windLabAllFeaturesComputation->GetWindLabSimulationWorker()->m_ResultVectorVal_cx;
    return true;
}
bool ViewProviderWindLabFeatureLocationDistribution::getComputationResultMatrix(mat& resultMatrix)
{
     if (!windLabAllFeaturesComputation)
        return false;
     resultMatrix = windLabAllFeaturesComputation->GetWindLabSimulationWorker()->m_ResultMatrix;
    return true;
}
bool ViewProviderWindLabFeatureLocationDistribution::getComputationResultComplexMatrix(cx_mat& resultMatrix_cx)
{
     if (!windLabAllFeaturesComputation)
        return false;
     resultMatrix_cx = windLabAllFeaturesComputation->GetWindLabSimulationWorker()->m_ResultMatrix_cx;
    return true;
}

bool ViewProviderWindLabFeatureLocationDistribution::runFeatureMethod(const QString function, const char* complexNumberDisplay)
{  
    ActivateFeature();
    WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}
    windLabAllFeaturesComputation = new WindLabAllFeaturesComputation(sim);
    windLabAllFeaturesComputation->startSimulationWorker(function, complexNumberDisplay);
    windLabAllFeaturesComputation->getWindLabSimulationThread()->start();
    return true;
}

