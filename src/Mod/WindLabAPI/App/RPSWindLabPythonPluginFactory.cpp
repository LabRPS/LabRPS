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
#ifndef _PreComp_
# include <QApplication>
#endif
#include "RPSWindLabPythonPluginFactory.h"
#include <Base/PyObjectBase.h>
#include "RPSWindLabAPI.h"
#include <Base/Console.h>
#include <Base/TypePy.h>
#include <Eigen/Core>

//#include <boost_python.hpp>
////#include <boost/python/numpy.hpp>
//#include <boost/python/class.hpp>
//#include <boost/python/wrapper.hpp>
//#include <boost/python/call.hpp>
//
////#define BOOST_LIB_NAME "boost_numpy"
//#include <boost/config/auto_link.hpp>
//#include <boost/config.hpp>
//
//#include <pybind11/pybind11.h>
//#include <pybind11/stl.h>
////#include <pybind11/numpy.h>
//#include <string.h>


//namespace py = pybind11;

using namespace WindLabAPI;
//namespace p = boost::python;
//namespace np = boost::python::numpy;

namespace WindLabAPI
{

// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsLocationDistributionFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsLocationDistributionFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listLocationDistributionAuthors: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionToBeInstalledFeature(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionToBeInstalledFeature(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionToBeInstalledFeature(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listLocationDistributionToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionFeatureDescription(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsLocationDistributionFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionFeatureDescription(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsLocationDistributionFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionFeatureDescription(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listLocationDistributionFeatureDescription: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveLocationDistributionFeatureDescription(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsLocationDistributionFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionPlugin(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsLocationDistributionFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionPlugin(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsLocationDistributionFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionPlugin(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listLocationDistributionPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveLocationDistributionPlugin(PyObject* self,
                                                                            PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsLocationDistributionFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionTitle(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsLocationDistributionFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionTitle(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsLocationDistributionFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionTitle(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listLocationDistributionTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionLink(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsLocationDistributionFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionLink(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsLocationDistributionFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionLink(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listLocationDistributionLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionDate(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsLocationDistributionFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionDate(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsLocationDistributionFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionDate(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listLocationDistributionDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionVersion(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsLocationDistributionFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionVersion(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsLocationDistributionFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionVersion(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listLocationDistributionVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionFeatureSkipDuringUnintallation(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionFeatureSkipDuringUnintallation(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionFeatureSkipDuringUnintallation(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listLocationDistributionFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddLocationDistributionProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

    WindLabAPI::CrpsLocationDistributionFactory::GetProducerMap()[name] = producer;
    Py_INCREF(producer);
    Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetLocationDistributionProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsLocationDistributionFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListLocationDistributionProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsLocationDistributionFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listLocationDistributionProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveLocationDistributionProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {
        
        WindLabAPI::CrpsLocationDistributionFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceLocationDistribution(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsLocationDistributionFactory::produceFeature(newFeatureName, simulationName, pluggedFeatureName);    
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Mean wind profile---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMeanAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMeanFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMeanFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listMeanAuthors: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddMeanToBeInstalledFeature(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMeanFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanToBeInstalledFeature(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMeanFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanToBeInstalledFeature(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listMeanToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddMeanFeatureDescription(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMeanFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanFeatureDescription(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMeanFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanFeatureDescription(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listMeanFeatureDescription: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveMeanFeatureDescription(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsMeanFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddMeanPlugin(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMeanFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanPlugin(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMeanFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanPlugin(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMeanPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveMeanPlugin(PyObject* self,
                                                                            PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsMeanFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddMeanTitle(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMeanFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanTitle(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMeanFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanTitle(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMeanTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMeanLink(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMeanFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanLink(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMeanFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanLink(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMeanLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMeanDate(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMeanFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanDate(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMeanFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanDate(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMeanDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMeanVersion(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMeanFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanVersion(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMeanFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanVersion(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMeanVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMeanFeatureSkipDuringUnintallation(PyObject* self,
                                                                       PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanFeatureSkipDuringUnintallation(PyObject* self,
                                                                       PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanFeatureSkipDuringUnintallation(PyObject* self,
                                                                        PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMeanFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMeanProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

    WindLabAPI::CrpsMeanFactory::GetProducerMap()[name] = producer;
    Py_INCREF(producer);
    Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetMeanProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsMeanFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMeanProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMeanFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMeanProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveMeanProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {
        
        WindLabAPI::CrpsMeanFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceMean(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsMeanFactory::produceFeature(newFeatureName, simulationName, pluggedFeatureName);    
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Coherence---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCoherenceAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCoherenceFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherenceAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCoherenceFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherenceAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCoherenceAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddCoherenceToBeInstalledFeature(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCoherenceFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherenceToBeInstalledFeature(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCoherenceFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherenceToBeInstalledFeature(PyObject* self,
                                                                      PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCoherenceToBeInstalledFeatures: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddCoherenceFeatureDescription(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCoherenceFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherenceFeatureDescription(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCoherenceFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherenceFeatureDescription(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCoherenceFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveCoherenceFeatureDescription(PyObject* self,
                                                                      PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsCoherenceFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddCoherencePlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCoherenceFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherencePlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCoherenceFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherencePlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCoherencePlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveCoherencePlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsCoherenceFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddCoherenceTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCoherenceFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherenceTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCoherenceFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherenceTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCoherenceTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCoherenceLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCoherenceFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherenceLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCoherenceFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherenceLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCoherenceLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCoherenceDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCoherenceFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherenceDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCoherenceFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherenceDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCoherenceDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCoherenceVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCoherenceFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherenceVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCoherenceFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherenceVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCoherenceVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCoherenceFeatureSkipDuringUnintallation(PyObject* self,
                                                                               PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherenceFeatureSkipDuringUnintallation(PyObject* self,
                                                                               PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherenceFeatureSkipDuringUnintallation(PyObject* self,
                                                                                PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listCoherenceFeatureSkipDuringUnintallations: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCoherenceProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsCoherenceFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetCoherenceProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsCoherenceFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCoherenceProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCoherenceFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCoherenceProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveCoherenceProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsCoherenceFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceCoherence(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsCoherenceFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------Along wind spectrum---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsXSpectrumFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsXSpectrumFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listXSpectrumAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsXSpectrumFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsXSpectrumFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumToBeInstalledFeature(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listXSpectrumToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsXSpectrumFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsXSpectrumFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumFeatureDescription(PyObject* self,
                                                                         PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listXSpectrumFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveXSpectrumFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsXSpectrumFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsXSpectrumFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsXSpectrumFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listXSpectrumPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveXSpectrumPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsXSpectrumFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsXSpectrumFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsXSpectrumFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listXSpectrumTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsXSpectrumFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsXSpectrumFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listXSpectrumLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsXSpectrumFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsXSpectrumFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listXSpectrumDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsXSpectrumFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsXSpectrumFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listXSpectrumVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumFeatureSkipDuringUnintallation(PyObject* self,
                                                                                     PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listXSpectrumFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddXSpectrumProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsXSpectrumFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetXSpectrumProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsXSpectrumFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListXSpectrumProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsXSpectrumFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listXSpectrumProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveXSpectrumProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsXSpectrumFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceXSpectrum(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsXSpectrumFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------Vertical wind spectrum---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsZSpectrumFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsZSpectrumFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listZSpectrumAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsZSpectrumFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsZSpectrumFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumToBeInstalledFeature(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listZSpectrumToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsZSpectrumFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsZSpectrumFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumFeatureDescription(PyObject* self,
                                                                         PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listZSpectrumFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveZSpectrumFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsZSpectrumFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsZSpectrumFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsZSpectrumFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listZSpectrumPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveZSpectrumPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsZSpectrumFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsZSpectrumFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsZSpectrumFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listZSpectrumTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsZSpectrumFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsZSpectrumFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listZSpectrumLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsZSpectrumFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsZSpectrumFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listZSpectrumDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsZSpectrumFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsZSpectrumFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listZSpectrumVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumFeatureSkipDuringUnintallation(PyObject* self,
                                                                                     PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listZSpectrumFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddZSpectrumProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsZSpectrumFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetZSpectrumProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsZSpectrumFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListZSpectrumProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsZSpectrumFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listZSpectrumProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveZSpectrumProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsZSpectrumFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceZSpectrum(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsZSpectrumFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Across wind spectrum---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsYSpectrumFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsYSpectrumFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listYSpectrumAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsYSpectrumFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsYSpectrumFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumToBeInstalledFeature(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listYSpectrumToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsYSpectrumFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsYSpectrumFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumFeatureDescription(PyObject* self,
                                                                         PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listYSpectrumFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveYSpectrumFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsYSpectrumFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsYSpectrumFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsYSpectrumFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listYSpectrumPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveYSpectrumPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsYSpectrumFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsYSpectrumFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsYSpectrumFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listYSpectrumTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsYSpectrumFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsYSpectrumFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listYSpectrumLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsYSpectrumFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsYSpectrumFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listYSpectrumDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsYSpectrumFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsYSpectrumFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listYSpectrumVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumFeatureSkipDuringUnintallation(PyObject* self,
                                                                                     PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listYSpectrumFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddYSpectrumProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsYSpectrumFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetYSpectrumProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsYSpectrumFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListYSpectrumProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsYSpectrumFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listYSpectrumProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveYSpectrumProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsYSpectrumFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceYSpectrum(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsYSpectrumFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------simulation method---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSimuMethodFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSimuMethodFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSimuMethodAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodToBeInstalledFeature(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listSimuMethodToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSimuMethodFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSimuMethodFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodFeatureDescription(PyObject* self,
                                                                         PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSimuMethodFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveSimuMethodFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsSimuMethodFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSimuMethodFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSimuMethodFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSimuMethodPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveSimuMethodPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsSimuMethodFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSimuMethodFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSimuMethodFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSimuMethodTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSimuMethodFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSimuMethodFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSimuMethodLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSimuMethodFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSimuMethodFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSimuMethodDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSimuMethodFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSimuMethodFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSimuMethodVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodFeatureSkipDuringUnintallation(PyObject* self,
                                                                                     PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listSimuMethodFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSimuMethodProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsSimuMethodFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetSimuMethodProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsSimuMethodFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSimuMethodProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSimuMethodFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSimuMethodProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveSimuMethodProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsSimuMethodFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceSimuMethod(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsSimuMethodFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------Frequency distribution---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsFrequencyDistributionFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsFrequencyDistributionFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listFrequencyDistributionAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionToBeInstalledFeature(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listFrequencyDistributionToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionFeatureDescription(PyObject* self,
                                                                         PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listFrequencyDistributionFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveFrequencyDistributionFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listFrequencyDistributionPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveFrequencyDistributionPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsFrequencyDistributionFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsFrequencyDistributionFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listFrequencyDistributionTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsFrequencyDistributionFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsFrequencyDistributionFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listFrequencyDistributionLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsFrequencyDistributionFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsFrequencyDistributionFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listFrequencyDistributionDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsFrequencyDistributionFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsFrequencyDistributionFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listFrequencyDistributionVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionFeatureSkipDuringUnintallation(PyObject* self,
                                                                                     PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listFrequencyDistributionFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddFrequencyDistributionProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsFrequencyDistributionFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetFrequencyDistributionProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsFrequencyDistributionFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListFrequencyDistributionProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsFrequencyDistributionFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listFrequencyDistributionProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveFrequencyDistributionProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsFrequencyDistributionFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceFrequencyDistribution(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsFrequencyDistributionFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------Randomness---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRandomnessFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRandomnessFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRandomnessAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRandomnessFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRandomnessFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessToBeInstalledFeature(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listRandomnessToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRandomnessFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRandomnessFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessFeatureDescription(PyObject* self,
                                                                         PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRandomnessFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveRandomnessFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsRandomnessFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRandomnessFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRandomnessFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRandomnessPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveRandomnessPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsRandomnessFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRandomnessFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRandomnessFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRandomnessTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRandomnessFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRandomnessFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRandomnessLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRandomnessFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRandomnessFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRandomnessDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRandomnessFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRandomnessFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRandomnessVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessFeatureSkipDuringUnintallation(PyObject* self,
                                                                                     PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listRandomnessFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRandomnessProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsRandomnessFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetRandomnessProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsRandomnessFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRandomnessProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRandomnessFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRandomnessProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveRandomnessProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsRandomnessFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceRandomness(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsRandomnessFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------PSD decomposition method---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPSDdecomMethodFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPSDdecomMethodFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPSDdecomMethodAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodToBeInstalledFeature(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listPSDdecomMethodToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodFeatureDescription(PyObject* self,
                                                                         PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPSDdecomMethodFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemovePSDdecomMethodFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPSDdecomMethodPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemovePSDdecomMethodPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPSDdecomMethodFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPSDdecomMethodFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPSDdecomMethodTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPSDdecomMethodFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPSDdecomMethodFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPSDdecomMethodLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPSDdecomMethodFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPSDdecomMethodFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPSDdecomMethodDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPSDdecomMethodFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPSDdecomMethodFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPSDdecomMethodVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodFeatureSkipDuringUnintallation(PyObject* self,
                                                                                     PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listPSDdecomMethodFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPSDdecomMethodProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsPSDdecomMethodFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetPSDdecomMethodProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsPSDdecomMethodFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPSDdecomMethodProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPSDdecomMethodFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPSDdecomMethodProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemovePSDdecomMethodProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsPSDdecomMethodFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProducePSDdecomMethod(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsPSDdecomMethodFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Correlation---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCorrelationFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCorrelationFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCorrelationAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCorrelationFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationToBeInstalledFeature(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCorrelationFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationToBeInstalledFeature(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listCorrelationToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCorrelationFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationFeatureDescription(PyObject* self,
                                                                        PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCorrelationFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationFeatureDescription(PyObject* self,
                                                                         PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCorrelationFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveCorrelationFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsCorrelationFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCorrelationFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCorrelationFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCorrelationPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveCorrelationPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsCorrelationFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCorrelationFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCorrelationFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCorrelationTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCorrelationFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCorrelationFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCorrelationLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCorrelationFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCorrelationFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCorrelationDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCorrelationFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCorrelationFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCorrelationVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCorrelationFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationFeatureSkipDuringUnintallation(PyObject* self,
                                                                                    PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCorrelationFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationFeatureSkipDuringUnintallation(PyObject* self,
                                                                                     PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listCorrelationFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCorrelationProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsCorrelationFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetCorrelationProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsCorrelationFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCorrelationProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCorrelationFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCorrelationProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveCorrelationProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsCorrelationFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceCorrelation(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsCorrelationFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Modulation---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddModulationAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsModulationFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetModulationAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsModulationFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListModulationAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listModulationAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddModulationToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsModulationFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetModulationToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsModulationFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListModulationToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listModulationToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddModulationFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsModulationFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetModulationFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsModulationFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListModulationFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listModulationFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveModulationFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsModulationFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddModulationPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsModulationFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetModulationPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsModulationFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListModulationPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listModulationPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveModulationPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsModulationFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddModulationTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsModulationFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetModulationTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsModulationFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListModulationTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listModulationTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddModulationLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsModulationFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetModulationLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsModulationFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListModulationLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listModulationLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddModulationDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsModulationFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetModulationDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsModulationFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListModulationDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listModulationDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddModulationVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsModulationFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetModulationVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsModulationFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListModulationVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listModulationVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddModulationFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetModulationFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListModulationFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listModulationFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddModulationProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsModulationFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetModulationProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsModulationFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListModulationProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsModulationFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listModulationProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveModulationProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsModulationFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceModulation(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsModulationFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Table tool---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTableToolAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTableToolFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTableToolAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTableToolFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTableToolAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTableToolAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddTableToolToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTableToolFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTableToolToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTableToolFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTableToolToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listTableToolToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddTableToolFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTableToolFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTableToolFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTableToolFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTableToolFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTableToolFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveTableToolFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsTableToolFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddTableToolPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTableToolFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTableToolPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTableToolFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTableToolPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTableToolPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveTableToolPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsTableToolFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddTableToolTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTableToolFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTableToolTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTableToolFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTableToolTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTableToolTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTableToolLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTableToolFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTableToolLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTableToolFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTableToolLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTableToolLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTableToolDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTableToolFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTableToolDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTableToolFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTableToolDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTableToolDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTableToolVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTableToolFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTableToolVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTableToolFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTableToolVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTableToolVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddTableToolFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetTableToolFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListTableToolFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listTableToolFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTableToolProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsTableToolFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetTableToolProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsTableToolFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTableToolProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTableToolFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTableToolProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveTableToolProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsTableToolFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceTableTool(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsTableToolFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Matrix tool---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMatrixToolAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMatrixToolFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMatrixToolAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMatrixToolFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMatrixToolAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMatrixToolAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddMatrixToolToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMatrixToolFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMatrixToolToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMatrixToolFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMatrixToolToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listMatrixToolToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddMatrixToolFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMatrixToolFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMatrixToolFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMatrixToolFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMatrixToolFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMatrixToolFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveMatrixToolFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsMatrixToolFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddMatrixToolPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMatrixToolFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMatrixToolPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMatrixToolFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMatrixToolPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMatrixToolPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveMatrixToolPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsMatrixToolFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddMatrixToolTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMatrixToolFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMatrixToolTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMatrixToolFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMatrixToolTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMatrixToolTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMatrixToolLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMatrixToolFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMatrixToolLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMatrixToolFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMatrixToolLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMatrixToolLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMatrixToolDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMatrixToolFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMatrixToolDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMatrixToolFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMatrixToolDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMatrixToolDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMatrixToolVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMatrixToolFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetMatrixToolVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMatrixToolFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMatrixToolVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMatrixToolVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddMatrixToolFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetMatrixToolFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListMatrixToolFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listMatrixToolFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddMatrixToolProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsMatrixToolFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetMatrixToolProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsMatrixToolFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListMatrixToolProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsMatrixToolFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listMatrixToolProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveMatrixToolProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsMatrixToolFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceMatrixTool(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsMatrixToolFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------User defined rps object---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listUserDefinedRPSObjectAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listUserDefinedRPSObjectToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listUserDefinedRPSObjectFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveUserDefinedRPSObjectFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listUserDefinedRPSObjectPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveUserDefinedRPSObjectPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listUserDefinedRPSObjectTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listUserDefinedRPSObjectLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listUserDefinedRPSObjectDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listUserDefinedRPSObjectVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listUserDefinedRPSObjectFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listUserDefinedRPSObjectProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveUserDefinedRPSObjectProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsUserDefinedRPSObjectFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceUserDefinedRPSObject(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsUserDefinedRPSObjectFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Cumulative probability distribution---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCumulativeProbabilityDistributionAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listCumulativeProbabilityDistributionToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCumulativeProbabilityDistributionFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveCumulativeProbabilityDistributionFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCumulativeProbabilityDistributionPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveCumulativeProbabilityDistributionPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCumulativeProbabilityDistributionTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCumulativeProbabilityDistributionLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCumulativeProbabilityDistributionDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCumulativeProbabilityDistributionVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listCumulativeProbabilityDistributionFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listCumulativeProbabilityDistributionProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveCumulativeProbabilityDistributionProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceCumulativeProbabilityDistribution(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsCumulativeProbabilityDistributionFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------Gust factor---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddGustFactorAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsGustFactorFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetGustFactorAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsGustFactorFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListGustFactorAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listGustFactorAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddGustFactorToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsGustFactorFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetGustFactorToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsGustFactorFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListGustFactorToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listGustFactorToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddGustFactorFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsGustFactorFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetGustFactorFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsGustFactorFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListGustFactorFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listGustFactorFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveGustFactorFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsGustFactorFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddGustFactorPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsGustFactorFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetGustFactorPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsGustFactorFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListGustFactorPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listGustFactorPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveGustFactorPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsGustFactorFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddGustFactorTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsGustFactorFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetGustFactorTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsGustFactorFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListGustFactorTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listGustFactorTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddGustFactorLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsGustFactorFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetGustFactorLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsGustFactorFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListGustFactorLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listGustFactorLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddGustFactorDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsGustFactorFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetGustFactorDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsGustFactorFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListGustFactorDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listGustFactorDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddGustFactorVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsGustFactorFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetGustFactorVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsGustFactorFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListGustFactorVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listGustFactorVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddGustFactorFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsGustFactorFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetGustFactorFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsGustFactorFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListGustFactorFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listGustFactorFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddGustFactorProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsGustFactorFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetGustFactorProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsGustFactorFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListGustFactorProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsGustFactorFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listGustFactorProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveGustFactorProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsGustFactorFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceGustFactor(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsGustFactorFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------Kurtosis---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddKurtosisAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsKurtosisFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetKurtosisAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsKurtosisFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListKurtosisAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listKurtosisAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddKurtosisToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsKurtosisFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetKurtosisToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsKurtosisFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListKurtosisToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listKurtosisToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddKurtosisFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsKurtosisFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetKurtosisFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsKurtosisFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListKurtosisFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listKurtosisFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveKurtosisFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsKurtosisFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddKurtosisPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsKurtosisFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetKurtosisPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsKurtosisFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListKurtosisPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listKurtosisPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveKurtosisPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsKurtosisFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddKurtosisTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsKurtosisFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetKurtosisTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsKurtosisFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListKurtosisTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listKurtosisTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddKurtosisLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsKurtosisFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetKurtosisLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsKurtosisFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListKurtosisLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listKurtosisLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddKurtosisDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsKurtosisFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetKurtosisDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsKurtosisFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListKurtosisDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listKurtosisDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddKurtosisVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsKurtosisFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetKurtosisVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsKurtosisFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListKurtosisVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listKurtosisVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddKurtosisFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetKurtosisFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListKurtosisFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listKurtosisFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddKurtosisProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsKurtosisFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetKurtosisProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsKurtosisFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListKurtosisProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsKurtosisFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listKurtosisProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveKurtosisProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsKurtosisFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceKurtosis(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsKurtosisFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------Peak factor---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPeakFactorAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPeakFactorFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPeakFactorAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPeakFactorFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPeakFactorAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPeakFactorAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddPeakFactorToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPeakFactorFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPeakFactorToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPeakFactorFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPeakFactorToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listPeakFactorToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddPeakFactorFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPeakFactorFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPeakFactorFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPeakFactorFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPeakFactorFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPeakFactorFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemovePeakFactorFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsPeakFactorFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddPeakFactorPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPeakFactorFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPeakFactorPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPeakFactorFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPeakFactorPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPeakFactorPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemovePeakFactorPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsPeakFactorFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddPeakFactorTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPeakFactorFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPeakFactorTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPeakFactorFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPeakFactorTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPeakFactorTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPeakFactorLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPeakFactorFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPeakFactorLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPeakFactorFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPeakFactorLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPeakFactorLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPeakFactorDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPeakFactorFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPeakFactorDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPeakFactorFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPeakFactorDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPeakFactorDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPeakFactorVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPeakFactorFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetPeakFactorVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPeakFactorFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPeakFactorVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPeakFactorVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddPeakFactorFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetPeakFactorFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListPeakFactorFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listPeakFactorFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddPeakFactorProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsPeakFactorFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetPeakFactorProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsPeakFactorFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListPeakFactorProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsPeakFactorFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listPeakFactorProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemovePeakFactorProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsPeakFactorFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProducePeakFactor(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsPeakFactorFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Probability density function---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listProbabilityDensityFunctionAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listProbabilityDensityFunctionToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listProbabilityDensityFunctionFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveProbabilityDensityFunctionFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listProbabilityDensityFunctionPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveProbabilityDensityFunctionPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listProbabilityDensityFunctionTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listProbabilityDensityFunctionLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listProbabilityDensityFunctionDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listProbabilityDensityFunctionVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listProbabilityDensityFunctionFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listProbabilityDensityFunctionProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveProbabilityDensityFunctionProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsProbabilityDensityFunctionFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceProbabilityDensityFunction(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsProbabilityDensityFunctionFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Roughness---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRoughnessAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRoughnessFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRoughnessAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRoughnessFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRoughnessAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRoughnessAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddRoughnessToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRoughnessFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRoughnessToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRoughnessFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRoughnessToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listRoughnessToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddRoughnessFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRoughnessFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRoughnessFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRoughnessFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRoughnessFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRoughnessFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveRoughnessFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsRoughnessFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddRoughnessPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRoughnessFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRoughnessPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRoughnessFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRoughnessPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRoughnessPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveRoughnessPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsRoughnessFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddRoughnessTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRoughnessFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRoughnessTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRoughnessFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRoughnessTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRoughnessTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRoughnessLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRoughnessFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRoughnessLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRoughnessFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRoughnessLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRoughnessLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRoughnessDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRoughnessFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRoughnessDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRoughnessFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRoughnessDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRoughnessDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRoughnessVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRoughnessFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetRoughnessVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRoughnessFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRoughnessVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRoughnessVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddRoughnessFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsRoughnessFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetRoughnessFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsRoughnessFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListRoughnessFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listRoughnessFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddRoughnessProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsRoughnessFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetRoughnessProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsRoughnessFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListRoughnessProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsRoughnessFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listRoughnessProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveRoughnessProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsRoughnessFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceRoughness(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsRoughnessFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------shear velocity of flow---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listShearVelocityOfFlowAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listShearVelocityOfFlowToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listShearVelocityOfFlowFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveShearVelocityOfFlowFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listShearVelocityOfFlowPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveShearVelocityOfFlowPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listShearVelocityOfFlowTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listShearVelocityOfFlowLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listShearVelocityOfFlowDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listShearVelocityOfFlowVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listShearVelocityOfFlowFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsShearVelocityOfFlowFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listShearVelocityOfFlowProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveShearVelocityOfFlowProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsShearVelocityOfFlowFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceShearVelocityOfFlow(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsShearVelocityOfFlowFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Skewness---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSkewnessAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSkewnessFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSkewnessAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSkewnessFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSkewnessAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSkewnessAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddSkewnessToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSkewnessFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSkewnessToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSkewnessFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSkewnessToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listSkewnessToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddSkewnessFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSkewnessFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSkewnessFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSkewnessFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSkewnessFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSkewnessFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveSkewnessFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsSkewnessFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddSkewnessPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSkewnessFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSkewnessPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSkewnessFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSkewnessPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSkewnessPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveSkewnessPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsSkewnessFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddSkewnessTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSkewnessFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSkewnessTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSkewnessFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSkewnessTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSkewnessTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSkewnessLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSkewnessFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSkewnessLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSkewnessFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSkewnessLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSkewnessLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSkewnessDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSkewnessFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSkewnessDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSkewnessFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSkewnessDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSkewnessDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSkewnessVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSkewnessFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetSkewnessVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSkewnessFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSkewnessVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSkewnessVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddSkewnessFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetSkewnessFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListSkewnessFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listSkewnessFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddSkewnessProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsSkewnessFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetSkewnessProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsSkewnessFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListSkewnessProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsSkewnessFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listSkewnessProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveSkewnessProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsSkewnessFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceSkewness(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsSkewnessFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------Standard deviation---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddStandardDeviationAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsStandardDeviationFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetStandardDeviationAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsStandardDeviationFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListStandardDeviationAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listStandardDeviationAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddStandardDeviationToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetStandardDeviationToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListStandardDeviationToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listStandardDeviationToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddStandardDeviationFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsStandardDeviationFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetStandardDeviationFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsStandardDeviationFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListStandardDeviationFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listStandardDeviationFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveStandardDeviationFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsStandardDeviationFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddStandardDeviationPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsStandardDeviationFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetStandardDeviationPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsStandardDeviationFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListStandardDeviationPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listStandardDeviationPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveStandardDeviationPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsStandardDeviationFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddStandardDeviationTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsStandardDeviationFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetStandardDeviationTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsStandardDeviationFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListStandardDeviationTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listStandardDeviationTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddStandardDeviationLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsStandardDeviationFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetStandardDeviationLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsStandardDeviationFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListStandardDeviationLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listStandardDeviationLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddStandardDeviationDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsStandardDeviationFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetStandardDeviationDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsStandardDeviationFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListStandardDeviationDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listStandardDeviationDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddStandardDeviationVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsStandardDeviationFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetStandardDeviationVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsStandardDeviationFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListStandardDeviationVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listStandardDeviationVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddStandardDeviationFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetStandardDeviationFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListStandardDeviationFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listStandardDeviationFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddStandardDeviationProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsStandardDeviationFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetStandardDeviationProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsStandardDeviationFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListStandardDeviationProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsStandardDeviationFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listStandardDeviationProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveStandardDeviationProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsStandardDeviationFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceStandardDeviation(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsStandardDeviationFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Turbulence intensity---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceIntensityAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceIntensityFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceIntensityAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceIntensityFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceIntensityAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceIntensityAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceIntensityToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceIntensityToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceIntensityToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listTurbulenceIntensityToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceIntensityFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceIntensityFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceIntensityFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceIntensityFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveTurbulenceIntensityFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceIntensityPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceIntensityPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceIntensityPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceIntensityPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveTurbulenceIntensityPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceIntensityTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceIntensityFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceIntensityTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceIntensityFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceIntensityTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceIntensityTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceIntensityLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceIntensityFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceIntensityLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceIntensityFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceIntensityLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceIntensityLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceIntensityDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceIntensityFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceIntensityDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceIntensityFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceIntensityDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceIntensityDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceIntensityVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceIntensityFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceIntensityVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceIntensityFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceIntensityVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceIntensityVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddTurbulenceIntensityFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetTurbulenceIntensityFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListTurbulenceIntensityFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listTurbulenceIntensityFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceIntensityProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsTurbulenceIntensityFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceIntensityProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsTurbulenceIntensityFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceIntensityProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceIntensityFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceIntensityProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveTurbulenceIntensityProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsTurbulenceIntensityFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceTurbulenceIntensity(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsTurbulenceIntensityFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Turbulence scale---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceScaleAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceScaleFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceScaleAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceScaleFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceScaleAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceScaleAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceScaleToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceScaleToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceScaleToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listTurbulenceScaleToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceScaleFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceScaleFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceScaleFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceScaleFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveTurbulenceScaleFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceScalePlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceScalePlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceScalePlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceScalePlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveTurbulenceScalePlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceScaleTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceScaleFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceScaleTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceScaleFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceScaleTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceScaleTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceScaleLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceScaleFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceScaleLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceScaleFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceScaleLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceScaleLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceScaleDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceScaleFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceScaleDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceScaleFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceScaleDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceScaleDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceScaleVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceScaleFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceScaleVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceScaleFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceScaleVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceScaleVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddTurbulenceScaleFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetTurbulenceScaleFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListTurbulenceScaleFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listTurbulenceScaleFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddTurbulenceScaleProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsTurbulenceScaleFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetTurbulenceScaleProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsTurbulenceScaleFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListTurbulenceScaleProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsTurbulenceScaleFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listTurbulenceScaleProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveTurbulenceScaleProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsTurbulenceScaleFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceTurbulenceScale(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsTurbulenceScaleFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}


// --------------------------------------------------------------Variance---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddVarianceAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsVarianceFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetVarianceAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsVarianceFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListVarianceAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listVarianceAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddVarianceToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsVarianceFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetVarianceToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsVarianceFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListVarianceToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listVarianceToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddVarianceFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsVarianceFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetVarianceFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsVarianceFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListVarianceFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listVarianceFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveVarianceFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsVarianceFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddVariancePlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsVarianceFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetVariancePlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsVarianceFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListVariancePlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listVariancePlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveVariancePlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsVarianceFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddVarianceTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsVarianceFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetVarianceTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsVarianceFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListVarianceTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listVarianceTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddVarianceLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsVarianceFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetVarianceLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsVarianceFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListVarianceLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listVarianceLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddVarianceDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsVarianceFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetVarianceDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsVarianceFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListVarianceDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listVarianceDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddVarianceVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsVarianceFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetVarianceVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsVarianceFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListVarianceVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listVarianceVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddVarianceFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetVarianceFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListVarianceFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listVarianceFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddVarianceProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsVarianceFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetVarianceProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsVarianceFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListVarianceProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsVarianceFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listVarianceProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveVarianceProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsVarianceFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceVariance(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsVarianceFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// --------------------------------------------------------------Wave passage effect---------------------------------------------------------------


// --------------------Author---------------------
PyObject* RPSWindLabPythonPluginFactory::AddWavePassageEffectAuthor(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsWavePassageEffectFactory::GetAuthorMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and author name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetWavePassageEffectAuthor(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsWavePassageEffectFactory::GetAuthorMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListWavePassageEffectAuthor(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetAuthorMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listWavePassageEffectAuthors: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location authors Map.");
    return nullptr;
}

//To be installed features
PyObject* RPSWindLabPythonPluginFactory::AddWavePassageEffectToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetWavePassageEffectToBeInstalledFeature(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListWavePassageEffectToBeInstalledFeature(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(
                PyExc_AttributeError,
                "RPSWindLabPythonPluginFactory::listWavePassageEffectToBeInstalledFeatures: cannot "
                "insert element '%s':'%s' ",
                it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location ToBeInstalledFeatures Map.");
    return nullptr;
}

//feature description
PyObject* RPSWindLabPythonPluginFactory::AddWavePassageEffectFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsWavePassageEffectFactory::GetOjectDescriptionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Feature Description expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetWavePassageEffectFeatureDescription(PyObject* self,
                                                                          PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsWavePassageEffectFactory::GetOjectDescriptionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListWavePassageEffectFeatureDescription(PyObject* self,
                                                                           PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetOjectDescriptionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listWavePassageEffectFeatureDescription: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Feature Descriptions Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveWavePassageEffectFeatureDescription(PyObject* self,
                                                                             PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsWavePassageEffectFactory::GetOjectDescriptionMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

//plugin
PyObject* RPSWindLabPythonPluginFactory::AddWavePassageEffectPlugin(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsWavePassageEffectFactory::GetOjectAndPluginMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Plugin name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetWavePassageEffectPlugin(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsWavePassageEffectFactory::GetOjectAndPluginMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListWavePassageEffectPlugin(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetOjectAndPluginMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listWavePassageEffectPlugins: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Plugins Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveWavePassageEffectPlugin(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsWavePassageEffectFactory::GetOjectAndPluginMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

// -----------------------------------------------------Title---------------------------------------------------------------------
PyObject* RPSWindLabPythonPluginFactory::AddWavePassageEffectTitle(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsWavePassageEffectFactory::GetTitleMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Title name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetWavePassageEffectTitle(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsWavePassageEffectFactory::GetTitleMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListWavePassageEffectTitle(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetTitleMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listWavePassageEffectTitles: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Titles Map.");
    return nullptr;
}

// --------------------Link---------------------
PyObject* RPSWindLabPythonPluginFactory::AddWavePassageEffectLink(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsWavePassageEffectFactory::GetLinkMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Link name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetWavePassageEffectLink(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsWavePassageEffectFactory::GetLinkMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListWavePassageEffectLink(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetLinkMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listWavePassageEffectLinks: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Links Map.");
    return nullptr;
}

// --------------------Date---------------------
PyObject* RPSWindLabPythonPluginFactory::AddWavePassageEffectDate(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsWavePassageEffectFactory::GetDateMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Date name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetWavePassageEffectDate(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsWavePassageEffectFactory::GetDateMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListWavePassageEffectDate(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetDateMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listWavePassageEffectDates: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Dates Map.");
    return nullptr;
}

// --------------------Version---------------------
PyObject* RPSWindLabPythonPluginFactory::AddWavePassageEffectVersion(PyObject* self, PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsWavePassageEffectFactory::GetVersionMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name and Version name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::GetWavePassageEffectVersion(PyObject* self, PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsWavePassageEffectFactory::GetVersionMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListWavePassageEffectVersion(PyObject* self, PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetVersionMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listWavePassageEffectVersions: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Versions Map.");
    return nullptr;
}

// --------------------FeatureSkipDuringUnintallation---------------------
PyObject*
RPSWindLabPythonPluginFactory::AddWavePassageEffectFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char *key, *value;

    if (PyArg_ParseTuple(args, "ss", &key, &value)) {
        WindLabAPI::CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap()[key] = value;
        Py_Return;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError,
                    "Feature name and FeatureSkipDuringUnintallation name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::GetWavePassageEffectFeatureSkipDuringUnintallation(PyObject* self,
                                                                            PyObject* args)
{
    char* key;
    std::string value;

    if (PyArg_ParseTuple(args, "s", &key)) {
        value = WindLabAPI::CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap()[key];
        return Py::new_reference_to(Py::String(value));
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject*
RPSWindLabPythonPluginFactory::ListWavePassageEffectFeatureSkipDuringUnintallation(PyObject* self,
                                                                             PyObject* args)
{
    std::map<const std::string, std::string> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, std::string>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success =
            PyDict_SetItem(mapDict, Py::String(it->first).ptr(), Py::String(it->second).ptr());

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::"
                         "listWavePassageEffectFeatureSkipDuringUnintallations: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError,
                    "couldn't get the Location FeatureSkipDuringUnintallations Map.");
    return nullptr;
}

// --------------------Producer---------------------
PyObject* RPSWindLabPythonPluginFactory::AddWavePassageEffectProducer(PyObject* self, PyObject* args)
{
    char* name;
    PyObject* producer;
    if (!PyArg_ParseTuple(args, "sO", &name, &producer))
        throw Py::Exception();
    try {
        if (PyCallable_Check(producer) == 0) {
            throw Py::TypeError("this location distribution producer is not callable");
        }

        WindLabAPI::CrpsWavePassageEffectFactory::GetProducerMap()[name] = producer;
        Py_INCREF(producer);
        Py_Return;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::GetWavePassageEffectProducer(PyObject* self, PyObject* args)
{
    char* key;
    PyObject* producer;

    if (PyArg_ParseTuple(args, "s", &key)) {
        producer = WindLabAPI::CrpsWavePassageEffectFactory::GetProducerMap()[key];
        return producer;
    }

    PyErr_Clear();

    PyErr_SetString(PyExc_TypeError, "Feature name expected.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::ListWavePassageEffectProducer(PyObject* self, PyObject* args)
{
    std::map<const std::string, PyObject*> objMap;
    if (!PyArg_ParseTuple(args, "")) {
        Py_Return;
    }

    PyErr_Clear();
    objMap = WindLabAPI::CrpsWavePassageEffectFactory::GetProducerMap();
    PyObject* mapDict = PyDict_New();

    for (std::map<const std::string, PyObject*>::const_iterator it = objMap.begin();
         it != objMap.end(); ++it) {
        int non_success = PyDict_SetItem(mapDict, Py::String(it->first).ptr(), it->second);

        if (non_success)
            PyErr_Format(PyExc_AttributeError,
                         "RPSWindLabPythonPluginFactory::listWavePassageEffectProducers: cannot "
                         "insert element '%s':'%s' ",
                         it->first, it->second);
    }

    return mapDict;

    PyErr_SetString(PyExc_TypeError, "couldn't get the Location Producers Map.");
    return nullptr;
}

PyObject* RPSWindLabPythonPluginFactory::RemoveWavePassageEffectProducer(PyObject* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        throw Py::Exception();
    try {

        WindLabAPI::CrpsWavePassageEffectFactory::GetProducerMap().erase(name);
        return nullptr;
    }
    catch (const Py::Exception&) {
        throw;
    }
}

PyObject* RPSWindLabPythonPluginFactory::ProduceWavePassageEffect(PyObject* self, PyObject* args)
{
    char* newFeatureName;
    char* simulationName;
    char* pluggedFeatureName;

    if (!PyArg_ParseTuple(args, "sss", &newFeatureName, &simulationName, &pluggedFeatureName))
        throw Py::Exception();
    try {

        PyObject* newFeat = WindLabAPI::CrpsWavePassageEffectFactory::produceFeature(
            newFeatureName, simulationName, pluggedFeatureName);
        return newFeat;
    }
    catch (const Py::Exception&) {
        throw;
    }
}









PyMethodDef RPSWindLabPythonPluginFactory::Methods[] = {
    {"addLocationDistributionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionAuthor, METH_VARARGS,
    "addLocationDistributionAuthor(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionAuthor, METH_VARARGS,
    "getLocationDistributionAuthor(key) - get a record from the location feature map"},
    {"listLocationDistributionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionAuthor, METH_VARARGS,
    "listLocationDistributionAuthor() - list all the records in the location feature map"},
    {"addLocationDistributionToBeInstalledFeature", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionToBeInstalledFeature, METH_VARARGS,
    "addLocationDistributionToBeInstalledFeature(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionToBeInstalledFeature", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionToBeInstalledFeature, METH_VARARGS,
    "getLocationDistributionToBeInstalledFeature(key) - get a record from the location feature map"},
    {"listLocationDistributionToBeInstalledFeature", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionToBeInstalledFeature, METH_VARARGS,
    "listLocationDistributionToBeInstalledFeature() - list all the records in the location feature map"},
    {"addLocationDistributionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionFeatureDescription, METH_VARARGS,
    "addLocationDistributionFeatureDescription(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionFeatureDescription, METH_VARARGS,
    "getLocationDistributionFeatureDescription(key) - get a record from the location feature map"},
    {"listLocationDistributionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionFeatureDescription, METH_VARARGS,
    "listLocationDistributionFeatureDescription() - list all the records in the location feature map"},
    {"removeLocationDistributionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveLocationDistributionFeatureDescription, METH_VARARGS,
    "removeLocationDistributionFeatureDescription(name) - list all the records in the location feature map"},
    {"addLocationDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionPlugin, METH_VARARGS,
    "addLocationDistributionPlugin(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionPlugin, METH_VARARGS,
    "getLocationDistributionPlugin(key) - get a record from the location feature map"},
    {"listLocationDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionPlugin, METH_VARARGS,
    "listLocationDistributionPlugin() - list all the records in the location feature map"},
    {"removeLocationDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveLocationDistributionPlugin, METH_VARARGS,
    "removeLocationDistributionPlugin(name) - remove a location distribution record from feature map"},
    {"addLocationDistributionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionTitle, METH_VARARGS,
    "addLocationDistributionTitle(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionTitle, METH_VARARGS,
    "getLocationDistributionTitle(key) - get a record from the location feature map"},
    {"listLocationDistributionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionTitle, METH_VARARGS,
    "listLocationDistributionTitle() - list all the records in the location feature map"},
    {"addLocationDistributionLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionLink, METH_VARARGS,
    "addLocationDistributionLink(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionLink, METH_VARARGS,
    "getLocationDistributionLink(key) - get a record from the location feature map"},
    {"listLocationDistributionLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionLink, METH_VARARGS,
    "listLocationDistributionLink() - list all the records in the location feature map"},
    {"addLocationDistributionDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionDate, METH_VARARGS,
    "addLocationDistributionDate(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionDate, METH_VARARGS,
    "getLocationDistributionDate(key) - get a record from the location feature map"},
    {"listLocationDistributionDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionDate, METH_VARARGS,
    "listLocationDistributionDate() - list all the records in the location feature map"},
    {"addLocationDistributionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionVersion, METH_VARARGS,
    "addLocationDistributionVersion(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionVersion, METH_VARARGS,
    "getLocationDistributionVersion(key) - get a record from the location feature map"},
    {"listLocationDistributionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionVersion, METH_VARARGS,
    "listLocationDistributionVersion() - list all the records in the location feature map"},
    {"addLocationDistributionFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionFeatureSkipDuringUnintallation, METH_VARARGS,
    "addLocationDistributionFeatureSkipDuringUnintallation(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionFeatureSkipDuringUnintallation, METH_VARARGS,
    "getLocationDistributionFeatureSkipDuringUnintallation(key) - get a record from the location feature map"},
    {"listLocationDistributionFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionFeatureSkipDuringUnintallation, METH_VARARGS,
    "listLocationDistributionFeatureSkipDuringUnintallation() - list all the records in the location feature map"},
    {"addLocationDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddLocationDistributionProducer, METH_VARARGS,
    "addLocationDistributionProducer(key,value) - add a record to the location feature  map"},
    {"getLocationDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetLocationDistributionProducer, METH_VARARGS,
    "getLocationDistributionProducer(key) - get a record from the location feature map"},
    {"listLocationDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListLocationDistributionProducer, METH_VARARGS,
    "listLocationDistributionProducer() - list all the records in the location feature map"},
   {"removeLocationDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveLocationDistributionProducer, METH_VARARGS,
    "removeLocationDistributionProducer(name) - list all the records in the location feature map"},
   {"produceLocationDistribution", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceLocationDistribution, METH_VARARGS,
    "produceLocationDistribution(name) - list all the records in the location feature map"},
    {"addMeanAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanAuthor, METH_VARARGS,
    "addMeanAuthor(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanAuthor, METH_VARARGS,
    "getMeanAuthor(key) - get a record from the mean wind profile feature map"},
    {"listMeanAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanAuthor, METH_VARARGS,
    "listMeanAuthor() - list all the records in the mean wind profile feature map"},
    {"addMeanToBeInstalledFeature", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanToBeInstalledFeature, METH_VARARGS,
    "addMeanToBeInstalledFeature(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanToBeInstalledFeature", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanToBeInstalledFeature, METH_VARARGS,
    "getMeanToBeInstalledFeature(key) - get a record from the mean wind profile feature map"},
    {"listMeanToBeInstalledFeature", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanToBeInstalledFeature, METH_VARARGS,
    "listMeanToBeInstalledFeature() - list all the records in the mean wind profile feature map"},
    {"addMeanFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanFeatureDescription, METH_VARARGS,
    "addMeanFeatureDescription(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanFeatureDescription, METH_VARARGS,
    "getMeanFeatureDescription(key) - get a record from the mean wind profile feature map"},
    {"listMeanFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanFeatureDescription, METH_VARARGS,
    "listMeanFeatureDescription() - list all the records in the mean wind profile feature map"},
    {"removeMeanFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveMeanFeatureDescription, METH_VARARGS,
    "removeMeanFeatureDescription(name) - list all the records in the mean wind profile feature map"},
    {"addMeanPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanPlugin, METH_VARARGS,
    "addMeanPlugin(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanPlugin, METH_VARARGS,
    "getMeanPlugin(key) - get a record from the mean wind profile feature map"},
    {"listMeanPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanPlugin, METH_VARARGS,
    "listMeanPlugin() - list all the records in the mean wind profile feature map"},
    {"removeMeanPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveMeanPlugin, METH_VARARGS,
    "removeMeanPlugin(name) - remove a mean wind profile distribution record from feature map"},
    {"addMeanTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanTitle, METH_VARARGS,
    "addMeanTitle(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanTitle, METH_VARARGS,
    "getMeanTitle(key) - get a record from the mean wind profile feature map"},
    {"listMeanTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanTitle, METH_VARARGS,
    "listMeanTitle() - list all the records in the mean wind profile feature map"},
    {"addMeanLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanLink, METH_VARARGS,
    "addMeanLink(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanLink, METH_VARARGS,
    "getMeanLink(key) - get a record from the mean wind profile feature map"},
    {"listMeanLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanLink, METH_VARARGS,
    "listMeanLink() - list all the records in the mean wind profile feature map"},
    {"addMeanDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanDate, METH_VARARGS,
    "addMeanDate(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanDate, METH_VARARGS,
    "getMeanDate(key) - get a record from the mean wind profile feature map"},
    {"listMeanDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanDate, METH_VARARGS,
    "listMeanDate() - list all the records in the mean wind profile feature map"},
    {"addMeanVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanVersion, METH_VARARGS,
    "addMeanVersion(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanVersion, METH_VARARGS,
    "getMeanVersion(key) - get a record from the mean wind profile feature map"},
    {"listMeanVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanVersion, METH_VARARGS,
    "listMeanVersion() - list all the records in the mean wind profile feature map"},
    {"addMeanFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanFeatureSkipDuringUnintallation, METH_VARARGS,
    "addMeanFeatureSkipDuringUnintallation(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanFeatureSkipDuringUnintallation, METH_VARARGS,
    "getMeanFeatureSkipDuringUnintallation(key) - get a record from the mean wind profile feature map"},
    {"listMeanFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanFeatureSkipDuringUnintallation, METH_VARARGS,
    "listMeanFeatureSkipDuringUnintallation() - list all the records in the mean wind profile feature map"},
    {"addMeanProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddMeanProducer, METH_VARARGS,
    "addMeanProducer(key,value) - add a record to the mean wind profile feature  map"},
    {"getMeanProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetMeanProducer, METH_VARARGS,
    "getMeanProducer(key) - get a record from the mean wind profile feature map"},
    {"listMeanProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListMeanProducer, METH_VARARGS,
    "listMeanProducer() - list all the records in the mean wind profile feature map"},
   {"removeMeanProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveMeanProducer, METH_VARARGS,
    "removeMeanProducer(name) - list all the records in the mean wind profile feature map"},
   {"produceMean", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceMean, METH_VARARGS,
    "produceMean(name) - list all the records in the mean wind profile feature map"},
     {"addCoherenceAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddCoherenceAuthor, METH_VARARGS,
     "addCoherenceAuthor(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherenceAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetCoherenceAuthor, METH_VARARGS,
     "getCoherenceAuthor(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherenceAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListCoherenceAuthor, METH_VARARGS,
     "listCoherenceAuthor() - list all the records in the Coherence wind profile feature map"},
    {"addCoherenceToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddCoherenceToBeInstalledFeature, METH_VARARGS,
     "addCoherenceToBeInstalledFeature(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherenceToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetCoherenceToBeInstalledFeature, METH_VARARGS,
     "getCoherenceToBeInstalledFeature(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherenceToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListCoherenceToBeInstalledFeature, METH_VARARGS,
     "listCoherenceToBeInstalledFeature() - list all the records in the Coherence wind profile feature map"},
    {"addCoherenceFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddCoherenceFeatureDescription, METH_VARARGS,
     "addCoherenceFeatureDescription(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherenceFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetCoherenceFeatureDescription, METH_VARARGS,
     "getCoherenceFeatureDescription(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherenceFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListCoherenceFeatureDescription, METH_VARARGS,
     "listCoherenceFeatureDescription() - list all the records in the Coherence wind profile feature map"},
    {"removeCoherenceFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveCoherenceFeatureDescription, METH_VARARGS,
     "removeCoherenceFeatureDescription(name) - list all the records in the Coherence wind profile feature map"},
    {"addCoherencePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddCoherencePlugin, METH_VARARGS,
     "addCoherencePlugin(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherencePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetCoherencePlugin, METH_VARARGS,
     "getCoherencePlugin(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherencePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListCoherencePlugin, METH_VARARGS,
     "listCoherencePlugin() - list all the records in the Coherence wind profile feature map"},
    {"removeCoherencePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveCoherencePlugin, METH_VARARGS,
     "removeCoherencePlugin(name) - remove a Coherence wind profile distribution record from feature map"},
    {"addCoherenceTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddCoherenceTitle, METH_VARARGS,
     "addCoherenceTitle(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherenceTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetCoherenceTitle, METH_VARARGS,
     "getCoherenceTitle(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherenceTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListCoherenceTitle, METH_VARARGS,
     "listCoherenceTitle() - list all the records in the Coherence wind profile feature map"},
    {"addCoherenceLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddCoherenceLink, METH_VARARGS,
     "addCoherenceLink(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherenceLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetCoherenceLink, METH_VARARGS,
     "getCoherenceLink(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherenceLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListCoherenceLink, METH_VARARGS,
     "listCoherenceLink() - list all the records in the Coherence wind profile feature map"},
    {"addCoherenceDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddCoherenceDate, METH_VARARGS,
     "addCoherenceDate(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherenceDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetCoherenceDate, METH_VARARGS,
     "getCoherenceDate(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherenceDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListCoherenceDate, METH_VARARGS,
     "listCoherenceDate() - list all the records in the Coherence wind profile feature map"},
    {"addCoherenceVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddCoherenceVersion, METH_VARARGS,
     "addCoherenceVersion(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherenceVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetCoherenceVersion, METH_VARARGS,
     "getCoherenceVersion(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherenceVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListCoherenceVersion, METH_VARARGS,
     "listCoherenceVersion() - list all the records in the Coherence wind profile feature map"},
    {"addCoherenceFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddCoherenceFeatureSkipDuringUnintallation,METH_VARARGS,
     "addCoherenceFeatureSkipDuringUnintallation(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherenceFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetCoherenceFeatureSkipDuringUnintallation, METH_VARARGS,
     "getCoherenceFeatureSkipDuringUnintallation(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherenceFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListCoherenceFeatureSkipDuringUnintallation,METH_VARARGS,
     "listCoherenceFeatureSkipDuringUnintallation() - list all the records in the Coherence wind profile feature map"},
    {"addCoherenceProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddCoherenceProducer, METH_VARARGS,
     "addCoherenceProducer(key,value) - add a record to the Coherence wind profile feature  map"},
    {"getCoherenceProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetCoherenceProducer, METH_VARARGS,
     "getCoherenceProducer(key) - get a record from the Coherence wind profile feature map"},
    {"listCoherenceProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListCoherenceProducer, METH_VARARGS,
     "listCoherenceProducer() - list all the records in the Coherence wind profile feature map"},
    {"removeCoherenceProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveCoherenceProducer,METH_VARARGS,
     "removeCoherenceProducer(name) - list all the records in the Coherence wind profile feature map"},
    {"produceCoherence", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceCoherence, METH_VARARGS,
     "produceCoherence(name) - list all the records in the Coherence wind profile feature map"},

      {"addXSpectrumAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumAuthor, METH_VARARGS,
     "addXSpectrumAuthor(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumAuthor, METH_VARARGS,
     "getXSpectrumAuthor(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumAuthor, METH_VARARGS,
     "listXSpectrumAuthor() - list all the records in the XSpectrum wind profile feature map"},
    {"addXSpectrumToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumToBeInstalledFeature, METH_VARARGS,
     "addXSpectrumToBeInstalledFeature(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumToBeInstalledFeature, METH_VARARGS,
     "getXSpectrumToBeInstalledFeature(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumToBeInstalledFeature, METH_VARARGS,
     "listXSpectrumToBeInstalledFeature() - list all the records in the XSpectrum wind profile feature map"},
    {"addXSpectrumFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumFeatureDescription, METH_VARARGS,
     "addXSpectrumFeatureDescription(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumFeatureDescription, METH_VARARGS,
     "getXSpectrumFeatureDescription(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumFeatureDescription, METH_VARARGS,
     "listXSpectrumFeatureDescription() - list all the records in the XSpectrum wind profile feature map"},
    {"removeXSpectrumFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveXSpectrumFeatureDescription, METH_VARARGS,
     "removeXSpectrumFeatureDescription(name) - list all the records in the XSpectrum wind profile feature map"},
    {"addXSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumPlugin, METH_VARARGS,
     "addXSpectrumPlugin(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumPlugin, METH_VARARGS,
     "getXSpectrumPlugin(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumPlugin, METH_VARARGS,
     "listXSpectrumPlugin() - list all the records in the XSpectrum wind profile feature map"},
    {"removeXSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveXSpectrumPlugin, METH_VARARGS,
     "removeXSpectrumPlugin(name) - remove a XSpectrum wind profile distribution record from feature map"},
    {"addXSpectrumTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumTitle, METH_VARARGS,
     "addXSpectrumTitle(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumTitle, METH_VARARGS,
     "getXSpectrumTitle(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumTitle, METH_VARARGS,
     "listXSpectrumTitle() - list all the records in the XSpectrum wind profile feature map"},
    {"addXSpectrumLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumLink, METH_VARARGS,
     "addXSpectrumLink(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumLink, METH_VARARGS,
     "getXSpectrumLink(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumLink, METH_VARARGS,
     "listXSpectrumLink() - list all the records in the XSpectrum wind profile feature map"},
    {"addXSpectrumDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumDate, METH_VARARGS,
     "addXSpectrumDate(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumDate, METH_VARARGS,
     "getXSpectrumDate(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumDate, METH_VARARGS,
     "listXSpectrumDate() - list all the records in the XSpectrum wind profile feature map"},
    {"addXSpectrumVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumVersion, METH_VARARGS,
     "addXSpectrumVersion(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumVersion, METH_VARARGS,
     "getXSpectrumVersion(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumVersion, METH_VARARGS,
     "listXSpectrumVersion() - list all the records in the XSpectrum wind profile feature map"},
    {"addXSpectrumFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumFeatureSkipDuringUnintallation,METH_VARARGS,
     "addXSpectrumFeatureSkipDuringUnintallation(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumFeatureSkipDuringUnintallation, METH_VARARGS,
     "getXSpectrumFeatureSkipDuringUnintallation(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumFeatureSkipDuringUnintallation,METH_VARARGS,
     "listXSpectrumFeatureSkipDuringUnintallation() - list all the records in the XSpectrum wind profile feature map"},
    {"addXSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddXSpectrumProducer, METH_VARARGS,
     "addXSpectrumProducer(key,value) - add a record to the XSpectrum wind profile feature  map"},
    {"getXSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetXSpectrumProducer, METH_VARARGS,
     "getXSpectrumProducer(key) - get a record from the XSpectrum wind profile feature map"},
    {"listXSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListXSpectrumProducer, METH_VARARGS,
     "listXSpectrumProducer() - list all the records in the XSpectrum wind profile feature map"},
    {"removeXSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveXSpectrumProducer,METH_VARARGS,
     "removeXSpectrumProducer(name) - list all the records in the XSpectrum wind profile feature map"},
    {"produceXSpectrum", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceXSpectrum, METH_VARARGS,
     "produceXSpectrum(name) - list all the records in the XSpectrum wind profile feature map"},

    {"addZSpectrumAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumAuthor, METH_VARARGS,
     "addZSpectrumAuthor(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumAuthor, METH_VARARGS,
     "getZSpectrumAuthor(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumAuthor, METH_VARARGS,
     "listZSpectrumAuthor() - list all the records in the ZSpectrum wind profile feature map"},
    {"addZSpectrumToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumToBeInstalledFeature, METH_VARARGS,
     "addZSpectrumToBeInstalledFeature(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumToBeInstalledFeature, METH_VARARGS,
     "getZSpectrumToBeInstalledFeature(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumToBeInstalledFeature, METH_VARARGS,
     "listZSpectrumToBeInstalledFeature() - list all the records in the ZSpectrum wind profile feature map"},
    {"addZSpectrumFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumFeatureDescription, METH_VARARGS,
     "addZSpectrumFeatureDescription(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumFeatureDescription, METH_VARARGS,
     "getZSpectrumFeatureDescription(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumFeatureDescription, METH_VARARGS,
     "listZSpectrumFeatureDescription() - list all the records in the ZSpectrum wind profile feature map"},
    {"removeZSpectrumFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveZSpectrumFeatureDescription, METH_VARARGS,
     "removeZSpectrumFeatureDescription(name) - list all the records in the ZSpectrum wind profile feature map"},
    {"addZSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumPlugin, METH_VARARGS,
     "addZSpectrumPlugin(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumPlugin, METH_VARARGS,
     "getZSpectrumPlugin(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumPlugin, METH_VARARGS,
     "listZSpectrumPlugin() - list all the records in the ZSpectrum wind profile feature map"},
    {"removeZSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveZSpectrumPlugin, METH_VARARGS,
     "removeZSpectrumPlugin(name) - remove a ZSpectrum wind profile distribution record from feature map"},
    {"addZSpectrumTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumTitle, METH_VARARGS,
     "addZSpectrumTitle(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumTitle, METH_VARARGS,
     "getZSpectrumTitle(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumTitle, METH_VARARGS,
     "listZSpectrumTitle() - list all the records in the ZSpectrum wind profile feature map"},
    {"addZSpectrumLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumLink, METH_VARARGS,
     "addZSpectrumLink(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumLink, METH_VARARGS,
     "getZSpectrumLink(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumLink, METH_VARARGS,
     "listZSpectrumLink() - list all the records in the ZSpectrum wind profile feature map"},
    {"addZSpectrumDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumDate, METH_VARARGS,
     "addZSpectrumDate(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumDate, METH_VARARGS,
     "getZSpectrumDate(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumDate, METH_VARARGS,
     "listZSpectrumDate() - list all the records in the ZSpectrum wind profile feature map"},
    {"addZSpectrumVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumVersion, METH_VARARGS,
     "addZSpectrumVersion(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumVersion, METH_VARARGS,
     "getZSpectrumVersion(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumVersion, METH_VARARGS,
     "listZSpectrumVersion() - list all the records in the ZSpectrum wind profile feature map"},
    {"addZSpectrumFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumFeatureSkipDuringUnintallation,METH_VARARGS,
     "addZSpectrumFeatureSkipDuringUnintallation(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumFeatureSkipDuringUnintallation, METH_VARARGS,
     "getZSpectrumFeatureSkipDuringUnintallation(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumFeatureSkipDuringUnintallation,METH_VARARGS,
     "listZSpectrumFeatureSkipDuringUnintallation() - list all the records in the ZSpectrum wind profile feature map"},
    {"addZSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddZSpectrumProducer, METH_VARARGS,
     "addZSpectrumProducer(key,value) - add a record to the ZSpectrum wind profile feature  map"},
    {"getZSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetZSpectrumProducer, METH_VARARGS,
     "getZSpectrumProducer(key) - get a record from the ZSpectrum wind profile feature map"},
    {"listZSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListZSpectrumProducer, METH_VARARGS,
     "listZSpectrumProducer() - list all the records in the ZSpectrum wind profile feature map"},
    {"removeZSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveZSpectrumProducer,METH_VARARGS,
     "removeZSpectrumProducer(name) - list all the records in the ZSpectrum wind profile feature map"},
    {"produceZSpectrum", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceZSpectrum, METH_VARARGS,
     "produceZSpectrum(name) - list all the records in the ZSpectrum wind profile feature map"},


    {"addYSpectrumAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumAuthor, METH_VARARGS,
     "addYSpectrumAuthor(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumAuthor, METH_VARARGS,
     "getYSpectrumAuthor(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumAuthor, METH_VARARGS,
     "listYSpectrumAuthor() - list all the records in the YSpectrum wind profile feature map"},
    {"addYSpectrumToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumToBeInstalledFeature, METH_VARARGS,
     "addYSpectrumToBeInstalledFeature(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumToBeInstalledFeature, METH_VARARGS,
     "getYSpectrumToBeInstalledFeature(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumToBeInstalledFeature, METH_VARARGS,
     "listYSpectrumToBeInstalledFeature() - list all the records in the YSpectrum wind profile feature map"},
    {"addYSpectrumFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumFeatureDescription, METH_VARARGS,
     "addYSpectrumFeatureDescription(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumFeatureDescription, METH_VARARGS,
     "getYSpectrumFeatureDescription(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumFeatureDescription, METH_VARARGS,
     "listYSpectrumFeatureDescription() - list all the records in the YSpectrum wind profile feature map"},
    {"removeYSpectrumFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveYSpectrumFeatureDescription, METH_VARARGS,
     "removeYSpectrumFeatureDescription(name) - list all the records in the YSpectrum wind profile feature map"},
    {"addYSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumPlugin, METH_VARARGS,
     "addYSpectrumPlugin(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumPlugin, METH_VARARGS,
     "getYSpectrumPlugin(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumPlugin, METH_VARARGS,
     "listYSpectrumPlugin() - list all the records in the YSpectrum wind profile feature map"},
    {"removeYSpectrumPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveYSpectrumPlugin, METH_VARARGS,
     "removeYSpectrumPlugin(name) - remove a YSpectrum wind profile distribution record from feature map"},
    {"addYSpectrumTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumTitle, METH_VARARGS,
     "addYSpectrumTitle(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumTitle, METH_VARARGS,
     "getYSpectrumTitle(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumTitle, METH_VARARGS,
     "listYSpectrumTitle() - list all the records in the YSpectrum wind profile feature map"},
    {"addYSpectrumLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumLink, METH_VARARGS,
     "addYSpectrumLink(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumLink, METH_VARARGS,
     "getYSpectrumLink(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumLink, METH_VARARGS,
     "listYSpectrumLink() - list all the records in the YSpectrum wind profile feature map"},
    {"addYSpectrumDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumDate, METH_VARARGS,
     "addYSpectrumDate(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumDate, METH_VARARGS,
     "getYSpectrumDate(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumDate, METH_VARARGS,
     "listYSpectrumDate() - list all the records in the YSpectrum wind profile feature map"},
    {"addYSpectrumVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumVersion, METH_VARARGS,
     "addYSpectrumVersion(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumVersion, METH_VARARGS,
     "getYSpectrumVersion(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumVersion, METH_VARARGS,
     "listYSpectrumVersion() - list all the records in the YSpectrum wind profile feature map"},
    {"addYSpectrumFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumFeatureSkipDuringUnintallation,METH_VARARGS,
     "addYSpectrumFeatureSkipDuringUnintallation(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumFeatureSkipDuringUnintallation, METH_VARARGS,
     "getYSpectrumFeatureSkipDuringUnintallation(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumFeatureSkipDuringUnintallation,METH_VARARGS,
     "listYSpectrumFeatureSkipDuringUnintallation() - list all the records in the YSpectrum wind profile feature map"},
    {"addYSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddYSpectrumProducer, METH_VARARGS,
     "addYSpectrumProducer(key,value) - add a record to the YSpectrum wind profile feature  map"},
    {"getYSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetYSpectrumProducer, METH_VARARGS,
     "getYSpectrumProducer(key) - get a record from the YSpectrum wind profile feature map"},
    {"listYSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListYSpectrumProducer, METH_VARARGS,
     "listYSpectrumProducer() - list all the records in the YSpectrum wind profile feature map"},
    {"removeYSpectrumProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveYSpectrumProducer,METH_VARARGS,
     "removeYSpectrumProducer(name) - list all the records in the YSpectrum wind profile feature map"},
    {"produceYSpectrum", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceYSpectrum, METH_VARARGS,
     "produceYSpectrum(name) - list all the records in the YSpectrum wind profile feature map"},



    {"addSimuMethodAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodAuthor, METH_VARARGS,
     "addSimuMethodAuthor(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodAuthor, METH_VARARGS,
     "getSimuMethodAuthor(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodAuthor, METH_VARARGS,
     "listSimuMethodAuthor() - list all the records in the SimuMethod wind profile feature map"},
    {"addSimuMethodToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodToBeInstalledFeature, METH_VARARGS,
     "addSimuMethodToBeInstalledFeature(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodToBeInstalledFeature, METH_VARARGS,
     "getSimuMethodToBeInstalledFeature(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodToBeInstalledFeature, METH_VARARGS,
     "listSimuMethodToBeInstalledFeature() - list all the records in the SimuMethod wind profile feature map"},
    {"addSimuMethodFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodFeatureDescription, METH_VARARGS,
     "addSimuMethodFeatureDescription(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodFeatureDescription, METH_VARARGS,
     "getSimuMethodFeatureDescription(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodFeatureDescription, METH_VARARGS,
     "listSimuMethodFeatureDescription() - list all the records in the SimuMethod wind profile feature map"},
    {"removeSimuMethodFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveSimuMethodFeatureDescription, METH_VARARGS,
     "removeSimuMethodFeatureDescription(name) - list all the records in the SimuMethod wind profile feature map"},
    {"addSimuMethodPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodPlugin, METH_VARARGS,
     "addSimuMethodPlugin(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodPlugin, METH_VARARGS,
     "getSimuMethodPlugin(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodPlugin, METH_VARARGS,
     "listSimuMethodPlugin() - list all the records in the SimuMethod wind profile feature map"},
    {"removeSimuMethodPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveSimuMethodPlugin, METH_VARARGS,
     "removeSimuMethodPlugin(name) - remove a SimuMethod wind profile distribution record from feature map"},
    {"addSimuMethodTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodTitle, METH_VARARGS,
     "addSimuMethodTitle(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodTitle, METH_VARARGS,
     "getSimuMethodTitle(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodTitle, METH_VARARGS,
     "listSimuMethodTitle() - list all the records in the SimuMethod wind profile feature map"},
    {"addSimuMethodLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodLink, METH_VARARGS,
     "addSimuMethodLink(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodLink, METH_VARARGS,
     "getSimuMethodLink(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodLink, METH_VARARGS,
     "listSimuMethodLink() - list all the records in the SimuMethod wind profile feature map"},
    {"addSimuMethodDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodDate, METH_VARARGS,
     "addSimuMethodDate(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodDate, METH_VARARGS,
     "getSimuMethodDate(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodDate, METH_VARARGS,
     "listSimuMethodDate() - list all the records in the SimuMethod wind profile feature map"},
    {"addSimuMethodVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodVersion, METH_VARARGS,
     "addSimuMethodVersion(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodVersion, METH_VARARGS,
     "getSimuMethodVersion(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodVersion, METH_VARARGS,
     "listSimuMethodVersion() - list all the records in the SimuMethod wind profile feature map"},
    {"addSimuMethodFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodFeatureSkipDuringUnintallation,METH_VARARGS,
     "addSimuMethodFeatureSkipDuringUnintallation(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodFeatureSkipDuringUnintallation, METH_VARARGS,
     "getSimuMethodFeatureSkipDuringUnintallation(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodFeatureSkipDuringUnintallation,METH_VARARGS,
     "listSimuMethodFeatureSkipDuringUnintallation() - list all the records in the SimuMethod wind profile feature map"},
    {"addSimuMethodProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddSimuMethodProducer, METH_VARARGS,
     "addSimuMethodProducer(key,value) - add a record to the SimuMethod wind profile feature  map"},
    {"getSimuMethodProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetSimuMethodProducer, METH_VARARGS,
     "getSimuMethodProducer(key) - get a record from the SimuMethod wind profile feature map"},
    {"listSimuMethodProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListSimuMethodProducer, METH_VARARGS,
     "listSimuMethodProducer() - list all the records in the SimuMethod wind profile feature map"},
    {"removeSimuMethodProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveSimuMethodProducer,METH_VARARGS,
     "removeSimuMethodProducer(name) - list all the records in the SimuMethod wind profile feature map"},
    {"produceSimuMethod", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceSimuMethod, METH_VARARGS,
     "produceSimuMethod(name) - list all the records in the SimuMethod wind profile feature map"},



     {"addFrequencyDistributionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionAuthor, METH_VARARGS,
     "addFrequencyDistributionAuthor(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionAuthor, METH_VARARGS,
     "getFrequencyDistributionAuthor(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionAuthor, METH_VARARGS,
     "listFrequencyDistributionAuthor() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"addFrequencyDistributionToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionToBeInstalledFeature, METH_VARARGS,
     "addFrequencyDistributionToBeInstalledFeature(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionToBeInstalledFeature, METH_VARARGS,
     "getFrequencyDistributionToBeInstalledFeature(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionToBeInstalledFeature, METH_VARARGS,
     "listFrequencyDistributionToBeInstalledFeature() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"addFrequencyDistributionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionFeatureDescription, METH_VARARGS,
     "addFrequencyDistributionFeatureDescription(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionFeatureDescription, METH_VARARGS,
     "getFrequencyDistributionFeatureDescription(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionFeatureDescription, METH_VARARGS,
     "listFrequencyDistributionFeatureDescription() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"removeFrequencyDistributionFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveFrequencyDistributionFeatureDescription, METH_VARARGS,
     "removeFrequencyDistributionFeatureDescription(name) - list all the records in the FrequencyDistribution wind profile feature map"},
    {"addFrequencyDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionPlugin, METH_VARARGS,
     "addFrequencyDistributionPlugin(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionPlugin, METH_VARARGS,
     "getFrequencyDistributionPlugin(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionPlugin, METH_VARARGS,
     "listFrequencyDistributionPlugin() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"removeFrequencyDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveFrequencyDistributionPlugin, METH_VARARGS,
     "removeFrequencyDistributionPlugin(name) - remove a FrequencyDistribution wind profile distribution record from feature map"},
    {"addFrequencyDistributionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionTitle, METH_VARARGS,
     "addFrequencyDistributionTitle(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionTitle, METH_VARARGS,
     "getFrequencyDistributionTitle(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionTitle, METH_VARARGS,
     "listFrequencyDistributionTitle() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"addFrequencyDistributionLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionLink, METH_VARARGS,
     "addFrequencyDistributionLink(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionLink, METH_VARARGS,
     "getFrequencyDistributionLink(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionLink, METH_VARARGS,
     "listFrequencyDistributionLink() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"addFrequencyDistributionDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionDate, METH_VARARGS,
     "addFrequencyDistributionDate(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionDate, METH_VARARGS,
     "getFrequencyDistributionDate(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionDate, METH_VARARGS,
     "listFrequencyDistributionDate() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"addFrequencyDistributionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionVersion, METH_VARARGS,
     "addFrequencyDistributionVersion(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionVersion, METH_VARARGS,
     "getFrequencyDistributionVersion(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionVersion, METH_VARARGS,
     "listFrequencyDistributionVersion() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"addFrequencyDistributionFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionFeatureSkipDuringUnintallation,METH_VARARGS,
     "addFrequencyDistributionFeatureSkipDuringUnintallation(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionFeatureSkipDuringUnintallation, METH_VARARGS,
     "getFrequencyDistributionFeatureSkipDuringUnintallation(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionFeatureSkipDuringUnintallation,METH_VARARGS,
     "listFrequencyDistributionFeatureSkipDuringUnintallation() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"addFrequencyDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddFrequencyDistributionProducer, METH_VARARGS,
     "addFrequencyDistributionProducer(key,value) - add a record to the FrequencyDistribution wind profile feature  map"},
    {"getFrequencyDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetFrequencyDistributionProducer, METH_VARARGS,
     "getFrequencyDistributionProducer(key) - get a record from the FrequencyDistribution wind profile feature map"},
    {"listFrequencyDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListFrequencyDistributionProducer, METH_VARARGS,
     "listFrequencyDistributionProducer() - list all the records in the FrequencyDistribution wind profile feature map"},
    {"removeFrequencyDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveFrequencyDistributionProducer,METH_VARARGS,
     "removeFrequencyDistributionProducer(name) - list all the records in the FrequencyDistribution wind profile feature map"},
    {"produceFrequencyDistribution", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceFrequencyDistribution, METH_VARARGS,
     "produceFrequencyDistribution(name) - list all the records in the FrequencyDistribution wind profile feature map"},


      {"addRandomnessAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessAuthor, METH_VARARGS,
     "addRandomnessAuthor(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessAuthor, METH_VARARGS,
     "getRandomnessAuthor(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessAuthor, METH_VARARGS,
     "listRandomnessAuthor() - list all the records in the Randomness wind profile feature map"},
    {"addRandomnessToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessToBeInstalledFeature, METH_VARARGS,
     "addRandomnessToBeInstalledFeature(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessToBeInstalledFeature, METH_VARARGS,
     "getRandomnessToBeInstalledFeature(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessToBeInstalledFeature, METH_VARARGS,
     "listRandomnessToBeInstalledFeature() - list all the records in the Randomness wind profile feature map"},
    {"addRandomnessFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessFeatureDescription, METH_VARARGS,
     "addRandomnessFeatureDescription(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessFeatureDescription, METH_VARARGS,
     "getRandomnessFeatureDescription(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessFeatureDescription, METH_VARARGS,
     "listRandomnessFeatureDescription() - list all the records in the Randomness wind profile feature map"},
    {"removeRandomnessFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveRandomnessFeatureDescription, METH_VARARGS,
     "removeRandomnessFeatureDescription(name) - list all the records in the Randomness wind profile feature map"},
    {"addRandomnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessPlugin, METH_VARARGS,
     "addRandomnessPlugin(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessPlugin, METH_VARARGS,
     "getRandomnessPlugin(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessPlugin, METH_VARARGS,
     "listRandomnessPlugin() - list all the records in the Randomness wind profile feature map"},
    {"removeRandomnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveRandomnessPlugin, METH_VARARGS,
     "removeRandomnessPlugin(name) - remove a Randomness wind profile distribution record from feature map"},
    {"addRandomnessTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessTitle, METH_VARARGS,
     "addRandomnessTitle(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessTitle, METH_VARARGS,
     "getRandomnessTitle(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessTitle, METH_VARARGS,
     "listRandomnessTitle() - list all the records in the Randomness wind profile feature map"},
    {"addRandomnessLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessLink, METH_VARARGS,
     "addRandomnessLink(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessLink, METH_VARARGS,
     "getRandomnessLink(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessLink, METH_VARARGS,
     "listRandomnessLink() - list all the records in the Randomness wind profile feature map"},
    {"addRandomnessDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessDate, METH_VARARGS,
     "addRandomnessDate(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessDate, METH_VARARGS,
     "getRandomnessDate(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessDate, METH_VARARGS,
     "listRandomnessDate() - list all the records in the Randomness wind profile feature map"},
    {"addRandomnessVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessVersion, METH_VARARGS,
     "addRandomnessVersion(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessVersion, METH_VARARGS,
     "getRandomnessVersion(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessVersion, METH_VARARGS,
     "listRandomnessVersion() - list all the records in the Randomness wind profile feature map"},
    {"addRandomnessFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessFeatureSkipDuringUnintallation,METH_VARARGS,
     "addRandomnessFeatureSkipDuringUnintallation(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessFeatureSkipDuringUnintallation, METH_VARARGS,
     "getRandomnessFeatureSkipDuringUnintallation(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessFeatureSkipDuringUnintallation,METH_VARARGS,
     "listRandomnessFeatureSkipDuringUnintallation() - list all the records in the Randomness wind profile feature map"},
    {"addRandomnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddRandomnessProducer, METH_VARARGS,
     "addRandomnessProducer(key,value) - add a record to the Randomness wind profile feature  map"},
    {"getRandomnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetRandomnessProducer, METH_VARARGS,
     "getRandomnessProducer(key) - get a record from the Randomness wind profile feature map"},
    {"listRandomnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListRandomnessProducer, METH_VARARGS,
     "listRandomnessProducer() - list all the records in the Randomness wind profile feature map"},
    {"removeRandomnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveRandomnessProducer,METH_VARARGS,
     "removeRandomnessProducer(name) - list all the records in the Randomness wind profile feature map"},
    {"produceRandomness", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceRandomness, METH_VARARGS,
     "produceRandomness(name) - list all the records in the Randomness wind profile feature map"},

      {"addPSDdecomMethodAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodAuthor, METH_VARARGS,
     "addPSDdecomMethodAuthor(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodAuthor, METH_VARARGS,
     "getPSDdecomMethodAuthor(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodAuthor, METH_VARARGS,
     "listPSDdecomMethodAuthor() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"addPSDdecomMethodToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodToBeInstalledFeature, METH_VARARGS,
     "addPSDdecomMethodToBeInstalledFeature(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodToBeInstalledFeature, METH_VARARGS,
     "getPSDdecomMethodToBeInstalledFeature(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodToBeInstalledFeature, METH_VARARGS,
     "listPSDdecomMethodToBeInstalledFeature() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"addPSDdecomMethodFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodFeatureDescription, METH_VARARGS,
     "addPSDdecomMethodFeatureDescription(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodFeatureDescription, METH_VARARGS,
     "getPSDdecomMethodFeatureDescription(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodFeatureDescription, METH_VARARGS,
     "listPSDdecomMethodFeatureDescription() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"removePSDdecomMethodFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemovePSDdecomMethodFeatureDescription, METH_VARARGS,
     "removePSDdecomMethodFeatureDescription(name) - list all the records in the PSDdecomMethod wind profile feature map"},
    {"addPSDdecomMethodPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodPlugin, METH_VARARGS,
     "addPSDdecomMethodPlugin(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodPlugin, METH_VARARGS,
     "getPSDdecomMethodPlugin(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodPlugin, METH_VARARGS,
     "listPSDdecomMethodPlugin() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"removePSDdecomMethodPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemovePSDdecomMethodPlugin, METH_VARARGS,
     "removePSDdecomMethodPlugin(name) - remove a PSDdecomMethod wind profile distribution record from feature map"},
    {"addPSDdecomMethodTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodTitle, METH_VARARGS,
     "addPSDdecomMethodTitle(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodTitle, METH_VARARGS,
     "getPSDdecomMethodTitle(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodTitle, METH_VARARGS,
     "listPSDdecomMethodTitle() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"addPSDdecomMethodLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodLink, METH_VARARGS,
     "addPSDdecomMethodLink(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodLink, METH_VARARGS,
     "getPSDdecomMethodLink(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodLink, METH_VARARGS,
     "listPSDdecomMethodLink() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"addPSDdecomMethodDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodDate, METH_VARARGS,
     "addPSDdecomMethodDate(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodDate, METH_VARARGS,
     "getPSDdecomMethodDate(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodDate, METH_VARARGS,
     "listPSDdecomMethodDate() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"addPSDdecomMethodVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodVersion, METH_VARARGS,
     "addPSDdecomMethodVersion(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodVersion, METH_VARARGS,
     "getPSDdecomMethodVersion(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodVersion, METH_VARARGS,
     "listPSDdecomMethodVersion() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"addPSDdecomMethodFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodFeatureSkipDuringUnintallation,METH_VARARGS,
     "addPSDdecomMethodFeatureSkipDuringUnintallation(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodFeatureSkipDuringUnintallation, METH_VARARGS,
     "getPSDdecomMethodFeatureSkipDuringUnintallation(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodFeatureSkipDuringUnintallation,METH_VARARGS,
     "listPSDdecomMethodFeatureSkipDuringUnintallation() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"addPSDdecomMethodProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddPSDdecomMethodProducer, METH_VARARGS,
     "addPSDdecomMethodProducer(key,value) - add a record to the PSDdecomMethod wind profile feature  map"},
    {"getPSDdecomMethodProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetPSDdecomMethodProducer, METH_VARARGS,
     "getPSDdecomMethodProducer(key) - get a record from the PSDdecomMethod wind profile feature map"},
    {"listPSDdecomMethodProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListPSDdecomMethodProducer, METH_VARARGS,
     "listPSDdecomMethodProducer() - list all the records in the PSDdecomMethod wind profile feature map"},
    {"removePSDdecomMethodProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemovePSDdecomMethodProducer,METH_VARARGS,
     "removePSDdecomMethodProducer(name) - list all the records in the PSDdecomMethod wind profile feature map"},
    {"producePSDdecomMethod", (PyCFunction)RPSWindLabPythonPluginFactory::ProducePSDdecomMethod, METH_VARARGS,
     "producePSDdecomMethod(name) - list all the records in the PSDdecomMethod wind profile feature map"},



    {"addCorrelationAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationAuthor, METH_VARARGS,
     "addCorrelationAuthor(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationAuthor, METH_VARARGS,
     "getCorrelationAuthor(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationAuthor, METH_VARARGS,
     "listCorrelationAuthor() - list all the records in the Correlation wind profile feature map"},
    {"addCorrelationToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationToBeInstalledFeature, METH_VARARGS,
     "addCorrelationToBeInstalledFeature(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationToBeInstalledFeature, METH_VARARGS,
     "getCorrelationToBeInstalledFeature(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationToBeInstalledFeature, METH_VARARGS,
     "listCorrelationToBeInstalledFeature() - list all the records in the Correlation wind profile feature map"},
    {"addCorrelationFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationFeatureDescription, METH_VARARGS,
     "addCorrelationFeatureDescription(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationFeatureDescription, METH_VARARGS,
     "getCorrelationFeatureDescription(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationFeatureDescription, METH_VARARGS,
     "listCorrelationFeatureDescription() - list all the records in the Correlation wind profile feature map"},
    {"removeCorrelationFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveCorrelationFeatureDescription, METH_VARARGS,
     "removeCorrelationFeatureDescription(name) - list all the records in the Correlation wind profile feature map"},
    {"addCorrelationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationPlugin, METH_VARARGS,
     "addCorrelationPlugin(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationPlugin, METH_VARARGS,
     "getCorrelationPlugin(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationPlugin, METH_VARARGS,
     "listCorrelationPlugin() - list all the records in the Correlation wind profile feature map"},
    {"removeCorrelationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveCorrelationPlugin, METH_VARARGS,
     "removeCorrelationPlugin(name) - remove a Correlation wind profile distribution record from feature map"},
    {"addCorrelationTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationTitle, METH_VARARGS,
     "addCorrelationTitle(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationTitle, METH_VARARGS,
     "getCorrelationTitle(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationTitle, METH_VARARGS,
     "listCorrelationTitle() - list all the records in the Correlation wind profile feature map"},
    {"addCorrelationLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationLink, METH_VARARGS,
     "addCorrelationLink(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationLink, METH_VARARGS,
     "getCorrelationLink(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationLink, METH_VARARGS,
     "listCorrelationLink() - list all the records in the Correlation wind profile feature map"},
    {"addCorrelationDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationDate, METH_VARARGS,
     "addCorrelationDate(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationDate, METH_VARARGS,
     "getCorrelationDate(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationDate, METH_VARARGS,
     "listCorrelationDate() - list all the records in the Correlation wind profile feature map"},
    {"addCorrelationVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationVersion, METH_VARARGS,
     "addCorrelationVersion(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationVersion, METH_VARARGS,
     "getCorrelationVersion(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationVersion, METH_VARARGS,
     "listCorrelationVersion() - list all the records in the Correlation wind profile feature map"},
    {"addCorrelationFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationFeatureSkipDuringUnintallation,METH_VARARGS,
     "addCorrelationFeatureSkipDuringUnintallation(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationFeatureSkipDuringUnintallation, METH_VARARGS,
     "getCorrelationFeatureSkipDuringUnintallation(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationFeatureSkipDuringUnintallation,METH_VARARGS,
     "listCorrelationFeatureSkipDuringUnintallation() - list all the records in the Correlation wind profile feature map"},
    {"addCorrelationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddCorrelationProducer, METH_VARARGS,
     "addCorrelationProducer(key,value) - add a record to the Correlation wind profile feature  map"},
    {"getCorrelationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetCorrelationProducer, METH_VARARGS,
     "getCorrelationProducer(key) - get a record from the Correlation wind profile feature map"},
    {"listCorrelationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListCorrelationProducer, METH_VARARGS,
     "listCorrelationProducer() - list all the records in the Correlation wind profile feature map"},
    {"removeCorrelationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveCorrelationProducer,METH_VARARGS,
     "removeCorrelationProducer(name) - list all the records in the Correlation wind profile feature map"},
    {"produceCorrelation", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceCorrelation, METH_VARARGS,
     "produceCorrelation(name) - list all the records in the Correlation wind profile feature map"},



    {"addModulationAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddModulationAuthor, METH_VARARGS,
     "addModulationAuthor(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetModulationAuthor, METH_VARARGS,
     "getModulationAuthor(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListModulationAuthor, METH_VARARGS,
     "listModulationAuthor() - list all the records in the Modulation wind profile feature map"},
    {"addModulationToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddModulationToBeInstalledFeature, METH_VARARGS,
     "addModulationToBeInstalledFeature(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetModulationToBeInstalledFeature, METH_VARARGS,
     "getModulationToBeInstalledFeature(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListModulationToBeInstalledFeature, METH_VARARGS,
     "listModulationToBeInstalledFeature() - list all the records in the Modulation wind profile feature map"},
    {"addModulationFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddModulationFeatureDescription, METH_VARARGS,
     "addModulationFeatureDescription(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetModulationFeatureDescription, METH_VARARGS,
     "getModulationFeatureDescription(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListModulationFeatureDescription, METH_VARARGS,
     "listModulationFeatureDescription() - list all the records in the Modulation wind profile feature map"},
    {"removeModulationFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveModulationFeatureDescription, METH_VARARGS,
     "removeModulationFeatureDescription(name) - list all the records in the Modulation wind profile feature map"},
    {"addModulationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddModulationPlugin, METH_VARARGS,
     "addModulationPlugin(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetModulationPlugin, METH_VARARGS,
     "getModulationPlugin(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListModulationPlugin, METH_VARARGS,
     "listModulationPlugin() - list all the records in the Modulation wind profile feature map"},
    {"removeModulationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveModulationPlugin, METH_VARARGS,
     "removeModulationPlugin(name) - remove a Modulation wind profile distribution record from feature map"},
    {"addModulationTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddModulationTitle, METH_VARARGS,
     "addModulationTitle(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetModulationTitle, METH_VARARGS,
     "getModulationTitle(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListModulationTitle, METH_VARARGS,
     "listModulationTitle() - list all the records in the Modulation wind profile feature map"},
    {"addModulationLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddModulationLink, METH_VARARGS,
     "addModulationLink(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetModulationLink, METH_VARARGS,
     "getModulationLink(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListModulationLink, METH_VARARGS,
     "listModulationLink() - list all the records in the Modulation wind profile feature map"},
    {"addModulationDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddModulationDate, METH_VARARGS,
     "addModulationDate(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetModulationDate, METH_VARARGS,
     "getModulationDate(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListModulationDate, METH_VARARGS,
     "listModulationDate() - list all the records in the Modulation wind profile feature map"},
    {"addModulationVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddModulationVersion, METH_VARARGS,
     "addModulationVersion(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetModulationVersion, METH_VARARGS,
     "getModulationVersion(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListModulationVersion, METH_VARARGS,
     "listModulationVersion() - list all the records in the Modulation wind profile feature map"},
    {"addModulationFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddModulationFeatureSkipDuringUnintallation,METH_VARARGS,
     "addModulationFeatureSkipDuringUnintallation(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetModulationFeatureSkipDuringUnintallation, METH_VARARGS,
     "getModulationFeatureSkipDuringUnintallation(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListModulationFeatureSkipDuringUnintallation,METH_VARARGS,
     "listModulationFeatureSkipDuringUnintallation() - list all the records in the Modulation wind profile feature map"},
    {"addModulationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddModulationProducer, METH_VARARGS,
     "addModulationProducer(key,value) - add a record to the Modulation wind profile feature  map"},
    {"getModulationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetModulationProducer, METH_VARARGS,
     "getModulationProducer(key) - get a record from the Modulation wind profile feature map"},
    {"listModulationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListModulationProducer, METH_VARARGS,
     "listModulationProducer() - list all the records in the Modulation wind profile feature map"},
    {"removeModulationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveModulationProducer,METH_VARARGS,
     "removeModulationProducer(name) - list all the records in the Modulation wind profile feature map"},
    {"produceModulation", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceModulation, METH_VARARGS,
     "produceModulation(name) - list all the records in the Modulation wind profile feature map"},



     {"addTableToolAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolAuthor, METH_VARARGS,
     "addTableToolAuthor(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolAuthor, METH_VARARGS,
     "getTableToolAuthor(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolAuthor, METH_VARARGS,
     "listTableToolAuthor() - list all the records in the TableTool wind profile feature map"},
    {"addTableToolToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolToBeInstalledFeature, METH_VARARGS,
     "addTableToolToBeInstalledFeature(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolToBeInstalledFeature, METH_VARARGS,
     "getTableToolToBeInstalledFeature(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolToBeInstalledFeature, METH_VARARGS,
     "listTableToolToBeInstalledFeature() - list all the records in the TableTool wind profile feature map"},
    {"addTableToolFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolFeatureDescription, METH_VARARGS,
     "addTableToolFeatureDescription(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolFeatureDescription, METH_VARARGS,
     "getTableToolFeatureDescription(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolFeatureDescription, METH_VARARGS,
     "listTableToolFeatureDescription() - list all the records in the TableTool wind profile feature map"},
    {"removeTableToolFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveTableToolFeatureDescription, METH_VARARGS,
     "removeTableToolFeatureDescription(name) - list all the records in the TableTool wind profile feature map"},
    {"addTableToolPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolPlugin, METH_VARARGS,
     "addTableToolPlugin(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolPlugin, METH_VARARGS,
     "getTableToolPlugin(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolPlugin, METH_VARARGS,
     "listTableToolPlugin() - list all the records in the TableTool wind profile feature map"},
    {"removeTableToolPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveTableToolPlugin, METH_VARARGS,
     "removeTableToolPlugin(name) - remove a TableTool wind profile distribution record from feature map"},
    {"addTableToolTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolTitle, METH_VARARGS,
     "addTableToolTitle(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolTitle, METH_VARARGS,
     "getTableToolTitle(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolTitle, METH_VARARGS,
     "listTableToolTitle() - list all the records in the TableTool wind profile feature map"},
    {"addTableToolLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolLink, METH_VARARGS,
     "addTableToolLink(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolLink, METH_VARARGS,
     "getTableToolLink(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolLink, METH_VARARGS,
     "listTableToolLink() - list all the records in the TableTool wind profile feature map"},
    {"addTableToolDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolDate, METH_VARARGS,
     "addTableToolDate(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolDate, METH_VARARGS,
     "getTableToolDate(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolDate, METH_VARARGS,
     "listTableToolDate() - list all the records in the TableTool wind profile feature map"},
    {"addTableToolVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolVersion, METH_VARARGS,
     "addTableToolVersion(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolVersion, METH_VARARGS,
     "getTableToolVersion(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolVersion, METH_VARARGS,
     "listTableToolVersion() - list all the records in the TableTool wind profile feature map"},
    {"addTableToolFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolFeatureSkipDuringUnintallation,METH_VARARGS,
     "addTableToolFeatureSkipDuringUnintallation(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolFeatureSkipDuringUnintallation, METH_VARARGS,
     "getTableToolFeatureSkipDuringUnintallation(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolFeatureSkipDuringUnintallation,METH_VARARGS,
     "listTableToolFeatureSkipDuringUnintallation() - list all the records in the TableTool wind profile feature map"},
    {"addTableToolProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddTableToolProducer, METH_VARARGS,
     "addTableToolProducer(key,value) - add a record to the TableTool wind profile feature  map"},
    {"getTableToolProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetTableToolProducer, METH_VARARGS,
     "getTableToolProducer(key) - get a record from the TableTool wind profile feature map"},
    {"listTableToolProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListTableToolProducer, METH_VARARGS,
     "listTableToolProducer() - list all the records in the TableTool wind profile feature map"},
    {"removeTableToolProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveTableToolProducer,METH_VARARGS,
     "removeTableToolProducer(name) - list all the records in the TableTool wind profile feature map"},
    {"produceTableTool", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceTableTool, METH_VARARGS,
     "produceTableTool(name) - list all the records in the TableTool wind profile feature map"},



     {"addMatrixToolAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolAuthor, METH_VARARGS,
     "addMatrixToolAuthor(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolAuthor, METH_VARARGS,
     "getMatrixToolAuthor(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolAuthor, METH_VARARGS,
     "listMatrixToolAuthor() - list all the records in the MatrixTool wind profile feature map"},
    {"addMatrixToolToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolToBeInstalledFeature, METH_VARARGS,
     "addMatrixToolToBeInstalledFeature(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolToBeInstalledFeature, METH_VARARGS,
     "getMatrixToolToBeInstalledFeature(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolToBeInstalledFeature, METH_VARARGS,
     "listMatrixToolToBeInstalledFeature() - list all the records in the MatrixTool wind profile feature map"},
    {"addMatrixToolFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolFeatureDescription, METH_VARARGS,
     "addMatrixToolFeatureDescription(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolFeatureDescription, METH_VARARGS,
     "getMatrixToolFeatureDescription(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolFeatureDescription, METH_VARARGS,
     "listMatrixToolFeatureDescription() - list all the records in the MatrixTool wind profile feature map"},
    {"removeMatrixToolFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveMatrixToolFeatureDescription, METH_VARARGS,
     "removeMatrixToolFeatureDescription(name) - list all the records in the MatrixTool wind profile feature map"},
    {"addMatrixToolPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolPlugin, METH_VARARGS,
     "addMatrixToolPlugin(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolPlugin, METH_VARARGS,
     "getMatrixToolPlugin(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolPlugin, METH_VARARGS,
     "listMatrixToolPlugin() - list all the records in the MatrixTool wind profile feature map"},
    {"removeMatrixToolPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveMatrixToolPlugin, METH_VARARGS,
     "removeMatrixToolPlugin(name) - remove a MatrixTool wind profile distribution record from feature map"},
    {"addMatrixToolTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolTitle, METH_VARARGS,
     "addMatrixToolTitle(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolTitle, METH_VARARGS,
     "getMatrixToolTitle(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolTitle, METH_VARARGS,
     "listMatrixToolTitle() - list all the records in the MatrixTool wind profile feature map"},
    {"addMatrixToolLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolLink, METH_VARARGS,
     "addMatrixToolLink(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolLink, METH_VARARGS,
     "getMatrixToolLink(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolLink, METH_VARARGS,
     "listMatrixToolLink() - list all the records in the MatrixTool wind profile feature map"},
    {"addMatrixToolDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolDate, METH_VARARGS,
     "addMatrixToolDate(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolDate, METH_VARARGS,
     "getMatrixToolDate(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolDate, METH_VARARGS,
     "listMatrixToolDate() - list all the records in the MatrixTool wind profile feature map"},
    {"addMatrixToolVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolVersion, METH_VARARGS,
     "addMatrixToolVersion(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolVersion, METH_VARARGS,
     "getMatrixToolVersion(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolVersion, METH_VARARGS,
     "listMatrixToolVersion() - list all the records in the MatrixTool wind profile feature map"},
    {"addMatrixToolFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolFeatureSkipDuringUnintallation,METH_VARARGS,
     "addMatrixToolFeatureSkipDuringUnintallation(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolFeatureSkipDuringUnintallation, METH_VARARGS,
     "getMatrixToolFeatureSkipDuringUnintallation(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolFeatureSkipDuringUnintallation,METH_VARARGS,
     "listMatrixToolFeatureSkipDuringUnintallation() - list all the records in the MatrixTool wind profile feature map"},
    {"addMatrixToolProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddMatrixToolProducer, METH_VARARGS,
     "addMatrixToolProducer(key,value) - add a record to the MatrixTool wind profile feature  map"},
    {"getMatrixToolProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetMatrixToolProducer, METH_VARARGS,
     "getMatrixToolProducer(key) - get a record from the MatrixTool wind profile feature map"},
    {"listMatrixToolProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListMatrixToolProducer, METH_VARARGS,
     "listMatrixToolProducer() - list all the records in the MatrixTool wind profile feature map"},
    {"removeMatrixToolProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveMatrixToolProducer,METH_VARARGS,
     "removeMatrixToolProducer(name) - list all the records in the MatrixTool wind profile feature map"},
    {"produceMatrixTool", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceMatrixTool, METH_VARARGS,
     "produceMatrixTool(name) - list all the records in the MatrixTool wind profile feature map"},




    {"addUserDefinedRPSObjectAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectAuthor, METH_VARARGS,
     "addUserDefinedRPSObjectAuthor(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectAuthor, METH_VARARGS,
     "getUserDefinedRPSObjectAuthor(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectAuthor, METH_VARARGS,
     "listUserDefinedRPSObjectAuthor() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"addUserDefinedRPSObjectToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectToBeInstalledFeature, METH_VARARGS,
     "addUserDefinedRPSObjectToBeInstalledFeature(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectToBeInstalledFeature, METH_VARARGS,
     "getUserDefinedRPSObjectToBeInstalledFeature(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectToBeInstalledFeature, METH_VARARGS,
     "listUserDefinedRPSObjectToBeInstalledFeature() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"addUserDefinedRPSObjectFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectFeatureDescription, METH_VARARGS,
     "addUserDefinedRPSObjectFeatureDescription(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectFeatureDescription, METH_VARARGS,
     "getUserDefinedRPSObjectFeatureDescription(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectFeatureDescription, METH_VARARGS,
     "listUserDefinedRPSObjectFeatureDescription() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"removeUserDefinedRPSObjectFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveUserDefinedRPSObjectFeatureDescription, METH_VARARGS,
     "removeUserDefinedRPSObjectFeatureDescription(name) - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"addUserDefinedRPSObjectPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectPlugin, METH_VARARGS,
     "addUserDefinedRPSObjectPlugin(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectPlugin, METH_VARARGS,
     "getUserDefinedRPSObjectPlugin(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectPlugin, METH_VARARGS,
     "listUserDefinedRPSObjectPlugin() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"removeUserDefinedRPSObjectPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveUserDefinedRPSObjectPlugin, METH_VARARGS,
     "removeUserDefinedRPSObjectPlugin(name) - remove a UserDefinedRPSObject wind profile distribution record from feature map"},
    {"addUserDefinedRPSObjectTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectTitle, METH_VARARGS,
     "addUserDefinedRPSObjectTitle(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectTitle, METH_VARARGS,
     "getUserDefinedRPSObjectTitle(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectTitle, METH_VARARGS,
     "listUserDefinedRPSObjectTitle() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"addUserDefinedRPSObjectLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectLink, METH_VARARGS,
     "addUserDefinedRPSObjectLink(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectLink, METH_VARARGS,
     "getUserDefinedRPSObjectLink(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectLink, METH_VARARGS,
     "listUserDefinedRPSObjectLink() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"addUserDefinedRPSObjectDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectDate, METH_VARARGS,
     "addUserDefinedRPSObjectDate(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectDate, METH_VARARGS,
     "getUserDefinedRPSObjectDate(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectDate, METH_VARARGS,
     "listUserDefinedRPSObjectDate() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"addUserDefinedRPSObjectVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectVersion, METH_VARARGS,
     "addUserDefinedRPSObjectVersion(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectVersion, METH_VARARGS,
     "getUserDefinedRPSObjectVersion(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectVersion, METH_VARARGS,
     "listUserDefinedRPSObjectVersion() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"addUserDefinedRPSObjectFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectFeatureSkipDuringUnintallation,METH_VARARGS,
     "addUserDefinedRPSObjectFeatureSkipDuringUnintallation(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectFeatureSkipDuringUnintallation, METH_VARARGS,
     "getUserDefinedRPSObjectFeatureSkipDuringUnintallation(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectFeatureSkipDuringUnintallation,METH_VARARGS,
     "listUserDefinedRPSObjectFeatureSkipDuringUnintallation() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"addUserDefinedRPSObjectProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddUserDefinedRPSObjectProducer, METH_VARARGS,
     "addUserDefinedRPSObjectProducer(key,value) - add a record to the UserDefinedRPSObject wind profile feature  map"},
    {"getUserDefinedRPSObjectProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetUserDefinedRPSObjectProducer, METH_VARARGS,
     "getUserDefinedRPSObjectProducer(key) - get a record from the UserDefinedRPSObject wind profile feature map"},
    {"listUserDefinedRPSObjectProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListUserDefinedRPSObjectProducer, METH_VARARGS,
     "listUserDefinedRPSObjectProducer() - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"removeUserDefinedRPSObjectProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveUserDefinedRPSObjectProducer,METH_VARARGS,
     "removeUserDefinedRPSObjectProducer(name) - list all the records in the UserDefinedRPSObject wind profile feature map"},
    {"produceUserDefinedRPSObject", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceUserDefinedRPSObject, METH_VARARGS,
     "produceUserDefinedRPSObject(name) - list all the records in the UserDefinedRPSObject wind profile feature map"},



    {"addCumulativeProbabilityDistributionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionAuthor, METH_VARARGS,
     "addCumulativeProbabilityDistributionAuthor(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionAuthor, METH_VARARGS,
     "getCumulativeProbabilityDistributionAuthor(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionAuthor, METH_VARARGS,
     "listCumulativeProbabilityDistributionAuthor() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"addCumulativeProbabilityDistributionToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionToBeInstalledFeature, METH_VARARGS,
     "addCumulativeProbabilityDistributionToBeInstalledFeature(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionToBeInstalledFeature, METH_VARARGS,
     "getCumulativeProbabilityDistributionToBeInstalledFeature(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionToBeInstalledFeature, METH_VARARGS,
     "listCumulativeProbabilityDistributionToBeInstalledFeature() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"addCumulativeProbabilityDistributionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionFeatureDescription, METH_VARARGS,
     "addCumulativeProbabilityDistributionFeatureDescription(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionFeatureDescription, METH_VARARGS,
     "getCumulativeProbabilityDistributionFeatureDescription(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionFeatureDescription, METH_VARARGS,
     "listCumulativeProbabilityDistributionFeatureDescription() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"removeCumulativeProbabilityDistributionFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveCumulativeProbabilityDistributionFeatureDescription, METH_VARARGS,
     "removeCumulativeProbabilityDistributionFeatureDescription(name) - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"addCumulativeProbabilityDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionPlugin, METH_VARARGS,
     "addCumulativeProbabilityDistributionPlugin(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionPlugin, METH_VARARGS,
     "getCumulativeProbabilityDistributionPlugin(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionPlugin, METH_VARARGS,
     "listCumulativeProbabilityDistributionPlugin() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"removeCumulativeProbabilityDistributionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveCumulativeProbabilityDistributionPlugin, METH_VARARGS,
     "removeCumulativeProbabilityDistributionPlugin(name) - remove a CumulativeProbabilityDistribution wind profile distribution record from feature map"},
    {"addCumulativeProbabilityDistributionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionTitle, METH_VARARGS,
     "addCumulativeProbabilityDistributionTitle(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionTitle, METH_VARARGS,
     "getCumulativeProbabilityDistributionTitle(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionTitle, METH_VARARGS,
     "listCumulativeProbabilityDistributionTitle() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"addCumulativeProbabilityDistributionLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionLink, METH_VARARGS,
     "addCumulativeProbabilityDistributionLink(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionLink, METH_VARARGS,
     "getCumulativeProbabilityDistributionLink(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionLink, METH_VARARGS,
     "listCumulativeProbabilityDistributionLink() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"addCumulativeProbabilityDistributionDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionDate, METH_VARARGS,
     "addCumulativeProbabilityDistributionDate(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionDate, METH_VARARGS,
     "getCumulativeProbabilityDistributionDate(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionDate, METH_VARARGS,
     "listCumulativeProbabilityDistributionDate() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"addCumulativeProbabilityDistributionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionVersion, METH_VARARGS,
     "addCumulativeProbabilityDistributionVersion(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionVersion, METH_VARARGS,
     "getCumulativeProbabilityDistributionVersion(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionVersion, METH_VARARGS,
     "listCumulativeProbabilityDistributionVersion() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"addCumulativeProbabilityDistributionFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionFeatureSkipDuringUnintallation,METH_VARARGS,
     "addCumulativeProbabilityDistributionFeatureSkipDuringUnintallation(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionFeatureSkipDuringUnintallation, METH_VARARGS,
     "getCumulativeProbabilityDistributionFeatureSkipDuringUnintallation(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionFeatureSkipDuringUnintallation,METH_VARARGS,
     "listCumulativeProbabilityDistributionFeatureSkipDuringUnintallation() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"addCumulativeProbabilityDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddCumulativeProbabilityDistributionProducer, METH_VARARGS,
     "addCumulativeProbabilityDistributionProducer(key,value) - add a record to the CumulativeProbabilityDistribution wind profile feature  map"},
    {"getCumulativeProbabilityDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetCumulativeProbabilityDistributionProducer, METH_VARARGS,
     "getCumulativeProbabilityDistributionProducer(key) - get a record from the CumulativeProbabilityDistribution wind profile feature map"},
    {"listCumulativeProbabilityDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListCumulativeProbabilityDistributionProducer, METH_VARARGS,
     "listCumulativeProbabilityDistributionProducer() - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"removeCumulativeProbabilityDistributionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveCumulativeProbabilityDistributionProducer,METH_VARARGS,
     "removeCumulativeProbabilityDistributionProducer(name) - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},
    {"produceCumulativeProbabilityDistribution", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceCumulativeProbabilityDistribution, METH_VARARGS,
     "produceCumulativeProbabilityDistribution(name) - list all the records in the CumulativeProbabilityDistribution wind profile feature map"},



     {"addGustFactorAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorAuthor, METH_VARARGS,
     "addGustFactorAuthor(key,value) - add a record to the GustFactor feature map"},
    {"getGustFactorAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorAuthor, METH_VARARGS,
     "getGustFactorAuthor(key) - get a record from the GustFactor feature map"},
    {"listGustFactorAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorAuthor, METH_VARARGS,
     "listGustFactorAuthor() - list all the records in the GustFactor feature map"},
    {"addGustFactorToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorToBeInstalledFeature, METH_VARARGS,
     "addGustFactorToBeInstalledFeature(key,value) - add a record to the GustFactor wind profile feature  map"},
    {"getGustFactorToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorToBeInstalledFeature, METH_VARARGS,
     "getGustFactorToBeInstalledFeature(key) - get a record from the GustFactor wind profile feature map"},
    {"listGustFactorToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorToBeInstalledFeature, METH_VARARGS,
     "listGustFactorToBeInstalledFeature() - list all the records in the GustFactor wind profile feature map"},
    {"addGustFactorFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorFeatureDescription, METH_VARARGS,
     "addGustFactorFeatureDescription(key,value) - add a record to the GustFactor wind profile feature  map"},
    {"getGustFactorFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorFeatureDescription, METH_VARARGS,
     "getGustFactorFeatureDescription(key) - get a record from the GustFactor wind profile feature map"},
    {"listGustFactorFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorFeatureDescription, METH_VARARGS,
     "listGustFactorFeatureDescription() - list all the records in the GustFactor wind profile feature map"},
    {"removeGustFactorFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveGustFactorFeatureDescription, METH_VARARGS,
     "removeGustFactorFeatureDescription(name) - list all the records in the GustFactor wind profile feature map"},
    {"addGustFactorPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorPlugin, METH_VARARGS,
     "addGustFactorPlugin(key,value) - add a record to the GustFactor wind profile feature  map"},
    {"getGustFactorPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorPlugin, METH_VARARGS,
     "getGustFactorPlugin(key) - get a record from the GustFactor wind profile feature map"},
    {"listGustFactorPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorPlugin, METH_VARARGS,
     "listGustFactorPlugin() - list all the records in the GustFactor wind profile feature map"},
    {"removeGustFactorPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveGustFactorPlugin, METH_VARARGS,
     "removeGustFactorPlugin(name) - remove a GustFactor wind profile distribution record from feature map"},
    {"addGustFactorTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorTitle, METH_VARARGS,
     "addGustFactorTitle(key,value) - add a record to the GustFactor wind profile feature  map"},
    {"getGustFactorTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorTitle, METH_VARARGS,
     "getGustFactorTitle(key) - get a record from the GustFactor wind profile feature map"},
    {"listGustFactorTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorTitle, METH_VARARGS,
     "listGustFactorTitle() - list all the records in the GustFactor wind profile feature map"},
    {"addGustFactorLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorLink, METH_VARARGS,
     "addGustFactorLink(key,value) - add a record to the GustFactor wind profile feature  map"},
    {"getGustFactorLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorLink, METH_VARARGS,
     "getGustFactorLink(key) - get a record from the GustFactor wind profile feature map"},
    {"listGustFactorLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorLink, METH_VARARGS,
     "listGustFactorLink() - list all the records in the GustFactor wind profile feature map"},
    {"addGustFactorDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorDate, METH_VARARGS,
     "addGustFactorDate(key,value) - add a record to the GustFactor wind profile feature  map"},
    {"getGustFactorDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorDate, METH_VARARGS,
     "getGustFactorDate(key) - get a record from the GustFactor wind profile feature map"},
    {"listGustFactorDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorDate, METH_VARARGS,
     "listGustFactorDate() - list all the records in the GustFactor wind profile feature map"},
    {"addGustFactorVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorVersion, METH_VARARGS,
     "addGustFactorVersion(key,value) - add a record to the GustFactor wind profile feature  map"},
    {"getGustFactorVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorVersion, METH_VARARGS,
     "getGustFactorVersion(key) - get a record from the GustFactor wind profile feature map"},
    {"listGustFactorVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorVersion, METH_VARARGS,
     "listGustFactorVersion() - list all the records in the GustFactor wind profile feature map"},
    {"addGustFactorFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorFeatureSkipDuringUnintallation,METH_VARARGS,
     "addGustFactorFeatureSkipDuringUnintallation(key,value) - add a record to the GustFactor wind profile feature  map"},
    {"getGustFactorFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorFeatureSkipDuringUnintallation, METH_VARARGS,
     "getGustFactorFeatureSkipDuringUnintallation(key) - get a record from the GustFactor wind profile feature map"},
    {"listGustFactorFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorFeatureSkipDuringUnintallation,METH_VARARGS,
     "listGustFactorFeatureSkipDuringUnintallation() - list all the records in the GustFactor wind profile feature map"},
    {"addGustFactorProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddGustFactorProducer, METH_VARARGS,
     "addGustFactorProducer(key,value) - add a record to the GustFactor wind profile feature  map"},
    {"getGustFactorProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetGustFactorProducer, METH_VARARGS,
     "getGustFactorProducer(key) - get a record from the GustFactor wind profile feature map"},
    {"listGustFactorProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListGustFactorProducer, METH_VARARGS,
     "listGustFactorProducer() - list all the records in the GustFactor wind profile feature map"},
    {"removeGustFactorProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveGustFactorProducer,METH_VARARGS,
     "removeGustFactorProducer(name) - list all the records in the GustFactor wind profile feature map"},
    {"produceGustFactor", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceGustFactor, METH_VARARGS,
     "produceGustFactor(name) - list all the records in the GustFactor wind profile feature map"},



     {"addKurtosisAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisAuthor, METH_VARARGS,
     "addKurtosisAuthor(key,value) - add a record to the Kurtosis feature map"},
    {"getKurtosisAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisAuthor, METH_VARARGS,
     "getKurtosisAuthor(key) - get a record from the Kurtosis feature map"},
    {"listKurtosisAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisAuthor, METH_VARARGS,
     "listKurtosisAuthor() - list all the records in the Kurtosis feature map"},
    {"addKurtosisToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisToBeInstalledFeature, METH_VARARGS,
     "addKurtosisToBeInstalledFeature(key,value) - add a record to the Kurtosis wind profile feature  map"},
    {"getKurtosisToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisToBeInstalledFeature, METH_VARARGS,
     "getKurtosisToBeInstalledFeature(key) - get a record from the Kurtosis wind profile feature map"},
    {"listKurtosisToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisToBeInstalledFeature, METH_VARARGS,
     "listKurtosisToBeInstalledFeature() - list all the records in the Kurtosis wind profile feature map"},
    {"addKurtosisFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisFeatureDescription, METH_VARARGS,
     "addKurtosisFeatureDescription(key,value) - add a record to the Kurtosis wind profile feature  map"},
    {"getKurtosisFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisFeatureDescription, METH_VARARGS,
     "getKurtosisFeatureDescription(key) - get a record from the Kurtosis wind profile feature map"},
    {"listKurtosisFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisFeatureDescription, METH_VARARGS,
     "listKurtosisFeatureDescription() - list all the records in the Kurtosis wind profile feature map"},
    {"removeKurtosisFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveKurtosisFeatureDescription, METH_VARARGS,
     "removeKurtosisFeatureDescription(name) - list all the records in the Kurtosis wind profile feature map"},
    {"addKurtosisPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisPlugin, METH_VARARGS,
     "addKurtosisPlugin(key,value) - add a record to the Kurtosis wind profile feature  map"},
    {"getKurtosisPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisPlugin, METH_VARARGS,
     "getKurtosisPlugin(key) - get a record from the Kurtosis wind profile feature map"},
    {"listKurtosisPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisPlugin, METH_VARARGS,
     "listKurtosisPlugin() - list all the records in the Kurtosis wind profile feature map"},
    {"removeKurtosisPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveKurtosisPlugin, METH_VARARGS,
     "removeKurtosisPlugin(name) - remove a Kurtosis wind profile distribution record from feature map"},
    {"addKurtosisTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisTitle, METH_VARARGS,
     "addKurtosisTitle(key,value) - add a record to the Kurtosis wind profile feature  map"},
    {"getKurtosisTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisTitle, METH_VARARGS,
     "getKurtosisTitle(key) - get a record from the Kurtosis wind profile feature map"},
    {"listKurtosisTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisTitle, METH_VARARGS,
     "listKurtosisTitle() - list all the records in the Kurtosis wind profile feature map"},
    {"addKurtosisLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisLink, METH_VARARGS,
     "addKurtosisLink(key,value) - add a record to the Kurtosis wind profile feature  map"},
    {"getKurtosisLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisLink, METH_VARARGS,
     "getKurtosisLink(key) - get a record from the Kurtosis wind profile feature map"},
    {"listKurtosisLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisLink, METH_VARARGS,
     "listKurtosisLink() - list all the records in the Kurtosis wind profile feature map"},
    {"addKurtosisDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisDate, METH_VARARGS,
     "addKurtosisDate(key,value) - add a record to the Kurtosis wind profile feature  map"},
    {"getKurtosisDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisDate, METH_VARARGS,
     "getKurtosisDate(key) - get a record from the Kurtosis wind profile feature map"},
    {"listKurtosisDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisDate, METH_VARARGS,
     "listKurtosisDate() - list all the records in the Kurtosis wind profile feature map"},
    {"addKurtosisVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisVersion, METH_VARARGS,
     "addKurtosisVersion(key,value) - add a record to the Kurtosis wind profile feature  map"},
    {"getKurtosisVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisVersion, METH_VARARGS,
     "getKurtosisVersion(key) - get a record from the Kurtosis wind profile feature map"},
    {"listKurtosisVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisVersion, METH_VARARGS,
     "listKurtosisVersion() - list all the records in the Kurtosis wind profile feature map"},
    {"addKurtosisFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisFeatureSkipDuringUnintallation,METH_VARARGS,
     "addKurtosisFeatureSkipDuringUnintallation(key,value) - add a record to the Kurtosis wind profile feature  map"},
    {"getKurtosisFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisFeatureSkipDuringUnintallation, METH_VARARGS,
     "getKurtosisFeatureSkipDuringUnintallation(key) - get a record from the Kurtosis wind profile feature map"},
    {"listKurtosisFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisFeatureSkipDuringUnintallation,METH_VARARGS,
     "listKurtosisFeatureSkipDuringUnintallation() - list all the records in the Kurtosis wind profile feature map"},
    {"addKurtosisProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddKurtosisProducer, METH_VARARGS,
     "addKurtosisProducer(key,value) - add a record to the Kurtosis wind profile feature  map"},
    {"getKurtosisProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetKurtosisProducer, METH_VARARGS,
     "getKurtosisProducer(key) - get a record from the Kurtosis wind profile feature map"},
    {"listKurtosisProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListKurtosisProducer, METH_VARARGS,
     "listKurtosisProducer() - list all the records in the Kurtosis wind profile feature map"},
    {"removeKurtosisProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveKurtosisProducer,METH_VARARGS,
     "removeKurtosisProducer(name) - list all the records in the Kurtosis wind profile feature map"},
    {"produceKurtosis", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceKurtosis, METH_VARARGS,
     "produceKurtosis(name) - list all the records in the Kurtosis wind profile feature map"},




    {"addPeakFactorAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorAuthor, METH_VARARGS,
     "addPeakFactorAuthor(key,value) - add a record to the PeakFactor feature map"},
    {"getPeakFactorAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorAuthor, METH_VARARGS,
     "getPeakFactorAuthor(key) - get a record from the PeakFactor feature map"},
    {"listPeakFactorAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorAuthor, METH_VARARGS,
     "listPeakFactorAuthor() - list all the records in the PeakFactor feature map"},
    {"addPeakFactorToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorToBeInstalledFeature, METH_VARARGS,
     "addPeakFactorToBeInstalledFeature(key,value) - add a record to the PeakFactor wind profile feature  map"},
    {"getPeakFactorToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorToBeInstalledFeature, METH_VARARGS,
     "getPeakFactorToBeInstalledFeature(key) - get a record from the PeakFactor wind profile feature map"},
    {"listPeakFactorToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorToBeInstalledFeature, METH_VARARGS,
     "listPeakFactorToBeInstalledFeature() - list all the records in the PeakFactor wind profile feature map"},
    {"addPeakFactorFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorFeatureDescription, METH_VARARGS,
     "addPeakFactorFeatureDescription(key,value) - add a record to the PeakFactor wind profile feature  map"},
    {"getPeakFactorFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorFeatureDescription, METH_VARARGS,
     "getPeakFactorFeatureDescription(key) - get a record from the PeakFactor wind profile feature map"},
    {"listPeakFactorFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorFeatureDescription, METH_VARARGS,
     "listPeakFactorFeatureDescription() - list all the records in the PeakFactor wind profile feature map"},
    {"removePeakFactorFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemovePeakFactorFeatureDescription, METH_VARARGS,
     "removePeakFactorFeatureDescription(name) - list all the records in the PeakFactor wind profile feature map"},
    {"addPeakFactorPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorPlugin, METH_VARARGS,
     "addPeakFactorPlugin(key,value) - add a record to the PeakFactor wind profile feature  map"},
    {"getPeakFactorPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorPlugin, METH_VARARGS,
     "getPeakFactorPlugin(key) - get a record from the PeakFactor wind profile feature map"},
    {"listPeakFactorPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorPlugin, METH_VARARGS,
     "listPeakFactorPlugin() - list all the records in the PeakFactor wind profile feature map"},
    {"removePeakFactorPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemovePeakFactorPlugin, METH_VARARGS,
     "removePeakFactorPlugin(name) - remove a PeakFactor wind profile distribution record from feature map"},
    {"addPeakFactorTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorTitle, METH_VARARGS,
     "addPeakFactorTitle(key,value) - add a record to the PeakFactor wind profile feature  map"},
    {"getPeakFactorTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorTitle, METH_VARARGS,
     "getPeakFactorTitle(key) - get a record from the PeakFactor wind profile feature map"},
    {"listPeakFactorTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorTitle, METH_VARARGS,
     "listPeakFactorTitle() - list all the records in the PeakFactor wind profile feature map"},
    {"addPeakFactorLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorLink, METH_VARARGS,
     "addPeakFactorLink(key,value) - add a record to the PeakFactor wind profile feature  map"},
    {"getPeakFactorLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorLink, METH_VARARGS,
     "getPeakFactorLink(key) - get a record from the PeakFactor wind profile feature map"},
    {"listPeakFactorLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorLink, METH_VARARGS,
     "listPeakFactorLink() - list all the records in the PeakFactor wind profile feature map"},
    {"addPeakFactorDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorDate, METH_VARARGS,
     "addPeakFactorDate(key,value) - add a record to the PeakFactor wind profile feature  map"},
    {"getPeakFactorDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorDate, METH_VARARGS,
     "getPeakFactorDate(key) - get a record from the PeakFactor wind profile feature map"},
    {"listPeakFactorDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorDate, METH_VARARGS,
     "listPeakFactorDate() - list all the records in the PeakFactor wind profile feature map"},
    {"addPeakFactorVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorVersion, METH_VARARGS,
     "addPeakFactorVersion(key,value) - add a record to the PeakFactor wind profile feature  map"},
    {"getPeakFactorVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorVersion, METH_VARARGS,
     "getPeakFactorVersion(key) - get a record from the PeakFactor wind profile feature map"},
    {"listPeakFactorVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorVersion, METH_VARARGS,
     "listPeakFactorVersion() - list all the records in the PeakFactor wind profile feature map"},
    {"addPeakFactorFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorFeatureSkipDuringUnintallation,METH_VARARGS,
     "addPeakFactorFeatureSkipDuringUnintallation(key,value) - add a record to the PeakFactor wind profile feature  map"},
    {"getPeakFactorFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorFeatureSkipDuringUnintallation, METH_VARARGS,
     "getPeakFactorFeatureSkipDuringUnintallation(key) - get a record from the PeakFactor wind profile feature map"},
    {"listPeakFactorFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorFeatureSkipDuringUnintallation,METH_VARARGS,
     "listPeakFactorFeatureSkipDuringUnintallation() - list all the records in the PeakFactor wind profile feature map"},
    {"addPeakFactorProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddPeakFactorProducer, METH_VARARGS,
     "addPeakFactorProducer(key,value) - add a record to the PeakFactor wind profile feature  map"},
    {"getPeakFactorProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetPeakFactorProducer, METH_VARARGS,
     "getPeakFactorProducer(key) - get a record from the PeakFactor wind profile feature map"},
    {"listPeakFactorProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListPeakFactorProducer, METH_VARARGS,
     "listPeakFactorProducer() - list all the records in the PeakFactor wind profile feature map"},
    {"removePeakFactorProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemovePeakFactorProducer,METH_VARARGS,
     "removePeakFactorProducer(name) - list all the records in the PeakFactor wind profile feature map"},
    {"producePeakFactor", (PyCFunction)RPSWindLabPythonPluginFactory::ProducePeakFactor, METH_VARARGS,
     "producePeakFactor(name) - list all the records in the PeakFactor wind profile feature map"},



     {"addProbabilityDensityFunctionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionAuthor, METH_VARARGS,
     "addProbabilityDensityFunctionAuthor(key,value) - add a record to the ProbabilityDensityFunction feature map"},
    {"getProbabilityDensityFunctionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionAuthor, METH_VARARGS,
     "getProbabilityDensityFunctionAuthor(key) - get a record from the ProbabilityDensityFunction feature map"},
    {"listProbabilityDensityFunctionAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionAuthor, METH_VARARGS,
     "listProbabilityDensityFunctionAuthor() - list all the records in the ProbabilityDensityFunction feature map"},
    {"addProbabilityDensityFunctionToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionToBeInstalledFeature, METH_VARARGS,
     "addProbabilityDensityFunctionToBeInstalledFeature(key,value) - add a record to the ProbabilityDensityFunction wind profile feature  map"},
    {"getProbabilityDensityFunctionToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionToBeInstalledFeature, METH_VARARGS,
     "getProbabilityDensityFunctionToBeInstalledFeature(key) - get a record from the ProbabilityDensityFunction wind profile feature map"},
    {"listProbabilityDensityFunctionToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionToBeInstalledFeature, METH_VARARGS,
     "listProbabilityDensityFunctionToBeInstalledFeature() - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"addProbabilityDensityFunctionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionFeatureDescription, METH_VARARGS,
     "addProbabilityDensityFunctionFeatureDescription(key,value) - add a record to the ProbabilityDensityFunction wind profile feature  map"},
    {"getProbabilityDensityFunctionFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionFeatureDescription, METH_VARARGS,
     "getProbabilityDensityFunctionFeatureDescription(key) - get a record from the ProbabilityDensityFunction wind profile feature map"},
    {"listProbabilityDensityFunctionFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionFeatureDescription, METH_VARARGS,
     "listProbabilityDensityFunctionFeatureDescription() - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"removeProbabilityDensityFunctionFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveProbabilityDensityFunctionFeatureDescription, METH_VARARGS,
     "removeProbabilityDensityFunctionFeatureDescription(name) - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"addProbabilityDensityFunctionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionPlugin, METH_VARARGS,
     "addProbabilityDensityFunctionPlugin(key,value) - add a record to the ProbabilityDensityFunction wind profile feature  map"},
    {"getProbabilityDensityFunctionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionPlugin, METH_VARARGS,
     "getProbabilityDensityFunctionPlugin(key) - get a record from the ProbabilityDensityFunction wind profile feature map"},
    {"listProbabilityDensityFunctionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionPlugin, METH_VARARGS,
     "listProbabilityDensityFunctionPlugin() - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"removeProbabilityDensityFunctionPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveProbabilityDensityFunctionPlugin, METH_VARARGS,
     "removeProbabilityDensityFunctionPlugin(name) - remove a ProbabilityDensityFunction wind profile distribution record from feature map"},
    {"addProbabilityDensityFunctionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionTitle, METH_VARARGS,
     "addProbabilityDensityFunctionTitle(key,value) - add a record to the ProbabilityDensityFunction wind profile feature  map"},
    {"getProbabilityDensityFunctionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionTitle, METH_VARARGS,
     "getProbabilityDensityFunctionTitle(key) - get a record from the ProbabilityDensityFunction wind profile feature map"},
    {"listProbabilityDensityFunctionTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionTitle, METH_VARARGS,
     "listProbabilityDensityFunctionTitle() - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"addProbabilityDensityFunctionLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionLink, METH_VARARGS,
     "addProbabilityDensityFunctionLink(key,value) - add a record to the ProbabilityDensityFunction wind profile feature  map"},
    {"getProbabilityDensityFunctionLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionLink, METH_VARARGS,
     "getProbabilityDensityFunctionLink(key) - get a record from the ProbabilityDensityFunction wind profile feature map"},
    {"listProbabilityDensityFunctionLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionLink, METH_VARARGS,
     "listProbabilityDensityFunctionLink() - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"addProbabilityDensityFunctionDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionDate, METH_VARARGS,
     "addProbabilityDensityFunctionDate(key,value) - add a record to the ProbabilityDensityFunction wind profile feature  map"},
    {"getProbabilityDensityFunctionDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionDate, METH_VARARGS,
     "getProbabilityDensityFunctionDate(key) - get a record from the ProbabilityDensityFunction wind profile feature map"},
    {"listProbabilityDensityFunctionDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionDate, METH_VARARGS,
     "listProbabilityDensityFunctionDate() - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"addProbabilityDensityFunctionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionVersion, METH_VARARGS,
     "addProbabilityDensityFunctionVersion(key,value) - add a record to the ProbabilityDensityFunction wind profile feature  map"},
    {"getProbabilityDensityFunctionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionVersion, METH_VARARGS,
     "getProbabilityDensityFunctionVersion(key) - get a record from the ProbabilityDensityFunction wind profile feature map"},
    {"listProbabilityDensityFunctionVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionVersion, METH_VARARGS,
     "listProbabilityDensityFunctionVersion() - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"addProbabilityDensityFunctionFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionFeatureSkipDuringUnintallation,METH_VARARGS,
     "addProbabilityDensityFunctionFeatureSkipDuringUnintallation(key,value) - add a record to the ProbabilityDensityFunction wind profile feature  map"},
    {"getProbabilityDensityFunctionFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionFeatureSkipDuringUnintallation, METH_VARARGS,
     "getProbabilityDensityFunctionFeatureSkipDuringUnintallation(key) - get a record from the ProbabilityDensityFunction wind profile feature map"},
    {"listProbabilityDensityFunctionFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionFeatureSkipDuringUnintallation,METH_VARARGS,
     "listProbabilityDensityFunctionFeatureSkipDuringUnintallation() - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"addProbabilityDensityFunctionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddProbabilityDensityFunctionProducer, METH_VARARGS,
     "addProbabilityDensityFunctionProducer(key,value) - add a record to the ProbabilityDensityFunction wind profile feature  map"},
    {"getProbabilityDensityFunctionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetProbabilityDensityFunctionProducer, METH_VARARGS,
     "getProbabilityDensityFunctionProducer(key) - get a record from the ProbabilityDensityFunction wind profile feature map"},
    {"listProbabilityDensityFunctionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListProbabilityDensityFunctionProducer, METH_VARARGS,
     "listProbabilityDensityFunctionProducer() - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"removeProbabilityDensityFunctionProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveProbabilityDensityFunctionProducer,METH_VARARGS,
     "removeProbabilityDensityFunctionProducer(name) - list all the records in the ProbabilityDensityFunction wind profile feature map"},
    {"produceProbabilityDensityFunction", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceProbabilityDensityFunction, METH_VARARGS,
     "produceProbabilityDensityFunction(name) - list all the records in the ProbabilityDensityFunction wind profile feature map"},



     {"addRoughnessAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessAuthor, METH_VARARGS,
     "addRoughnessAuthor(key,value) - add a record to the Roughness feature map"},
    {"getRoughnessAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessAuthor, METH_VARARGS,
     "getRoughnessAuthor(key) - get a record from the Roughness feature map"},
    {"listRoughnessAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessAuthor, METH_VARARGS,
     "listRoughnessAuthor() - list all the records in the Roughness feature map"},
    {"addRoughnessToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessToBeInstalledFeature, METH_VARARGS,
     "addRoughnessToBeInstalledFeature(key,value) - add a record to the Roughness wind profile feature  map"},
    {"getRoughnessToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessToBeInstalledFeature, METH_VARARGS,
     "getRoughnessToBeInstalledFeature(key) - get a record from the Roughness wind profile feature map"},
    {"listRoughnessToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessToBeInstalledFeature, METH_VARARGS,
     "listRoughnessToBeInstalledFeature() - list all the records in the Roughness wind profile feature map"},
    {"addRoughnessFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessFeatureDescription, METH_VARARGS,
     "addRoughnessFeatureDescription(key,value) - add a record to the Roughness wind profile feature  map"},
    {"getRoughnessFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessFeatureDescription, METH_VARARGS,
     "getRoughnessFeatureDescription(key) - get a record from the Roughness wind profile feature map"},
    {"listRoughnessFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessFeatureDescription, METH_VARARGS,
     "listRoughnessFeatureDescription() - list all the records in the Roughness wind profile feature map"},
    {"removeRoughnessFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveRoughnessFeatureDescription, METH_VARARGS,
     "removeRoughnessFeatureDescription(name) - list all the records in the Roughness wind profile feature map"},
    {"addRoughnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessPlugin, METH_VARARGS,
     "addRoughnessPlugin(key,value) - add a record to the Roughness wind profile feature  map"},
    {"getRoughnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessPlugin, METH_VARARGS,
     "getRoughnessPlugin(key) - get a record from the Roughness wind profile feature map"},
    {"listRoughnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessPlugin, METH_VARARGS,
     "listRoughnessPlugin() - list all the records in the Roughness wind profile feature map"},
    {"removeRoughnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveRoughnessPlugin, METH_VARARGS,
     "removeRoughnessPlugin(name) - remove a Roughness wind profile distribution record from feature map"},
    {"addRoughnessTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessTitle, METH_VARARGS,
     "addRoughnessTitle(key,value) - add a record to the Roughness wind profile feature  map"},
    {"getRoughnessTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessTitle, METH_VARARGS,
     "getRoughnessTitle(key) - get a record from the Roughness wind profile feature map"},
    {"listRoughnessTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessTitle, METH_VARARGS,
     "listRoughnessTitle() - list all the records in the Roughness wind profile feature map"},
    {"addRoughnessLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessLink, METH_VARARGS,
     "addRoughnessLink(key,value) - add a record to the Roughness wind profile feature  map"},
    {"getRoughnessLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessLink, METH_VARARGS,
     "getRoughnessLink(key) - get a record from the Roughness wind profile feature map"},
    {"listRoughnessLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessLink, METH_VARARGS,
     "listRoughnessLink() - list all the records in the Roughness wind profile feature map"},
    {"addRoughnessDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessDate, METH_VARARGS,
     "addRoughnessDate(key,value) - add a record to the Roughness wind profile feature  map"},
    {"getRoughnessDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessDate, METH_VARARGS,
     "getRoughnessDate(key) - get a record from the Roughness wind profile feature map"},
    {"listRoughnessDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessDate, METH_VARARGS,
     "listRoughnessDate() - list all the records in the Roughness wind profile feature map"},
    {"addRoughnessVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessVersion, METH_VARARGS,
     "addRoughnessVersion(key,value) - add a record to the Roughness wind profile feature  map"},
    {"getRoughnessVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessVersion, METH_VARARGS,
     "getRoughnessVersion(key) - get a record from the Roughness wind profile feature map"},
    {"listRoughnessVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessVersion, METH_VARARGS,
     "listRoughnessVersion() - list all the records in the Roughness wind profile feature map"},
    {"addRoughnessFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessFeatureSkipDuringUnintallation,METH_VARARGS,
     "addRoughnessFeatureSkipDuringUnintallation(key,value) - add a record to the Roughness wind profile feature  map"},
    {"getRoughnessFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessFeatureSkipDuringUnintallation, METH_VARARGS,
     "getRoughnessFeatureSkipDuringUnintallation(key) - get a record from the Roughness wind profile feature map"},
    {"listRoughnessFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessFeatureSkipDuringUnintallation,METH_VARARGS,
     "listRoughnessFeatureSkipDuringUnintallation() - list all the records in the Roughness wind profile feature map"},
    {"addRoughnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddRoughnessProducer, METH_VARARGS,
     "addRoughnessProducer(key,value) - add a record to the Roughness wind profile feature  map"},
    {"getRoughnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetRoughnessProducer, METH_VARARGS,
     "getRoughnessProducer(key) - get a record from the Roughness wind profile feature map"},
    {"listRoughnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListRoughnessProducer, METH_VARARGS,
     "listRoughnessProducer() - list all the records in the Roughness wind profile feature map"},
    {"removeRoughnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveRoughnessProducer,METH_VARARGS,
     "removeRoughnessProducer(name) - list all the records in the Roughness wind profile feature map"},
    {"produceRoughness", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceRoughness, METH_VARARGS,
     "produceRoughness(name) - list all the records in the Roughness wind profile feature map"},


     {"addShearVelocityOfFlowAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowAuthor, METH_VARARGS,
     "addShearVelocityOfFlowAuthor(key,value) - add a record to the ShearVelocityOfFlow feature map"},
    {"getShearVelocityOfFlowAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowAuthor, METH_VARARGS,
     "getShearVelocityOfFlowAuthor(key) - get a record from the ShearVelocityOfFlow feature map"},
    {"listShearVelocityOfFlowAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowAuthor, METH_VARARGS,
     "listShearVelocityOfFlowAuthor() - list all the records in the ShearVelocityOfFlow feature map"},
    {"addShearVelocityOfFlowToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowToBeInstalledFeature, METH_VARARGS,
     "addShearVelocityOfFlowToBeInstalledFeature(key,value) - add a record to the ShearVelocityOfFlow wind profile feature  map"},
    {"getShearVelocityOfFlowToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowToBeInstalledFeature, METH_VARARGS,
     "getShearVelocityOfFlowToBeInstalledFeature(key) - get a record from the ShearVelocityOfFlow wind profile feature map"},
    {"listShearVelocityOfFlowToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowToBeInstalledFeature, METH_VARARGS,
     "listShearVelocityOfFlowToBeInstalledFeature() - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"addShearVelocityOfFlowFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowFeatureDescription, METH_VARARGS,
     "addShearVelocityOfFlowFeatureDescription(key,value) - add a record to the ShearVelocityOfFlow wind profile feature  map"},
    {"getShearVelocityOfFlowFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowFeatureDescription, METH_VARARGS,
     "getShearVelocityOfFlowFeatureDescription(key) - get a record from the ShearVelocityOfFlow wind profile feature map"},
    {"listShearVelocityOfFlowFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowFeatureDescription, METH_VARARGS,
     "listShearVelocityOfFlowFeatureDescription() - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"removeShearVelocityOfFlowFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveShearVelocityOfFlowFeatureDescription, METH_VARARGS,
     "removeShearVelocityOfFlowFeatureDescription(name) - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"addShearVelocityOfFlowPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowPlugin, METH_VARARGS,
     "addShearVelocityOfFlowPlugin(key,value) - add a record to the ShearVelocityOfFlow wind profile feature  map"},
    {"getShearVelocityOfFlowPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowPlugin, METH_VARARGS,
     "getShearVelocityOfFlowPlugin(key) - get a record from the ShearVelocityOfFlow wind profile feature map"},
    {"listShearVelocityOfFlowPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowPlugin, METH_VARARGS,
     "listShearVelocityOfFlowPlugin() - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"removeShearVelocityOfFlowPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveShearVelocityOfFlowPlugin, METH_VARARGS,
     "removeShearVelocityOfFlowPlugin(name) - remove a ShearVelocityOfFlow wind profile distribution record from feature map"},
    {"addShearVelocityOfFlowTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowTitle, METH_VARARGS,
     "addShearVelocityOfFlowTitle(key,value) - add a record to the ShearVelocityOfFlow wind profile feature  map"},
    {"getShearVelocityOfFlowTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowTitle, METH_VARARGS,
     "getShearVelocityOfFlowTitle(key) - get a record from the ShearVelocityOfFlow wind profile feature map"},
    {"listShearVelocityOfFlowTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowTitle, METH_VARARGS,
     "listShearVelocityOfFlowTitle() - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"addShearVelocityOfFlowLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowLink, METH_VARARGS,
     "addShearVelocityOfFlowLink(key,value) - add a record to the ShearVelocityOfFlow wind profile feature  map"},
    {"getShearVelocityOfFlowLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowLink, METH_VARARGS,
     "getShearVelocityOfFlowLink(key) - get a record from the ShearVelocityOfFlow wind profile feature map"},
    {"listShearVelocityOfFlowLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowLink, METH_VARARGS,
     "listShearVelocityOfFlowLink() - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"addShearVelocityOfFlowDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowDate, METH_VARARGS,
     "addShearVelocityOfFlowDate(key,value) - add a record to the ShearVelocityOfFlow wind profile feature  map"},
    {"getShearVelocityOfFlowDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowDate, METH_VARARGS,
     "getShearVelocityOfFlowDate(key) - get a record from the ShearVelocityOfFlow wind profile feature map"},
    {"listShearVelocityOfFlowDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowDate, METH_VARARGS,
     "listShearVelocityOfFlowDate() - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"addShearVelocityOfFlowVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowVersion, METH_VARARGS,
     "addShearVelocityOfFlowVersion(key,value) - add a record to the ShearVelocityOfFlow wind profile feature  map"},
    {"getShearVelocityOfFlowVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowVersion, METH_VARARGS,
     "getShearVelocityOfFlowVersion(key) - get a record from the ShearVelocityOfFlow wind profile feature map"},
    {"listShearVelocityOfFlowVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowVersion, METH_VARARGS,
     "listShearVelocityOfFlowVersion() - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"addShearVelocityOfFlowFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowFeatureSkipDuringUnintallation,METH_VARARGS,
     "addShearVelocityOfFlowFeatureSkipDuringUnintallation(key,value) - add a record to the ShearVelocityOfFlow wind profile feature  map"},
    {"getShearVelocityOfFlowFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowFeatureSkipDuringUnintallation, METH_VARARGS,
     "getShearVelocityOfFlowFeatureSkipDuringUnintallation(key) - get a record from the ShearVelocityOfFlow wind profile feature map"},
    {"listShearVelocityOfFlowFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowFeatureSkipDuringUnintallation,METH_VARARGS,
     "listShearVelocityOfFlowFeatureSkipDuringUnintallation() - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"addShearVelocityOfFlowProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddShearVelocityOfFlowProducer, METH_VARARGS,
     "addShearVelocityOfFlowProducer(key,value) - add a record to the ShearVelocityOfFlow wind profile feature  map"},
    {"getShearVelocityOfFlowProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetShearVelocityOfFlowProducer, METH_VARARGS,
     "getShearVelocityOfFlowProducer(key) - get a record from the ShearVelocityOfFlow wind profile feature map"},
    {"listShearVelocityOfFlowProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListShearVelocityOfFlowProducer, METH_VARARGS,
     "listShearVelocityOfFlowProducer() - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"removeShearVelocityOfFlowProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveShearVelocityOfFlowProducer,METH_VARARGS,
     "removeShearVelocityOfFlowProducer(name) - list all the records in the ShearVelocityOfFlow wind profile feature map"},
    {"produceShearVelocityOfFlow", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceShearVelocityOfFlow, METH_VARARGS,
     "produceShearVelocityOfFlow(name) - list all the records in the ShearVelocityOfFlow wind profile feature map"},




     {"addSkewnessAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessAuthor, METH_VARARGS,
     "addSkewnessAuthor(key,value) - add a record to the Skewness feature map"},
    {"getSkewnessAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessAuthor, METH_VARARGS,
     "getSkewnessAuthor(key) - get a record from the Skewness feature map"},
    {"listSkewnessAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessAuthor, METH_VARARGS,
     "listSkewnessAuthor() - list all the records in the Skewness feature map"},
    {"addSkewnessToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessToBeInstalledFeature, METH_VARARGS,
     "addSkewnessToBeInstalledFeature(key,value) - add a record to the Skewness wind profile feature  map"},
    {"getSkewnessToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessToBeInstalledFeature, METH_VARARGS,
     "getSkewnessToBeInstalledFeature(key) - get a record from the Skewness wind profile feature map"},
    {"listSkewnessToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessToBeInstalledFeature, METH_VARARGS,
     "listSkewnessToBeInstalledFeature() - list all the records in the Skewness wind profile feature map"},
    {"addSkewnessFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessFeatureDescription, METH_VARARGS,
     "addSkewnessFeatureDescription(key,value) - add a record to the Skewness wind profile feature  map"},
    {"getSkewnessFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessFeatureDescription, METH_VARARGS,
     "getSkewnessFeatureDescription(key) - get a record from the Skewness wind profile feature map"},
    {"listSkewnessFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessFeatureDescription, METH_VARARGS,
     "listSkewnessFeatureDescription() - list all the records in the Skewness wind profile feature map"},
    {"removeSkewnessFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveSkewnessFeatureDescription, METH_VARARGS,
     "removeSkewnessFeatureDescription(name) - list all the records in the Skewness wind profile feature map"},
    {"addSkewnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessPlugin, METH_VARARGS,
     "addSkewnessPlugin(key,value) - add a record to the Skewness wind profile feature  map"},
    {"getSkewnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessPlugin, METH_VARARGS,
     "getSkewnessPlugin(key) - get a record from the Skewness wind profile feature map"},
    {"listSkewnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessPlugin, METH_VARARGS,
     "listSkewnessPlugin() - list all the records in the Skewness wind profile feature map"},
    {"removeSkewnessPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveSkewnessPlugin, METH_VARARGS,
     "removeSkewnessPlugin(name) - remove a Skewness wind profile distribution record from feature map"},
    {"addSkewnessTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessTitle, METH_VARARGS,
     "addSkewnessTitle(key,value) - add a record to the Skewness wind profile feature  map"},
    {"getSkewnessTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessTitle, METH_VARARGS,
     "getSkewnessTitle(key) - get a record from the Skewness wind profile feature map"},
    {"listSkewnessTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessTitle, METH_VARARGS,
     "listSkewnessTitle() - list all the records in the Skewness wind profile feature map"},
    {"addSkewnessLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessLink, METH_VARARGS,
     "addSkewnessLink(key,value) - add a record to the Skewness wind profile feature  map"},
    {"getSkewnessLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessLink, METH_VARARGS,
     "getSkewnessLink(key) - get a record from the Skewness wind profile feature map"},
    {"listSkewnessLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessLink, METH_VARARGS,
     "listSkewnessLink() - list all the records in the Skewness wind profile feature map"},
    {"addSkewnessDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessDate, METH_VARARGS,
     "addSkewnessDate(key,value) - add a record to the Skewness wind profile feature  map"},
    {"getSkewnessDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessDate, METH_VARARGS,
     "getSkewnessDate(key) - get a record from the Skewness wind profile feature map"},
    {"listSkewnessDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessDate, METH_VARARGS,
     "listSkewnessDate() - list all the records in the Skewness wind profile feature map"},
    {"addSkewnessVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessVersion, METH_VARARGS,
     "addSkewnessVersion(key,value) - add a record to the Skewness wind profile feature  map"},
    {"getSkewnessVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessVersion, METH_VARARGS,
     "getSkewnessVersion(key) - get a record from the Skewness wind profile feature map"},
    {"listSkewnessVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessVersion, METH_VARARGS,
     "listSkewnessVersion() - list all the records in the Skewness wind profile feature map"},
    {"addSkewnessFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessFeatureSkipDuringUnintallation,METH_VARARGS,
     "addSkewnessFeatureSkipDuringUnintallation(key,value) - add a record to the Skewness wind profile feature  map"},
    {"getSkewnessFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessFeatureSkipDuringUnintallation, METH_VARARGS,
     "getSkewnessFeatureSkipDuringUnintallation(key) - get a record from the Skewness wind profile feature map"},
    {"listSkewnessFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessFeatureSkipDuringUnintallation,METH_VARARGS,
     "listSkewnessFeatureSkipDuringUnintallation() - list all the records in the Skewness wind profile feature map"},
    {"addSkewnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddSkewnessProducer, METH_VARARGS,
     "addSkewnessProducer(key,value) - add a record to the Skewness wind profile feature  map"},
    {"getSkewnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetSkewnessProducer, METH_VARARGS,
     "getSkewnessProducer(key) - get a record from the Skewness wind profile feature map"},
    {"listSkewnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListSkewnessProducer, METH_VARARGS,
     "listSkewnessProducer() - list all the records in the Skewness wind profile feature map"},
    {"removeSkewnessProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveSkewnessProducer,METH_VARARGS,
     "removeSkewnessProducer(name) - list all the records in the Skewness wind profile feature map"},
    {"produceSkewness", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceSkewness, METH_VARARGS,
     "produceSkewness(name) - list all the records in the Skewness wind profile feature map"},



    {"addStandardDeviationAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationAuthor, METH_VARARGS,
     "addStandardDeviationAuthor(key,value) - add a record to the StandardDeviation feature map"},
    {"getStandardDeviationAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationAuthor, METH_VARARGS,
     "getStandardDeviationAuthor(key) - get a record from the StandardDeviation feature map"},
    {"listStandardDeviationAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationAuthor, METH_VARARGS,
     "listStandardDeviationAuthor() - list all the records in the StandardDeviation feature map"},
    {"addStandardDeviationToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationToBeInstalledFeature, METH_VARARGS,
     "addStandardDeviationToBeInstalledFeature(key,value) - add a record to the StandardDeviation wind profile feature  map"},
    {"getStandardDeviationToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationToBeInstalledFeature, METH_VARARGS,
     "getStandardDeviationToBeInstalledFeature(key) - get a record from the StandardDeviation wind profile feature map"},
    {"listStandardDeviationToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationToBeInstalledFeature, METH_VARARGS,
     "listStandardDeviationToBeInstalledFeature() - list all the records in the StandardDeviation wind profile feature map"},
    {"addStandardDeviationFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationFeatureDescription, METH_VARARGS,
     "addStandardDeviationFeatureDescription(key,value) - add a record to the StandardDeviation wind profile feature  map"},
    {"getStandardDeviationFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationFeatureDescription, METH_VARARGS,
     "getStandardDeviationFeatureDescription(key) - get a record from the StandardDeviation wind profile feature map"},
    {"listStandardDeviationFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationFeatureDescription, METH_VARARGS,
     "listStandardDeviationFeatureDescription() - list all the records in the StandardDeviation wind profile feature map"},
    {"removeStandardDeviationFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveStandardDeviationFeatureDescription, METH_VARARGS,
     "removeStandardDeviationFeatureDescription(name) - list all the records in the StandardDeviation wind profile feature map"},
    {"addStandardDeviationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationPlugin, METH_VARARGS,
     "addStandardDeviationPlugin(key,value) - add a record to the StandardDeviation wind profile feature  map"},
    {"getStandardDeviationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationPlugin, METH_VARARGS,
     "getStandardDeviationPlugin(key) - get a record from the StandardDeviation wind profile feature map"},
    {"listStandardDeviationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationPlugin, METH_VARARGS,
     "listStandardDeviationPlugin() - list all the records in the StandardDeviation wind profile feature map"},
    {"removeStandardDeviationPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveStandardDeviationPlugin, METH_VARARGS,
     "removeStandardDeviationPlugin(name) - remove a StandardDeviation wind profile distribution record from feature map"},
    {"addStandardDeviationTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationTitle, METH_VARARGS,
     "addStandardDeviationTitle(key,value) - add a record to the StandardDeviation wind profile feature  map"},
    {"getStandardDeviationTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationTitle, METH_VARARGS,
     "getStandardDeviationTitle(key) - get a record from the StandardDeviation wind profile feature map"},
    {"listStandardDeviationTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationTitle, METH_VARARGS,
     "listStandardDeviationTitle() - list all the records in the StandardDeviation wind profile feature map"},
    {"addStandardDeviationLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationLink, METH_VARARGS,
     "addStandardDeviationLink(key,value) - add a record to the StandardDeviation wind profile feature  map"},
    {"getStandardDeviationLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationLink, METH_VARARGS,
     "getStandardDeviationLink(key) - get a record from the StandardDeviation wind profile feature map"},
    {"listStandardDeviationLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationLink, METH_VARARGS,
     "listStandardDeviationLink() - list all the records in the StandardDeviation wind profile feature map"},
    {"addStandardDeviationDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationDate, METH_VARARGS,
     "addStandardDeviationDate(key,value) - add a record to the StandardDeviation wind profile feature  map"},
    {"getStandardDeviationDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationDate, METH_VARARGS,
     "getStandardDeviationDate(key) - get a record from the StandardDeviation wind profile feature map"},
    {"listStandardDeviationDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationDate, METH_VARARGS,
     "listStandardDeviationDate() - list all the records in the StandardDeviation wind profile feature map"},
    {"addStandardDeviationVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationVersion, METH_VARARGS,
     "addStandardDeviationVersion(key,value) - add a record to the StandardDeviation wind profile feature  map"},
    {"getStandardDeviationVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationVersion, METH_VARARGS,
     "getStandardDeviationVersion(key) - get a record from the StandardDeviation wind profile feature map"},
    {"listStandardDeviationVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationVersion, METH_VARARGS,
     "listStandardDeviationVersion() - list all the records in the StandardDeviation wind profile feature map"},
    {"addStandardDeviationFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationFeatureSkipDuringUnintallation,METH_VARARGS,
     "addStandardDeviationFeatureSkipDuringUnintallation(key,value) - add a record to the StandardDeviation wind profile feature  map"},
    {"getStandardDeviationFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationFeatureSkipDuringUnintallation, METH_VARARGS,
     "getStandardDeviationFeatureSkipDuringUnintallation(key) - get a record from the StandardDeviation wind profile feature map"},
    {"listStandardDeviationFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationFeatureSkipDuringUnintallation,METH_VARARGS,
     "listStandardDeviationFeatureSkipDuringUnintallation() - list all the records in the StandardDeviation wind profile feature map"},
    {"addStandardDeviationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddStandardDeviationProducer, METH_VARARGS,
     "addStandardDeviationProducer(key,value) - add a record to the StandardDeviation wind profile feature  map"},
    {"getStandardDeviationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetStandardDeviationProducer, METH_VARARGS,
     "getStandardDeviationProducer(key) - get a record from the StandardDeviation wind profile feature map"},
    {"listStandardDeviationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListStandardDeviationProducer, METH_VARARGS,
     "listStandardDeviationProducer() - list all the records in the StandardDeviation wind profile feature map"},
    {"removeStandardDeviationProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveStandardDeviationProducer,METH_VARARGS,
     "removeStandardDeviationProducer(name) - list all the records in the StandardDeviation wind profile feature map"},
    {"produceStandardDeviation", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceStandardDeviation, METH_VARARGS,
     "produceStandardDeviation(name) - list all the records in the StandardDeviation wind profile feature map"},



     {"addTurbulenceIntensityAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityAuthor, METH_VARARGS,
     "addTurbulenceIntensityAuthor(key,value) - add a record to the TurbulenceIntensity feature map"},
    {"getTurbulenceIntensityAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityAuthor, METH_VARARGS,
     "getTurbulenceIntensityAuthor(key) - get a record from the TurbulenceIntensity feature map"},
    {"listTurbulenceIntensityAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityAuthor, METH_VARARGS,
     "listTurbulenceIntensityAuthor() - list all the records in the TurbulenceIntensity feature map"},
    {"addTurbulenceIntensityToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityToBeInstalledFeature, METH_VARARGS,
     "addTurbulenceIntensityToBeInstalledFeature(key,value) - add a record to the TurbulenceIntensity wind profile feature  map"},
    {"getTurbulenceIntensityToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityToBeInstalledFeature, METH_VARARGS,
     "getTurbulenceIntensityToBeInstalledFeature(key) - get a record from the TurbulenceIntensity wind profile feature map"},
    {"listTurbulenceIntensityToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityToBeInstalledFeature, METH_VARARGS,
     "listTurbulenceIntensityToBeInstalledFeature() - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"addTurbulenceIntensityFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityFeatureDescription, METH_VARARGS,
     "addTurbulenceIntensityFeatureDescription(key,value) - add a record to the TurbulenceIntensity wind profile feature  map"},
    {"getTurbulenceIntensityFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityFeatureDescription, METH_VARARGS,
     "getTurbulenceIntensityFeatureDescription(key) - get a record from the TurbulenceIntensity wind profile feature map"},
    {"listTurbulenceIntensityFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityFeatureDescription, METH_VARARGS,
     "listTurbulenceIntensityFeatureDescription() - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"removeTurbulenceIntensityFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveTurbulenceIntensityFeatureDescription, METH_VARARGS,
     "removeTurbulenceIntensityFeatureDescription(name) - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"addTurbulenceIntensityPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityPlugin, METH_VARARGS,
     "addTurbulenceIntensityPlugin(key,value) - add a record to the TurbulenceIntensity wind profile feature  map"},
    {"getTurbulenceIntensityPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityPlugin, METH_VARARGS,
     "getTurbulenceIntensityPlugin(key) - get a record from the TurbulenceIntensity wind profile feature map"},
    {"listTurbulenceIntensityPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityPlugin, METH_VARARGS,
     "listTurbulenceIntensityPlugin() - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"removeTurbulenceIntensityPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveTurbulenceIntensityPlugin, METH_VARARGS,
     "removeTurbulenceIntensityPlugin(name) - remove a TurbulenceIntensity wind profile distribution record from feature map"},
    {"addTurbulenceIntensityTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityTitle, METH_VARARGS,
     "addTurbulenceIntensityTitle(key,value) - add a record to the TurbulenceIntensity wind profile feature  map"},
    {"getTurbulenceIntensityTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityTitle, METH_VARARGS,
     "getTurbulenceIntensityTitle(key) - get a record from the TurbulenceIntensity wind profile feature map"},
    {"listTurbulenceIntensityTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityTitle, METH_VARARGS,
     "listTurbulenceIntensityTitle() - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"addTurbulenceIntensityLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityLink, METH_VARARGS,
     "addTurbulenceIntensityLink(key,value) - add a record to the TurbulenceIntensity wind profile feature  map"},
    {"getTurbulenceIntensityLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityLink, METH_VARARGS,
     "getTurbulenceIntensityLink(key) - get a record from the TurbulenceIntensity wind profile feature map"},
    {"listTurbulenceIntensityLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityLink, METH_VARARGS,
     "listTurbulenceIntensityLink() - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"addTurbulenceIntensityDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityDate, METH_VARARGS,
     "addTurbulenceIntensityDate(key,value) - add a record to the TurbulenceIntensity wind profile feature  map"},
    {"getTurbulenceIntensityDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityDate, METH_VARARGS,
     "getTurbulenceIntensityDate(key) - get a record from the TurbulenceIntensity wind profile feature map"},
    {"listTurbulenceIntensityDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityDate, METH_VARARGS,
     "listTurbulenceIntensityDate() - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"addTurbulenceIntensityVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityVersion, METH_VARARGS,
     "addTurbulenceIntensityVersion(key,value) - add a record to the TurbulenceIntensity wind profile feature  map"},
    {"getTurbulenceIntensityVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityVersion, METH_VARARGS,
     "getTurbulenceIntensityVersion(key) - get a record from the TurbulenceIntensity wind profile feature map"},
    {"listTurbulenceIntensityVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityVersion, METH_VARARGS,
     "listTurbulenceIntensityVersion() - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"addTurbulenceIntensityFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityFeatureSkipDuringUnintallation,METH_VARARGS,
     "addTurbulenceIntensityFeatureSkipDuringUnintallation(key,value) - add a record to the TurbulenceIntensity wind profile feature  map"},
    {"getTurbulenceIntensityFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityFeatureSkipDuringUnintallation, METH_VARARGS,
     "getTurbulenceIntensityFeatureSkipDuringUnintallation(key) - get a record from the TurbulenceIntensity wind profile feature map"},
    {"listTurbulenceIntensityFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityFeatureSkipDuringUnintallation,METH_VARARGS,
     "listTurbulenceIntensityFeatureSkipDuringUnintallation() - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"addTurbulenceIntensityProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceIntensityProducer, METH_VARARGS,
     "addTurbulenceIntensityProducer(key,value) - add a record to the TurbulenceIntensity wind profile feature  map"},
    {"getTurbulenceIntensityProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceIntensityProducer, METH_VARARGS,
     "getTurbulenceIntensityProducer(key) - get a record from the TurbulenceIntensity wind profile feature map"},
    {"listTurbulenceIntensityProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceIntensityProducer, METH_VARARGS,
     "listTurbulenceIntensityProducer() - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"removeTurbulenceIntensityProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveTurbulenceIntensityProducer,METH_VARARGS,
     "removeTurbulenceIntensityProducer(name) - list all the records in the TurbulenceIntensity wind profile feature map"},
    {"produceTurbulenceIntensity", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceTurbulenceIntensity, METH_VARARGS,
     "produceTurbulenceIntensity(name) - list all the records in the TurbulenceIntensity wind profile feature map"},



     {"addTurbulenceScaleAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScaleAuthor, METH_VARARGS,
     "addTurbulenceScaleAuthor(key,value) - add a record to the TurbulenceScale feature map"},
    {"getTurbulenceScaleAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScaleAuthor, METH_VARARGS,
     "getTurbulenceScaleAuthor(key) - get a record from the TurbulenceScale feature map"},
    {"listTurbulenceScaleAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScaleAuthor, METH_VARARGS,
     "listTurbulenceScaleAuthor() - list all the records in the TurbulenceScale feature map"},
    {"addTurbulenceScaleToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScaleToBeInstalledFeature, METH_VARARGS,
     "addTurbulenceScaleToBeInstalledFeature(key,value) - add a record to the TurbulenceScale wind profile feature  map"},
    {"getTurbulenceScaleToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScaleToBeInstalledFeature, METH_VARARGS,
     "getTurbulenceScaleToBeInstalledFeature(key) - get a record from the TurbulenceScale wind profile feature map"},
    {"listTurbulenceScaleToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScaleToBeInstalledFeature, METH_VARARGS,
     "listTurbulenceScaleToBeInstalledFeature() - list all the records in the TurbulenceScale wind profile feature map"},
    {"addTurbulenceScaleFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScaleFeatureDescription, METH_VARARGS,
     "addTurbulenceScaleFeatureDescription(key,value) - add a record to the TurbulenceScale wind profile feature  map"},
    {"getTurbulenceScaleFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScaleFeatureDescription, METH_VARARGS,
     "getTurbulenceScaleFeatureDescription(key) - get a record from the TurbulenceScale wind profile feature map"},
    {"listTurbulenceScaleFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScaleFeatureDescription, METH_VARARGS,
     "listTurbulenceScaleFeatureDescription() - list all the records in the TurbulenceScale wind profile feature map"},
    {"removeTurbulenceScaleFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveTurbulenceScaleFeatureDescription, METH_VARARGS,
     "removeTurbulenceScaleFeatureDescription(name) - list all the records in the TurbulenceScale wind profile feature map"},
    {"addTurbulenceScalePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScalePlugin, METH_VARARGS,
     "addTurbulenceScalePlugin(key,value) - add a record to the TurbulenceScale wind profile feature  map"},
    {"getTurbulenceScalePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScalePlugin, METH_VARARGS,
     "getTurbulenceScalePlugin(key) - get a record from the TurbulenceScale wind profile feature map"},
    {"listTurbulenceScalePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScalePlugin, METH_VARARGS,
     "listTurbulenceScalePlugin() - list all the records in the TurbulenceScale wind profile feature map"},
    {"removeTurbulenceScalePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveTurbulenceScalePlugin, METH_VARARGS,
     "removeTurbulenceScalePlugin(name) - remove a TurbulenceScale wind profile distribution record from feature map"},
    {"addTurbulenceScaleTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScaleTitle, METH_VARARGS,
     "addTurbulenceScaleTitle(key,value) - add a record to the TurbulenceScale wind profile feature  map"},
    {"getTurbulenceScaleTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScaleTitle, METH_VARARGS,
     "getTurbulenceScaleTitle(key) - get a record from the TurbulenceScale wind profile feature map"},
    {"listTurbulenceScaleTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScaleTitle, METH_VARARGS,
     "listTurbulenceScaleTitle() - list all the records in the TurbulenceScale wind profile feature map"},
    {"addTurbulenceScaleLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScaleLink, METH_VARARGS,
     "addTurbulenceScaleLink(key,value) - add a record to the TurbulenceScale wind profile feature  map"},
    {"getTurbulenceScaleLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScaleLink, METH_VARARGS,
     "getTurbulenceScaleLink(key) - get a record from the TurbulenceScale wind profile feature map"},
    {"listTurbulenceScaleLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScaleLink, METH_VARARGS,
     "listTurbulenceScaleLink() - list all the records in the TurbulenceScale wind profile feature map"},
    {"addTurbulenceScaleDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScaleDate, METH_VARARGS,
     "addTurbulenceScaleDate(key,value) - add a record to the TurbulenceScale wind profile feature  map"},
    {"getTurbulenceScaleDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScaleDate, METH_VARARGS,
     "getTurbulenceScaleDate(key) - get a record from the TurbulenceScale wind profile feature map"},
    {"listTurbulenceScaleDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScaleDate, METH_VARARGS,
     "listTurbulenceScaleDate() - list all the records in the TurbulenceScale wind profile feature map"},
    {"addTurbulenceScaleVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScaleVersion, METH_VARARGS,
     "addTurbulenceScaleVersion(key,value) - add a record to the TurbulenceScale wind profile feature  map"},
    {"getTurbulenceScaleVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScaleVersion, METH_VARARGS,
     "getTurbulenceScaleVersion(key) - get a record from the TurbulenceScale wind profile feature map"},
    {"listTurbulenceScaleVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScaleVersion, METH_VARARGS,
     "listTurbulenceScaleVersion() - list all the records in the TurbulenceScale wind profile feature map"},
    {"addTurbulenceScaleFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScaleFeatureSkipDuringUnintallation,METH_VARARGS,
     "addTurbulenceScaleFeatureSkipDuringUnintallation(key,value) - add a record to the TurbulenceScale wind profile feature  map"},
    {"getTurbulenceScaleFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScaleFeatureSkipDuringUnintallation, METH_VARARGS,
     "getTurbulenceScaleFeatureSkipDuringUnintallation(key) - get a record from the TurbulenceScale wind profile feature map"},
    {"listTurbulenceScaleFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScaleFeatureSkipDuringUnintallation,METH_VARARGS,
     "listTurbulenceScaleFeatureSkipDuringUnintallation() - list all the records in the TurbulenceScale wind profile feature map"},
    {"addTurbulenceScaleProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddTurbulenceScaleProducer, METH_VARARGS,
     "addTurbulenceScaleProducer(key,value) - add a record to the TurbulenceScale wind profile feature  map"},
    {"getTurbulenceScaleProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetTurbulenceScaleProducer, METH_VARARGS,
     "getTurbulenceScaleProducer(key) - get a record from the TurbulenceScale wind profile feature map"},
    {"listTurbulenceScaleProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListTurbulenceScaleProducer, METH_VARARGS,
     "listTurbulenceScaleProducer() - list all the records in the TurbulenceScale wind profile feature map"},
    {"removeTurbulenceScaleProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveTurbulenceScaleProducer,METH_VARARGS,
     "removeTurbulenceScaleProducer(name) - list all the records in the TurbulenceScale wind profile feature map"},
    {"produceTurbulenceScale", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceTurbulenceScale, METH_VARARGS,
     "produceTurbulenceScale(name) - list all the records in the TurbulenceScale wind profile feature map"},



     {"addVarianceAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddVarianceAuthor, METH_VARARGS,
     "addVarianceAuthor(key,value) - add a record to the Variance feature map"},
    {"getVarianceAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetVarianceAuthor, METH_VARARGS,
     "getVarianceAuthor(key) - get a record from the Variance feature map"},
    {"listVarianceAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListVarianceAuthor, METH_VARARGS,
     "listVarianceAuthor() - list all the records in the Variance feature map"},
    {"addVarianceToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddVarianceToBeInstalledFeature, METH_VARARGS,
     "addVarianceToBeInstalledFeature(key,value) - add a record to the Variance wind profile feature  map"},
    {"getVarianceToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetVarianceToBeInstalledFeature, METH_VARARGS,
     "getVarianceToBeInstalledFeature(key) - get a record from the Variance wind profile feature map"},
    {"listVarianceToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListVarianceToBeInstalledFeature, METH_VARARGS,
     "listVarianceToBeInstalledFeature() - list all the records in the Variance wind profile feature map"},
    {"addVarianceFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddVarianceFeatureDescription, METH_VARARGS,
     "addVarianceFeatureDescription(key,value) - add a record to the Variance wind profile feature  map"},
    {"getVarianceFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetVarianceFeatureDescription, METH_VARARGS,
     "getVarianceFeatureDescription(key) - get a record from the Variance wind profile feature map"},
    {"listVarianceFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListVarianceFeatureDescription, METH_VARARGS,
     "listVarianceFeatureDescription() - list all the records in the Variance wind profile feature map"},
    {"removeVarianceFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveVarianceFeatureDescription, METH_VARARGS,
     "removeVarianceFeatureDescription(name) - list all the records in the Variance wind profile feature map"},
    {"addVariancePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddVariancePlugin, METH_VARARGS,
     "addVariancePlugin(key,value) - add a record to the Variance wind profile feature  map"},
    {"getVariancePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetVariancePlugin, METH_VARARGS,
     "getVariancePlugin(key) - get a record from the Variance wind profile feature map"},
    {"listVariancePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListVariancePlugin, METH_VARARGS,
     "listVariancePlugin() - list all the records in the Variance wind profile feature map"},
    {"removeVariancePlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveVariancePlugin, METH_VARARGS,
     "removeVariancePlugin(name) - remove a Variance wind profile distribution record from feature map"},
    {"addVarianceTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddVarianceTitle, METH_VARARGS,
     "addVarianceTitle(key,value) - add a record to the Variance wind profile feature  map"},
    {"getVarianceTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetVarianceTitle, METH_VARARGS,
     "getVarianceTitle(key) - get a record from the Variance wind profile feature map"},
    {"listVarianceTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListVarianceTitle, METH_VARARGS,
     "listVarianceTitle() - list all the records in the Variance wind profile feature map"},
    {"addVarianceLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddVarianceLink, METH_VARARGS,
     "addVarianceLink(key,value) - add a record to the Variance wind profile feature  map"},
    {"getVarianceLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetVarianceLink, METH_VARARGS,
     "getVarianceLink(key) - get a record from the Variance wind profile feature map"},
    {"listVarianceLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListVarianceLink, METH_VARARGS,
     "listVarianceLink() - list all the records in the Variance wind profile feature map"},
    {"addVarianceDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddVarianceDate, METH_VARARGS,
     "addVarianceDate(key,value) - add a record to the Variance wind profile feature  map"},
    {"getVarianceDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetVarianceDate, METH_VARARGS,
     "getVarianceDate(key) - get a record from the Variance wind profile feature map"},
    {"listVarianceDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListVarianceDate, METH_VARARGS,
     "listVarianceDate() - list all the records in the Variance wind profile feature map"},
    {"addVarianceVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddVarianceVersion, METH_VARARGS,
     "addVarianceVersion(key,value) - add a record to the Variance wind profile feature  map"},
    {"getVarianceVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetVarianceVersion, METH_VARARGS,
     "getVarianceVersion(key) - get a record from the Variance wind profile feature map"},
    {"listVarianceVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListVarianceVersion, METH_VARARGS,
     "listVarianceVersion() - list all the records in the Variance wind profile feature map"},
    {"addVarianceFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddVarianceFeatureSkipDuringUnintallation,METH_VARARGS,
     "addVarianceFeatureSkipDuringUnintallation(key,value) - add a record to the Variance wind profile feature  map"},
    {"getVarianceFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetVarianceFeatureSkipDuringUnintallation, METH_VARARGS,
     "getVarianceFeatureSkipDuringUnintallation(key) - get a record from the Variance wind profile feature map"},
    {"listVarianceFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListVarianceFeatureSkipDuringUnintallation,METH_VARARGS,
     "listVarianceFeatureSkipDuringUnintallation() - list all the records in the Variance wind profile feature map"},
    {"addVarianceProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddVarianceProducer, METH_VARARGS,
     "addVarianceProducer(key,value) - add a record to the Variance wind profile feature  map"},
    {"getVarianceProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetVarianceProducer, METH_VARARGS,
     "getVarianceProducer(key) - get a record from the Variance wind profile feature map"},
    {"listVarianceProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListVarianceProducer, METH_VARARGS,
     "listVarianceProducer() - list all the records in the Variance wind profile feature map"},
    {"removeVarianceProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveVarianceProducer,METH_VARARGS,
     "removeVarianceProducer(name) - list all the records in the Variance wind profile feature map"},
    {"produceVariance", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceVariance, METH_VARARGS,
     "produceVariance(name) - list all the records in the Variance wind profile feature map"},




    {"addWavePassageEffectAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectAuthor, METH_VARARGS,
     "addWavePassageEffectAuthor(key,value) - add a record to the WavePassageEffect feature map"},
    {"getWavePassageEffectAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectAuthor, METH_VARARGS,
     "getWavePassageEffectAuthor(key) - get a record from the WavePassageEffect feature map"},
    {"listWavePassageEffectAuthor", (PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectAuthor, METH_VARARGS,
     "listWavePassageEffectAuthor() - list all the records in the WavePassageEffect feature map"},
    {"addWavePassageEffectToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectToBeInstalledFeature, METH_VARARGS,
     "addWavePassageEffectToBeInstalledFeature(key,value) - add a record to the WavePassageEffect wind profile feature  map"},
    {"getWavePassageEffectToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectToBeInstalledFeature, METH_VARARGS,
     "getWavePassageEffectToBeInstalledFeature(key) - get a record from the WavePassageEffect wind profile feature map"},
    {"listWavePassageEffectToBeInstalledFeature",(PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectToBeInstalledFeature, METH_VARARGS,
     "listWavePassageEffectToBeInstalledFeature() - list all the records in the WavePassageEffect wind profile feature map"},
    {"addWavePassageEffectFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectFeatureDescription, METH_VARARGS,
     "addWavePassageEffectFeatureDescription(key,value) - add a record to the WavePassageEffect wind profile feature  map"},
    {"getWavePassageEffectFeatureDescription", (PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectFeatureDescription, METH_VARARGS,
     "getWavePassageEffectFeatureDescription(key) - get a record from the WavePassageEffect wind profile feature map"},
    {"listWavePassageEffectFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectFeatureDescription, METH_VARARGS,
     "listWavePassageEffectFeatureDescription() - list all the records in the WavePassageEffect wind profile feature map"},
    {"removeWavePassageEffectFeatureDescription",(PyCFunction)RPSWindLabPythonPluginFactory::RemoveWavePassageEffectFeatureDescription, METH_VARARGS,
     "removeWavePassageEffectFeatureDescription(name) - list all the records in the WavePassageEffect wind profile feature map"},
    {"addWavePassageEffectPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectPlugin, METH_VARARGS,
     "addWavePassageEffectPlugin(key,value) - add a record to the WavePassageEffect wind profile feature  map"},
    {"getWavePassageEffectPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectPlugin, METH_VARARGS,
     "getWavePassageEffectPlugin(key) - get a record from the WavePassageEffect wind profile feature map"},
    {"listWavePassageEffectPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectPlugin, METH_VARARGS,
     "listWavePassageEffectPlugin() - list all the records in the WavePassageEffect wind profile feature map"},
    {"removeWavePassageEffectPlugin", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveWavePassageEffectPlugin, METH_VARARGS,
     "removeWavePassageEffectPlugin(name) - remove a WavePassageEffect wind profile distribution record from feature map"},
    {"addWavePassageEffectTitle", (PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectTitle, METH_VARARGS,
     "addWavePassageEffectTitle(key,value) - add a record to the WavePassageEffect wind profile feature  map"},
    {"getWavePassageEffectTitle", (PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectTitle, METH_VARARGS,
     "getWavePassageEffectTitle(key) - get a record from the WavePassageEffect wind profile feature map"},
    {"listWavePassageEffectTitle", (PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectTitle, METH_VARARGS,
     "listWavePassageEffectTitle() - list all the records in the WavePassageEffect wind profile feature map"},
    {"addWavePassageEffectLink", (PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectLink, METH_VARARGS,
     "addWavePassageEffectLink(key,value) - add a record to the WavePassageEffect wind profile feature  map"},
    {"getWavePassageEffectLink", (PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectLink, METH_VARARGS,
     "getWavePassageEffectLink(key) - get a record from the WavePassageEffect wind profile feature map"},
    {"listWavePassageEffectLink", (PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectLink, METH_VARARGS,
     "listWavePassageEffectLink() - list all the records in the WavePassageEffect wind profile feature map"},
    {"addWavePassageEffectDate", (PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectDate, METH_VARARGS,
     "addWavePassageEffectDate(key,value) - add a record to the WavePassageEffect wind profile feature  map"},
    {"getWavePassageEffectDate", (PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectDate, METH_VARARGS,
     "getWavePassageEffectDate(key) - get a record from the WavePassageEffect wind profile feature map"},
    {"listWavePassageEffectDate", (PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectDate, METH_VARARGS,
     "listWavePassageEffectDate() - list all the records in the WavePassageEffect wind profile feature map"},
    {"addWavePassageEffectVersion", (PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectVersion, METH_VARARGS,
     "addWavePassageEffectVersion(key,value) - add a record to the WavePassageEffect wind profile feature  map"},
    {"getWavePassageEffectVersion", (PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectVersion, METH_VARARGS,
     "getWavePassageEffectVersion(key) - get a record from the WavePassageEffect wind profile feature map"},
    {"listWavePassageEffectVersion", (PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectVersion, METH_VARARGS,
     "listWavePassageEffectVersion() - list all the records in the WavePassageEffect wind profile feature map"},
    {"addWavePassageEffectFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectFeatureSkipDuringUnintallation,METH_VARARGS,
     "addWavePassageEffectFeatureSkipDuringUnintallation(key,value) - add a record to the WavePassageEffect wind profile feature  map"},
    {"getWavePassageEffectFeatureSkipDuringUnintallation", (PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectFeatureSkipDuringUnintallation, METH_VARARGS,
     "getWavePassageEffectFeatureSkipDuringUnintallation(key) - get a record from the WavePassageEffect wind profile feature map"},
    {"listWavePassageEffectFeatureSkipDuringUnintallation",(PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectFeatureSkipDuringUnintallation,METH_VARARGS,
     "listWavePassageEffectFeatureSkipDuringUnintallation() - list all the records in the WavePassageEffect wind profile feature map"},
    {"addWavePassageEffectProducer", (PyCFunction)RPSWindLabPythonPluginFactory::AddWavePassageEffectProducer, METH_VARARGS,
     "addWavePassageEffectProducer(key,value) - add a record to the WavePassageEffect wind profile feature  map"},
    {"getWavePassageEffectProducer", (PyCFunction)RPSWindLabPythonPluginFactory::GetWavePassageEffectProducer, METH_VARARGS,
     "getWavePassageEffectProducer(key) - get a record from the WavePassageEffect wind profile feature map"},
    {"listWavePassageEffectProducer", (PyCFunction)RPSWindLabPythonPluginFactory::ListWavePassageEffectProducer, METH_VARARGS,
     "listWavePassageEffectProducer() - list all the records in the WavePassageEffect wind profile feature map"},
    {"removeWavePassageEffectProducer", (PyCFunction)RPSWindLabPythonPluginFactory::RemoveWavePassageEffectProducer,METH_VARARGS,
     "removeWavePassageEffectProducer(name) - list all the records in the WavePassageEffect wind profile feature map"},
    {"produceWavePassageEffect", (PyCFunction)RPSWindLabPythonPluginFactory::ProduceWavePassageEffect, METH_VARARGS,
     "produceWavePassageEffect(name) - list all the records in the WavePassageEffect wind profile feature map"},
    {nullptr, nullptr, 0, nullptr}  /* Sentinel */
};


} //namespace AttacherGui
