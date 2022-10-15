#ifndef DAVENPORTSPECTRUM_H
#define DAVENPORTSPECTRUM_H

#include "rpsTools/RPSToolsDefines.h"
#include "WindSpectrum.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT DavenportSpectrum : public WindSpectrum 
{
public:
    DavenportSpectrum();
    ~DavenportSpectrum();

    //this computes the along wind spectrum
    double computeAlongWindAutoSpectrum(const double &frequency, const double &meanSpeed);

};

}

}

#endif //DAVENPORTSPECTRUM_H
