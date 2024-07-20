#include "PreCompiled.h"
#include "TrapezoidalModulation.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/modulation/TrapezoidalModulationPy.h>

using namespace SeismicLabTools;

TrapezoidalModulation::TrapezoidalModulation()
{

}

TrapezoidalModulation::~TrapezoidalModulation()
{

}

double  TrapezoidalModulation::computeModulation(const double &time, const double &riseTime, const double &levelTime, const double &maxTime)
{
    double value = 0.0;
    if ((time >= 0) && (time <= riseTime))
        value = time / riseTime;
    else if ((time > riseTime) && (time <= levelTime))
        value = 1.0;
    else if ((time > levelTime) && (time <= maxTime))
        value = (maxTime - time)/(maxTime - levelTime);
    return value;
}

PyObject* TrapezoidalModulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new TrapezoidalModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}