#include "PreCompiled.h"
#include "ExponentialModulation.h"
#include <math.h>
#include <Mod/WindLabTools/App/modulation/ExponentialModulationPy.h>

using namespace WindLabTools;

ExponentialModulation::ExponentialModulation()
{

}

ExponentialModulation::~ExponentialModulation()
{

}

double  ExponentialModulation::computeModulation(const double &time, const double &timeOfMax, const double &stormLength)
{
    double value = exp(-(time - timeOfMax)*(time - timeOfMax) / (2 * stormLength*stormLength));

    return value;
}

PyObject* ExponentialModulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ExponentialModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}