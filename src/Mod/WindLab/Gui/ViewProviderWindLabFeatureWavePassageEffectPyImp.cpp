#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureWavePassageEffectPy.h"
#include "ViewProviderWindLabFeatureWavePassageEffectPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureWavePassageEffect.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureWavePassageEffectPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureWavePassageEffect object>");
}

PyObject* ViewProviderWindLabFeatureWavePassageEffectPy::computeWavePassageEffectVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureWavePassageEffect* vp = this->getViewProviderWindLabFeatureWavePassageEffectPtr();
    if (vp)
    {
        bool ok = vp->computeWavePassageEffectVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureWavePassageEffectPy::computeWavePassageEffectVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureWavePassageEffect* vp = this->getViewProviderWindLabFeatureWavePassageEffectPtr();
    if (vp)
    {
        bool ok = vp->computeWavePassageEffectVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureWavePassageEffectPy::computeWavePassageEffectMatrixPP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureWavePassageEffect* vp = this->getViewProviderWindLabFeatureWavePassageEffectPtr();
    if (vp)
    {
        bool ok = vp->computeWavePassageEffectMatrixPP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureWavePassageEffectPy::computeWavePassageEffectValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureWavePassageEffect* vp = this->getViewProviderWindLabFeatureWavePassageEffectPtr();
    if (vp)
    {
        bool ok = vp->computeWavePassageEffectValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureWavePassageEffectPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureWavePassageEffectPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
