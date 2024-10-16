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
#include "BoxCarModulation.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of BoxCarModulationPy.xml)
#include "Mod/SeismicLabTools/App/modulation/BoxCarModulationPy.h"
#include "Mod/SeismicLabTools/App/modulation/BoxCarModulationPy.cpp"

//#include <API/SeismicLabAPI/RPSSeismicLabsimuDataPy.h>

using namespace SeismicLabTools;

// returns a string which represents the object e.g. when printed in python
std::string BoxCarModulationPy::representation(void) const
{
    return std::string("<BoxCarModulation object>");
}

PyObject* BoxCarModulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new BoxCarModulationPy(new BoxCarModulation());
}

// constructor method
int BoxCarModulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* BoxCarModulationPy::computeModulation(PyObject *args)
{
    double time;
    double scalingFactor;
    double strongMotionPeriod;


    if (!PyArg_ParseTuple(args, "ddd", &time, &scalingFactor, &strongMotionPeriod));
    return nullptr;
    return Py::new_reference_to(Py::Float(getBoxCarModulationPtr()->computeModulation(time, scalingFactor, strongMotionPeriod)));
}


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *BoxCarModulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int BoxCarModulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
