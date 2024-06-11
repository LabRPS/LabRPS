#include "PreCompiled.h"
#include "HarrisSpectrum.h"
#include <math.h>
#include <Mod/WindLabTools/App/spectrum/HarrisSpectrumPy.h>

using namespace WindLabTools;

HarrisSpectrum::HarrisSpectrum()
{

}

HarrisSpectrum::~HarrisSpectrum()
{

}

double  HarrisSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &shearVelocity, const double &meanSpeed10)
{
    const double towPi = 2*22.0/7.0;
    const double a = 1800.0;
    const double K = 0.4; //Karman constant
    const double freq = (a*frequency / meanSpeed10)/towPi;
    const double numer = std::pow(freq,2);
    const double denom = std::pow(2+numer, 5.0/6.0);
    const double dPSD = 4.0 * K * shearVelocity * shearVelocity*(numer/denom);
    return dPSD/towPi;
}


PyObject* HarrisSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new HarrisSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}