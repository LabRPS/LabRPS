#ifndef WINDSPECTRUM_H
#define WINDSPECTRUM_H

#include "rpsTools/RPSToolsDefines.h"
#include "rpsTools/RPS.h"
#include <string>

namespace rps {

namespace WindVelocity {

class RPS_TOOLS_EXPORT WindSpectrum
{
public:

    //constructor
     WindSpectrum();

    //destructor
    virtual ~WindSpectrum();
};

}

}

#endif //WINDSPECTRUM_H
