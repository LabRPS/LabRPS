#include "PreCompiled.h"
#include "HongandHong2021MeanWindSpeed.h"
#include <math.h>
#include <Mod/WindLabTools/App/meanWindSpeed/HongandHong2021MeanWindSpeedPy.h>

using namespace WindLabTools;

HongandHong2021MeanWindSpeed::HongandHong2021MeanWindSpeed()
{

}

HongandHong2021MeanWindSpeed::~HongandHong2021MeanWindSpeed()
{

}

double  HongandHong2021MeanWindSpeed::computeMeanWindSpeed(const double &height, const double &xCoordinate, const double &time)
{
    return 30.00 * pow((height) / 10, 0.12) * (1.00/8.00) * (7.00 + sin(3.14 * xCoordinate/450.00)) * (0.50) * (1.00 + sin(3.14 * time/600.00));
}

PyObject* HongandHong2021MeanWindSpeed::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new HongandHong2021MeanWindSpeedPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}