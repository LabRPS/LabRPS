#include "ThreeParametersModulation.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

ThreeParametersModulation::ThreeParametersModulation()
{

}

ThreeParametersModulation::~ThreeParametersModulation()
{

}

double  ThreeParametersModulation::computeModulation(const double &alpha, const double &betta, const double &lambda, const double &time)
{
    double value = alpha * (pow(time, betta))*(exp(-lambda * time));

    return value;
}
