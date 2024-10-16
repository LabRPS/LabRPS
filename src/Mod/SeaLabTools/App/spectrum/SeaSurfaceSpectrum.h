#ifndef SEASURFACE_SPECTRUM_H
#define SEASURFACE_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include <string>
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport SeaSurfaceSpectrum
{
public:

    //constructor
     SeaSurfaceSpectrum();

    //destructor
    virtual ~SeaSurfaceSpectrum();

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //SEASURFACE_SPECTRUM_H
