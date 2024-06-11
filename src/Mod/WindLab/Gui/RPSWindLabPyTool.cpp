/***************************************************************************
 *   Copyright (c) 2016 Victor Titov (DeepSOIC) <vv.titov@gmail.com>       *
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

#include <Gui/MainWindow.h>
#include <Gui/AlphaPlot.h>
#include "RPSWindLabPyTool.h"
#include <Base/PyObjectBase.h>
#include <Libraries/Alphaplot/RPS.h>
#include <string.h> 
#include <boost/algorithm/string/predicate.hpp>

#include <boost/python/copy_const_reference.hpp>

namespace WindLabGui
{

PyObject* RPSWindLabPyTool::ShowArray(PyObject* self, PyObject* args)
{
    int row;
    int col;
    PyObject* numpyArray;

    if (!PyArg_ParseTuple(args, "iiO", &row, &col, &numpyArray))
        throw Py::Exception();
    try {
        std::vector<std::vector<double>> poly;
        int num_items = PyList_Size(numpyArray);
        if (num_items < 0)
            return NULL;
        Py::List list_f(numpyArray);

        for (int i = 0; i < num_items; ++i) {
            PyObject* pypoint = PyList_GetItem(numpyArray, i);
            std::vector<double> point;
            // Verify that each pypoint also a list
            if (!PyList_Check(pypoint)) {
                PyErr_SetString(PyExc_TypeError, "must pass in list of list");
                return NULL;
            }
            for (int j = 0; j < PyList_Size(pypoint); ++j) {
                PyObject* coord = PyList_GetItem(pypoint, j);
                double val;
                // Check that each coord is a long/double
                if (PyLong_Check(coord)) {
                    val = (double)PyLong_AsLong(coord);
                }
                else if (PyFloat_Check(coord)) {
                    val = PyFloat_AsDouble(coord);
                }
                else {
                    PyErr_SetString(PyExc_TypeError, "must pass in list of list of number");
                    return NULL;
                }
                point.push_back(val);
                //Base::Console().Warning(std::to_string(val).c_str());

            }
            poly.push_back(point);
        }

        Gui::getMainWindow()->getAlphaPlot()->newTableShowArrayPy(row, col, poly, QString::fromLatin1("table"));
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPyTool::ShowArrayAsMatrix(PyObject* self, PyObject* args)
{
    int row;
    int col;
    PyObject* numpyArray;

    if (!PyArg_ParseTuple(args, "iiO", &row, &col, &numpyArray))
        throw Py::Exception();
    try {
        std::vector<std::vector<double>> poly;
        int num_items = PyList_Size(numpyArray);
        Py::List list_f(numpyArray);

        for (int i = 0; i < num_items; ++i) {
            PyObject* pypoint = PyList_GetItem(numpyArray, i);
            std::vector<double> point;
            // Verify that each pypoint also a list
            if (!PyList_Check(pypoint)) {
                PyErr_SetString(PyExc_TypeError, "must pass in list of list");
                return NULL;
            }
            for (int j = 0; j < PyList_Size(pypoint); ++j) {
                PyObject* coord = PyList_GetItem(pypoint, j);
                double val;
                // Check that each coord is a long/double
                if (PyLong_Check(coord)) {
                    val = (double)PyLong_AsLong(coord);
                }
                else if (PyFloat_Check(coord)) {
                    val = PyFloat_AsDouble(coord);
                }
                else {
                    PyErr_SetString(PyExc_TypeError, "must pass in list of list of number");
                    return NULL;
                }
                point.push_back(val);
                //Base::Console().Warning(std::to_string(val).c_str());

            }
            poly.push_back(point);
        }

        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowArrayPy(row, col, poly, QString::fromLatin1("table"));

        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPyTool::ShowValueAsTable(PyObject* self, PyObject* args)
{
    double value;

    if (!PyArg_ParseTuple(args, "d", &value))
        throw Py::Exception();
    try {
        
        Table* table = Gui::getMainWindow()->getAlphaPlot()->newTable(QString::fromLatin1("table"),1,2);
        table->setCellValue(0, 0, 1);
        table->setCellValue(0, 1, value);

        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPyTool::GetActiveTable(PyObject* self, PyObject* args)
{
    //get the current table
    Table* table = qobject_cast<Table*>(Gui::getMainWindow()->getactiveMyWidget());
    if (!table)
        return NULL;

    //allocate momery for the active table
    mat activeTable(table->numRows(), table->numCols());

    //convert the Alphaplot table to Eigen table
    Gui::getMainWindow()->getAlphaPlot()->convertTableToEigenMatrix(table, activeTable);

 // <class 'numpy.array'>
    Py::List activeArray;
    for (int i = 0; i < activeTable.rows(); i++) {
        Py::List row;
        for (int j = 0; j < activeTable.cols(); j++) {
            row.append(Py::Float((activeTable.coeff(i, j))));
        }
        activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}

PyObject* RPSWindLabPyTool::GetActiveMatrix(PyObject* self, PyObject* args)
{
    //get the current matrix
    Matrix* matrix = qobject_cast<Matrix*>(Gui::getMainWindow()->getactiveMyWidget());

    if (!matrix)
       return NULL;

    //allocate momery for the active matrix
    mat activeMatrix(matrix->numRows(), matrix->numCols());

    //convert the Alphaplot matrix to Eigen matrix
    Gui::getMainWindow()->getAlphaPlot()->convertMatrixToEigenMatrix(matrix, activeMatrix);

    // <class 'numpy.array'>
    Py::List activeArray;
    for (int i = 0; i < activeMatrix.rows(); i++) {
        Py::List row;
        for (int j = 0; j < activeMatrix.cols(); j++) {
            row.append(Py::Float((activeMatrix.coeff(i, j))));
        }
        activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}


PyMethodDef RPSWindLabPyTool::Methods[] = {
    {"showArray", (PyCFunction)RPSWindLabPyTool::ShowArray, METH_VARARGS,
    "showArray(row,col,array) - take a python list and display it in Alphaplot table"},
    {"showArrayAsMatrix", (PyCFunction)RPSWindLabPyTool::ShowArrayAsMatrix, METH_VARARGS,
    "showArrayAsMatrix(row,col,array) - take a python list and display it in Alphaplot matrix"},
    {"showValueAsTable", (PyCFunction)RPSWindLabPyTool::ShowValueAsTable, METH_VARARGS,
    "showValueAsTable(value) - take a python floating value and display it in Alphaplot table"},
    {"getActiveTable", (PyCFunction)RPSWindLabPyTool::GetActiveTable, METH_VARARGS,
    "getActiveTable() - return the active AlphaPlot table"},
    {"getActiveMatrix", (PyCFunction)RPSWindLabPyTool::GetActiveMatrix, METH_VARARGS,
    "getActiveMatrix() - return the active AlphaPlot matrix"},
    {nullptr, nullptr, 0, nullptr}  /* Sentinel */
};


} //namespace WindLabAPI
