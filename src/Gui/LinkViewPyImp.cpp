/****************************************************************************
 *   Copyright (c) 2017 Zheng Lei (realthunder) <realthunder.dev@gmail.com> *
 *                                                                          *
 *   This file is part of the LabRPS CAx development system.               *
 *                                                                          *
 *   This library is free software; you can redistribute it and/or          *
 *   modify it under the terms of the GNU Library General Public            *
 *   License as published by the Free Software Foundation; either           *
 *   version 2 of the License, or (at your option) any later version.       *
 *                                                                          *
 *   This library  is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Library General Public License for more details.                   *
 *                                                                          *
 *   You should have received a copy of the GNU Library General Public      *
 *   License along with this library; see the file COPYING.LIB. If not,     *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,          *
 *   Suite 330, Boston, MA  02111-1307, USA                                 *
 *                                                                          *
 ****************************************************************************/

#include "PreCompiled.h"

#include <App/DocumentObjectPy.h>

#include "LinkViewPy.h"
#include "LinkViewPy.cpp"
#include "ViewProviderDocumentObjectPy.h"


using namespace Gui;

PyObject *LinkViewPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    return new LinkViewPy(new LinkView);
}

int LinkViewPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}


// returns a string which represent the object e.g. when printed in python
std::string LinkViewPy::representation() const
{
    return "<Link view>";
}

PyObject* LinkViewPy::reset(PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    PY_TRY {
        auto lv = getLinkViewPtr();
        lv->setSize(0);
        lv->setLink(nullptr);
        Py_Return;
    } PY_CATCH;
}

PyObject* LinkViewPy::setType(PyObject *args) {
    short type;
    PyObject *sublink = Py_True;
    if (!PyArg_ParseTuple(args, "h|O", &type,&sublink))
        return nullptr;

    PY_TRY{
        getLinkViewPtr()->setNodeType((LinkView::SnapshotType)type,PyObject_IsTrue(sublink));
        Py_Return;
    } PY_CATCH;
}

PyObject*  LinkViewPy::setChildren(PyObject *args) {
    PyObject *pyObj;
    PyObject *pyVis = Py_None;
    short type=0;
    if (!PyArg_ParseTuple(args, "O|Os",&pyObj,&pyVis,&type))
        return nullptr;

    PY_TRY{
        App::PropertyBoolList vis;
        App::PropertyLinkList links;
        if(pyObj!=Py_None)
            links.setPyObject(pyObj);
        if(pyVis!=Py_None)
            vis.setPyObject(pyVis);
        getLinkViewPtr()->setChildren(links.getValue(),vis.getValue(),(LinkView::SnapshotType)type);
        Py_Return;
    } PY_CATCH;
}

PyObject*  LinkViewPy::setLink(PyObject *args)
{
    PyObject *pyObj;
    PyObject *pySubName = Py_None;
    if (!PyArg_ParseTuple(args, "O|O",&pyObj,&pySubName))
        return nullptr;

    PY_TRY {
        ViewProviderDocumentObject *vpd = nullptr;
        App::DocumentObject *obj = nullptr;
        if(pyObj!=Py_None) {
            if(PyObject_TypeCheck(pyObj,&App::DocumentObjectPy::Type))
                obj = static_cast<App::DocumentObjectPy*>(pyObj)->getDocumentObjectPtr();
            else if(PyObject_TypeCheck(pyObj,&ViewProviderDocumentObjectPy::Type))
                vpd = static_cast<ViewProviderDocumentObjectPy*>(pyObj)->getViewProviderDocumentObjectPtr();
            else {
                PyErr_SetString(PyExc_TypeError,
                        "exepcting a type of DocumentObject or ViewProviderDocumentObject");
                return nullptr;
            }
        }

        // Too lazy to parse the argument...
        App::PropertyStringList prop;
        if(pySubName!=Py_None)
            prop.setPyObject(pySubName);

        if(obj)
            getLinkViewPtr()->setLink(obj,prop.getValue());
        else
            getLinkViewPtr()->setLinkViewObject(vpd,prop.getValue());
        Py_Return;
    } PY_CATCH;
}

Py::Object LinkViewPy::getOwner() const {
    auto owner = getLinkViewPtr()->getOwner();
    if(!owner)
        return Py::Object();
    return Py::Object(owner->getPyObject(),true);
}

void LinkViewPy::setOwner(Py::Object owner) {
    ViewProviderDocumentObject *vp = nullptr;
    if(!owner.isNone()) {
        if(!PyObject_TypeCheck(owner.ptr(),&ViewProviderDocumentObjectPy::Type))
            throw Py::TypeError("exepcting the owner to be of ViewProviderDocumentObject");
        vp = static_cast<ViewProviderDocumentObjectPy*>(
                owner.ptr())->getViewProviderDocumentObjectPtr();
    }
    getLinkViewPtr()->setOwner(vp);
}

Py::Object LinkViewPy::getLinkedView() const {
    auto linked = getLinkViewPtr()->getLinkedView();
    if(!linked)
        return Py::Object();
    return Py::Object(linked->getPyObject(),true);
}

Py::Object LinkViewPy::getSubNames() const {
    const auto &subs = getLinkViewPtr()->getSubNames();
    if(subs.empty())
        return Py::Object();
    Py::Tuple ret(subs.size());
    int i=0;
    for(auto &s : subs)
        ret.setItem(i++,Py::String(s.c_str()));
    return ret;
}

PyObject *LinkViewPy::getCustomAttributes(const char*) const
{
    return nullptr;
}

int LinkViewPy::setCustomAttributes(const char*, PyObject*)
{
    return 0;
}

Py::Object LinkViewPy::getVisibilities() const {
    auto linked = getLinkViewPtr();
    if(!linked->getSize())
        return Py::Object();
    Py::Tuple ret(linked->getSize());
    for(int i=0;i<linked->getSize();++i)
        ret.setItem(i,Py::Boolean(linked->isElementVisible(i)));
    return ret;
}

void LinkViewPy::setVisibilities(Py::Object value) {
    App::PropertyBoolList v;
    if(!value.isNone())
        v.setPyObject(value.ptr());

    auto linked = getLinkViewPtr();
    const auto &vis = v.getValue();
    for(int i=0;i<linked->getSize();++i)
        linked->setElementVisible(i,i>=(int)vis.size()||vis[i]);
}

PyObject* LinkViewPy::getChildren(PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    auto children = getLinkViewPtr()->getChildren();
    if(children.empty())
        Py_Return;
    Py::Tuple ret(children.size());
    int i=0;
    for(auto vp : children)
        ret.setItem(i++,Py::Object(vp->getPyObject(),true));
    return Py::new_reference_to(ret);
}

Py::Int LinkViewPy::getCount() const {
    return Py::Int(getLinkViewPtr()->getSize());
}

void LinkViewPy::setCount(Py::Int count) {
    try {
        getLinkViewPtr()->setSize((int)count);
    } catch (const Base::Exception& e) {
        throw Py::RuntimeError(e.what());
    }
}

