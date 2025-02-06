#ifndef ISSC_SPECTRUM_H
#define ISSC_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "SeaSurfaceSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport ISSCSpectrum : public SeaSurfaceSpectrum
{
public:
    ISSCSpectrum();
    ~ISSCSpectrum();

    //this computes the along wind spectrum
    double computeSpectrum(double frequency, double significantWaveHeight, double modalFrequency, double c1 = 0.3123, double c2 = -1.2489);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //ISSC_SPECTRUM_H
