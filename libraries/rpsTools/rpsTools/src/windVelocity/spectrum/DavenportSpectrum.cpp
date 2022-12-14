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

double  DavenportSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &meanSpeed10)
{
    const double towPi = 2*22.0/7.0;
    const double a = 1200.0;
    const double K = 0.4; //Karman constant
    const double x = (a*frequency / meanSpeed10)/towPi;
    const double xx = std::pow(x,2);
    const double denom = std::pow(1+xx, 4.0/3.0);
    const double dPSD = 4.0 * K * meanSpeed10 * meanSpeed10*(x/denom);
    return dPSD/towPi;
}

