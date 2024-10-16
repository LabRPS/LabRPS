#include "PreCompiled.h"
#include "JonswapSpectrum.h"
#include <math.h>
#include <Mod/SeaLabTools/App/spectrum/JonswapSpectrumPy.h>

using namespace SeaLabTools;

JonswapSpectrum::JonswapSpectrum()
{

}

JonswapSpectrum::~JonswapSpectrum()
{

}

double  JonswapSpectrum::computeSpectrum(double frequency, double significantWaveHeight, double peakPeriod, bool autoGamma, bool autoSigma, double gamma, double sigma1, double sigma2)
{
    double peakFrequency = 1 / peakPeriod;
    double sigma;

    if (autoGamma){
        if (peakPeriod/sqrt(significantWaveHeight) <= 3.6) gamma = 5.0;
        else if (peakPeriod/sqrt(significantWaveHeight) > 3.6 && peakPeriod/sqrt(significantWaveHeight) <= 5) gamma = exp(5.75-1.15*peakPeriod/sqrt(significantWaveHeight));
        else gamma = 1;
    }

    if (autoSigma){
        if (frequency <= peakFrequency) sigma = 0.07;
        else sigma = 0.09;
    }
    else{
        if (frequency <= peakFrequency) sigma = sigma1;
        else sigma = sigma2;
    }

    double f_ratio = frequency / peakFrequency;

    double value = 0.3125*pow(significantWaveHeight,2.0)*peakPeriod*pow(f_ratio,-5.0)*exp(-1.25*pow(f_ratio,-4.0))*(1.0-0.287*log(gamma))*pow(gamma,exp(-0.5*pow((f_ratio-1.0)/sigma,2.0)));

    return value;
}

PyObject* JonswapSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new JonswapSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}