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

double  DavenportSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &shearVelocity, const double &meanSpeed10)
{
    const double x = (1200.0 * frequency / meanSpeed10);
    const double xx = std::pow(x,2);
    const double denominator = std::pow(1+xx, 4.0/3.0);
    const double dPSD = 0.4 * shearVelocity * shearVelocity * xx/denominator/frequency;
    return dPSD;
}

PyObject* DavenportSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new DavenportSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

