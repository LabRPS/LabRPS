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
#include "GeneralizedKaimalSpectrum.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of GeneralizedKaimalSpectrumPy.xml)
#include "Mod/WindLabTools/App/spectrum/GeneralizedKaimalSpectrumPy.h"
#include "Mod/WindLabTools/App/spectrum/GeneralizedKaimalSpectrumPy.cpp"

//#include <API/WindLabAPI/RPSWindLabSimulationDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string GeneralizedKaimalSpectrumPy::representation(void) const
{
    return std::string("<GeneralizedKaimalSpectrum object>");
}

PyObject* GeneralizedKaimalSpectrumPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new GeneralizedKaimalSpectrumPy(new GeneralizedKaimalSpectrum());
}

// constructor method
int GeneralizedKaimalSpectrumPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* GeneralizedKaimalSpectrumPy::computeGeneralizedKaimalWindAutoSpectrum(PyObject *args)
{
        double frequency;
        double height;
        double meanSpeed;
        double shearVelocity;
        double a = 200.0;
        double b = 1.0;
        double c = 0.0;
        double d = 1.0;
        double e = 1.0;
        double f = 1.0;
        double g = 1.0;
        double h = 50.0;
        double i = 1.0;
        double j = 5.0/3.0;

    if (!PyArg_ParseTuple(args, "dddd|dddddddddd", &frequency, &height, &meanSpeed, &shearVelocity, &a,  &b,  &c,  &d,  &e,  &f,  &g,  &h,  &i,  &j))
    return nullptr;
    return Py::new_reference_to(Py::Float(getGeneralizedKaimalSpectrumPtr()->computeGeneralizedKaimalWindAutoSpectrum(
        frequency, height, meanSpeed, shearVelocity, a,  b,  c,  d,  e,  f,  g,  h,  i,  j)));

}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *GeneralizedKaimalSpectrumPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int GeneralizedKaimalSpectrumPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
