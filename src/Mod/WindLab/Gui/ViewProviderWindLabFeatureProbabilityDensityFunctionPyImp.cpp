#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureProbabilityDensityFunctionPy.h"
#include "ViewProviderWindLabFeatureProbabilityDensityFunctionPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureProbabilityDensityFunction.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureProbabilityDensityFunctionPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureProbabilityDensityFunction object>");
}

PyObject* ViewProviderWindLabFeatureProbabilityDensityFunctionPy::computePDFValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureProbabilityDensityFunction* vp = this->getViewProviderWindLabFeatureProbabilityDensityFunctionPtr();
    if (vp)
    {
        bool ok = vp->computePDFValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureProbabilityDensityFunctionPy::computePDFVectorX(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureProbabilityDensityFunction* vp =
        this->getViewProviderWindLabFeatureProbabilityDensityFunctionPtr();
    if (vp) {
        bool ok = vp->computePDFVectorX();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureProbabilityDensityFunctionPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureProbabilityDensityFunctionPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
