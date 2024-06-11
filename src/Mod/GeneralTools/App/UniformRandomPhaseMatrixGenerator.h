#ifndef UNIFORMRANDOMPHASEMATRIXGENERATOR_H
#define UNIFORMRANDOMPHASEMATRIXGENERATOR_H

#include "RPS.h"
#include <Mod/GeneralTools/GeneralToolsGlobal.h>

namespace rps {

namespace General {

class GeneralToolsExport UniformRandomPhaseMatrixGenerator
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
