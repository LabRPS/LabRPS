#ifndef GENERALIZEDVONKARMANSPECTRUM_H
#define GENERALIZEDVONKARMANSPECTRUM_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include "WindSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport GeneralizedVonKarmanSpectrum : public WindSpectrum
{
public:
    GeneralizedVonKarmanSpectrum();
    ~GeneralizedVonKarmanSpectrum();

    //this computes the along wind spectrum
    double computeGeneralizedVonKarmanWindAutoSpectrum(const double &frequency,
                                                       const double &integralLengthScale,
                                                       const double &meanSpeed,
                                                       const double &standardDeviation,
                                                       const double &a = 4.0,
                                                       const double &b = 0.0,
                                                       const double &c = 1.0,
                                                       const double &d = 1.0,
                                                       const double &e = 1.0,
                                                       const double &f = 1.0,
                                                       const double &g = 1.0,
                                                       const double &h = 70.8,
                                                       const double &i = 2.0,
                                                       const double &j = 5.0/6.0);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //GENERALIZEDVONKARMANSPECTRUM_H
