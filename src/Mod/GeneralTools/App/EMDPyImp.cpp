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
#include <Base/VectorPy.h>
#include "EMD.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/python/copy_const_reference.hpp>

// inclusion of the generated files (generated out of EMDPy.xml)
#include "Mod/GeneralTools/App/EMDPy.h"
#include "Mod/GeneralTools/App/EMDPy.cpp"

//#include <API/WindLabAPI/RPSWindLabSimulationDataPy.h>

using namespace GeneralTools;

// returns a string which represents the object e.g. when printed in python
std::string EMDPy::representation(void) const
{
    return std::string("<EMD object>");
}

PyObject* EMDPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new EMDPy(new EMD());
}

// constructor method
int EMDPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* EMDPy::computeEMD(PyObject *args)
{
    PyObject* signal;
    int maxIMFs = 10;

    if (!PyArg_ParseTuple(args, "O|i", &signal, &maxIMFs))
        throw Py::Exception();
    try {
        std::vector<double> data;
        std::vector<std::vector<double>> results;
        int num_items = PyList_Size(signal);
            for (int j = 0; j < PyList_Size(signal); ++j) {
                PyObject* sig = PyList_GetItem(signal, j);
                double val;
                if (PyLong_Check(sig)) {
                    val = (double)PyLong_AsLong(sig);
                }
                else if (PyFloat_Check(sig)) {
                    val = PyFloat_AsDouble(sig);
                }
                else {
                    PyErr_SetString(PyExc_TypeError, "must pass in list of number");
                    return NULL;
                }
                data.push_back(val);
            }

            results = getEMDPtr()->emd(data, maxIMFs);

            Py::List activeArray;
            for (int i = 0; i < results.size(); i++) {
                Py::List row;
                for (int j = 0; j < results[i].size(); j++) {
                    row.append(Py::Float(results[i][j]));
                }
                activeArray.append(row);
            }
            return boost::python::incref(activeArray.ptr());
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *EMDPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int EMDPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
