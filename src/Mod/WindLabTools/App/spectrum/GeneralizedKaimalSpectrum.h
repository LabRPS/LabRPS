#ifndef GENERALIZEDKAIMALSPECTRUM_H
#define GENERALIZEDKAIMALSPECTRUM_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include "WindSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace WindLabTools {

class WindLabToolsExport GeneralizedKaimalSpectrum : public WindSpectrum
{
public:
    GeneralizedKaimalSpectrum();
    ~GeneralizedKaimalSpectrum();

    double computeGeneralizedKaimalWindAutoSpectrum(const double &frequency,
                                                       const double &height,
                                                       const double &meanSpeed,
                                                       const double &shearVelocity,
                                                       const double &a = 200.0,
                                                       const double &b = 1.0,
                                                       const double &c = 0.0,
                                                       const double &d = 1.0,
                                                       const double &e = 1.0,
                                                       const double &f = 1.0,
                                                       const double &g = 1.0,
                                                       const double &h = 50.0,
                                                       const double &i = 1.0,
                                                       const double &j = 5.0/3.0);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //GENERALIZEDKAIMALSPECTRUM_H
