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

#include "RPSFeature.h"


// inclusion of the generated files (generated out of RPSFeaturePy.xml)
#include "RPSFeaturePy.h"
#include "RPSFeaturePy.cpp"

using namespace App;

// returns a string which represents the object e.g. when printed in python
std::string RPSFeaturePy::representation(void) const
{
    std::stringstream str;
    str << "<RPS Feature: " << getRPSFeaturePtr()->Label.getValue() << ">";
    return str.str();
}

PyObject *RPSFeaturePy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of RPSFeaturePy and the Twin object
    return new RPSFeaturePy(new RPSFeature());
}

// constructor method
int RPSFeaturePy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}


// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *RPSFeaturePy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int RPSFeaturePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}


