#include "DavenportCoherence.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

DavenportCoherence::DavenportCoherence()
{

}

DavenportCoherence::~DavenportCoherence()
{

}
double  DavenportCoherence::computeCoherenceValue(const double &locationJxCoord,
                                                  const double &locationJyCoord,
                                                  const double &locationJzCoord,
                                                  const double &locationKxCoord,
                                                  const double &locationKyCoord,
                                                  const double &locationKzCoord,
                                                  const double &frequency,
                                                  const double &locationJMeanSpeed,
                                                  const double &locationKMeanSpeed,
                                                  const double &exponentialDecayCx,
                                                  const double &exponentialDecayCy,
                                                  const double &exponentialDecayCz)
{
    double dValue = (exponentialDecayCx * exponentialDecayCx * (locationJxCoord - locationKxCoord) * (locationJxCoord - locationKxCoord) +
                  exponentialDecayCy * exponentialDecayCy * (locationJyCoord - locationKyCoord) * (locationJyCoord - locationKyCoord) +
                  exponentialDecayCz * exponentialDecayCz * (locationJzCoord - locationKzCoord) * (locationJzCoord - locationKzCoord));

        dValue = sqrt(dValue);

        dValue = dValue / 2.0 / 3.14;

        dValue = -2 * dValue / (locationJMeanSpeed + locationKMeanSpeed);

        dValue = exp(dValue * frequency);

        return dValue;
}
