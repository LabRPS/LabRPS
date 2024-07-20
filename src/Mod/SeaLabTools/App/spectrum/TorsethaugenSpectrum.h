#ifndef TORSETHAUGEN_SPECTRUM_H
#define TORSETHAUGEN_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "SeaSurfaceSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport TorsethaugenSpectrum : public SeaSurfaceSpectrum
{
public:
    TorsethaugenSpectrum();
    ~TorsethaugenSpectrum();

    //this computes the along wind spectrum
    double computeSpectrum(double frequency, double significantWaveHeight, double peakPeriod, bool autoGamma, bool autoSigma, double gamma, double sigma1, double sigma2, bool isDouble);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //TORSETHAUGEN_SPECTRUM_H
