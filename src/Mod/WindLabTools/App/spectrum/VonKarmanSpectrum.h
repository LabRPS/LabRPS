#ifndef VONKARMANSPECTRUM_H
#define VONKARMANSPECTRUM_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include "WindSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport VonKarmanSpectrum : public WindSpectrum
{
public:
    VonKarmanSpectrum();
    ~VonKarmanSpectrum();

    //this computes the along wind spectrum
    double computeAlongWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &integralLengthScale, const double &standardDeviation, double Par1 = 4.0, double Par2 =70.8);

    //this computes the across wind spectrum
    double computeAcrossWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &integralLengthScale, const double &standardDeviation, double Par1 = 4.0, double Par2 = 775.2, double Par3 = 283.2);

    //this computes the vertical wind spectrum
    double computeVerticalWindAutoSpectrum(const double &frequency, const double &meanSpeed, const double &integralLengthScale, const double &standardDeviation, double Par1 = 4.0, double Par2 = 775.2, double Par3 = 283.2);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //VONKARMANSPECTRUM_H
