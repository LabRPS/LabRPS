#include "KaimalSpectrum.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

KaimalSpectrum::KaimalSpectrum()
{

}

KaimalSpectrum::~KaimalSpectrum()
{

}

double  KaimalSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
    double Par1 = 200.0;
    double Par2 = 50.0;
    double PI = 22.0 / 7.0;

    dBuf1 = 1.0 + Par2 * frequency * height / (2.0 * PI *meanSpeed);

    dBuf2 = pow(dBuf1, 5.0 / 3.0);

    dPSD = Par1 * shearVelocity * shearVelocity * height / meanSpeed;

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= 2.0*PI;

    return dPSD;
}

double KaimalSpectrum::computeAcrossWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
    double Par1 = 17.0;
    double Par2 = 9.5;
    double PI = 22.0 / 7.0;

    dBuf1 = 1.0 + Par2 * frequency * height / (2.0 * PI *meanSpeed);

    dBuf2 = pow(dBuf1, 5.0 / 3.0);

    dPSD = Par1 * shearVelocity * shearVelocity * height / meanSpeed;

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= 2.0*PI;

    return dPSD;
}

double KaimalSpectrum::computeVerticalWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
    double Par1 = 2.0;
    double Par2 = 5.3;
    double PI = 22.0 / 7.0;

    dBuf1 = frequency * height / (2.0 * PI *meanSpeed);

    dBuf2 = 1.0 + Par2 *pow(dBuf1, 5.0 / 3.0);

    dPSD = Par1 * shearVelocity * shearVelocity * height / meanSpeed;

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= 2.0*PI;

    return dPSD;
}
