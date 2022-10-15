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
    double computeAlongWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, const double &integralLengthScale, const double &standardDeviation);

    //this computes the across wind spectrum
    double computeAcrossWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, const double &integralLengthScale, const double &standardDeviation);

    //this computes the vertical wind spectrum
    double computeVerticalWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, const double &integralLengthScale, const double &standardDeviation);

};

}

}

#endif //VONKARMANSPECTRUM_H
