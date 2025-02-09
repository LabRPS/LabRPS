#include "PreCompiled.h"
#include "ISSCSpectrum.h"
#include <math.h>
#include <Mod/SeaLabTools/App/spectrum/ISSCSpectrumPy.h>

using namespace SeaLabTools;

ISSCSpectrum::ISSCSpectrum()
{

}

ISSCSpectrum::~ISSCSpectrum()
{

}

// Ocean Wave Mechanics, Applications in Marine Structures, by Dr. V. Sundar, P.133, Eq. 6.34
double  ISSCSpectrum::computeSpectrum(double frequency, double significantWaveHeight, double peakFrequency, double c1, double c2)
{
    double value = c1*pow(significantWaveHeight,2.0)*pow(peakFrequency, 4.0)/pow(frequency, 5.0)*exp(c2*pow(peakFrequency/frequency, 4.0));
    return value;
}

PyObject* ISSCSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ISSCSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}