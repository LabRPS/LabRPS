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
#include "WavePassageEffect.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of WavePassageEffectPy.xml)
#include "Mod/WindLabTools/App/wavePassageEffect/WavePassageEffectPy.h"
#include "Mod/WindLabTools/App/wavePassageEffect/WavePassageEffectPy.cpp"

//#include <API/WindLabAPI/RPSWindLabsimuDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string WavePassageEffectPy::representation(void) const
{
    return std::string("<WavePassageEffect object>");
}

PyObject* WavePassageEffectPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new WavePassageEffectPy(new WavePassageEffect());
}

// constructor method
int WavePassageEffectPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* WavePassageEffectPy::computeWavePassageEffect(PyObject *args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    double apparentWaveVelocity;

    if (!PyArg_ParseTuple(args, "OOdd", &pyLocationJ, &pyLocationK, &frequency, &apparentWaveVelocity))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();

    Py::List activeArray;
    activeArray.append(Py::Float((getWavePassageEffectPtr()->computeWavePassageEffect(*locationJ, *locationK, frequency, apparentWaveVelocity)).real()));
    activeArray.append(Py::Float((getWavePassageEffectPtr()->computeWavePassageEffect(*locationJ, *locationK, frequency, apparentWaveVelocity)).imag()));

    return Py::new_reference_to(Py::List(activeArray));

}
PyObject* WavePassageEffectPy::computeApparentWaveVelocity(PyObject *args)
{
    double velocityJ;
    double velocityK;
    double coefficient;

    if (!PyArg_ParseTuple(args, "ddd", &velocityJ, &velocityK, &coefficient))
    return nullptr;
    return Py::new_reference_to(Py::Float(getWavePassageEffectPtr()->computeApparentWaveVelocity(velocityJ, velocityK, coefficient)));
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *WavePassageEffectPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int WavePassageEffectPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
