#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureYSpectrumPy.h"
#include "ViewProviderWindLabFeatureYSpectrumPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureYSpectrum.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureYSpectrumPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureYSpectrum object>");
}

PyObject* ViewProviderWindLabFeatureYSpectrumPy::computeYCrossSpectrumValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureYSpectrum* vp = this->getViewProviderWindLabFeatureYSpectrumPtr();
    if (vp) {
        bool ok = vp->computeYCrossSpectrumValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureYSpectrumPy::computeYCrossSpectrumVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureYSpectrum* vp = this->getViewProviderWindLabFeatureYSpectrumPtr();
    if (vp) {
        bool ok = vp->computeYCrossSpectrumVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureYSpectrumPy::computeYCrossSpectrumVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureYSpectrum* vp = this->getViewProviderWindLabFeatureYSpectrumPtr();
    if (vp) {
        bool ok = vp->computeYCrossSpectrumVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureYSpectrumPy::computeYCrossSpectrumMatrixPP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureYSpectrum* vp = this->getViewProviderWindLabFeatureYSpectrumPtr();
    if (vp) {
        bool ok = vp->computeYCrossSpectrumMatrixPP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureYSpectrumPy::computeYAutoSpectrumValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureYSpectrum* vp = this->getViewProviderWindLabFeatureYSpectrumPtr();
    if (vp) {
        bool ok = vp->computeYAutoSpectrumValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureYSpectrumPy::computeYAutoSpectrumVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureYSpectrum* vp = this->getViewProviderWindLabFeatureYSpectrumPtr();
    if (vp) {
        bool ok = vp->computeYAutoSpectrumVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureYSpectrumPy::computeYAutoSpectrumVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureYSpectrum* vp = this->getViewProviderWindLabFeatureYSpectrumPtr();
    if (vp) {
        bool ok = vp->computeYAutoSpectrumVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureYSpectrumPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureYSpectrumPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
