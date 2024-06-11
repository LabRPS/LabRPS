#ifndef rpsCholeskyDecomposition_PLUGIN_CholeskyDecomposition_H
#define rpsCholeskyDecomposition_PLUGIN_CholeskyDecomposition_H

#include <Mod/WindLabAPI/App/IrpsWLMatrixTool.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CholeskyDecomposition : public WindLabAPI::IrpsWLMatrixTool
{
public:

    bool MatrixToolCompute(const WindLabAPI::WindLabSimuData& Data, const mat &inputMatrix, mat &outputMatrix);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

};

} // namespace App

#endif // rpsCholeskyDecomposition_PLUGIN_CholeskyDecomposition_H
