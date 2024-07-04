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
#include "HongandHong2021MeanWindSpeed.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of HongandHong2021MeanWindSpeedPy.xml)
#include "Mod/WindLabTools/App/meanWindSpeed/HongandHong2021MeanWindSpeedPy.h"
#include "Mod/WindLabTools/App/meanWindSpeed/HongandHong2021MeanWindSpeedPy.cpp"

//#include <API/WindLabAPI/RPSWindLabsimuDataPy.h>

using namespace WindLabTools;

// returns a string which represents the object e.g. when printed in python
std::string HongandHong2021MeanWindSpeedPy::representation(void) const
{
    return std::string("<HongandHong2021MeanWindSpeed object>");
}

PyObject* HongandHong2021MeanWindSpeedPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new HongandHong2021MeanWindSpeedPy(new HongandHong2021MeanWindSpeed());
}

// constructor method
int HongandHong2021MeanWindSpeedPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* HongandHong2021MeanWindSpeedPy::computeMeanWindSpeed(PyObject *args)
{
        double height;
        double xCoordinate;
        double time;

    if (!PyArg_ParseTuple(args, "ddd", &height, &xCoordinate, &time))
    return nullptr;
    return Py::new_reference_to(Py::Float(getHongandHong2021MeanWindSpeedPtr()->computeMeanWindSpeed(height, xCoordinate, time)));

}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *HongandHong2021MeanWindSpeedPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int HongandHong2021MeanWindSpeedPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
