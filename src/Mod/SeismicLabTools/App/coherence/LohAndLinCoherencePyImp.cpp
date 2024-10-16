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
#include "LohAndLinCoherence.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of LohAndLinCoherencePy.xml)
#include "Mod/SeismicLabTools/App/coherence/LohAndLinCoherencePy.h"
#include "Mod/SeismicLabTools/App/coherence/LohAndLinCoherencePy.cpp"

//#include <API/SeismicLabAPI/RPSSeismicLabsimuDataPy.h>

using namespace SeismicLabTools;

// returns a string which represents the object e.g. when printed in python
std::string LohAndLinCoherencePy::representation(void) const
{
    return std::string("<LohAndLinCoherence object>");
}

PyObject* LohAndLinCoherencePy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new LohAndLinCoherencePy(new LohAndLinCoherence());
}

// constructor method
int LohAndLinCoherencePy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* LohAndLinCoherencePy::computeCoherenceValue(PyObject *args)
{
        double locationJxCoord;
        double locationJyCoord;
        double locationJzCoord;
        double locationKxCoord;
        double locationKyCoord;
        double locationKzCoord;
        double frequency;
        double parameterAlpha;
        double parameterB;

    if (!PyArg_ParseTuple(args, "ddddddddd", &locationJxCoord, &locationJyCoord, &locationJzCoord,
                                                  &locationKxCoord, &locationKyCoord, &locationKzCoord,
                                                  &frequency, &parameterAlpha, &parameterB))
    return nullptr;
    return Py::new_reference_to(Py::Float(getLohAndLinCoherencePtr()->computeCoherenceValue(locationJxCoord, locationJyCoord, locationJzCoord,
                                                  locationKxCoord, locationKyCoord, locationKzCoord,
                                                  frequency, parameterAlpha, parameterB)));
}

PyObject* LohAndLinCoherencePy::computeCrossCoherenceValue(PyObject *args)
{
        PyObject *locationJ;
        PyObject *locationK;
        double frequency;
        double parameterAlpha;
        double parameterB;

    if (!PyArg_ParseTuple(args, "O!O!ddd", &(Base::VectorPy::Type),&locationJ,
                                                  &(Base::VectorPy::Type),&locationK,
                                                  &frequency, &parameterAlpha, &parameterB))
    return nullptr;

    Base::Vector3d myLocationJ = static_cast<Base::VectorPy*>(locationJ)->value();
    Base::Vector3d myLocationK = static_cast<Base::VectorPy*>(locationK)->value();

    return Py::new_reference_to(Py::Float(getLohAndLinCoherencePtr()->computeCrossCoherenceValue(myLocationJ, myLocationK, frequency, parameterAlpha, parameterB)));
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *LohAndLinCoherencePy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int LohAndLinCoherencePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
