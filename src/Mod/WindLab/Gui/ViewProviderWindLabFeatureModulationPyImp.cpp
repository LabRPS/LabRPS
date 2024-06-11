#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureModulationPy.h"
#include "ViewProviderWindLabFeatureModulationPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureModulation.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureModulationPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureModulation object>");
}

PyObject* ViewProviderWindLabFeatureModulationPy::computeModulationValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureModulation* vp = this->getViewProviderWindLabFeatureModulationPtr();
    if (vp)
    {
        bool ok = vp->computeModulationValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureModulationPy::computeModulationVectorP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureModulation* vp = this->getViewProviderWindLabFeatureModulationPtr();
    if (vp) {
        bool ok = vp->computeModulationVectorP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureModulationPy::computeModulationVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureModulation* vp = this->getViewProviderWindLabFeatureModulationPtr();
    if (vp) {
        bool ok = vp->computeModulationVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureModulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureModulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
