#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureVariancePy.h"
#include "ViewProviderWindLabFeatureVariancePy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureVariance.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureVariancePy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureVariance object>");
}

PyObject* ViewProviderWindLabFeatureVariancePy::computeVarianceValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureVariance* vp = this->getViewProviderWindLabFeatureVariancePtr();
    if (vp)
    {
        bool ok = vp->computeVarianceValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureVariancePy::computeVarianceVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureVariance* vp = this->getViewProviderWindLabFeatureVariancePtr();
    if (vp) {
        bool ok = vp->computeVarianceVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureVariancePy::computeVarianceVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureVariance* vp = this->getViewProviderWindLabFeatureVariancePtr();
    if (vp) {
        bool ok = vp->computeVarianceVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureVariancePy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureVariancePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
