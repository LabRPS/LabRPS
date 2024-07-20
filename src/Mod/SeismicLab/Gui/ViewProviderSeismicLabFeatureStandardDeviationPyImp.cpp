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

#include "ViewProviderSeismicLabFeatureStandardDeviationPy.h"
#include "ViewProviderSeismicLabFeatureStandardDeviationPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderSeismicLabFeatureStandardDeviation.h"

using namespace SeismicLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderSeismicLabFeatureStandardDeviationPy::representation(void) const
{
    return std::string("<ViewProviderSeismicLabFeatureStandardDeviation object>");
}

PyObject* ViewProviderSeismicLabFeatureStandardDeviationPy::computeStandardDeviationValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderSeismicLabFeatureStandardDeviation* vp = this->getViewProviderSeismicLabFeatureStandardDeviationPtr();
    if (vp)
    {
        bool ok = vp->computeStandardDeviationValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderSeismicLabFeatureStandardDeviationPy::computeStandardDeviationVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderSeismicLabFeatureStandardDeviation* vp = this->getViewProviderSeismicLabFeatureStandardDeviationPtr();
    if (vp)
    {
        bool ok = vp->computeStandardDeviationVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderSeismicLabFeatureStandardDeviationPy::computeStandardDeviationVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderSeismicLabFeatureStandardDeviation* vp = this->getViewProviderSeismicLabFeatureStandardDeviationPtr();
    if (vp)
    {
        bool ok = vp->computeStandardDeviationVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderSeismicLabFeatureStandardDeviationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderSeismicLabFeatureStandardDeviationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
