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

#include "ViewProviderWindLabFeatureCoherence.h"
#include "ViewProviderWindLabFeatureCoherencePy.h"

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
#include <Mod/WindLabAPI/App/IrpsWLCoherence.h>
#include <CXX/Objects.hxx>
#include <Gui/Command.h>

using namespace WindLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(WindLabGui::ViewProviderWindLabFeatureCoherence, Gui::ViewProviderRPSFeature)


ViewProviderWindLabFeatureCoherence::ViewProviderWindLabFeatureCoherence()
{
    static const char* complexDisplayGroup = "Complex Display";
    static const char* complexRealImagEnum[] = {"Real", "Imaginary", nullptr};
    
    ADD_PROPERTY_TYPE(ComplexNumberDisplay, ((long int)0), complexDisplayGroup, App::Prop_None, "This specifies how to display the complex numbers.");

    ComplexNumberDisplay.setEnums(complexRealImagEnum);

    sPixmap = ":/icons/WindLabFeatures/WindLab_Feature_CoherenceObj.svg";
}

ViewProviderWindLabFeatureCoherence::~ViewProviderWindLabFeatureCoherence()
{

}

bool ViewProviderWindLabFeatureCoherence::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderWindLabFeatureCoherence::ActivateFeature()
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
    if (!parentSim) {Base::Console().Error("The parent simulation of the selected feature couldn't be actived.\n");return false;}

    bool isfeatureStationary = static_cast<WindLabAPI::WindLabFeature*>(obj)->IsStationary.getValue();
    if (true == parentSim->Stationarity.getValue() && false == isfeatureStationary)
    {
        Base::Console().Error("Simulation stationarity and that of the feature does not match. The feature couldn't be activated.\n");
        return false;
    }

    WindLabGui::WindLabSimulationObserver::instance()->setActiveSimulation(parentSim);

    parentSim->CoherenceFunction.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderWindLabFeatureCoherence::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {

        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderWindLabFeatureCoherence::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderWindLabFeatureCoherence::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);

    QAction* val = menu->addAction(QObject::tr("ComputeCrossCoherenceValue"));
    func->trigger(val, boost::bind(&ViewProviderWindLabFeatureCoherence::ComputeCrossCoherenceValue, this));

    QAction* carrayF = menu->addAction(QObject::tr("ComputeCrossCoherenceVectorF"));
    func->trigger(carrayF, boost::bind(&ViewProviderWindLabFeatureCoherence::ComputeCrossCoherenceVectorF, this));

    QAction* carray = menu->addAction(QObject::tr("ComputeCrossCoherenceVectorT"));
    func->trigger(carray, boost::bind(&ViewProviderWindLabFeatureCoherence::ComputeCrossCoherenceVectorT, this));

    QAction* carrayPP = menu->addAction(QObject::tr("ComputeCrossCoherenceMatrixPP"));
    func->trigger(carrayPP, boost::bind(&ViewProviderWindLabFeatureCoherence::ComputeCrossCoherenceMatrixPP, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderWindLabFeatureCoherence::OnInitialSetting, this));

    QAction* act = menu->addAction(QObject::tr("Activate Feature"));
    func->trigger(act, boost::bind(&ViewProviderWindLabFeatureCoherence::ActivateFeature, this));

    QAction* gtp = menu->addAction(QObject::tr("Go to Publication"));
    func->trigger(gtp, boost::bind(&ViewProviderWindLabFeatureCoherence::goToPublication, this));

  }

bool ViewProviderWindLabFeatureCoherence::ComputeCrossCoherenceValue() 
{
   return runFeatureMethod(WindLab::WindLabUtils::ComputeCrossCoherenceValue, this->ComplexNumberDisplay.getValueAsString());
}

bool ViewProviderWindLabFeatureCoherence::ComputeCrossCoherenceVectorT()
{
    return runFeatureMethod(WindLab::WindLabUtils::ComputeCrossCoherenceVectorT, this->ComplexNumberDisplay.getValueAsString());
}

bool ViewProviderWindLabFeatureCoherence::ComputeCrossCoherenceVectorF()
{
    return runFeatureMethod(WindLab::WindLabUtils::ComputeCrossCoherenceVectorF, this->ComplexNumberDisplay.getValueAsString());
}

bool ViewProviderWindLabFeatureCoherence::ComputeCrossCoherenceMatrixPP()
{
    return runFeatureMethod(WindLab::WindLabUtils::ComputeCrossCoherenceMatrixPP, this->ComplexNumberDisplay.getValueAsString());
}


bool ViewProviderWindLabFeatureCoherence::OnInitialSetting()
{
ActivateFeature();
    WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    sim->windLabFeatureInitalSetting(WindLab::WindLabUtils::objGroupCoherenceFunction, QString::fromUtf8(sim->getSimulationData()->coherenceFunction.getValue()));
    return true;
}


void ViewProviderWindLabFeatureCoherence::onChanged(const App::Property* prop)
{
    if (prop == &ComplexNumberDisplay) {

    }
    ViewProviderDocumentObject::onChanged(prop);
}

PyObject* ViewProviderWindLabFeatureCoherence::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderWindLabFeatureCoherencePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}


bool ViewProviderWindLabFeatureCoherence::runFeatureMethod(const QString function, const char* complexNumberDisplay)
{
     
    ActivateFeature();
    WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    WindLabGui::ViewProviderWindLabSimulation* vp = dynamic_cast<WindLabGui::ViewProviderWindLabSimulation*>(Gui::Application::Instance->getViewProvider(sim));
    if (sim->isRuning())
    {
        Base::Console().Error("A simulation is running, please stop it first.\n");
        return false;
    }

    vp->setAllComputation(new WindLabAllFeaturesComputation(sim));
    vp->getAllComputation()->startSimulationWorker(function, complexNumberDisplay);
    vp->getAllComputation()->getWindLabSimulationThread()->start();

    return true;
    
}