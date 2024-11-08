/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>               *
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

#include <Base/VectorPy.h>
#include <CXX/Objects.hxx>
#include "UserLabSimulation.h"
#include <Base/TypePy.h>

// inclusion of the generated files (generated out of UserLabSimulationPy.xml)
#include "UserLabSimulationPy.h"
#include "UserLabSimulationPy.cpp"
#include <Mod/UserLabAPI/App/UserLabSimulationData.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <App/RPSFeaturePy.h>
#include <Base/Console.h>



using namespace UserLab;
using namespace UserLabAPI;

PyObject* returnResult1(vec& dVarVector, vec& dValVector, std::string featureName)
{
    mat resArray(dVarVector.rows(), 2);
    resArray.col(0) = dVarVector;
    resArray.col(1) = dValVector;


    for (int j = 0; j < resArray.rows(); j++) {
        resArray(j, 0) = dVarVector(j);
        resArray(j, 1) = dValVector(j);
    }

    Py::List activeArray;
    for (int i = 0; i < resArray.rows(); i++) {
        Py::List row;
        for (int j = 0; j < resArray.cols(); j++) {
            row.append(Py::Float((resArray.coeff(i, j))));
        }
        activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}

PyObject* returnResult2(vec& dVarVector, cx_vec& dValVector, std::string featureName)
{
    mat resArray(dVarVector.rows(), 3);

    Py::List activeArray;
    for (int i = 0; i < resArray.rows(); i++) {
    resArray(i, 0) = dVarVector(i);
    resArray(i, 1) = dValVector(i).real();
    resArray(i, 2) = dValVector(i).imag();
    Py::List row;
    for (int j = 0; j < resArray.cols(); j++) {
        row.append(Py::Float((resArray.coeff(i, j))));
    }
    activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}

PyObject* returnResult3(cx_mat& resArray, std::string featureName, const char* displayOption)
{
    Py::List activeArray;
    for (int i = 0; i < resArray.rows(); i++) {
    Py::List row;
    for (int j = 0; j < resArray.cols(); j++) {

       if (strcmp(displayOption, "i") == 0) {
            row.append(Py::Float((resArray.coeff(i, j)).imag()));
       }
       else
       {
            row.append(Py::Float((resArray.coeff(i, j)).real()));
       }    
    }
    activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}

PyObject* returnResult4(mat& resArray, std::string featureName)
{
    Py::List activeArray;
    for (int i = 0; i < resArray.rows(); i++) {
    Py::List row;
    for (int j = 0; j < resArray.cols(); j++) {
        row.append(Py::Float((resArray.coeff(i, j))));
    }
    activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}

PyObject* returnResult5(std::complex<double>& resValue, std::string featureName)
{
    Py::List activeArray;
    activeArray.append(Py::Float(resValue.real()));
    activeArray.append(Py::Float(resValue.imag()));

    return boost::python::incref(activeArray.ptr());
}

PyObject* returnResult6(double resValue, std::string featureName)
{
    Py::Float activeValue(resValue);
    
    return boost::python::incref(activeValue.ptr());
}


std::string UserLabSimulationPy::representation(void) const
{
    std::stringstream str;
    str << "<UserLab Simulation: " << getUserLabSimulationPtr()->Label.getValue() << ">";
    return str.str();
}

PyObject* UserLabSimulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    return new UserLabSimulationPy(new UserLabSimulation());
}

// constructor method
int UserLabSimulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* UserLabSimulationPy::run(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    return Py::new_reference_to(Py::Long(getUserLabSimulationPtr()->run()));
}

PyObject* UserLabSimulationPy::stop(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    return Py::new_reference_to(Py::Long(getUserLabSimulationPtr()->stop()));
}

PyObject* UserLabSimulationPy::getPhenomenonName(PyObject *args)
{
    Py::String phenomenonName(Py::String(getUserLabSimulationPtr()->getPhenomenonName()));
    return Py::new_reference_to(phenomenonName);
}

PyObject* UserLabSimulationPy::getSimulationData(PyObject *args)
{
    UserLabSimulationData* simData = getUserLabSimulationPtr()->getSimulationData();
    if (simData)
    return Py::new_reference_to(simData->getPyObject());

    Py_Return;
}

    PyObject* UserLabSimulationPy::getActiveSimulationMethod(PyObject* args){
    App::DocumentObject* feat = getUserLabSimulationPtr()->getActiveSimulationMethod();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}


PyObject* UserLabSimulationPy::findAllPluggedUserLabFeatures(PyObject* args)
{
    const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
     QStringList pluggedFeaturesForThisGroup = getUserLabSimulationPtr()->findAllPluggedUserLabFeatures(QString::fromLatin1(group));

     for (QStringList::ConstIterator pt = pluggedFeaturesForThisGroup.begin(); pt != pluggedFeaturesForThisGroup.end(); ++pt) {
        res.append(Py::String((*pt).toUtf8().constData()));
     }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}

PyObject* UserLabSimulationPy::findAllUserLabFeaturesOfThisType(PyObject* args)
{
    const char* sType;
    if (!PyArg_ParseTuple(args, "s", &sType))
    return nullptr;

    Base::Type type = Base::Type::getTypeIfDerivedFrom(sType, UserLabAPI::UserLabFeature::getClassTypeId(), true);
    if (type.isBad()) {
        std::stringstream str;
        str << "'" << sType << "' is not a UserLab feature type";
        throw Base::TypeError(str.str());
    }

    Py::List res;
    PY_TRY
    {
    std::vector<std::string> createdFeaturesOfThisType = getUserLabSimulationPtr()->findAllUserLabFeaturesOfThisType(type);

    for (std::vector<std::string>::const_iterator cf = createdFeaturesOfThisType.begin(); cf != createdFeaturesOfThisType.end(); ++cf) {
        res.append(Py::String(*cf));
    }
    return Py::new_reference_to(res);
    }
    PY_CATCH



}

PyObject* UserLabSimulationPy::getUserLabPluggableFeatures(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     Py::List res;
    PY_TRY
    {
    std::vector<QString> pluggeableFeatures = getUserLabSimulationPtr()->getUserLabPluggableFeatures();

    for (std::vector<QString>::const_iterator cf = pluggeableFeatures.begin(); cf != pluggeableFeatures.end(); ++cf) {
        res.append(Py::String((*cf).toUtf8().constData()));
    }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}

PyObject* UserLabSimulationPy::getRPSTypesOfPluggableFeatures(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     Py::List res;
    PY_TRY
    {
    std::vector<Base::Type> rpsTypesOfFeatures = getUserLabSimulationPtr()->getRPSTypesOfPluggableFeatures();

    Py::List res;
    for (std::vector<Base::Type>::iterator it = rpsTypesOfFeatures.begin(); it != rpsTypesOfFeatures.end(); ++it) {
        res.append(Py::asObject(new Base::TypePy(new Base::Type(*it))));
    }
    return Py::new_reference_to(res);

    }
    PY_CATCH
}


    // +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *UserLabSimulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int UserLabSimulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}

// +++ computation methods ++++++++++++++++++++++++++++++++++++++++

PyObject* UserLabSimulationPy::simulate(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getUserLabSimulationPtr()->simulate(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}
PyObject* UserLabSimulationPy::simulateInLargeScaleMode(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    std::string featureName;

    bool result = getUserLabSimulationPtr()->simulateInLargeScaleMode(featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }
}

PyObject* UserLabSimulationPy::setActiveFeature(PyObject* args)
{
    PyObject* feature = nullptr;
        if (!PyArg_ParseTuple(args, "O", &feature))
        throw Py::Exception();

    if (!PyObject_TypeCheck(feature, &App::RPSFeaturePy::Type))
        throw Py::TypeError("Expect the argument to be a RPS feature object");

        App::RPSFeature* feat = static_cast<App::RPSFeaturePy*>(feature)->getRPSFeaturePtr();
    if (feat)
       getUserLabSimulationPtr()->setActiveFeature(feat);

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* UserLabSimulationPy::getActiveFeature(PyObject* args)
{
    const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
    App::RPSFeature* feat = getUserLabSimulationPtr()->getActiveFeature(QString::fromLatin1(group));
    if (feat)
        return Py::new_reference_to(feat->getPyObject());
    }
    PY_CATCH
}

PyObject* UserLabSimulationPy::getAllFeatures(PyObject* args)
{
     const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
    std::vector<App::RPSFeature*> features = getUserLabSimulationPtr()->getAllFeatures(QString::fromLatin1(group));
    for (std::vector<App::RPSFeature*>::iterator j = features.begin(); j != features.end(); ++j) {
        res.append(Py::asObject((*j)->getPyObject()));
     }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}