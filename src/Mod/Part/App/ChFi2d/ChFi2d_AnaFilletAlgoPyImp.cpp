/***************************************************************************
 *   Copyright (c) 2022 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the LabRPS CAx development system.              *
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
#ifndef _PreComp_
# include <gp_Pln.hxx>
# include <Standard_Failure.hxx>
# include <TopoDS.hxx>
# include <TopoDS_Edge.hxx>
# include <TopoDS_Wire.hxx>
#endif

#include <Mod/Part/App/ChFi2d/ChFi2d_AnaFilletAlgoPy.h>
#include <Mod/Part/App/ChFi2d/ChFi2d_AnaFilletAlgoPy.cpp>
#include <Mod/Part/App/TopoShapeEdgePy.h>
#include <Mod/Part/App/TopoShapeWirePy.h>
#include <Mod/Part/App/Geometry.h>
#include <Mod/Part/App/PlanePy.h>
#include <Base/VectorPy.h>
#include "Tools.h"

using namespace Part;


PyObject *ChFi2d_AnaFilletAlgoPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of ChFi2d_AnaFilletAlgoPy and the Twin object
    return new ChFi2d_AnaFilletAlgoPy(new ChFi2d_AnaFilletAlgo);
}

// constructor method
int ChFi2d_AnaFilletAlgoPy::PyInit(PyObject* args, PyObject* /*kwd*/)
{
    if (PyArg_ParseTuple(args, ""))
        return 0;

    PyErr_Clear();
    PyObject* wire;
    PyObject* plane;
    if (PyArg_ParseTuple(args, "O!O!", &TopoShapeWirePy::Type, &wire, &PlanePy::Type, &plane)) {
        TopoDS_Shape shape = static_cast<TopoShapeWirePy*>(wire)->getTopoShapePtr()->getShape();
        Handle(Geom_Plane) hPlane = Handle(Geom_Plane)::DownCast(static_cast<PlanePy*>(plane)->getGeomPlanePtr()->handle());
        getChFi2d_AnaFilletAlgoPtr()->Init(TopoDS::Wire(shape), hPlane->Pln());
        return 0;
    }

    PyErr_Clear();
    PyObject* edge1;
    PyObject* edge2;
    if (PyArg_ParseTuple(args, "O!O!O!", &TopoShapeEdgePy::Type, &edge1,
                                         &TopoShapeEdgePy::Type, &edge2,
                                         &PlanePy::Type, &plane)) {
        TopoDS_Shape shape1 = static_cast<TopoShapeEdgePy*>(edge1)->getTopoShapePtr()->getShape();
        TopoDS_Shape shape2 = static_cast<TopoShapeEdgePy*>(edge2)->getTopoShapePtr()->getShape();
        Handle(Geom_Plane) hPlane = Handle(Geom_Plane)::DownCast(static_cast<PlanePy*>(plane)->getGeomPlanePtr()->handle());
        getChFi2d_AnaFilletAlgoPtr()->Init(TopoDS::Edge(shape1), TopoDS::Edge(shape2), hPlane->Pln());
        return 0;
    }

    PyErr_SetString(PyExc_TypeError, "Wrong arguments:\n"
                                     "-- AnaFilletAlgo()\n"
                                     "-- AnaFilletAlgo(wire, plane)"
                                     "-- AnaFilletAlgo(edge, edge, plane)\n");
    return -1;
}

// returns a string which represents the object e.g. when printed in python
std::string ChFi2d_AnaFilletAlgoPy::representation() const
{
    return std::string("<AnaFilletAlgo object>");
}

PyObject* ChFi2d_AnaFilletAlgoPy::init(PyObject *args)
{
    PyObject* wire;
    PyObject* plane;
    if (PyArg_ParseTuple(args, "O!O!", &TopoShapeWirePy::Type, &wire, &PlanePy::Type, &plane)) {
        TopoDS_Shape shape = static_cast<TopoShapeWirePy*>(wire)->getTopoShapePtr()->getShape();
        Handle(Geom_Plane) hPlane = Handle(Geom_Plane)::DownCast(static_cast<PlanePy*>(plane)->getGeomPlanePtr()->handle());
        getChFi2d_AnaFilletAlgoPtr()->Init(TopoDS::Wire(shape), hPlane->Pln());
        Py_Return;
    }

    PyErr_Clear();
    PyObject* edge1;
    PyObject* edge2;
    if (PyArg_ParseTuple(args, "O!O!O!", &TopoShapeEdgePy::Type, &edge1,
                                         &TopoShapeEdgePy::Type, &edge2,
                                         &PlanePy::Type, &plane)) {
        TopoDS_Shape shape1 = static_cast<TopoShapeEdgePy*>(edge1)->getTopoShapePtr()->getShape();
        TopoDS_Shape shape2 = static_cast<TopoShapeEdgePy*>(edge2)->getTopoShapePtr()->getShape();
        Handle(Geom_Plane) hPlane = Handle(Geom_Plane)::DownCast(static_cast<PlanePy*>(plane)->getGeomPlanePtr()->handle());
        getChFi2d_AnaFilletAlgoPtr()->Init(TopoDS::Edge(shape1), TopoDS::Edge(shape2), hPlane->Pln());
        Py_Return;
    }

    PyErr_SetString(PyExc_TypeError, "Wrong arguments:\n"
                                     "-- init(wire, plane)"
                                     "-- init(edge, edge, plane)\n");
    return nullptr;
}

PyObject* ChFi2d_AnaFilletAlgoPy::perform(PyObject *args)
{
    double radius;
    if (!PyArg_ParseTuple(args, "d", &radius))
        return nullptr;

    try {
        bool ok = getChFi2d_AnaFilletAlgoPtr()->Perform(radius);
        return Py::new_reference_to(Py::Boolean(ok));
    }
    catch (Standard_Failure& e) {
        PyErr_SetString(Base::PyExc_FC_CADKernelError, e.GetMessageString());
        return nullptr;
    }
}

PyObject* ChFi2d_AnaFilletAlgoPy::result(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    try {
        TopoDS_Edge theEdge1, theEdge2;
        TopoDS_Shape res_edge = getChFi2d_AnaFilletAlgoPtr()->Result(theEdge1, theEdge2);

        Py::TupleN tuple(Py::asObject(TopoShape(res_edge).getPyObject()),
                         Py::asObject(TopoShape(theEdge1).getPyObject()),
                         Py::asObject(TopoShape(theEdge2).getPyObject()));
        return Py::new_reference_to(tuple);
    }
    catch (Standard_Failure& e) {
        PyErr_SetString(Base::PyExc_FC_CADKernelError, e.GetMessageString());
        return nullptr;
    }
}

PyObject *ChFi2d_AnaFilletAlgoPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int ChFi2d_AnaFilletAlgoPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
