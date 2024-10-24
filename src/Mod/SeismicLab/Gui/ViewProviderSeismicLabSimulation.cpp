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

#include <App/TextDocument.h>
#include <Gui/ActionFunction.h>
#include "ViewProviderSeismicLabSimulation.h"
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/MainWindow.h>

#include <Mod/SeismicLab/Gui/SeismicLabSimulationObserver.h>
#include <App/Simulation.h>
#include <Mod/SeismicLab/App/SeismicLabSimulation.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeature.h>
#include <Gui/Document.h>
#include <Gui/Application.h>
#include <App/Document.h>
#include "Control.h"
#include "ViewProviderSeismicLabFeatureSimulationMethod.h"

#include <Mod/SeismicLabAPI/App/SeismicLabFeatureLocationDistribution.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureMeanAcceleration.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureSpectrum.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeaturePSDDecompositionMethod.h> 
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureCoherence.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureSimulationMethod.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureFrequencyDistribution.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureRandomness.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureModulation.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureCorrelation.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureTableTool.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureMatrixTool.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureCumulativeProbabilityDistribution.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureKurtosis.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeaturePeakFactor.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureProbabilityDensityFunction.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureShearVelocityOfFlow.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureSkewness.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureStandardDeviation.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureVariance.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureWavePassageEffect.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureUserDefinedRPSObject.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureMatrixTool.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeatureTableTool.h>
#include <Gui/Command.h>
#include <App/AutoTransaction.h>
#include <Mod/SeismicLabAPI/App/IrpsSLSimulationMethod.h>

using namespace SeismicLabGui;
using namespace Gui;

// ----------------------------------------------------------------------------

/* TRANSLATOR SeismicLabGui::ViewProviderSeismicLabSimulation */

PROPERTY_SOURCE(SeismicLabGui::ViewProviderSeismicLabSimulation, Gui::ViewProviderDocumentObjectGroup)


ViewProviderSeismicLabSimulation::ViewProviderSeismicLabSimulation()
{
    sPixmap = "SeismicLab_NewSimulation";
}

ViewProviderSeismicLabSimulation::~ViewProviderSeismicLabSimulation()
{

}

void ViewProviderSeismicLabSimulation::attach(App::DocumentObject* obj)
{
    Gui::ViewProviderDocumentObjectGroup::attach(obj);
}

void ViewProviderSeismicLabSimulation::highlightView(Gui::ViewProviderDocumentObject* view)
{
}

bool ViewProviderSeismicLabSimulation::doubleClicked(void)
{
    Gui::Command::assureWorkbench("SeismicLabWorkbench");
    Gui::Command::addModule(Gui::Command::Gui, "SeismicLabGui");
    Gui::Command::doCommand(Gui::Command::Gui,
                            "SeismicLabGui.setActiveSimulation(App.activeDocument().%s)",
                            this->getObject()->getNameInDocument());
    Gui::Command::doCommand(Gui::Command::Gui, "Gui.Selection.clearSelection()");
    std::vector<App::DocumentObject*> selVector {};
    selVector.push_back(this->getObject());
    auto *docName = this->getObject()->getDocument()->getName();
    Gui::Selection().setSelection(docName, selVector);
    return true;
}

bool ViewProviderSeismicLabSimulation::run()
{
     SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    auto activeMethod = sim->getActiveSimulationMethod();

    //SeismicLabAPI::IrpsSLSimulationMethod* activeSimMethod = static_cast<SeismicLabAPI::IrpsSLSimulationMethod*>(sim->getActiveSimulationMethod());
    if (!activeMethod) {
        return false;
    }
    SeismicLabGui::ViewProviderSeismicLabFeatureSimulationMethod* vp = dynamic_cast<SeismicLabGui::ViewProviderSeismicLabFeatureSimulationMethod*>(Gui::Application::Instance->getViewProvider(activeMethod));

    if (!vp) {
        return false;
    }

    vp->simulate();

    return true;
}

bool ViewProviderSeismicLabSimulation::stop()
{
     SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->getSimulation(this->getObject()->getNameInDocument()));
    if (!sim) {
        return false;
    }
    //get the corresponding view provider
    SeismicLabGui::ViewProviderSeismicLabFeatureSimulationMethod* vp = dynamic_cast<SeismicLabGui::ViewProviderSeismicLabFeatureSimulationMethod*>(Gui::Application::Instance->getViewProvider(sim));

    vp->stop();

    return true;
}

bool ViewProviderSeismicLabSimulation::activateSimulation() { return doubleClicked(); }

std::vector<App::DocumentObject*> ViewProviderSeismicLabSimulation::claimChildren(void)const
{
    return Gui::ViewProviderDocumentObjectGroup::claimChildren();
}

std::vector<std::string> ViewProviderSeismicLabSimulation::getDisplayModes(void) const
{
    return { "SeismicLabSimulation" };
}

bool ViewProviderSeismicLabSimulation::refresh() {
    std::vector<App::Simulation*> sims = SeismicLabGui::SeismicLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<SeismicLab::SeismicLabSimulation*>(*it)->resetAllEnums();
    }

    Gui::Document* doc = Gui::Application::Instance->activeDocument();

	App::AutoTransaction trans("Recompute");
    Command::doCommand(Command::Doc, "App.getDocument(\"%s\").recompute()", doc->getDocument()->getName());

    return true;
}

void ViewProviderSeismicLabSimulation::hide(void)
{
    Gui::ViewProviderDocumentObjectGroup::hide();
}

void ViewProviderSeismicLabSimulation::show(void)
{
    Gui::ViewProviderDocumentObjectGroup::show();
}

void ViewProviderSeismicLabSimulation::setupContextMenu(QMenu* menu, QObject* , const char* )
{
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* act = menu->addAction(QString::fromLatin1("Activate Simulation"));
    func->trigger(act, boost::bind(&ViewProviderSeismicLabSimulation::doubleClicked, this));

    QAction* run = menu->addAction(QString::fromLatin1("Run"));
    func->trigger(run, boost::bind(&ViewProviderSeismicLabSimulation::run, this));

    QAction* stop = menu->addAction(QString::fromLatin1("Stop"));
    func->trigger(stop, boost::bind(&ViewProviderSeismicLabSimulation::stop, this));

     QAction* refresh = menu->addAction(QString::fromLatin1("Refresh"));
    func->trigger(refresh, boost::bind(&ViewProviderSeismicLabSimulation::refresh, this));
}


bool ViewProviderSeismicLabSimulation::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default ) {        
        return true;
    }
    else {
        return Gui::ViewProviderDocumentObjectGroup::setEdit(ModNum);
    }
}

void ViewProviderSeismicLabSimulation::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObjectGroup::unsetEdit(ModNum);
    }
}

bool ViewProviderSeismicLabSimulation::canDragObjects() const
{
    return true;
}

bool ViewProviderSeismicLabSimulation::canDragObject(App::DocumentObject* obj) const
{
     if (!obj)
        return false;

    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureLocationDistribution::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureMeanAcceleration ::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureSpectrum::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeaturePSDDecompositionMethod::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureCoherence::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureSimulationMethod::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureFrequencyDistribution::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureRandomness::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureModulation::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureCorrelation::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureTableTool::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureMatrixTool::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureCumulativeProbabilityDistribution::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureKurtosis::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeaturePeakFactor::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureProbabilityDensityFunction::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureShearVelocityOfFlow::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureSkewness::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureStandardDeviation::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureVariance::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureWavePassageEffect::getClassTypeId())) 
        return true;
    if (obj->getTypeId().isDerivedFrom( SeismicLabAPI::SeismicLabFeatureUserDefinedRPSObject::getClassTypeId())) 
        return true;
    else if (obj->getTypeId().isDerivedFrom(Base::Type::fromName("App::FeaturePython")))
        return true;
    else if (obj->getTypeId().isDerivedFrom(App::TextDocument::getClassTypeId()))
        return true;
    else
        return false;
}

void ViewProviderSeismicLabSimulation::dragObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dragObject(obj);
}

bool ViewProviderSeismicLabSimulation::canDropObjects() const
{
    return true;
}

bool ViewProviderSeismicLabSimulation::canDropObject(App::DocumentObject* obj) const
{
    return canDragObject(obj);
}

void ViewProviderSeismicLabSimulation::dropObject(App::DocumentObject* obj)
{
    ViewProviderDocumentObjectGroup::dropObject(obj);
   
    std::vector<App::Simulation*> sims = SeismicLabGui::SeismicLabSimulationObserver::instance()->getAllSimulations();
    
    std::vector<App::Simulation*>::const_iterator it;

    for (it = sims.begin(); it < sims.end(); ++it) {
        static_cast<SeismicLab::SeismicLabSimulation*>(*it)->resetAllEnums();
    }
}

bool ViewProviderSeismicLabSimulation::onDelete(const std::vector<std::string>&)
{
    // warn the user if the object has unselected children
    auto objs = claimChildren();
    return checkSelectedChildren(objs, this->getDocument(), "SeismicLab simulation");
}

bool ViewProviderSeismicLabSimulation::canDelete(App::DocumentObject* obj) const
{
    // deletions of objects from a SeismicLabSimulation don't necessarily destroy anything
    // thus we can pass this action
    // we can warn the user if necessary in the object's ViewProvider in the onDelete() function
    Q_UNUSED(obj)
    return true;
}

bool ViewProviderSeismicLabSimulation::checkSelectedChildren(const std::vector<App::DocumentObject*> objs,
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
