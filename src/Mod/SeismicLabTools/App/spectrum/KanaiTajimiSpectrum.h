#ifndef KANAITAJIMISPECTRUM_H
#define KANAITAJIMISPECTRUM_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include "SeismicGroundMotionSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport KanaiTajimiSpectrum : public SeismicGroundMotionSpectrum
{
public:
    KanaiTajimiSpectrum();
    ~KanaiTajimiSpectrum();

    //this computes the along wind spectrum
    double computeKanaiTajimiSpectrum(const double& frequency, const double& groundNaturalFrequency, const double &groundDampingRatio, const double &constantSpectralIntensity);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //KANAITAJIMISPECTRUM_H
