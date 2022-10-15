#include "SineModulation.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

SineModulation::SineModulation()
{

}

SineModulation::~SineModulation()
{

}

double  SineModulation::computeModulation(const double &time, const double &pulseDuration)
{
    double value = sin(3.14*time / pulseDuration);

    return value;
}
