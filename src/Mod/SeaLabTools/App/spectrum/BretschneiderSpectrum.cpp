#include "PreCompiled.h"
#include "BretschneiderSpectrum.h"
#include <math.h>
#include <Mod/SeaLabTools/App/spectrum/BretschneiderSpectrumPy.h>

using namespace SeaLabTools;

BretschneiderSpectrum::BretschneiderSpectrum()
{

}

BretschneiderSpectrum::~BretschneiderSpectrum()
{

}

double  BretschneiderSpectrum::computeSpectrum(double frequency, double significantWaveHeight, double modalFrequency, double c1, double c2)
{
    double value = c1*pow(significantWaveHeight,2.0)*pow(modalFrequency, 4.0)/pow(frequency, 5.0)*exp(c2*pow(modalFrequency/frequency, 4.0));
    return value;
}

PyObject* BretschneiderSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new BretschneiderSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}