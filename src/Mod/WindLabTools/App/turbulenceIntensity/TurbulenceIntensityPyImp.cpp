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
#include "TurbulenceIntensity.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of TurbulenceIntensityPy.xml)
#include "Mod/WindLabTools/App/turbulenceIntensity/TurbulenceIntensityPy.h"
#include "Mod/WindLabTools/App/turbulenceIntensity/TurbulenceIntensityPy.cpp"

//#include <API/WindLabAPI/RPSWindLabSimulationDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string TurbulenceIntensityPy::representation(void) const
{
    return std::string("<TurbulenceIntensity object>");
}

PyObject* TurbulenceIntensityPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new TurbulenceIntensityPy(new TurbulenceIntensity());
}

// constructor method
int TurbulenceIntensityPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* TurbulenceIntensityPy::computeASCETurbulenceIntensityValue(PyObject *args)
{
        double height;
        double intensity10;

    if (!PyArg_ParseTuple(args, "dd", &height, &intensity10))
    return nullptr;
    return Py::new_reference_to(Py::Float(getTurbulenceIntensityPtr()->computeASCETurbulenceIntensityValue(height, intensity10)));
}

PyObject* TurbulenceIntensityPy::computeASNZ1170TurbulenceIntensityValue(PyObject *args)
{
        double height;
        double intensity10;
        double exponent;

    if (!PyArg_ParseTuple(args, "ddd", &height, &intensity10, &exponent))
    return nullptr;
    return Py::new_reference_to(Py::Float(getTurbulenceIntensityPtr()->computeASNZ1170TurbulenceIntensityValue(height, intensity10, exponent)));
}


PyObject* TurbulenceIntensityPy::computeEurocodeTurbulenceIntensityValue(PyObject *args)
{
        double height;
        double referenceHeight;

    if (!PyArg_ParseTuple(args, "dd", &height, &referenceHeight))
    return nullptr;
    return Py::new_reference_to(Py::Float(getTurbulenceIntensityPtr()->computeEurocodeTurbulenceIntensityValue(height, referenceHeight)));
}


PyObject* TurbulenceIntensityPy::computeIS875TurbulenceIntensityValue(PyObject* args)
{
        double height;
        double referenceHeight;

    if (!PyArg_ParseTuple(args, "dd", &height, &referenceHeight))
    return nullptr;
    return Py::new_reference_to(Py::Float(getTurbulenceIntensityPtr()->computeIS875TurbulenceIntensityValue(height, referenceHeight)));
}
PyObject* TurbulenceIntensityPy::computeISOTurbulenceIntensityValue(PyObject* args)
{
        double height;
        double referenceHeight;

    if (!PyArg_ParseTuple(args, "dd", &height, &referenceHeight))
    return nullptr;
    return Py::new_reference_to(Py::Float(getTurbulenceIntensityPtr()->computeISOTurbulenceIntensityValue(height, referenceHeight)));
}


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *TurbulenceIntensityPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int TurbulenceIntensityPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
