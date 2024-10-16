#include "PreCompiled.h"
#include "WavePassageEffect.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/wavePassageEffect/WavePassageEffectPy.h>

using namespace SeismicLabTools;

WavePassageEffect::WavePassageEffect()
{

}

WavePassageEffect::~WavePassageEffect()
{

}

std::complex<double>  WavePassageEffect::computeWavePassageEffect(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &frequency, const double &apparentWaveVelocity)
{
    // the imaginary i
    std::complex<double> i(0, 1);
    double x2 = locationJ.x - locationK.x;
    double y2 = locationJ.y - locationK.y;
    double z2 = locationJ.z - locationK.z;
    double distanceJK = sqrt(x2 * x2 + y2 * y2 + z2 * z2);
    std::complex<double> wpe = exp(-i * distanceJK * frequency / apparentWaveVelocity);
    return wpe;
}

double  WavePassageEffect::computeApparentWaveVelocity(const double &velocityJ, const double &velocityK, const double &coefficient)
{
    return (22 / 7) * (velocityJ + velocityK) / coefficient;
}

PyObject* WavePassageEffect::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new WavePassageEffectPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}