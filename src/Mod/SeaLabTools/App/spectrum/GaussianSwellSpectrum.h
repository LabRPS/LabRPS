#ifndef GUASSIAN_SPECTRUM_H
#define GUASSIAN_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "SeaSurfaceSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport GaussianSwellSpectrum : public SeaSurfaceSpectrum
{
public:
    GaussianSwellSpectrum();
    ~GaussianSwellSpectrum();

    //this computes the along wind spectrum
    double computeSpectrum(double frequency, double significantWaveHeight, double peakFrequency, double sigma);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //GUASSIAN_SPECTRUM_H
