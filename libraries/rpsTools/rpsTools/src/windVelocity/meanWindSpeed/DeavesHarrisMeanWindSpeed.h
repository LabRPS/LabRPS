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
    double computeMeanWindSpeed(const double &height, const double &terrainRoughness, const double &shearVelocity, const double &heightOfABL);

};

}

}

#endif //DHMEANWINDSPEED_H
