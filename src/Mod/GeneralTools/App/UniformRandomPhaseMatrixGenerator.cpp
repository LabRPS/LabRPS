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

void UniformRandomPhaseMatrixGenerator::generateUniformRandomPhaseCube(cube &randomPhaseCube, const double &min, const double &max)
{
    mat randomPhaseMatrix(randomPhaseCube.dimension(0), randomPhaseCube.dimension(1));

    for (int k = 0; k < randomPhaseCube.dimension(2); ++k) {  // Iterate over the first dimension (depth)

    std::srand((unsigned int) time(0));
	randomPhaseMatrix = (max-min) * MatrixXd::Random(randomPhaseCube.dimension(0), randomPhaseCube.dimension(1));
	randomPhaseMatrix.array() += min;

        for (int i = 0; i < randomPhaseCube.dimension(0); ++i) {  // Iterate over the second dimension (rows)
            for (int j = 0; j < randomPhaseCube.dimension(1); ++j) {  // Iterate over the third dimension (columns)
                randomPhaseCube(i, j, k) = randomPhaseMatrix(i, j);
            }
        }
    }    
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
