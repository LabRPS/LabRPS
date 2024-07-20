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

#include "ViewProviderSeismicLabFeatureCoherence.h"
#include "ViewProviderSeismicLabFeatureCorrelation.h"
#include "ViewProviderSeismicLabFeatureCumulativeProbabilityDistribution.h"
#include "ViewProviderSeismicLabFeatureFrequencyDistribution.h"
#include "ViewProviderSeismicLabFeatureKurtosis.h"
#include "ViewProviderSeismicLabFeatureLocationDistribution.h"
#include "ViewProviderSeismicLabFeatureMatrixTool.h"
#include "ViewProviderSeismicLabFeatureMeanAcceleration.h"
#include "ViewProviderSeismicLabFeatureModulation.h"
#include "ViewProviderSeismicLabFeaturePSDDecompositionMethod.h"
#include "ViewProviderSeismicLabFeaturePeakFactor.h"
#include "ViewProviderSeismicLabFeatureProbabilityDensityFunction.h"
#include "ViewProviderSeismicLabFeatureRandomness.h"
#include "ViewProviderSeismicLabFeatureShearVelocityOfFlow.h"
#include "ViewProviderSeismicLabFeatureSimulationMethod.h"
#include "ViewProviderSeismicLabFeatureSkewness.h"
#include "ViewProviderSeismicLabFeatureStandardDeviation.h"
#include "ViewProviderSeismicLabFeatureTableTool.h"
#include "ViewProviderSeismicLabFeatureUserDefinedRPSObject.h"
#include "ViewProviderSeismicLabFeatureVariance.h"
#include "ViewProviderSeismicLabFeatureWavePassageEffect.h"
#include "ViewProviderSeismicLabFeatureSpectrum.h"
#include "ViewProviderSeismicLabSimulation.h"
#include "ViewProviderSeismicLabSimulationComparison.h"


#include "Workbench.h"
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Language/Translator.h>
#include <Gui/WidgetFactory.h>
#include "RPSSeismicLabPyTool.h"
#include <Mod/SeismicLab/App/SeismicLabSimulation.h>
#include <Mod/SeismicLab/Gui/SeismicLabSimulationObserver.h>
#include <App/DocumentObjectPy.h>
#include "DlgSettingsSeismicLabGeneralImp.h"
#include "DlgSettingsSeismicLabLimitImp.h"

// create the commands
void CreateSeismicLabCommands(void);

void loadSeismicLabResource()
{
    // add resources and reloads the translators
    Q_INIT_RESOURCE(SeismicLab);
    Gui::Translator::instance()->refresh();
}


namespace SeismicLabGui
{
class Module: public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("SeismicLabGui")
    {
         add_varargs_method("setActiveSimulation", &Module::setActiveSimulation,
            "setActiveSimulation(SimulationObject) -- Set the Simulation object in work."
        );
        add_varargs_method("getActiveSimulation", &Module::getActiveSimulation,
            "getActiveSimulation() -- Returns the Simulation object in work."
        );
        initialize("This module is the SeismicLabGui module.");// register with Python
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
        if (SeismicLabGui::SeismicLabSimulationObserver::instance()->hasActiveObject()) {
            SeismicLabGui::SeismicLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue ,false);
            SeismicLabGui::SeismicLabSimulationObserver::instance()->setActiveSimulation(nullptr);
        }

        PyObject* object = nullptr;
        if (PyArg_ParseTuple(args.ptr(), "|O!", &(App::DocumentObjectPy::Type), &object)
            && object) {
            App::DocumentObject* obj =
                static_cast<App::DocumentObjectPy*>(object)->getDocumentObjectPtr();
            if (!obj
                || !obj->getTypeId().isDerivedFrom(SeismicLab::SeismicLabSimulation::getClassTypeId())) {
                throw Py::Exception(
                    Base::PyExc_RPS_GeneralError,
                    "Active Simulation object have to be of type SeismicLab::SeismicLabSimulation!");
            }

            SeismicLab::SeismicLabSimulation*  sim = static_cast<SeismicLab::SeismicLabSimulation*>(obj);
            SeismicLabGui::SeismicLabSimulationObserver::instance()->setActiveSimulation(sim);
            SeismicLabGui::SeismicLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue, true);
        }

        return Py::None();
    }
    Py::Object getActiveSimulation(const Py::Tuple& args)
    {
        if (!PyArg_ParseTuple(args.ptr(), ""))
            throw Py::Exception();
        if (SeismicLabGui::SeismicLabSimulationObserver::instance()->hasActiveObject()) {
            return Py::asObject(static_cast<App::Simulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active())->getPyObject());
        }
        return Py::None();
    }
};

PyObject* initModule() { return Base::Interpreter().addModule(new Module); }

}// namespace SeismicLabGui

/* Python entry */
PyMOD_INIT_FUNC(SeismicLabGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(nullptr);
    }
    try {
        Base::Interpreter().runString("import SeismicLab");
        Base::Interpreter().runString("import SeismicLabAPIScripts");

    }
    catch (const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(nullptr);
    }

    PyObject* mod = SeismicLabGui::initModule();
    Base::Console().Log("Loading GUI of SeismicLab module... done\n");

    CreateSeismicLabCommands();

    SeismicLabGui::Workbench::init();

    // init objects
    SeismicLabGui::ViewProviderSeismicLabSimulation ::init();
    SeismicLabGui::ViewProviderSeismicLabSimulationComparison ::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureLocationDistribution::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureMeanAcceleration::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureSpectrum::init();
    SeismicLabGui::ViewProviderSeismicLabFeaturePSDDecompositionMethod::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureCoherence::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureSimulationMethod::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureFrequencyDistribution::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureRandomness::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureModulation::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureCorrelation::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureCumulativeProbabilityDistribution::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureKurtosis::init();
    SeismicLabGui::ViewProviderSeismicLabFeaturePeakFactor::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureProbabilityDensityFunction::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureShearVelocityOfFlow::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureSkewness::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureStandardDeviation::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureVariance::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureWavePassageEffect::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureUserDefinedRPSObject::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureTableTool::init();
    SeismicLabGui::ViewProviderSeismicLabFeatureMatrixTool::init();

    new Gui::PrefPageProducer<SeismicLabGui::DlgSettingsSeismicLabGeneralImp>(QT_TRANSLATE_NOOP("QObject", "SeismicLab"));
    new Gui::PrefPageProducer<SeismicLabGui::DlgSettingsSeismicLabLimitImp>(QT_TRANSLATE_NOOP("QObject", "SeismicLab"));

    loadSeismicLabResource();

    static struct PyModuleDef pSeismicLabPyToolPyModuleDef = {
        PyModuleDef_HEAD_INIT,
        "SeismicLabPyTool",
        "SeismicLabPyTool", -1,
        SeismicLabGui::RPSSeismicLabPyTool::Methods,
        nullptr, nullptr, nullptr, nullptr};

    PyObject* pSeismicLabPyToolPyModule = PyModule_Create(&pSeismicLabPyToolPyModuleDef);

    Py_INCREF(pSeismicLabPyToolPyModule);
    PyModule_AddObject(mod, "SeismicLabPyTool", pSeismicLabPyToolPyModule);


    PyMOD_Return(mod);
}
