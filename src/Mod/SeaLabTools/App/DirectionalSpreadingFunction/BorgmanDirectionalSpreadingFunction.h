#ifndef BORGMAN_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
#define BORGMAN_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "DirectionalSpreadingFunction.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport BorgmanDirectionalSpreadingFunction : public DirectionalSpreadingFunction
{
public:
    BorgmanDirectionalSpreadingFunction();
    ~BorgmanDirectionalSpreadingFunction();

    //this computes the along wind spectrum
    double computeSpreadingFunction(double waveDirection, double  angleOfPropagationOfPredominantWaveEnergy, double positiveConstant);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //BORGMAN_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
