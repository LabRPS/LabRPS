#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureXSpectrumPy.h"
#include "ViewProviderWindLabFeatureXSpectrumPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureXSpectrum.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureXSpectrumPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureXSpectrum object>");
}

PyObject* ViewProviderWindLabFeatureXSpectrumPy::computeXCrossSpectrumValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureXSpectrum* vp = this->getViewProviderWindLabFeatureXSpectrumPtr();
    if (vp)
    {
        bool ok = vp->computeXCrossSpectrumValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureXSpectrumPy::computeXCrossSpectrumVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureXSpectrum* vp = this->getViewProviderWindLabFeatureXSpectrumPtr();
    if (vp) {
        bool ok = vp->computeXCrossSpectrumVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureXSpectrumPy::computeXCrossSpectrumVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureXSpectrum* vp = this->getViewProviderWindLabFeatureXSpectrumPtr();
    if (vp) {
        bool ok = vp->computeXCrossSpectrumVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureXSpectrumPy::computeXCrossSpectrumMatrixPP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureXSpectrum* vp = this->getViewProviderWindLabFeatureXSpectrumPtr();
    if (vp) {
        bool ok = vp->computeXCrossSpectrumMatrixPP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureXSpectrumPy::computeXAutoSpectrumValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureXSpectrum* vp = this->getViewProviderWindLabFeatureXSpectrumPtr();
    if (vp) {
        bool ok = vp->computeXAutoSpectrumValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureXSpectrumPy::computeXAutoSpectrumVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureXSpectrum* vp = this->getViewProviderWindLabFeatureXSpectrumPtr();
    if (vp) {
        bool ok = vp->computeXAutoSpectrumVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureXSpectrumPy::computeXAutoSpectrumVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureXSpectrum* vp = this->getViewProviderWindLabFeatureXSpectrumPtr();
    if (vp) {
        bool ok = vp->computeXAutoSpectrumVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureXSpectrumPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureXSpectrumPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
