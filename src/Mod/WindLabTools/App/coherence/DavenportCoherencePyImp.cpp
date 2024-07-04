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
#include "DavenportCoherence.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of DavenportCoherencePy.xml)
#include "Mod/WindLabTools/App/coherence/DavenportCoherencePy.h"
#include "Mod/WindLabTools/App/coherence/DavenportCoherencePy.cpp"

//#include <API/WindLabAPI/RPSWindLabsimuDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string DavenportCoherencePy::representation(void) const
{
    return std::string("<DavenportCoherence object>");
}

PyObject* DavenportCoherencePy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new DavenportCoherencePy(new DavenportCoherence());
}

// constructor method
int DavenportCoherencePy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* DavenportCoherencePy::computeCoherenceValue(PyObject *args)
{
        double locationJxCoord;
        double locationJyCoord;
        double locationJzCoord;
        double locationKxCoord;
        double locationKyCoord;
        double locationKzCoord;
        double frequency;
        double locationJMeanSpeed;
        double locationKMeanSpeed;
        double exponentialDecayCx = 10;
        double exponentialDecayCy = 7;
        double exponentialDecayCz = 6;

    if (!PyArg_ParseTuple(args, "ddddddddd|ddd", &locationJxCoord, &locationJyCoord, &locationJzCoord,
                                                  &locationKxCoord, &locationKyCoord, &locationKzCoord,
                                                  &frequency, &locationJMeanSpeed, &locationKMeanSpeed,
                                                  &exponentialDecayCx, &exponentialDecayCy, &exponentialDecayCz))
    return nullptr;
    return Py::new_reference_to(Py::Float(getDavenportCoherencePtr()->computeCoherenceValue(locationJxCoord, locationJyCoord, locationJzCoord,
                                                  locationKxCoord, locationKyCoord, locationKzCoord,
                                                  frequency, locationJMeanSpeed, locationKMeanSpeed,
                                                  exponentialDecayCx, exponentialDecayCy, exponentialDecayCz)));
}

PyObject* DavenportCoherencePy::computeCrossCoherenceValue(PyObject *args)
{
        PyObject *locationJ;
        PyObject *locationK;
        double frequency;
        double locationJMeanSpeed;
        double locationKMeanSpeed;
        double exponentialDecayCx = 10;
        double exponentialDecayCy = 7;
        double exponentialDecayCz = 6;

    if (!PyArg_ParseTuple(args, "O!O!ddd|ddd", &(Base::VectorPy::Type),&locationJ,
                                                  &(Base::VectorPy::Type),&locationK,
                                                  &frequency, &locationJMeanSpeed, &locationKMeanSpeed,
                                                  &exponentialDecayCx, &exponentialDecayCy, &exponentialDecayCz))
    return nullptr;

    Base::Vector3d myLocationJ = static_cast<Base::VectorPy*>(locationJ)->value();
    Base::Vector3d myLocationK = static_cast<Base::VectorPy*>(locationK)->value();

    return Py::new_reference_to(Py::Float(getDavenportCoherencePtr()->computeCrossCoherenceValue(myLocationJ,
                                                  myLocationK,
                                                  frequency, locationJMeanSpeed, locationKMeanSpeed,
                                                  exponentialDecayCx, exponentialDecayCy, exponentialDecayCz)));
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *DavenportCoherencePy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int DavenportCoherencePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
