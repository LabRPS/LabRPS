#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureLocationDistributionPy.h"
#include "ViewProviderWindLabFeatureLocationDistributionPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureLocationDistribution.h"
#include <boost/python/copy_const_reference.hpp>

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureLocationDistributionPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureLocationDistribution object>");
}

PyObject* ViewProviderWindLabFeatureLocationDistributionPy::computeLocationCoordinateMatrixP3(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureLocationDistribution* vp = this->getViewProviderWindLabFeatureLocationDistributionPtr();
    if (vp)
    {
        bool ok = vp->ComputeLocationCoordinateMatrixP3();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureLocationDistributionPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

PyObject* ViewProviderWindLabFeatureLocationDistributionPy::getComputationResultVariableVector(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
   
    ViewProviderWindLabFeatureLocationDistribution* vp = this->getViewProviderWindLabFeatureLocationDistributionPtr();
   
    vec dVarVector;

    if (vp)
    {
        bool ok = vp->getComputationResultVariableVector(dVarVector);

        if (!ok)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    Py::List resList;
    for (int j = 0; j < dVarVector.cols(); j++) {
        resList.append(Py::Float((dVarVector.coeff(j))));
    }

    return boost::python::incref(resList.ptr());
}
PyObject* ViewProviderWindLabFeatureLocationDistributionPy::getComputationResultValueVector(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
        return nullptr;
   
    ViewProviderWindLabFeatureLocationDistribution* vp = this->getViewProviderWindLabFeatureLocationDistributionPtr();
   
    vec dVarVeltor;

    if (vp)
    {
        bool ok = vp->getComputationResultValueVector(dVarVeltor);

        if (!ok)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    Py::List resList;
    for (int j = 0; j < dVarVeltor.cols(); j++) {
        resList.append(Py::Float((dVarVeltor.coeff(j))));
    }

    return boost::python::incref(resList.ptr());
}
PyObject* ViewProviderWindLabFeatureLocationDistributionPy::getComputationResultComplexValueVector(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
        return nullptr;
   
    ViewProviderWindLabFeatureLocationDistribution* vp = this->getViewProviderWindLabFeatureLocationDistributionPtr();
   
    cx_vec dVarVeltor_cx;

    if (vp)
    {
        bool ok = vp->getComputationResultComplexValueVector(dVarVeltor_cx);

        if (!ok)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    Py::List resList;
    for (int j = 0; j < dVarVeltor_cx.cols(); j++) {
        resList.append(Py::Float((dVarVeltor_cx(j).real())));
        resList.append(Py::Float((dVarVeltor_cx(j).imag())));
    }

    return boost::python::incref(resList.ptr());
}
PyObject* ViewProviderWindLabFeatureLocationDistributionPy::getComputationResultMatrix(PyObject* args)
{
     if (!PyArg_ParseTuple(args, ""))
        return nullptr;
   
    ViewProviderWindLabFeatureLocationDistribution* vp = this->getViewProviderWindLabFeatureLocationDistributionPtr();
   
    mat resultMatrix;

    if (vp)
    {
        bool ok = vp->getComputationResultMatrix(resultMatrix);

        if (!ok)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
    }

   Py::List resList;
    for (int i = 0; i < resultMatrix.rows(); i++) {
        Py::List row;
        for (int j = 0; j < resultMatrix.cols(); j++) {
            row.append(Py::Float((resultMatrix.coeff(i, j))));
        }
        resList.append(row);
    }
    return boost::python::incref(resList.ptr());
}
PyObject* ViewProviderWindLabFeatureLocationDistributionPy::getComputationResultComplexMatrix(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;
   
    ViewProviderWindLabFeatureLocationDistribution* vp = this->getViewProviderWindLabFeatureLocationDistributionPtr();
   
    cx_mat resultMatrix_cx;

    if (vp)
    {
        bool ok = vp->getComputationResultComplexMatrix(resultMatrix_cx);

        if (!ok)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
    }

   Py::List resList;
    for (int i = 0; i < resultMatrix_cx.rows(); i++) {
        Py::List row;
        for (int j = 0; j < resultMatrix_cx.cols(); j++) {
            row.append(Py::Float((resultMatrix_cx.coeff(i, j).real())));
        }
        resList.append(row);
    }
    return boost::python::incref(resList.ptr());
}

int ViewProviderWindLabFeatureLocationDistributionPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
