#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureRoughnessPy.h"
#include "ViewProviderWindLabFeatureRoughnessPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureRoughness.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureRoughnessPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureRoughness object>");
}

PyObject* ViewProviderWindLabFeatureRoughnessPy::computeRoughnessValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureRoughness* vp = this->getViewProviderWindLabFeatureRoughnessPtr();
    if (vp)
    {
        bool ok = vp->computeRoughnessValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureRoughnessPy::computeRoughnessVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureRoughness* vp = this->getViewProviderWindLabFeatureRoughnessPtr();
    if (vp)
    {
        bool ok = vp->computeRoughnessVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureRoughnessPy::computeRoughnessVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureRoughness* vp = this->getViewProviderWindLabFeatureRoughnessPtr();
    if (vp) {
        bool ok = vp->computeRoughnessVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}
PyObject *ViewProviderWindLabFeatureRoughnessPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureRoughnessPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
