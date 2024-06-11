#include "PreCompiled.h"
#include "DeavesHarrisMeanWindSpeed.h"
#include <math.h>
#include <Mod/WindLabTools/App/meanWindSpeed/DeavesHarrisMeanWindSpeedPy.h>

using namespace WindLabTools;

DeavesHarrisMeanWindSpeed::DeavesHarrisMeanWindSpeed()
{

}

DeavesHarrisMeanWindSpeed::~DeavesHarrisMeanWindSpeed()
{

}

double  DeavesHarrisMeanWindSpeed::computeMeanWindSpeed(const double &height, const double &terrainRoughness, const double &shearVelocity, const double &zeroPlanDisplacement, const double &latitude, const double &earthAngularVelocity, const double &beta)
{
    const double coriolisParameter = 2 * earthAngularVelocity * std::sin(latitude);
    const double gradientHeight = shearVelocity/(beta * coriolisParameter);
    const double ratio1 = (height - zeroPlanDisplacement)/terrainRoughness;
    const double ratio2 = (height - zeroPlanDisplacement)/gradientHeight;

    double meanSpeed = shearVelocity * (log(ratio1) + 5.75 * ratio2 - 1.88 * pow(ratio2, 2) - 1.33 * pow(ratio2, 3) + 0.25 * pow(ratio2, 4)) / 0.4;
    return meanSpeed;
}

PyObject* DeavesHarrisMeanWindSpeed::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new DeavesHarrisMeanWindSpeedPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}