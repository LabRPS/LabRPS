#ifndef COS_TWOS_TYPE_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
#define COS_TWOS_TYPE_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "DirectionalSpreadingFunction.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport Cos2sTypeDirectionalSpreadingFunction : public DirectionalSpreadingFunction
{
public:
    Cos2sTypeDirectionalSpreadingFunction();
    ~Cos2sTypeDirectionalSpreadingFunction();

    //this computes the along wind spectrum
    double computeSpreadingFunction(double waveDirection, double principalWaveDirection, double spreadingExponent);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //COS_TWOS_TYPE_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
