#ifndef EXPONENTIALMODULATION_H
#define EXPONENTIALMODULATION_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport ExponentialModulation
{
public:
    ExponentialModulation();
    ~ExponentialModulation();

    double  computeModulation(const double &time, const double &timeOfMax, const double &stormLength);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //EXPONENTIALMODULATION_H
