#include "PreCompiled.h"
#include "CosineSquareDirectionalSpreadingFunction.h"
#include <math.h>
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/CosineSquareDirectionalSpreadingFunctionPy.h>

#define PI_   3.14159265358979323846

using namespace SeaLabTools;

CosineSquareDirectionalSpreadingFunction::CosineSquareDirectionalSpreadingFunction()
{

}

CosineSquareDirectionalSpreadingFunction::~CosineSquareDirectionalSpreadingFunction()
{

}

// OCEAN WAVES, CAMBRIDGE OCEAN TECHNOLOGY SERIES: 6, Eq. 7.115
double  CosineSquareDirectionalSpreadingFunction::computeSpreadingFunction(double waveDirection)
{
    double value = 0.00;
    if((waveDirection > -PI_/2) && (waveDirection < PI_/2))
    value = (2.00/PI_) * cos(waveDirection) * cos(waveDirection);
    return value;
}

PyObject* CosineSquareDirectionalSpreadingFunction::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new CosineSquareDirectionalSpreadingFunctionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}