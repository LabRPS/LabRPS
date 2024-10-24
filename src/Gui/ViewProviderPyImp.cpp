/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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
# include <QByteArray>
# include <QDataStream>
#endif

#include "PythonWrapper.h"

// inclusion of the generated files (generated out of ViewProviderPy.xml)
#include <Gui/ViewProviderPy.h>
#include <Gui/ViewProviderPy.cpp>
#include <Base/Interpreter.h>
#include <App/Document.h>
#include <App/DocumentObject.h>
#include <App/DocumentObjectPy.h>


using namespace Gui;

// returns a string which represent the object e.g. when printed in python
std::string ViewProviderPy::representation() const
{
    return "<View provider object>";
}

PyObject*  ViewProviderPy::addProperty(PyObject *args)
{
    char *sType,*sName=nullptr,*sGroup=nullptr,*sDoc=nullptr;
    short attr=0;
    std::string sDocStr;
    PyObject *ro = Py_False, *hd = Py_False;
    if (!PyArg_ParseTuple(args, "s|ssethO!O!", &sType,&sName,&sGroup,"utf-8",&sDoc,&attr,
        &PyBool_Type, &ro, &PyBool_Type, &hd))
        return nullptr;

    if (sDoc) {
        sDocStr = sDoc;
        PyMem_Free(sDoc);
    }

    App::Property* prop=nullptr;
    try {
        prop = getViewProviderPtr()->addDynamicProperty(sType,sName,sGroup,sDocStr.c_str(),attr,
            PyObject_IsTrue(ro) ? true : false, PyObject_IsTrue(hd) ? true : false);
    }
    catch (const Base::Exception& e) {
        throw Py::RuntimeError(e.what());
    }
    if (!prop) {
        std::stringstream str;
        str << "No property found of type '" << sType << "'" << std::ends;
        throw Py::TypeError(str.str());
    }

    return Py::new_reference_to(this);
}

PyObject*  ViewProviderPy::removeProperty(PyObject *args)
{
    char *sName;
    if (!PyArg_ParseTuple(args, "s", &sName))
        return nullptr;

    try {
        bool ok = getViewProviderPtr()->removeDynamicProperty(sName);
        return Py_BuildValue("O", (ok ? Py_True : Py_False));
    }
    catch (const Base::Exception& e) {
        throw Py::RuntimeError(e.what());
    }
}

PyObject*  ViewProviderPy::supportedProperties(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    std::vector<Base::Type> ary;
    Base::Type::getAllDerivedFrom(App::Property::getClassTypeId(), ary);
    Py::List res;
    for (std::vector<Base::Type>::iterator it = ary.begin(); it != ary.end(); ++it) {
        Base::BaseClass *data = static_cast<Base::BaseClass*>(it->createInstance());
        if (data) {
            delete data;
            res.append(Py::String(it->getName()));
        }
    }
    return Py::new_reference_to(res);
}

PyObject*  ViewProviderPy::show(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    PY_TRY {
        getViewProviderPtr()->show();
        Py_Return;
    }
    PY_CATCH;
}

PyObject*  ViewProviderPy::hide(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    PY_TRY {
        getViewProviderPtr()->hide();
        Py_Return;
    }
    PY_CATCH;
}

PyObject*  ViewProviderPy::isVisible(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    PY_TRY {
        return Py::new_reference_to(Py::Boolean(getViewProviderPtr()->isShow()));
    }
    PY_CATCH;
}

PyObject*  ViewProviderPy::canDragObject(PyObject *args)
{
    PyObject *obj = Py_None;
    if (!PyArg_ParseTuple(args, "|O", &obj))
        return nullptr;

    PY_TRY {
        bool ret;
        if (obj == Py_None) {
            ret = getViewProviderPtr()->canDragObjects();
        }
        else {
            if (!PyObject_TypeCheck(obj, &App::DocumentObjectPy::Type)) {
                PyErr_SetString(PyExc_TypeError, "'obj' must be a App::DocumentObject or None");
                return nullptr;
            }
            ret = getViewProviderPtr()->canDragObject(
                    static_cast<App::DocumentObjectPy*>(obj)->getDocumentObjectPtr());
        }

        return Py::new_reference_to(Py::Boolean(ret));
    }
    PY_CATCH;
}

PyObject*  ViewProviderPy::canDropObject(PyObject *args, PyObject *kw)
{
    PyObject *obj = Py_None;
    PyObject *owner = Py_None;
    PyObject *pyElements = Py_None;
    const char *subname = nullptr;
    static char* kwlist[] = {"obj","owner","subname","elem",nullptr};
    if (!PyArg_ParseTupleAndKeywords(args, kw, "|OOsO", kwlist, &obj, &owner, &subname, &pyElements))
        return nullptr;

    PY_TRY {
        bool ret;
        App::DocumentObject* pcObject;
        App::DocumentObject* pcOwner = nullptr;
        App::PropertyStringList elements;
        if (obj == Py_None && (owner != Py_None || pyElements != Py_None || subname)) {
            PyErr_SetString(PyExc_ValueError, "'obj' must be specified if 'owner', 'subname' or 'elem' is given");
            return nullptr;
        }
        if(obj == Py_None) {
            ret = getViewProviderPtr()->canDropObjects();
            return Py::new_reference_to(Py::Boolean(ret));
        }
        else {
            if (!PyObject_TypeCheck(obj, &App::DocumentObjectPy::Type)) {
                PyErr_SetString(PyExc_TypeError, "'obj' must be a App::DocumentObject or None");
                return nullptr;
            }
            pcObject = static_cast<App::DocumentObjectPy*>(obj)->getDocumentObjectPtr();
        }

        if (owner != Py_None) {
            if (!PyObject_TypeCheck(owner, &App::DocumentObjectPy::Type)) {
                PyErr_SetString(PyExc_TypeError, "'owner' must be a App::DocumentObject or None");
                return nullptr;
            }
            pcOwner = static_cast<App::DocumentObjectPy*>(owner)->getDocumentObjectPtr();
        }
        if (pyElements != Py_None) {
            try {
                elements.setPyObject(pyElements);
            }
            catch(...) {
                PyErr_SetString(PyExc_TypeError, "'elem' must be a sequence of strings");
                return nullptr;
            }
        }
        ret = getViewProviderPtr()->canDropObjectEx(pcObject,pcOwner,subname,elements.getValues());
        return Py::new_reference_to(Py::Boolean(ret));
    }
    PY_CATCH;
}

PyObject*  ViewProviderPy::canDragAndDropObject(PyObject *args)
{
    PyObject *obj;
    if (!PyArg_ParseTuple(args, "O!", &App::DocumentObjectPy::Type,&obj))
        return nullptr;

    PY_TRY {
        bool ret = getViewProviderPtr()->canDragAndDropObject(
                    static_cast<App::DocumentObjectPy*>(obj)->getDocumentObjectPtr());
        return Py::new_reference_to(Py::Boolean(ret));
    }
    PY_CATCH;
}

PyObject*  ViewProviderPy::dropObject(PyObject *args, PyObject *kw)
{
    PyObject *obj;
    PyObject *owner = Py_None;
    PyObject *pyElements = Py_None;
    const char *subname = nullptr;
    static char* kwlist[] = {"obj","owner","subname","elem",nullptr};
    if (!PyArg_ParseTupleAndKeywords(args, kw, "O!|OsO", kwlist,
            &App::DocumentObjectPy::Type, &obj, &owner, &subname, &pyElements))
        return nullptr;

    PY_TRY {
        auto pcObject = static_cast<App::DocumentObjectPy*>(obj)->getDocumentObjectPtr();
        App::DocumentObject *pcOwner = nullptr;
        App::PropertyStringList elements;
        if (owner != Py_None) {
            if (!PyObject_TypeCheck(owner, &App::DocumentObjectPy::Type)) {
                PyErr_SetString(PyExc_TypeError, "'owner' must be a App::DocumentObject or None");
                return nullptr;
            }
            pcOwner = static_cast<App::DocumentObjectPy*>(owner)->getDocumentObjectPtr();
        }

        if (pyElements != Py_None) {
            try {
                elements.setPyObject(pyElements);
            }
            catch(...) {
                PyErr_SetString(PyExc_TypeError, "'elem' must be a sequence of strings");
                return nullptr;
            }
        }
        auto ret = getViewProviderPtr()->dropObjectEx(pcObject,pcOwner, subname,elements.getValues());
        return Py::new_reference_to(Py::String(ret));
    }
    PY_CATCH;
}

PyObject*  ViewProviderPy::dragObject(PyObject *args)
{
    PyObject *obj;
    if (!PyArg_ParseTuple(args, "O!", &App::DocumentObjectPy::Type,&obj))
        return nullptr;

    PY_TRY {
        getViewProviderPtr()->dragObject(
                static_cast<App::DocumentObjectPy*>(obj)->getDocumentObjectPtr());
        Py_Return;
    }
    PY_CATCH;
}

PyObject* ViewProviderPy::replaceObject(PyObject *args)
{
    PyObject *oldObj;
    PyObject *newObj;
    if (!PyArg_ParseTuple(args, "O!O!",
                &App::DocumentObjectPy::Type,&oldObj,
                &App::DocumentObjectPy::Type,&newObj))
        return nullptr;

    PY_TRY {
        int ret = getViewProviderPtr()->replaceObject(
                static_cast<App::DocumentObjectPy*>(oldObj)->getDocumentObjectPtr(),
                static_cast<App::DocumentObjectPy*>(newObj)->getDocumentObjectPtr());
        return Py::new_reference_to(Py::Int(ret));
    }
    PY_CATCH;
}

PyObject*  ViewProviderPy::toString(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    PY_TRY {
        std::string buffer = getViewProviderPtr()->toString();
        return Py::new_reference_to(Py::String(buffer));
    }
    PY_CATCH;
}

PyObject* ViewProviderPy::claimChildren(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    std::vector<App::DocumentObject*> children = this->getViewProviderPtr()->claimChildren();
    Py::List ret;
    for(App::DocumentObject* child: children){
        if (child)
            ret.append(Py::asObject(child->getPyObject()));
        else
            ret.append(Py::None());
    }
    return Py::new_reference_to(ret);
}

PyObject *ViewProviderPy::signalChangeIcon(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    getViewProviderPtr()->signalChangeIcon();
    Py_Return;
}

PyObject *ViewProviderPy::doubleClicked(PyObject *args) {
    if(!PyArg_ParseTuple(args, ""))
        return nullptr;

    PY_TRY {
        return Py::new_reference_to(Py::Boolean(getViewProviderPtr()->doubleClicked()));
    }
    PY_CATCH;
}

PyObject *ViewProviderPy::getCustomAttributes(const char* attr) const
{
    // search for dynamic property
    App::Property* prop = getViewProviderPtr()->getDynamicPropertyByName(attr);
    if (prop)
        return prop->getPyObject();
    else
        return nullptr;
}

int ViewProviderPy::setCustomAttributes(const char* attr, PyObject* value)
{
    // search for dynamic property
    try {
        App::Property* prop = getViewProviderPtr()->getDynamicPropertyByName(attr);
        if (prop) {
            prop->setPyObject(value);
            return 1;
        }
        return 0;
    }
    catch (Base::Exception &exc) {
        PyErr_Format(PyExc_AttributeError, "Attribute (Name: %s) error: '%s' ", attr, exc.what());
        return -1;
    }
    catch (...) {
        PyErr_Format(PyExc_AttributeError, "Unknown error in attribute %s", attr);
        return -1;
    }
}


Py::Object ViewProviderPy::getIcon() const
{
#if 0
    QByteArray ba;
    QDataStream str(&ba, QIODevice::WriteOnly);
    QIcon icon = getViewProviderPtr()->getIcon();
    str << icon;
    return Py::String(ba.constData(), ba.size());
#else
    PythonWrapper wrap;
    wrap.loadGuiModule();
    wrap.loadWidgetsModule();
    QIcon icon = getViewProviderPtr()->getIcon();
    return wrap.fromQIcon(new QIcon(icon));
#endif
}


Py::Boolean ViewProviderPy::getCanRemoveChildrenFromRoot() const
{
    return Py::Boolean(getViewProviderPtr()->canRemoveChildrenFromRoot());
}

Py::Boolean ViewProviderPy::getLinkVisibility() const
{
    return Py::Boolean(getViewProviderPtr()->isLinkVisible());
}

void ViewProviderPy::setLinkVisibility(Py::Boolean arg)
{
    getViewProviderPtr()->setLinkVisible(arg);
}

Py::String ViewProviderPy::getDropPrefix() const
{
    return Py::String(getViewProviderPtr()->getDropPrefix());
}
