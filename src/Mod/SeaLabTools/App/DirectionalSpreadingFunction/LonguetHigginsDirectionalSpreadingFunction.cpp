#include "PreCompiled.h"
#include "LonguetHigginsDirectionalSpreadingFunction.h"
#include <math.h>
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/LonguetHigginsDirectionalSpreadingFunctionPy.h>

#define PI_   3.14159265358979323846

using namespace SeaLabTools;

LonguetHigginsDirectionalSpreadingFunction::LonguetHigginsDirectionalSpreadingFunction()
{

}

LonguetHigginsDirectionalSpreadingFunction::~LonguetHigginsDirectionalSpreadingFunction()
{

}

// OCEAN WAVES, CAMBRIDGE OCEAN TECHNOLOGY SERIES: 6, Eq. 7.116
double  LonguetHigginsDirectionalSpreadingFunction::computeSpreadingFunction(double waveDirection, double frequency, double peakFrequency, double tenMeterHeightMeanWindSpeed, double mainDirection)
{
    double mu = 0.0;
    if(frequency <= peakFrequency)
    mu = 5;
    else
    mu = -2.5;
    double s = 11.5 * pow(9.8/(peakFrequency * tenMeterHeightMeanWindSpeed), 2.5) * pow(frequency/peakFrequency, mu);
    double value = (1.00/(2*sqrt(PI_))) * tgamma(s+1)/tgamma(s+0.5) * pow(cos((mainDirection - waveDirection)/2), 2*s);
    return value;
}

PyObject* LonguetHigginsDirectionalSpreadingFunction::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new LonguetHigginsDirectionalSpreadingFunctionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}