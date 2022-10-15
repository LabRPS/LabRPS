#ifndef DAVENPORTCOHERENCE_H
#define DAVENPORTCOHERENCE_H

#include "rpsTools/RPSToolsDefines.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT DavenportCoherence  
{
public:
    DavenportCoherence();
    ~DavenportCoherence();

    double computeCoherenceValue(const double &locationJxCoord,
                                                      const double &locationJyCoord,
                                                      const double &locationJzCoord,
                                                      const double &locationKxCoord,
                                                      const double &locationKyCoord,
                                                      const double &locationKzCoord,
                                                      const double &frequency,
                                                      const double &locationJMeanSpeed,
                                                      const double &locationKMeanSpeed,
                                                      const double &exponentialDecayCx = 10,
                                                      const double &exponentialDecayCy = 7,
                                                      const double &exponentialDecayCz = 6);
};

}

}

#endif //DAVENPORTCOHERENCE_H
