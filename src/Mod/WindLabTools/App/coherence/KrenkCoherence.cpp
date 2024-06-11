#include "PreCompiled.h"
#include "KrenkCoherence.h"
#include <math.h>
#include <Mod/WindLabTools/App/coherence/KrenkCoherencePy.h>

using namespace WindLabTools;

KrenkCoherence::KrenkCoherence()
{

}

KrenkCoherence::~KrenkCoherence()
{

}
double  KrenkCoherence::computeCoherenceValue(const double &locationJxCoord,
                                                  const double &locationJyCoord,
                                                  const double &locationJzCoord,
                                                  const double &locationKxCoord,
                                                  const double &locationKyCoord,
                                                  const double &locationKzCoord,
                                                  const double &frequency,
                                                  const double &locationJMeanSpeed,
                                                  const double &locationKMeanSpeed,
                                                  const double &integralLength)
{
    const double distance = sqrt(((locationJxCoord - locationKxCoord) * (locationJxCoord - locationKxCoord) +
                                 (locationJyCoord - locationKyCoord) * (locationJyCoord - locationKyCoord) +
                                 (locationJzCoord - locationKzCoord) * (locationJzCoord - locationKzCoord)));

    const double meanSpeedJK = (locationJMeanSpeed + locationKMeanSpeed) /2;
    const double alpha = sqrt((frequency / meanSpeedJK) * (frequency / meanSpeedJK) + (1 / (1.34 * integralLength)) * (1 / (1.34 * integralLength)));
    const double dValue = (1 - 0.35 * alpha * distance) * exp(-0.7 * alpha * distance);
    return dValue;
}

  double KrenkCoherence::computeCrossCoherenceValue(Base::Vector3d locationJ, Base::Vector3d locationK,
                             const double& frequency, const double& locationJMeanSpeed,
                             const double& locationKMeanSpeed,
                             const double& integralLength)
{
   const double distance = sqrt((locationJ.x - locationK.x) * (locationJ.x - locationK.x)
                              + (locationJ.y - locationK.y) * (locationJ.y - locationK.y)
                              + (locationJ.z - locationK.z) * (locationJ.z - locationK.z));

    const double meanSpeedJK = (locationJMeanSpeed + locationKMeanSpeed) /2;
    const double alpha = sqrt((frequency / meanSpeedJK) * (frequency / meanSpeedJK) + (1 / (1.34 * integralLength)) * (1 / (1.34 * integralLength)));
    const double dValue = (1 - 0.35 * alpha * distance) * exp(-0.7 * alpha * distance);
    return dValue;
}

PyObject* KrenkCoherence::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new KrenkCoherencePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}