#ifndef DHMEANWINDSPEED_H
#define DHMEANWINDSPEED_H

#include "rpsTools/RPSToolsDefines.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT DeavesHarrisMeanWindSpeed
{
public:
    DeavesHarrisMeanWindSpeed();
    ~DeavesHarrisMeanWindSpeed();

    //this computes the along wind spectrum
    double computeMeanWindSpeed(const double &height, const double &terrainRoughness, const double &shearVelocity, const double &zeroPlanDisplacement, const double &latitude, const double &earthAngularVelocity = 0.0000729, const double &beta = 6);

};

}

}

#endif //DHMEANWINDSPEED_H
