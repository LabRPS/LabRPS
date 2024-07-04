/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
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

#include <Base/VectorPy.h>
#include <CXX/Objects.hxx>

#include "WindLabSimuData.h"


// inclusion of the generated files (generated out of WindLabSimuDataPy.xml)
#include "WindLabSimuDataPy.h"
#include "WindLabSimuDataPy.cpp"

using namespace WindLabAPI;

// returns a string which represents the object e.g. when printed in python
std::string WindLabSimuDataPy::representation(void) const
{
    return std::string("<WindLabSimuData object>");
    std::stringstream str;
    str << "<WindLab Simulation Data>";
    return str.str();
}

PyObject *WindLabSimuDataPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of WindLabSimuDataPy and the Twin object
    return new WindLabSimuDataPy(new WindLabSimuData());
}

// constructor method
int WindLabSimuDataPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++

PyObject *WindLabSimuDataPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int WindLabSimuDataPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}


