#ifndef LONGUEHIGGINS_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
#define LONGUEHIGGINS_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "DirectionalSpreadingFunction.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport LonguetHigginsDirectionalSpreadingFunction : public DirectionalSpreadingFunction
{
public:
    LonguetHigginsDirectionalSpreadingFunction();
    ~LonguetHigginsDirectionalSpreadingFunction();

    //this computes the along wind spectrum
    double computeSpreadingFunction(double waveDirection, double frequency, double peakFrequency, double tenMeterHeightMeanWindSpeed, double mainDirection);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //LONGUEHIGGINS_DIRECTIONAL_WAVE_SPFREADING_FUNCTION_H
