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
#include "SeismicGroundMotionSpectrum.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of SeismicGroundMotionSpectrumPy.xml)
#include "Mod/SeismicLabTools/App/spectrum/SeismicGroundMotionSpectrumPy.h"
#include "Mod/SeismicLabTools/App/spectrum/SeismicGroundMotionSpectrumPy.cpp"

//#include <API/SeismicLabAPI/RPSSeismicLabsimuDataPy.h>

using namespace SeismicLabTools;

// returns a string which represents the object e.g. when printed in python
std::string SeismicGroundMotionSpectrumPy::representation(void) const
{
    return std::string("<SeismicGroundMotionSpectrum object>");
}

PyObject* SeismicGroundMotionSpectrumPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new SeismicGroundMotionSpectrumPy(new SeismicGroundMotionSpectrum());
}

// constructor method
int SeismicGroundMotionSpectrumPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *SeismicGroundMotionSpectrumPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int SeismicGroundMotionSpectrumPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
