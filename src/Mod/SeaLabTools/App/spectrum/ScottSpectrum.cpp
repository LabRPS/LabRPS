#include "PreCompiled.h"
#include "ScottSpectrum.h"
#include <math.h>
#include <Mod/SeaLabTools/App/spectrum/ScottSpectrumPy.h>

using namespace SeaLabTools;

ScottSpectrum::ScottSpectrum()
{

}

ScottSpectrum::~ScottSpectrum()
{

}

double  ScottSpectrum::computeSpectrum(double frequency, double significantWaveHeight, double peakFrequency)
{
    double value = 0.00;
    if((frequency - peakFrequency > -0.26) && (frequency - peakFrequency < 1.65))
        value = 0.214 * pow(significantWaveHeight, 2) * exp(-pow((frequency - peakFrequency) * (frequency - peakFrequency)/(0.065 * (frequency - peakFrequency + 0.26)), 0.5));
    return value;
}

PyObject* ScottSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ScottSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}