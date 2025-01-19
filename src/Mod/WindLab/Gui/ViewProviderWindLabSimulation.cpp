/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>          *
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
# include <boost_bind_bind.hpp>
# include <QAction>
# include <QApplication>
# include <QMenu>
# include <QMessageBox>
# include <QTextStream>
#endif

#include "ViewProviderWindLabSimulation.h"
#include "ViewProviderWindLabSimulationPy.h"

#include <App/TextDocument.h>
#include <Gui/ActionFunction.h>
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/MainWindow.h>

#include <Mod/WindLab/Gui/WindLabSimulationObserver.h>
#include <App/Simulation.h>
#include <Mod/WindLab/App/WindLabSimulation.h>
#include <Mod/WindLabAPI/App/WindLabFeature.h>
#include <Gui/Document.h>
#include <Gui/Application.h>
#include <App/Document.h>
#include "Control.h"
#include "ViewProviderWindLabFeatureSimulationMethod.h"

#include <Mod/WindLabAPI/App/WindLabFeatureLocationDistribution.h>
#include <Mod/WindLabAPI/App/WindLabFeatureMeanWind.h>
#include <Mod/WindLabAPI/App/WindLabFeatureXSpectrum.h>
#include <Mod/WindLabAPI/App/WindLabFeatureZSpectrum.h>
#include <Mod/WindLabAPI/App/WindLabFeatureYSpectrum.h>
#include <Mod/WindLabAPI/App/WindLabFeaturePSDDecompositionMethod.h> 
#include <Mod/WindLabAPI/App/WindLabFeatureCoherence.h>
#include <Mod/WindLabAPI/App/WindLabFeatureSimulationMethod.h>
#include <Mod/WindLabAPI/App/WindLabFeatureFrequencyDistribution.h>
#include <Mod/WindLabAPI/App/WindLabFeatureRandomness.h>
#include <Mod/WindLabAPI/App/WindLabFeatureModulation.h>
#include <Mod/WindLabAPI/App/WindLabFeatureCorrelation.h>
#include <Mod/WindLabAPI/App/WindLabFeatureTableTool.h>
#include <Mod/WindLabAPI/App/WindLabFeatureMatrixTool.h>
#include <Mod/WindLabAPI/App/WindLabFeatureCumulativeProbabilityDistribution.h>
#include <Mod/WindLabAPI/App/WindLabFeatureGustFactor.h>
#include <Mod/WindLabAPI/App/WindLabFeatureKurtosis.h>
#include <Mod/WindLabAPI/App/WindLabFeaturePeakFactor.h>
#include <Mod/WindLabAPI/App/WindLabFeatureProbabilityDensityFunction.h>
#include <Mod/WindLabAPI/App/WindLabFeatureRoughness.h>
#include <Mod/WindLabAPI/App/WindLabFeatureShearVelocityOfFlow.h>
#include <Mod/WindLabAPI/App/WindLabFeatureSkewness.h>
#include <Mod/WindLabAPI/App/WindLabFeatureStandardDeviation.h>
#include <Mod/WindLabAPI/App/WindLabFeatureTurbulenceIntensity.h>
#include <Mod/WindLabAPI/App/WindLabFeatureTurbulenceScale.h>
#include <Mod/WindLabAPI/App/WindLabFeatureVariance.h>
#include <Mod/WindLabAPI/App/WindLabFeatureWavePassageEffect.h>
#include <Mod/WindLabAPI/App/WindLabFeatureUserDefinedRPSObject.h>
#include <Mod/WindLabAPI/App/WindLabFeatureMatrixTool.h>
#include <Mod/WindLabAPI/App/WindLabFeatureTableTool.h>
#include <Gui/Command.h>
#include <App/AutoTransaction.h>
#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>

using namespace WindLabGui;
using namespace Gui;

// ----------------------------------------------------------------------------

/* TRANSLATOR WindLabGui::ViewProviderWindLabSimulation */

PROPERTY_SOURCE(WindLabGui::ViewProviderWindLabSimulation, Gui::ViewProviderDocumentObjectGroup)


ViewProviderWindLabSimulation::ViewProviderWindLabSimulation()
{
    sPixmap = "WindLab_CreateSimulation";
}

ViewProviderWindLabSimulation::~ViewProviderWindLabSimulation()
{

}

void ViewProviderWindLabSimulation::attach(App::DocumentObject* obj)
{
    Gui::ViewProviderDocumentObjectGroup::attach(obj);
}

void ViewProviderWindLabSimulation::highlightView(Gui::ViewProviderDocumentObject* view)
{
}

bool ViewProviderWindLabSimulation::doubleClicked(void)
{
    Gui::Command::assureWorkbench("WindLabWorkbench");
    Gui::Command::addModule(Gui::Command::Gui, "WindLabGui");
    Gui::Command::doCommand(Gui::Command::Gui,
                            "WindLabGui.setActiveSimulation(App.activeDocument().%s)",
                            this->getObject()->getNameInDocument());
    Gui::Command::doCommand(Gui::Command::Gui, "Gui.Selection.clearSelection()");
    std::vector<App::DocumentObject*> selVector {};
    selVector.push_back(this->getObject());
    auto *docName = this->getObject()->getDocument()->getName();
    Gui::Selection().setSelection(docName, selVector);
    return true;
}

bool ViewProviderWindLabSimulation::run()
{
    WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    
    if (sim->isRuning())
    {
        Base::Console().Error("This simulation is already running.\n");
        return false;
    }

    auto activeMethod = sim->getActiveSimulationMethod();

    if (!activeMethod) {
        sim->setStatus(App::SimulationStatus::Failed, true);
        return false;
    }
    
    WindLabGui::ViewProviderWindLabFeatureSimulationMethod* vp = dynamic_cast<WindLabGui::ViewProviderWindLabFeatureSimulationMethod*>(Gui::Application::Instance->getViewProvider(activeMethod));

    if (!vp) {
        sim->setStatus(App::SimulationStatus::Failed, true);
        return false;
    }

    vp->simulate();
    
    sim->setStatus(App::SimulationStatus::Running, true);
    return true;
}

bool ViewProviderWindLabSimulation::stop()
{
    WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    
    if (!sim->isRuning())
    {
        Base::Console().Warning("This simulation is not running.\n");
        return false;
    }
    auto worker = getAllComputation()->GetWindLabSimulationWorker();
    if (worker) {
        getAllComputation()->GetWindLabSimulationWorker()->stop();
    }
 
    if (windLabAllFeaturesComputation)
    Q_EMIT windLabAllFeaturesComputation->stopped();

    return true;
}

bool ViewProviderWindLabSimulation::activateSimulation() { return doubleClicked(); }

std::vector<App::DocumentObject*> ViewProviderWindLabSimulation::claimChildren(void)const
{
    return Gui::ViewProviderDocumentObjectGroup::claimChildren();
}

std::vector<std::string> ViewProviderWindLabSimulation::getDisplayModes(void) const
{
    return { "WindLabSimulation" };
}

bool ViewProviderWindLabSimulation::refresh() {
    std::vector<App::Simulation*> sims = WindLabGui::WindLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<WindLab::WindLabSimulation*>(*it)->resetAllEnums();
    }

    Gui::Document* doc = Gui::Application::Instance->activeDocument();
 
	App::AutoTransaction trans("Recompute");
    Command::doCommand(Command::Doc, "App.getDocument(\"%s\").recompute()", doc->getDocument()->getName());

    return true;
}

void ViewProviderWindLabSimulation::hide(void)
{
    Gui::ViewProviderDocumentObjectGroup::hide();
}

void ViewProviderWindLabSimulation::show(void)
{
    Gui::ViewProviderDocumentObjectGroup::show();
}

void ViewProviderWindLabSimulation::setupContextMenu(QMenu* menu, QObject* , const char* )
{
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* act = menu->addAction(QString::fromLatin1("Activate Simulation"));
    func->trigger(act, boost::bind(&ViewProviderWindLabSimulation::doubleClicked, this));

    QAction* run = menu->addAction(QString::fromLatin1("Run"));
    func->trigger(run, boost::bind(&ViewProviderWindLabSimulation::run, this));

    QAction* stop = menu->addAction(QString::fromLatin1("Stop"));
    func->trigger(stop, boost::bind(&ViewProviderWindLabSimulation::stop, this));

     QAction* refresh = menu->addAction(QString::fromLatin1("Refresh"));
    func->trigger(refresh, boost::bind(&ViewProviderWindLabSimulation::refresh, this));
}


bool ViewProviderWindLabSimulation::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default ) {        
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObjectGroup::setEdit(ModNum);
    }
}

void ViewProviderWindLabSimulation::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObjectGroup::unsetEdit(ModNum);
    }
}

bool ViewProviderWindLabSimulation::canDragObjects() const
{
    return true;
}

bool ViewProviderWindLabSimulation::canDragObject(App::DocumentObject* obj) const
{
     if (!obj)
        return false;

    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureLocationDistribution::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureMeanWind ::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureXSpectrum::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureZSpectrum::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureYSpectrum::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeaturePSDDecompositionMethod::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureCoherence::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureSimulationMethod::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureFrequencyDistribution::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureRandomness::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureModulation::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureCorrelation::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureTableTool::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureMatrixTool::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution::getClassTypeId())) return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureGustFactor::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureKurtosis::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeaturePeakFactor::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureProbabilityDensityFunction::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureRoughness::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureShearVelocityOfFlow::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureSkewness::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureStandardDeviation::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureTurbulenceIntensity::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureTurbulenceScale::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureVariance::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureWavePassageEffect::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( WindLabAPI::WindLabFeatureUserDefinedRPSObject::getClassTypeId())) 
        return true;
    else if (obj->getTypeId().isDerivedFrom(Base::Type::fromName("App::FeaturePython")))
        return true;
    else if (obj->getTypeId().isDerivedFrom(App::TextDocument::getClassTypeId()))
        return true;
    else
        return false;
}

void ViewProviderWindLabSimulation::dragObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dragObject(obj);
}

bool ViewProviderWindLabSimulation::canDropObjects() const
{
    return true;
}

bool ViewProviderWindLabSimulation::canDropObject(App::DocumentObject* obj) const
{
    return canDragObject(obj);
}

void ViewProviderWindLabSimulation::dropObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dropObject(obj);
   
    std::vector<App::Simulation*> sims = WindLabGui::WindLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<WindLab::WindLabSimulation*>(*it)->resetAllEnums();
    }
}

bool ViewProviderWindLabSimulation::onDelete(const std::vector<std::string>&)
{
    // warn the user if the object has unselected children
    auto objs = claimChildren();
    return checkSelectedChildren(objs, this->getDocument(), "WindLab simulation");
}

bool ViewProviderWindLabSimulation::canDelete(App::DocumentObject* obj) const
{
    // deletions of objects from a WindLabSimulation don't necessarily destroy anything
    // thus we can pass this action
    // we can warn the user if necessary in the object's ViewProvider in the onDelete() function
    Q_UNUSED(obj)
    return true;
}

bool ViewProviderWindLabSimulation::checkSelectedChildren(const std::vector<App::DocumentObject*> objs,
                                                    Gui::Document* docGui, std::string objectName)
{
    // warn the user if the object has unselected children
    if (!objs.empty()) {
        // check if all children are in the selection
        bool found = false;
        auto selectionList = Gui::Selection().getSelectionEx(docGui->getDocument()->getName());
        for (auto child : objs) {
            found = false;
            for (Gui::SelectionObject selection : selectionList) {
                if (std::string(child->getNameInDocument())
                    == std::string(selection.getFeatName())) {
                    found = true;
                    break;
                }
            }
            if (!found)
                break;
        }
        if (found)// all children are selected too
            return true;

        // generate dialog
        QString bodyMessage;
        QTextStream bodyMessageStream(&bodyMessage);
        bodyMessageStream << qApp->translate("Std_Delete",
            ("The " + objectName + " is not empty, therefore the\nfollowing "
             "referencing objects might be lost:").c_str());
        bodyMessageStream << '\n';
        for (auto ObjIterator : objs)
            bodyMessageStream << '\n' << QString::fromUtf8(ObjIterator->Label.getValue());
        bodyMessageStream << "\n\n" << QObject::tr("Are you sure you want to continue?");
        // show and evaluate the dialog
        int DialogResult = QMessageBox::warning(Gui::getMainWindow(),
            qApp->translate("Std_Delete", "Object dependencies"), bodyMessage,
            QMessageBox::Yes, QMessageBox::No);
        if (DialogResult == QMessageBox::Yes)
            return true;
        else
            return false;
    }
    else {
        return true;
    }
}

WindLabAllFeaturesComputation* ViewProviderWindLabSimulation::getAllComputation()
{
    return windLabAllFeaturesComputation;
}
void ViewProviderWindLabSimulation::setAllComputation(WindLabAllFeaturesComputation* computation)
{
    windLabAllFeaturesComputation = computation;
}

PyObject* ViewProviderWindLabSimulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderWindLabSimulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}