#include "PreCompiled.h"
#include "DominikEtAl2013.h"
#include <math.h>
#include <Mod/WindLabTools/App/modulation/DominikEtAl2013Py.h>

using namespace WindLabTools;

DominikEtAl2013::DominikEtAl2013()
{

}

DominikEtAl2013::~DominikEtAl2013()
{

}

double  DominikEtAl2013::computeModulationA(const double &time, const double &nonZeroUpperBound)
{
    double value = 0.0;
    if(time >= 0 && time <= nonZeroUpperBound)
    value = (exp(-0.025 * time) - exp(-0.05 * time)) / 0.25;
    return value;
}

double  DominikEtAl2013::computeModulationB(const double &time, const double &nonZeroUpperBound)
{
    double value = 0.0;
    if(time >= 0 && time <= nonZeroUpperBound)
    value = (exp(0.025 * time - 5) - exp(0.05 * time - 10)) / 0.25;
    return value;
}

PyObject* DominikEtAl2013::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new DominikEtAl2013Py(this), true);
    }
    return Py::new_reference_to(PythonObject);
}