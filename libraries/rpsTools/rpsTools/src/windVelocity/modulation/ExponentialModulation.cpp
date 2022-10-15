#include "ExponentialModulation.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

ExponentialModulation::ExponentialModulation()
{

}

ExponentialModulation::~ExponentialModulation()
{

}

double  ExponentialModulation::computeModulation(const double &time, const double &timeOfMax, const double &stormLength)
{
    double value = exp(-(time - timeOfMax)*(time - timeOfMax) / (2 * stormLength*stormLength));

    return value;
}
