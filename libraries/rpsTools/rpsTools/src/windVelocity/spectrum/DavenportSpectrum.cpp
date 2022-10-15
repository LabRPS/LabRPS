#include "DavenportSpectrum.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

DavenportSpectrum::DavenportSpectrum()
{

}

DavenportSpectrum::~DavenportSpectrum()
{

}

double  DavenportSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &meanSpeed)
{
    double dBuf1, dBuf2;
    double dPSD = 0.0;
    double Par1 = 1200.0;
    double Par2 = 1200.0;
    double PI = 22.0 / 7.0;
    double K = 0.4;

    dBuf1 = 1.0 + Par2 * Par2 * frequency * frequency / (2.0 * PI * meanSpeed * 2.0 * PI * meanSpeed);

    dBuf2 = pow(dBuf1, 4.0 / 3.0);

    dPSD = 4.0 * K * Par1 * Par1 * frequency / (2.0 * PI * 2.0 * PI);

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= 2.0 * PI;

    return dPSD;
}

