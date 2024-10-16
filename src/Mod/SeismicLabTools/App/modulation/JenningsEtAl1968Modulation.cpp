#include "PreCompiled.h"
#include "JenningsEtAl1968Modulation.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/modulation/JenningsEtAl1968ModulationPy.h>

using namespace SeismicLabTools;

JenningsEtAl1968Modulation::JenningsEtAl1968Modulation()
{

}

JenningsEtAl1968Modulation::~JenningsEtAl1968Modulation()
{

}

double  JenningsEtAl1968Modulation::computeModulation(const double &time, const double &riseTime, const double &levelTime, const double &alpha, const double &power)
{
    double value = 0.0;
    if ((time >= 0) && (time <= riseTime))
        value = pow(time / riseTime, power);
    else if ((time > riseTime) && (time <= levelTime))
        value = 1.0;
    else if (time > levelTime)
        value = exp(-alpha *(time - levelTime));
    return value;
}

PyObject* JenningsEtAl1968Modulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new JenningsEtAl1968ModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}