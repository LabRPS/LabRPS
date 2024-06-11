#include "PreCompiled.h"
#include "GeneralizedKaimalSpectrum.h"
#include <math.h>
#include <Mod/WindLabTools/App/spectrum/GeneralizedKaimalSpectrumPy.h>

using namespace WindLabTools;

GeneralizedKaimalSpectrum::GeneralizedKaimalSpectrum()
{

}

GeneralizedKaimalSpectrum::~GeneralizedKaimalSpectrum()
{

}

double GeneralizedKaimalSpectrum::computeGeneralizedKaimalWindAutoSpectrum(const double &frequency,
                                                   const double &height,
                                                   const double &meanSpeed,
                                                   const double &shearVelocity,
                                                   const double &a,
                                                   const double &b,
                                                   const double &c,
                                                   const double &d,
                                                   const double &e,
                                                   const double &f,
                                                   const double &g,
                                                   const double &h,
                                                   const double &i,
                                                   const double &j)
{
    const double towPi = 2*22.0/7.0;
    const double freq = (frequency * height/(meanSpeed))/towPi;
    const double numer = a*freq*std::pow(b+(c*(std::pow(freq,d))),e);
    const double denom = f*std::pow(g+(h*(std::pow(freq,i))),j);
    const double psd = (shearVelocity*shearVelocity)*(numer/denom)/(frequency/towPi);

    return psd/towPi;
}

PyObject* GeneralizedKaimalSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new GeneralizedKaimalSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}