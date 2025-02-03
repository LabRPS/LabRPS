#ifndef SEASURFACE_DIRECTIONALSPREADINGFUNCTION_H
#define SEASURFACE_DIRECTIONALSPREADINGFUNCTION_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include <string>
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport DirectionalSpreadingFunction
{
public:

    //constructor
     DirectionalSpreadingFunction();

    //destructor
    virtual ~DirectionalSpreadingFunction();

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //SEASURFACE_SPECTRUM_H
