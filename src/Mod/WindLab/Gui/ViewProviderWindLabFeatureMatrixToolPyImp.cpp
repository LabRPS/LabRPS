#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureMatrixToolPy.h"
#include "ViewProviderWindLabFeatureMatrixToolPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureMatrixTool.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureMatrixToolPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureMatrixTool object>");
}

PyObject* ViewProviderWindLabFeatureMatrixToolPy::MatrixToolCompute(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureMatrixTool* vp = this->getViewProviderWindLabFeatureMatrixToolPtr();
    if (vp)
    {
        bool ok = vp->MatrixToolCompute();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureMatrixToolPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureMatrixToolPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
