#include "PreCompiled.h"
#include "BoxCarModulation.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/modulation/BoxCarModulationPy.h>

using namespace SeismicLabTools;

BoxCarModulation::BoxCarModulation()
{

}

BoxCarModulation::~BoxCarModulation()
{

}

double  BoxCarModulation::computeModulation(const double &time, const double &scalingFactor, const double &strongMotionPeriod)
{
    double value = 0.0;
    if ((time >= 0) && (time <= strongMotionPeriod))
        value = scalingFactor;
    // else if (time > strongMotionPeriod)
    //     value = 0.0;
    return value;
}

PyObject* BoxCarModulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new BoxCarModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}