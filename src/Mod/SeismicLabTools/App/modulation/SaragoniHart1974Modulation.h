#ifndef SARAGONIHART1974MODULATION_H
#define SARAGONIHART1974MODULATION_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport SaragoniHart1974Modulation
{
public:
    SaragoniHart1974Modulation();
    ~SaragoniHart1974Modulation();

    double  computeModulation(const double &time, const double &alphaOne, const double &alphaTwo, const double &alphaThree);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //SARAGONIHART1974MODULATION_H
