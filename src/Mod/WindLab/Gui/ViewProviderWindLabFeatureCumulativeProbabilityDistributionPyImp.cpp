#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureCumulativeProbabilityDistributionPy.h"
#include "ViewProviderWindLabFeatureCumulativeProbabilityDistributionPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureCumulativeProbabilityDistribution.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureCumulativeProbabilityDistributionPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureCumulativeProbabilityDistribution object>");
}

PyObject* ViewProviderWindLabFeatureCumulativeProbabilityDistributionPy::computeCPDValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureCumulativeProbabilityDistribution* vp = this->getViewProviderWindLabFeatureCumulativeProbabilityDistributionPtr();
    if (vp)
    {
        bool ok = vp->computeCPDValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureCumulativeProbabilityDistributionPy::computeCPDVectorX(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureCumulativeProbabilityDistribution* vp = this->getViewProviderWindLabFeatureCumulativeProbabilityDistributionPtr();
    if (vp)
    {
        bool ok = vp->computeCPDVectorX();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeatureCumulativeProbabilityDistributionPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureCumulativeProbabilityDistributionPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
