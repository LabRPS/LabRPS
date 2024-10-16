#ifndef DAVENPORTSPECTRUM_H
#define DAVENPORTSPECTRUM_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include "SeismicGroundMotionSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport CloughPenzienSpectrum : public SeismicGroundMotionSpectrum
{
public:
    CloughPenzienSpectrum();
    ~CloughPenzienSpectrum();

    //this computes the along wind spectrum
    double computeCloughPenzienSpectrum(const double& frequency, const double& groundNaturalFrequency, const double &groundDampingRatio, const double &secondFilterLayerFrequency, const double &secondFilterLayerDampingRatio, const double &constantSpectralIntensity);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //DAVENPORTSPECTRUM_H
