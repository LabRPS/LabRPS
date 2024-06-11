#include "PreCompiled.h"
#include "DavenportCoherence.h"
#include <math.h>
#include <Mod/WindLabTools/App/coherence/DavenportCoherencePy.h>

using namespace WindLabTools;

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

  double DavenportCoherence::computeCrossCoherenceValue(Base::Vector3d locationJ, Base::Vector3d locationK,
                             const double& frequency, const double& locationJMeanSpeed,
                             const double& locationKMeanSpeed,
                             const double& exponentialDecayCx,
                             const double& exponentialDecayCy,
                             const double& exponentialDecayCz)
{
        double dValue =
            (exponentialDecayCx * exponentialDecayCx * (locationJ.x - locationK.x) * (locationJ.x - locationK.x)
           + exponentialDecayCy * exponentialDecayCy * (locationJ.y - locationK.y) * (locationJ.y - locationK.y)
           + exponentialDecayCz * exponentialDecayCz * (locationJ.z - locationK.z) * (locationJ.z - locationK.z));

        dValue = sqrt(dValue);

        dValue = dValue / 2.0 / 3.14;

        dValue = -2 * dValue / (locationJMeanSpeed + locationKMeanSpeed);

        dValue = exp(dValue * frequency);

        return dValue;
}

PyObject* DavenportCoherence::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new DavenportCoherencePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}