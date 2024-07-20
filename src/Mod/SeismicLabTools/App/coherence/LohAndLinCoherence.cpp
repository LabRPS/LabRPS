#include "PreCompiled.h"
#include "LohAndLinCoherence.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/coherence/LohAndLinCoherencePy.h>

using namespace SeismicLabTools;

LohAndLinCoherence::LohAndLinCoherence()
{

}

LohAndLinCoherence::~LohAndLinCoherence()
{

}
double  LohAndLinCoherence::computeCoherenceValue(const double &locationJxCoord,
                                                  const double &locationJyCoord,
                                                  const double &locationJzCoord,
                                                  const double &locationKxCoord,
                                                  const double &locationKyCoord,
                                                  const double &locationKzCoord,
                                                  const double &frequency, 
                                                  const double &parameterAlpha, 
                                                  const double &parameterB)
{
    double dValue = sqrt((locationJxCoord - locationKxCoord) * (locationJxCoord - locationKxCoord) +
                  (locationJyCoord - locationKyCoord) * (locationJyCoord - locationKyCoord) +
                  (locationJzCoord - locationKzCoord) * (locationJzCoord - locationKzCoord));

        dValue = -(parameterAlpha + parameterB * frequency * frequency) * dValue;
        dValue = exp(dValue);
        return dValue;
}

  double LohAndLinCoherence::computeCrossCoherenceValue(Base::Vector3d locationJ, Base::Vector3d locationK,
                                                      const double& frequency,
                                                      const double& parameterAlpha,
                                                      const double& parameterB)
{
        double dValue = sqrt((locationJ.x - locationK.x) * (locationJ.x - locationK.x)
                       + (locationJ.y - locationK.y) * (locationJ.y - locationK.y)
                       + (locationJ.z - locationK.z) * (locationJ.z - locationK.z));

        dValue = -(parameterAlpha + parameterB * frequency * frequency) * dValue;
        dValue = exp(dValue);
        return dValue;
}

PyObject* LohAndLinCoherence::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new LohAndLinCoherencePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}