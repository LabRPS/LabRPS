#ifndef HUZHOU_SPECTRUM_H
#define HUZHOU_SPECTRUM_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include "SeismicGroundMotionSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport HuZhouSpectrum : public SeismicGroundMotionSpectrum
{
public:
    HuZhouSpectrum();
    ~HuZhouSpectrum();

    //this computes the along wind spectrum
    double computeHuZhouSpectrum(const double& frequency, const double& groundNaturalFrequency, const double &groundDampingRatio, const double &secondFilterLayerDampingRatio, const double &constantSpectralIntensity);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //HUZHOU_SPECTRUM_H
