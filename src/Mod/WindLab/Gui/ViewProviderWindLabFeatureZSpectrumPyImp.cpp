#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureZSpectrumPy.h"
#include "ViewProviderWindLabFeatureZSpectrumPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureZSpectrum.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureZSpectrumPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureZSpectrum object>");
}

PyObject* ViewProviderWindLabFeatureZSpectrumPy::computeZCrossSpectrumValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureZSpectrum* vp = this->getViewProviderWindLabFeatureZSpectrumPtr();
    if (vp) {
        bool ok = vp->computeZCrossSpectrumValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureZSpectrumPy::computeZCrossSpectrumVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureZSpectrum* vp = this->getViewProviderWindLabFeatureZSpectrumPtr();
    if (vp) {
        bool ok = vp->computeZCrossSpectrumVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureZSpectrumPy::computeZCrossSpectrumVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureZSpectrum* vp = this->getViewProviderWindLabFeatureZSpectrumPtr();
    if (vp) {
        bool ok = vp->computeZCrossSpectrumVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureZSpectrumPy::computeZCrossSpectrumMatrixPP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureZSpectrum* vp = this->getViewProviderWindLabFeatureZSpectrumPtr();
    if (vp) {
        bool ok = vp->computeZCrossSpectrumMatrixPP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureZSpectrumPy::computeZAutoSpectrumValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureZSpectrum* vp = this->getViewProviderWindLabFeatureZSpectrumPtr();
    if (vp) {
        bool ok = vp->computeZAutoSpectrumValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureZSpectrumPy::computeZAutoSpectrumVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureZSpectrum* vp = this->getViewProviderWindLabFeatureZSpectrumPtr();
    if (vp) {
        bool ok = vp->computeZAutoSpectrumVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureZSpectrumPy::computeZAutoSpectrumVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureZSpectrum* vp = this->getViewProviderWindLabFeatureZSpectrumPtr();
    if (vp) {
        bool ok = vp->computeZAutoSpectrumVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureZSpectrumPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureZSpectrumPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
