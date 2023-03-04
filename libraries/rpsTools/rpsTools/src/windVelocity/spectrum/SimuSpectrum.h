#ifndef SIMUSPECTRUM_H
#define SIMUSPECTRUM_H

#include "rpsTools/RPSToolsDefines.h"
#include "WindSpectrum.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT SimuSpectrum : public WindSpectrum 
{
public:
    SimuSpectrum();
    ~SimuSpectrum();

    //this computes the along wind spectrum
    double computeAlongWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1, double Par2);

    //this computes the across wind spectrum
    double computeAcrossWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1, double Par2);

    //this computes the vertical wind spectrum
    double computeVerticalWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1, double Par2);

};

}

}

#endif //SIMUSPECTRUM_H
