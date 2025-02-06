#ifndef HASSELMANN_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
#define HASSELMANN_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "DirectionalSpreadingFunction.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport HasselmannDirectionalSpreadingFunction : public DirectionalSpreadingFunction
{
public:
    HasselmannDirectionalSpreadingFunction();
    ~HasselmannDirectionalSpreadingFunction();

    //this computes the along wind spectrum
    double computeSpreadingFunction(double waveDirection, double frequency, double modalFrequency, double meanWindSpeed, double waveCelerity);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //HASSELMANN_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
