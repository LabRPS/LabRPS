#ifndef POWERLAWMEANWINDSPEED_H
#define POWERLAWMEANWINDSPEED_H

#include "rpsTools/RPSToolsDefines.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT PowerLawMeanWindSpeed
{
public:
    PowerLawMeanWindSpeed();
    ~PowerLawMeanWindSpeed();

    //this computes the along wind spectrum
    double  computeMeanWindSpeed(const double &height, const double &referenceHeight, const double &referenceMeanSpeed);

};

}

}

#endif //POWERLAWMEANWINDSPEED_H
