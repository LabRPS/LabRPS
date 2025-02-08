#include "PreCompiled.h"
#include "HasselmannDirectionalSpreadingFunction.h"
#include <math.h>
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/HasselmannDirectionalSpreadingFunctionPy.h>

#define PI_   3.14159265358979323846

using namespace SeaLabTools;

HasselmannDirectionalSpreadingFunction::HasselmannDirectionalSpreadingFunction()
{

}

HasselmannDirectionalSpreadingFunction::~HasselmannDirectionalSpreadingFunction()
{

}

// Elsevier ocean engineering book series 2,Wind Generated Ocean Waves (1999, Elsevier), P.127
double  HasselmannDirectionalSpreadingFunction::computeSpreadingFunction(double waveDirection, double frequency, double modalFrequency, double meanWindSpeed)
{
    double s = 0.0;
    double mu = -2.33 - 1.45 * (meanWindSpeed*modalFrequency / 9.8 - 1.17);
    if (frequency < 1.05 * modalFrequency)
        s = 0.97 * pow(frequency / modalFrequency, 4.06);
    else
        s = 9.77 * pow(frequency / modalFrequency, mu);
    double value = (pow(2, 2 * s - 1) / PI_) * tgamma(s + 1) * tgamma(s + 1) / tgamma(2 * s + 1) * pow(fabs(waveDirection / 2), 2 * s);
    return value;      
    
   /* double s = 0.0;
    if((frequency <= modalFrequency) && (meanWindSpeed > waveCelerity) )
    {
        double ex = -(2.33+0.06) - (1.45+0.45) * (meanWindSpeed/waveCelerity - 1.17);
        s = (9.77+0.43) * pow(frequency/modalFrequency, ex);
    }
    else if((frequency > modalFrequency) && (meanWindSpeed > waveCelerity) )
    {
        double ex = 4.06+0.22;
        s = (6.97+0.83) * pow(frequency/modalFrequency, ex);
    }
    
    double value = (pow(2, 2*s -1)/PI_) * tgamma(s+1) * tgamma(s+1)/tgamma(2*s+1) * pow(fabs(waveDirection/2), 2*s);
   
    return value;*/
}

PyObject* HasselmannDirectionalSpreadingFunction::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new HasselmannDirectionalSpreadingFunctionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}