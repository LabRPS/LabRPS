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
#include "VonKarmanSpectrum.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of VonKarmanSpectrumPy.xml)
#include "Mod/WindLabTools/App/spectrum/VonKarmanSpectrumPy.h"
#include "Mod/WindLabTools/App/spectrum/VonKarmanSpectrumPy.cpp"

//#include <API/WindLabAPI/RPSWindLabsimuDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string VonKarmanSpectrumPy::representation(void) const
{
    return std::string("<VonKarmanSpectrum object>");
}

PyObject* VonKarmanSpectrumPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new VonKarmanSpectrumPy(new VonKarmanSpectrum());
}

// constructor method
int VonKarmanSpectrumPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* VonKarmanSpectrumPy::computeAlongWindAutoSpectrum(PyObject* args)
{
        double frequency;
        double meanSpeed;
        double integralLengthScale;
        double standardDeviation;
        double Par1;
        double Par2;

    if (!PyArg_ParseTuple(args, "dddddd", &frequency, &meanSpeed, &integralLengthScale, &standardDeviation, &Par1, &Par2))
    return nullptr;
    return Py::new_reference_to(Py::Float(getVonKarmanSpectrumPtr()->computeAlongWindAutoSpectrum(
        frequency, meanSpeed, integralLengthScale, standardDeviation, Par1, Par2)));

}

PyObject* VonKarmanSpectrumPy::computeAcrossWindAutoSpectrum(PyObject* args)
{
        double frequency;
        double meanSpeed;
        double integralLengthScale;
        double standardDeviation;
        double Par1;
        double Par2;
        double Par3;

    if (!PyArg_ParseTuple(args, "ddddddd", &frequency, &meanSpeed, &integralLengthScale, &standardDeviation, &Par1, &Par2, &Par3))
    return nullptr;
    return Py::new_reference_to(Py::Float(getVonKarmanSpectrumPtr()->computeAcrossWindAutoSpectrum(
        frequency, meanSpeed, integralLengthScale, standardDeviation, Par1, Par2, Par3)));

}

PyObject* VonKarmanSpectrumPy::computeVerticalWindAutoSpectrum(PyObject* args)
{
        double frequency;
        double meanSpeed;
        double integralLengthScale;
        double standardDeviation;
        double Par1;
        double Par2;
        double Par3;

    if (!PyArg_ParseTuple(args, "ddddddd", &frequency, &meanSpeed, &integralLengthScale, &standardDeviation, &Par1, &Par2, &Par3))
    return nullptr;
    return Py::new_reference_to(Py::Float(getVonKarmanSpectrumPtr()->computeVerticalWindAutoSpectrum(
        frequency, meanSpeed, integralLengthScale, standardDeviation, Par1, Par2, Par3)));

}

 
// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *VonKarmanSpectrumPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int VonKarmanSpectrumPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
