#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureCorrelationPy.h"
#include "ViewProviderWindLabFeatureCorrelationPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureCorrelation.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureCorrelationPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureCorrelation object>");
}

PyObject* ViewProviderWindLabFeatureCorrelationPy::computeCrossCorrelationValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureCorrelation* vp = this->getViewProviderWindLabFeatureCorrelationPtr();
    if (vp)
    {
        bool ok = vp->computeCrossCorrelationValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureCorrelationPy::computeCrossCorrelationVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureCorrelation* vp = this->getViewProviderWindLabFeatureCorrelationPtr();
    if (vp) {
        bool ok = vp->computeCrossCorrelationVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureCorrelationPy::computeCrossCorrelationMatrixPP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureCorrelation* vp = this->getViewProviderWindLabFeatureCorrelationPtr();
    if (vp) {
        bool ok = vp->computeCrossCorrelationMatrixPP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureCorrelationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureCorrelationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
