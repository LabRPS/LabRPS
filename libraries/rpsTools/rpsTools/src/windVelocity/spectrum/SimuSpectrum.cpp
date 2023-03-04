#include "SimuSpectrum.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

SimuSpectrum::SimuSpectrum()
{

}

SimuSpectrum::~SimuSpectrum()
{

}

double  SimuSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1, double Par2)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
//    double Par1 = 105.0;
//    double Par2 = 33.0;
    const double towPi = 2*22.0/7.0;

    dBuf1 = 1.0 + (Par2 * frequency * height / meanSpeed)/towPi;

    dBuf2 = pow(dBuf1, 5.0 / 3.0);

    dPSD = Par1 * shearVelocity * shearVelocity * height / meanSpeed;

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= towPi;

    return dPSD;
}

double SimuSpectrum::computeAcrossWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1, double Par2)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
//    double Par1 = 17.0;
//    double Par2 = 9.5;
    const double towPi = 2*22.0/7.0;

    dBuf1 = 1.0 + (Par2 * frequency * height / meanSpeed)/towPi;

    dBuf2 = pow(dBuf1, 5.0 / 3.0);

    dPSD = Par1 * shearVelocity * shearVelocity * height / meanSpeed;

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= towPi;

    return dPSD;
}

double SimuSpectrum::computeVerticalWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1, double Par2)
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
