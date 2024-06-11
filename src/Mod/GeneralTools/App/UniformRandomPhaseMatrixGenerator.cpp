#include "PreCompiled.h"
#include "UniformRandomPhaseMatrixGenerator.h"
#include <math.h>

using namespace rps;
using namespace General;

UniformRandomPhaseMatrixGenerator::UniformRandomPhaseMatrixGenerator()
{

}

UniformRandomPhaseMatrixGenerator::~UniformRandomPhaseMatrixGenerator()
{

}

void UniformRandomPhaseMatrixGenerator::generateUniformRandomPhaseValue(double &value, const double &min, const double &max)
{
    //std::srand((unsigned int) time(0));
    //value = (std::rand()*(max-min)) + min;
    std::srand((unsigned int) time(0));
    value = (max - min) * MatrixXd::Random(1, 1)(0, 0) + min;
}

void UniformRandomPhaseMatrixGenerator::generateUniformRandomPhaseMatrix(mat &randomPhaseMatrix, const double &min, const double &max)
{
    std::srand((unsigned int) time(0));
	randomPhaseMatrix = (max-min) * MatrixXd::Random(randomPhaseMatrix.rows(), randomPhaseMatrix.cols());
	randomPhaseMatrix.array() += min;
}
