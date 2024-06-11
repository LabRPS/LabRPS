#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureShearVelocityOfFlowPy.h"
#include "ViewProviderWindLabFeatureShearVelocityOfFlowPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureShearVelocityOfFlow.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureShearVelocityOfFlowPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureShearVelocityOfFlow object>");
}

PyObject* ViewProviderWindLabFeatureShearVelocityOfFlowPy::computeShearVelocityOfFlowValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureShearVelocityOfFlow* vp = this->getViewProviderWindLabFeatureShearVelocityOfFlowPtr();
    if (vp)
    {
        bool ok = vp->computeShearVelocityOfFlowValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureShearVelocityOfFlowPy::computeShearVelocityOfFlowVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureShearVelocityOfFlow* vp = this->getViewProviderWindLabFeatureShearVelocityOfFlowPtr();
    if (vp)
    {
        bool ok = vp->computeShearVelocityOfFlowVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureShearVelocityOfFlowPy::computeShearVelocityOfFlowVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureShearVelocityOfFlow* vp = this->getViewProviderWindLabFeatureShearVelocityOfFlowPtr();
    if (vp)
    {
        bool ok = vp->computeShearVelocityOfFlowVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}


PyObject *ViewProviderWindLabFeatureShearVelocityOfFlowPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureShearVelocityOfFlowPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
