#include "PreCompiled.h"
#include "GaussianSwellSpectrum.h"
#include <Mod/SeaLabTools/App/spectrum/GaussianSwellSpectrumPy.h>
#include <math.h>

#define PI_ 3.14159265358979323846

using namespace SeaLabTools;

GaussianSwellSpectrum::GaussianSwellSpectrum()
{

}

GaussianSwellSpectrum::~GaussianSwellSpectrum()
{

}

double  GaussianSwellSpectrum::computeSpectrum(double frequency, double significantWaveHeight, double peakFrequency, double sigma)
{
    double value = (significantWaveHeight/4) * (significantWaveHeight/4) * (1/(sigma * sqrt(2*PI_))) * exp(-(frequency - peakFrequency) * (frequency - peakFrequency) /(2*sigma*sigma));
    return value;
}

PyObject* GaussianSwellSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new GaussianSwellSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}