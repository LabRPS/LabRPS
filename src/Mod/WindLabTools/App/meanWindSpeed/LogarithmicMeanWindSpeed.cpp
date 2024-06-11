#include "PreCompiled.h"
#include "LogarithmicMeanWindSpeed.h"
#include <math.h>
#include <Mod/WindLabTools/App/meanWindSpeed/LogarithmicMeanWindSpeedPy.h>

using namespace WindLabTools;

LogarithmicMeanWindSpeed::LogarithmicMeanWindSpeed()
{

}

LogarithmicMeanWindSpeed::~LogarithmicMeanWindSpeed()
{

}

double  LogarithmicMeanWindSpeed::computeMeanWindSpeed(const double &height, const double &terrainRoughness, const double &shearVelocity, const double &zeroPlanDisplacement)
{
    return log((height - zeroPlanDisplacement) / terrainRoughness)*shearVelocity / 0.4;
}

PyObject* LogarithmicMeanWindSpeed::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new LogarithmicMeanWindSpeedPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}