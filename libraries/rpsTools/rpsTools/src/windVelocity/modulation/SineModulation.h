#ifndef SINEMODULATION_H
#define SINEMODULATION_H

#include "rpsTools/RPSToolsDefines.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT SineModulation
{
public:
    SineModulation();
    ~SineModulation();

double  computeModulation(const double &time, const double &pulseDuration);

};

}

}

#endif //SINEMODULATION_H
