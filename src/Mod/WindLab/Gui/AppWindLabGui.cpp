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

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureCoherence.h"
#include "ViewProviderWindLabFeatureCorrelation.h"
#include "ViewProviderWindLabFeatureCumulativeProbabilityDistribution.h"
#include "ViewProviderWindLabFeatureFrequencyDistribution.h"
#include "ViewProviderWindLabFeatureGustFactor.h"
#include "ViewProviderWindLabFeatureKurtosis.h"
#include "ViewProviderWindLabFeatureLocationDistribution.h"
#include "ViewProviderWindLabFeatureMatrixTool.h"
#include "ViewProviderWindLabFeatureMeanWind.h"
#include "ViewProviderWindLabFeatureModulation.h"
#include "ViewProviderWindLabFeaturePSDDecompositionMethod.h"
#include "ViewProviderWindLabFeaturePeakFactor.h"
#include "ViewProviderWindLabFeatureProbabilityDensityFunction.h"
#include "ViewProviderWindLabFeatureRandomness.h"
#include "ViewProviderWindLabFeatureRoughness.h"
#include "ViewProviderWindLabFeatureShearVelocityOfFlow.h"
#include "ViewProviderWindLabFeatureSimulationMethod.h"
#include "ViewProviderWindLabFeatureSkewness.h"
#include "ViewProviderWindLabFeatureStandardDeviation.h"
#include "ViewProviderWindLabFeatureTableTool.h"
#include "ViewProviderWindLabFeatureTurbulenceIntensity.h"
#include "ViewProviderWindLabFeatureTurbulenceScale.h"
#include "ViewProviderWindLabFeatureUserDefinedRPSObject.h"
#include "ViewProviderWindLabFeatureVariance.h"
#include "ViewProviderWindLabFeatureWavePassageEffect.h"
#include "ViewProviderWindLabFeatureXSpectrum.h"
#include "ViewProviderWindLabFeatureYSpectrum.h"
#include "ViewProviderWindLabFeatureZSpectrum.h"
#include "ViewProviderWindLabSimulation.h"


#include "Workbench.h"
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Language/Translator.h>
#include <Gui/WidgetFactory.h>
#include <Mod/WindLab/App/WindLabSimulation.h>
#include <Mod/WindLab/Gui/WindLabSimulationObserver.h>
#include <App/DocumentObjectPy.h>
#include "DlgSettingsWindLabGeneralImp.h"
#include "DlgSettingsWindLabLimitImp.h"

// create the commands
void CreateWindLabCommands(void);

void loadWindLabResource()
{
    // add resources and reloads the translators
    Q_INIT_RESOURCE(WindLab);
    Gui::Translator::instance()->refresh();
}


namespace WindLabGui
{
class Module: public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("WindLabGui")
    {
         add_varargs_method("setActiveSimulation", &Module::setActiveSimulation,
            "setActiveSimulation(SimulationObject) -- Set the simulation as active."
        );
        add_varargs_method("getActiveSimulation", &Module::getActiveSimulation,
            "getActiveSimulation() -- Returns the active simulation."
        );
        initialize("This module is the WindLabGui module.");// register with Python
    }

    virtual ~Module() {}

private:
    Py::Object invoke_method_varargs(void* method_def, const Py::Tuple& args) override
    {
        try {
            return Py::ExtensionModule<Module>::invoke_method_varargs(method_def, args);
        }
        catch (const Base::Exception& e) {
            throw Py::RuntimeError(e.what());
        }
        catch (const std::exception& e) {
            throw Py::RuntimeError(e.what());
        }
    }
    Py::Object setActiveSimulation(const Py::Tuple& args)
    {
        if (WindLabGui::WindLabSimulationObserver::instance()->hasActiveObject()) {
            WindLabGui::WindLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue ,false);
            WindLabGui::WindLabSimulationObserver::instance()->setActiveSimulation(nullptr);
        }

        PyObject* object = nullptr;
        if (PyArg_ParseTuple(args.ptr(), "|O!", &(App::DocumentObjectPy::Type), &object)
            && object) {
            App::DocumentObject* obj =
                static_cast<App::DocumentObjectPy*>(object)->getDocumentObjectPtr();
            if (!obj
                || !obj->getTypeId().isDerivedFrom(WindLab::WindLabSimulation::getClassTypeId())) {
                throw Py::Exception(
                    Base::PyExc_RPS_GeneralError,
                    "Active Simulation object have to be of type WindLab::WindLabSimulation!");
            }

            WindLab::WindLabSimulation*  sim = static_cast<WindLab::WindLabSimulation*>(obj);
            WindLabGui::WindLabSimulationObserver::instance()->setActiveSimulation(sim);
            WindLabGui::WindLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue, true);
        }

        return Py::None();
    }
    Py::Object getActiveSimulation(const Py::Tuple& args)
    {
        if (!PyArg_ParseTuple(args.ptr(), ""))
            throw Py::Exception();
        if (WindLabGui::WindLabSimulationObserver::instance()->hasActiveObject()) {
            return Py::asObject(static_cast<App::Simulation*>(WindLabGui::WindLabSimulationObserver::instance()->active())->getPyObject());
        }
        return Py::None();
    }
};

PyObject* initModule() { return Base::Interpreter().addModule(new Module); }

}// namespace WindLabGui

/* Python entry */
PyMOD_INIT_FUNC(WindLabGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(nullptr);
    }
    try {
        Base::Interpreter().runString("import WindLab");
        Base::Interpreter().runString("import WindLabAPIScripts");

    }
    catch (const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(nullptr);
    }

    PyObject* mod = WindLabGui::initModule();
    Base::Console().Log("Loading GUI of WindLab module... done\n");

    CreateWindLabCommands();

    WindLabGui::Workbench::init();

    // init objects
    WindLabGui::ViewProviderWindLabSimulation ::init();
    WindLabGui::ViewProviderWindLabFeatureLocationDistribution::init();
    WindLabGui::ViewProviderWindLabFeatureMeanWind::init();
    WindLabGui::ViewProviderWindLabFeatureXSpectrum::init();
    WindLabGui::ViewProviderWindLabFeatureZSpectrum::init();
    WindLabGui::ViewProviderWindLabFeatureYSpectrum::init();
    WindLabGui::ViewProviderWindLabFeaturePSDDecompositionMethod::init();
    WindLabGui::ViewProviderWindLabFeatureCoherence::init();
    WindLabGui::ViewProviderWindLabFeatureSimulationMethod::init();
    WindLabGui::ViewProviderWindLabFeatureFrequencyDistribution::init();
    WindLabGui::ViewProviderWindLabFeatureRandomness::init();
    WindLabGui::ViewProviderWindLabFeatureModulation::init();
    WindLabGui::ViewProviderWindLabFeatureCorrelation::init();
    WindLabGui::ViewProviderWindLabFeatureCumulativeProbabilityDistribution::init();
    WindLabGui::ViewProviderWindLabFeatureGustFactor::init();
    WindLabGui::ViewProviderWindLabFeatureKurtosis::init();
    WindLabGui::ViewProviderWindLabFeaturePeakFactor::init();
    WindLabGui::ViewProviderWindLabFeatureProbabilityDensityFunction::init();
    WindLabGui::ViewProviderWindLabFeatureRoughness::init();
    WindLabGui::ViewProviderWindLabFeatureShearVelocityOfFlow::init();
    WindLabGui::ViewProviderWindLabFeatureSkewness::init();
    WindLabGui::ViewProviderWindLabFeatureStandardDeviation::init();
    WindLabGui::ViewProviderWindLabFeatureTurbulenceIntensity::init();
    WindLabGui::ViewProviderWindLabFeatureTurbulenceScale::init();
    WindLabGui::ViewProviderWindLabFeatureVariance::init();
    WindLabGui::ViewProviderWindLabFeatureWavePassageEffect::init();
    WindLabGui::ViewProviderWindLabFeatureUserDefinedRPSObject::init();
    WindLabGui::ViewProviderWindLabFeatureTableTool::init();
    WindLabGui::ViewProviderWindLabFeatureMatrixTool::init();

    new Gui::PrefPageProducer<WindLabGui::DlgSettingsWindLabGeneralImp>(QT_TRANSLATE_NOOP("QObject", "WindLab"));
    new Gui::PrefPageProducer<WindLabGui::DlgSettingsWindLabLimitImp>(QT_TRANSLATE_NOOP("QObject", "WindLab"));

    loadWindLabResource();

    PyMOD_Return(mod);
}
