#include "PreCompiled.h"

#include "ViewProviderSeaLabFeatureTableToolPy.h"
#include "ViewProviderSeaLabFeatureTableToolPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderSeaLabFeatureTableTool.h"

using namespace SeaLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderSeaLabFeatureTableToolPy::representation(void) const
{
    return std::string("<ViewProviderSeaLabFeatureTableTool object>");
}

PyObject* ViewProviderSeaLabFeatureTableToolPy::tableToolCompute(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderSeaLabFeatureTableTool* vp = this->getViewProviderSeaLabFeatureTableToolPtr();
    if (vp)
    {
        bool ok = vp->tableToolCompute();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderSeaLabFeatureTableToolPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderSeaLabFeatureTableToolPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
