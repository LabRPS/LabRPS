#ifndef JENNINGSETAL1968MODULATION_H
#define JENNINGSETAL1968MODULATION_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport JenningsEtAl1968Modulation
{
public:
    JenningsEtAl1968Modulation();
    ~JenningsEtAl1968Modulation();

    double  computeModulation(const double &time, const double &riseTime, const double &levelTime, const double &alpha, const double &power);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //JENNINGSETAL1968MODULATION_H
