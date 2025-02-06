#include "PreCompiled.h"
#include "BorgmanDirectionalSpreadingFunction.h"
#include <math.h>
#include <boost/math/special_functions/bessel.hpp>

#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/BorgmanDirectionalSpreadingFunctionPy.h>

#define PI_   3.14159265358979323846

using namespace SeaLabTools;

BorgmanDirectionalSpreadingFunction::BorgmanDirectionalSpreadingFunction()
{

}

BorgmanDirectionalSpreadingFunction::~BorgmanDirectionalSpreadingFunction()
{

}

// https://www.orcina.com/webhelp/OrcaFlex/Content/html/Wavetheory.htm#WaveSpreadingTheory
double  BorgmanDirectionalSpreadingFunction::computeSpreadingFunction(double waveDirection, double  angleOfPropagationOfPredominantWaveEnergy, double positiveConstant)
{
    double value = (1.00 /(2 * PI_ * boost::math::cyl_bessel_i(0, positiveConstant))) * exp(positiveConstant * cos(waveDirection - angleOfPropagationOfPredominantWaveEnergy));

    return value;
}

PyObject* BorgmanDirectionalSpreadingFunction::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new BorgmanDirectionalSpreadingFunctionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}