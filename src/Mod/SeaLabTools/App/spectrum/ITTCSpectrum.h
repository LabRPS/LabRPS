#ifndef ITTC_SPECTRUM_H
#define ITTC_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "SeaSurfaceSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport ITTCSpectrum : public SeaSurfaceSpectrum
{
public:
    ITTCSpectrum();
    ~ITTCSpectrum();

    //this computes the along wind spectrum
    double computeSpectrum(double frequency, double significantWaveHeight, double alpha = 0.0081);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //ITTC_SPECTRUM_H
