#ifndef CONSTANTMODULATION_H
#define CONSTANTMODULATION_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport ConstantModulation
{
public:
    ConstantModulation();
    ~ConstantModulation();

    double  computeModulation(const double &time, const double &constantValue = 1);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //CONSTANTMODULATION_H
