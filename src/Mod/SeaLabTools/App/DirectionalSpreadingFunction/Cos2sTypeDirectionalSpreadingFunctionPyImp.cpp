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
#include "Cos2sTypeDirectionalSpreadingFunction.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of Cos2sTypeDirectionalSpreadingFunctionPy.xml)
#include "Mod/SeaLabTools/App/DirectionalSpreadingFunction/Cos2sTypeDirectionalSpreadingFunctionPy.h"
#include "Mod/SeaLabTools/App/DirectionalSpreadingFunction/Cos2sTypeDirectionalSpreadingFunctionPy.cpp"

//#include <API/SeaLabAPI/RPSSeaLabsimuDataPy.h>

using namespace SeaLabTools;

// returns a string which represents the object e.g. when printed in python
std::string Cos2sTypeDirectionalSpreadingFunctionPy::representation(void) const
{
    return std::string("<Cos2sTypeDirectionalSpreadingFunction object>");
}

PyObject* Cos2sTypeDirectionalSpreadingFunctionPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new Cos2sTypeDirectionalSpreadingFunctionPy(new Cos2sTypeDirectionalSpreadingFunction());
}

// constructor method
int Cos2sTypeDirectionalSpreadingFunctionPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* Cos2sTypeDirectionalSpreadingFunctionPy::computeSpreadingFunction(PyObject* args)
{
    double waveDirection;
    double principalWaveDirection;
    double spreadingExponent;

    if (!PyArg_ParseTuple(args, "ddd", &waveDirection, &principalWaveDirection, &spreadingExponent))
    return nullptr;
    return Py::new_reference_to(Py::Float(getCos2sTypeDirectionalSpreadingFunctionPtr()->computeSpreadingFunction(waveDirection, principalWaveDirection, spreadingExponent)));

}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *Cos2sTypeDirectionalSpreadingFunctionPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int Cos2sTypeDirectionalSpreadingFunctionPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
