#include "PreCompiled.h"
#include "PowerLawMeanWindSpeed.h"
#include <math.h>
#include <Mod/WindLabTools/App/meanWindSpeed/PowerLawMeanWindSpeedPy.h>

using namespace WindLabTools;

PowerLawMeanWindSpeed::PowerLawMeanWindSpeed()
{

}

PowerLawMeanWindSpeed::~PowerLawMeanWindSpeed()
{

}

double  PowerLawMeanWindSpeed::computeMeanWindSpeed(const double &height, const double &referenceHeight, const double &referenceMeanSpeed, const double &zeroPlanDisplacement, const double &dimensionlessPower)
{
    return pow((height - zeroPlanDisplacement) / referenceHeight, dimensionlessPower) * referenceMeanSpeed;
}

PyObject* PowerLawMeanWindSpeed::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new PowerLawMeanWindSpeedPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}