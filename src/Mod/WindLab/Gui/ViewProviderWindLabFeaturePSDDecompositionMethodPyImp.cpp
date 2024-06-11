#include "PreCompiled.h"

#include "ViewProviderWindLabFeaturePSDDecompositionMethodPy.h"
#include "ViewProviderWindLabFeaturePSDDecompositionMethodPy.cpp"
#include <CXX/Objects.hxx>

#include "ViewProviderWindLabFeaturePSDDecompositionMethod.h"

using namespace WindLabGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderWindLabFeaturePSDDecompositionMethodPy::representation(void) const
{
    return std::string("<ViewProviderWindLabFeaturePSDDecompositionMethod object>");
}

PyObject* ViewProviderWindLabFeaturePSDDecompositionMethodPy::computeDecomposedCrossSpectrumVectorF(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeaturePSDDecompositionMethod* vp = this->getViewProviderWindLabFeaturePSDDecompositionMethodPtr();
    if (vp)
    {
        bool ok = vp->computeDecomposedCrossSpectrumVectorF();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeaturePSDDecompositionMethodPy::computeDecomposedCrossSpectrumVectorT(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeaturePSDDecompositionMethod* vp = this->getViewProviderWindLabFeaturePSDDecompositionMethodPtr();
    if (vp)
    {
        bool ok = vp->computeDecomposedCrossSpectrumVectorT();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject* ViewProviderWindLabFeaturePSDDecompositionMethodPy::computeDecomposedCrossSpectrumMatrixPP(PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
        return nullptr;

    ViewProviderWindLabFeaturePSDDecompositionMethod* vp = this->getViewProviderWindLabFeaturePSDDecompositionMethodPtr();
    if (vp)
    {
        bool ok = vp->computeDecomposedCrossSpectrumMatrixPP();
        return Py::new_reference_to(Py::Boolean(ok));
    }

    Py_RETURN_NONE;
}

PyObject *ViewProviderWindLabFeaturePSDDecompositionMethodPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}


int ViewProviderWindLabFeaturePSDDecompositionMethodPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
