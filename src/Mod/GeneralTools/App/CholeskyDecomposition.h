#ifndef CHOLESKYDECOMPOSITION_H
#define CHOLESKYDECOMPOSITION_H

#include "RPS.h"
#include <Mod/GeneralTools/GeneralToolsGlobal.h>

namespace rps {

namespace General {

class GeneralToolsExport CholeskyDecomposition
{
public:
    CholeskyDecomposition();
    ~CholeskyDecomposition();

    void computeCholeskyDecomposition(const mat &inputMatrix, mat &outputMatrix, const bool &lower = true);
    void computeCholeskyDecomposition_cx(const cx_mat &inputMatrix, cx_mat &outputMatrix, const bool &lower = true);

};

}

}

#endif //CHOLESKYDECOMPOSITION_H
