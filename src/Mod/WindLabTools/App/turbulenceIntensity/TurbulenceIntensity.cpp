#include "PreCompiled.h"
#include "TurbulenceIntensity.h"
#include <math.h>
#include <Mod/WindLabTools/App/turbulenceIntensity/TurbulenceIntensityPy.h>


using namespace WindLabTools;

TurbulenceIntensity::TurbulenceIntensity()
{

}

TurbulenceIntensity::~TurbulenceIntensity()
{

}
double  TurbulenceIntensity::computeASCETurbulenceIntensityValue(const double &height, const double &intensity10)
{
    double value = 0.00;

    try {
        value = intensity10 * pow((10.00 / height), (1.00 / 6.00));
    }
    catch (const std::exception& e) {
        std::string msg("WindLabTools::TurbulenceIntensity: ");
        msg += e.what();
        throw Base::RuntimeError(msg);
    }
    return value;
}

double TurbulenceIntensity::computeASNZ1170TurbulenceIntensityValue(const double& height, const double& intensity10, const double& exponent)
{
    double value = 0.00;

    try {
        value = intensity10 * pow((10.00 / height), exponent);
    }
    catch (const std::exception& e) {
        std::string msg("WindLabTools::TurbulenceIntensity: ");
        msg += e.what();
        throw Base::RuntimeError(msg);
    }
    return value;
}

double TurbulenceIntensity::computeEurocodeTurbulenceIntensityValue(const double& height, const double& referenceHeight)
{
    const double value = 1.00 / log(height / referenceHeight);
    return value;
}
double TurbulenceIntensity::computeIS875TurbulenceIntensityValue(const double& height, const double& referenceHeight)
{
    const double value = 0.466 - 0.1358 * log10(height / referenceHeight);
    return value;

    
}
double TurbulenceIntensity::computeISOTurbulenceIntensityValue(const double& height, const double& referenceHeight)
{
    const double value = 1.00 / log(height / referenceHeight);
    return value;
}

PyObject* TurbulenceIntensity::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new TurbulenceIntensityPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}