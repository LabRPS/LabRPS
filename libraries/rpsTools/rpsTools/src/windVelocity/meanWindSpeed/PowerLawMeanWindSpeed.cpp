#include "PowerLawMeanWindSpeed.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

PowerLawMeanWindSpeed::PowerLawMeanWindSpeed()
{

}

PowerLawMeanWindSpeed::~PowerLawMeanWindSpeed()
{

}

double  PowerLawMeanWindSpeed::computeMeanWindSpeed(const double &height, const double &referenceHeight, const double &referenceMeanSpeed)
{
    return pow(height / referenceHeight, 0.12) * referenceMeanSpeed;
}
