#ifndef GENERALIZEDKAIMALSPECTRUM_H
#define GENERALIZEDKAIMALSPECTRUM_H

#include "rpsTools/RPSToolsDefines.h"
#include "WindSpectrum.h"

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT GeneralizedKaimalSpectrum : public WindSpectrum
{
public:
    GeneralizedKaimalSpectrum();
    ~GeneralizedKaimalSpectrum();

    double computeGeneralizedKaimalWindAutoSpectrum(const double &frequency,
                                                       const double &height,
                                                       const double &meanSpeed,
                                                       const double &shearVelocity,
                                                       const double &a = 200.0,
                                                       const double &b = 1.0,
                                                       const double &c = 0.0,
                                                       const double &d = 1.0,
                                                       const double &e = 1.0,
                                                       const double &f = 1.0,
                                                       const double &g = 1.0,
                                                       const double &h = 50.0,
                                                       const double &i = 1.0,
                                                       const double &j = 5.0/3.0);
};

}

}

#endif //GENERALIZEDKAIMALSPECTRUM_H
