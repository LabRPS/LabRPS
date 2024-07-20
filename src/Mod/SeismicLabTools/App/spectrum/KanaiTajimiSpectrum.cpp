#include "PreCompiled.h"
#include "KanaiTajimiSpectrum.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/spectrum/KanaiTajimiSpectrumPy.h>

using namespace SeismicLabTools;

KanaiTajimiSpectrum::KanaiTajimiSpectrum()
{

}

KanaiTajimiSpectrum::~KanaiTajimiSpectrum()
{

}

double  KanaiTajimiSpectrum::computeKanaiTajimiSpectrum(const double& frequency, const double& groundNaturalFrequency, const double &groundDampingRatio, const double &constantSpectralIntensity)
{
    double psd1 = std::pow(groundNaturalFrequency, 4);
    double psd2 = 4 * std::pow(groundNaturalFrequency * groundDampingRatio * frequency, 2);
    double psd3 = (std::pow(groundNaturalFrequency, 2) - std::pow(frequency, 2)) * (std::pow(groundNaturalFrequency, 2) - std::pow(frequency, 2));
    double psd = ((psd1 + psd2) / (psd3 + psd2)) * constantSpectralIntensity; //S(K-T) * groundShakingIntensity
    return psd;
}

PyObject* KanaiTajimiSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new KanaiTajimiSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}