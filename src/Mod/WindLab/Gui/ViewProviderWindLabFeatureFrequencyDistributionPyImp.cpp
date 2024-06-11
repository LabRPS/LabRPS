#include "PreCompiled.h"

#include "ViewProviderWindLabFeatureFrequencyDistributionPy.h"
#include "ViewProviderWindLabFeatureFrequencyDistributionPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeatureFrequencyDistribution.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeatureFrequencyDistributionPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeatureFrequencyDistribution object>");
}

PyObject* ViewProviderWindLabFeatureFrequencyDistributionPy::computeFrequencyValue(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureFrequencyDistribution* vp = this->getViewProviderWindLabFeatureFrequencyDistributionPtr();
    if (vp)
    {
        bool ok = vp->computeFrequencyValue();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureFrequencyDistributionPy::computeFrequenciesVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureFrequencyDistribution* vp = this->getViewProviderWindLabFeatureFrequencyDistributionPtr();
    if (vp)
    {
        bool ok = vp->computeFrequenciesVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeatureFrequencyDistributionPy::computeFrequenciesMatrixFP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeatureFrequencyDistribution* vp = this->getViewProviderWindLabFeatureFrequencyDistributionPtr();
    if (vp)
    {
        bool ok = vp->computeFrequenciesMatrixFP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}
PyObject *ViewProviderWindLabFeatureFrequencyDistributionPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeatureFrequencyDistributionPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
