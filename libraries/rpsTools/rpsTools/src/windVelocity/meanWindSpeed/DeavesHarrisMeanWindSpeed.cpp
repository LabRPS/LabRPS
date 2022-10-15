#include "DeavesHarrisMeanWindSpeed.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

DeavesHarrisMeanWindSpeed::DeavesHarrisMeanWindSpeed()
{

}

DeavesHarrisMeanWindSpeed::~DeavesHarrisMeanWindSpeed()
{

}

double  DeavesHarrisMeanWindSpeed::computeMeanWindSpeed(const double &height, const double &terrainRoughness, const double &shearVelocity, const double &heightOfABL)
{
    double ratio = (height/heightOfABL);
    double meanSpeed = shearVelocity * (log(ratio) + 5.75 * ratio - 1.88 * pow(ratio, 2) - 1.33 * pow(ratio, 3) + 0.25 * pow(ratio, 4)) * 0.4;
    return meanSpeed;
}
