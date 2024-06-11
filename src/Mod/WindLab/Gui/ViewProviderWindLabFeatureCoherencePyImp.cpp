#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureCoherencePy.h"
#include "ViewProviderWindLabFeatureCoherencePy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureCoherence.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureCoherencePy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureCoherence object>");
}

PyObject* ViewProviderWindLabFeatureCoherencePy::computeCrossCoherenceValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureCoherence* vp = this->getViewProviderWindLabFeatureCoherencePtr();
    if (vp)
    {
        bool ok = vp->ComputeCrossCoherenceValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureCoherencePy::computeCrossCoherenceVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureCoherence* vp = this->getViewProviderWindLabFeatureCoherencePtr();
    if (vp) {
        bool ok = vp->ComputeCrossCoherenceVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureCoherencePy::computeCrossCoherenceVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureCoherence* vp = this->getViewProviderWindLabFeatureCoherencePtr();
    if (vp) {
        bool ok = vp->ComputeCrossCoherenceVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureCoherencePy::computeCrossCoherenceMatrixPP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureCoherence* vp = this->getViewProviderWindLabFeatureCoherencePtr();
    if (vp) {
        bool ok = vp->ComputeCrossCoherenceMatrixPP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureCoherencePy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureCoherencePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
