/***************************************************************************
 *   Copyright (c) 2007 Jürgen Riegel <juergen.riegel@web.de>              *
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

// inclusion of the generated files (generated out of RPSWindLabFrameworkPy.xml)
#include "RPSWindLabFrameworkPy.h"
#include "RPSWindLabFrameworkPy.cpp"

using namespace Base;

// returns a string which represent the object e.g. when printed in python
std::string RPSWindLabFrameworkPy::representation() const
{
    return std::string("<WindLab Framework object>");
}


PyObject*  RPSWindLabFrameworkPy::computeLocationCoordinateMatrixP3(PyObject *args)
{
    return NULL;
}


PyObject *RPSWindLabFrameworkPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int RPSWindLabFrameworkPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}


