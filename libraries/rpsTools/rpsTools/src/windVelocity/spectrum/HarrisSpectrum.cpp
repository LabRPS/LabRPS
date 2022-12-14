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

double  HarrisSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &shearVelocity, const double &meanSpeed10)
{
    const double towPi = 2*22.0/7.0;
    const double a = 1800.0;
    const double K = 0.4; //Karman constant
    const double freq = (a*frequency / meanSpeed10)/towPi;
    const double numer = std::pow(freq,2);
    const double denom = std::pow(2+numer, 5.0/6.0);
    const double dPSD = 4.0 * K * shearVelocity * shearVelocity*(numer/denom);
    return dPSD/towPi;
}
