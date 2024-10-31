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

#include "ViewProviderSeaLabFeatureSpectrum.h"
#include "ViewProviderSeaLabFeatureSpectrumPy.h"

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
#include <Mod/SeaLabAPI/App/IrpsSeLSpectrum.h>

using namespace SeaLabGui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(SeaLabGui::ViewProviderSeaLabFeatureSpectrum, Gui::ViewProviderRPSFeature)


ViewProviderSeaLabFeatureSpectrum::ViewProviderSeaLabFeatureSpectrum()
{
    static const char* complexDisplayGroup = "Complex Number Display";
    static const char* complexRealImagEnum[] = {"Real", "Imaginary", nullptr};
    
    ADD_PROPERTY_TYPE(ComplexNumberDisplay, ((long int)0), complexDisplayGroup, App::Prop_None, "This specifies how to display the complex numbers.");

    ComplexNumberDisplay.setEnums(complexRealImagEnum);

  sPixmap = ":/icons/SeaLabFeatures/SeaLab_Feature_SpectrumObj.svg";
}

ViewProviderSeaLabFeatureSpectrum::~ViewProviderSeaLabFeatureSpectrum()
{

}

bool ViewProviderSeaLabFeatureSpectrum::doubleClicked(void)
{
    ActivateFeature();
    Gui::Application::Instance->activeDocument()->setEdit(this);
    OnInitialSetting();
    return true;
}

bool ViewProviderSeaLabFeatureSpectrum::ActivateFeature()
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
    if (true == parentSim->Stationarity.getValue() && false == isfeatureStationary)
    {
        Base::Console().Warning("Simulation stationarity and that of the feature does not match. The feature couldn't be activated.\n");
        return false;
    }

    SeaLabGui::SeaLabSimulationObserver::instance()->setActiveSimulation(parentSim);

    parentSim->SpectrumModel.setValue(obj->getNameInDocument());
    return true;
}

bool ViewProviderSeaLabFeatureSpectrum::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {

        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderSeaLabFeatureSpectrum::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderSeaLabFeatureSpectrum::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    // toggle command to display components
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* cvalue = menu->addAction(QObject::tr("ComputeCrossSpectrumValue"));
    func->trigger(cvalue, boost::bind(&ViewProviderSeaLabFeatureSpectrum::computeCrossSpectrumValue, this));

    QAction* cvector = menu->addAction(QObject::tr("ComputeCrossSpectrumVectorF"));
    func->trigger(cvector, boost::bind(&ViewProviderSeaLabFeatureSpectrum::computeCrossSpectrumVectorF, this));

    QAction* carray = menu->addAction(QObject::tr("ComputeCrossSpectrumVectorT"));
    func->trigger(carray, boost::bind(&ViewProviderSeaLabFeatureSpectrum::computeCrossSpectrumVectorT, this));

    QAction* cmatrix = menu->addAction(QObject::tr("ComputeCrossSpectrumMatrixPP"));
    func->trigger(cmatrix, boost::bind(&ViewProviderSeaLabFeatureSpectrum::computeCrossSpectrumMatrixPP, this));

    
    QAction* autoValue = menu->addAction(QObject::tr("ComputeAutoSpectrumValue"));
    func->trigger(autoValue, boost::bind(&ViewProviderSeaLabFeatureSpectrum::computeAutoSpectrumValue, this));

    QAction* autoF = menu->addAction(QObject::tr("ComputeAutoSpectrumVectorF"));
    func->trigger(autoF, boost::bind(&ViewProviderSeaLabFeatureSpectrum::computeAutoSpectrumVectorF, this));

    QAction* autoT = menu->addAction(QObject::tr("ComputeAutoSpectrumVectorT"));
    func->trigger(autoT, boost::bind(&ViewProviderSeaLabFeatureSpectrum::computeAutoSpectrumVectorT, this));

    QAction* init = menu->addAction(QObject::tr("Setup Feature"));
    func->trigger(init, boost::bind(&ViewProviderSeaLabFeatureSpectrum::OnInitialSetting, this));

    QAction* act = menu->addAction(QObject::tr("Activate Feature"));
    func->trigger(act, boost::bind(&ViewProviderSeaLabFeatureSpectrum::ActivateFeature, this));

    QAction* gtp = menu->addAction(QObject::tr("Go to Publication"));
    func->trigger(gtp, boost::bind(&ViewProviderSeaLabFeatureSpectrum::goToPublication, this));
}

bool ViewProviderSeaLabFeatureSpectrum::computeCrossSpectrumValue()
{
    
    return runFeatureMethod(SeaLab::SeaLabUtils::ComputeCrossSpectrumValue, this->ComplexNumberDisplay.getValueAsString());
    
}


bool ViewProviderSeaLabFeatureSpectrum::computeCrossSpectrumVectorT()
{
    
    return runFeatureMethod(SeaLab::SeaLabUtils::ComputeCrossSpectrumVectorT, this->ComplexNumberDisplay.getValueAsString());
    
}

bool ViewProviderSeaLabFeatureSpectrum::computeAutoSpectrumValue()
{
    
    return runFeatureMethod(SeaLab::SeaLabUtils::ComputeAutoSpectrumValue);
    
}
bool ViewProviderSeaLabFeatureSpectrum::computeAutoSpectrumVectorF()
{
    
    return runFeatureMethod(SeaLab::SeaLabUtils::ComputeAutoSpectrumVectorF);
    
}
bool ViewProviderSeaLabFeatureSpectrum::computeAutoSpectrumVectorT()
{
    
    return runFeatureMethod(SeaLab::SeaLabUtils::ComputeAutoSpectrumVectorT);
    
}

bool ViewProviderSeaLabFeatureSpectrum::computeCrossSpectrumVectorF()
{
    
    return runFeatureMethod(SeaLab::SeaLabUtils::ComputeCrossSpectrumVectorF, this->ComplexNumberDisplay.getValueAsString());
    
}

bool ViewProviderSeaLabFeatureSpectrum::computeCrossSpectrumMatrixPP()
{
    
    return runFeatureMethod(SeaLab::SeaLabUtils::ComputeCrossSpectrumMatrixPP, this->ComplexNumberDisplay.getValueAsString());
    
}

bool ViewProviderSeaLabFeatureSpectrum::OnInitialSetting()
{
ActivateFeature();
    SeaLab::SeaLabSimulation* sim = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    sim->seaLabFeatureInitalSetting(SeaLab::SeaLabUtils::objGroupSpectrum, QString::fromUtf8(sim->getSimulationData()->spectrumModel.getValue()));
     
    return true;
}

PyObject* ViewProviderSeaLabFeatureSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderSeaLabFeatureSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool ViewProviderSeaLabFeatureSpectrum::runFeatureMethod(const QString function, const char* complexNumberDisplay)
{  
ActivateFeature();
    SeaLab::SeaLabSimulation* sim = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
    if (!sim) {Base::Console().Warning("No valide active simulation found.\n");return false;}

    seaLabAllFeaturesComputation = new SeaLabAllFeaturesComputation(sim);
    seaLabAllFeaturesComputation->startSimulationWorker(function, complexNumberDisplay);
    seaLabAllFeaturesComputation->getSeaLabSimulationThread()->start();
    return true;
}