#include "PreCompiled.h"
#include "DavenportSpectrum.h"
#include <math.h>
#include <Mod/WindLabTools/App/spectrum/DavenportSpectrumPy.h>

using namespace WindLabTools;

DavenportSpectrum::DavenportSpectrum()
{

}

DavenportSpectrum::~DavenportSpectrum()
{

}

double  DavenportSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &meanSpeed10)
{
    const double towPi = 2*22.0/7.0;
    const double a = 1200.0;
    const double K = 0.4; //Karman constant
    const double x = (a*frequency / meanSpeed10)/towPi;
    const double xx = std::pow(x,2);
    const double denom = std::pow(1+xx, 4.0/3.0);
    const double dPSD = 4.0 * K * meanSpeed10 * meanSpeed10*(x/denom);
    return dPSD/towPi;
}

PyObject* DavenportSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new DavenportSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}