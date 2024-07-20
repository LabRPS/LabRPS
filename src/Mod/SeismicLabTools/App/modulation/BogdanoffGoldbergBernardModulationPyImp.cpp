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
#include "BogdanoffGoldbergBernardModulation.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of BogdanoffGoldbergBernardModulationPy.xml)
#include "Mod/SeismicLabTools/App/modulation/BogdanoffGoldbergBernardModulationPy.h"
#include "Mod/SeismicLabTools/App/modulation/BogdanoffGoldbergBernardModulationPy.cpp"

//#include <API/SeismicLabAPI/RPSSeismicLabsimuDataPy.h>

using namespace SeismicLabTools;

// returns a string which represents the object e.g. when printed in python
std::string BogdanoffGoldbergBernardModulationPy::representation(void) const
{
    return std::string("<BogdanoffGoldbergBernardModulation object>");
}

PyObject* BogdanoffGoldbergBernardModulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new BogdanoffGoldbergBernardModulationPy(new BogdanoffGoldbergBernardModulation());
}

// constructor method
int BogdanoffGoldbergBernardModulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* BogdanoffGoldbergBernardModulationPy::computeModulation(PyObject *args)
{
    double time; 
    double coefficientOne;
    double coefficientTwo;

    if (!PyArg_ParseTuple(args, "ddd", &time, &coefficientOne, &coefficientTwo))
    return nullptr;
    return Py::new_reference_to(Py::Float(getBogdanoffGoldbergBernardModulationPtr()->computeModulation(time, coefficientOne, coefficientTwo)));
}


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *BogdanoffGoldbergBernardModulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int BogdanoffGoldbergBernardModulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
