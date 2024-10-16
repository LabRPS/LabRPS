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

#include "ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod.h"
#include "ViewProviderUserDefinedPhenomenonLabSimulation.h"
#include "ViewProviderUserDefinedPhenomenonLabSimulationComparison.h"


#include "Workbench.h"
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Language/Translator.h>
#include <Gui/WidgetFactory.h>
#include "RPSUserDefinedPhenomenonLabPyTool.h"
#include <Mod/UserDefinedPhenomenonLab/App/UserDefinedPhenomenonLabSimulation.h>
#include <Mod/UserDefinedPhenomenonLab/Gui/UserDefinedPhenomenonLabSimulationObserver.h>
#include <App/DocumentObjectPy.h>
#include "DlgSettingsUserDefinedPhenomenonLabGeneralImp.h"
#include "DlgSettingsUserDefinedPhenomenonLabLimitImp.h"

// create the commands
void CreateUserDefinedPhenomenonLabCommands(void);

void loadUserDefinedPhenomenonLabResource()
{
    // add resources and reloads the translators
    Q_INIT_RESOURCE(UserDefinedPhenomenonLab);
    Gui::Translator::instance()->refresh();
}


namespace UserDefinedPhenomenonLabGui
{
class Module: public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("UserDefinedPhenomenonLabGui")
    {
         add_varargs_method("setActiveSimulation", &Module::setActiveSimulation,
            "setActiveSimulation(SimulationObject) -- Set the Simulation object in work."
        );
        add_varargs_method("getActiveSimulation", &Module::getActiveSimulation,
            "getActiveSimulation() -- Returns the Simulation object in work."
        );
        initialize("This module is the UserDefinedPhenomenonLabGui module.");// register with Python
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
        if (UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->hasActiveObject()) {
            UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue ,false);
            UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->setActiveSimulation(nullptr);
        }

        PyObject* object = nullptr;
        if (PyArg_ParseTuple(args.ptr(), "|O!", &(App::DocumentObjectPy::Type), &object)
            && object) {
            App::DocumentObject* obj =
                static_cast<App::DocumentObjectPy*>(object)->getDocumentObjectPtr();
            if (!obj
                || !obj->getTypeId().isDerivedFrom(UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation::getClassTypeId())) {
                throw Py::Exception(
                    Base::PyExc_RPS_GeneralError,
                    "Active Simulation object have to be of type UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation!");
            }

            UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*  sim = static_cast<UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation*>(obj);
            UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->setActiveSimulation(sim);
            UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue, true);
        }

        return Py::None();
    }
    Py::Object getActiveSimulation(const Py::Tuple& args)
    {
        if (!PyArg_ParseTuple(args.ptr(), ""))
            throw Py::Exception();
        if (UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->hasActiveObject()) {
            return Py::asObject(static_cast<App::Simulation*>(UserDefinedPhenomenonLabGui::UserDefinedPhenomenonLabSimulationObserver::instance()->active())->getPyObject());
        }
        return Py::None();
    }
};

PyObject* initModule() { return Base::Interpreter().addModule(new Module); }

}// namespace UserDefinedPhenomenonLabGui

/* Python entry */
PyMOD_INIT_FUNC(UserDefinedPhenomenonLabGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(nullptr);
    }
    try {
        Base::Interpreter().runString("import UserDefinedPhenomenonLab");
        Base::Interpreter().runString("import UserDefinedPhenomenonLabAPIScripts");

    }
    catch (const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(nullptr);
    }

    PyObject* mod = UserDefinedPhenomenonLabGui::initModule();
    Base::Console().Log("Loading GUI of UserDefinedPhenomenonLab module... done\n");

    CreateUserDefinedPhenomenonLabCommands();

    UserDefinedPhenomenonLabGui::Workbench::init();

    // init objects
    UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabSimulation ::init();
    UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabSimulationComparison ::init();
    UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod::init();

    new Gui::PrefPageProducer<UserDefinedPhenomenonLabGui::DlgSettingsUserDefinedPhenomenonLabGeneralImp>(QT_TRANSLATE_NOOP("QObject", "UserDefinedPhenomenonLab"));
    new Gui::PrefPageProducer<UserDefinedPhenomenonLabGui::DlgSettingsUserDefinedPhenomenonLabLimitImp>(QT_TRANSLATE_NOOP("QObject", "UserDefinedPhenomenonLab"));

    loadUserDefinedPhenomenonLabResource();

    static struct PyModuleDef pUserDefinedPhenomenonLabPyToolPyModuleDef = {
        PyModuleDef_HEAD_INIT,
        "UserDefinedPhenomenonLabPyTool",
        "UserDefinedPhenomenonLabPyTool", -1,
        UserDefinedPhenomenonLabGui::RPSUserDefinedPhenomenonLabPyTool::Methods,
        nullptr, nullptr, nullptr, nullptr};

    PyObject* pUserDefinedPhenomenonLabPyToolPyModule = PyModule_Create(&pUserDefinedPhenomenonLabPyToolPyModuleDef);

    Py_INCREF(pUserDefinedPhenomenonLabPyToolPyModule);
    PyModule_AddObject(mod, "UserDefinedPhenomenonLabPyTool", pUserDefinedPhenomenonLabPyToolPyModule);


    PyMOD_Return(mod);
}
