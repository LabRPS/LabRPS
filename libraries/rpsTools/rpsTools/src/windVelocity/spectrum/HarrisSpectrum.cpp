#include "HarrisSpectrum.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

HarrisSpectrum::HarrisSpectrum()
{

}

HarrisSpectrum::~HarrisSpectrum()
{

}

double  HarrisSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &shearVelocity)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
    double Par1 = 1800.0;
    double Par2 = 1800.0;
    double PI = 22.0 / 7.0;

    dBuf1 = 2.0 + Par2 * Par2 * frequency * frequency / (2.0 * PI * 2.0 * PI);

    dBuf2 = pow(dBuf1, 5.0 / 6.0);

    dPSD = 4.0 * shearVelocity * shearVelocity * Par1 / (2.0 * PI * meanSpeed);

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= 2.0 * PI;

    return dPSD;
}
