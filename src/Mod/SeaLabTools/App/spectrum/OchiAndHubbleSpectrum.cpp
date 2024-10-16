#include "PreCompiled.h"
#include "OchiAndHubbleSpectrum.h"
#include <math.h>
#include <Mod/SeaLabTools/App/spectrum/OchiAndHubbleSpectrumPy.h>

#define PI_ 3.14159265358979323846

using namespace SeaLabTools;

OchiAndHubbleSpectrum::OchiAndHubbleSpectrum()
{

}

OchiAndHubbleSpectrum::~OchiAndHubbleSpectrum()
{

}

double  OchiAndHubbleSpectrum::computeSpectrum(double frequency, double peakShape1, double peakShape2, double peakFrequency1, double peakFrequency2, double significantWaveHeight1, double significantWaveHeight2)
{
    double w1 = peakFrequency1 * 2.0 * PI_;
    double w2 = peakFrequency2 * 2.0 * PI_;
    double w = frequency * 2.0 * PI_;

    double S1 = 1./4. * pow(((4.0*peakShape1+1)/4.0)*pow(w1,4),peakShape1)/tgamma(peakShape1)*pow(significantWaveHeight1,2)/pow(w,4.0*peakShape1+1)*exp(-(4.0*peakShape1+1)/4.0*pow(w1/w,4));
    double S2 = 1./4. * pow(((4.0*peakShape2+1)/4.0)*pow(w2,4),peakShape2)/tgamma(peakShape2)*pow(significantWaveHeight2,2)/pow(w,4.0*peakShape2+1)*exp(-(4.0*peakShape2+1)/4.0*pow(w2/w,4));

    return S1+S2;
}

PyObject* OchiAndHubbleSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new OchiAndHubbleSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}