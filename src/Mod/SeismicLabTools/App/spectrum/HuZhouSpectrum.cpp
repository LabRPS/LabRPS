#include "PreCompiled.h"
#include "HuZhouSpectrum.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/spectrum/HuZhouSpectrumPy.h>

using namespace SeismicLabTools;

HuZhouSpectrum::HuZhouSpectrum()
{

}

HuZhouSpectrum::~HuZhouSpectrum()
{

}

double  HuZhouSpectrum::computeHuZhouSpectrum(const double& frequency, const double& groundNaturalFrequency, const double &groundDampingRatio, const double &lowFrequencyControlFactor, const double &constantSpectralIntensity)
{
    double psd1 = std::pow(groundNaturalFrequency, 4);
    double psd2 = 4 * std::pow(groundNaturalFrequency * groundDampingRatio * frequency, 2);
    double psd3 = (std::pow(groundNaturalFrequency, 2) - std::pow(frequency, 2)) * (std::pow(groundNaturalFrequency, 2) - std::pow(frequency, 2));
    double psd4 = std::pow(frequency, 6);
    double psd5 = std::pow(lowFrequencyControlFactor, 6);
    double psd = ((psd1 + psd2) / (psd3 + psd2)) * (psd4 / (psd4 + psd5)) * constantSpectralIntensity; //S(K-T) * Filter * groundShakingIntensity
    return psd;
}

PyObject* HuZhouSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new HuZhouSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}