#ifndef OCHIANDHUBBLE_SPECTRUM_H
#define OCHIANDHUBBLE_SPECTRUM_H

#include <Mod/SeaLabTools/SeaLabToolsGlobal.h>
#include "SeaSurfaceSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeaLabTools {

class SeaLabToolsExport OchiAndHubbleSpectrum : public SeaSurfaceSpectrum
{
public:
    OchiAndHubbleSpectrum();
    ~OchiAndHubbleSpectrum();

    //this computes the along wind spectrum
    double computeSpectrum(double frequency, double peakShape1, double peakShape2, double peakFrequency1, double peakFrequency2, double significantWaveHeight1, double significantWaveHeight2, bool autoPara, double significantWaveHeight);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //OCHIANDHUBBLE_SPECTRUM_H
