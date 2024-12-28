/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *                *
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

#include <Gui/MainWindow.h>
#include <Gui/AlphaPlot.h>
#include "RPSGeneralToolsPyTool.h"
#include <Base/PyObjectBase.h>
#include <Libraries/Alphaplot/RPS.h>
#include <string.h> 
#include <boost/algorithm/string/predicate.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <Libraries/Alphaplot/2Dplot/Layout2D.h>
#include <Libraries/Alphaplot/future/core/column/Column.h>

namespace GeneralToolsGui
{

PyObject* RPSGeneralToolsPyTool::ShowArray(PyObject* self, PyObject* args)
{
    int row;
    int col;
    bool drawCurve = true;
    PyObject* numpyArray;

    if (!PyArg_ParseTuple(args, "iiO|b", &row, &col, &numpyArray, &drawCurve))
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
            // Verify that each pypoint also is a list
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

            }
            poly.push_back(point);
        }
    Table *table = Gui::getMainWindow()->getAlphaPlot()->newTableShowArrayPy(row, col, poly, QString::fromLatin1("table"));
        if(drawCurve)
        {
            Layout2D* layout = Gui::getMainWindow()->getAlphaPlot()->newGraph2D();
            if (!layout)
                return NULL;
            if (!table)
                return NULL;
            if (table->numCols() < 2)
                return NULL;
            QList<Column*> columns;
            columns.append(table->column(0));
            columns.append(table->column(1));
            layout->generateCurve2DPlot(AxisRect2D::LineScatterType::Line2D, table, columns.at(0), QList<Column *>() << columns.at(1), 0, table->numRows() - 1);
        }

        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSGeneralToolsPyTool::ShowArrayAsMatrix(PyObject* self, PyObject* args)
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

PyObject* RPSGeneralToolsPyTool::ShowValueAsTable(PyObject* self, PyObject* args)
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

PyObject* RPSGeneralToolsPyTool::GetActiveTable(PyObject* self, PyObject* args)
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

PyObject* RPSGeneralToolsPyTool::GetActiveMatrix(PyObject* self, PyObject* args)
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

PyObject* RPSGeneralToolsPyTool::GetTableByName(PyObject* self, PyObject* args)
{
    char* tableName = nullptr;
    if (!PyArg_ParseTuple(args, "s", &tableName))
        return nullptr;

    //get the table by a name
    Table* table = Gui::getMainWindow()->getAlphaPlot()->getTableByName(QString::fromLatin1(tableName));

    if (!table)
       return NULL;

    //allocate momery for the table
    mat theTable(table->numRows(), table->numCols());

    //convert the Alphaplot table to Eigen matrix
    Gui::getMainWindow()->getAlphaPlot()->convertTableToEigenMatrix(table, theTable);

    // <class 'numpy.array'>
    Py::List theArray;
    for (int i = 0; i < theTable.rows(); i++) {
        Py::List row;
        for (int j = 0; j < theTable.cols(); j++) {
            row.append(Py::Float((theTable.coeff(i, j))));
        }
        theArray.append(row);
    }
    return boost::python::incref(theArray.ptr());
}
PyObject* RPSGeneralToolsPyTool::GetMatrixByName(PyObject* /*self*/, PyObject* args)
{
    char* matrixName = nullptr;
    if (!PyArg_ParseTuple(args, "s", &matrixName))
        return nullptr;

    //get the matrix by a name
    Matrix* matrix = Gui::getMainWindow()->getAlphaPlot()->getMatrixByName(QString::fromLatin1(matrixName));

    if (!matrix)
       return NULL;

    //allocate momery for the matrix
    mat theMatrix(matrix->numRows(), matrix->numCols());

    //convert the Alphaplot matrix to Eigen matrix
    Gui::getMainWindow()->getAlphaPlot()->convertMatrixToEigenMatrix(matrix, theMatrix);

    // <class 'numpy.array'>
    Py::List theArray;
    for (int i = 0; i < theMatrix.rows(); i++) {
        Py::List row;
        for (int j = 0; j < theMatrix.cols(); j++) {
            row.append(Py::Float((theMatrix.coeff(i, j))));
        }
        theArray.append(row);
    }
    return boost::python::incref(theArray.ptr());
}

PyMethodDef RPSGeneralToolsPyTool::Methods[] = {
    {"showArray", (PyCFunction)RPSGeneralToolsPyTool::ShowArray, METH_VARARGS,
    "showArray(row,col,array) - take a python list and display it in Alphaplot table"},
    {"showArrayAsMatrix", (PyCFunction)RPSGeneralToolsPyTool::ShowArrayAsMatrix, METH_VARARGS,
    "showArrayAsMatrix(row,col,array) - take a python list and display it in Alphaplot matrix"},
    {"showValueAsTable", (PyCFunction)RPSGeneralToolsPyTool::ShowValueAsTable, METH_VARARGS,
    "showValueAsTable(value) - take a python floating value and display it in Alphaplot table"},
    {"getActiveTable", (PyCFunction)RPSGeneralToolsPyTool::GetActiveTable, METH_VARARGS,
    "getActiveTable() - return the active AlphaPlot table as python list of lists"},
    {"getActiveMatrix", (PyCFunction)RPSGeneralToolsPyTool::GetActiveMatrix, METH_VARARGS,
    "getActiveMatrix() - return the active AlphaPlot matrix as python list of lists"},
    {"getTableByName", (PyCFunction)RPSGeneralToolsPyTool::GetTableByName, METH_VARARGS,
    "getTableByName() - return the AlphaPlot table as python list of lists given the AphaPlot table name"},
    {"getMatrixByName", (PyCFunction)RPSGeneralToolsPyTool::GetMatrixByName, METH_VARARGS,
    "getMatrixByName() - return the AlphaPlot matrix as python list of lists given the AphaPlot matrix name"},
    {nullptr, nullptr, 0, nullptr}  /* Sentinel */
};


} //namespace GeneralToolsAPI
