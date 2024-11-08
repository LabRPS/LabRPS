#ifndef BASE_RESPONSE_SPECTRUM_H
#define BASE_RESPONSE_SPECTRUM_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <string>
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport BaseDesignResponseSpectrum
{
public:

    //constructor
     BaseDesignResponseSpectrum();

    //destructor
    virtual ~BaseDesignResponseSpectrum();

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //BASE_RESPONSE_SPECTRUM_H
