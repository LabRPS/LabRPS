#ifndef EXPONENTIALMODULATION_H
#define EXPONENTIALMODULATION_H

#include "rpsTools/RPSToolsDefines.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT ExponentialModulation
{
public:
    ExponentialModulation();
    ~ExponentialModulation();

double  computeModulation(const double &time, const double &timeOfMax, const double &stormLength);

};

}

}

#endif //EXPONENTIALMODULATION_H
