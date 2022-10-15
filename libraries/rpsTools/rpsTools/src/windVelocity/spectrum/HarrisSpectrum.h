#ifndef HARRISSPECTRUM_H
#define HARRISSPECTRUM_H

#include "rpsTools/RPSToolsDefines.h"
#include "WindSpectrum.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT HarrisSpectrum : public WindSpectrum 
{
public:
    HarrisSpectrum();
    ~HarrisSpectrum();

    //this computes the along wind spectrum
    double computeAlongWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &shearVelocity);

};

}

}

#endif //HARRISSPECTRUM_H
