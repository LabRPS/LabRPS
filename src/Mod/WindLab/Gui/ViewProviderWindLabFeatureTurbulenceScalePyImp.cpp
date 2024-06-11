#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureTurbulenceScalePy.h"
#include "ViewProviderWindLabFeatureTurbulenceScalePy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureTurbulenceScale.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureTurbulenceScalePy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureTurbulenceScale object>");
}

PyObject* ViewProviderWindLabFeatureTurbulenceScalePy::computeTurbulenceScaleValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTurbulenceScale* vp = this->getViewProviderWindLabFeatureTurbulenceScalePtr();
    if (vp)
    {
        bool ok = vp->computeTurbulenceScaleValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureTurbulenceScalePy::computeTurbulenceScaleVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTurbulenceScale* vp = this->getViewProviderWindLabFeatureTurbulenceScalePtr();
    if (vp)
    {
        bool ok = vp->computeTurbulenceScaleVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureTurbulenceScalePy::computeTurbulenceScaleVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTurbulenceScale* vp = this->getViewProviderWindLabFeatureTurbulenceScalePtr();
    if (vp)
    {
        bool ok = vp->computeTurbulenceScaleVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}
PyObject *ViewProviderWindLabFeatureTurbulenceScalePy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureTurbulenceScalePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
