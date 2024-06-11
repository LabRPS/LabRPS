#include "PreCompiled.h"
#include "CholeskyDecomposition.h"
#include <math.h>

using namespace rps;
using namespace General;

CholeskyDecomposition::CholeskyDecomposition()
{

}

CholeskyDecomposition::~CholeskyDecomposition()
{

}

void CholeskyDecomposition::computeCholeskyDecomposition(const mat &inputMatrix, mat &outputMatrix, const bool &lower)
{
    if(lower)
    {
    	outputMatrix = inputMatrix.llt().matrixL();
    }
    else
    {
        outputMatrix = inputMatrix.llt().matrixU();
    }
}

void CholeskyDecomposition::computeCholeskyDecomposition_cx(const cx_mat &inputMatrix, cx_mat &outputMatrix, const bool &lower)
{
    if(lower)
    {
    	outputMatrix = inputMatrix.llt().matrixL();
    }
    else
    {
        outputMatrix = inputMatrix.llt().matrixU();
    }
}