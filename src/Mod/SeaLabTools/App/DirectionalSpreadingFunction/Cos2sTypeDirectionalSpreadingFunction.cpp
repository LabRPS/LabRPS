#include "PreCompiled.h"
#include "Cos2sTypeDirectionalSpreadingFunction.h"
#include <math.h>
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/Cos2sTypeDirectionalSpreadingFunctionPy.h>

#define PI_   3.14159265358979323846

using namespace SeaLabTools;

Cos2sTypeDirectionalSpreadingFunction::Cos2sTypeDirectionalSpreadingFunction()
{

}

Cos2sTypeDirectionalSpreadingFunction::~Cos2sTypeDirectionalSpreadingFunction()
{

}

// Estimation of Directional Wave Spectrum Using Measurement Array Pressure Data on Bottom-Mounted Offshore Structure in Incident and Diffracted Wave Field, Eq. 22
double  Cos2sTypeDirectionalSpreadingFunction::computeSpreadingFunction(double waveDirection, double principalWaveDirection, double spreadingExponent)
{
    double C = tgamma(spreadingExponent + 1) * tgamma(spreadingExponent + 1.00)/ tgamma(2 * spreadingExponent + 1.00);

    double value = C * pow(cos((waveDirection - principalWaveDirection)/2), 2 * spreadingExponent);

    return value;
}

PyObject* Cos2sTypeDirectionalSpreadingFunction::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new Cos2sTypeDirectionalSpreadingFunctionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}