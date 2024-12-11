#include "PreCompiled.h"
#include "KougioumtzoglouAndSpanoSpectrum.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/spectrum/KougioumtzoglouAndSpanoSpectrumPy.h>

using namespace SeismicLabTools;

KougioumtzoglouAndSpanoSpectrum::KougioumtzoglouAndSpanoSpectrum()
{

}

KougioumtzoglouAndSpanoSpectrum::~KougioumtzoglouAndSpanoSpectrum()
{

}

double  KougioumtzoglouAndSpanoSpectrum::computeKougioumtzoglouAndSpanoSpectrum(const double& frequency, const double& time, const double &constantS)
{
    double f = std::pow(frequency / (5.0 * 3.14), 2);
    double psd1 = std::exp(0.15 * time);
    double psd2 = time * time;
    double psd = constantS * f * psd1 * psd2 * std::exp(-f * time);
    return psd;
}

PyObject* KougioumtzoglouAndSpanoSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new KougioumtzoglouAndSpanoSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}