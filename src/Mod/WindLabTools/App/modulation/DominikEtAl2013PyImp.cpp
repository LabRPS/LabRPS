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

#include <CXX/Objects.hxx>
#include "DominikEtAl2013.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of DominikEtAl2013Py.xml)
#include "Mod/WindLabTools/App/modulation/DominikEtAl2013Py.h"
#include "Mod/WindLabTools/App/modulation/DominikEtAl2013Py.cpp"

//#include <API/WindLabAPI/RPSWindLabsimuDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string DominikEtAl2013Py::representation(void) const
{
    return std::string("<DominikEtAl2013 object>");
}

PyObject* DominikEtAl2013Py::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new DominikEtAl2013Py(new DominikEtAl2013());
}

// constructor method
int DominikEtAl2013Py::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* DominikEtAl2013Py::computeModulationA(PyObject *args)
{
    double time;
    double nonZeroUpperBound = 200;

    if (!PyArg_ParseTuple(args, "d|d", &time, &nonZeroUpperBound))
    return nullptr;
    return Py::new_reference_to(Py::Float(getDominikEtAl2013Ptr()->computeModulationA(time, nonZeroUpperBound)));
}

PyObject* DominikEtAl2013Py::computeModulationB(PyObject *args)
{
    double time;
    double nonZeroUpperBound = 200;

    if (!PyArg_ParseTuple(args, "d|d", &time, &nonZeroUpperBound))
    return nullptr;
    return Py::new_reference_to(Py::Float(getDominikEtAl2013Ptr()->computeModulationB(time, nonZeroUpperBound)));
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *DominikEtAl2013Py::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int DominikEtAl2013Py::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
