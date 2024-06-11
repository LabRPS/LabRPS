#include "PreCompiled.h"

#include "ViewProviderWindLabSimulationComparisonPy.h"
#include "ViewProviderWindLabSimulationComparisonPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabSimulationComparison.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabSimulationComparisonPy::representation(void) const
{
    return std::string("<ViewProviderWindLabSimulationComparison object>");
}

PyObject* ViewProviderWindLabSimulationComparisonPy::start(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    this->getViewProviderWindLabSimulationComparisonPtr()->start();

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabSimulationComparisonPy::stop(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    this->getViewProviderWindLabSimulationComparisonPtr()->stop();

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabSimulationComparisonPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabSimulationComparisonPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
