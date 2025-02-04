#include "PreCompiled.h"
#include "ITTCSpectrum.h"
#include <math.h>
#include <Mod/SeaLabTools/App/spectrum/ITTCSpectrumPy.h>

using namespace SeaLabTools;

ITTCSpectrum::ITTCSpectrum()
{

}

ITTCSpectrum::~ITTCSpectrum()
{

}

double  ITTCSpectrum::computeSpectrum(double frequency, double significantWaveHeight, double alpha)
{
    double c1 = alpha * 9.8 * 9.8;
    double c2 = c1 * -4 * c1 / pow(significantWaveHeight, 2);
    double value = c1*pow(frequency, -5.0)*exp(c2*pow(frequency, -4.0));

    return value;
}

PyObject* ITTCSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ITTCSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}