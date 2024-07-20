#include "PreCompiled.h"
#include "AbrahamsonCoherence.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/coherence/AbrahamsonCoherencePy.h>

using namespace SeismicLabTools;

AbrahamsonCoherence::AbrahamsonCoherence()
{

}

AbrahamsonCoherence::~AbrahamsonCoherence()
{

}
double  AbrahamsonCoherence::computeCoherenceValue(const double &locationJxCoord,
                                                              const double &locationJyCoord,
                                                              const double &locationJzCoord,
                                                              const double &locationKxCoord,
                                                              const double &locationKyCoord,
                                                              const double &locationKzCoord,
                                                              const double &frequency)
{
    double distance = sqrt((locationJxCoord - locationKxCoord) * (locationJxCoord - locationKxCoord) + (locationJyCoord - locationKyCoord) * (locationJyCoord - locationKyCoord) + (locationJzCoord - locationKzCoord) * (locationJzCoord - locationKzCoord));
    double c3 = (3.95 /(1 + 0.0077 * distance + 0.000023 * distance * distance)) + 0.85 * exp(-0.00013 * distance);
    double c4 = 0.4 * (1-1/(1 + pow(distance/5, 3)))/((1 + pow(distance/190, 8)) * (1 + pow(distance/180, 3)));
    double c6 = 3 * (exp(-distance / 20) - 1) - 0.0018 * distance;
    double c7 = -0.598 + 0.106 * log(distance + 325) - 0.0151 * exp(-0.6 * distance);
    double c8 = exp(8.54 - 1.07 * log(distance + 200)) + 100 * exp(-distance);
    double value = 1 / (1 + pow(frequency / (2 * 3.14 * c8), 6)) * tanh(c3 / (1+frequency*c4/6.28 + frequency*frequency*c7/(6.28*6.28)) + (4.80 - c3)* exp(c6*frequency/6.28) + 0.35);
    return value;
}

  double AbrahamsonCoherence::computeCrossCoherenceValue(Base::Vector3d locationJ, Base::Vector3d locationK, const double& frequency)
{
    double distance = sqrt((locationJ.x - locationK.x) * (locationJ.x - locationK.x) + (locationJ.y - locationK.y) * (locationJ.y - locationK.y) + (locationJ.z - locationK.z) * (locationJ.z - locationK.z));
    double c3 = (3.95 /(1 + 0.0077 * distance + 0.000023 * distance * distance)) + 0.85 * exp(-0.00013 * distance);
    double c4 = 0.4 * (1-1/(1 + pow(distance/5, 3)))/((1 + pow(distance/190, 8)) * (1 + pow(distance/180, 3)));
    double c6 = 3 * (exp(-distance / 20) - 1) - 0.0018 * distance;
    double c7 = -0.598 + 0.106 * log(distance + 325) - 0.0151 * exp(-0.6 * distance);
    double c8 = exp(8.54 - 1.07 * log(distance + 200)) + 100 * exp(-distance);
    double value = 1 / (1 + pow(frequency / (2 * 3.14 * c8), 6)) * tanh(c3 / (1+frequency*c4/6.28 + frequency*frequency*c7/(6.28*6.28)) + (4.80 - c3)* exp(c6*frequency/6.28) + 0.35);
    return value;
}

PyObject* AbrahamsonCoherence::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new AbrahamsonCoherencePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}