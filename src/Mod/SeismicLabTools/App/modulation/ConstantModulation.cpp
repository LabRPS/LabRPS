#include "PreCompiled.h"
#include "ConstantModulation.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/modulation/ConstantModulationPy.h>

using namespace SeismicLabTools;

ConstantModulation::ConstantModulation()
{

}

ConstantModulation::~ConstantModulation()
{

}

double  ConstantModulation::computeModulation(const double &time, const double &constantValue)
{
    return constantValue;
}

PyObject* ConstantModulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ConstantModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}