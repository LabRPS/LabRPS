#ifndef HARRISSPECTRUM_H
#define HARRISSPECTRUM_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include "WindSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport HarrisSpectrum : public WindSpectrum
{
public:
    HarrisSpectrum();
    ~HarrisSpectrum();

    //this computes the along wind spectrum
    double computeAlongWindAutoSpectrum(const double &frequency, const double &shearVelocity, const double &meanSpeed10 = 30.0);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //HARRISSPECTRUM_H
