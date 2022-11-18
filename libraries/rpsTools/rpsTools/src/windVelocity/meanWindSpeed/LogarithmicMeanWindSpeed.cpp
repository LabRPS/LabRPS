#include "LogarithmicMeanWindSpeed.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

LogarithmicMeanWindSpeed::LogarithmicMeanWindSpeed()
{

}

LogarithmicMeanWindSpeed::~LogarithmicMeanWindSpeed()
{

}

double  LogarithmicMeanWindSpeed::computeMeanWindSpeed(const double &height, const double &terrainRoughness, const double &shearVelocity, const double &zeroPlanDisplacement)
{
    return log((height - zeroPlanDisplacement) / terrainRoughness)*shearVelocity / 0.4;
}
