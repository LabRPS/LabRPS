
#include "CholeskyDecomposition.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/GeneralTools/App/CholeskyDecomposition.h>

using namespace WindLab;
using namespace WindLabAPI;

bool CholeskyDecomposition::MatrixToolCompute(const WindLabAPI::WindLabSimuData& Data, const mat &inputMatrix, mat &outputMatrix)
{
    rps::General::CholeskyDecomposition decomposition;
    decomposition.computeCholeskyDecomposition(inputMatrix, outputMatrix);
    return true;
}

bool CholeskyDecomposition::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{

    return true;
}


