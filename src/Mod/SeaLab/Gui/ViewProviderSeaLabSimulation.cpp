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

#include "ViewProviderSeaLabSimulation.h"
#include "ViewProviderSeaLabSimulationPy.h"

#include <App/TextDocument.h>
#include <Gui/ActionFunction.h>
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/MainWindow.h>

#include <Mod/SeaLab/Gui/SeaLabSimulationObserver.h>
#include <App/Simulation.h>
#include <Mod/SeaLab/App/SeaLabSimulation.h>
#include <Mod/SeaLabAPI/App/SeaLabFeature.h>
#include <Gui/Document.h>
#include <Gui/Application.h>
#include <App/Document.h>
#include "Control.h"
#include "ViewProviderSeaLabFeatureSimulationMethod.h"

#include <Mod/SeaLabAPI/App/SeaLabFeatureLocationDistribution.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureMeanAcceleration.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureSpectrum.h>
#include <Mod/SeaLabAPI/App/SeaLabFeaturePSDDecompositionMethod.h> 
#include <Mod/SeaLabAPI/App/SeaLabFeatureCoherence.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureSimulationMethod.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureFrequencyDistribution.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureRandomness.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureModulation.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureCorrelation.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureTableTool.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureMatrixTool.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureCumulativeProbabilityDistribution.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureKurtosis.h>
#include <Mod/SeaLabAPI/App/SeaLabFeaturePeakFactor.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureProbabilityDensityFunction.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureShearVelocityOfFlow.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureSkewness.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureStandardDeviation.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureVariance.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureWavePassageEffect.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureUserDefinedRPSObject.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureMatrixTool.h>
#include <Mod/SeaLabAPI/App/SeaLabFeatureTableTool.h>
#include <Gui/Command.h>
#include <App/AutoTransaction.h>
#include <Mod/SeaLabAPI/App/IrpsSeLSimulationMethod.h>

using namespace SeaLabGui;
using namespace Gui;

// ----------------------------------------------------------------------------

/* TRANSLATOR SeaLabGui::ViewProviderSeaLabSimulation */

PROPERTY_SOURCE(SeaLabGui::ViewProviderSeaLabSimulation, Gui::ViewProviderDocumentObjectGroup)


ViewProviderSeaLabSimulation::ViewProviderSeaLabSimulation()
{
    sPixmap = "SeaLab_NewSimulation";
}

ViewProviderSeaLabSimulation::~ViewProviderSeaLabSimulation()
{

}

void ViewProviderSeaLabSimulation::attach(App::DocumentObject* obj)
{
    Gui::ViewProviderDocumentObjectGroup::attach(obj);
}

void ViewProviderSeaLabSimulation::highlightView(Gui::ViewProviderDocumentObject* view)
{
}

bool ViewProviderSeaLabSimulation::doubleClicked(void)
{
    Gui::Command::assureWorkbench("SeaLabWorkbench");
    Gui::Command::addModule(Gui::Command::Gui, "SeaLabGui");
    Gui::Command::doCommand(Gui::Command::Gui,
                            "SeaLabGui.setActiveSimulation(App.activeDocument().%s)",
                            this->getObject()->getNameInDocument());
    Gui::Command::doCommand(Gui::Command::Gui, "Gui.Selection.clearSelection()");
    std::vector<App::DocumentObject*> selVector {};
    selVector.push_back(this->getObject());
    auto *docName = this->getObject()->getDocument()->getName();
    Gui::Selection().setSelection(docName, selVector);
    return true;
}

bool ViewProviderSeaLabSimulation::run()
{
     SeaLab::SeaLabSimulation* sim = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    auto activeMethod = sim->getActiveSimulationMethod();

    if (!activeMethod) {
        sim->setStatus(App::SimulationStatus::Failed, true);
        return false;
    }
    SeaLabGui::ViewProviderSeaLabFeatureSimulationMethod* vp = dynamic_cast<SeaLabGui::ViewProviderSeaLabFeatureSimulationMethod*>(Gui::Application::Instance->getViewProvider(activeMethod));

    if (!vp) {
        sim->setStatus(App::SimulationStatus::Failed, true);
        return false;
    }

    if (!sim->getSimulationData()->largeScaleSimulationMode.getValue())
    {
        vp->simulate();
    }
    else
    {
        vp->simulateInLargeScaleMode();
    }
    
    sim->setStatus(App::SimulationStatus::Running, true);
    return true;
}

bool ViewProviderSeaLabSimulation::stop()
{
     SeaLab::SeaLabSimulation* sim = static_cast<SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    
    if (!sim->isRuning())
    {
        Base::Console().Warning("This simulation is not running.\n");
        return false;
    }
    auto worker = getAllComputation()->GetSeaLabSimulationWorker();
    if (worker) {
        getAllComputation()->GetSeaLabSimulationWorker()->stop();
    }
 
    if (seaLabAllFeaturesComputation)
        Q_EMIT seaLabAllFeaturesComputation->stopped();

    return true;
}

bool ViewProviderSeaLabSimulation::activateSimulation() { return doubleClicked(); }

std::vector<App::DocumentObject*> ViewProviderSeaLabSimulation::claimChildren(void)const
{
    return Gui::ViewProviderDocumentObjectGroup::claimChildren();
}

std::vector<std::string> ViewProviderSeaLabSimulation::getDisplayModes(void) const
{
    return { "SeaLabSimulation" };
}

bool ViewProviderSeaLabSimulation::refresh() {
    std::vector<App::Simulation*> sims = SeaLabGui::SeaLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<SeaLab::SeaLabSimulation*>(*it)->resetAllEnums();
    }

    Gui::Document* doc = Gui::Application::Instance->activeDocument();

	App::AutoTransaction trans("Recompute");
    Command::doCommand(Command::Doc, "App.getDocument(\"%s\").recompute()", doc->getDocument()->getName());

    return true;
}

void ViewProviderSeaLabSimulation::hide(void)
{
    Gui::ViewProviderDocumentObjectGroup::hide();
}

void ViewProviderSeaLabSimulation::show(void)
{
    Gui::ViewProviderDocumentObjectGroup::show();
}

void ViewProviderSeaLabSimulation::setupContextMenu(QMenu* menu, QObject* , const char* )
{
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* act = menu->addAction(QString::fromLatin1("Activate Simulation"));
    func->trigger(act, boost::bind(&ViewProviderSeaLabSimulation::doubleClicked, this));

    QAction* run = menu->addAction(QString::fromLatin1("Run"));
    func->trigger(run, boost::bind(&ViewProviderSeaLabSimulation::run, this));

    QAction* stop = menu->addAction(QString::fromLatin1("Stop"));
    func->trigger(stop, boost::bind(&ViewProviderSeaLabSimulation::stop, this));

     QAction* refresh = menu->addAction(QString::fromLatin1("Refresh"));
    func->trigger(refresh, boost::bind(&ViewProviderSeaLabSimulation::refresh, this));
}


bool ViewProviderSeaLabSimulation::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default ) {        
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObjectGroup::setEdit(ModNum);
    }
}

void ViewProviderSeaLabSimulation::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObjectGroup::unsetEdit(ModNum);
    }
}

bool ViewProviderSeaLabSimulation::canDragObjects() const
{
    return true;
}

bool ViewProviderSeaLabSimulation::canDragObject(App::DocumentObject* obj) const
{
     if (!obj)
        return false;

    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureLocationDistribution::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureMeanAcceleration ::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureSpectrum::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeaturePSDDecompositionMethod::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureCoherence::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureSimulationMethod::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureFrequencyDistribution::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureRandomness::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureModulation::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureCorrelation::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureTableTool::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureMatrixTool::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureCumulativeProbabilityDistribution::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureKurtosis::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeaturePeakFactor::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureProbabilityDensityFunction::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureShearVelocityOfFlow::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureSkewness::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureStandardDeviation::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureVariance::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureWavePassageEffect::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeaLabAPI::SeaLabFeatureUserDefinedRPSObject::getClassTypeId())) 
        return true;
    else if (obj->getTypeId().isDerivedFrom(Base::Type::fromName("App::FeaturePython")))
        return true;
    else if (obj->getTypeId().isDerivedFrom(App::TextDocument::getClassTypeId()))
        return true;
    else
        return false;
}

void ViewProviderSeaLabSimulation::dragObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dragObject(obj);
}

bool ViewProviderSeaLabSimulation::canDropObjects() const
{
    return true;
}

bool ViewProviderSeaLabSimulation::canDropObject(App::DocumentObject* obj) const
{
    return canDragObject(obj);
}

void ViewProviderSeaLabSimulation::dropObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dropObject(obj);
   
    std::vector<App::Simulation*> sims = SeaLabGui::SeaLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<SeaLab::SeaLabSimulation*>(*it)->resetAllEnums();
    }
}

bool ViewProviderSeaLabSimulation::onDelete(const std::vector<std::string>&)
{
    // warn the user if the object has unselected children
    auto objs = claimChildren();
    return checkSelectedChildren(objs, this->getDocument(), "SeaLab simulation");
}

bool ViewProviderSeaLabSimulation::canDelete(App::DocumentObject* obj) const
{
    // deletions of objects from a SeaLabSimulation don't necessarily destroy anything
    // thus we can pass this action
    // we can warn the user if necessary in the object's ViewProvider in the onDelete() function
    Q_UNUSED(obj)
    return true;
}

bool ViewProviderSeaLabSimulation::checkSelectedChildren(const std::vector<App::DocumentObject*> objs,
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

SeaLabAllFeaturesComputation* ViewProviderSeaLabSimulation::getAllComputation()
{
    return seaLabAllFeaturesComputation;
}
void ViewProviderSeaLabSimulation::setAllComputation(SeaLabAllFeaturesComputation* computation)
{
    seaLabAllFeaturesComputation = computation;
}

PyObject* ViewProviderSeaLabSimulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderSeaLabSimulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}