#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureTableToolPy.h"
#include "ViewProviderWindLabFeatureTableToolPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureTableTool.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureTableToolPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureTableTool object>");
}

PyObject* ViewProviderWindLabFeatureTableToolPy::tableToolCompute(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureTableTool* vp = this->getViewProviderWindLabFeatureTableToolPtr();
    if (vp)
    {
        bool ok = vp->tableToolCompute();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureTableToolPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureTableToolPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
