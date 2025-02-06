#ifndef SCOTT_SPECTRUM_H
#define SCOTT_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "SeaSurfaceSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport ScottSpectrum : public SeaSurfaceSpectrum
{
public:
    ScottSpectrum();
    ~ScottSpectrum();

    //this computes the along wind spectrum
    double computeSpectrum(double frequency, double significantWaveHeight, double peakFrequency);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //SCOTT_SPECTRUM_H
