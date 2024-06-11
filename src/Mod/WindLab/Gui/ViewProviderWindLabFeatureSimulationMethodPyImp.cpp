#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureSimulationMethodPy.h"
#include "ViewProviderWindLabFeatureSimulationMethodPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureSimulationMethod.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureSimulationMethodPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureSimulationMethod object>");
}

PyObject* ViewProviderWindLabFeatureSimulationMethodPy::simulate(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureSimulationMethod* vp = this->getViewProviderWindLabFeatureSimulationMethodPtr();
    if (vp)
    {
        bool ok = vp->simulate();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureSimulationMethodPy::simulateInLargeScaleMode(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureSimulationMethod* vp = this->getViewProviderWindLabFeatureSimulationMethodPtr();
    if (vp)
    {
        bool ok = vp->simulateInLargeScaleMode();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureSimulationMethodPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureSimulationMethodPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
