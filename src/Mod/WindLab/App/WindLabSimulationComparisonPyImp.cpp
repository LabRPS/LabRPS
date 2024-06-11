/***************************************************************************
 *   Copyright (c) 2010 Jürgen Riegel <juergen.riegel@web.de>              *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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
#include "WindLabSimulationComparison.h"
#include <Base/TypePy.h>

// inclusion of the generated files (generated out of WindLabSimulationComparisonPy.xml)
#include "WindLabSimulationComparisonPy.h"
#include "WindLabSimulationComparisonPy.cpp"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/python/copy_const_reference.hpp>


using namespace WindLab;
using namespace WindLabAPI;

// returns a string which represents the object e.g. when printed in python
std::string WindLabSimulationComparisonPy::representation(void) const
{
    std::stringstream str;
    str << "<WindLab Simulation Comparison: " << getWindLabSimulationComparisonPtr()->Label.getValue() << ">";
    return str.str();
}

PyObject* WindLabSimulationComparisonPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new WindLabSimulationComparisonPy(new WindLabSimulationComparison());
}

// constructor method
int WindLabSimulationComparisonPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *WindLabSimulationComparisonPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int WindLabSimulationComparisonPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* WindLabSimulationComparisonPy::start(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    getWindLabSimulationComparisonPtr()->start();
    Py_Return;
}

PyObject* WindLabSimulationComparisonPy::stop(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    getWindLabSimulationComparisonPtr()->stop();
    Py_Return;

}