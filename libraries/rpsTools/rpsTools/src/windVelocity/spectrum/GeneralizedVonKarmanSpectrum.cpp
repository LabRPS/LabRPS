#include "GeneralizedVonKarmanSpectrum.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

GeneralizedVonKarmanSpectrum::GeneralizedVonKarmanSpectrum()
{

}

GeneralizedVonKarmanSpectrum::~GeneralizedVonKarmanSpectrum()
{

}

double GeneralizedVonKarmanSpectrum::computeGeneralizedVonKarmanWindAutoSpectrum(const double &frequency,
                                                   const double &integralLengthScale,
                                                   const double &meanSpeed,
                                                   const double &standardDeviation,
                                                   const double &a,
                                                   const double &b,
                                                   const double &c,
                                                   const double &d,
                                                   const double &e,
                                                   const double &f,
                                                   const double &g,
                                                   const double &h,
                                                   const double &i,
                                                   const double &j)
{
    const double towPi = 2*22.0/7.0;
    const double freq = (frequency * integralLengthScale/(meanSpeed))/towPi;
    const double numer = a*freq*std::pow(b+(c*(std::pow(freq,d))),e);
    const double denom = f*std::pow(g+(h*(std::pow(freq,i))),j);
    const double psd = (standardDeviation*standardDeviation)*(numer/denom)/(frequency/towPi);
    return psd/towPi;
}


