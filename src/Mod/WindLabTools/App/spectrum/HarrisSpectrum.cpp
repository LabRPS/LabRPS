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
    const double x = (1800.0 * frequency / meanSpeed10);
    const double xx = std::pow(x,2);
    const double denominator = std::pow(2+xx, 5.0/6.0);
    const double dPSD = 0.4 * shearVelocity * shearVelocity * xx/denominator/frequency;
    return dPSD;
}


PyObject* HarrisSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new HarrisSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}