#include "PreCompiled.h"
#include "HarichandranVanmarckeCoherence.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/coherence/HarichandranVanmarckeCoherencePy.h>

using namespace SeismicLabTools;

HarichandranVanmarckeCoherence::HarichandranVanmarckeCoherence()
{

}

HarichandranVanmarckeCoherence::~HarichandranVanmarckeCoherence()
{

}
double  HarichandranVanmarckeCoherence::computeCoherenceValue(const double &locationJxCoord,
                                                              const double &locationJyCoord,
                                                              const double &locationJzCoord,
                                                              const double &locationKxCoord,
                                                              const double &locationKyCoord,
                                                              const double &locationKzCoord,
                                                              const double &frequency,
                                                              const double &parameterA,
                                                              const double &parameterAlpha,
                                                              const double &parameterK,
                                                              const double &parameterOmegaZero,
                                                              const double &parameterB)
{
    double distance = sqrt((locationJxCoord - locationKxCoord) * (locationJxCoord - locationKxCoord) + (locationJyCoord - locationKyCoord) * (locationJyCoord - locationKyCoord) + (locationJzCoord - locationKzCoord) * (locationJzCoord - locationKzCoord));
    double value1 = 2 * distance / (1 - parameterA + parameterAlpha * parameterA);
    double theFrequency = pow(frequency / parameterOmegaZero, parameterB);
    double correlationDistance = parameterK * pow(1 + theFrequency, -0.5);
    double value = parameterA * exp(-value1/(parameterAlpha * correlationDistance)) + (1 - parameterA) * exp(-value1/correlationDistance);
    return value;
}

  double HarichandranVanmarckeCoherence::computeCrossCoherenceValue(Base::Vector3d locationJ, Base::Vector3d locationK, const double& frequency, const double& parameterA, const double& parameterAlpha, const double& parameterK, const double& parameterOmegaZero, const double& parameterB)
{
    double distance = sqrt((locationJ.x - locationK.x) * (locationJ.x - locationK.x) + (locationJ.y - locationK.y) * (locationJ.y - locationK.y) + (locationJ.z - locationK.z) * (locationJ.z - locationK.z));
    double value1 = 2 * distance / (1 - parameterA + parameterAlpha * parameterA);
    double theFrequency = pow(frequency / parameterOmegaZero, parameterB);
    double correlationDistance = parameterK * pow(1 + theFrequency, -0.5);
    double value = parameterA * exp(-value1/(parameterAlpha * correlationDistance)) + (1 - parameterA) * exp(-value1/correlationDistance);
    return value;
}

PyObject* HarichandranVanmarckeCoherence::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new HarichandranVanmarckeCoherencePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}