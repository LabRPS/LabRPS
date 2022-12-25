#ifndef KAIMALSPECTRUM_H
#define KAIMALSPECTRUM_H

#include "rpsTools/RPSToolsDefines.h"
#include "WindSpectrum.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT KaimalSpectrum : public WindSpectrum 
{
public:
    KaimalSpectrum();
    ~KaimalSpectrum();

    //this computes the along wind spectrum
    double computeAlongWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1 = 200.0, double Par2 = 50.0);

    //this computes the across wind spectrum
    double computeAcrossWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1 = 17.0, double Par2 = 9.5);

    //this computes the vertical wind spectrum
    double computeVerticalWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1 = 2.0, double Par2 = 5.3);

};

}

}

#endif //KAIMALSPECTRUM_H
