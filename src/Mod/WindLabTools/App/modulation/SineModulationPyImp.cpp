/***************************************************************************
 *   Copyright (c) 2010 Jürgen Riegel <juergen.riegel@web.de>              *
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

#include <CXX/Objects.hxx>
#include "SineModulation.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of SineModulationPy.xml)
#include "Mod/WindLabTools/App/modulation/SineModulationPy.h"
#include "Mod/WindLabTools/App/modulation/SineModulationPy.cpp"

//#include <API/WindLabAPI/RPSWindLabSimulationDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string SineModulationPy::representation(void) const
{
    return std::string("<SineModulation object>");
}

PyObject* SineModulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new SineModulationPy(new SineModulation());
}

// constructor method
int SineModulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* SineModulationPy::computeModulation(PyObject *args)
{
    double time;
    double pulseDuration;

    if (!PyArg_ParseTuple(args, "dd", &time, &pulseDuration))
    return nullptr;
    return Py::new_reference_to(Py::Float(getSineModulationPtr()->computeModulation(time, pulseDuration)));
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *SineModulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int SineModulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
