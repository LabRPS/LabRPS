#include "PreCompiled.h"
#include "SwopDirectionalSpreadingFunction.h"
#include <math.h>
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/SwopDirectionalSpreadingFunctionPy.h>

#define PI_   3.14159265358979323846

using namespace SeaLabTools;

SwopDirectionalSpreadingFunction::SwopDirectionalSpreadingFunction()
{

}

SwopDirectionalSpreadingFunction::~SwopDirectionalSpreadingFunction()
{

}

// Study on Numerical Simulation and Electromagnetic Scattering of Time-Invariant Freak Waves, Eq.5
double  SwopDirectionalSpreadingFunction::computeSpreadingFunction(double waveDirection, double frequency, double tenMetersHeightMeanWindSpeed)
{
    double omega0 = 0.855 * 9.8 /tenMetersHeightMeanWindSpeed;
    double value = (1.00/PI_) * (1.00 + (0.5 + 0.82 * exp(-pow(frequency/omega0, 4)/2.00)) * cos(2.00 * waveDirection) + 0.32 * exp(-pow(frequency/omega0, 4.00)/2.00) * cos(4.00 * waveDirection));
    return value;
}

PyObject* SwopDirectionalSpreadingFunction::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new SwopDirectionalSpreadingFunctionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}