#ifndef MITSUYASU_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
#define MITSUYASU_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "DirectionalSpreadingFunction.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport MitsuyasuDirectionalSpreadingFunction : public DirectionalSpreadingFunction
{
public:
    MitsuyasuDirectionalSpreadingFunction();
    ~MitsuyasuDirectionalSpreadingFunction();

    //this computes the along wind spectrum
    double computeSpreadingFunction(double waveDirection, double frequency, double modalFrequency, double tenMeterHeightmeanWindSpeed);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //MITSUYASU_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
