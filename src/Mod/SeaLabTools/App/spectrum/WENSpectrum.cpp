#include "PreCompiled.h"
#include "WENSpectrum.h"
#include <math.h>
#include <Mod/SeaLabTools/App/spectrum/WENSpectrumPy.h>

using namespace SeaLabTools;

WENSpectrum::WENSpectrum()
{

}

WENSpectrum::~WENSpectrum()
{

}

// Study on Numerical Simulation and Electromagnetic Scattering of Time-Invariant Freak Waves, Eq.4
double  WENSpectrum::computeSpectrum(double frequency, double significantWaveHeight, double significantPeriod, double depthParameter, double tenMetersHeightMeanWindSpeed)
{
    double omega0 = 0.855 * 9.8 /tenMetersHeightMeanWindSpeed;
    double m0 = (1.00/16.00) * significantWaveHeight * significantWaveHeight;
    double p = 95.3 * pow(significantWaveHeight, 1.35) / pow(significantPeriod, 2.7);
    double Ww = 5.72 / significantPeriod;
    double m = 2 * (2 - depthParameter);
    double value = 0.00;
    if((frequency >= 0)&&(frequency<=1.15*Ww))
    value = (m0 * p/Ww) * exp(-95.00*(log(( p*(5.813 - 5.137*depthParameter))/((6.77 - 1.088*p+0.013*p*p)*(1.307 - 1.426*depthParameter)))*pow(frequency/omega0 -1,12.0/5.0)));
    else if(frequency>1.15*Ww)
    value = (m0/Ww) * (( 6.77 - 1.088*p+0.013*p*p)*(1.307 - 1.426*depthParameter)/(5.813 - 5.137*depthParameter)) *pow(1.15*Ww/frequency,m);
    return value;
}

PyObject* WENSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new WENSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}