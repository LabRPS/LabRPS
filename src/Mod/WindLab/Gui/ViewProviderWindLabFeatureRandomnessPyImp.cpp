#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureRandomnessPy.h"
#include "ViewProviderWindLabFeatureRandomnessPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureRandomness.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureRandomnessPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureRandomness object>");
}

PyObject* ViewProviderWindLabFeatureRandomnessPy::GenerateRandomMatrixFP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureRandomness* vp = this->getViewProviderWindLabFeatureRandomnessPtr();
    if (vp)
    {
        bool ok = vp->generateRandomMatrixFP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}


PyObject *ViewProviderWindLabFeatureRandomnessPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureRandomnessPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
