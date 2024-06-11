#include "PreCompiled.h"
#include "SineModulation.h"
#include <math.h>
#include <Mod/WindLabTools/App/modulation/SineModulationPy.h>

using namespace WindLabTools;

SineModulation::SineModulation()
{

}

SineModulation::~SineModulation()
{

}

double  SineModulation::computeModulation(const double &time, const double &pulseDuration)
{
    double value = sin(3.14*time / pulseDuration);

    return value;
}

PyObject* SineModulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new SineModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}