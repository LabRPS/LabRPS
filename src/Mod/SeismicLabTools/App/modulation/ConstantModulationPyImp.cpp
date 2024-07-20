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
#include "ConstantModulation.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of ConstantModulationPy.xml)
#include "Mod/SeismicLabTools/App/modulation/ConstantModulationPy.h"
#include "Mod/SeismicLabTools/App/modulation/ConstantModulationPy.cpp"

//#include <API/SeismicLabAPI/RPSSeismicLabsimuDataPy.h>

using namespace SeismicLabTools;

// returns a string which represents the object e.g. when printed in python
std::string ConstantModulationPy::representation(void) const
{
    return std::string("<ConstantModulation object>");
}

PyObject* ConstantModulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new ConstantModulationPy(new ConstantModulation());
}

// constructor method
int ConstantModulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* ConstantModulationPy::computeModulation(PyObject *args)
{
    double time;
    double constantValue = 1;

    if (!PyArg_ParseTuple(args, "d|d", &time, &constantValue));
    return nullptr;
    return Py::new_reference_to(Py::Float(getConstantModulationPtr()->computeModulation(time, constantValue)));
}


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *ConstantModulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int ConstantModulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
