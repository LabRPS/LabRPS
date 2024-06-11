#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureStandardDeviationPy.h"
#include "ViewProviderWindLabFeatureStandardDeviationPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureStandardDeviation.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureStandardDeviationPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureStandardDeviation object>");
}

PyObject* ViewProviderWindLabFeatureStandardDeviationPy::computeStandardDeviationValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureStandardDeviation* vp = this->getViewProviderWindLabFeatureStandardDeviationPtr();
    if (vp)
    {
        bool ok = vp->computeStandardDeviationValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureStandardDeviationPy::computeStandardDeviationVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureStandardDeviation* vp = this->getViewProviderWindLabFeatureStandardDeviationPtr();
    if (vp)
    {
        bool ok = vp->computeStandardDeviationVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureStandardDeviationPy::computeStandardDeviationVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureStandardDeviation* vp = this->getViewProviderWindLabFeatureStandardDeviationPtr();
    if (vp)
    {
        bool ok = vp->computeStandardDeviationVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureStandardDeviationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureStandardDeviationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
