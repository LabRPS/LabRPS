#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureMeanWindPy.h"
#include "ViewProviderWindLabFeatureMeanWindPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureMeanWind.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureMeanWindPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureMeanWind object>");
}

PyObject* ViewProviderWindLabFeatureMeanWindPy::computeMeanWindSpeedValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureMeanWind* vp = this->getViewProviderWindLabFeatureMeanWindPtr();
    if (vp)
    {
        bool ok = vp->computeMeanWindSpeedValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureMeanWindPy::computeMeanWindSpeedVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureMeanWind* vp = this->getViewProviderWindLabFeatureMeanWindPtr();
    if (vp) {
        bool ok = vp->computeMeanWindSpeedVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureMeanWindPy::computeMeanWindSpeedVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureMeanWind* vp = this->getViewProviderWindLabFeatureMeanWindPtr();
    if (vp) {
        bool ok = vp->computeMeanWindSpeedVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureMeanWindPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureMeanWindPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
