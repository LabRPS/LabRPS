#ifndef WEN_SPECTRUM_H
#define WEN_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "SeaSurfaceSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport WENSpectrum : public SeaSurfaceSpectrum
{
public:
    WENSpectrum();
    ~WENSpectrum();

    //this computes the along wind spectrum
    double computeSpectrum(double frequency, double significantWaveHeight, double significantPeriod, double depthParameter, double tenMetersHeightMeanWindSpeed);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //WEN_SPECTRUM_H
