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

#include "ViewProviderSeaLabFeatureCoherence.h"
#include "ViewProviderSeaLabFeatureCorrelation.h"
#include "ViewProviderSeaLabFeatureCumulativeProbabilityDistribution.h"
#include "ViewProviderSeaLabFeatureFrequencyDistribution.h"
#include "ViewProviderSeaLabFeatureKurtosis.h"
#include "ViewProviderSeaLabFeatureLocationDistribution.h"
#include "ViewProviderSeaLabFeatureMatrixTool.h"
#include "ViewProviderSeaLabFeatureMeanAcceleration.h"
#include "ViewProviderSeaLabFeatureModulation.h"
#include "ViewProviderSeaLabFeaturePSDDecompositionMethod.h"
#include "ViewProviderSeaLabFeaturePeakFactor.h"
#include "ViewProviderSeaLabFeatureProbabilityDensityFunction.h"
#include "ViewProviderSeaLabFeatureRandomness.h"
#include "ViewProviderSeaLabFeatureShearVelocityOfFlow.h"
#include "ViewProviderSeaLabFeatureSimulationMethod.h"
#include "ViewProviderSeaLabFeatureSkewness.h"
#include "ViewProviderSeaLabFeatureStandardDeviation.h"
#include "ViewProviderSeaLabFeatureTableTool.h"
#include "ViewProviderSeaLabFeatureUserDefinedRPSObject.h"
#include "ViewProviderSeaLabFeatureVariance.h"
#include "ViewProviderSeaLabFeatureWavePassageEffect.h"
#include "ViewProviderSeaLabFeatureSpectrum.h"
#include "ViewProviderSeaLabSimulation.h"
#include "ViewProviderSeaLabSimulationComparison.h"


#include "Workbench.h"
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Language/Translator.h>
#include <Gui/WidgetFactory.h>
#include "RPSSeaLabPyTool.h"
#include <Mod/SeaLab/App/SeaLabSimulation.h>
#include <Mod/SeaLab/Gui/SeaLabSimulationObserver.h>
#include <App/DocumentObjectPy.h>
#include "DlgSettingsSeaLabGeneralImp.h"
#include "DlgSettingsSeaLabLimitImp.h"

// create the commands
void CreateSeaLabCommands(void);

void loadSeaLabResource()
{
    // add resources and reloads the translators
    Q_INIT_RESOURCE(SeaLab);
    Gui::Translator::instance()->refresh();
}


namespace SeaLabGui
{
class Module: public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("SeaLabGui")
    {
         add_varargs_method("setActiveSimulation", &Module::setActiveSimulation,
            "setActiveSimulation(SimulationObject) -- Set the Simulation object in work."
        );
        add_varargs_method("getActiveSimulation", &Module::getActiveSimulation,
            "getActiveSimulation() -- Returns the Simulation object in work."
        );
        initialize("This module is the SeaLabGui module.");// register with Python
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
        if (SeaLabGui::SeaLabSimulationObserver::instance()->hasActiveObject()) {
            SeaLabGui::SeaLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue ,false);
            SeaLabGui::SeaLabSimulationObserver::instance()->setActiveSimulation(nullptr);
        }

        PyObject* object = nullptr;
        if (PyArg_ParseTuple(args.ptr(), "|O!", &(App::DocumentObjectPy::Type), &object)
            && object) {
            App::DocumentObject* obj =
                static_cast<App::DocumentObjectPy*>(object)->getDocumentObjectPtr();
            if (!obj
                || !obj->getTypeId().isDerivedFrom(SeaLab::SeaLabSimulation::getClassTypeId())) {
                throw Py::Exception(
                    Base::PyExc_RPS_GeneralError,
                    "Active Simulation object have to be of type SeaLab::SeaLabSimulation!");
            }

            SeaLab::SeaLabSimulation*  sim = static_cast<SeaLab::SeaLabSimulation*>(obj);
            SeaLabGui::SeaLabSimulationObserver::instance()->setActiveSimulation(sim);
            SeaLabGui::SeaLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue, true);
        }

        return Py::None();
    }
    Py::Object getActiveSimulation(const Py::Tuple& args)
    {
        if (!PyArg_ParseTuple(args.ptr(), ""))
            throw Py::Exception();
        if (SeaLabGui::SeaLabSimulationObserver::instance()->hasActiveObject()) {
            return Py::asObject(static_cast<App::Simulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active())->getPyObject());
        }
        return Py::None();
    }
};

PyObject* initModule() { return Base::Interpreter().addModule(new Module); }

}// namespace SeaLabGui

/* Python entry */
PyMOD_INIT_FUNC(SeaLabGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(nullptr);
    }
    try {
        Base::Interpreter().runString("import SeaLab");
        Base::Interpreter().runString("import SeaLabAPIScripts");

    }
    catch (const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(nullptr);
    }

    PyObject* mod = SeaLabGui::initModule();
    Base::Console().Log("Loading GUI of SeaLab module... done\n");

    CreateSeaLabCommands();

    SeaLabGui::Workbench::init();

    // init objects
    SeaLabGui::ViewProviderSeaLabSimulation ::init();
    SeaLabGui::ViewProviderSeaLabSimulationComparison ::init();
    SeaLabGui::ViewProviderSeaLabFeatureLocationDistribution::init();
    SeaLabGui::ViewProviderSeaLabFeatureMeanAcceleration::init();
    SeaLabGui::ViewProviderSeaLabFeatureSpectrum::init();
    SeaLabGui::ViewProviderSeaLabFeaturePSDDecompositionMethod::init();
    SeaLabGui::ViewProviderSeaLabFeatureCoherence::init();
    SeaLabGui::ViewProviderSeaLabFeatureSimulationMethod::init();
    SeaLabGui::ViewProviderSeaLabFeatureFrequencyDistribution::init();
    SeaLabGui::ViewProviderSeaLabFeatureRandomness::init();
    SeaLabGui::ViewProviderSeaLabFeatureModulation::init();
    SeaLabGui::ViewProviderSeaLabFeatureCorrelation::init();
    SeaLabGui::ViewProviderSeaLabFeatureCumulativeProbabilityDistribution::init();
    SeaLabGui::ViewProviderSeaLabFeatureKurtosis::init();
    SeaLabGui::ViewProviderSeaLabFeaturePeakFactor::init();
    SeaLabGui::ViewProviderSeaLabFeatureProbabilityDensityFunction::init();
    SeaLabGui::ViewProviderSeaLabFeatureShearVelocityOfFlow::init();
    SeaLabGui::ViewProviderSeaLabFeatureSkewness::init();
    SeaLabGui::ViewProviderSeaLabFeatureStandardDeviation::init();
    SeaLabGui::ViewProviderSeaLabFeatureVariance::init();
    SeaLabGui::ViewProviderSeaLabFeatureWavePassageEffect::init();
    SeaLabGui::ViewProviderSeaLabFeatureUserDefinedRPSObject::init();
    SeaLabGui::ViewProviderSeaLabFeatureTableTool::init();
    SeaLabGui::ViewProviderSeaLabFeatureMatrixTool::init();

    new Gui::PrefPageProducer<SeaLabGui::DlgSettingsSeaLabGeneralImp>(QT_TRANSLATE_NOOP("QObject", "SeaLab"));
    new Gui::PrefPageProducer<SeaLabGui::DlgSettingsSeaLabLimitImp>(QT_TRANSLATE_NOOP("QObject", "SeaLab"));

    loadSeaLabResource();

    static struct PyModuleDef pSeaLabPyToolPyModuleDef = {
        PyModuleDef_HEAD_INIT,
        "SeaLabPyTool",
        "SeaLabPyTool", -1,
        SeaLabGui::RPSSeaLabPyTool::Methods,
        nullptr, nullptr, nullptr, nullptr};

    PyObject* pSeaLabPyToolPyModule = PyModule_Create(&pSeaLabPyToolPyModuleDef);

    Py_INCREF(pSeaLabPyToolPyModule);
    PyModule_AddObject(mod, "SeaLabPyTool", pSeaLabPyToolPyModule);


    PyMOD_Return(mod);
}
