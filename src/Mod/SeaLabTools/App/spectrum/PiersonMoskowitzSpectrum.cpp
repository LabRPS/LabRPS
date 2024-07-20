#include "PreCompiled.h"
#include "PiersonMoskowitzSpectrum.h"
#include <math.h>
#include <Mod/SeaLabTools/App/spectrum/PiersonMoskowitzSpectrumPy.h>

using namespace SeaLabTools;

PiersonMoskowitzSpectrum::PiersonMoskowitzSpectrum()
{

}

PiersonMoskowitzSpectrum::~PiersonMoskowitzSpectrum()
{

}

double  PiersonMoskowitzSpectrum::computeSpectrum(double frequency, double significantWaveHeight, double peakPeriod)
{
    double peakFrequency = 1 / peakPeriod;

    double f_ratio = frequency / peakFrequency;

    double value = 0.3125*pow(significantWaveHeight,2.0)*peakPeriod*pow(f_ratio,-5.0)*exp(-1.25*pow(f_ratio,-4.0));

    return value;
}

PyObject* PiersonMoskowitzSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new PiersonMoskowitzSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}