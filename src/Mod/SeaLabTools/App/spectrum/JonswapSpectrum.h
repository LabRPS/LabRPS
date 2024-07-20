#ifndef JONSWAP_SPECTRUM_H
#define JONSWAP_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "SeaSurfaceSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport JonswapSpectrum : public SeaSurfaceSpectrum
{
public:
    JonswapSpectrum();
    ~JonswapSpectrum();

    //this computes the along wind spectrum
    double computeSpectrum(double frequency, double significantWaveHeight, double peakPeriod, bool autoGamma=true, bool autoSigma=true, double gamma=0, double sigma1=0, double sigma2=0);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //JONSWAP_SPECTRUM_H
