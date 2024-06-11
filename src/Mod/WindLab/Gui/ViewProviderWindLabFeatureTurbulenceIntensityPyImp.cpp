#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureTurbulenceIntensityPy.h"
#include "ViewProviderWindLabFeatureTurbulenceIntensityPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureTurbulenceIntensity.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureTurbulenceIntensityPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureTurbulenceIntensity object>");
}

PyObject* ViewProviderWindLabFeatureTurbulenceIntensityPy::computeTurbulenceIntensityValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTurbulenceIntensity* vp = this->getViewProviderWindLabFeatureTurbulenceIntensityPtr();
    if (vp)
    {
        bool ok = vp->computeTurbulenceIntensityValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureTurbulenceIntensityPy::computeTurbulenceIntensityVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTurbulenceIntensity* vp = this->getViewProviderWindLabFeatureTurbulenceIntensityPtr();
    if (vp)
    {
        bool ok = vp->computeTurbulenceIntensityVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureTurbulenceIntensityPy::computeTurbulenceIntensityVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTurbulenceIntensity* vp = this->getViewProviderWindLabFeatureTurbulenceIntensityPtr();
    if (vp)
    {
        bool ok = vp->computeTurbulenceIntensityVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureTurbulenceIntensityPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureTurbulenceIntensityPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
