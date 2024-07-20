#ifndef TRAPEZOIDALMODULATION_H
#define TRAPEZOIDALMODULATION_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport TrapezoidalModulation
{
public:
    TrapezoidalModulation();
    ~TrapezoidalModulation();

    double computeModulation(const double& time, const double& riseTime, const double& levelTime, const double &maxTime);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //TRAPEZOIDALMODULATION_H
