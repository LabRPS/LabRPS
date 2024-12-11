#ifndef KOUGIOUTZOGLOU_AND_SPANO_SPECTRUM_H
#define KOUGIOUTZOGLOU_AND_SPANO_SPECTRUM_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include "SeismicGroundMotionSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport KougioumtzoglouAndSpanoSpectrum : public SeismicGroundMotionSpectrum
{
public:
    KougioumtzoglouAndSpanoSpectrum();
    ~KougioumtzoglouAndSpanoSpectrum();

    double computeKougioumtzoglouAndSpanoSpectrum(const double& frequency, const double& time, const double &constantS = 0.03);
    
    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //KOUGIOUTZOGLOU_AND_SPANO_SPECTRUM_H
