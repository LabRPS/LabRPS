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

void UniformRandomPhaseMatrixGenerator::generateUniformRandomPhaseMatrix(mat &randomPhaseMatrix, const double &min, const double &max)
{
    std::srand((unsigned int) time(0));
	randomPhaseMatrix = (max-min) * MatrixXd::Random(randomPhaseMatrix.rows(), randomPhaseMatrix.cols());
	randomPhaseMatrix.array() += min;
}
