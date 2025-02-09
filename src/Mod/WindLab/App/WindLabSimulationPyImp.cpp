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
#include "WindLabSimulation.h"
#include <Base/TypePy.h>

// inclusion of the generated files (generated out of WindLabSimulationPy.xml)
#include "WindLabSimulationPy.h"
#include "WindLabSimulationPy.cpp"
#include <Mod/WindLabAPI/App/WindLabSimulationData.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <App/RPSFeaturePy.h>
#include <Base/Console.h>



using namespace WindLab;
using namespace WindLabAPI;

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

PyObject* returnResult7(cube& resArray, std::string featureName)
{
    Py::List activeArray;
    for (int i = 0; i < resArray.dimension(0); ++i) {  // Iterate over the first dimension (depth)
        Py::List array;
        for (int j = 0; j < resArray.dimension(1); ++j) {  // Iterate over the second dimension (rows)
            Py::List row;
            for (int k = 0; k < resArray.dimension(2); ++k) {  // Iterate over the third dimension (columns)
                row.append(Py::Float((resArray(i, j, k))));
            }
            array.append(row);
        }
       activeArray.append(array);
    }

    return boost::python::incref(activeArray.ptr());
}

std::string WindLabSimulationPy::representation(void) const
{
    std::stringstream str;
    str << "<WindLab Simulation: " << getWindLabSimulationPtr()->Label.getValue() << ">";
    return str.str();
}

PyObject* WindLabSimulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    return new WindLabSimulationPy(new WindLabSimulation());
}

// constructor method
int WindLabSimulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* WindLabSimulationPy::run(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    return Py::new_reference_to(Py::Long(getWindLabSimulationPtr()->run()));
}

PyObject* WindLabSimulationPy::stop(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    return Py::new_reference_to(Py::Long(getWindLabSimulationPtr()->stop()));
}

PyObject* WindLabSimulationPy::getPhenomenonName(PyObject *args)
{
    Py::String phenomenonName(Py::String(getWindLabSimulationPtr()->getPhenomenonName()));
    return Py::new_reference_to(phenomenonName);
}

PyObject* WindLabSimulationPy::getSimulationData(PyObject *args)
{
    WindLabSimulationData* simData = getWindLabSimulationPtr()->getSimulationData();
    if (simData)
    return Py::new_reference_to(simData->getPyObject());

    Py_Return;
}

PyObject* WindLabSimulationPy::getActiveCoherence(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveCoherence();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveCorrelation(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveCorrelation();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveCumulativeProbabilityDistribution(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveCumulativeProbabilityDistribution();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveFrequencyDistribution(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveFrequencyDistribution();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveGustFactor(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveGustFactor();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveKurtosis(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveKurtosis();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveLocationDistribution(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveLocationDistribution();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveMeanWind(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveMeanWind();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveModulation(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveModulation();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActivePeakFactor(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActivePeakFactor();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveProbabilityDensityFunction(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveProbabilityDensityFunction();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActivePSDDecompositionMethod(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActivePSDDecompositionMethod();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveRandomness(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveRandomness();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveRoughness(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveRoughness();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveShearVelocityOfFlow(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveShearVelocityOfFlow();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveSimulationMethod(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveSimulationMethod();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveSkewness(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveSkewness();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveStandardDeviation(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveStandardDeviation();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveTurbulenceIntensity(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveTurbulenceIntensity();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveTurbulenceScale(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveTurbulenceScale();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveUserDefinedRPSObject(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveUserDefinedRPSObject();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveVariance(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveVariance();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveWavePassageEffect(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveWavePassageEffect();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveXSpectrum(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveXSpectrum();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveYSpectrum(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveYSpectrum();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveZSpectrum(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveZSpectrum();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveMatrixTool(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveMatrixTool();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* WindLabSimulationPy::getActiveTableTool(PyObject* args){
    App::DocumentObject* feat = getWindLabSimulationPtr()->getActiveTableTool();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}


PyObject* WindLabSimulationPy::findAllPluggedWindLabFeatures(PyObject* args)
{
    const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
     QStringList pluggedFeaturesForThisGroup = getWindLabSimulationPtr()->findAllPluggedWindLabFeatures(QString::fromLatin1(group));

     for (QStringList::ConstIterator pt = pluggedFeaturesForThisGroup.begin(); pt != pluggedFeaturesForThisGroup.end(); ++pt) {
        res.append(Py::String((*pt).toUtf8().constData()));
     }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}

PyObject* WindLabSimulationPy::findAllWindLabFeaturesOfThisType(PyObject* args)
{
    const char* sType;
    if (!PyArg_ParseTuple(args, "s", &sType))
    return nullptr;

    Base::Type type = Base::Type::getTypeIfDerivedFrom(sType, WindLabAPI::WindLabFeature::getClassTypeId(), true);
    if (type.isBad()) {
        std::stringstream str;
        str << "'" << sType << "' is not a WindLab feature type";
        throw Base::TypeError(str.str());
    }

    Py::List res;
    PY_TRY
    {
    std::vector<std::string> createdFeaturesOfThisType = getWindLabSimulationPtr()->findAllWindLabFeaturesOfThisType(type);

    for (std::vector<std::string>::const_iterator cf = createdFeaturesOfThisType.begin(); cf != createdFeaturesOfThisType.end(); ++cf) {
        res.append(Py::String(*cf));
    }
    return Py::new_reference_to(res);
    }
    PY_CATCH



}

PyObject* WindLabSimulationPy::getWindLabPluggableFeatures(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     Py::List res;
    PY_TRY
    {
    std::vector<QString> pluggeableFeatures = getWindLabSimulationPtr()->getWindLabPluggableFeatures();

    for (std::vector<QString>::const_iterator cf = pluggeableFeatures.begin(); cf != pluggeableFeatures.end(); ++cf) {
        res.append(Py::String((*cf).toUtf8().constData()));
    }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}

PyObject* WindLabSimulationPy::getRPSTypesOfPluggableFeatures(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     Py::List res;
    PY_TRY
    {
    std::vector<Base::Type> rpsTypesOfFeatures = getWindLabSimulationPtr()->getRPSTypesOfPluggableFeatures();

    Py::List res;
    for (std::vector<Base::Type>::iterator it = rpsTypesOfFeatures.begin(); it != rpsTypesOfFeatures.end(); ++it) {
        res.append(Py::asObject(new Base::TypePy(new Base::Type(*it))));
    }
    return Py::new_reference_to(res);

    }
    PY_CATCH
}


    // +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *WindLabSimulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int WindLabSimulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}

// +++ computation methods ++++++++++++++++++++++++++++++++++++++++

PyObject *WindLabSimulationPy::computeCrossCoherenceVectorF(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();

    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeCrossCoherenceVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);

    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeCrossCoherenceVectorT(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeCrossCoherenceVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeCrossCoherenceMatrixPP(PyObject* args)
{
    char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeCrossCoherenceMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

	
PyObject *WindLabSimulationPy::computeCrossCorrelationVectorT(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    if (!PyArg_ParseTuple(args, "OO", &pyLocationJ, &pyLocationK))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeCrossCorrelationVectorT(*locationJ, *locationK, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeCrossCorrelationMatrixPP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeCrossCorrelationMatrixPP(time, resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *WindLabSimulationPy::computeFrequenciesVectorF(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    mat resArray;
    std::string featureName;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeFrequenciesVectorF(*locationJ, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    Py::List activeArray;
    for (int i = 0; i < dValVector.rows(); i++) {
    activeArray.append(Py::Float((dValVector(i))));
    }
    return boost::python::incref(activeArray.ptr());
}	
  
PyObject *WindLabSimulationPy::computeFrequenciesMatrixFP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeFrequenciesMatrixFP(resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *WindLabSimulationPy::computeLocationCoordinateMatrixP3(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeLocationCoordinateMatrixP3(resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *WindLabSimulationPy::computeMeanWindSpeedVectorP(PyObject* args)
{
     double time;
     if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeMeanWindSpeedVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeMeanWindSpeedVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeMeanWindSpeedVectorT(*locationJ, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeModulationVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double frequency = 0.0;

    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeModulationVectorT(*locationJ, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeModulationVectorP(PyObject* args)
{
    double time = 0.0;
    double frequency = 0.0;

    if (!PyArg_ParseTuple(args, "dd", &frequency, &time))
    return nullptr;

    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeModulationVectorP(frequency, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeDecomposedCrossSpectrumVectorF(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeDecomposedCrossSpectrumVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeDecomposedCrossSpectrumVectorT(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeDecomposedCrossSpectrumVectorT(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeDecomposedCrossSpectrumMatrixPP(PyObject* args)
{
    char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeDecomposedCrossSpectrumMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

PyObject *WindLabSimulationPy::generateRandomMatrixFP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->generateRandomMatrixFP(resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult4(resArray, featureName);
}

PyObject *WindLabSimulationPy::generateRandomCubeFPS(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    cube resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->generateRandomCubeFPS(resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult7(resArray, featureName);
}
//-----------------------------------------------------------------------------------------------------------//

PyObject *WindLabSimulationPy::computeXCrossSpectrumVectorF(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeXCrossSpectrumVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeXCrossSpectrumVectorT(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeXCrossSpectrumVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeXCrossSpectrumMatrixPP(PyObject* args)
{
   char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeXCrossSpectrumMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

PyObject *WindLabSimulationPy::computeXAutoSpectrumValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "Odd", &pyLocation, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeXAutoSpectrumValue(*location, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
    
PyObject *WindLabSimulationPy::computeXAutoSpectrumVectorF(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeXAutoSpectrumVectorF(*location, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeXAutoSpectrumVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeXAutoSpectrumVectorT(*location, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	
//------------------------------------------------------------------------
PyObject *WindLabSimulationPy::computeYCrossSpectrumVectorF(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeYCrossSpectrumVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeYCrossSpectrumVectorT(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeYCrossSpectrumVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeYCrossSpectrumMatrixPP(PyObject* args)
{
   char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeYCrossSpectrumMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

PyObject *WindLabSimulationPy::computeYAutoSpectrumValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "Odd", &pyLocation, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeYAutoSpectrumValue(*location, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
    
PyObject *WindLabSimulationPy::computeYAutoSpectrumVectorF(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeYAutoSpectrumVectorF(*location, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeYAutoSpectrumVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeYAutoSpectrumVectorT(*location, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	
//-----------------------------------------------------------------------------------------------------------------
PyObject *WindLabSimulationPy::computeZCrossSpectrumVectorF(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeZCrossSpectrumVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeZCrossSpectrumVectorT(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeZCrossSpectrumVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeZCrossSpectrumMatrixPP(PyObject* args)
{
   char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeZCrossSpectrumMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

PyObject *WindLabSimulationPy::computeZAutoSpectrumValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "Odd", &pyLocation, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeZAutoSpectrumValue(*location, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
    
PyObject *WindLabSimulationPy::computeZAutoSpectrumVectorF(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeZAutoSpectrumVectorF(*location, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeZAutoSpectrumVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeZAutoSpectrumVectorT(*location, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	
//---------------------------------------------------------------------------------------------------------------
PyObject *WindLabSimulationPy::computeCrossSpectrumVectorF(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeCrossSpectrumVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeCrossSpectrumVectorT(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeCrossSpectrumVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeCrossSpectrumMatrixPP(PyObject* args)
{
   char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeCrossSpectrumMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

PyObject *WindLabSimulationPy::computeAutoSpectrumValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "Odd", &pyLocation, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeAutoSpectrumValue(*location, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
    
PyObject *WindLabSimulationPy::computeAutoSpectrumVectorF(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeAutoSpectrumVectorF(*location, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeAutoSpectrumVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the  argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeAutoSpectrumVectorT(*location, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}
//-----------------------------------------------------------------------------------------------------
PyObject *WindLabSimulationPy::computeCrossCoherenceValue(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "OOdd", &pyLocationJ, &pyLocationK, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();

     std::complex<double> resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeCrossCoherenceValue(*locationJ, *locationK, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult5(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeCrossCorrelationValue(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "OOdd", &pyLocationJ, &pyLocationK, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeCrossCorrelationValue(*locationJ, *locationK, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeMeanWindSpeedValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeMeanWindSpeedValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeModulationValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time = 0.0;
    double frequency = 0.0;

    if (!PyArg_ParseTuple(args, "Odd", &pyLocation, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeModulationValue(*location, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeRandomValue(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeRandomValue(resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeXCrossSpectrumValue(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "OOdd", &pyLocationJ, &pyLocationK, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();

     std::complex<double> resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeXCrossSpectrumValue(*locationJ, *locationK, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult5(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeYCrossSpectrumValue(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "OOdd", &pyLocationJ, &pyLocationK, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();

     std::complex<double> resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeYCrossSpectrumValue(*locationJ, *locationK, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult5(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeZCrossSpectrumValue(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "OOdd", &pyLocationJ, &pyLocationK, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();

     std::complex<double> resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeZCrossSpectrumValue(*locationJ, *locationK, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult5(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeCrossSpectrumValue(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "OOdd", &pyLocationJ, &pyLocationK, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();

     std::complex<double> resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeCrossSpectrumValue(*locationJ, *locationK, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult5(resValue, featureName);
}	
	PyObject *WindLabSimulationPy::computeFrequencyValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    int index;
    if (!PyArg_ParseTuple(args, "Oi", &pyLocation, &index))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeFrequencyValue(*location, index, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	


PyObject* WindLabSimulationPy::tableToolCompute(PyObject* args)
{
    PyObject* pythonList;

    if (!PyArg_ParseTuple(args, "O", &pythonList))
        return nullptr;
    mat outputMatrix;
    std::string featureName;
    int rows = PyList_Size(pythonList);
    int cols = PyList_Size(PyList_GetItem(pythonList, 0));
    mat inputMatrix(rows, cols);

       try {
        std::vector<std::vector<double>> cppVectorofVector;
        Py::List list_f(pythonList);
        for (int i = 0; i < rows; ++i) {
        PyObject* pythonlistItem = PyList_GetItem(pythonList, i);
            std::vector<double> cppVector;
            // Verify that each pythonlistItem also a list
            if (!PyList_Check(pythonlistItem)) {
                PyErr_SetString(PyExc_TypeError, "must pass in list of list");
                return NULL;
            }
            for (int j = 0; j < cols; ++j) {
                PyObject* pythonValue = PyList_GetItem(pythonlistItem, j);
                double val;
                // Check that each pythonValue is a long/double
                if (PyLong_Check(pythonValue)) {
                    val = (double)PyLong_AsLong(pythonValue);
                }
                else if (PyFloat_Check(pythonValue)) {
                    val = PyFloat_AsDouble(pythonValue);
                }
                else {
                    PyErr_SetString(PyExc_TypeError, "must pass in list of list of number");
                    return NULL;
                }

                inputMatrix(i,j) =  val;
            }
            cppVectorofVector.push_back(cppVector);
        }

        bool result = getWindLabSimulationPtr()->tableToolCompute(inputMatrix, outputMatrix, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }
    }
    catch (const Py::Exception&) {
        throw;
    }
    
     return returnResult4(outputMatrix, featureName);
}	
PyObject* WindLabSimulationPy::matrixToolCompute(PyObject* args)
{
      PyObject* pythonList;

    if (!PyArg_ParseTuple(args, "O", &pythonList))
        return nullptr;
    mat outputMatrix;
    std::string featureName;
    int rows = PyList_Size(pythonList);
    int cols = PyList_Size(PyList_GetItem(pythonList, 0));
    mat inputMatrix(rows, cols);

       try {
        std::vector<std::vector<double>> cppVectorofVector;
        Py::List list_f(pythonList);
        for (int i = 0; i < rows; ++i) {
        PyObject* pythonlistItem = PyList_GetItem(pythonList, i);
            std::vector<double> cppVector;
            // Verify that each pythonlistItem also a list
            if (!PyList_Check(pythonlistItem)) {
                PyErr_SetString(PyExc_TypeError, "must pass in list of list");
                return NULL;
            }
            for (int j = 0; j < cols; ++j) {
                PyObject* pythonValue = PyList_GetItem(pythonlistItem, j);
                double val;
                // Check that each pythonValue is a long/double
                if (PyLong_Check(pythonValue)) {
                    val = (double)PyLong_AsLong(pythonValue);
                }
                else if (PyFloat_Check(pythonValue)) {
                    val = PyFloat_AsDouble(pythonValue);
                }
                else {
                    PyErr_SetString(PyExc_TypeError, "must pass in list of list of number");
                    return NULL;
                }

                inputMatrix(i,j) =  val;
            }
            cppVectorofVector.push_back(cppVector);
        }

        bool result = getWindLabSimulationPtr()->matrixToolCompute(inputMatrix, outputMatrix, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }
    }
    catch (const Py::Exception&) {
        throw;
    }
    
     return returnResult4(outputMatrix, featureName);
}	
PyObject* WindLabSimulationPy::userDefinedRPSObjectCompute(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->userDefinedRPSObjectCompute(resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *WindLabSimulationPy::computeCPDValue(PyObject* args)
{
     double x;
     if (!PyArg_ParseTuple(args, "d", &x))
    return nullptr;

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeCPDValue(x, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject* WindLabSimulationPy::computeCPDVectorX(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeCPDVectorX(dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
    
PyObject *WindLabSimulationPy::computeGustFactorValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeGustFactorValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeGustFactorVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeGustFactorVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeGustFactorVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeGustFactorVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeKurtosisValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeKurtosisValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeKurtosisVectorP(PyObject* args)
{
     double time;
     if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeKurtosisVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeKurtosisVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeKurtosisVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computePeakFactorValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computePeakFactorValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computePeakFactorVectorP(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeKurtosisVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computePeakFactorVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computePeakFactorVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computePDFValue(PyObject* args)
{
    double x;
    if (!PyArg_ParseTuple(args, "d", &x))
    return nullptr;

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computePDFValue(x, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computePDFVectorX(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computePDFVectorX(dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeRoughnessValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

     double resValue;
     std::string featureName;

     bool result = getWindLabSimulationPtr()->computeRoughnessValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeRoughnessVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeRoughnessVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeRoughnessVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeRoughnessVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeShearVelocityOfFlowValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeShearVelocityOfFlowValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeShearVelocityOfFlowVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeShearVelocityOfFlowVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeShearVelocityOfFlowVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeShearVelocityOfFlowVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeSkewnessValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeSkewnessValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeSkewnessVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeSkewnessVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeSkewnessVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeSkewnessVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeStandardDeviationValue(PyObject* args)
{
   PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeStandardDeviationValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeStandardDeviationVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeStandardDeviationVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeStandardDeviationVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeStandardDeviationVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeTurbulenceIntensityValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeTurbulenceIntensityValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeTurbulenceIntensityVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeTurbulenceIntensityVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeTurbulenceIntensityVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeTurbulenceIntensityVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeTurbulenceScaleValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeTurbulenceScaleValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeTurbulenceScaleVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeTurbulenceScaleVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeTurbulenceScaleVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeTurbulenceScaleVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeVarianceValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "Od", &pyLocation, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

    double resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeVarianceValue(*location, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *WindLabSimulationPy::computeVarianceVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeVarianceVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeVarianceVectorT(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    if (!PyArg_ParseTuple(args, "O", &pyLocation))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
    throw Py::TypeError("Expect the argument to be a vector object");

    Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getWindLabSimulationPtr()->computeVarianceVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *WindLabSimulationPy::computeWavePassageEffectVectorF(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double time;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeWavePassageEffectVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult2(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeWavePassageEffectVectorT(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    if (!PyArg_ParseTuple(args, "OOd", &pyLocationJ, &pyLocationK, &frequency))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();
    
    std::string featureName;
    vec dVarVector;
    cx_vec dValVector;

    bool result = getWindLabSimulationPtr()->computeWavePassageEffectVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult2(dVarVector, dValVector, featureName);
}	
PyObject *WindLabSimulationPy::computeWavePassageEffectMatrixPP(PyObject* args)
{
    char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeWavePassageEffectMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    return returnResult3(resArray, featureName, displayOption);
}	
PyObject *WindLabSimulationPy::computeWavePassageEffectValue(PyObject* args)
{
    PyObject* pyLocationJ = nullptr;
    PyObject* pyLocationK = nullptr;
    double frequency;
    double time;
    if (!PyArg_ParseTuple(args, "OOdd", &pyLocationJ, &pyLocationK, &frequency, &time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocationJ, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the first argument to be a vector object");

    if (!PyObject_TypeCheck(pyLocationK, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the second argument to be a vector object");

    Base::Vector3d* locationJ = static_cast<Base::VectorPy*>(pyLocationJ)->getVectorPtr();
    Base::Vector3d* locationK = static_cast<Base::VectorPy*>(pyLocationK)->getVectorPtr();

    std::complex<double> resValue;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->computeWavePassageEffectValue(*locationJ, *locationK, frequency, time, resValue, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

     return returnResult5(resValue, featureName);
}	

PyObject* WindLabSimulationPy::simulate(PyObject* args)
{
    int sampleIndex = -1;
    if (!PyArg_ParseTuple(args, "|i", &sampleIndex))
        return nullptr;

    cube resArray;
    std::string featureName;

    bool result = getWindLabSimulationPtr()->simulate(resArray, featureName);
    if (!result)
    {
        PyErr_SetString(PyExc_RuntimeError, "The computation has failed.\n");
        return nullptr;
    }

    if (sampleIndex >= 0 && sampleIndex < getWindLabSimulationPtr()->getSimulationData()->numberOfSample.getValue())
    {
        Eigen::Tensor<double, 2> matrix_at_k = resArray.chip(sampleIndex, 2);
        Eigen::Map<Eigen::MatrixXd> matrix_k(matrix_at_k.data(), matrix_at_k.dimension(0), matrix_at_k.dimension(1));
        mat ResultMatrix = matrix_k;
        return returnResult4(ResultMatrix, featureName);
    }
    else
    {
        return returnResult7(resArray, featureName);
    }

}


PyObject* WindLabSimulationPy::setActiveFeature(PyObject* args)
{
    PyObject* feature = nullptr;
        if (!PyArg_ParseTuple(args, "O", &feature))
        throw Py::Exception();

    if (!PyObject_TypeCheck(feature, &App::RPSFeaturePy::Type))
        throw Py::TypeError("Expect the argument to be a RPS feature object");

        App::RPSFeature* feat = static_cast<App::RPSFeaturePy*>(feature)->getRPSFeaturePtr();
    if (feat)
       getWindLabSimulationPtr()->setActiveFeature(feat);

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* WindLabSimulationPy::getActiveFeature(PyObject* args)
{
    const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
    App::RPSFeature* feat = getWindLabSimulationPtr()->getActiveFeature(QString::fromLatin1(group));
    if (feat)
        return Py::new_reference_to(feat->getPyObject());
    }
    PY_CATCH
}

PyObject* WindLabSimulationPy::getAllFeatures(PyObject* args)
{
     const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
    std::vector<App::RPSFeature*> features = getWindLabSimulationPtr()->getAllFeatures(QString::fromLatin1(group));
    for (std::vector<App::RPSFeature*>::iterator j = features.begin(); j != features.end(); ++j) {
        res.append(Py::asObject((*j)->getPyObject()));
     }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}