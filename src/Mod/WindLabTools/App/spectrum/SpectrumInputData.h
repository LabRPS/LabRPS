#ifndef SPECTRUMINPUTDATA_H
#define SPECTRUMINPUTDATA_H

#include "rpsTools/RPSToolsDefines.h"
#include "rpsTools/RPS.h"
#include <string>

namespace WindLabTools {

class RPS_TOOLS_EXPORT SpectrumInputData
{
public:

    //constructor
     SpectrumInputData();

    //destructor
    virtual ~SpectrumInputData();

    mat meanWindSpeeds;
    vec heights;
    vec timeIncrements;
    vec frequencyIncrements;
    vec shearVelocities;
};

}

#endif //SPECTRUMINPUTDATA_H
