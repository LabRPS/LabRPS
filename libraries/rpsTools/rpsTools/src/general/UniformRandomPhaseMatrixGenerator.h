#ifndef UNIFORMRANDOMPHASEMATRIXGENERATOR_H
#define UNIFORMRANDOMPHASEMATRIXGENERATOR_H

#include "rpsTools/RPSToolsDefines.h"
#include "rpsTools/RPS.h"

namespace rps {

namespace General {

class RPS_TOOLS_EXPORT UniformRandomPhaseMatrixGenerator
{
public:
    UniformRandomPhaseMatrixGenerator();
    ~UniformRandomPhaseMatrixGenerator();

void generateUniformRandomPhaseMatrix(mat &randomPhaseMatrix, const double &min, const double &max);
void generateUniformRandomPhaseValue(double &value, const double &min, const double &max);

};

}

}

#endif //UNIFORMRANDOMPHASEMATRIXGENERATOR_H
