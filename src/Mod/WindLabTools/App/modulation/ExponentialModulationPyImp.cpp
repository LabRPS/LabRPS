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
#include "ExponentialModulation.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of ExponentialModulationPy.xml)
#include "Mod/WindLabTools/App/modulation/ExponentialModulationPy.h"
#include "Mod/WindLabTools/App/modulation/ExponentialModulationPy.cpp"

//#include <API/WindLabAPI/RPSWindLabsimuDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string ExponentialModulationPy::representation(void) const
{
    return std::string("<ExponentialModulation object>");
}

PyObject* ExponentialModulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new ExponentialModulationPy(new ExponentialModulation());
}

// constructor method
int ExponentialModulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* ExponentialModulationPy::computeModulation(PyObject *args)
{
    double time;
    double timeOfMax;
    double stormLength;

    if (!PyArg_ParseTuple(args, "ddd", &time, &timeOfMax, &stormLength))
    return nullptr;
    return Py::new_reference_to(Py::Float(getExponentialModulationPtr()->computeModulation(time, timeOfMax, stormLength)));
}


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *ExponentialModulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int ExponentialModulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
