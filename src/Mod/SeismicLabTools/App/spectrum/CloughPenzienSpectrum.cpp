#include "PreCompiled.h"
#include "CloughPenzienSpectrum.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/spectrum/CloughPenzienSpectrumPy.h>

using namespace SeismicLabTools;

CloughPenzienSpectrum::CloughPenzienSpectrum()
{

}

CloughPenzienSpectrum::~CloughPenzienSpectrum()
{

}

double  CloughPenzienSpectrum::computeCloughPenzienSpectrum(const double& frequency, const double& groundNaturalFrequency, const double &groundDampingRatio, const double &secondFilterLayerFrequency, const double &secondFilterLayerDampingRatio, const double &constantSpectralIntensity)
{
    double psd1 = std::pow(groundNaturalFrequency, 4);
    double psd2 = 4 * std::pow(groundNaturalFrequency * groundDampingRatio * frequency, 2);
    double psd3 = (std::pow(groundNaturalFrequency, 2) - std::pow(frequency, 2)) * (std::pow(groundNaturalFrequency, 2) - std::pow(frequency, 2));
    double psd4 = (std::pow(secondFilterLayerFrequency, 2) - std::pow(frequency, 2)) * (std::pow(secondFilterLayerFrequency, 2) - std::pow(frequency, 2));
    double psd5 = 4 * std::pow(secondFilterLayerFrequency * secondFilterLayerDampingRatio * frequency, 2);
    double psd6 = std::pow(frequency, 4);
    double psd = ((psd1 + psd2) / (psd3 + psd2)) * (psd6 / (psd4 + psd5)) * constantSpectralIntensity; //S(K-T) * Filter * groundShakingIntensity
    return psd;
}

PyObject* CloughPenzienSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new CloughPenzienSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}