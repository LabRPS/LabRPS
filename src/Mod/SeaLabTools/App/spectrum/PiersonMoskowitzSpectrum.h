#ifndef PIERSONMOSKOWITZ_SPECTRUM_H
#define PIERSONMOSKOWITZ_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "SeaSurfaceSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport PiersonMoskowitzSpectrum : public SeaSurfaceSpectrum
{
public:
    PiersonMoskowitzSpectrum();
    ~PiersonMoskowitzSpectrum();

    //this computes the along wind spectrum
    double computeSpectrum(double frequency, double significantWaveHeight, double peakPeriod);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //JONSWAP_SPECTRUM_H
