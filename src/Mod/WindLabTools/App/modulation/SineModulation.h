#ifndef SINEMODULATION_H
#define SINEMODULATION_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport SineModulation
{
public:
    SineModulation();
    ~SineModulation();

    double  computeModulation(const double &time, const double &pulseDuration);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //SINEMODULATION_H
