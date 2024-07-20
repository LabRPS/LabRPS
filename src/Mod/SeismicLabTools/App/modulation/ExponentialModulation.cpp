#include "PreCompiled.h"
#include "ExponentialModulation.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/modulation/ExponentialModulationPy.h>

using namespace SeismicLabTools;

ExponentialModulation::ExponentialModulation()
{

}

ExponentialModulation::~ExponentialModulation()
{

}
double ExponentialModulation::computeCoefficientA(const double& alpha, const double& beta)
{
    double Tmax = (log(alpha) - log(beta)) / (alpha - beta);
    double A = 1 / (exp(-alpha * Tmax) - exp(-beta * Tmax));
    return A;
}

double  ExponentialModulation::computeModulation(const double &time, const double &alpha, const double &beta)
{
    double A = computeCoefficientA(alpha, beta);
    double value = A * (exp(-alpha * time) - exp(-beta * time));
    return value;
}

PyObject* ExponentialModulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ExponentialModulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}