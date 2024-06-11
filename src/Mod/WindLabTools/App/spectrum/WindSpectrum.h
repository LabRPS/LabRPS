#ifndef WINDSPECTRUM_H
#define WINDSPECTRUM_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <string>
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport WindSpectrum
{
public:

    //constructor
     WindSpectrum();

    //destructor
    virtual ~WindSpectrum();

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //WINDSPECTRUM_H
