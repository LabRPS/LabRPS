#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureSkewnessPy.h"
#include "ViewProviderWindLabFeatureSkewnessPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureSkewness.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureSkewnessPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureSkewness object>");
}

PyObject* ViewProviderWindLabFeatureSkewnessPy::computeSkewnessValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureSkewness* vp = this->getViewProviderWindLabFeatureSkewnessPtr();
    if (vp)
    {
        bool ok = vp->computeSkewnessValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureSkewnessPy::computeSkewnessVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureSkewness* vp = this->getViewProviderWindLabFeatureSkewnessPtr();
    if (vp) {
        bool ok = vp->computeSkewnessVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureSkewnessPy::computeSkewnessVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureSkewness* vp = this->getViewProviderWindLabFeatureSkewnessPtr();
    if (vp) {
        bool ok = vp->computeSkewnessVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureSkewnessPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureSkewnessPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
