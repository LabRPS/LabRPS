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

#include "ViewProviderWindLabFeatureTurbulenceScalePy.h"
#include "ViewProviderWindLabFeatureTurbulenceScalePy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureTurbulenceScale.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureTurbulenceScalePy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureTurbulenceScale object>");
}

PyObject* ViewProviderWindLabFeatureTurbulenceScalePy::computeTurbulenceScaleValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTurbulenceScale* vp = this->getViewProviderWindLabFeatureTurbulenceScalePtr();
    if (vp)
    {
        bool ok = vp->computeTurbulenceScaleValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureTurbulenceScalePy::computeTurbulenceScaleVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTurbulenceScale* vp = this->getViewProviderWindLabFeatureTurbulenceScalePtr();
    if (vp)
    {
        bool ok = vp->computeTurbulenceScaleVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureTurbulenceScalePy::computeTurbulenceScaleVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTurbulenceScale* vp = this->getViewProviderWindLabFeatureTurbulenceScalePtr();
    if (vp)
    {
        bool ok = vp->computeTurbulenceScaleVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}
PyObject *ViewProviderWindLabFeatureTurbulenceScalePy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureTurbulenceScalePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
