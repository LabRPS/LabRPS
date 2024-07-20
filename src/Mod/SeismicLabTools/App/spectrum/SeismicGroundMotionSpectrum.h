#ifndef SEISMICGROUNDMOTIONSPECTRUM_H
#define SEISMICGROUNDMOTIONSPECTRUM_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <string>
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport SeismicGroundMotionSpectrum
{
public:

    //constructor
     SeismicGroundMotionSpectrum();

    //destructor
    virtual ~SeismicGroundMotionSpectrum();

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //WINDSPECTRUM_H
