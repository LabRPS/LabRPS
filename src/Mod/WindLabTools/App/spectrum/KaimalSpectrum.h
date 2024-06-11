#ifndef KAIMALSPECTRUM_H
#define KAIMALSPECTRUM_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include "WindSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport KaimalSpectrum : public WindSpectrum
{
public:
    KaimalSpectrum();
    ~KaimalSpectrum();

    //this computes the along wind spectrum
    double computeAlongWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1 = 200.0, double Par2 = 50.0);

    //this computes the across wind spectrum
    double computeAcrossWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1 = 17.0, double Par2 = 9.5);

    //this computes the vertical wind spectrum
    double computeVerticalWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, double Par1 = 2.0, double Par2 = 5.3);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //KAIMALSPECTRUM_H
