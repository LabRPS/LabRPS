#ifndef THREEPARAMETERSMODULATION_H
#define THREEPARAMETERSMODULATION_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport ThreeParametersModulation
{
public:
    ThreeParametersModulation();
    ~ThreeParametersModulation();

    double computeModulation(const double &time, const double &alpha, const double &betta, const double &lambda);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //THREEPARAMETERSMODULATION_H
