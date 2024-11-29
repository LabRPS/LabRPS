#include "PreCompiled.h"
#include "VonKarmanSpectrum.h"
#include <math.h>
#include <Mod/WindLabTools/App/spectrum/VonKarmanSpectrumPy.h>

using namespace WindLabTools;

VonKarmanSpectrum::VonKarmanSpectrum()
{

}

VonKarmanSpectrum::~VonKarmanSpectrum()
{

}

double  VonKarmanSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &integralLengthScale, const double &standardDeviation, double Par1, double Par2)
{
    double dBuf1, dBuf2, f;

    double dPSD = 0.0;

    f = frequency * integralLengthScale / meanSpeed;
 
    dBuf1 = 1.0 + (Par2 * f * f);

    dBuf2 = pow(dBuf1, 5.0 / 6.0);

    dPSD = Par1 * standardDeviation * standardDeviation * f / dBuf2 / frequency;

    return dPSD;
}

double VonKarmanSpectrum::computeAcrossWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &integralLengthScale, const double &standardDeviation, double Par1, double Par2, double Par3)
{
    return 0.0;
}

double VonKarmanSpectrum::computeVerticalWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &integralLengthScale, const double &standardDeviation, double Par1, double Par2, double Par3)
{
    return 0.0;
}


PyObject* VonKarmanSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new VonKarmanSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}