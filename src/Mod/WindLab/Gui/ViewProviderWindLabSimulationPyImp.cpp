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

#include "ViewProviderWindLabSimulationPy.h"
#include "ViewProviderWindLabSimulationPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabSimulation.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabSimulationPy::representation(void) const
{
    return std::string("<ViewProviderWindLabSimulation object>");
}


PyObject* ViewProviderWindLabSimulationPy::run(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    this->getViewProviderWindLabSimulationPtr()->run();

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabSimulationPy::stop(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    this->getViewProviderWindLabSimulationPtr()->stop();

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabSimulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabSimulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
