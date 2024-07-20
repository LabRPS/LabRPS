#ifndef EXPONENTIALMODULATION_H
#define EXPONENTIALMODULATION_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport ExponentialModulation
{
public:
    ExponentialModulation();
    ~ExponentialModulation();

    double computeCoefficientA(const double& alpha, const double& beta);
    double computeModulation(const double& time, const double& alpha, const double& beta);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //EXPONENTIALMODULATION_H
