#ifndef SWOP_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
#define SWOP_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "DirectionalSpreadingFunction.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport SwopDirectionalSpreadingFunction : public DirectionalSpreadingFunction
{
public:
    SwopDirectionalSpreadingFunction();
    ~SwopDirectionalSpreadingFunction();

    //this computes the along wind spectrum
    double computeSpreadingFunction(double waveDirection, double frequency, double tenMetersHeightMeanWindSpeed);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //SWOP_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
