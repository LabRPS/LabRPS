#ifndef VONKARMANSPECTRUM_H
#define VONKARMANSPECTRUM_H

#include "rpsTools/RPSToolsDefines.h"
#include "WindSpectrum.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT VonKarmanSpectrum : public WindSpectrum 
{
public:
    VonKarmanSpectrum();
    ~VonKarmanSpectrum();

    //this computes the along wind spectrum
    double computeAlongWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &integralLengthScale, const double &standardDeviation, double Par1, double Par2);

    //this computes the across wind spectrum
    double computeAcrossWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &integralLengthScale, const double &standardDeviation, double Par1, double Par2, double Par3);

    //this computes the vertical wind spectrum
    double computeVerticalWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &integralLengthScale, const double &standardDeviation, double Par1, double Par2, double Par3);

};

}

}

#endif //VONKARMANSPECTRUM_H
