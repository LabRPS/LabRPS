#ifndef ORCAFLEX_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
#define ORCAFLEX_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "DirectionalSpreadingFunction.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport OrcaFlexDirectionalSpreadingFunction : public DirectionalSpreadingFunction
{
public:
    OrcaFlexDirectionalSpreadingFunction();
    ~OrcaFlexDirectionalSpreadingFunction();

    //this computes the along wind spectrum
    double computeSpreadingFunction(double waveDirection, double principalWaveDirection, double spreadingExponent);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //ORCAFLEX_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
