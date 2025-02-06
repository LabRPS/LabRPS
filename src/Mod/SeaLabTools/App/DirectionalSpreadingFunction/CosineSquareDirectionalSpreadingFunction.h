#ifndef COSSQUARE_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
#define COSSQUARE_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "DirectionalSpreadingFunction.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport CosineSquareDirectionalSpreadingFunction : public DirectionalSpreadingFunction
{
public:
    CosineSquareDirectionalSpreadingFunction();
    ~CosineSquareDirectionalSpreadingFunction();

    //this computes the along wind spectrum
    double computeSpreadingFunction(double waveDirection);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //COSSQUARE_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
