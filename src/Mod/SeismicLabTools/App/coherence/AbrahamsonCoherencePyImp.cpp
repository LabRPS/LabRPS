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
#include "AbrahamsonCoherence.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of AbrahamsonCoherencePy.xml)
#include "Mod/SeismicLabTools/App/coherence/AbrahamsonCoherencePy.h"
#include "Mod/SeismicLabTools/App/coherence/AbrahamsonCoherencePy.cpp"

//#include <API/SeismicLabAPI/RPSSeismicLabsimuDataPy.h>

using namespace SeismicLabTools;

// returns a string which represents the object e.g. when printed in python
std::string AbrahamsonCoherencePy::representation(void) const
{
    return std::string("<AbrahamsonCoherence object>");
}

PyObject* AbrahamsonCoherencePy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new AbrahamsonCoherencePy(new AbrahamsonCoherence());
}

// constructor method
int AbrahamsonCoherencePy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* AbrahamsonCoherencePy::computeCoherenceValue(PyObject *args)
{
        double locationJxCoord;
        double locationJyCoord;
        double locationJzCoord;
        double locationKxCoord;
        double locationKyCoord;
        double locationKzCoord;
        double frequency;

    if (!PyArg_ParseTuple(args, "ddddddd", &locationJxCoord, &locationJyCoord, &locationJzCoord,
                                                  &locationKxCoord, &locationKyCoord, &locationKzCoord,
                                                  &frequency))
    return nullptr;
    return Py::new_reference_to(Py::Float(getAbrahamsonCoherencePtr()->computeCoherenceValue(
        locationJxCoord, locationJyCoord, locationJzCoord,locationKxCoord, locationKyCoord, locationKzCoord, frequency)));
}

PyObject* AbrahamsonCoherencePy::computeCrossCoherenceValue(PyObject *args)
{
        PyObject *locationJ;
        PyObject *locationK;
        double frequency;

    if (!PyArg_ParseTuple(args, "O!O!d", &(Base::VectorPy::Type),&locationJ,
                                                  &(Base::VectorPy::Type),&locationK,
                                                  &frequency))
    return nullptr;

    Base::Vector3d myLocationJ = static_cast<Base::VectorPy*>(locationJ)->value();
    Base::Vector3d myLocationK = static_cast<Base::VectorPy*>(locationK)->value();

    return Py::new_reference_to(Py::Float(getAbrahamsonCoherencePtr()->computeCrossCoherenceValue(myLocationJ, myLocationK, frequency)));
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *AbrahamsonCoherencePy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int AbrahamsonCoherencePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
