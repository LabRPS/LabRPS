#ifndef DOMINIKETALMODULATION_H
#define DOMINIKETALMODULATION_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport DominikEtAl2013
{
public:
    DominikEtAl2013();
    ~DominikEtAl2013();

    double  computeModulationA(const double &time, const double &nonZeroUpperBound = 200);
    double  computeModulationB(const double &time, const double &nonZeroUpperBound = 200);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //DOMINIKETALMODULATION_H
