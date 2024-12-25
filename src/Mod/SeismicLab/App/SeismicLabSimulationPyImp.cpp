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
#include "SeismicLabSimulation.h"
#include <Base/TypePy.h>

// inclusion of the generated files (generated out of SeismicLabSimulationPy.xml)
#include "SeismicLabSimulationPy.h"
#include "SeismicLabSimulationPy.cpp"
#include <Mod/SeismicLabAPI/App/SeismicLabSimulationData.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <App/RPSFeaturePy.h>
#include <Base/Console.h>



using namespace SeismicLab;
using namespace SeismicLabAPI;

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


std::string SeismicLabSimulationPy::representation(void) const
{
    std::stringstream str;
    str << "<SeismicLab Simulation: " << getSeismicLabSimulationPtr()->Label.getValue() << ">";
    return str.str();
}

PyObject* SeismicLabSimulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    return new SeismicLabSimulationPy(new SeismicLabSimulation());
}

// constructor method
int SeismicLabSimulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* SeismicLabSimulationPy::run(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    return Py::new_reference_to(Py::Long(getSeismicLabSimulationPtr()->run()));
}

PyObject* SeismicLabSimulationPy::stop(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    return Py::new_reference_to(Py::Long(getSeismicLabSimulationPtr()->stop()));
}

PyObject* SeismicLabSimulationPy::getPhenomenonName(PyObject *args)
{
    Py::String phenomenonName(Py::String(getSeismicLabSimulationPtr()->getPhenomenonName()));
    return Py::new_reference_to(phenomenonName);
}

PyObject* SeismicLabSimulationPy::getSimulationData(PyObject *args)
{
    SeismicLabSimulationData* simData = getSeismicLabSimulationPtr()->getSimulationData();
    if (simData)
    return Py::new_reference_to(simData->getPyObject());

    Py_Return;
}

PyObject* SeismicLabSimulationPy::getActiveCoherence(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveCoherence();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveCorrelation(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveCorrelation();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveCumulativeProbabilityDistribution(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveCumulativeProbabilityDistribution();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveFrequencyDistribution(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveFrequencyDistribution();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}

    PyObject* SeismicLabSimulationPy::getActiveKurtosis(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveKurtosis();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveLocationDistribution(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveLocationDistribution();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveMeanAcceleration(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveMeanAcceleration();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveModulation(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveModulation();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActivePeakFactor(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActivePeakFactor();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveProbabilityDensityFunction(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveProbabilityDensityFunction();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActivePSDDecompositionMethod(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActivePSDDecompositionMethod();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveRandomness(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveRandomness();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}

    PyObject* SeismicLabSimulationPy::getActiveShearVelocityOfFlow(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveShearVelocityOfFlow();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveSimulationMethod(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveSimulationMethod();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveSkewness(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveSkewness();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveStandardDeviation(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveStandardDeviation();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}

    PyObject* SeismicLabSimulationPy::getActiveUserDefinedRPSObject(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveUserDefinedRPSObject();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveVariance(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveVariance();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveWavePassageEffect(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveWavePassageEffect();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveSpectrum(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveSpectrum();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}

    PyObject* SeismicLabSimulationPy::getActiveMatrixTool(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveMatrixTool();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeismicLabSimulationPy::getActiveTableTool(PyObject* args){
    App::DocumentObject* feat = getSeismicLabSimulationPtr()->getActiveTableTool();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}


PyObject* SeismicLabSimulationPy::findAllPluggedSeismicLabFeatures(PyObject* args)
{
    const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
     QStringList pluggedFeaturesForThisGroup = getSeismicLabSimulationPtr()->findAllPluggedSeismicLabFeatures(QString::fromLatin1(group));

     for (QStringList::ConstIterator pt = pluggedFeaturesForThisGroup.begin(); pt != pluggedFeaturesForThisGroup.end(); ++pt) {
        res.append(Py::String((*pt).toUtf8().constData()));
     }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}

PyObject* SeismicLabSimulationPy::findAllSeismicLabFeaturesOfThisType(PyObject* args)
{
    const char* sType;
    if (!PyArg_ParseTuple(args, "s", &sType))
    return nullptr;

    Base::Type type = Base::Type::getTypeIfDerivedFrom(sType, SeismicLabAPI::SeismicLabFeature::getClassTypeId(), true);
    if (type.isBad()) {
        std::stringstream str;
        str << "'" << sType << "' is not a SeismicLab feature type";
        throw Base::TypeError(str.str());
    }

    Py::List res;
    PY_TRY
    {
    std::vector<std::string> createdFeaturesOfThisType = getSeismicLabSimulationPtr()->findAllSeismicLabFeaturesOfThisType(type);

    for (std::vector<std::string>::const_iterator cf = createdFeaturesOfThisType.begin(); cf != createdFeaturesOfThisType.end(); ++cf) {
        res.append(Py::String(*cf));
    }
    return Py::new_reference_to(res);
    }
    PY_CATCH



}

PyObject* SeismicLabSimulationPy::getSeismicLabPluggableFeatures(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     Py::List res;
    PY_TRY
    {
    std::vector<QString> pluggeableFeatures = getSeismicLabSimulationPtr()->getSeismicLabPluggableFeatures();

    for (std::vector<QString>::const_iterator cf = pluggeableFeatures.begin(); cf != pluggeableFeatures.end(); ++cf) {
        res.append(Py::String((*cf).toUtf8().constData()));
    }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}

PyObject* SeismicLabSimulationPy::getRPSTypesOfPluggableFeatures(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     Py::List res;
    PY_TRY
    {
    std::vector<Base::Type> rpsTypesOfFeatures = getSeismicLabSimulationPtr()->getRPSTypesOfPluggableFeatures();

    Py::List res;
    for (std::vector<Base::Type>::iterator it = rpsTypesOfFeatures.begin(); it != rpsTypesOfFeatures.end(); ++it) {
        res.append(Py::asObject(new Base::TypePy(new Base::Type(*it))));
    }
    return Py::new_reference_to(res);

    }
    PY_CATCH
}


    // +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *SeismicLabSimulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int SeismicLabSimulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}

// +++ computation methods ++++++++++++++++++++++++++++++++++++++++

PyObject *SeismicLabSimulationPy::computeCrossCoherenceVectorF(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeCrossCoherenceVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);

    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeCrossCoherenceVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeCrossCoherenceVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeCrossCoherenceMatrixPP(PyObject* args)
{
    char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->computeCrossCoherenceMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

	
PyObject *SeismicLabSimulationPy::computeCrossCorrelationVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeCrossCorrelationVectorT(*locationJ, *locationK, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeCrossCorrelationMatrixPP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->computeCrossCorrelationMatrixPP(time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *SeismicLabSimulationPy::computeFrequenciesVectorF(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeFrequenciesVectorF(*locationJ, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    Py::List activeArray;
    for (int i = 0; i < dValVector.rows(); i++) {
    activeArray.append(Py::Float((dValVector(i))));
    }
    return boost::python::incref(activeArray.ptr());
}	
  
PyObject *SeismicLabSimulationPy::computeFrequenciesMatrixFP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->computeFrequenciesMatrixFP(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *SeismicLabSimulationPy::computeLocationCoordinateMatrixP3(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->computeLocationCoordinateMatrixP3(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *SeismicLabSimulationPy::computeMeanAccelerationVectorP(PyObject* args)
{
     double time;
     if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeismicLabSimulationPtr()->computeMeanAccelerationVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeMeanAccelerationVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeMeanAccelerationVectorT(*locationJ, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeModulationVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeModulationVectorT(*locationJ, frequency, dVarVector, dValVector, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeModulationVectorP(PyObject* args)
{
    double time = 0.0;
    double frequency = 0.0;

    if (!PyArg_ParseTuple(args, "dd", &frequency, & time))
    return nullptr;

    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeismicLabSimulationPtr()->computeModulationVectorP(frequency, time, dVarVector, dValVector, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeDecomposedCrossSpectrumVectorF(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeDecomposedCrossSpectrumVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeDecomposedCrossSpectrumVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeDecomposedCrossSpectrumVectorT(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeDecomposedCrossSpectrumMatrixPP(PyObject* args)
{
    char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->computeDecomposedCrossSpectrumMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

PyObject *SeismicLabSimulationPy::generateRandomMatrixFP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->generateRandomMatrixFP(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}

PyObject *SeismicLabSimulationPy::generateRandomCubeFPS(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    cube resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->generateRandomCubeFPS(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult7(resArray, featureName);
}
//-----------------------------------------------------------------------------------------------------------//

PyObject *SeismicLabSimulationPy::computeCrossSpectrumVectorF(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeCrossSpectrumVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeCrossSpectrumVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeCrossSpectrumVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeCrossSpectrumMatrixPP(PyObject* args)
{
   char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->computeCrossSpectrumMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

PyObject *SeismicLabSimulationPy::computeAutoSpectrumValue(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeAutoSpectrumValue(*location, frequency, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
    
PyObject *SeismicLabSimulationPy::computeAutoSpectrumVectorF(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeAutoSpectrumVectorF(*location, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeAutoSpectrumVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeAutoSpectrumVectorT(*location, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	
//-----------------------------------------------------------------------------------------------------
PyObject *SeismicLabSimulationPy::computeCrossCoherenceValue(PyObject* args)
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

     bool result = getSeismicLabSimulationPtr()->computeCrossCoherenceValue(*locationJ, *locationK, frequency, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult5(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeCrossCorrelationValue(PyObject* args)
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

     bool result = getSeismicLabSimulationPtr()->computeCrossCorrelationValue(*locationJ, *locationK, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeMeanAccelerationValue(PyObject* args)
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

     bool result = getSeismicLabSimulationPtr()->computeMeanAccelerationValue(*location, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeModulationValue(PyObject* args)
{
    PyObject* pyLocation = nullptr;
    double time = 0.0;
    double frequency = 0.0;

    if (!PyArg_ParseTuple(args, "Odd", &pyLocation, &frequency, & time))
    return nullptr;

    if (!PyObject_TypeCheck(pyLocation, &Base::VectorPy::Type))
        throw Py::TypeError("Expect the argument to be a vector object");

     Base::Vector3d* location = static_cast<Base::VectorPy*>(pyLocation)->getVectorPtr();

     double resValue;
     std::string featureName;

     bool result = getSeismicLabSimulationPtr()->computeModulationValue(*location, frequency, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeRandomValue(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     double resValue;
     std::string featureName;

     bool result = getSeismicLabSimulationPtr()->computeRandomValue(resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeCrossSpectrumValue(PyObject* args)
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

     bool result = getSeismicLabSimulationPtr()->computeCrossSpectrumValue(*locationJ, *locationK, frequency, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult5(resValue, featureName);
}	

PyObject *SeismicLabSimulationPy::computeFrequencyValue(PyObject* args)
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

     bool result = getSeismicLabSimulationPtr()->computeFrequencyValue(*location, index, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	


PyObject* SeismicLabSimulationPy::tableToolCompute(PyObject* args)
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

        bool result = getSeismicLabSimulationPtr()->tableToolCompute(inputMatrix, outputMatrix, featureName);
        if (!result)
        {
        Py_INCREF(Py_None);
        return Py_None;
        }
    }
    catch (const Py::Exception&) {
        throw;
    }
    
     return returnResult4(outputMatrix, featureName);
}	
PyObject* SeismicLabSimulationPy::matrixToolCompute(PyObject* args)
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

        bool result = getSeismicLabSimulationPtr()->matrixToolCompute(inputMatrix, outputMatrix, featureName);
        if (!result)
        {
        Py_INCREF(Py_None);
        return Py_None;
        }
    }
    catch (const Py::Exception&) {
        throw;
    }
    
     return returnResult4(outputMatrix, featureName);
}	
PyObject* SeismicLabSimulationPy::userDefinedRPSObjectCompute(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->userDefinedRPSObjectCompute(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *SeismicLabSimulationPy::computeCPDValue(PyObject* args)
{
     double x;
     if (!PyArg_ParseTuple(args, "d", &x))
    return nullptr;

     double resValue;
     std::string featureName;

     bool result = getSeismicLabSimulationPtr()->computeCPDValue(x, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject* SeismicLabSimulationPy::computeCPDVectorX(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeismicLabSimulationPtr()->computeCPDVectorX(dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeKurtosisValue(PyObject* args)
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

     bool result = getSeismicLabSimulationPtr()->computeKurtosisValue(*location, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeKurtosisVectorP(PyObject* args)
{
     double time;
     if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeismicLabSimulationPtr()->computeKurtosisVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeismicLabSimulationPy::computeKurtosisVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeKurtosisVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computePeakFactorValue(PyObject* args)
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

     bool result = getSeismicLabSimulationPtr()->computePeakFactorValue(*location, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computePeakFactorVectorP(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeKurtosisVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeismicLabSimulationPy::computePeakFactorVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computePeakFactorVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computePDFValue(PyObject* args)
{
    double x;
    if (!PyArg_ParseTuple(args, "d", &x))
    return nullptr;

     double resValue;
     std::string featureName;

     bool result = getSeismicLabSimulationPtr()->computePDFValue(x, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computePDFVectorX(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeismicLabSimulationPtr()->computePDFVectorX(dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	


PyObject *SeismicLabSimulationPy::computeShearVelocityOfFlowValue(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeShearVelocityOfFlowValue(*location, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeShearVelocityOfFlowVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeismicLabSimulationPtr()->computeShearVelocityOfFlowVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeismicLabSimulationPy::computeShearVelocityOfFlowVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeShearVelocityOfFlowVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeSkewnessValue(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeSkewnessValue(*location, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeSkewnessVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeismicLabSimulationPtr()->computeSkewnessVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeismicLabSimulationPy::computeSkewnessVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeSkewnessVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeStandardDeviationValue(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeStandardDeviationValue(*location, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeStandardDeviationVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeismicLabSimulationPtr()->computeStandardDeviationVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeismicLabSimulationPy::computeStandardDeviationVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeStandardDeviationVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeVarianceValue(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeVarianceValue(*location, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *SeismicLabSimulationPy::computeVarianceVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeismicLabSimulationPtr()->computeVarianceVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeismicLabSimulationPy::computeVarianceVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeVarianceVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeismicLabSimulationPy::computeWavePassageEffectVectorF(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeWavePassageEffectVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult2(dVarVector, dValVector, featureName);
}	
PyObject *SeismicLabSimulationPy::computeWavePassageEffectVectorT(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeWavePassageEffectVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult2(dVarVector, dValVector, featureName);
}	
PyObject *SeismicLabSimulationPy::computeWavePassageEffectMatrixPP(PyObject* args)
{
    char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->computeWavePassageEffectMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult3(resArray, featureName, displayOption);
}	
PyObject *SeismicLabSimulationPy::computeWavePassageEffectValue(PyObject* args)
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

    bool result = getSeismicLabSimulationPtr()->computeWavePassageEffectValue(*locationJ, *locationK, frequency, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult5(resValue, featureName);
}	

PyObject* SeismicLabSimulationPy::simulate(PyObject* args)
{
    int sampleIndex = -1;
    if (!PyArg_ParseTuple(args, "|i", &sampleIndex))
        return nullptr;
    
    cube resArray;
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->simulate(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    if (sampleIndex >= 0 && sampleIndex <= getSeismicLabSimulationPtr()->getSimulationData()->numberOfSample.getValue())
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
PyObject* SeismicLabSimulationPy::simulateInLargeScaleMode(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    std::string featureName;

    bool result = getSeismicLabSimulationPtr()->simulateInLargeScaleMode(featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }
}

PyObject* SeismicLabSimulationPy::setActiveFeature(PyObject* args)
{
    PyObject* feature = nullptr;
        if (!PyArg_ParseTuple(args, "O", &feature))
        throw Py::Exception();

    if (!PyObject_TypeCheck(feature, &App::RPSFeaturePy::Type))
        throw Py::TypeError("Expect the argument to be a RPS feature object");

        App::RPSFeature* feat = static_cast<App::RPSFeaturePy*>(feature)->getRPSFeaturePtr();
    if (feat)
       getSeismicLabSimulationPtr()->setActiveFeature(feat);

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* SeismicLabSimulationPy::getActiveFeature(PyObject* args)
{
    const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
    App::RPSFeature* feat = getSeismicLabSimulationPtr()->getActiveFeature(QString::fromLatin1(group));
    if (feat)
        return Py::new_reference_to(feat->getPyObject());
    }
    PY_CATCH
}

PyObject* SeismicLabSimulationPy::getAllFeatures(PyObject* args)
{
     const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
    std::vector<App::RPSFeature*> features = getSeismicLabSimulationPtr()->getAllFeatures(QString::fromLatin1(group));
    for (std::vector<App::RPSFeature*>::iterator j = features.begin(); j != features.end(); ++j) {
        res.append(Py::asObject((*j)->getPyObject()));
     }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}