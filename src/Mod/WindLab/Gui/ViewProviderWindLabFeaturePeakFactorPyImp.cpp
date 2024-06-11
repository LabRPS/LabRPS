#include "PreCompiled.h"

#include "ViewProviderWindLabFeaturePeakFactorPy.h"
#include "ViewProviderWindLabFeaturePeakFactorPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeaturePeakFactor.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeaturePeakFactorPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeaturePeakFactor object>");
}

PyObject* ViewProviderWindLabFeaturePeakFactorPy::computePeakFactorValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeaturePeakFactor* vp = this->getViewProviderWindLabFeaturePeakFactorPtr();
    if (vp)
    {
        bool ok = vp->computePeakFactorValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeaturePeakFactorPy::computePeakFactorVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeaturePeakFactor* vp = this->getViewProviderWindLabFeaturePeakFactorPtr();
    if (vp) {
        bool ok = vp->computePeakFactorVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeaturePeakFactorPy::computePeakFactorVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeaturePeakFactor* vp = this->getViewProviderWindLabFeaturePeakFactorPtr();
    if (vp) {
        bool ok = vp->computePeakFactorVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeaturePeakFactorPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeaturePeakFactorPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
