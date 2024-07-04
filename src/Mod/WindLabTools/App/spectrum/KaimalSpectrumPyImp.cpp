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
#include "KaimalSpectrum.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of KaimalSpectrumPy.xml)
#include "Mod/WindLabTools/App/spectrum/KaimalSpectrumPy.h"
#include "Mod/WindLabTools/App/spectrum/KaimalSpectrumPy.cpp"

//#include <API/WindLabAPI/RPSWindLabsimuDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string KaimalSpectrumPy::representation(void) const
{
    return std::string("<KaimalSpectrum object>");
}

PyObject* KaimalSpectrumPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new KaimalSpectrumPy(new KaimalSpectrum());
}

// constructor method
int KaimalSpectrumPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* KaimalSpectrumPy::computeAlongWindAutoSpectrum(PyObject *args)
{
        double frequency;
        double height;
        double meanSpeed;
        double shearVelocity;
        double Par1 = 200.0;
        double Par2 = 50.0;

    if (!PyArg_ParseTuple(args, "dddd|dd", &frequency, &height, &meanSpeed, &shearVelocity, &Par1, &Par2))
    return nullptr;
    return Py::new_reference_to(Py::Float(getKaimalSpectrumPtr()->computeAlongWindAutoSpectrum(
        frequency, height, meanSpeed, shearVelocity, Par1, Par2)));

}

PyObject* KaimalSpectrumPy::computeAcrossWindAutoSpectrum(PyObject *args)
{
        double frequency;
        double height;
        double meanSpeed;
        double shearVelocity;
        double Par1 = 17.0;
        double Par2 = 9.5;

    if (!PyArg_ParseTuple(args, "dddd|dd", &frequency, &height, &meanSpeed, &shearVelocity, &Par1, &Par2))
    return nullptr;
    return Py::new_reference_to(Py::Float(getKaimalSpectrumPtr()->computeAcrossWindAutoSpectrum(
        frequency, height, meanSpeed, shearVelocity, Par1, Par2)));

}

PyObject* KaimalSpectrumPy::computeVerticalWindAutoSpectrum(PyObject *args)
{
        double frequency;
        double height;
        double meanSpeed;
        double shearVelocity;
        double Par1 = 2.0;
        double Par2 = 5.3;

    if (!PyArg_ParseTuple(args, "dddd|dd", &frequency, &height, &meanSpeed, &shearVelocity, &Par1, &Par2))
    return nullptr;
    return Py::new_reference_to(Py::Float(getKaimalSpectrumPtr()->computeVerticalWindAutoSpectrum(
        frequency, height, meanSpeed, shearVelocity, Par1, Par2)));

}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *KaimalSpectrumPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int KaimalSpectrumPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
