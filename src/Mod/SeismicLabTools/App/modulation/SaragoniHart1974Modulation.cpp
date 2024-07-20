#include "PreCompiled.h"
#include "SaragoniHart1974Modulation.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/modulation/SaragoniHart1974ModulationPy.h>

using namespace SeismicLabTools;

SaragoniHart1974Modulation::SaragoniHart1974Modulation()
{

}

SaragoniHart1974Modulation::~SaragoniHart1974Modulation()
{

}

double  SaragoniHart1974Modulation::computeModulation(const double &time, const double &alphaOne, const double &alphaTwo, const double &alphaThree)
{
    double value = alphaOne * pow(time, alphaTwo - 1) * exp(-alphaThree * time);
    return value;
}

PyObject* SaragoniHart1974Modulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new SaragoniHart1974ModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}