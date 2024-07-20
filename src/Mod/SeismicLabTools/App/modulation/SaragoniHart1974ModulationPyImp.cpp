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
#include "SaragoniHart1974Modulation.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of SaragoniHart1974ModulationPy.xml)
#include "Mod/SeismicLabTools/App/modulation/SaragoniHart1974ModulationPy.h"
#include "Mod/SeismicLabTools/App/modulation/SaragoniHart1974ModulationPy.cpp"

//#include <API/SeismicLabAPI/RPSSeismicLabsimuDataPy.h>

using namespace SeismicLabTools;

// returns a string which represents the object e.g. when printed in python
std::string SaragoniHart1974ModulationPy::representation(void) const
{
    return std::string("<SaragoniHart1974Modulation object>");
}

PyObject* SaragoniHart1974ModulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new SaragoniHart1974ModulationPy(new SaragoniHart1974Modulation());
}

// constructor method
int SaragoniHart1974ModulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* SaragoniHart1974ModulationPy::computeModulation(PyObject *args)
{
    double time;
    double alphaOne;
    double alphaTwo;
    double alphaThree;

    if (!PyArg_ParseTuple(args, "dddd", &time, &alphaOne, &alphaTwo, &alphaThree))
    return nullptr;
    return Py::new_reference_to(Py::Float(getSaragoniHart1974ModulationPtr()->computeModulation(time, alphaOne, alphaTwo, alphaThree)));
}


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *SaragoniHart1974ModulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int SaragoniHart1974ModulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
