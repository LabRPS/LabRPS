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
    double  computeMeanWindSpeed(const double &height, const double &referenceHeight, const double &referenceMeanSpeed, const double &zeroPlanDisplacement = 0, const double &dimensionlessPower = 0.12);

};

}

}

#endif //POWERLAWMEANWINDSPEED_H
