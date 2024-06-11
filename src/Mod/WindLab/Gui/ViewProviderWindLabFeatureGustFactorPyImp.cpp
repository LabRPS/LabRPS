#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureGustFactorPy.h"
#include "ViewProviderWindLabFeatureGustFactorPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureGustFactor.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureGustFactorPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureGustFactor object>");
}

PyObject* ViewProviderWindLabFeatureGustFactorPy::computeGustFactorValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureGustFactor* vp = this->getViewProviderWindLabFeatureGustFactorPtr();
    if (vp)
    {
        bool ok = vp->computeGustFactorValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureGustFactorPy::computeGustFactorVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureGustFactor* vp = this->getViewProviderWindLabFeatureGustFactorPtr();
    if (vp) {
        bool ok = vp->computeGustFactorVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureGustFactorPy::computeGustFactorVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureGustFactor* vp = this->getViewProviderWindLabFeatureGustFactorPtr();
    if (vp) {
        bool ok = vp->computeGustFactorVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureGustFactorPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureGustFactorPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
