#include "PreCompiled.h"

#include "ViewProviderWindLabSimulationPy.h"
#include "ViewProviderWindLabSimulationPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabSimulation.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabSimulationPy::representation(void) const
{
    return std::string("<ViewProviderWindLabSimulation object>");
}


PyObject* ViewProviderWindLabSimulationPy::run(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    this->getViewProviderWindLabSimulationPtr()->run();

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabSimulationPy::stop(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    this->getViewProviderWindLabSimulationPtr()->stop();

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabSimulationPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabSimulationPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
