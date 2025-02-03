#include "PreCompiled.h"
#include "OrcaFlexDirectionalSpreadingFunction.h"
#include <math.h>
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/OrcaFlexDirectionalSpreadingFunctionPy.h>

#define PI_   3.14159265358979323846

using namespace SeaLabTools;

OrcaFlexDirectionalSpreadingFunction::OrcaFlexDirectionalSpreadingFunction()
{

}

OrcaFlexDirectionalSpreadingFunction::~OrcaFlexDirectionalSpreadingFunction()
{

}

// https://www.orcina.com/webhelp/OrcaFlex/Content/html/Wavetheory.htm#WaveSpreadingTheory
double  OrcaFlexDirectionalSpreadingFunction::computeSpreadingFunction(double waveDirection, double principalWaveDirection, double spreadingExponent)
{
    double C = tgamma((spreadingExponent/2)+1)/(sqrt(PI_) * tgamma((spreadingExponent/2) + 0.5));

    double value = C * pow(cos(waveDirection - principalWaveDirection), spreadingExponent);

    return value;
}

PyObject* OrcaFlexDirectionalSpreadingFunction::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new OrcaFlexDirectionalSpreadingFunctionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}