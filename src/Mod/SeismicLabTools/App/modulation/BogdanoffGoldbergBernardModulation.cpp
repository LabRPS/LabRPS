#include "PreCompiled.h"
#include "BogdanoffGoldbergBernardModulation.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/modulation/BogdanoffGoldbergBernardModulationPy.h>

using namespace SeismicLabTools;

BogdanoffGoldbergBernardModulation::BogdanoffGoldbergBernardModulation()
{

}

BogdanoffGoldbergBernardModulation::~BogdanoffGoldbergBernardModulation()
{

}

double  BogdanoffGoldbergBernardModulation::computeModulation(const double &time, const double& coefficientOne, const double& coefficientTwo)
{
    double value = coefficientOne * time * exp(-coefficientTwo * time);
    return value;
}

PyObject* BogdanoffGoldbergBernardModulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new BogdanoffGoldbergBernardModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}