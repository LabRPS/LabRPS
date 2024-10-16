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

#include <Base/VectorPy.h>
#include <CXX/Objects.hxx>
#include "SeaLabSimulationComparison.h"
#include <Base/TypePy.h>

// inclusion of the generated files (generated out of SeaLabSimulationComparisonPy.xml)
#include "SeaLabSimulationComparisonPy.h"
#include "SeaLabSimulationComparisonPy.cpp"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/python/copy_const_reference.hpp>


using namespace SeaLab;
using namespace SeaLabAPI;

// returns a string which represents the object e.g. when printed in python
std::string SeaLabSimulationComparisonPy::representation(void) const
{
    std::stringstream str;
    str << "<SeaLab Simulation Comparison: " << getSeaLabSimulationComparisonPtr()->Label.getValue() << ">";
    return str.str();
}

PyObject* SeaLabSimulationComparisonPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new SeaLabSimulationComparisonPy(new SeaLabSimulationComparison());
}

// constructor method
int SeaLabSimulationComparisonPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *SeaLabSimulationComparisonPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int SeaLabSimulationComparisonPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* SeaLabSimulationComparisonPy::start(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    getSeaLabSimulationComparisonPtr()->start();
    Py_Return;
}

PyObject* SeaLabSimulationComparisonPy::stop(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    getSeaLabSimulationComparisonPtr()->stop();
    Py_Return;

}