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
#include "SeaLabSimulation.h"
#include <Base/TypePy.h>

// inclusion of the generated files (generated out of SeaLabSimulationPy.xml)
#include "SeaLabSimulationPy.h"
#include "SeaLabSimulationPy.cpp"
#include <Mod/SeaLabAPI/App/SeaLabSimulationData.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <App/RPSFeaturePy.h>
#include <Base/Console.h>



using namespace SeaLab;
using namespace SeaLabAPI;

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


std::string SeaLabSimulationPy::representation(void) const
{
    std::stringstream str;
    str << "<SeaLab Simulation: " << getSeaLabSimulationPtr()->Label.getValue() << ">";
    return str.str();
}

PyObject* SeaLabSimulationPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    return new SeaLabSimulationPy(new SeaLabSimulation());
}

// constructor method
int SeaLabSimulationPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* SeaLabSimulationPy::run(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    return Py::new_reference_to(Py::Long(getSeaLabSimulationPtr()->run()));
}

PyObject* SeaLabSimulationPy::stop(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
    return Py::new_reference_to(Py::Long(getSeaLabSimulationPtr()->stop()));
}

PyObject* SeaLabSimulationPy::getPhenomenonName(PyObject *args)
{
    Py::String phenomenonName(Py::String(getSeaLabSimulationPtr()->getPhenomenonName()));
    return Py::new_reference_to(phenomenonName);
}

PyObject* SeaLabSimulationPy::getSimulationData(PyObject *args)
{
    SeaLabSimulationData* simData = getSeaLabSimulationPtr()->getSimulationData();
    if (simData)
    return Py::new_reference_to(simData->getPyObject());

    Py_Return;
}

PyObject* SeaLabSimulationPy::getActiveCoherence(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveCoherence();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveCorrelation(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveCorrelation();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveCumulativeProbabilityDistribution(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveCumulativeProbabilityDistribution();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveFrequencyDistribution(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveFrequencyDistribution();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}

    PyObject* SeaLabSimulationPy::getActiveKurtosis(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveKurtosis();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveLocationDistribution(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveLocationDistribution();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveMeanAcceleration(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveMeanAcceleration();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveModulation(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveModulation();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActivePeakFactor(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActivePeakFactor();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveProbabilityDensityFunction(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveProbabilityDensityFunction();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActivePSDDecompositionMethod(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActivePSDDecompositionMethod();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveRandomness(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveRandomness();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}

    PyObject* SeaLabSimulationPy::getActiveShearVelocityOfFlow(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveShearVelocityOfFlow();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveSimulationMethod(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveSimulationMethod();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveSkewness(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveSkewness();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveStandardDeviation(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveStandardDeviation();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}

    PyObject* SeaLabSimulationPy::getActiveUserDefinedRPSObject(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveUserDefinedRPSObject();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveVariance(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveVariance();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveWavePassageEffect(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveWavePassageEffect();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveSpectrum(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveSpectrum();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}

    PyObject* SeaLabSimulationPy::getActiveMatrixTool(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveMatrixTool();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}
    PyObject* SeaLabSimulationPy::getActiveTableTool(PyObject* args){
    App::DocumentObject* feat = getSeaLabSimulationPtr()->getActiveTableTool();
    if (feat)
    return Py::new_reference_to(feat->getPyObject());

    Py_Return;
}


PyObject* SeaLabSimulationPy::findAllPluggedSeaLabFeatures(PyObject* args)
{
    const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
     QStringList pluggedFeaturesForThisGroup = getSeaLabSimulationPtr()->findAllPluggedSeaLabFeatures(QString::fromLatin1(group));

     for (QStringList::ConstIterator pt = pluggedFeaturesForThisGroup.begin(); pt != pluggedFeaturesForThisGroup.end(); ++pt) {
        res.append(Py::String((*pt).toUtf8().constData()));
     }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}

PyObject* SeaLabSimulationPy::findAllSeaLabFeaturesOfThisType(PyObject* args)
{
    const char* sType;
    if (!PyArg_ParseTuple(args, "s", &sType))
    return nullptr;

    Base::Type type = Base::Type::getTypeIfDerivedFrom(sType, SeaLabAPI::SeaLabFeature::getClassTypeId(), true);
    if (type.isBad()) {
        std::stringstream str;
        str << "'" << sType << "' is not a SeaLab feature type";
        throw Base::TypeError(str.str());
    }

    Py::List res;
    PY_TRY
    {
    std::vector<std::string> createdFeaturesOfThisType = getSeaLabSimulationPtr()->findAllSeaLabFeaturesOfThisType(type);

    for (std::vector<std::string>::const_iterator cf = createdFeaturesOfThisType.begin(); cf != createdFeaturesOfThisType.end(); ++cf) {
        res.append(Py::String(*cf));
    }
    return Py::new_reference_to(res);
    }
    PY_CATCH



}

PyObject* SeaLabSimulationPy::getSeaLabPluggableFeatures(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     Py::List res;
    PY_TRY
    {
    std::vector<QString> pluggeableFeatures = getSeaLabSimulationPtr()->getSeaLabPluggableFeatures();

    for (std::vector<QString>::const_iterator cf = pluggeableFeatures.begin(); cf != pluggeableFeatures.end(); ++cf) {
        res.append(Py::String((*cf).toUtf8().constData()));
    }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}

PyObject* SeaLabSimulationPy::getRPSTypesOfPluggableFeatures(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     Py::List res;
    PY_TRY
    {
    std::vector<Base::Type> rpsTypesOfFeatures = getSeaLabSimulationPtr()->getRPSTypesOfPluggableFeatures();

    Py::List res;
    for (std::vector<Base::Type>::iterator it = rpsTypesOfFeatures.begin(); it != rpsTypesOfFeatures.end(); ++it) {
        res.append(Py::asObject(new Base::TypePy(new Base::Type(*it))));
    }
    return Py::new_reference_to(res);

    }
    PY_CATCH
}


    // +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *SeaLabSimulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int SeaLabSimulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}

// +++ computation methods ++++++++++++++++++++++++++++++++++++++++

PyObject *SeaLabSimulationPy::computeCrossCoherenceVectorF(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeCrossCoherenceVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);

    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeCrossCoherenceVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeCrossCoherenceVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeCrossCoherenceMatrixPP(PyObject* args)
{
    char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->computeCrossCoherenceMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

	
PyObject *SeaLabSimulationPy::computeCrossCorrelationVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeCrossCorrelationVectorT(*locationJ, *locationK, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeCrossCorrelationMatrixPP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->computeCrossCorrelationMatrixPP(time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *SeaLabSimulationPy::computeFrequenciesVectorF(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeFrequenciesVectorF(*locationJ, dValVector, featureName);
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
  
PyObject *SeaLabSimulationPy::computeFrequenciesMatrixFP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->computeFrequenciesMatrixFP(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *SeaLabSimulationPy::computeLocationCoordinateMatrixP3(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->computeLocationCoordinateMatrixP3(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *SeaLabSimulationPy::computeMeanAccelerationVectorP(PyObject* args)
{
     double time;
     if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeaLabSimulationPtr()->computeMeanAccelerationVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeMeanAccelerationVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeMeanAccelerationVectorT(*locationJ, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeModulationVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeModulationVectorT(*locationJ, frequency, dVarVector, dValVector, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeModulationVectorP(PyObject* args)
{
    double time = 0.0;
    double frequency = 0.0;
    if (!PyArg_ParseTuple(args, "dd", &frequency, &time))
    return nullptr;

    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeaLabSimulationPtr()->computeModulationVectorP(frequency, time, dVarVector, dValVector, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeDecomposedCrossSpectrumVectorF(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeDecomposedCrossSpectrumVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeDecomposedCrossSpectrumVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeDecomposedCrossSpectrumVectorT(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeDecomposedCrossSpectrumMatrixPP(PyObject* args)
{
    char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->computeDecomposedCrossSpectrumMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

PyObject *SeaLabSimulationPy::generateRandomMatrixFP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->generateRandomMatrixFP(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}

PyObject *SeaLabSimulationPy::generateRandomCubeFPS(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    cube resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->generateRandomCubeFPS(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult7(resArray, featureName);
}
	
//-----------------------------------------------------------------------------------------------------------//

PyObject *SeaLabSimulationPy::computeCrossSpectrumVectorF(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeCrossSpectrumVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeCrossSpectrumVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeCrossSpectrumVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult2(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeCrossSpectrumMatrixPP(PyObject* args)
{
   char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->computeCrossSpectrumMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult3(resArray, featureName, displayOption);
}	

PyObject *SeaLabSimulationPy::computeAutoSpectrumValue(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeAutoSpectrumValue(*location, frequency, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
    
PyObject *SeaLabSimulationPy::computeAutoSpectrumVectorF(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeAutoSpectrumVectorF(*location, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeAutoSpectrumVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeAutoSpectrumVectorT(*location, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult1(dVarVector, dValVector, featureName);
}	
//-----------------------------------------------------------------------------------------------------
PyObject *SeaLabSimulationPy::computeCrossCoherenceValue(PyObject* args)
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

     bool result = getSeaLabSimulationPtr()->computeCrossCoherenceValue(*locationJ, *locationK, frequency, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult5(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeCrossCorrelationValue(PyObject* args)
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

     bool result = getSeaLabSimulationPtr()->computeCrossCorrelationValue(*locationJ, *locationK, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeMeanAccelerationValue(PyObject* args)
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

     bool result = getSeaLabSimulationPtr()->computeMeanAccelerationValue(*location, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeModulationValue(PyObject* args)
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

     bool result = getSeaLabSimulationPtr()->computeModulationValue(*location, frequency, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeRandomValue(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;

     double resValue;
     std::string featureName;

     bool result = getSeaLabSimulationPtr()->computeRandomValue(resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeCrossSpectrumValue(PyObject* args)
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

     bool result = getSeaLabSimulationPtr()->computeCrossSpectrumValue(*locationJ, *locationK, frequency, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult5(resValue, featureName);
}	

PyObject *SeaLabSimulationPy::computeFrequencyValue(PyObject* args)
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

     bool result = getSeaLabSimulationPtr()->computeFrequencyValue(*location, index, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	


PyObject* SeaLabSimulationPy::tableToolCompute(PyObject* args)
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

        bool result = getSeaLabSimulationPtr()->tableToolCompute(inputMatrix, outputMatrix, featureName);
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
PyObject* SeaLabSimulationPy::matrixToolCompute(PyObject* args)
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

        bool result = getSeaLabSimulationPtr()->matrixToolCompute(inputMatrix, outputMatrix, featureName);
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
PyObject* SeaLabSimulationPy::userDefinedRPSObjectCompute(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    mat resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->userDefinedRPSObjectCompute(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult4(resArray, featureName);
}	

PyObject *SeaLabSimulationPy::computeCPDValue(PyObject* args)
{
     double x;
     if (!PyArg_ParseTuple(args, "d", &x))
    return nullptr;

     double resValue;
     std::string featureName;

     bool result = getSeaLabSimulationPtr()->computeCPDValue(x, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject* SeaLabSimulationPy::computeCPDVectorX(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeaLabSimulationPtr()->computeCPDVectorX(dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeKurtosisValue(PyObject* args)
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

     bool result = getSeaLabSimulationPtr()->computeKurtosisValue(*location, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeKurtosisVectorP(PyObject* args)
{
     double time;
     if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeaLabSimulationPtr()->computeKurtosisVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeaLabSimulationPy::computeKurtosisVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeKurtosisVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computePeakFactorValue(PyObject* args)
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

     bool result = getSeaLabSimulationPtr()->computePeakFactorValue(*location, time, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computePeakFactorVectorP(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeKurtosisVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeaLabSimulationPy::computePeakFactorVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computePeakFactorVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computePDFValue(PyObject* args)
{
    double x;
    if (!PyArg_ParseTuple(args, "d", &x))
    return nullptr;

     double resValue;
     std::string featureName;

     bool result = getSeaLabSimulationPtr()->computePDFValue(x, resValue, featureName);
     if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
     }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computePDFVectorX(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeaLabSimulationPtr()->computePDFVectorX(dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	


PyObject *SeaLabSimulationPy::computeShearVelocityOfFlowValue(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeShearVelocityOfFlowValue(*location, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeShearVelocityOfFlowVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeaLabSimulationPtr()->computeShearVelocityOfFlowVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeaLabSimulationPy::computeShearVelocityOfFlowVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeShearVelocityOfFlowVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeSkewnessValue(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeSkewnessValue(*location, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeSkewnessVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeaLabSimulationPtr()->computeSkewnessVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeaLabSimulationPy::computeSkewnessVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeSkewnessVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeStandardDeviationValue(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeStandardDeviationValue(*location, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeStandardDeviationVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeaLabSimulationPtr()->computeStandardDeviationVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeaLabSimulationPy::computeStandardDeviationVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeStandardDeviationVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeVarianceValue(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeVarianceValue(*location, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult6(resValue, featureName);
}	
PyObject *SeaLabSimulationPy::computeVarianceVectorP(PyObject* args)
{
    double time;
    if (!PyArg_ParseTuple(args, "d", &time))
    return nullptr;
    
    std::string featureName;
    vec dVarVector;
    vec dValVector;

    bool result = getSeaLabSimulationPtr()->computeVarianceVectorP(time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	
PyObject *SeaLabSimulationPy::computeVarianceVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeVarianceVectorT(*location, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult1(dVarVector, dValVector, featureName);
}	

PyObject *SeaLabSimulationPy::computeWavePassageEffectVectorF(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeWavePassageEffectVectorF(*locationJ, *locationK, time, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult2(dVarVector, dValVector, featureName);
}	
PyObject *SeaLabSimulationPy::computeWavePassageEffectVectorT(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeWavePassageEffectVectorT(*locationJ, *locationK, frequency, dVarVector, dValVector, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult2(dVarVector, dValVector, featureName);
}	
PyObject *SeaLabSimulationPy::computeWavePassageEffectMatrixPP(PyObject* args)
{
    char* displayOption;
    double frequency;
    double time;

    if (!PyArg_ParseTuple(args, "dd|s", &frequency, &time, &displayOption))
    return nullptr;
    
    cx_mat resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->computeWavePassageEffectMatrixPP(frequency, time, resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

    return returnResult3(resArray, featureName, displayOption);
}	
PyObject *SeaLabSimulationPy::computeWavePassageEffectValue(PyObject* args)
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

    bool result = getSeaLabSimulationPtr()->computeWavePassageEffectValue(*locationJ, *locationK, frequency, time, resValue, featureName);
    if (!result) {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult5(resValue, featureName);
}	

PyObject* SeaLabSimulationPy::simulate(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    cube resArray;
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->simulate(resArray, featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }

     return returnResult7(resArray, featureName);
}
PyObject* SeaLabSimulationPy::simulateInLargeScaleMode(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
    return nullptr;
    
    std::string featureName;

    bool result = getSeaLabSimulationPtr()->simulateInLargeScaleMode(featureName);
    if (!result)
    {
    Py_INCREF(Py_None);
    return Py_None;
    }
}

PyObject* SeaLabSimulationPy::setActiveFeature(PyObject* args)
{
    PyObject* feature = nullptr;
        if (!PyArg_ParseTuple(args, "O", &feature))
        throw Py::Exception();

    if (!PyObject_TypeCheck(feature, &App::RPSFeaturePy::Type))
        throw Py::TypeError("Expect the argument to be a RPS feature object");

        App::RPSFeature* feat = static_cast<App::RPSFeaturePy*>(feature)->getRPSFeaturePtr();
    if (feat)
       getSeaLabSimulationPtr()->setActiveFeature(feat);

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* SeaLabSimulationPy::getActiveFeature(PyObject* args)
{
    const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
    App::RPSFeature* feat = getSeaLabSimulationPtr()->getActiveFeature(QString::fromLatin1(group));
    if (feat)
        return Py::new_reference_to(feat->getPyObject());
    }
    PY_CATCH
}

PyObject* SeaLabSimulationPy::getAllFeatures(PyObject* args)
{
     const char* group;
    if (!PyArg_ParseTuple(args, "s", &group))
    return nullptr;
    Py::List res;
    PY_TRY
    {
    std::vector<App::RPSFeature*> features = getSeaLabSimulationPtr()->getAllFeatures(QString::fromLatin1(group));
    for (std::vector<App::RPSFeature*>::iterator j = features.begin(); j != features.end(); ++j) {
        res.append(Py::asObject((*j)->getPyObject()));
     }
    return Py::new_reference_to(res);
    }
    PY_CATCH
}