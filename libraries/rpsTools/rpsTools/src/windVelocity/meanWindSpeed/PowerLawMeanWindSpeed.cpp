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

double  PowerLawMeanWindSpeed::computeMeanWindSpeed(const double &height, const double &referenceHeight, const double &referenceMeanSpeed, const double &zeroPlanDisplacement, const double &dimensionlessPower)
{
    return pow((height - zeroPlanDisplacement) / referenceHeight, dimensionlessPower) * referenceMeanSpeed;
}
