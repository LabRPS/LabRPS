#ifndef CHOLESKYDECOMPOSITION_H
#define CHOLESKYDECOMPOSITION_H

#include "rpsTools/RPSToolsDefines.h"
#include "rpsTools/RPS.h"

namespace rps {

namespace General {

class RPS_TOOLS_EXPORT CholeskyDecomposition
{
public:
    CholeskyDecomposition();
    ~CholeskyDecomposition();

    void computeCholeskyDecomposition(const mat &inputMatrix, mat &outputMatrix, const bool &lower = true);

};

}

}

#endif //CHOLESKYDECOMPOSITION_H
