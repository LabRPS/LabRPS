#include "PreCompiled.h"
#include "KaimalSpectrum.h"
#include <math.h>
#include <Mod/WindLabTools/App/spectrum/KaimalSpectrumPy.h>

using namespace WindLabTools;

KaimalSpectrum::KaimalSpectrum()
{

}

KaimalSpectrum::~KaimalSpectrum()
{

}

double  KaimalSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1, double Par2)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
//    const double Par1 = 200.0;
//    const double Par2 = 50.0;
    const double towPi = 2*22.0/7.0;

    dBuf1 = 1.0 + Par2 * frequency * height / (towPi*meanSpeed);

    dBuf2 = pow(dBuf1, 5.0 / 3.0);

    dPSD = Par1 * shearVelocity * shearVelocity * height / meanSpeed;

    dPSD /= dBuf2;

    dPSD /= towPi;

    return dPSD;
}

double KaimalSpectrum::computeAcrossWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1, double Par2)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
//    double Par1 = 17.0;
//    double Par2 = 9.5;
    const double towPi = 2*22.0/7.0;

    dBuf1 = 1.0 + Par2 * frequency * height / (towPi *meanSpeed);

    dBuf2 = pow(dBuf1, 5.0 / 3.0);

    dPSD = Par1 * shearVelocity * shearVelocity * height / meanSpeed;

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= towPi;

    return dPSD;
}

double KaimalSpectrum::computeVerticalWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1, double Par2)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
//    double Par1 = 2.0;
//    double Par2 = 5.3;
    const double towPi = 2*22.0/7.0;

    dBuf1 = (frequency * height / meanSpeed)/towPi;

    dBuf2 = 1.0 + Par2 *pow(dBuf1, 5.0 / 3.0);

    dPSD = Par1 * shearVelocity * shearVelocity * height / meanSpeed;

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= towPi;

    return dPSD;
}

PyObject* KaimalSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new KaimalSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}