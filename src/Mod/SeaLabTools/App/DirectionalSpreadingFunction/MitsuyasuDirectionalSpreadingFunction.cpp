#include "PreCompiled.h"
#include "MitsuyasuDirectionalSpreadingFunction.h"
#include <math.h>
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/MitsuyasuDirectionalSpreadingFunctionPy.h>

#define PI_   3.14159265358979323846

using namespace SeaLabTools;

MitsuyasuDirectionalSpreadingFunction::MitsuyasuDirectionalSpreadingFunction()
{

}

MitsuyasuDirectionalSpreadingFunction::~MitsuyasuDirectionalSpreadingFunction()
{

}

// OCEAN WAVES, CAMBRIDGE OCEAN TECHNOLOGY SERIES: 6, Eq. 7.116
double  MitsuyasuDirectionalSpreadingFunction::computeSpreadingFunction(double waveDirection, double frequency, double modalFrequency, double tenMeterHeightmeanWindSpeed)
{
    double Sm = pow(11.5 * modalFrequency * tenMeterHeightmeanWindSpeed/9.8, -2.5);
    double s = 0.0;
    if(frequency <= modalFrequency)
    s = Sm * pow(frequency/modalFrequency, 5.00);
    else
    s = Sm * pow(frequency/modalFrequency, -2.5);
    double value = (pow(2, 2*s -1)/PI_) * tgamma(s+1) * tgamma(s+1)/tgamma(2*s+1) * pow(fabs(waveDirection/2), 2*s);
    return value;
}

PyObject* MitsuyasuDirectionalSpreadingFunction::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new MitsuyasuDirectionalSpreadingFunctionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}