#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureUserDefinedRPSObjectPy.h"
#include "ViewProviderWindLabFeatureUserDefinedRPSObjectPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureUserDefinedRPSObject.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureUserDefinedRPSObjectPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureUserDefinedRPSObject object>");
}

PyObject* ViewProviderWindLabFeatureUserDefinedRPSObjectPy::userDefinedRPSObjectCompute(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureUserDefinedRPSObject* vp = this->getViewProviderWindLabFeatureUserDefinedRPSObjectPtr();
    if (vp)
    {
        bool ok = vp->userDefinedRPSObjectCompute();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureUserDefinedRPSObjectPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureUserDefinedRPSObjectPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
