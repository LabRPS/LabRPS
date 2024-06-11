#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureKurtosisPy.h"
#include "ViewProviderWindLabFeatureKurtosisPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureKurtosis.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureKurtosisPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureKurtosis object>");
}

PyObject* ViewProviderWindLabFeatureKurtosisPy::computeKurtosisValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureKurtosis* vp = this->getViewProviderWindLabFeatureKurtosisPtr();
    if (vp)
    {
        bool ok = vp->computeKurtosisValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureKurtosisPy::computeKurtosisVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureKurtosis* vp = this->getViewProviderWindLabFeatureKurtosisPtr();
    if (vp) {
        bool ok = vp->computeKurtosisVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureKurtosisPy::computeKurtosisVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureKurtosis* vp = this->getViewProviderWindLabFeatureKurtosisPtr();
    if (vp) {
        bool ok = vp->computeKurtosisVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureKurtosisPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureKurtosisPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
