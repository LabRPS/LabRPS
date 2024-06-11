#include "PreCompiled.h"
#include "ThreeParametersModulation.h"
#include <math.h>
#include <Mod/WindLabTools/App/modulation/ThreeParametersModulationPy.h>

using namespace WindLabTools;

ThreeParametersModulation::ThreeParametersModulation()
{

}

ThreeParametersModulation::~ThreeParametersModulation()
{

}

double  ThreeParametersModulation::computeModulation(const double &time, const double &alpha, const double &betta, const double &lambda)
{
    double value = alpha * (pow(time, betta))*(exp(-lambda * time));

    return value;
}

PyObject* ThreeParametersModulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ThreeParametersModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}