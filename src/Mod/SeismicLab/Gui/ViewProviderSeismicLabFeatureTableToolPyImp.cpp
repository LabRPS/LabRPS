#include "PreCompiled.h"

#include "ViewProviderSeismicLabFeatureTableToolPy.h"
#include "ViewProviderSeismicLabFeatureTableToolPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderSeismicLabFeatureTableTool.h"

using namespace SeismicLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderSeismicLabFeatureTableToolPy::representation(void) const
{
    return std::string("<ViewProviderSeismicLabFeatureTableTool object>");
}

PyObject* ViewProviderSeismicLabFeatureTableToolPy::tableToolCompute(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderSeismicLabFeatureTableTool* vp = this->getViewProviderSeismicLabFeatureTableToolPtr();
    if (vp)
    {
        bool ok = vp->tableToolCompute();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderSeismicLabFeatureTableToolPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderSeismicLabFeatureTableToolPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
