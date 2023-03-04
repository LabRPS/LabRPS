#ifndef THREEPARAMETERSMODULATION_H
#define THREEPARAMETERSMODULATION_H

#include "rpsTools/RPSToolsDefines.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT ThreeParametersModulation
{
public:
    ThreeParametersModulation();
    ~ThreeParametersModulation();

    double computeModulation(const double &time, const double &alpha, const double &betta, const double &lambda);

};

}

}

#endif //THREEPARAMETERSMODULATION_H
