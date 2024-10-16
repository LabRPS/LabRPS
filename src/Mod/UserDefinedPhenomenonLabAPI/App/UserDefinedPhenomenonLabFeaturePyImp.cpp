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

#include <CXX/Objects.hxx>

#include "Mod/UserDefinedPhenomenonLabAPI/App/UserDefinedPhenomenonLabFeature.h"


// inclusion of the generated files (generated out of UserDefinedPhenomenonLabFeaturePy.xml)
#include "UserDefinedPhenomenonLabFeaturePy.h"
#include "UserDefinedPhenomenonLabFeaturePy.cpp"

using namespace UserDefinedPhenomenonLabAPI;

// returns a string which represents the object e.g. when printed in python
std::string UserDefinedPhenomenonLabFeaturePy::representation(void) const
{
    return std::string("<UserDefinedPhenomenonLabFeature object>");
}

PyObject *UserDefinedPhenomenonLabFeaturePy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of UserDefinedPhenomenonLabFeaturePy and the Twin object
    return new UserDefinedPhenomenonLabFeaturePy(new UserDefinedPhenomenonLabFeature());
}

// constructor method
int UserDefinedPhenomenonLabFeaturePy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *UserDefinedPhenomenonLabFeaturePy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int UserDefinedPhenomenonLabFeaturePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}


