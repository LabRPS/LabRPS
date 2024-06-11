/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <werner.wm.mayer@gmx.de>              *
 *                                                                         *
 *   This file is part of the LabRPS CAx development system.              *
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
# include <QFileInfo>
#endif

#include <App/DocumentObjectPy.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Document.h>
#include <Gui/EditorView.h>
#include <Gui/MainWindow.h>
#include <Gui/TextEdit.h>
#include <Mod/WindLab/App/WindLabSimulation.h>
#include <Mod/WindLab/Gui/WindLabSimulationObserver.h>


namespace WindLabGui {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("WindLabGui")
    {
        add_varargs_method("setActiveSimulation", &Module::setActiveSimulation,
            "setActiveSimulation(SimulationObject) -- Set the Simulation object in work."
        );
        add_varargs_method("getActiveSimulation", &Module::getActiveSimulation,
            "getActiveSimulation() -- Returns the Simulation object in work."
        );
        initialize("This module is the WindLabGui module."); // register with Python
    }

    ~Module() override {}

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
            WindLabGui::WindLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue, false);
            WindLabGui::WindLabSimulationObserver::instance()->setActiveSimulation(nullptr);
        }

        PyObject* object = nullptr;
        if (PyArg_ParseTuple(args.ptr(), "|O!", &(App::DocumentObjectPy::Type), &object) && object) {
            App::DocumentObject* obj = static_cast<App::DocumentObjectPy*>(object)->getDocumentObjectPtr();
            if (!obj || !obj->getTypeId().isDerivedFrom(WindLab::WindLabSimulation::getClassTypeId())) {
                throw Py::Exception(Base::PyExc_FC_GeneralError, "Active Simulation object have to be of type WindLab::WindLabSimulation!");
            }

            // get the gui document of the Simulation Item
            WindLabGui::WindLabSimulationObserver::instance()->setActiveSimulation(static_cast<WindLab::WindLabSimulation*>(obj));
            WindLabGui::WindLabSimulationObserver::instance()->highlightActiveObject(Gui::HighlightMode::Blue, true);
        }

        return Py::None();
    }
    Py::Object getActiveSimulation(const Py::Tuple& args)
    {
        if (!PyArg_ParseTuple(args.ptr(), ""))
            throw Py::Exception();
        if (WindLabGui::WindLabSimulationObserver::instance()->hasActiveObject()) {
            return Py::asObject(WindLabGui::WindLabSimulationObserver::instance()->active()->getPyObject());
        }
        return Py::None();
    }

};

PyObject* initModule()
{
    return Base::Interpreter().addModule(new Module);
}

} // namespace WindLabGui
