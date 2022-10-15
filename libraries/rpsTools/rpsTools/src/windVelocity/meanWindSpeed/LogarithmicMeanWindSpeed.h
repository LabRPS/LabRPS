#ifndef LOGARITHMICMEANWINDSPEED_H
#define LOGARITHMICMEANWINDSPEED_H

#include "rpsTools/RPSToolsDefines.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT LogarithmicMeanWindSpeed
{
public:
    LogarithmicMeanWindSpeed();
    ~LogarithmicMeanWindSpeed();

    //this computes the along wind spectrum
    double  computeMeanWindSpeed(const double &height, const double &terrainRoughness, const double &shearVelocity);

};

}

}

#endif //LOGARITHMICMEANWINDSPEED_H
